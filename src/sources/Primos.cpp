/* 
 * $Id$
 */


#include "Primos.h"
#include "Random.h"
#include "Z_n.h"
#include "Funciones.h"
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
    Funciones *funcs = Funciones::getInstance();
    GCD* gcd;
    funcs->getFunc(gcd);
    RandomRapido* rnd; funcs->getFunc(rnd);
    
    if( p == (Cifra)2 ){
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
      const size_t b = pMenosUno.numDoses();
      const Z m = pMenosUno >> b;
      
      for( size_t i = 0; i < iteraciones_; i++){
        //Por 4.28 Menezes, el producto de 2 "mentirosos fuertes" (bases
        //que poducen un pseudoprimo fuerte "n" en realidad compuesto)
        //es casi con toda seguridad, también un mentiroso fuerte. 
        //Por tanto, se utilizan como bases los primos sucesivos.
        if(i >= 303 ){ 
          //por si a alguien se le ocurre la "brillante" idea de poner un numero
          //de iteraciones asi de grande
          z = rnd->leerBits( std::min((size_t)16,p.numBits()-1) );
          (*testigo) = z;
        }
        else{
          z = Z(Constantes::TABLA_PRIMOS_2000[i]);
          if( z.esCero() ) {
            // ya que eso quiere decir que son el mismo número( p | z,
            // con z primo => p = z ), y al ser z un primo, p será también primo.
            testigo->hacerCero();
            return true;
          }
          (*testigo) = z;
        }
        
        z ^= m;
        
        if( (!z.esUno()) && ( z != pMenosUno) ){
          for(size_t j = 0; (j < b) && (z != pMenosUno) ; j++ ){
            z.cuadrado();  // recordar que z es Zp
            if( z.esUno() ) //ya que no cambiará aun en los cuadrados sucesivos...
              return false;
          }
          if ( z != pMenosUno )
            return false;
        }
      }
      // si resulta que "es primo", no tiene sentido hablar de
      // testigos, asi que se le da el imposible valor de cero a éste.
      testigo->hacerCero();
      return true;
    }
    else{ //no hay que devolver testigo

      if( p.esPar() || p.esUno() ) {
        return false;
      }

      size_t cota;
      if( p <= (Cifra)4000000 ){ // 2000^2
        cota = raizCuadrada(p[0]);
        for(size_t i = 0; Constantes::TABLA_PRIMOS_2000[i] <= cota; i++){
          if ( (!gcd->gcd(p, Constantes::TABLA_PRIMOS_2000[i]).esUno()) ){ //si el gcd no es uno... 
            return false;
          }
        }

        return true;

        /* Resultado GANTIZADO */
      }
      else{
        cota = 303;
      }

      for(size_t i = 0; i < cota; i++){
        if ( (!gcd->gcd(p, Constantes::TABLA_PRIMOS_2000[i]).esUno()) ){ //si el gcd no es uno... 
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
       8 | 341550071728321 <- fuera por superfluo

*/
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
      const size_t b = pMenosUno.numDoses();
      const Z m = pMenosUno >> b;
      for( size_t i = 0; i < iteraciones_; i++){

        //Por 4.28 Menezes, el producto de 2 "mentirosos fuertes" (bases
        //que poducen un pseudoprimo fuerte "n" en realidad compuesto)
        //es casi con toda seguridad, también un mentiroso fuerte. 
        //Por tanto, se utilizan como bases los primos sucesivos.
        if(i >= 303 ) 
          //por si a alguien se le ocurre la "brillante" idea de poner un numero
          //de iteraciones asi de grande
          z = rnd->leerBits( std::min((size_t)16,p.numBits()-1) );
        else
          z = Z(Constantes::TABLA_PRIMOS_2000[i]);

        z ^= m;

        if( (!z.esUno()) && ( z != pMenosUno) ){
          for(size_t j = 0; (j < b) && (z != pMenosUno) ; j++ ){
            z ^= (Cifra)2; //FIXME
            if( z.esUno() ) //ya que no cambiará aun en los cuadrados sucesivos...
              return false;
          }
          if ( z != pMenosUno )
            return false;
        }
      }

      return true;
    }
  }

  void RabinMiller::ponerIteraciones(size_t iteraciones)
  {
      iteraciones_ = iteraciones;
  }
  


  bool TMersenneLucasLehmer::esPrimo(const CifraSigno p) 
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

    Funciones *funcs = Funciones::getInstance();
    RedModularALaMersenne* redmodmers; funcs->getFunc(redmodmers);

    TestPrimoProb *primTest; funcs->getFunc(primTest);
    if( !primTest->esPrimo(Z(p)) )
      return false;
    
    Z s((Cifra)4);
    
    for(CifraSigno i = 3; i <= p; i++){
      s.cuadrado(); 
      s -= (Cifra)2;
      redmodmers->redModularALaMersenne(&s,p,1);
    }
    if( s.esCero() )
      return true;
    else
      return false;
    
  }

////////////////////////////////////////////////

  GenPrimos::GenPrimos()
  {
    Funciones::getInstance()->getFunc(_rnd);
  }

  void GenPrimos::setRandomSeed(const Z& seed)
  {
    _rnd->ponerSemilla(seed);
  }

  Z GenPrimos::leerPrimoProb(size_t bits)
  {
    Funciones *funcs = Funciones::getInstance();
    TestPrimoProb* test; funcs->getFunc(test);

    Z n(_rnd->leerBits(bits));

    //poner a 1 los bits más y menos significativos 
    //poner a 1 el bit mas significativo hace que el nº
    //generado tenga el numero de bits especificado
    const size_t i = (bits-1) / Constantes::BITS_EN_CIFRA;
    const size_t j = (bits-1) % Constantes::BITS_EN_CIFRA;
    const Cifra mascara = (1U << j);

    n[i] |= mascara; //el más
    n[0] |= 0x1;     //el menos


    size_t iteraciones;
    // pagina 148 Handbook of Applied Cryptography
    // Se garantiza una probabilidad de error <= que (1/2)^80
    if( bits >= 1300 )
      iteraciones = 2;
    else if( bits >= 850 )
      iteraciones = 3;
    else if( bits >= 650 )
      iteraciones = 4;
    else if( bits >= 550 )
      iteraciones = 5;
    else if( bits >= 450 )
      iteraciones = 6;
    else if( bits >= 400 )
      iteraciones = 7;
    else if( bits >= 350 )
      iteraciones = 8;
    else if( bits >= 300 )
      iteraciones = 9;
    else if( bits >= 250 )
      iteraciones = 12;
    else if( bits >= 200 )
      iteraciones = 15;
    else if( bits >= 150 )
      iteraciones = 18;
    else if( bits >= 100 )
      iteraciones = 27;
    else
      iteraciones = 30;

    test->ponerIteraciones(iteraciones);
    while( !test->esPrimo(n) ){
      n++; n++;
    }
    
    //aquí, esPrimo(n) == true

    return n;
  }

  Z GenPrimos::siguientePrimoProb(const Z& comienzo)
  {
    Funciones *funcs = Funciones::getInstance();
    TestPrimoProb* test; funcs->getFunc(test);

    //caso especial
    if( comienzo == (Cifra)2 )
      return Z((Cifra)3);
    
    Z n = comienzo;
    if( comienzo.esPar() ){
      n++;
    }
    else{
      n++; n++;
    }
      

    size_t iteraciones;
    size_t bits = n.numBits();
    // pagina 148 Handbook of Applied Cryptography
    // Se garantiza una probabilidad de error <= que (1/2)^80
    if( bits >= 1300 )
      iteraciones = 2;
    else if( bits >= 850 )
      iteraciones = 3;
    else if( bits >= 650 )
      iteraciones = 4;
    else if( bits >= 550 )
      iteraciones = 5;
    else if( bits >= 450 )
      iteraciones = 6;
    else if( bits >= 400 )
      iteraciones = 7;
    else if( bits >= 350 )
      iteraciones = 8;
    else if( bits >= 300 )
      iteraciones = 9;
    else if( bits >= 250 )
      iteraciones = 12;
    else if( bits >= 200 )
      iteraciones = 15;
    else if( bits >= 150 )
      iteraciones = 18;
    else if( bits >= 100 )
      iteraciones = 27;
    else
      iteraciones = 30;

    test->ponerIteraciones(iteraciones);
    while( !test->esPrimo(n) ){
      n++; n++;
    }
    
    //aquí, esPrimo(n) == true

    return n;
  }


  Z GenPrimos::leerPrimoFuerte(size_t bits)
  {
    Funciones *funcs = Funciones::getInstance();
    TestPrimoProb* testPrim; funcs->getFunc(testPrim);
    
    Z s,t;
    s = leerPrimoProb( bits/2 );
    t = leerPrimoProb( (bits/2) - 2 );

    Z r(t);
    r <<= 2;
    r++;
    t <<= 1;

    while( !testPrim->esPrimo(r) ){
      r += t; //este "t" es el doble del "t" inicial
    }

    Z p,p0;
    PotModular *potModular; funcs->getFunc(potModular);
    p0 = potModular->potModular(s,r-(Cifra)2, r);
    p0 *= s; p0 <<= 1; p0--;
    
    Z dosRS = r*s; dosRS <<= 1;
    p = p0; p += dosRS;
    while( !testPrim->esPrimo(p) ){
      p += dosRS;
    }

    return p;
  }

  
}        
    
