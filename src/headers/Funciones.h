/* 
 * $Id$
 */

#ifndef __FUNCIONES_H
#define __FUNCIONES_H

#include "Random.h"
#include "Primos.h"
#include "Potencia.h"
#include "GCD.h"
#include "Hash.h"
#include "RedModular.h"
#include "SimbolosLegendre.h"
#include "CRT.h"
#include "LCM.h"
#include "Factor.h"
#include "Trascendentes.h"

#include <memory>


using std::auto_ptr;

namespace numth{

  /** Clase repositorio de funciones.
   *
   * Esta clase implementa los mecanismos expuestos en la
   * documentación de teoría (dentro del capítulo "Implementación de
   * algoritmos básicos") en lo relativo al repositorio de
   * funciones. 
   */
  class Funciones
  {
    public:

      /** Asignar tests de composición por defecto */
      void setTestPrimoProb(TestPrimoProb* ptr);
      /** Asignar test de primalidad para primos de Mersenne por
       * defecto */
      void setTestPrimoMersenne(TestPrimoMersenne* ptr);
      /** Asignar generador de números aleatorios por defecto */
      void setRandomRapido(RandomRapido* ptr);
      /** Asignar generador de números aleatorios seguros por defecto */
      void setRandomSeguro(RandomSeguro* ptr);
      /** Asignar tests de aleatoriedad por defecto*/
      void setPruebaRandom(PruebaRandom* ptr);
      /** Asignar generador de primos por defecto */
      void setGenPrimos(GenPrimos* ptr);
      /** Asignar función hash por defecto */
      void setHash(Hash* ptr);
      /** Asignar método de potenciación por defecto*/
      void setPotencia(Potencia* ptr);
      /** Asignar método de potenciación de reales por defecto*/
      void setPotenciaR(PotenciaR* ptr);

      /** Asignar método para el cálculo del máximo común divisor por
       * defecto*/
      void setGCD(GCD* ptr);
      /** Asignar método para el cálculo del máximo común divisor
       * extendido por defecto */
      void setGCDExt(GCDExt* ptr);
      /** Asignar método para el cálculo del mínimo común multiplo por
       * defecto*/
      void setLCM(LCM* ptr);
      /** Asignar método de potenciación modular por defecto */
      void setPotModular(PotModular* ptr);
      /** Asignar algoritmo para la reducción de Barrett por defecto */
      void setBarrettReduction(RedBarrett* ptr);
      /** Asignar algoritmo para la reducción de Montogomery por
       * defecto */
      void setMontgomeryReduction(RedMontgomery* ptr);
      /** Asignar algoritmo para la reducción de números de la forma
       * \f$ b^t-c\f$ con \f$c\f$ un número de \f$l\f$ dígitos en base 
       * \f$b\f$ y \f$l < t\f$ por defecto*/
      void setModularReductionALaMersenne(RedModularALaMersenne* ptr);
      /** Asignar algoritmo para al cálculo del símbolo de Kronecker
       * por defecto*/
      void setKroneckerSymbol(SimboloKronecker* ptr);
      /** Asignar algoritmo para el cálculo del símbolo de Jacobi por
       * defecto */
      void setJacobiSymbol(SimboloJacobi* ptr);
      /** Asignar algoritmo para el cálculo del símbolo de Legendre
       * por defecto*/
      void setLegendreSymbol(SimboloLegendre* ptr);
      /** Asignar algoritmo para el cálculo del Teorema del Resto
       * Chino por defecto*/
      void setCRT(CRT* ptr); 
      /** Asignar método de factorización por defecto */
      void setFactoriza(Factoriza* ptr);
       /** Asignar método de calculo de exponencial por defecto */
      void setExponencial(Exponencial* ptr);
      /** Asignar método de calculo de log nep por defecto */
      void setLn(Ln* ptr);
      /** Asignar método de calculo del coseno por defecto */
      void setCoseno(Coseno* ptr);
      /** Asignar método de calculo del seno por defecto */
      void setSeno(Seno* ptr);
      /** Asignar método de calculo del arcotangente por defecto */
      void setArcoTangente(ArcoTangente* ptr);
      /** Asignar método de calculo de \f$ \pi \f$ por defecto */
      void setPi(Pi* ptr);
   






      /** Obtención del tests de composición por defecto */
      TestPrimoProb* getTestPrimoProb(void);
      /** Obtención del test de primalidad para primos de Mersenne por
       * defecto */
      TestPrimoMersenne* getTestPrimoMersenne(void);
      /** Obtención del generador de números aleatorios por defecto */
      RandomRapido* getRandomRapido(void);
      /** Obtención del generador de números aleatorios seguros por defecto */
      RandomSeguro* getRandomSeguro(void);
      /** Obtención del tests de aleatoriedad por defecto*/
      PruebaRandom* getPruebaRandom(void);
      /** Obtención del generador de primos por defecto */
      GenPrimos* getGenPrimos(void);
      /** Obtención del función hash por defecto */
      Hash* getHash(void);
      /** Obtención del método de potenciación por defecto*/
      Potencia* getPotencia(void);
      /** Obtención del método de potenciación de reales por defecto*/
      PotenciaR* getPotenciaR(void);
      /** Obtención del método para el cálculo del máximo común divisor por
       * defecto*/
      GCD* getGCD(void);
      /** Obtención del método para el cálculo del máximo común divisor
       * extendido por defecto */
      GCDExt * getGCDExt(void);
      /** Obtención del método para el cálculo del mínimo común multiplo por
       * defecto*/
      LCM* getLCM(void);
      /** Obtención del método de potenciación modular por defecto */
      PotModular* getPotModular(void);
      /** Obtención del algoritmo para la reducción de Barrett por defecto */
      RedBarrett* getBarrettReduction(void);
      /** Obtención del algoritmo para la reducción de Montogomery por
       * defecto */
      RedMontgomery* getMontgomeryReduction(void);
      /** Obtención del algoritmo para la reducción de números de la forma
       * \f$ b^t-c\f$ con \f$c\f$ un número de \f$l\f$ dígitos en base 
       * \f$b\f$ y \f$l < t\f$ por defecto*/
      RedModularALaMersenne* getModularReductionALaMersenne(void);
      /** Obtención del algoritmo para al cálculo del símbolo de Kronecker
       * por defecto*/
      SimboloKronecker* getKroneckerSymbol(void);
      /** Obtención del algoritmo para al cálculo del símbolo de Kronecker
       * por defecto*/
      SimboloJacobi* getJacobiSymbol(void);
      /** Obtención del algoritmo para al cálculo del símbolo de Kronecker
       * por defecto*/
      SimboloLegendre* getLegendreSymbol(void);
      
      /** Obtención del algoritmo para el cálculo del Teorema del Resto
       * Chino por defecto*/
      CRT* getCRT(void);
      
      /** Obtención del método de factorización por defecto */
      Factoriza* getFactoriza(void);
 


      /* FUNCIONES SOBRE REALES */
      /** Obtención del método del calculo de exponencial ( e^x ) por defecto */
      Exponencial* getExponencial(void);
      /** Obtención del método del calculo del log nep por defecto */
      Ln* getLn(void);
       /** Obtención del método de calculo del coseno por defecto */
      Coseno* getCoseno(void);
       /** Obtención del método de calculo del seno por defecto */
      Seno* getSeno(void);
      /** Obtención del método de calculo del arcotangente por defecto */
      ArcoTangente* getArcotangente(void);
      /** Obtención del método de calculo de \f$ \pi \f$ por defecto */
      Pi* getPi(void);
    
      
      ~Funciones();

    private:


      auto_ptr< TestPrimoProb > testPrimoProbPTR;
      auto_ptr< TestPrimoMersenne > testPrimoMersennePTR;
      auto_ptr< RandomRapido > randomRapidoPTR;
      auto_ptr< RandomSeguro > randomSeguroPTR;
      auto_ptr< PruebaRandom > pruebaRandomPTR;
      auto_ptr< GenPrimos > genPrimosPTR;
      auto_ptr< Hash > hashPTR;
      auto_ptr< Potencia > potenciaPTR;
      auto_ptr< PotenciaR > potenciaRPTR;
      auto_ptr< GCD > gcdPTR;
      auto_ptr< GCDExt > gcdextPTR;
      auto_ptr< LCM > lcmPTR;
      auto_ptr< PotModular > potModularPTR;
      auto_ptr< RedBarrett > redBarrettPTR;
      auto_ptr< RedMontgomery > redMontgomeryPTR;
      auto_ptr< RedModularALaMersenne > redModularALaMersennePTR;
      auto_ptr< SimboloKronecker > simboloKroneckerPTR;
      auto_ptr< SimboloJacobi > simboloJacobiPTR;
      auto_ptr< SimboloLegendre > simboloLegendrePTR;
      auto_ptr< CRT > crtPTR;
      auto_ptr< Factoriza > factorizaPTR;
      auto_ptr< Exponencial > exponencialPTR;
      auto_ptr< Ln > lnPTR;
      auto_ptr< Coseno > cosenoPTR;
      auto_ptr< Seno > senoPTR;
      auto_ptr< ArcoTangente > arcotangentePTR;
      auto_ptr< Pi > piPTR;
  };


}
      
#endif
    
