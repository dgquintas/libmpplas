/* 
 * $Id$
 */


#include "Primos.h"
#include "Random.h"
#include "Z_n.h"
#include "Funciones.h"
#include <cmath>
#include <algorithm>

namespace numth{

  RabinMiller::RabinMiller()
    : iteraciones_(5)
  {}

  bool RabinMiller::esPrimo(const Z& p, Z* testigo) 
  {
    numth::Funciones funcs;
    GCD* gcd = funcs.getGCD();
    RandomRapido* rnd = funcs.getRandomRapido();
    
    if( p == (Cifra)2 )
      return true;
    
    if(testigo){ 
      //se ha de rellenar "a toda costa", asi que ni se realiza
      //división por primos pequeños ni ninguna otra optimizacion... 
      //sólamente interesa conocer un testigo (de haberlo, claro)
      //Esto se utiliza para la función de detección de potencias de
      //primo
      Z_n z(p); 
      Z pMenosUno(p); pMenosUno--;
      size_t b = pMenosUno.numDoses();
      Z m = pMenosUno >> b;
      
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
          z = Z::convertir(Constantes::TABLA_PRIMOS_2000[i]);
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

      if( p.esPar() || p.esUno() ) 
        return false;

      size_t cota;
      if( p <= (Cifra)4000000 ){ // 2000^2
        cota = raizCuadrada(p[0]);
        for(size_t i = 0; Constantes::TABLA_PRIMOS_2000[i] <= cota; i++)
          if ( (!gcd->gcd(p, Constantes::TABLA_PRIMOS_2000[i]).esUno()) ) //si el gcd no es uno... 
            return false;

        return true;

        /* Resultado GANTIZADO */
      }
      else
        cota = 303;

      for(size_t i = 0; i < cota; i++)
        if ( (!gcd->gcd(p, Constantes::TABLA_PRIMOS_2000[i]).esUno()) ) //si el gcd no es uno... 
          return false;


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
      Z psi_3; psi_3[0] = (Cifra)25326001UL;
      Z psi_4; psi_4[0] = (Cifra)3215031751UL;
      Z psi_5; psi_5.potenciaBase(1); psi_5[1] = 501; psi_5[0] = 524283451;
      Z psi_6; psi_6.potenciaBase(1); psi_6[1] = 809; psi_6[0] = 121117919;
      Z psi_7; psi_7.potenciaBase(1); psi_7[1] = 79523; psi_7[0] = 1387448513;

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
      size_t b = pMenosUno.numDoses();
      Z m = pMenosUno >> b;
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
          z = Z::convertir(Constantes::TABLA_PRIMOS_2000[i]);

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

    Funciones funcs;
    RedModularALaMersenne* redmodmers = funcs.getModularReductionALaMersenne();

    if( !funcs.getTestPrimoProb()->esPrimo(Z::convertir(p)) )
      return false;
    
    Z s(Z::convertir((Cifra)4));
    
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


  Z GenPrimos::leerPrimoProb(size_t bits)
  {
    Funciones funcs;
    TestPrimoProb* test = funcs.getTestPrimoProb();
    RandomRapido* rnd = funcs.getRandomRapido();

    Z n(rnd->leerBits(bits));

    //poner a 1 los bits más y menos significativos 
    //FIXME: poner a 1 el bit mas significativo hace que el nº
    //generado sea siempre > que (2**bits)/2. asi que lo desativo (10/3)
//    size_t i = bits / BITS_EN_CIFRA;
//    size_t j = bits % BITS_EN_CIFRA;
//    Cifra mascara = (1 << j);

//    n[i] |= mascara; //el más
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
    Funciones funcs;
    TestPrimoProb* test = funcs.getTestPrimoProb();

    //caso especial
    if( comienzo == (Cifra)2 )
      return Z::convertir((Cifra)3);
    
    Z n = comienzo;
    if( comienzo.esPar() )
      n++;
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
    Funciones funcs;
    TestPrimoProb* testPrim = funcs.getTestPrimoProb();
    
    Z s,t;
    s = leerPrimoProb( bits/2 );
    t = leerPrimoProb( (bits/2) - 2 );

    Z r(t);
    r <<= 2;
    r++;
    t <<= 1;

    while( !testPrim->esPrimo(r) )
      r += t; //este "t" es el doble del "t" inicial

    Z p,p0;
    p0 = funcs.getPotModular()->potModular(s,r-(Cifra)2, r);
    p0 *= s; p0 <<= 1; p0--;
    
    Z dosRS = r*s; dosRS <<= 1;
    p = p0; p += dosRS;
    while( !testPrim->esPrimo(p) )
      p += dosRS;

    return p;
  }

  
}        
    
