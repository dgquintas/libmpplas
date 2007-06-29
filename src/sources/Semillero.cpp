/* 
 * $Id$ 
 */

#include "Seedbank.h"
#include "Funciones.h"
#include "constants.h"
#include "err.h"
#include "Hash.h"
#include <ctime>
#include <fstream>
#ifdef __WIN32__
	#include <windows.h>
	#include <wincrypt.h>
#endif


namespace mpplas{

  Seedbank::Seedbank(void)
  {
  }
    
  Z Seedbank::leerSemillaSegura(size_t numBytes)
  {
		_randomData = _source(numBytes);
		
     Z resultado;
     resultado.leerBytes(_randomData.begin(), _randomData.end());

     return resultado;
  }
  
  Z Seedbank::leerSemilla(size_t numBytes)
  {
    Funciones *funcs = Funciones::getInstance();
    Hash* hash; funcs->getFunc(hash);
    static size_t contador = 0;
//    _randomData.resize( hash->numBitsResumen() >> 3);
    
    if( (contador >= Constants::UMBRAL_SEMILLA) || (contador == 0) ){ //contador==0 para la 1ª llamada
			_randomData = _source( hash->numBitsResumen() >> 3);
      contador = 1;
    }
    contador += numBytes;

    MiVec<uint8_t> resultadosTemp;
    MiVec<uint8_t> agitador(1,(uint8_t)0); //un dato que agite un poco las cosas al hacer hashing
    agitador[0] = ((unsigned long)time(NULL)) & 0xff;
    
    size_t nTemp = numBytes;
    MiVec<uint8_t> datosRndTemp( hash->numBitsResumen() >> 3);
    while( true ){
      hash->inicializar();
      hash->actualizar(_randomData);
      hash->actualizar(agitador);
      hash->finalizar();
      agitador[0]++;

      hash->obtenerEnteroResumen().escribirBytes(datosRndTemp.begin(), datosRndTemp.end());
      
      resultadosTemp.insert( resultadosTemp.end(),
                             datosRndTemp.begin(), 
                             datosRndTemp.end() 
                           ); 
      nTemp -= (hash->numBitsResumen() >> 3);
      if( (nTemp > numBytes) || (nTemp == 0) ) // es decir, cuando se produzca underflow => nTemp < 0
        break;
    }

    Z resultado;
    resultado.leerBytes(resultadosTemp.begin(), resultadosTemp.begin()+numBytes);
    
    return resultado;
  }


  MiVec<uint8_t> Seedbank::_source(size_t numBytes)
  {
		MiVec<uint8_t> rnd(numBytes);
#ifdef __WIN32__
		//utilizar CryptGetRandom
  	HCRYPTPROV crypt_prov;
		uint8_t ptr;
	  if( !CryptAcquireContext (&crypt_prov, NULL, MS_DEF_PROV, PROV_RSA_FULL,
			       CRYPT_VERIFYCONTEXT | CRYPT_MACHINE_KEYSET) ){
      throw Errors::FuenteEntropiaInvalida();
    }

		for(size_t i=0; i < numBytes; i++){
			if( !CryptGenRandom(crypt_prov, 1, (BYTE *)&ptr) ){
        throw Errors::FuenteEntropiaInvalida();
      }
			rnd[i] = ptr;
		}

#else
    //Se *supone* estar en un sistema tipo UNIX con /dev/urandom
		std::ifstream* urandom;
    urandom = new std::ifstream("/dev/urandom", std::ios::in | std::ios::binary );
    if( !urandom->is_open() ){
        throw Errors::FuenteEntropiaInvalida();
    }
    
    for(size_t i=0; i < numBytes; i++){
      (*urandom) >> rnd[i];
    }

		urandom->close();
		if(urandom){
			delete urandom;
    }
#endif	
		
		return rnd;
	}

  Seedbank::~Seedbank(void)
  {
  }
    
}
    
    
      
      
      
