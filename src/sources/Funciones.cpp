/* 
 * $Id$
 */

#include "Funciones.h"

namespace numth{

  TestPrimoProb* Funciones::testPrimoProbPTR = NULL;
  TestPrimoMersenne* Funciones::testPrimoMersennePTR = NULL;
//  Random* Funciones::randomPTR = NULL;
  RandomRapido* Funciones::randomRapidoPTR = NULL;
  RandomSeguro* Funciones::randomSeguroPTR = NULL;
  PruebaRandom* Funciones::pruebaRandomPTR = NULL;
  GenPrimos* Funciones::genPrimosPTR = NULL;
  Hash* Funciones::hashPTR = NULL;
  Potencia* Funciones::potenciaPTR = NULL;
  PotenciaR* Funciones::potenciaRPTR = NULL;
  GCD* Funciones::gcdPTR = NULL;
  GCDExt* Funciones::gcdextPTR = NULL;
  LCM* Funciones::lcmPTR = NULL;
  PotModular* Funciones::potModularPTR = NULL;
  RedBarrett* Funciones::redBarrettPTR = NULL;
  RedMontgomery* Funciones::redMontgomeryPTR = NULL;
  RedModularALaMersenne* Funciones::redModularALaMersennePTR = NULL;
  SimboloKronecker* Funciones::simboloKroneckerPTR = NULL;
  SimboloJacobi* Funciones::simboloJacobiPTR = NULL;
  SimboloLegendre* Funciones::simboloLegendrePTR = NULL;
  CRT* Funciones::crtPTR = NULL;
  Factoriza* Funciones::factorizaPTR = NULL;
  Exponencial* Funciones::exponencialPTR = NULL;
  Ln* Funciones::lnPTR = NULL;
  Coseno* Funciones::cosenoPTR = NULL;
  Seno* Funciones::senoPTR = NULL;
  ArcoTangente* Funciones::arcotangentePTR = NULL;
  Pi* Funciones::piPTR = NULL;


  /** Destructor.
   *
   * @note No se liberan los punteros ya que no tiene sentido que las
   *       instancias de las funciones esten creandose y destruyendose a
   *       la vez que la instancia de Funciones (ya que para eso se
   *       declaran como "static"). 
   *       Y ya que las funciones habrán de perdurar durante todo el programa, se
   *       deja que sea el sistema, al finalizar totalmente la ejecución,
   *       quien libere los recursos.
   */
  Funciones::~Funciones()
  { 
    // No se liberan los punteros ya que no tiene sentido que las
    // instancias de las funciones esten creandose y destruyendose a
    // la vez que la instancia de Funciones (justo por eso son
    // static...). 
    // Y ya que las funciones habrán de perdurar todo el programa, se
    // deja que sea el sistema, al finalizar totalmente la ejecución,
    // quien libere las cosas.
  }

  void Funciones::ponerTestPrimoProb(TestPrimoProb* ptr)
  {
    if( ptr ){
      if( testPrimoProbPTR)
        delete testPrimoProbPTR;
      testPrimoProbPTR = ptr;
    }
    else{ //poner el por omision
      if( testPrimoProbPTR )
        delete testPrimoProbPTR;
      testPrimoProbPTR = new TestPrimoProbDFL;
    }
    return;
  }
  void Funciones::ponerTestPrimoMersenne(TestPrimoMersenne* ptr)
  {
    if( ptr ){
      if( testPrimoMersennePTR)
        delete testPrimoMersennePTR;
      testPrimoMersennePTR = ptr;
    }
    else{ //poner el por omision
      if( testPrimoMersennePTR )
        delete testPrimoMersennePTR;
      testPrimoMersennePTR = new TestPrimoMersenneDFL;
    }
    return;
  }

  void Funciones::ponerRandomRapido(RandomRapido* ptr)
  {
    if( ptr ){
      if( randomRapidoPTR)
        delete randomRapidoPTR;
      randomRapidoPTR = ptr;
    }
    else{ //poner el por omision
      if( randomRapidoPTR )
        delete randomRapidoPTR;
      randomRapidoPTR = new RandomRapidoDFL;
    }
    return;
  }
  void Funciones::ponerRandomSeguro(RandomSeguro* ptr)
  {
    if( ptr ){
      if( randomSeguroPTR)
        delete randomSeguroPTR;
      randomSeguroPTR = ptr;
    }
    else{ //poner el por omision
      if( randomSeguroPTR )
        delete randomSeguroPTR;
      randomSeguroPTR = new RandomSeguroDFL;
    }
    return;
  }
  void Funciones::ponerPruebaRandom(PruebaRandom* ptr)
  {
    if( ptr ){
      if( pruebaRandomPTR)
        delete pruebaRandomPTR;
      pruebaRandomPTR = ptr;
    }
    else{ //poner el por omision
      if( pruebaRandomPTR )
        delete pruebaRandomPTR;
      pruebaRandomPTR = new PruebaRandomDFL;
    }
    return;
  }

  void Funciones::ponerGenPrimos(GenPrimos* ptr)
  {
    if( ptr ){
      if( genPrimosPTR)
        delete genPrimosPTR;
      genPrimosPTR = ptr;
    }
    else{ //poner el por omision
      if( genPrimosPTR )
        delete genPrimosPTR;
      genPrimosPTR = new GenPrimosDFL;
    }
    return;
  }
 
  void Funciones::ponerHash(Hash* ptr)
  {
    if( ptr ){
      if( hashPTR)
        delete hashPTR;
      hashPTR = ptr;
    }
    else{ //poner el por omision
      if( hashPTR )
        delete hashPTR;
      hashPTR = new HashDFL;
    }
    return;
  } 

  void Funciones::ponerPotencia(Potencia* ptr)
  {
    if( ptr ){
      if( potenciaPTR)
        delete potenciaPTR;
      potenciaPTR = ptr;
    }
    else{ //poner el por omision
      if( potenciaPTR )
        delete potenciaPTR;
      potenciaPTR = new PotenciaDFL;
    }
    return;
  } 
 
  void Funciones::ponerPotenciaR(PotenciaR* ptr)
  {
    if( ptr ){
      if( potenciaRPTR)
        delete potenciaRPTR;
      potenciaRPTR = ptr;
    }
    else{ //poner el por omision
      if( potenciaRPTR )
        delete potenciaRPTR;
      potenciaRPTR = new PotenciaRDFL;
    }
    return;
  } 

  void Funciones::ponerGCD(GCD* ptr)
  {
    if( ptr ){
      if( gcdPTR)
        delete gcdPTR;
      gcdPTR = ptr;
    }
    else{ //poner el por omision
      if( gcdPTR )
        delete gcdPTR;
      gcdPTR = new GCDDFL;
    }
    return;
  } 
 
  void Funciones::ponerGCDExt(GCDExt* ptr)
  {
    if( ptr ){
      if( gcdextPTR)
        delete gcdextPTR;
      gcdextPTR = ptr;
    }
    else{ //poner el por omision
      if( gcdextPTR )
        delete gcdextPTR;
      gcdextPTR = new GCDExtDFL;
    }
    return;
  } 
  void Funciones::ponerLCM(LCM* ptr)
  {
    if( ptr ){
      if( lcmPTR)
        delete lcmPTR;
      lcmPTR = ptr;
    }
    else{ //poner el por omision
      if( lcmPTR )
        delete lcmPTR;
      lcmPTR = new LCMDFL;
    }
    return;
  } 

  void Funciones::ponerPotModular(PotModular* ptr)
  {
    if( ptr ){
      if( potModularPTR)
        delete potModularPTR;
      potModularPTR = ptr;
    }
    else{ //poner el por omision
      if( potModularPTR )
        delete potModularPTR;
      potModularPTR = new PotModularDFL;
    }
    return;
  } 

  void Funciones::ponerRedBarrett(RedBarrett* ptr)
  {
    if( ptr ){
      if( redBarrettPTR)
        delete redBarrettPTR;
      redBarrettPTR = ptr;
    }
    else{ //poner el por omision
      if( redBarrettPTR )
        delete redBarrettPTR;
      redBarrettPTR = new RedBarrettDFL;
    }
    return;
  } 
  void Funciones::ponerRedMontgomery(RedMontgomery* ptr)
  {
    if( ptr ){
      if( redMontgomeryPTR)
        delete redMontgomeryPTR;
      redMontgomeryPTR = ptr;
    }
    else{ //poner el por omision
      if( redMontgomeryPTR )
        delete redMontgomeryPTR;
      redMontgomeryPTR = new RedMontgomeryDFL;
    }
    return;
  } 
  void Funciones::ponerRedModularALaMersenne(RedModularALaMersenne* ptr)
  {
    if( ptr ){
      if( redModularALaMersennePTR)
        delete redModularALaMersennePTR;
      redModularALaMersennePTR = ptr;
    }
    else{ //poner el por omision
      if( redModularALaMersennePTR )
        delete redModularALaMersennePTR;
      redModularALaMersennePTR = new RedModularALaMersenneDFL;
    }
    return;
  } 

  void Funciones::ponerSimboloKronecker(SimboloKronecker* ptr)
  {
    if( ptr ){
      if( simboloKroneckerPTR)
        delete simboloKroneckerPTR;
      simboloKroneckerPTR = ptr;
    }
    else{ //poner el por omision
      if( simboloKroneckerPTR )
        delete simboloKroneckerPTR;
      simboloKroneckerPTR = new SimboloKroneckerDFL;
    }
    return;
  } 
  void Funciones::ponerSimboloJacobi(SimboloJacobi* ptr)
  {
    if( ptr ){
      if( simboloJacobiPTR)
        delete simboloJacobiPTR;
      simboloJacobiPTR = ptr;
    }
    else{ //poner el por omision
      if( simboloJacobiPTR )
        delete simboloJacobiPTR;
      simboloJacobiPTR = new SimboloJacobiDFL;
    }
    return;
  } 
  void Funciones::ponerSimboloLegendre(SimboloLegendre* ptr)
  {
    if( ptr ){
      if( simboloLegendrePTR)
        delete simboloLegendrePTR;
      simboloLegendrePTR = ptr;
    }
    else{ //poner el por omision
      if( simboloLegendrePTR )
        delete simboloLegendrePTR;
      simboloLegendrePTR = new SimboloLegendreDFL;
    }
    return;
  } 

  void Funciones::ponerCRT(CRT* ptr)
  {
    if( ptr ){
      if( crtPTR)
        delete crtPTR;
      crtPTR = ptr;
    }
    else{ //poner el por omision
      if( crtPTR )
        delete crtPTR;
      crtPTR = new CRTDFL;
    }
    return;
  } 

  void Funciones::ponerFactoriza(Factoriza* ptr)
  {
    if( ptr ){
      if( factorizaPTR)
        delete factorizaPTR;
      factorizaPTR = ptr;
    }
    else{ //poner el por omision
      if( factorizaPTR )
        delete factorizaPTR;
      factorizaPTR = new FactorizaDFL;
    }
    return;
  } 

  void Funciones::ponerExponencial(Exponencial* ptr)
  {
    if( ptr ){
      if( exponencialPTR)
        delete exponencialPTR;
      exponencialPTR = ptr;
    }
    else{ //poner el por omision
      if( exponencialPTR )
        delete exponencialPTR;
      exponencialPTR = new ExponencialDFL;
    }
    return;
  } 

  void Funciones::ponerLn(Ln* ptr)
  {
    if( ptr ){
      if( lnPTR)
        delete lnPTR;
      lnPTR = ptr;
    }
    else{ //poner el por omision
      if( lnPTR )
        delete lnPTR;
      lnPTR = new LnDFL;
    }
    return;
  } 

  void Funciones::ponerCoseno(Coseno* ptr)
  {
    if( ptr ){
      if( cosenoPTR)
        delete cosenoPTR;
      cosenoPTR = ptr;
    }
    else{ //poner el por omision
      if( cosenoPTR )
        delete cosenoPTR;
      cosenoPTR = new CosenoDFL;
    }
    return;
  } 

  void Funciones::ponerSeno(Seno* ptr)
  {
    if( ptr ){
      if( senoPTR)
        delete senoPTR;
      senoPTR = ptr;
    }
    else{ //poner el por omision
      if( senoPTR )
        delete senoPTR;
      senoPTR = new SenoDFL;
    }
    return;
  } 

  
  void Funciones::ponerArcoTangente(ArcoTangente* ptr)
  {
    if( ptr ){
      if( arcotangentePTR)
        delete arcotangentePTR;
      arcotangentePTR = ptr;
    }
    else{ //poner el por omision
      if( arcotangentePTR )
        delete arcotangentePTR;
      arcotangentePTR = new ArcoTangenteDFL;
    }
    return;
  } 

  
  void Funciones::ponerPi(Pi* ptr)
  {
    if( ptr ){
      if( piPTR)
        delete piPTR;
      piPTR = ptr;
    }
    else{ //poner el por omision
      if( piPTR )
        delete piPTR;
      piPTR = new PiDFL;
    }
    return;
  } 




  
  
 
  TestPrimoProb* Funciones::testPrimoProb(void)
  {
    if ( !testPrimoProbPTR )
      //instanciar la implementacion concreta por defecto, que se habra definido p ej
      //via typedef en la cabecera del tipo
      testPrimoProbPTR = new TestPrimoProbDFL;
                                               
    return testPrimoProbPTR;
  }                  
  TestPrimoMersenne* Funciones::testPrimoMersenne(void)
  {
    if ( !testPrimoMersennePTR )
      //instanciar la implementacion concreta por defecto, que se habra definido p ej
      //via typedef en la cabecera del tipo
      testPrimoMersennePTR = new TestPrimoMersenneDFL;
                                               
    return testPrimoMersennePTR;
  }                  
                                              
  RandomRapido* Funciones::randomRapido(void)
  {
    if ( !randomRapidoPTR )
      //instanciar la implementacion concreta por defecto, que se habra definido p ej
      //via typedef en la cabecera del tipo
      randomRapidoPTR = new RandomRapidoDFL;
    
    return randomRapidoPTR;
  }   
  RandomSeguro* Funciones::randomSeguro(void)
  {
    if ( !randomSeguroPTR )
      //instanciar la implementacion concreta por defecto, que se habra definido p ej
      //via typedef en la cabecera del tipo
      randomSeguroPTR = new RandomSeguroDFL;
    
    return randomSeguroPTR;
  }   
  PruebaRandom* Funciones::pruebaRandom(void)
  {
    if ( !pruebaRandomPTR )
      //instanciar la implementacion concreta por defecto, que se habra definido p ej
      //via typedef en la cabecera del tipo
      pruebaRandomPTR = new PruebaRandomDFL;
    
    return pruebaRandomPTR;
  }   

  GenPrimos* Funciones::genPrimos(void)
  {
    if ( !genPrimosPTR )
      //instanciar la implementacion concreta por defecto, que se habra definido p ej
      //via typedef en la cabecera del tipo
      genPrimosPTR = new GenPrimosDFL;
    
    return genPrimosPTR;
  }
 
  Hash* Funciones::hash(void)
  {
    if ( !hashPTR )
      //instanciar la implementacion concreta por defecto, que se habra definido p ej
      //via typedef en la cabecera del tipo
      hashPTR = new HashDFL;
    
    return hashPTR;
  }

  Potencia* Funciones::potencia(void)
  {
    if ( !potenciaPTR )
      //instanciar la implementacion concreta por defecto, que se habra definido p ej
      //via typedef en la cabecera del tipo
      potenciaPTR = new PotenciaDFL;
    
    return potenciaPTR;
  }

  PotenciaR* Funciones::potenciaR(void)
  {
    if ( !potenciaRPTR )
      //instanciar la implementacion concreta por defecto, que se habra definido p ej
      //via typedef en la cabecera del tipo
      potenciaRPTR = new PotenciaRDFL;
    
    return potenciaRPTR;
  }

  
  GCD* Funciones::gcd(void)
  {
    if ( !gcdPTR )
      //instanciar la implementacion concreta por defecto, que se habra definido p ej
      //via typedef en la cabecera del tipo
      gcdPTR = new GCDDFL;
    
    return gcdPTR;
  }

  GCDExt* Funciones::gcdext(void)
  {
    if ( !gcdextPTR )
      //instanciar la implementacion concreta por defecto, que se habra definido p ej
      //via typedef en la cabecera del tipo
      gcdextPTR = new GCDExtDFL;
    
    return gcdextPTR;
  }
  LCM* Funciones::lcm(void)
  {
    if ( !lcmPTR )
      //instanciar la implementacion concreta por defecto, que se habra definido p ej
      //via typedef en la cabecera del tipo
      lcmPTR = new LCMDFL;
    
    return lcmPTR;
  }

  PotModular* Funciones::potModular(void)
  {
    if ( !potModularPTR )
      //instanciar la implementacion concreta por defecto, que se habra definido p ej
      //via typedef en la cabecera del tipo
      potModularPTR = new PotModularDFL;
    
    return potModularPTR;
  }

  RedBarrett* Funciones::redBarrett(void)
  {
    if ( !redBarrettPTR )
      //instanciar la implementacion concreta por defecto, que se habra definido p ej
      //via typedef en la cabecera del tipo
      redBarrettPTR = new RedBarrettDFL;
    
    return redBarrettPTR;
  }
  RedMontgomery* Funciones::redMontgomery(void)
  {
    if ( !redMontgomeryPTR )
      //instanciar la implementacion concreta por defecto, que se habra definido p ej
      //via typedef en la cabecera del tipo
      redMontgomeryPTR = new RedMontgomeryDFL;
    
    return redMontgomeryPTR;
  }
  RedModularALaMersenne* Funciones::redModularALaMersenne(void)
  {
    if ( !redModularALaMersennePTR )
      //instanciar la implementacion concreta por defecto, que se habra definido p ej
      //via typedef en la cabecera del tipo
      redModularALaMersennePTR = new RedModularALaMersenneDFL;
    
    return redModularALaMersennePTR;
  }

  SimboloKronecker* Funciones::simboloKronecker(void)
  {
    if ( !simboloKroneckerPTR )
      //instanciar la implementacion concreta por defecto, que se habra definido p ej
      //via typedef en la cabecera del tipo
      simboloKroneckerPTR = new SimboloKroneckerDFL;
    
    return simboloKroneckerPTR;
  }
  SimboloJacobi* Funciones::simboloJacobi(void)
  {
    if ( !simboloJacobiPTR )
      //instanciar la implementacion concreta por defecto, que se habra definido p ej
      //via typedef en la cabecera del tipo
      simboloJacobiPTR = new SimboloJacobiDFL;
    
    return simboloJacobiPTR;
  }
  SimboloLegendre* Funciones::simboloLegendre(void)
  {
    if ( !simboloLegendrePTR )
      //instanciar la implementacion concreta por defecto, que se habra definido p ej
      //via typedef en la cabecera del tipo
      simboloLegendrePTR = new SimboloLegendreDFL;
    
    return simboloLegendrePTR;
  }


  CRT* Funciones::crt(void)
  {
    if ( !crtPTR )
      //instanciar la implementacion concreta por defecto, que se habra definido p ej
      //via typedef en la cabecera del tipo
      crtPTR = new CRTDFL;
    
    return crtPTR;
  }

  Factoriza* Funciones::factoriza(void)
  {
    if ( !factorizaPTR )
      //instanciar la implementacion concreta por defecto, que se habra definido p ej
      //via typedef en la cabecera del tipo
      factorizaPTR = new FactorizaDFL;
    
    return factorizaPTR;
  }

  Exponencial* Funciones::exponencial(void)
  {
    if ( !exponencialPTR )
      //instanciar la implementacion concreta por defecto, que se habra definido p ej
      //via typedef en la cabecera del tipo
      exponencialPTR = new ExponencialDFL;
    
    return exponencialPTR;
  }
 
  Ln* Funciones::ln(void)
  {
    if ( !lnPTR )
      //instanciar la implementacion concreta por defecto, que se habra definido p ej
      //via typedef en la cabecera del tipo
      lnPTR = new LnDFL;
    
    return lnPTR;
  }
 
  Coseno* Funciones::coseno(void)
  {
    if ( !cosenoPTR )
      //instanciar la implementacion concreta por defecto, que se habra definido p ej
      //via typedef en la cabecera del tipo
      cosenoPTR = new CosenoDFL;
    
    return cosenoPTR;
  }

  Seno* Funciones::seno(void)
  {
    if ( !senoPTR )
      //instanciar la implementacion concreta por defecto, que se habra definido p ej
      //via typedef en la cabecera del tipo
      senoPTR = new SenoDFL;
    
    return senoPTR;
  }

  
  ArcoTangente* Funciones::arcotangente(void)
  {
    if ( !arcotangentePTR )
      //instanciar la implementacion concreta por defecto, que se habra definido p ej
      //via typedef en la cabecera del tipo
      arcotangentePTR = new ArcoTangenteDFL;
    
    return arcotangentePTR;
  }

  
  Pi* Funciones::pi(void)
  {
    if ( !piPTR )
      //instanciar la implementacion concreta por defecto, que se habra definido p ej
      //via typedef en la cabecera del tipo
      piPTR = new PiDFL;
    
    return piPTR;
  }

}
