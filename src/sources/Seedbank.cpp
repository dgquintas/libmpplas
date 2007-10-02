/* 
 * $Id$ 
 */

#include "Seedbank.h"
#include "MethodsFactory.h"
#include "Constants.h"
#include "Errors.h"
#include "Hash.h"
#include <ctime>
#include <fstream>
#ifdef __WIN32__
	#include <windows.h>
	#include <wincrypt.h>
#endif


namespace mpplas{

  Seedbank::Seedbank(void)
  { }
    
  Z Seedbank::getSecureSeed(const int numBytes)
  {
		_randomData = _source(numBytes);
		
     Z resultado;
     resultado.leerBytes(_randomData.begin(), _randomData.end());

     return resultado;
  }
  
  Z Seedbank::getSeed(const int numBytes)
  {
    MethodsFactory *funcs = MethodsFactory::getInstance();
    Hash* hash; funcs->getFunc(hash);
    static int counter = 0;
    
    if( (counter >= Constants::UMBRAL_SEMILLA) || (counter == 0) ){ //counter==0 para la 1ª llamada
			_randomData = _source( hash->numBitsResumen() >> 3);
      counter = 1;
    }
    counter += numBytes;

    MiVec<uint8_t> resultadosTemp;
    MiVec<uint8_t> salt(1,(uint8_t)0); //un dato que agite un poco las cosas al hacer hashing
    salt[0] = ((unsigned long)time(NULL)) & 0xff;
    
    int nTemp = numBytes;
    MiVec<uint8_t> datosRndTemp( hash->numBitsResumen() >> 3);
    while( nTemp > 0 ){
      hash->inicializar();
      hash->actualizar(_randomData);
      hash->actualizar(salt);
      hash->finalizar();
      salt[0]++;

      hash->obtenerEnteroResumen().escribirBytes(datosRndTemp.begin(), datosRndTemp.end());
      
      resultadosTemp.insert( resultadosTemp.end(),
                             datosRndTemp.begin(), 
                             datosRndTemp.end() 
                           ); 
      nTemp -= (hash->numBitsResumen() >> 3);
    }

    Z resultado;
    resultado.leerBytes(resultadosTemp.begin(), resultadosTemp.begin()+numBytes);
    
    return resultado;
  }


  MiVec<uint8_t> Seedbank::_source(const int numBytes)
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

		for(int i=0; i < numBytes; i++){
			if( !CryptGenRandom(crypt_prov, 1, (BYTE *)&ptr) ){
        throw Errors::FuenteEntropiaInvalida();
      }
			rnd[i] = ptr;
		}

#else
    //Se *supone* estar en un sistema tipo UNIX con /dev/urandom
		std::ifstream* const urandom(new std::ifstream("/dev/urandom", std::ios::in | std::ios::binary ));
    if( !urandom->is_open() ){
        throw Errors::FuenteEntropiaInvalida();
    }
    
    for(int i=0; i < numBytes; i++){
      (*urandom) >> rnd[i];
    }

		urandom->close();
    delete urandom; //deleting a null pointer has no effect anyway
#endif	
		
		return rnd;
	}

  Seedbank::~Seedbank(void)
  { }
    
}
    
    
      
      
      
