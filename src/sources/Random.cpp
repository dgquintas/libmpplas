/* 
 * $Id$ 
 */
#include "Random.h"
#include "MethodsFactory.h"
#include "Seedbank.h"
#include "Primos.h"
#include "GCD.h"
#include "Errors.h"

#include <algorithm> //para max()
#include <limits>

namespace mpplas{

  /* IMPLEMENTACION MIEMBROS NO PUROS DE Random */
  Digit Random::getDigit(void)
  {
    const Digit temp( (this->getInteger(Constants::BITS_EN_CIFRA)).toDigit());
    return temp;
  }
  SignedDigit Random::getSignedDigit(void)
  {
    const SignedDigit temp( (this->getInteger(Constants::BITS_EN_CIFRASIGNO)).toSignedDigit());
    return temp;
  }

  Z Random::getIntegerBounded(const Z& bound) {
    const int bitsCota = bound.getBitLength();  
    Z temp(this->getInteger(bitsCota));

    while( temp >= bound ){
      temp = this->getInteger(bitsCota);
    }

    return temp;
  }
  
  /* IMPL. NumThRC4Gen */
  NumThRC4Gen::NumThRC4Gen()
  {
    Seedbank seedbank;
    
    //una seed de 16 bytes parece razonable...
    //Por una parte, las funciones hash más habituales (SHA, MD* ...)
    //tienen este o mayor tamaño de resumen.
    //Por otra, la busqueda en un espacio de 2^{16*8} = 2^{128} parece
    //suficientemente grande como para estar razonablemente a salvo de
    //la fuerza bruta.
    _seed = seedbank.getSeed(16); 
    _initialize();
  }

  Z NumThRC4Gen::getInteger(int n) {
    if( (n >= std::numeric_limits<int>::max() - 7) || (n < 0) ){
      throw mpplas::Errors::TooBig();
    }
    if( n == 0){
      return Z::ZERO;
    }
    const int n_bytes = (n+7) >> 3;
    MiVec<uint8_t> bytesRand(n_bytes);
    
    uint8_t t;
    uint8_t temp;
    for(int c = 0; c < n_bytes; c++){
      _i = (_i+1) & 0xff;
      _j = (_j+_s[_i]) & 0xff;
      
      //intercambiar s[i] <-> s[j]
      temp = _s[_i];
      _s[_i] = _s[_j];
      _s[_j] = temp;

      t = (_s[_i] + _s[_j]) & 0xff;

      bytesRand[c] = _s[t];
    }
      
    const int numDigits = ((n_bytes+(Constants::BYTES_EN_CIFRA-1)) / Constants::BYTES_EN_CIFRA); 
    MiVec<Digit> vecRandom(numDigits);
    
    int i;
    for(i = 0 ; i < numDigits-1 ; i++){
      for(int j = 0; j < (Constants::BYTES_EN_CIFRA); j++){
        vecRandom[i] <<= 8;
        vecRandom[i] |= bytesRand[(i*Constants::BYTES_EN_CIFRA)+j];
      }
    }

    int j;
    //last iteration
    if( n_bytes % Constants::BYTES_EN_CIFRA ){
      for(j = 0; j < (n_bytes % Constants::BYTES_EN_CIFRA)-1; j++){
        vecRandom[i] <<= 8;
        vecRandom[i] |= bytesRand[(i*Constants::BYTES_EN_CIFRA)+j];
      }
      if ( n & 0x7 ){ // n % 8
        vecRandom[i] <<= (n & 0x7);
        vecRandom[i] |= (bytesRand[(i*Constants::BYTES_EN_CIFRA)+j]) & ((1 << (n & 0x7))-1);
      }
      else{
        vecRandom[i] <<= 8;
        vecRandom[i] |= bytesRand[(i*Constants::BYTES_EN_CIFRA)+j];
      }
    }
    else{
      for(int j = 0; j < (Constants::BYTES_EN_CIFRA); j++){
        vecRandom[i] <<= 8;
        vecRandom[i] |= bytesRand[(i*Constants::BYTES_EN_CIFRA)+j];
      }
    }
    
    return Z(vecRandom);
    
  }

  void NumThRC4Gen::setSeed(const Z& seed)
  {
    _seed = seed;
    _initialize();
    return;
  }

  void NumThRC4Gen::_initialize(void)
  {
    const int lengthSeed(_seed.longitud());

    Digit mascara;
    int posSeed = 0;
    for(int m = 0; m < 256; m++){
      _s[m] = m;
    }
    
    for(int m = 0; m < 256; ){
      mascara = 0xff;
      posSeed++;
      if ( posSeed == lengthSeed ) {
        posSeed = 0;
      }

      for(int n = 0; n < Constants::BYTES_EN_CIFRA ; n++){
        _k[m] = _seed[ posSeed ] & mascara;
        m++;
        mascara <<= 8;
      }
    }
    _i = 0; _j = 0;
    uint8_t temp;
    for( ; _i < 256; _i++){
      _j = (_j + _s[_i] + _k[_i]) & 0xff;
      //intercambiar s[i] <-> s[j]
      temp = _s[_i];
      _s[_i] = _s[_j];
      _s[_j] = temp;
    }

    return;
  }
  
    
    


  /* IMPL. Generador con congruencias lineales */
    /* Se utilizará un generador que responda a la expresion
     * 
     * X_n = (aX_{n-1} + b) (mod m)
     * 
     * con a = 9301 
     *     b = 49297
     *     m = 233280
     * como valores de las constantes (extraidos de pagia 370
     * Schneier y son generadores de periodo maximo (en este caso pues 
     * el periodo sera de 233280)
     *
     * De cada X_i se consideraran tan solo los 16 bits inferiores.
     */
  CongruentGen::CongruentGen(void)
    : _a(9301UL), _b(49297UL), _m(233280UL)
  {
    Seedbank seedbank;

    //ATENCION!!!
    //una semilla de sizeof(Digit) (normalmente = 4) es algo relativamente
    //PEQUEÑO. El espacio de claves es de aprox. tan solo 2^{4*8} =
    //2^32 ~ 4 millones es insuficiente para aplicaciones de alta
    //seguridad. 
    //Pero por otra parte, el generador por congruencias lineales es
    //inherentemente inseguro... vease Scheier pag. 369
    _Xi = (Digit)(seedbank.getSeed(sizeof(Digit)))[0]; 
    return;
  }
  
      
  Z CongruentGen::getInteger(int n) {
    if( (n >= std::numeric_limits<int>::max() - 7) || (n < 0) ){
      throw mpplas::Errors::TooBig();
    }
    if( n == 0){
      return Z::ZERO;
    }

    int n_bytes = (n+7) >> 3;
    MiVec<uint8_t> bytesRand(n_bytes);
    
    int numDigits = ((n_bytes+(Constants::BYTES_EN_CIFRA-1)) / Constants::BYTES_EN_CIFRA); 
    MiVec<Digit> vecRandom(numDigits,0);
    
    // rellenar bytesRand
    int c = 0;
    while( c < n_bytes ){
      //esto de los pares/impares es cosa mia, dado que el modulo _m
      //no llega (el por omisión al menos) para suplir 32 bits, se
      //usan solo 16... y dado que se van generando byte a byte se van 
      //cogiendo la parte alta de los 16 bits bajos de _Xi y la baja
      bytesRand[c++] = (_Xi & 0xff00) >> 8;
      if( c >= n_bytes ) break;
      bytesRand[c++] = _Xi & 0x00ff;
      // Generar el siguiente número de la secuencia
      _Xi = _a * _Xi;
      _Xi += _b;
      _Xi %= _m;
    }

    int i;
    for(i = 0 ; i < numDigits-1 ; i++)
      for(int j = 0; j < (Constants::BYTES_EN_CIFRA); j++){
        vecRandom[i] <<= 8;
        vecRandom[i] |= bytesRand[(i*Constants::BYTES_EN_CIFRA)+j];
      }

    //y ultima iteracion
    int j;
    if( n_bytes % Constants::BYTES_EN_CIFRA ){
      for(j = 0; j < (n_bytes % Constants::BYTES_EN_CIFRA)-1; j++){
        vecRandom[i] <<= 8;
        vecRandom[i] |= bytesRand[(i*Constants::BYTES_EN_CIFRA)+j];
      }
      vecRandom[i] <<= (n % 8);
      vecRandom[i] |= (bytesRand[(i*Constants::BYTES_EN_CIFRA)+j]) & ((1 << (n % 8))-1);
    }
    else{
      for(int j = 0; j < (Constants::BYTES_EN_CIFRA); j++){
        vecRandom[i] <<= 8;
        vecRandom[i] |= bytesRand[(i*Constants::BYTES_EN_CIFRA)+j];
      }
    }
    
    return Z(vecRandom);
    
  }

  void CongruentGen::setSeed(const Z& seed)
  {
    _Xi = seed[0] % _m;
    return;
  }



  BBSGen::BBSGen(void)
    : _quality(256)
  {
    _initialize();
  }

  void BBSGen::setQuality(int n)  {
    _quality = n;
    _initialize(); // tras un cambio de la calidad, hay que recomputar los primos
  }

  void BBSGen::_initialize(void)
  {
    //1º, encontrar 2 primos p y q de Blum ( p = 3 (mod 4) <=>
    // (-1/p) == -1 
    MethodsFactory *funcs = MethodsFactory::getInstance();
    PrimeGen* gprimos; funcs->getFunc(gprimos);
//    SimboloLegendre* slegendre = funcs->simboloLegendre();
    RandomFast* rnd; funcs->getFunc(rnd);
 
    Z p,q;
    Z menosUno; menosUno.makeOne(); menosUno.hacerNegativo();
    
//    do{
//      p = gprimos->getPrime(_quality);
//    } while( slegendre->simboloLegendre(menosUno, p) != (SignedDigit)-1 );
//    
//    do{
//      q = gprimos->getPrime(_quality);
//    } while( slegendre->simboloLegendre(menosUno, q) != (SignedDigit)-1 );
 
    do{
      p = gprimos->getPrime(_quality);
    } while( (p[0] & 0x3) != 3 ); // p & 0x3 == p mod 4
    
    do{
      q = gprimos->getPrime(_quality);
    } while( (q[0] & 0x3) != 3 );

    
    _n = p*q;
    do{
      _Xi = rnd->getIntegerBounded(_n);
    }while( Z::gcd(_Xi, _n) != (Digit)1);

    _Xi.modularSquare(_n); 
    
    return;
  }
    
  Z BBSGen::getInteger(int num){
    Z resultado; resultado.makeZero();
    //según pagina 418 de Schneier, si "n" es la longitud de "Xi", los
    //Log_2{n} bits menos significativos de Xi pueden ser usados.
    //Es claro que el número de bits necesario para representar un
    //número x es igual al ceil(Log_2{x}). 
    //Por tanto, cuando x NO sea una potencia de 2, se puede
    //considerar Log_2{x} = getBitLength(x) - 1. Cuando x SI sea potencia
    //de 2, sera Log_2{x} = getBitLength(x)
    //De todas formas, se considerará siempre el primer caso (por ser
    //el más "conservador") y de cada _Xi se tomarán sus 
    //max(1,getBitLength(n)-1) bits de menos peso
    
    const int n = getBitLength(_Xi);
    const int longConsiderada = std::max(getBitLength((Digit)n)-1,1);
    Digit mascara = (1UL << longConsiderada)-1;
    while(num > 0){
      _Xi.modularSquare(_n); 
      if(num < (2*longConsiderada) ){
        resultado[0] |= (_Xi[0] & mascara);
        resultado <<= num;
        
        mascara = (1UL << num)-1;
        _Xi.modularSquare(_n); 
        resultado[0] |= (_Xi[0] & mascara);
        break;
      }
      else{
        resultado[0] |= (_Xi[0] & mascara);
        resultado <<= longConsiderada;
        num -= longConsiderada;
      }
    }

    return resultado;
  }
    
 
  bool FIPS_140_1::testRandom(Random& generadorRandom) {
    // Menezes p 183. VER TABLA DE NOTE 5.32 PARA EXPLICACION DE LOS
    // NUMEROS MAGICOS
    Z muestra(generadorRandom.getInteger(20000));
  
    int unos;
    float estadisticoPoker;
    int recorridoMaximo;
    int bloques[6] = {0};
    int huecos[6] = {0};
    
    unos = monobitTest_(muestra);
    if( (9654 >= unos) || (unos >= 10346) )  // si no se cumple 9654 < unos < 10346
      return false;

    estadisticoPoker = pokerTest_(muestra);
    if( (1.03 >= estadisticoPoker) || (estadisticoPoker >= 57.4) ) // si no se cumple 1.03 < x < 57.4
      return false;
    
    recorridoMaximo = runTests_(muestra, bloques, huecos);
    if( (bloques[0] < 2267) || (bloques[0] > 2733 ) ) return false;
    if( ( huecos[0] < 2267) || ( huecos[0] > 2733 ) ) return false;

    if( (bloques[1] < 1079) || (bloques[1] > 1421 ) ) return false;
    if( ( huecos[1] < 1079) || ( huecos[1] > 1421 ) ) return false;
    
    if( (bloques[2] < 502) || (bloques[2] >  748) ) return false;
    if( ( huecos[2] < 502) || ( huecos[2] >  748) ) return false;
 
    if( (bloques[3] < 223) || (bloques[3] > 402 ) ) return false;
    if( ( huecos[3] < 223) || ( huecos[3] > 402 ) ) return false;
    
    if( (bloques[4] < 90) || (bloques[4] > 223 ) ) return false;
    if( ( huecos[4] < 90) || ( huecos[4] > 223 ) ) return false;
    
    if( (bloques[5] < 90) || (bloques[5] > 223 ) ) return false;
    if( ( huecos[5] < 90) || ( huecos[5] > 223 ) ) return false;

    /* test de maximo recorrido ("long run") */
    if( recorridoMaximo >= 34 ) return false;
    
    return true;
  }

  int FIPS_140_1::monobitTest_(Z muestraLocal)
  {
    //Menezes 181
    int unos = 0;
    for (int i = 0; i < 20000; i++){
      if( (muestraLocal[0] & 0x1) == 1) 
        unos++;
      muestraLocal >>= 1;
    }

    return unos;
  }
  float FIPS_140_1::pokerTest_(Z muestraLocal)
  {
    Digit mascara; mascara = 0xf;
    
    int numSeqIesima[16] = {0}; // 16 = 2^m = 2^4  ; Menezes 183
    
    int k = 5000;
    int indice;
    for (int i = 0; i < k; i++) {
      indice = muestraLocal[0] & mascara;
      numSeqIesima[indice]++;
      muestraLocal >>= 4;
    }

    unsigned long sum = 0;
    for (int i = 0; i < 16; i++) // m = 16
      sum += numSeqIesima[i] * numSeqIesima[i];
    
    float estadistico;
    estadistico = 16.0 * ((float)sum / (float)k) - k;

    return estadistico;
  }


  int FIPS_140_1::runTests_(Z muestraLocal, int* bloques, int* huecos)
  {
    // ver Menezes p 180 Def 5.26
    int recorridoMaximo = 0;
    Z muestraLocal2(muestraLocal);
    
    int i,j;
    i = 0;
    while( i < 20000 ){
      j = 0;
      while( (i < 20000) && ((muestraLocal[0] & 0x1) == 1)) {
        i++; j++; // se avanza y se cuentan unos
        muestraLocal >>= 1;
      }
      if(j <= 6) 
        bloques[j - 1]++; 
      else 
        bloques[5]++; // ya que Menezes p.183 5.32(iii): secuencias > 6 son consideradas como 6  
      if (j > recorridoMaximo) 
        recorridoMaximo = j;
      while( (i < 20000) && ((muestraLocal[0] & 0x1) == 0)){
        muestraLocal >>= 1;
        i++; // saltar la seq. de ceros
      }
    }
    
    i = 0;
    while( i < 20000 ){
      j = 0;
      while( (i < 20000) && ((muestraLocal2[0] & 0x1) == 0)){
        i++; j++; // se avanza y se cuentan ceros
        muestraLocal2 >>= 1;
      }
      if(j <= 6) 
        huecos[j - 1]++; 
      else 
        huecos[5]++; // ya que Menezes p.183 5.32(iii): secuencias > 6 son consideradas como 6  
      if (j > recorridoMaximo) 
        recorridoMaximo = j;
      while( (i < 20000) && ((muestraLocal2[0] & 0x1) == 1)) {
        muestraLocal2 >>= 1;
        i++; // saltar la seq. de unos
      }
    }
    return recorridoMaximo;
  } 
}

