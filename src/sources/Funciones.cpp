/* 
 * $Id$
 */

#include <memory> //for auto_ptr
#include "Funciones.h"

namespace numth{

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
    //auto_ptr takes care of freeing (destroying) the pointers (functions) not needed anymore
  }

  void Funciones::setTestPrimoProb(TestPrimoProb* ptr)
  {
    if( ptr ){
      testPrimoProbPTR.reset(ptr);
    }
    else{ //instantiate the default one
      testPrimoProbPTR.reset(new TestPrimoProbDFL());
    }
    return;
  }
  void Funciones::setTestPrimoMersenne(TestPrimoMersenne* ptr)
  {
    if( ptr ){
      testPrimoMersennePTR.reset(ptr);
    }
    else{ //instantiate the default one
      testPrimoMersennePTR.reset(new TestPrimoMersenneDFL);
    }
    return;
  }

  void Funciones::setRandomRapido(RandomRapido* ptr)
  {
    if( ptr ){
      randomRapidoPTR.reset(ptr);
    }
    else{ //instantiate the default one
      randomRapidoPTR.reset(new RandomRapidoDFL);
    }
    return;
  }
  void Funciones::setRandomSeguro(RandomSeguro* ptr)
  {
    if( ptr ){
      randomSeguroPTR.reset(ptr);
    }
    else{ //instantiate the default one
      randomSeguroPTR.reset(new RandomSeguroDFL);
    }
    return;
  }
  void Funciones::setPruebaRandom(PruebaRandom* ptr)
  {
    if( ptr ){
      pruebaRandomPTR.reset(ptr);
    }
    else{ //instantiate the default one
      pruebaRandomPTR.reset(new PruebaRandomDFL);
    }
    return;
  }

  void Funciones::setGenPrimos(GenPrimos* ptr)
  {
    if( ptr ){
      genPrimosPTR.reset(ptr);
    }
    else{ //instantiate the default one
      genPrimosPTR.reset(new GenPrimosDFL);
    }
    return;
  }
 
  void Funciones::setHash(Hash* ptr)
  {
    if( ptr ){
      hashPTR.reset(ptr);
    }
    else{ //instantiate the default one
      hashPTR.reset(new HashDFL);
    }
    return;
  } 

  void Funciones::setPotencia(Potencia* ptr)
  {
    if( ptr ){
      potenciaPTR.reset(ptr);
    }
    else{ //instantiate the default one
      potenciaPTR.reset(new PotenciaDFL);
    }
    return;
  } 
 
  void Funciones::setPotenciaR(PotenciaR* ptr)
  {
    if( ptr ){
      potenciaRPTR.reset(ptr);
    }
    else{ //instantiate the default one
      potenciaRPTR.reset(new PotenciaRDFL);
    }
    return;
  } 

  void Funciones::setGCD(GCD* ptr)
  {
    if( ptr ){
      gcdPTR.reset(ptr);
    }
    else{ //instantiate the default one
      gcdPTR.reset(new GCDDFL);
    }
    return;
  } 
 
  void Funciones::setGCDExt(GCDExt* ptr)
  {
    if( ptr ){
      gcdextPTR.reset(ptr);
    }
    else{ //instantiate the default one
      gcdextPTR.reset(new GCDExtDFL);
    }
    return;
  } 
  void Funciones::setLCM(LCM* ptr)
  {
    if( ptr ){
      lcmPTR.reset(ptr);
    }
    else{ //instantiate the default one
      lcmPTR.reset(new LCMDFL);
    }
    return;
  } 

  void Funciones::setPotModular(PotModular* ptr)
  {
    if( ptr ){
      potModularPTR.reset(ptr);
    }
    else{ //instantiate the default one
      potModularPTR.reset(new PotModularDFL);
    }
    return;
  } 

  void Funciones::setBarrettReduction(RedBarrett* ptr)
  {
    if( ptr ){
      redBarrettPTR.reset(ptr);
    }
    else{ //instantiate the default one
      redBarrettPTR.reset(new RedBarrettDFL);
    }
    return;
  } 
  void Funciones::setMontgomeryReduction(RedMontgomery* ptr)
  {
    if( ptr ){
      redMontgomeryPTR.reset(ptr);
    }
    else{ //instantiate the default one
      redMontgomeryPTR.reset(new RedMontgomeryDFL);
    }
    return;
  } 
  void Funciones::setModularReductionALaMersenne(RedModularALaMersenne* ptr)
  {
    if( ptr ){
      redModularALaMersennePTR.reset(ptr);
    }
    else{ //instantiate the default one
      redModularALaMersennePTR.reset(new RedModularALaMersenneDFL);
    }
    return;
  } 

  void Funciones::setKroneckerSymbol(SimboloKronecker* ptr)
  {
    if( ptr ){
      simboloKroneckerPTR.reset(ptr);
    }
    else{ //instantiate the default one
      simboloKroneckerPTR.reset(new SimboloKroneckerDFL);
    }
    return;
  } 
  void Funciones::setJacobiSymbol(SimboloJacobi* ptr)
  {
    if( ptr ){
      simboloJacobiPTR.reset(ptr);
    }
    else{ //instantiate the default one
      simboloJacobiPTR.reset(new SimboloJacobiDFL);
    }
    return;
  } 
  void Funciones::setLegendreSymbol(SimboloLegendre* ptr)
  {
    if( ptr ){
      simboloLegendrePTR.reset(ptr);
    }
    else{ //instantiate the default one
      simboloLegendrePTR.reset(new SimboloLegendreDFL);
    }
    return;
  } 

  void Funciones::setCRT(CRT* ptr)
  {
    if( ptr ){
      crtPTR.reset(ptr);
    }
    else{ //instantiate the default one
      crtPTR.reset(new CRTDFL);
    }
    return;
  } 

  void Funciones::setFactoriza(Factoriza* ptr)
  {
    if( ptr ){
      factorizaPTR.reset(ptr);
    }
    else{ //instantiate the default one
      factorizaPTR.reset(new FactorizaDFL);
    }
    return;
  } 

  void Funciones::setExponencial(Exponencial* ptr)
  {
    if( ptr ){
      exponencialPTR.reset(ptr);
    }
    else{ //instantiate the default one
      exponencialPTR.reset(new ExponencialDFL);
    }
    return;
  } 

  void Funciones::setLn(Ln* ptr)
  {
    if( ptr ){
      lnPTR.reset(ptr);
    }
    else{ //instantiate the default one
      lnPTR.reset(new LnDFL);
    }
    return;
  } 

  void Funciones::setCoseno(Coseno* ptr)
  {
    if( ptr ){
      cosenoPTR.reset(ptr);
    }
    else{ //instantiate the default one
      cosenoPTR.reset(new CosenoDFL);
    }
    return;
  } 

  void Funciones::setSeno(Seno* ptr)
  {
    if( ptr ){
      senoPTR.reset(ptr);
    }
    else{ //instantiate the default one
      senoPTR.reset(new SenoDFL);
    }
    return;
  } 
  
  void Funciones::setArcoTangente(ArcoTangente* ptr)
  {
    if( ptr ){
      arcotangentePTR.reset(ptr);
    }
    else{ //instantiate the default one
      arcotangentePTR.reset(new ArcoTangenteDFL);
    }
    return;
  } 
  
  void Funciones::setPi(Pi* ptr)
  {
    if( ptr ){
      piPTR.reset(ptr);
    }
    else{ //instantiate the default one
      piPTR.reset(new PiDFL);
    }
    return;
  } 



///////////////////////////////////////////////////////////////////////////////////////////
  
  
 
  TestPrimoProb* Funciones::getTestPrimoProb(void)
  {
    if ( testPrimoProbPTR.get() == NULL )
      //instanciar la implementacion concreta por defecto, que se habra definido p ej
      //via typedef en la cabecera del tipo
      testPrimoProbPTR.reset(new TestPrimoProbDFL);
                                               
    return testPrimoProbPTR.get();
  }                  
  TestPrimoMersenne* Funciones::getTestPrimoMersenne(void)
  {
    if ( testPrimoMersennePTR.get() == NULL )
      //instanciar la implementacion concreta por defecto, que se habra definido p ej
      //via typedef en la cabecera del tipo
      testPrimoMersennePTR.reset(new TestPrimoMersenneDFL);
                                               
    return testPrimoMersennePTR.get();
  }                  
                                              
  RandomRapido* Funciones::getRandomRapido(void)
  {
    if ( randomRapidoPTR.get() == NULL )
      //instanciar la implementacion concreta por defecto, que se habra definido p ej
      //via typedef en la cabecera del tipo
      randomRapidoPTR.reset(new RandomRapidoDFL);
    
    return randomRapidoPTR.get();
  }   
  RandomSeguro* Funciones::getRandomSeguro(void)
  {
    if ( randomSeguroPTR.get() == NULL )
      //instanciar la implementacion concreta por defecto, que se habra definido p ej
      //via typedef en la cabecera del tipo
      randomSeguroPTR.reset(new RandomSeguroDFL);
    
    return randomSeguroPTR.get();
  }   
  PruebaRandom* Funciones::getPruebaRandom(void)
  {
    if ( pruebaRandomPTR.get() == NULL )
      //instanciar la implementacion concreta por defecto, que se habra definido p ej
      //via typedef en la cabecera del tipo
      pruebaRandomPTR.reset(new PruebaRandomDFL);
    
    return pruebaRandomPTR.get();
  }   

  GenPrimos* Funciones::getGenPrimos(void)
  {
    if ( genPrimosPTR.get() == NULL )
      //instanciar la implementacion concreta por defecto, que se habra definido p ej
      //via typedef en la cabecera del tipo
      genPrimosPTR.reset(new GenPrimosDFL);
    
    return genPrimosPTR.get();
  }
 
  Hash* Funciones::getHash(void)
  {
    if ( hashPTR.get() == NULL )
      //instanciar la implementacion concreta por defecto, que se habra definido p ej
      //via typedef en la cabecera del tipo
      hashPTR.reset(new HashDFL);
    
    return hashPTR.get();
  }

  Potencia* Funciones::getPotencia(void)
  {
    if ( potenciaPTR.get() == NULL )
      //instanciar la implementacion concreta por defecto, que se habra definido p ej
      //via typedef en la cabecera del tipo
      potenciaPTR.reset(new PotenciaDFL);
    
    return potenciaPTR.get();
  }

  PotenciaR* Funciones::getPotenciaR(void)
  {
    if ( potenciaRPTR.get() == NULL )
      //instanciar la implementacion concreta por defecto, que se habra definido p ej
      //via typedef en la cabecera del tipo
      potenciaRPTR.reset(new PotenciaRDFL);
    
    return potenciaRPTR.get();
  }

  
  GCD* Funciones::getGCD(void)
  {
    if ( gcdPTR.get() == NULL )
      //instanciar la implementacion concreta por defecto, que se habra definido p ej
      //via typedef en la cabecera del tipo
      gcdPTR.reset(new GCDDFL);
    
    return gcdPTR.get();
  }

  GCDExt* Funciones::getGCDExt(void)
  {
    if ( gcdextPTR.get() == NULL )
      //instanciar la implementacion concreta por defecto, que se habra definido p ej
      //via typedef en la cabecera del tipo
      gcdextPTR.reset(new GCDExtDFL);
    
    return gcdextPTR.get();
  }
  LCM* Funciones::getLCM(void)
  {
    if ( lcmPTR.get() == NULL )
      //instanciar la implementacion concreta por defecto, que se habra definido p ej
      //via typedef en la cabecera del tipo
      lcmPTR.reset(new LCMDFL);
    
    return lcmPTR.get();
  }

  PotModular* Funciones::getPotModular(void)
  {
    if ( potModularPTR.get() == NULL )
      //instanciar la implementacion concreta por defecto, que se habra definido p ej
      //via typedef en la cabecera del tipo
      potModularPTR.reset(new PotModularDFL);
    
    return potModularPTR.get();
  }

  RedBarrett* Funciones::getBarrettReduction(void)
  {
    if ( redBarrettPTR.get() == NULL )
      //instanciar la implementacion concreta por defecto, que se habra definido p ej
      //via typedef en la cabecera del tipo
      redBarrettPTR.reset(new RedBarrettDFL);
    
    return redBarrettPTR.get();
  }
  RedMontgomery* Funciones::getMontgomeryReduction(void)
  {
    if ( redMontgomeryPTR.get() == NULL )
      //instanciar la implementacion concreta por defecto, que se habra definido p ej
      //via typedef en la cabecera del tipo
      redMontgomeryPTR.reset(new RedMontgomeryDFL);
    
    return redMontgomeryPTR.get();
  }
  RedModularALaMersenne* Funciones::getModularReductionALaMersenne(void)
  {
    if ( redModularALaMersennePTR.get() == NULL )
      //instanciar la implementacion concreta por defecto, que se habra definido p ej
      //via typedef en la cabecera del tipo
      redModularALaMersennePTR.reset(new RedModularALaMersenneDFL);
    
    return redModularALaMersennePTR.get();
  }

  SimboloKronecker* Funciones::getKroneckerSymbol(void)
  {
    if ( simboloKroneckerPTR.get() == NULL )
      //instanciar la implementacion concreta por defecto, que se habra definido p ej
      //via typedef en la cabecera del tipo
      simboloKroneckerPTR.reset(new SimboloKroneckerDFL);
    
    return simboloKroneckerPTR.get();
  }
  SimboloJacobi* Funciones::getJacobiSymbol(void)
  {
    if ( simboloJacobiPTR.get() == NULL )
      //instanciar la implementacion concreta por defecto, que se habra definido p ej
      //via typedef en la cabecera del tipo
      simboloJacobiPTR.reset(new SimboloJacobiDFL);
    
    return simboloJacobiPTR.get();
  }
  SimboloLegendre* Funciones::getLegendreSymbol(void)
  {
    if ( simboloLegendrePTR.get() == NULL )
      //instanciar la implementacion concreta por defecto, que se habra definido p ej
      //via typedef en la cabecera del tipo
      simboloLegendrePTR.reset(new SimboloLegendreDFL);
    
    return simboloLegendrePTR.get();
  }


  CRT* Funciones::getCRT(void)
  {
    if ( crtPTR.get() == NULL )
      //instanciar la implementacion concreta por defecto, que se habra definido p ej
      //via typedef en la cabecera del tipo
      crtPTR.reset(new CRTDFL);
    
    return crtPTR.get();
  }

  Factoriza* Funciones::getFactoriza(void)
  {
    if ( factorizaPTR.get() == NULL )
      //instanciar la implementacion concreta por defecto, que se habra definido p ej
      //via typedef en la cabecera del tipo
      factorizaPTR.reset(new FactorizaDFL);
    
    return factorizaPTR.get();
  }

  Exponencial* Funciones::getExponencial(void)
  {
    if ( exponencialPTR.get() == NULL )
      //instanciar la implementacion concreta por defecto, que se habra definido p ej
      //via typedef en la cabecera del tipo
      exponencialPTR.reset(new ExponencialDFL);
    
    return exponencialPTR.get();
  }
 
  Ln* Funciones::getLn(void)
  {
    if ( lnPTR.get() == NULL )
      //instanciar la implementacion concreta por defecto, que se habra definido p ej
      //via typedef en la cabecera del tipo
      lnPTR.reset(new LnDFL);
    
    return lnPTR.get();
  }
 
  Coseno* Funciones::getCoseno(void)
  {
    if ( cosenoPTR.get() == NULL )
      //instanciar la implementacion concreta por defecto, que se habra definido p ej
      //via typedef en la cabecera del tipo
      cosenoPTR.reset(new CosenoDFL);
    
    return cosenoPTR.get();
  }

  Seno* Funciones::getSeno(void)
  {
    if ( senoPTR.get() == NULL )
      //instanciar la implementacion concreta por defecto, que se habra definido p ej
      //via typedef en la cabecera del tipo
      senoPTR.reset(new SenoDFL);
    
    return senoPTR.get();
  }

  
  ArcoTangente* Funciones::getArcotangente(void)
  {
    if ( arcotangentePTR.get() == NULL )
      //instanciar la implementacion concreta por defecto, que se habra definido p ej
      //via typedef en la cabecera del tipo
      arcotangentePTR.reset(new ArcoTangenteDFL);
    
    return arcotangentePTR.get();
  }

  
  Pi* Funciones::getPi(void)
  {
    if ( piPTR.get() == NULL )
      //instanciar la implementacion concreta por defecto, que se habra definido p ej
      //via typedef en la cabecera del tipo
      piPTR.reset(new PiDFL);
    
    return piPTR.get();
  }

}
