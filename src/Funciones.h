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
      void ponerTestPrimoProb(TestPrimoProb* ptr);
      /** Asignar test de primalidad para primos de Mersenne por
       * defecto */
      void ponerTestPrimoMersenne(TestPrimoMersenne* ptr);
//      void ponerRandom(Random* ptr);
      /** Asignar generador de números aleatorios por defecto */
      void ponerRandomRapido(RandomRapido* ptr);
      /** Asignar generador de números aleatorios seguros por defecto */
      void ponerRandomSeguro(RandomSeguro* ptr);
      /** Asignar tests de aleatoriedad por defecto*/
      void ponerPruebaRandom(PruebaRandom* ptr);
      /** Asignar generador de primos por defecto */
      void ponerGenPrimos(GenPrimos* ptr);
      /** Asignar función hash por defecto */
      void ponerHash(Hash* ptr);
      /** Asignar método de potenciación por defecto*/
      void ponerPotencia(Potencia* ptr);
      /** Asignar método de potenciación de reales por defecto*/
      void ponerPotenciaR(PotenciaR* ptr);

      /** Asignar método para el cálculo del máximo común divisor por
       * defecto*/
      void ponerGCD(GCD* ptr);
      /** Asignar método para el cálculo del máximo común divisor
       * extendido por defecto */
      void ponerGCDExt(GCDExt* ptr);
      /** Asignar método para el cálculo del mínimo común multiplo por
       * defecto*/
      void ponerLCM(LCM* ptr);
      /** Asignar método de potenciación modular por defecto */
      void ponerPotModular(PotModular* ptr);
      /** Asignar algoritmo para la reducción de Barrett por defecto */
      void ponerRedBarrett(RedBarrett* ptr);
      /** Asignar algoritmo para la reducción de Montogomery por
       * defecto */
      void ponerRedMontgomery(RedMontgomery* ptr);
      /** Asignar algoritmo para la reducción de números de la forma
       * \f$ b^t-c\f$ con \f$c\f$ un número de \f$l\f$ dígitos en base 
       * \f$b\f$ y \f$l < t\f$ por defecto*/
      void ponerRedModularALaMersenne(RedModularALaMersenne* ptr);
      /** Asignar algoritmo para al cálculo del símbolo de Kronecker
       * por defecto*/
      void ponerSimboloKronecker(SimboloKronecker* ptr);
      /** Asignar algoritmo para el cálculo del símbolo de Jacobi por
       * defecto */
      void ponerSimboloJacobi(SimboloJacobi* ptr);
      /** Asignar algoritmo para el cálculo del símbolo de Legendre
       * por defecto*/
      void ponerSimboloLegendre(SimboloLegendre* ptr);
      /** Asignar algoritmo para el cálculo del Teorema del Resto
       * Chino por defecto*/
      void ponerCRT(CRT* ptr); 
      /** Asignar método de factorización por defecto */
      void ponerFactoriza(Factoriza* ptr);
       /** Asignar método de calculo de exponencial por defecto */
      void ponerExponencial(Exponencial* ptr);
      /** Asignar método de calculo de log nep por defecto */
      void ponerLn(Ln* ptr);
      /** Asignar método de calculo del coseno por defecto */
      void ponerCoseno(Coseno* ptr);
      /** Asignar método de calculo del seno por defecto */
      void ponerSeno(Seno* ptr);
      /** Asignar método de calculo del arcotangente por defecto */
      void ponerArcoTangente(ArcoTangente* ptr);
      /** Asignar método de calculo de \f$ \pi \f$ por defecto */
      void ponerPi(Pi* ptr);
   
      /** Obtención del tests de composición por defecto */
      TestPrimoProb* testPrimoProb(void);
      /** Obtención del test de primalidad para primos de Mersenne por
       * defecto */
      TestPrimoMersenne* testPrimoMersenne(void);
//      Random* random(void);
      /** Obtención del generador de números aleatorios por defecto */
      RandomRapido* randomRapido(void);
      /** Obtención del generador de números aleatorios seguros por defecto */
      RandomSeguro* randomSeguro(void);
      /** Obtención del tests de aleatoriedad por defecto*/
      PruebaRandom* pruebaRandom(void);
      /** Obtención del generador de primos por defecto */
      GenPrimos* genPrimos(void);
      /** Obtención del función hash por defecto */
      Hash* hash(void);
      /** Obtención del método de potenciación por defecto*/
      Potencia* potencia(void);
      /** Obtención del método de potenciación de reales por defecto*/
      PotenciaR* potenciaR(void);
      /** Obtención del método para el cálculo del máximo común divisor por
       * defecto*/
      GCD* gcd(void);
      /** Obtención del método para el cálculo del máximo común divisor
       * extendido por defecto */
      GCDExt * gcdext(void);
      /** Obtención del método para el cálculo del mínimo común multiplo por
       * defecto*/
      LCM* lcm(void);
      /** Obtención del método de potenciación modular por defecto */
      PotModular* potModular(void);
      /** Obtención del algoritmo para la reducción de Barrett por defecto */
      RedBarrett* redBarrett(void);
      /** Obtención del algoritmo para la reducción de Montogomery por
       * defecto */
      RedMontgomery* redMontgomery(void);
      /** Obtención del algoritmo para la reducción de números de la forma
       * \f$ b^t-c\f$ con \f$c\f$ un número de \f$l\f$ dígitos en base 
       * \f$b\f$ y \f$l < t\f$ por defecto*/
      RedModularALaMersenne* redModularALaMersenne(void);
      /** Obtención del algoritmo para al cálculo del símbolo de Kronecker
       * por defecto*/
      SimboloKronecker* simboloKronecker(void);
      /** Obtención del algoritmo para al cálculo del símbolo de Kronecker
       * por defecto*/
      SimboloJacobi* simboloJacobi(void);
      /** Obtención del algoritmo para al cálculo del símbolo de Kronecker
       * por defecto*/
      SimboloLegendre* simboloLegendre(void);
      
      /** Obtención del algoritmo para el cálculo del Teorema del Resto
       * Chino por defecto*/
      CRT* crt(void);
      
      /** Obtención del método de factorización por defecto */
      Factoriza* factoriza(void);
 


      /* FUNCIONES SOBRE REALES */
      /** Obtención del método del calculo de exponencial ( e^x ) por defecto */
      Exponencial* exponencial(void);
      /** Obtención del método del calculo del log nep por defecto */
      Ln* ln(void);
       /** Obtención del método de calculo del coseno por defecto */
      Coseno* coseno(void);
       /** Obtención del método de calculo del seno por defecto */
      Seno* seno(void);
      /** Obtención del método de calculo del arcotangente por defecto */
      ArcoTangente* arcotangente(void);
      /** Obtención del método de calculo de \f$ \pi \f$ por defecto */
      Pi* pi(void);
    
      
      ~Funciones();

    private:
      static TestPrimoProb* testPrimoProbPTR;
      static TestPrimoMersenne* testPrimoMersennePTR;
//      static Random* randomPTR;
      static RandomRapido* randomRapidoPTR;
      static RandomSeguro* randomSeguroPTR;
      static PruebaRandom* pruebaRandomPTR;
      static GenPrimos* genPrimosPTR;
      static Hash* hashPTR;
      static Potencia* potenciaPTR;
      static PotenciaR* potenciaRPTR;
      static GCD* gcdPTR;
      static GCDExt* gcdextPTR;
      static LCM* lcmPTR;
      static PotModular* potModularPTR;
      static RedBarrett* redBarrettPTR;
      static RedMontgomery* redMontgomeryPTR;
      static RedModularALaMersenne* redModularALaMersennePTR;
      static SimboloKronecker* simboloKroneckerPTR;
      static SimboloJacobi* simboloJacobiPTR;
      static SimboloLegendre* simboloLegendrePTR;
      static CRT* crtPTR;
      static Factoriza* factorizaPTR;
      static Exponencial* exponencialPTR;
      static Ln* lnPTR;
      static Coseno* cosenoPTR;
      static Seno* senoPTR;
      static ArcoTangente* arcotangentePTR;
      static Pi* piPTR;

      
  };


}
      
#endif
    
