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
   * documentaci�n de teor�a (dentro del cap�tulo "Implementaci�n de
   * algoritmos b�sicos") en lo relativo al repositorio de
   * funciones. 
   */
  class Funciones
  {
    public:

      /** Asignar tests de composici�n por defecto */
      void setTestPrimoProb(TestPrimoProb* ptr);
      /** Asignar test de primalidad para primos de Mersenne por
       * defecto */
      void setTestPrimoMersenne(TestPrimoMersenne* ptr);
      /** Asignar generador de n�meros aleatorios por defecto */
      void setRandomRapido(RandomRapido* ptr);
      /** Asignar generador de n�meros aleatorios seguros por defecto */
      void setRandomSeguro(RandomSeguro* ptr);
      /** Asignar tests de aleatoriedad por defecto*/
      void setPruebaRandom(PruebaRandom* ptr);
      /** Asignar generador de primos por defecto */
      void setGenPrimos(GenPrimos* ptr);
      /** Asignar funci�n hash por defecto */
      void setHash(Hash* ptr);
      /** Asignar m�todo de potenciaci�n por defecto*/
      void setPotencia(Potencia* ptr);
      /** Asignar m�todo de potenciaci�n de reales por defecto*/
      void setPotenciaR(PotenciaR* ptr);

      /** Asignar m�todo para el c�lculo del m�ximo com�n divisor por
       * defecto*/
      void setGCD(GCD* ptr);
      /** Asignar m�todo para el c�lculo del m�ximo com�n divisor
       * extendido por defecto */
      void setGCDExt(GCDExt* ptr);
      /** Asignar m�todo para el c�lculo del m�nimo com�n multiplo por
       * defecto*/
      void setLCM(LCM* ptr);
      /** Asignar m�todo de potenciaci�n modular por defecto */
      void setPotModular(PotModular* ptr);
      /** Asignar algoritmo para la reducci�n de Barrett por defecto */
      void setBarrettReduction(RedBarrett* ptr);
      /** Asignar algoritmo para la reducci�n de Montogomery por
       * defecto */
      void setMontgomeryReduction(RedMontgomery* ptr);
      /** Asignar algoritmo para la reducci�n de n�meros de la forma
       * \f$ b^t-c\f$ con \f$c\f$ un n�mero de \f$l\f$ d�gitos en base 
       * \f$b\f$ y \f$l < t\f$ por defecto*/
      void setModularReductionALaMersenne(RedModularALaMersenne* ptr);
      /** Asignar algoritmo para al c�lculo del s�mbolo de Kronecker
       * por defecto*/
      void setKroneckerSymbol(SimboloKronecker* ptr);
      /** Asignar algoritmo para el c�lculo del s�mbolo de Jacobi por
       * defecto */
      void setJacobiSymbol(SimboloJacobi* ptr);
      /** Asignar algoritmo para el c�lculo del s�mbolo de Legendre
       * por defecto*/
      void setLegendreSymbol(SimboloLegendre* ptr);
      /** Asignar algoritmo para el c�lculo del Teorema del Resto
       * Chino por defecto*/
      void setCRT(CRT* ptr); 
      /** Asignar m�todo de factorizaci�n por defecto */
      void setFactoriza(Factoriza* ptr);
       /** Asignar m�todo de calculo de exponencial por defecto */
      void setExponencial(Exponencial* ptr);
      /** Asignar m�todo de calculo de log nep por defecto */
      void setLn(Ln* ptr);
      /** Asignar m�todo de calculo del coseno por defecto */
      void setCoseno(Coseno* ptr);
      /** Asignar m�todo de calculo del seno por defecto */
      void setSeno(Seno* ptr);
      /** Asignar m�todo de calculo del arcotangente por defecto */
      void setArcoTangente(ArcoTangente* ptr);
      /** Asignar m�todo de calculo de \f$ \pi \f$ por defecto */
      void setPi(Pi* ptr);
   






      /** Obtenci�n del tests de composici�n por defecto */
      TestPrimoProb* getTestPrimoProb(void);
      /** Obtenci�n del test de primalidad para primos de Mersenne por
       * defecto */
      TestPrimoMersenne* getTestPrimoMersenne(void);
      /** Obtenci�n del generador de n�meros aleatorios por defecto */
      RandomRapido* getRandomRapido(void);
      /** Obtenci�n del generador de n�meros aleatorios seguros por defecto */
      RandomSeguro* getRandomSeguro(void);
      /** Obtenci�n del tests de aleatoriedad por defecto*/
      PruebaRandom* getPruebaRandom(void);
      /** Obtenci�n del generador de primos por defecto */
      GenPrimos* getGenPrimos(void);
      /** Obtenci�n del funci�n hash por defecto */
      Hash* getHash(void);
      /** Obtenci�n del m�todo de potenciaci�n por defecto*/
      Potencia* getPotencia(void);
      /** Obtenci�n del m�todo de potenciaci�n de reales por defecto*/
      PotenciaR* getPotenciaR(void);
      /** Obtenci�n del m�todo para el c�lculo del m�ximo com�n divisor por
       * defecto*/
      GCD* getGCD(void);
      /** Obtenci�n del m�todo para el c�lculo del m�ximo com�n divisor
       * extendido por defecto */
      GCDExt * getGCDExt(void);
      /** Obtenci�n del m�todo para el c�lculo del m�nimo com�n multiplo por
       * defecto*/
      LCM* getLCM(void);
      /** Obtenci�n del m�todo de potenciaci�n modular por defecto */
      PotModular* getPotModular(void);
      /** Obtenci�n del algoritmo para la reducci�n de Barrett por defecto */
      RedBarrett* getBarrettReduction(void);
      /** Obtenci�n del algoritmo para la reducci�n de Montogomery por
       * defecto */
      RedMontgomery* getMontgomeryReduction(void);
      /** Obtenci�n del algoritmo para la reducci�n de n�meros de la forma
       * \f$ b^t-c\f$ con \f$c\f$ un n�mero de \f$l\f$ d�gitos en base 
       * \f$b\f$ y \f$l < t\f$ por defecto*/
      RedModularALaMersenne* getModularReductionALaMersenne(void);
      /** Obtenci�n del algoritmo para al c�lculo del s�mbolo de Kronecker
       * por defecto*/
      SimboloKronecker* getKroneckerSymbol(void);
      /** Obtenci�n del algoritmo para al c�lculo del s�mbolo de Kronecker
       * por defecto*/
      SimboloJacobi* getJacobiSymbol(void);
      /** Obtenci�n del algoritmo para al c�lculo del s�mbolo de Kronecker
       * por defecto*/
      SimboloLegendre* getLegendreSymbol(void);
      
      /** Obtenci�n del algoritmo para el c�lculo del Teorema del Resto
       * Chino por defecto*/
      CRT* getCRT(void);
      
      /** Obtenci�n del m�todo de factorizaci�n por defecto */
      Factoriza* getFactoriza(void);
 


      /* FUNCIONES SOBRE REALES */
      /** Obtenci�n del m�todo del calculo de exponencial ( e^x ) por defecto */
      Exponencial* getExponencial(void);
      /** Obtenci�n del m�todo del calculo del log nep por defecto */
      Ln* getLn(void);
       /** Obtenci�n del m�todo de calculo del coseno por defecto */
      Coseno* getCoseno(void);
       /** Obtenci�n del m�todo de calculo del seno por defecto */
      Seno* getSeno(void);
      /** Obtenci�n del m�todo de calculo del arcotangente por defecto */
      ArcoTangente* getArcotangente(void);
      /** Obtenci�n del m�todo de calculo de \f$ \pi \f$ por defecto */
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
    
