/* 
 * $Id$
 */

#ifndef __PRIMOS_H
#define __PRIMOS_H

#include "Z.h"
#include "Random.h"
#include "AbstractMethod.h"

namespace mpplas{

  class RabinMiller;
  class TMersenneLucasLehmer;
  
  /** Interfaz para tests probabilísticos de primalidad (tests de
   * composición).
   *
   * Clase base para algoritmos que implementen tests de composición.
   * 
   */
  class TestPrimoProb : public AbstractMethod
  {
    public:
      /** Determinación de primalidad.
       *
       * @param entero Entero a comprobar.
       * @param testigo Puntero a entero que de ser distinto de NULL,
       * contendrá un testigo de la composición del entero a
       * comprobar (base que demuestra la composición, véase teoría). 
       * Si el entero a comprobar resulta ser primo, será 0. 
       *
       * @return true si @a entero es primo.\n
       *         false si es compuesto.
       */
      virtual bool esPrimo(const Z& entero, Z* testigo=NULL) = 0;
      /** Establecer el número de iteraciones.
       *
       * Forzar el número de iteraciones del método probabilístico en
       * cuestión. 
       *
       * @param iteraciones El número de iteraciones que el tests de
       * composición habrá de considerar.
       *
       * @note Este método no debería ser utilizado más que cuando
       * realmente se quiera forzar un comportamiento determinado, ya
       * que el número de iteraciones óptimo se determina
       * automáticamente. Véase teoría.
       */
      virtual void ponerIteraciones(size_t iteraciones) = 0;

      virtual ~TestPrimoProb(){}


      typedef RabinMiller DFL;
  };
 
  /** Interfaz para tests de primalidad para primos de Mersenne.
   *
   * Clase base para algoritmos que implementen tests de primalidad
   * para primos de Mersenne (números de la forma \f$2^{p} -1\f$).
   * 
   */
  class TestPrimoMersenne : public AbstractMethod
  {
    public:
      /** Determinación de primalidad para primos de Mersenne.
       *
       * Se comprueba si el número \f$2^{p}-1\f$ es primo.
       * 
       * @param p Exponente (ha de ser primo) a utilizar.
       *
       * @return true si @a entero es primo.\n
       *         false si es compuesto.
       */
      virtual bool esPrimo(const CifraSigno p) = 0;

      virtual ~TestPrimoMersenne(){}

      typedef TMersenneLucasLehmer DFL;
  };
 
  /** Interfaz la generación de primos.
   *
   * Clase base para algoritmos que implementen métodos de generación
   * de primos.
   * 
   */
  class GenPrimos : public AbstractMethod
  {
    public:

      GenPrimos();

      /** Generación de primo.
       *
       * Se genera un primo de aproximadamente @a bits bits.
       * 
       * @param bits Bits del primo a generar.
       * @return El primo generado.
       */
      virtual Z leerPrimoProb(size_t bits);

      /** Generación del primer primos posterior a uno dado.
       *
       * Se genera el primer primo mayor que el entero @a comienzo.
       * 
       * @param comienzo Entero a partir del cual comenzar la búsqueda
       * del primo.
       * @return El primer primo mayor que @a comienzo.
       */
      virtual Z siguientePrimoProb(const Z& comienzo);
 
      /** Generación de primo fuerte.
       *
       * Se genera un primo fuerte de aproximadamente @a bits bits.
       * 
       * @param bits Bits del primo a generar.
       * @return El primo fuerte generado.
       */
      virtual Z leerPrimoFuerte(size_t bits);

      virtual ~GenPrimos(){}

      virtual void setRandomSeed(const Z& seed); 


      typedef GenPrimos DFL;

    private:
      RandomRapido* _rnd;
  };


  /* IMPLEMENTACIONES */
  /** Test de composición de Rabin-Miller.
   *
   * Descrito en Handbook of Applied Cryptography, algoritmo 4.24\n
   * Applied Cryptography, página 259\n
   * A Course ini Computational Algebraic Number Theory, algoritmo
   * 8.2.2\n
   * 
   * @note Es el método que la librería utiliza por omisión.
   */
  class RabinMiller : public TestPrimoProb
  {
    public:
      RabinMiller();
      
      virtual bool esPrimo(const Z& entero, Z* testigo=NULL);
      virtual void ponerIteraciones(size_t iteraciones);

      virtual ~RabinMiller(){}
      
    private:
      size_t iteraciones_;
  };
  
   /** Test de primalidad para primos de Mersenne de Lucas-Lehmer.
   *
   * Descrito en Handbook of Applied Cryptography, algoritmo 4.37
   * 
   * @note Es el método que la librería utiliza por omisión.
   */
  class TMersenneLucasLehmer : public TestPrimoMersenne
  {
    public:
      virtual bool esPrimo(const CifraSigno p) ;

      virtual ~TMersenneLucasLehmer(){}
  };


}
  
#endif
