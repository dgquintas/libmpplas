/* 
 * $Id$
 */


#include "Primos.h"
#include "Random.h"
#include "Z_n.h"
#include "MethodsFactory.h"
#include "GCD.h"
#include "RedModular.h"
#include "Potencia.h"
#include <cmath>
#include <algorithm>

namespace mpplas{

  RabinMiller::RabinMiller()
    : iteraciones_(5)
  {}

  bool RabinMiller::esPrimo(const Z& p, Z* testigo) 
  {
    MethodsFactory* const funcs = MethodsFactory::getInstance();
    RandomFast* rnd; funcs->getFunc(rnd);
    GCD<Z>* gcd; funcs->getFunc(gcd);
    
    if( p == (Digit)2 ){
      return true;
    }
    
    if(testigo){ 
      //se ha de rellenar "a toda costa", asi que ni se realiza
      //división por primos pequeños ni ninguna otra optimizacion... 
      //sólamente interesa conocer un testigo (de haberlo, claro)
      //Esto se utiliza para la función de detección de potencias de
      //primo
      Z_n z(p); 
      Z pMenosUno(p); pMenosUno--;
      const int b = pMenosUno.numDoses();
      const Z m = pMenosUno >> b;
      
      for( int i = 0; i < iteraciones_; i++){
        //Por 4.28 Menezes, el producto de 2 "mentirosos fuertes" (bases
        //que poducen un pseudoprimo fuerte "n" en realidad compuesto)
        //es casi con toda seguridad, también un mentiroso fuerte. 
        //Por tanto, se utilizan como bases los primos sucesivos.
        if(i >= 303 ){ 
          //por si a alguien se le ocurre la "brillante" idea de poner un numero
          //de iteraciones asi de grande
          z = rnd->getInteger( std::min(16,p.getBitLength()-1) );
          (*testigo) = z;
        }
        else{
          z = Z(Constants::TABLA_PRIMOS_2000[i]);
          if( z.isZero() ) {
            // ya que eso quiere decir que son el mismo número( p | z,
            // con z primo => p = z ), y al ser z un primo, p será también primo.
            testigo->makeZero();
            return true;
          }
          (*testigo) = z;
        }
        
        z ^= m;
        
        if( (!z.isOne()) && ( z != pMenosUno) ){
          for(int j = 0; (j < b) && (z != pMenosUno) ; j++ ){
            z.square();  // recordar que z es Zp
            if( z.isOne() ){ //ya que no cambiará aun en los cuadrados sucesivos...
              return false;
            }
          }
          if ( z != pMenosUno ){
            return false;
          }
        }
      }
      // si resulta que "es primo", no tiene sentido hablar de
      // testigos, asi que se le da el imposible valor de cero a éste.
      testigo->makeZero();
      return true;
    } /* if testigo */
    else{ //no hay que devolver testigo

      if( p.isEven() || p.isOne() ) {
        return false;
      }

      int cota;
      if( p <= (Digit)4000000 ){ // 2000^2
        cota = iSquareRoot(p[0]);
        for(int i = 0; Constants::TABLA_PRIMOS_2000[i] <= cota; i++){
//          if ( (!Z::gcd(p, Constants::TABLA_PRIMOS_2000[i]).isOne()) ){ //si el gcd no es uno... 
          if ( (!gcd->_gcd(p, Constants::TABLA_PRIMOS_2000[i]).isOne()) ){ //si el gcd no es uno... 
            return false;
          }
        }
        /* Resultado GANTIZADO */
        return true;
      }
      else{
        cota = 303;
      }
      for(int i = 0; i < cota; i++){
//        if ( (!Z::gcd(p, Constants::TABLA_PRIMOS_2000[i]).isOne()) ){ //si el gcd no es uno... 
        if ( (!gcd->_gcd(p, Constants::TABLA_PRIMOS_2000[i]).isOne()) ){ //si el gcd no es uno...
        return false;
        }
      }
      /* Sloane's A014233: 
       * Menores impares para los cuales el test de Rabin-Miller para los
       * k primeros primos falla.

       n | a(n)
       --------
       1 | 2047         <- fuera por trial
       2 | 1373653      <- idem
       3 | 25326001
       4 | 3215031751
       5 | 2152302898747
       6 | 3474749660383
       7 | 341550071728321
       8 | 341550071728321 <- fuera por superfluo */
      static const Z psi_3("25326001");
      static const Z psi_4("3215031751");
      static const Z psi_5("2152302898747");
      static const Z psi_6("3474749660383");
      static const Z psi_7("341550071728321");

      if( p < psi_7 ){
        if( p < psi_6 ){
          if( p < psi_5 ){
            if( p < psi_4 ){
              if( p < psi_3 ){
                iteraciones_ = 3;
              } else iteraciones_ = 4;
            } else iteraciones_ = 5;
          } else iteraciones_ = 6;
        } else iteraciones_ = 7;
      }
      /* Con lo de arriba se GARANTIZA la primalidad. Ver Menezes p.140
       * 4.29*/

      Z_n z(p); 
      Z pMenosUno(p); pMenosUno--;
      const int b = pMenosUno.numDoses();
      const Z m(pMenosUno >> b);
      for( int i = 0; i < iteraciones_; i++){
        //Por 4.28 Menezes, el producto de 2 "mentirosos fuertes" (bases
        //que poducen un pseudoprimo fuerte "n" en realidad compuesto)
        //es casi con toda seguridad, también un mentiroso fuerte. 
        //Por tanto, se utilizan como bases los primos sucesivos.
        if(i >= 303 ) {
          //por si a alguien se le ocurre la "brillante" idea de poner un numero
          //de iteraciones asi de grande
          z = rnd->getInteger( std::min(16,p.getBitLength()-1) );
        }
        else{
          z = Z(Constants::TABLA_PRIMOS_2000[i]);
        }

        z ^= m;

        if( (!z.isOne()) && ( z != pMenosUno) ){
          for(int j = 0; (j < b) && (z != pMenosUno) ; j++ ){
            z.square();
            if( z.isOne() ){ //ya que no cambiará aun en los cuadrados sucesivos...
              return false;
            }
          }
          if ( z != pMenosUno ){
            return false;
          }
        }
      }

      return true;
    }
  }

  void RabinMiller::ponerIteraciones(int iteraciones)
  {
      iteraciones_ = iteraciones;
  }
  


  bool TMersenneLucasLehmer::esPrimo(const SignedDigit p) 
  {
    /*
    Lucas_Lehmer_Test(p):
      s := 4;
    for i from 3 to p do s := s2-2 mod 2p-1;
    if s == 0 then
      2p-1 is prime
    else
      2p-1 is composite;
    */

    MethodsFactory *funcs = MethodsFactory::getInstance();
    RedModularALaMersenne* redmodmers; funcs->getFunc(redmodmers);

    TestPrimoProb *primTest; funcs->getFunc(primTest);
    if( !primTest->esPrimo(Z(p)) )
      return false;
    
    Z s((Digit)4);
    
    for(SignedDigit i = 3; i <= p; i++){
      s.square(); 
      s -= (Digit)2;
      redmodmers->redModularALaMersenne(&s,p,1);
    }
    if( s.isZero() )
      return true;
    else
      return false;
    
  }

////////////////////////////////////////////////

  GenPrimos::GenPrimos(){
    MethodsFactory::getInstance()->getFunc(_rnd);
  }

  void GenPrimos::setRandomSeed(const Z& seed) const {
    _rnd->setSeed(seed);
  }


  Z GenPrimos::getPrime(const int bits) const {

    Z n(_rnd->getInteger(bits));


    //because it _might_ happen that the length of the 
    //generated integer is less than the bits argument,
    //so that in the next step, we _might_ get an out of 
    //bounds exception
    const int actualBits = n.getBitLength();

    //poner a 1 los bits más y menos significativos 
    //poner a 1 el bit mas significativo hace que el nº
    //generado tenga el numero de bits especificado
    const int i = (actualBits-1) / Constants::BITS_EN_CIFRA;
    const int j = (actualBits-1) % Constants::BITS_EN_CIFRA;
    const Digit mask = (((Digit)1) << j);

    n[i] |= mask; // MSB
    n[0] |= 0x1;     // LSB


    return this->getPrime(n);

  }

  Z GenPrimos::getPrime(Z from) const {
    MethodsFactory* const funcs = MethodsFactory::getInstance();
    TestPrimoProb* test; funcs->getFunc(test);

    //caso especial
    if( from == (Digit)2 ){
      return Z((Digit)3);
    }
    
    if( from.isEven() ){
      from++;
    }
    else{
      from += (Digit)2;
    }

    const int bits = from.getBitLength();

    int iteraciones;
    // pagina 148 Handbook of Applied Cryptography
    // Se garantiza una probabilidad de error <= que (1/2)^80
    if( bits >= 1300 ) {
      iteraciones = 2;
    }
    else if( bits >= 850 ) { 
      iteraciones = 3;
    }
    else if( bits >= 650 ) {
      iteraciones = 4;
    }
    else if( bits >= 550 ) {
      iteraciones = 5;
    }
    else if( bits >= 450 ) {
      iteraciones = 6;
    }
    else if( bits >= 400 ) {
      iteraciones = 7;
    }
    else if( bits >= 350 ) {
      iteraciones = 8;
    }
    else if( bits >= 300 ) {
      iteraciones = 9;
    }
    else if( bits >= 250 ) {
      iteraciones = 12;
    }
    else if( bits >= 200 ) {
      iteraciones = 15;
    }
    else if( bits >= 150 ) {
      iteraciones = 18;
    }
    else if( bits >= 100 ) {
      iteraciones = 27;
    }
    else {
      iteraciones = 30;
    }

    test->ponerIteraciones(iteraciones);
    while( !test->esPrimo(from) ){
      from += (Digit)2;
    }
    
    //aquí, esPrimo(from) == true

    return from;

  }


  Z GenPrimos::getPrimeStrong(const int bits) const {
    MethodsFactory* const funcs = MethodsFactory::getInstance();
    TestPrimoProb* testPrim; funcs->getFunc(testPrim);
    
    const Z s(getPrime( bits/2 ));
    Z t(getPrime( (bits/2) - 2 ));

    Z r(t);
    r <<= 2;
    r++;
    t <<= 1;

    while( !testPrim->esPrimo(r) ){
      r += t; //este "t" es el doble del "t" inicial
    }

    Exponentiation<Z_n> *potModular; funcs->getFunc(potModular);
    Z_n p0_n(s,r);
    potModular->exponentiation(&p0_n, r-(Digit)2);
    Z p0( p0_n );
    p0 *= s; p0 <<= 1; p0--;
    
    Z dosRS = r*s; dosRS <<= 1;
    Z p(p0); p += dosRS;
    while( !testPrim->esPrimo(p) ){
      p += dosRS;
    }

    return p;
  }

  
}        
    
