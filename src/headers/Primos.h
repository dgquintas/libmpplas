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
  
  /** Interfaz para tests probabil�sticos de primalidad (tests de
   * composici�n).
   *
   * Clase base para algoritmos que implementen tests de composici�n.
   * 
   */
  class TestPrimoProb : public AbstractMethod
  {
    public:
      /** Determinaci�n de primalidad.
       *
       * @param entero Entero a comprobar.
       * @param testigo Puntero a entero que de ser distinto de NULL,
       * contendr� un testigo de la composici�n del entero a
       * comprobar (base que demuestra la composici�n, v�ase teor�a). 
       * Si el entero a comprobar resulta ser primo, ser� 0. 
       *
       * @return true si @a entero es primo.\n
       *         false si es compuesto.
       */
      virtual bool esPrimo(const Z& entero, Z* testigo=NULL) = 0;
      /** Establecer el n�mero de iteraciones.
       *
       * Forzar el n�mero de iteraciones del m�todo probabil�stico en
       * cuesti�n. 
       *
       * @param iteraciones El n�mero de iteraciones que el tests de
       * composici�n habr� de considerar.
       *
       * @note Este m�todo no deber�a ser utilizado m�s que cuando
       * realmente se quiera forzar un comportamiento determinado, ya
       * que el n�mero de iteraciones �ptimo se determina
       * autom�ticamente. V�ase teor�a.
       */
      virtual void ponerIteraciones(size_t iteraciones) = 0;

      virtual ~TestPrimoProb(){}


      typedef RabinMiller DFL;
  };
 
  /** Interfaz para tests de primalidad para primos de Mersenne.
   *
   * Clase base para algoritmos que implementen tests de primalidad
   * para primos de Mersenne (n�meros de la forma \f$2^{p} -1\f$).
   * 
   */
  class TestPrimoMersenne : public AbstractMethod
  {
    public:
      /** Determinaci�n de primalidad para primos de Mersenne.
       *
       * Se comprueba si el n�mero \f$2^{p}-1\f$ es primo.
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
 
  /** Interfaz la generaci�n de primos.
   *
   * Clase base para algoritmos que implementen m�todos de generaci�n
   * de primos.
   * 
   */
  class GenPrimos : public AbstractMethod
  {
    public:

      GenPrimos();

      /** Generaci�n de primo.
       *
       * Se genera un primo de aproximadamente @a bits bits.
       * 
       * @param bits Bits del primo a generar.
       * @return El primo generado.
       */
      virtual Z leerPrimoProb(size_t bits);

      /** Generaci�n del primer primos posterior a uno dado.
       *
       * Se genera el primer primo mayor que el entero @a comienzo.
       * 
       * @param comienzo Entero a partir del cual comenzar la b�squeda
       * del primo.
       * @return El primer primo mayor que @a comienzo.
       */
      virtual Z siguientePrimoProb(const Z& comienzo);
 
      /** Generaci�n de primo fuerte.
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
  /** Test de composici�n de Rabin-Miller.
   *
   * Descrito en Handbook of Applied Cryptography, algoritmo 4.24\n
   * Applied Cryptography, p�gina 259\n
   * A Course ini Computational Algebraic Number Theory, algoritmo
   * 8.2.2\n
   * 
   * @note Es el m�todo que la librer�a utiliza por omisi�n.
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
   * @note Es el m�todo que la librer�a utiliza por omisi�n.
   */
  class TMersenneLucasLehmer : public TestPrimoMersenne
  {
    public:
      virtual bool esPrimo(const CifraSigno p) ;

      virtual ~TMersenneLucasLehmer(){}
  };


}
  
#endif
