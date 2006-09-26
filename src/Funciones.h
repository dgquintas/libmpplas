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
   * documentaci�n de teor�a (dentro del cap�tulo "Implementaci�n de
   * algoritmos b�sicos") en lo relativo al repositorio de
   * funciones. 
   */
  class Funciones
  {
    public:

      /** Asignar tests de composici�n por defecto */
      void ponerTestPrimoProb(TestPrimoProb* ptr);
      /** Asignar test de primalidad para primos de Mersenne por
       * defecto */
      void ponerTestPrimoMersenne(TestPrimoMersenne* ptr);
//      void ponerRandom(Random* ptr);
      /** Asignar generador de n�meros aleatorios por defecto */
      void ponerRandomRapido(RandomRapido* ptr);
      /** Asignar generador de n�meros aleatorios seguros por defecto */
      void ponerRandomSeguro(RandomSeguro* ptr);
      /** Asignar tests de aleatoriedad por defecto*/
      void ponerPruebaRandom(PruebaRandom* ptr);
      /** Asignar generador de primos por defecto */
      void ponerGenPrimos(GenPrimos* ptr);
      /** Asignar funci�n hash por defecto */
      void ponerHash(Hash* ptr);
      /** Asignar m�todo de potenciaci�n por defecto*/
      void ponerPotencia(Potencia* ptr);
      /** Asignar m�todo de potenciaci�n de reales por defecto*/
      void ponerPotenciaR(PotenciaR* ptr);

      /** Asignar m�todo para el c�lculo del m�ximo com�n divisor por
       * defecto*/
      void ponerGCD(GCD* ptr);
      /** Asignar m�todo para el c�lculo del m�ximo com�n divisor
       * extendido por defecto */
      void ponerGCDExt(GCDExt* ptr);
      /** Asignar m�todo para el c�lculo del m�nimo com�n multiplo por
       * defecto*/
      void ponerLCM(LCM* ptr);
      /** Asignar m�todo de potenciaci�n modular por defecto */
      void ponerPotModular(PotModular* ptr);
      /** Asignar algoritmo para la reducci�n de Barrett por defecto */
      void ponerRedBarrett(RedBarrett* ptr);
      /** Asignar algoritmo para la reducci�n de Montogomery por
       * defecto */
      void ponerRedMontgomery(RedMontgomery* ptr);
      /** Asignar algoritmo para la reducci�n de n�meros de la forma
       * \f$ b^t-c\f$ con \f$c\f$ un n�mero de \f$l\f$ d�gitos en base 
       * \f$b\f$ y \f$l < t\f$ por defecto*/
      void ponerRedModularALaMersenne(RedModularALaMersenne* ptr);
      /** Asignar algoritmo para al c�lculo del s�mbolo de Kronecker
       * por defecto*/
      void ponerSimboloKronecker(SimboloKronecker* ptr);
      /** Asignar algoritmo para el c�lculo del s�mbolo de Jacobi por
       * defecto */
      void ponerSimboloJacobi(SimboloJacobi* ptr);
      /** Asignar algoritmo para el c�lculo del s�mbolo de Legendre
       * por defecto*/
      void ponerSimboloLegendre(SimboloLegendre* ptr);
      /** Asignar algoritmo para el c�lculo del Teorema del Resto
       * Chino por defecto*/
      void ponerCRT(CRT* ptr); 
      /** Asignar m�todo de factorizaci�n por defecto */
      void ponerFactoriza(Factoriza* ptr);
       /** Asignar m�todo de calculo de exponencial por defecto */
      void ponerExponencial(Exponencial* ptr);
      /** Asignar m�todo de calculo de log nep por defecto */
      void ponerLn(Ln* ptr);
      /** Asignar m�todo de calculo del coseno por defecto */
      void ponerCoseno(Coseno* ptr);
      /** Asignar m�todo de calculo del seno por defecto */
      void ponerSeno(Seno* ptr);
      /** Asignar m�todo de calculo del arcotangente por defecto */
      void ponerArcoTangente(ArcoTangente* ptr);
      /** Asignar m�todo de calculo de \f$ \pi \f$ por defecto */
      void ponerPi(Pi* ptr);
   
      /** Obtenci�n del tests de composici�n por defecto */
      TestPrimoProb* testPrimoProb(void);
      /** Obtenci�n del test de primalidad para primos de Mersenne por
       * defecto */
      TestPrimoMersenne* testPrimoMersenne(void);
//      Random* random(void);
      /** Obtenci�n del generador de n�meros aleatorios por defecto */
      RandomRapido* randomRapido(void);
      /** Obtenci�n del generador de n�meros aleatorios seguros por defecto */
      RandomSeguro* randomSeguro(void);
      /** Obtenci�n del tests de aleatoriedad por defecto*/
      PruebaRandom* pruebaRandom(void);
      /** Obtenci�n del generador de primos por defecto */
      GenPrimos* genPrimos(void);
      /** Obtenci�n del funci�n hash por defecto */
      Hash* hash(void);
      /** Obtenci�n del m�todo de potenciaci�n por defecto*/
      Potencia* potencia(void);
      /** Obtenci�n del m�todo de potenciaci�n de reales por defecto*/
      PotenciaR* potenciaR(void);
      /** Obtenci�n del m�todo para el c�lculo del m�ximo com�n divisor por
       * defecto*/
      GCD* gcd(void);
      /** Obtenci�n del m�todo para el c�lculo del m�ximo com�n divisor
       * extendido por defecto */
      GCDExt * gcdext(void);
      /** Obtenci�n del m�todo para el c�lculo del m�nimo com�n multiplo por
       * defecto*/
      LCM* lcm(void);
      /** Obtenci�n del m�todo de potenciaci�n modular por defecto */
      PotModular* potModular(void);
      /** Obtenci�n del algoritmo para la reducci�n de Barrett por defecto */
      RedBarrett* redBarrett(void);
      /** Obtenci�n del algoritmo para la reducci�n de Montogomery por
       * defecto */
      RedMontgomery* redMontgomery(void);
      /** Obtenci�n del algoritmo para la reducci�n de n�meros de la forma
       * \f$ b^t-c\f$ con \f$c\f$ un n�mero de \f$l\f$ d�gitos en base 
       * \f$b\f$ y \f$l < t\f$ por defecto*/
      RedModularALaMersenne* redModularALaMersenne(void);
      /** Obtenci�n del algoritmo para al c�lculo del s�mbolo de Kronecker
       * por defecto*/
      SimboloKronecker* simboloKronecker(void);
      /** Obtenci�n del algoritmo para al c�lculo del s�mbolo de Kronecker
       * por defecto*/
      SimboloJacobi* simboloJacobi(void);
      /** Obtenci�n del algoritmo para al c�lculo del s�mbolo de Kronecker
       * por defecto*/
      SimboloLegendre* simboloLegendre(void);
      
      /** Obtenci�n del algoritmo para el c�lculo del Teorema del Resto
       * Chino por defecto*/
      CRT* crt(void);
      
      /** Obtenci�n del m�todo de factorizaci�n por defecto */
      Factoriza* factoriza(void);
 


      /* FUNCIONES SOBRE REALES */
      /** Obtenci�n del m�todo del calculo de exponencial ( e^x ) por defecto */
      Exponencial* exponencial(void);
      /** Obtenci�n del m�todo del calculo del log nep por defecto */
      Ln* ln(void);
       /** Obtenci�n del m�todo de calculo del coseno por defecto */
      Coseno* coseno(void);
       /** Obtenci�n del m�todo de calculo del seno por defecto */
      Seno* seno(void);
      /** Obtenci�n del m�todo de calculo del arcotangente por defecto */
      ArcoTangente* arcotangente(void);
      /** Obtenci�n del m�todo de calculo de \f$ \pi \f$ por defecto */
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
    
