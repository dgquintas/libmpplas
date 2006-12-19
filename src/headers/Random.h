/*
 * $Id$
 */

#ifndef __RANDOM_H
#define __RANDOM_H

#include "MiVec.h"
#include "Z.h"
#include "constantes.h"
#include <cassert>

namespace numth{
 
  /** Interfaz para la generaci�n de n�meros aleatorios.
   *
   * Clase base para m�todos de generaci�n de n�meros aleatorios.
   * 
   */
  class Random
  {
    public:
      /** Obtenci�n de un n�mero determinado de bits aleatorios.
       *
       * @param n N�mero de bits aleatorios a obtener.
       *
       * @return Un entero formado a partir de la concatenaci�n de los
       * @a n bits aleatorios.
       */
      virtual Z leerBits(size_t n) = 0;
      /** Obtenci�n de una Cifra aleatoria.
       *
       * @return Una Cifra aleatoria.
       *
       * @note Esto es solo una atajo de para cuando se quieren
       * generar un n�mero aleatorio de \f$BASE\f$ bits.
       */
      virtual Cifra leerCifra(void);
 
      /** Get a random CifraSigno
       *
       * @return A random CifraSigno.
       *
       */
      virtual CifraSigno leerCifraSigno(void);

      /** Obtenci�n de un n�mero aleatorio menor que otro dado.
       *
       * @param cota El entero representando la cota a no superar.
       *
       * @return Un entero aleatorio menor que @a cota.
       */
      virtual Z leerEntero(Z cota);

      virtual ~Random() {}
  };
 
  /** Interfaz para la generaci�n r�pida de n�meros aleatorios.
   *
   * Clase base para m�todos de generaci�n r�pida de n�meros aleatorios.
   * 
   */
  class RandomRapido : public Random
  {
    public:
      /** Establecer la semilla para los generadores.
       *
       * Establece la semilla que los generadores r�pidos de n�meros
       * aleatorios necesitan como estado inicial. De no
       * proporcionarse una, se tomar�a autom�ticamente del Semillero.
       *
       * @param semilla Entero representando la semilla.
       *
       */
      virtual void ponerSemilla(const Z& semilla) = 0;
  };
   
  /** Interfaz para la generaci�n de n�meros aleatorios
   * criptogr�ficamente seguros.
   *
   * Clase base para m�todos de generaci�n de n�meros aleatorios
   * criptogr�ficamente seguros.
   * 
   */
  class RandomSeguro : public Random
  {
    public:
      /** Establecer la calidad de los n�meros criptogr�ficamente
       * seguros generados.
       *
       * Los m�todos de generaci�n de n�meros criptogr�ficamente
       * seguros se basan en todos los casos considerados en el
       * problema FACTORING, teniendo que generar factores primos de
       * un determinado tama�o. Este m�todo permite especificar dicho
       * tama�o: a mayor tama�o, mayor seguridad  pero tambi�n m�s
       * lentitud a la hora de instanciar las clases generadoras.
       * Si no se especifica, se utiliza un valor de 256 bits por
       * omisi�n.
       *
       * @param n Tama�o de los primos a generar internamente por los algoritmos.
       *
       */
      virtual void ponerCalidad(size_t n) = 0;
  };

  /** Interfaz para los algoritmos que implementen tests de
   * aleatoreidad.
   *
   * Clase base para los algoritmos que implementen tests de
   * aleatoreidad.
   */
  class PruebaRandom
  {
    public:
      /** Determinar si un generador de n�meros pseudoaleatorios supera el tests.
       *
       * @param generadorRandom El generador a probar.
       *
       * @return true si el generador @a generadorRandom supera el
       * test.\n
       *         false si no.
       */
      virtual bool pruebaRandom(Random& generadorRandom) = 0;

      virtual ~PruebaRandom() {}
  };
  
  /* IMPLEMENTACIONES */
  /** Algoritmo NumThRC4 (RC4) para la generaci�n r�pida de n�meros
   * pseudoaleatorios.
   *
   * Descrito en Applied Cryptography, p�gina 397, punto 17.1\n
   * 
   * @note Es el m�todo que la librer�a utiliza por omisi�n.
   */
  class NumThRC4Gen : public RandomRapido
  {
    public:
      NumThRC4Gen();

      virtual ~NumThRC4Gen(){}
      
      virtual Z leerBits(size_t n);
      virtual void ponerSemilla(const Z& semilla);
      
    private:
      uint8_t s_[256];
      uint8_t k_[256];
      size_t i_;
      size_t j_;
      Z semilla_;
      void inicializar_(void);
  };
  typedef NumThRC4Gen RandomRapidoDFL;
  typedef NumThRC4Gen RandomDFL;

  /** Algoritmo para la generaci�n r�pida de n�meros
   * pseudoaleatorios mediante congruencias lineales.
   *
   * Descrito en Applied Cryptography, p�gina 369, punto 16.1\n
   * The Art of Computer Programming Vol. 2, p�g. 9, punto 3.2.1
   * 
   */
  class congruentGen : public RandomRapido
  {
    public:
      congruentGen(void);

      virtual ~congruentGen(){}

      virtual Z leerBits(size_t n);
      virtual void ponerSemilla(const Z& semilla);

      //FIXME: dar la opcion de modificar la "a", "b", "m" del metodo?
      
    private:
      unsigned long a_;
      unsigned long b_;
      unsigned long m_;

      unsigned long Xi_;
  };

  /** Algoritmo Blum-Blum-Shub para la generaci�n de n�meros
   * pseudoaleatorios criptogr�ficamente seguros.
   *
   * Descrito en Handbook of Applied Cryptography, p�gina 186, algoritmo 5.40\n
   * Applied Cryptography, p�gina 417, punto 17.9\n
   * Cryptographic Secure Pseudo-Random Bits Generation: The Blum-
   * Blum-Shub Generator, Pascal Junod, 1999
   *
   * @note Es el m�todo que la librer�a utiliza por omisi�n.
   */
  class BBSGen : public RandomSeguro
  {
    public:
      BBSGen(void);
      
      virtual Z leerBits(size_t n);
      virtual void ponerCalidad(size_t n);

      virtual ~BBSGen(){}

    private:
      size_t calidad_;
      Z n_; // producto de los primos p y q de la inicializacion
      Z Xi_;

      void inicializar_(void);
  };
  typedef BBSGen RandomSeguroDFL;
  




  /** Implementaci�n del conjunto de tests FIPS 140-1.
   *
   * Descrito en Handbook of Applied Cryptography, p�gina 183, algoritmo 5.32\n
   *
   * @note Es el m�todo que la librer�a utiliza por omisi�n.
   */
  class FIPS_140_1 : public PruebaRandom
  {
    public:
      virtual bool pruebaRandom(Random& generadorRandom);
      virtual ~FIPS_140_1(){}
      
    protected:
      size_t monobitTest_(Z muestraLocal);
      float pokerTest_(Z muestraLocal);
      size_t runTests_(Z muestraLocal, size_t* bloques, size_t* huecos);

  };
  typedef FIPS_140_1 PruebaRandomDFL;
  
}
#endif

