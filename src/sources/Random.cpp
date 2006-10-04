/* 
 * $Id$ 
 */
#include "Random.h"
#include "Funciones.h"
#include "Semillero.h"
#include <algorithm> //para max()

namespace numth{

  /* IMPLEMENTACION MIEMBROS NO PUROS DE Random */
  Cifra Random::leerCifra(void)
  {
    Cifra temp;
    temp = (this->leerBits(Constantes::BITS_EN_CIFRA))[0];

    return temp;
  }

  Z Random::leerEntero(Z cota)
  {
    unsigned long bitsCota = cota.numBits();  
    Z temp;
    temp = this->leerBits(bitsCota);

    while( temp >= cota )
      temp = this->leerBits(bitsCota);

    return temp;
  }
  
  /* IMPL. NumThRC4Gen */
  NumThRC4Gen::NumThRC4Gen()
  {
    Semillero semillero;
    
    //una semilla de 16 bytes parece razonable...
    //Por una parte, las funciones hash más habituales (SHA, MD* ...)
    //tienen este o mayor tamaño de resumen.
    //Por otra, la busqueda en un espacio de 2^{16*8} = 2^{128} parece
    //suficientemente grande como para estar razonablemente a salvo de
    //la fuerza bruta.
    semilla_ = semillero.leerSemilla(16); 
    inicializar_();
  }

  Z NumThRC4Gen::leerBits(size_t n)
  {
    size_t n_bytes = (n+7) >> 3;
    MiVec<uint8_t> bytesRand(n_bytes);
    
    uint8_t t;
    uint8_t temp;
    for(size_t c = 0; c < n_bytes; c++){
      i_ = (i_+1) & 0xff;
      j_ = (j_+s_[i_]) & 0xff;
      
      //intercambiar s[i] <-> s[j]
      temp = s_[i_];
      s_[i_] = s_[j_];
      s_[j_] = temp;

      t = (s_[i_] + s_[j_]) & 0xff;

      bytesRand[c] = s_[t];
    }
      
    size_t numCifras = ((n_bytes+(Constantes::BYTES_EN_CIFRA-1)) / Constantes::BYTES_EN_CIFRA); 
    MiVec<Cifra> vecRandom(numCifras,0);
    
    size_t i;
    for(i = 0 ; i < numCifras-1 ; i++)
      for(size_t j = 0; j < (Constantes::BYTES_EN_CIFRA); j++){
        vecRandom[i] <<= 8;
        vecRandom[i] |= bytesRand[(i*Constantes::BYTES_EN_CIFRA)+j];
      }

    //y ultima iteracion
    size_t j;
    if( n_bytes % Constantes::BYTES_EN_CIFRA ){
      for(j = 0; j < (n_bytes % Constantes::BYTES_EN_CIFRA)-1; j++){
        vecRandom[i] <<= 8;
        vecRandom[i] |= bytesRand[(i*Constantes::BYTES_EN_CIFRA)+j];
      }
      if ( n & 0x7 ){ // n % 8
        vecRandom[i] <<= (n & 0x7);
        vecRandom[i] |= (bytesRand[(i*Constantes::BYTES_EN_CIFRA)+j]) & ((1 << (n & 0x7))-1);
      }
      else{
        vecRandom[i] <<= 8;
        vecRandom[i] |= bytesRand[(i*Constantes::BYTES_EN_CIFRA)+j];
      }
    }
    else{
      for(size_t j = 0; j < (Constantes::BYTES_EN_CIFRA); j++){
        vecRandom[i] <<= 8;
        vecRandom[i] |= bytesRand[(i*Constantes::BYTES_EN_CIFRA)+j];
      }
    }
    
    return Z::convertir(vecRandom);
    
  }

  void NumThRC4Gen::ponerSemilla(const Z& semilla)
  {
    semilla_ = semilla;
    inicializar_();
    return;
  }

  void NumThRC4Gen::inicializar_(void)
  {
    size_t longSemilla = semilla_.longitud();

    Cifra mascara;
    size_t posSemilla = 0;
    for(size_t m = 0; m < 256; m++)
      s_[m] = m;
    
    for(size_t m = 0; m < 256; ){
      mascara = 0xff;
      posSemilla++;
      if ( posSemilla == longSemilla ) 
        posSemilla = 0;

      for(size_t n = 0; n < Constantes::BYTES_EN_CIFRA ; n++){
        k_[m] = semilla_[ posSemilla ] & mascara;
        m++;
        mascara <<= 8;
      }
    }
    i_ = 0; j_ = 0;
    uint8_t temp;
    for( ; i_ < 256; i_++){
      j_ = (j_ + s_[i_] + k_[i_]) & 0xff;
      //intercambiar s[i] <-> s[j]
      temp = s_[i_];
      s_[i_] = s_[j_];
      s_[j_] = temp;
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
  congruentGen::congruentGen(void)
    : a_(9301UL), b_(49297UL), m_(233280UL)
  {
    Semillero semillero;

    //ATENCION!!!
    //una semilla de sizeof(ulong) (normalmente = 4) es algo relativamente
    //PEQUEÑO. El espacio de claves es de aprox. tan solo 2^{4*8} =
    //2^32 ~ 4 millones es insuficiente para aplicaciones de alta
    //seguridad. 
    //Pero por otra parte, el generador por congruencias lineales es
    //inherentemente inseguro... vease Scheier pag. 369
    Xi_ = (unsigned long)(semillero.leerSemilla(sizeof(unsigned long)))[0]; 

    return;
  }
  
      
  Z congruentGen::leerBits(size_t n)
  {
    size_t n_bytes = (n+7)/8;
    MiVec<uint8_t> bytesRand(n_bytes);
    
    size_t numCifras = ((n_bytes+(Constantes::BYTES_EN_CIFRA-1)) / Constantes::BYTES_EN_CIFRA); 
    MiVec<Cifra> vecRandom(numCifras,0);
    
    // rellenar bytesRand
    size_t c = 0;
    while( c < n_bytes ){
      //esto de los pares/impares es cosa mia, dado que el modulo m_
      //no llega (el por omisión al menos) para suplir 32 bits, se
      //usan solo 16... y dado que se van generando byte a byte se van 
      //cogiendo la parte alta de los 16 bits bajos de Xi_ y la baja
      bytesRand[c++] = (Xi_ & 0xff00) >> 8;
      if( c >= n_bytes ) break;
      bytesRand[c++] = Xi_ & 0x00ff;
      // Generar el siguiente número de la secuencia
      Xi_ = a_ * Xi_;
      Xi_ += b_;
      Xi_ %= m_;
    }

    size_t i;
    for(i = 0 ; i < numCifras-1 ; i++)
      for(size_t j = 0; j < (Constantes::BYTES_EN_CIFRA); j++){
        vecRandom[i] <<= 8;
        vecRandom[i] |= bytesRand[(i*Constantes::BYTES_EN_CIFRA)+j];
      }

    //y ultima iteracion
    size_t j;
    if( n_bytes % Constantes::BYTES_EN_CIFRA ){
      for(j = 0; j < (n_bytes % Constantes::BYTES_EN_CIFRA)-1; j++){
        vecRandom[i] <<= 8;
        vecRandom[i] |= bytesRand[(i*Constantes::BYTES_EN_CIFRA)+j];
      }
      vecRandom[i] <<= (n % 8);
      vecRandom[i] |= (bytesRand[(i*Constantes::BYTES_EN_CIFRA)+j]) & ((1 << (n % 8))-1);
    }
    else{
      for(size_t j = 0; j < (Constantes::BYTES_EN_CIFRA); j++){
        vecRandom[i] <<= 8;
        vecRandom[i] |= bytesRand[(i*Constantes::BYTES_EN_CIFRA)+j];
      }
    }
    
    return Z::convertir(vecRandom);
    
  }

  void congruentGen::ponerSemilla(const Z& semilla)
  {
    Xi_ = semilla[0] % m_;
    return;
  }



  BBSGen::BBSGen(void)
    : calidad_(256)
  {
    inicializar_();
  }

  void BBSGen::ponerCalidad(size_t n)
  {
    calidad_ = n;
    inicializar_(); // tras un cambio de la calidad, hay que recomputar los primos
  }

  void BBSGen::inicializar_(void)
  {
    //1º, encontrar 2 primos p y q de Blum ( p = 3 (mod 4) <=>
    // (-1/p) == -1 
    Funciones funcs;
    GenPrimos* gprimos = funcs.genPrimos();
//    SimboloLegendre* slegendre = funcs.simboloLegendre();
    GCD* gcd = funcs.gcd();
    RandomRapido* rnd = funcs.randomRapido();
 
    Z p,q;
    Z menosUno; menosUno.hacerUno(); menosUno.hacerNegativo();
    
//    do{
//      p = gprimos->leerPrimoProb(calidad_);
//    } while( slegendre->simboloLegendre(menosUno, p) != (CifraSigno)-1 );
//    
//    do{
//      q = gprimos->leerPrimoProb(calidad_);
//    } while( slegendre->simboloLegendre(menosUno, q) != (CifraSigno)-1 );
 
    do{
      p = gprimos->leerPrimoProb(calidad_);
    } while( (p[0] & 0x3) != 3 ); // p & 0x3 == p mod 4
    
    do{
      q = gprimos->leerPrimoProb(calidad_);
    } while( (q[0] & 0x3) != 3 );

    
    n_ = p*q;
    do{
      Xi_ = rnd->leerEntero(n_);
    }while( gcd->gcd(Xi_, n_) != (Cifra)1);

    Xi_.cuadradoModular(n_); 
    
    return;
  }
    
  Z BBSGen::leerBits(size_t num)
  {
    
    Z resultado; resultado.hacerCero();
    //según pagina 418 de Schneier, si "n" es la longitud de "Xi", los
    //Log_2{n} bits menos significativos de Xi pueden ser usados.
    //Es claro que el número de bits necesario para representar un
    //número x es igual al ceil(Log_2{x}). 
    //Por tanto, cuando x NO sea una potencia de 2, se puede
    //considerar Log_2{x} = numBits(x) - 1. Cuando x SI sea potencia
    //de 2, sera Log_2{x} = numBits(x)
    //De todas formas, se considerará siempre el primer caso (por ser
    //el más "conservador") y de cada Xi_ se tomarán sus 
    //max(1,numBits(n)-1) bits de menos peso
    
    size_t n = numBits(Xi_);
    Cifra longConsiderada = std::max(numBits((Cifra)n)-1,(size_t)1);
    Cifra mascara = (1UL << longConsiderada)-1;
    while(num){
      Xi_.cuadradoModular(n_); 
      if(num < (2*longConsiderada) ){
        resultado[0] |= (Xi_[0] & mascara);
        resultado <<= num;
        
        mascara = (1UL << num)-1;
        Xi_.cuadradoModular(n_); 
        resultado[0] |= (Xi_[0] & mascara);
        break;
      }
      else{
        resultado[0] |= (Xi_[0] & mascara);
        resultado <<= longConsiderada;
        num -= longConsiderada;
      }
    }

    return resultado;
  }
    
 
  bool FIPS_140_1::pruebaRandom(Random& generadorRandom)
  {
    // Menezes p 183. VER TABLA DE NOTE 5.32 PARA EXPLICACION DE LOS
    // NUMEROS MAGICOS
    Z muestra(generadorRandom.leerBits(20000));
  
    size_t unos;
    float estadisticoPoker;
    size_t recorridoMaximo;
    size_t bloques[6] = {0};
    size_t huecos[6] = {0};
    
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

  size_t FIPS_140_1::monobitTest_(Z muestraLocal)
  {
    //Menezes 181
    size_t unos = 0;
    for (size_t i = 0; i < 20000; i++){
      if( (muestraLocal[0] & 0x1) == 1) 
        unos++;
      muestraLocal >>= 1;
    }

    return unos;
  }
  float FIPS_140_1::pokerTest_(Z muestraLocal)
  {
    Cifra mascara; mascara = 0xf;
    
    size_t numSeqIesima[16] = {0}; // 16 = 2^m = 2^4  ; Menezes 183
    
    size_t k = 5000;
    size_t indice;
    for (size_t i = 0; i < k; i++) {
      indice = muestraLocal[0] & mascara;
      numSeqIesima[indice]++;
      muestraLocal >>= 4;
    }

    unsigned long sum = 0;
    for (size_t i = 0; i < 16; i++) // m = 16
      sum += numSeqIesima[i] * numSeqIesima[i];
    
    float estadistico;
    estadistico = 16.0 * ((float)sum / (float)k) - k;

    return estadistico;
  }


  size_t FIPS_140_1::runTests_(Z muestraLocal, size_t* bloques, size_t* huecos)
  {
    // ver Menezes p 180 Def 5.26
    size_t recorridoMaximo = 0;
    Z muestraLocal2(muestraLocal);
    
    size_t i,j;
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

