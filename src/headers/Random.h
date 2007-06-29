/*
 * $Id$
 */

#ifndef __RANDOM_H
#define __RANDOM_H

#include "MiVec.h"
#include "Z.h"
#include "constants.h"
#include "AbstractMethod.h"
#include <cassert>

namespace mpplas{
 
  class NumThRC4Gen ;
  class BBSGen;
  class FIPS_140_1 ;

  /** (Pseudo)Random number generation interface 
   *
   * Base class for methods implementing (pseudo)random number generators.
   * 
   */
  class Random : public AbstractMethod
  {
    public:
      /** Get a random integer.
       *
       * @param n Random bits to consider.
       *
       * @return An integer made up of @a n random bits.
       */
      virtual Z leerBits(size_t n) = 0;
      /** Get a random Digit
       *
       * @return A random Digit.
       *
       */
      virtual Digit leerDigit(void);
 
      /** Get a random SignedDigit
       *
       * @return A random SignedDigit.
       *
       */
      virtual SignedDigit leerSignedDigit(void);

      /** Get a bounded random integer.
       *
       * @param bound The upper bound integer.
       *
       * @return A random integer less than @a bound.
       */
      virtual Z leerEntero(const Z& bound);

      virtual ~Random() {}

      /** Default implementation */
      typedef NumThRC4Gen DFL;
  };
 
  /** Fast random number generation.
   *
   * Base class for methods implementing fast (pseudo)random number
   * generators. 
   *
   * @note In this context, fast means the generated PRN is <b>not</b>
   * suitable for cryptographic use. It is only required that the
   * generated sequence passes some statistical tests (see
   * RandomnessTest).
   * 
   */
  class RandomRapido : public Random
  {
    public:
      /** Sets the generator's seed.
       *
       * Sets the seed that the fast random number generators 
       * need as their initial state. If none is provided, 
       * one would be automatically fetched from the Seedbank.
       *
       * @param seed Integer representing the seed.
       *
       */
      virtual void ponerSemilla(const Z& seed) = 0;

      /** Default implementation */
      typedef NumThRC4Gen DFL;
  };
   
  /** Cryptographically secure pseudorandom number generator
   * (CSPRNG).
   *
   * Base class for methods implementing cryptographically secure
   * pseudorandom number generators.
   *
   * @note By <em>secure</em> it is meant that not only the generated
   * sequence passes the statistical tests (see RandomnessTest), but
   * also that it is <em>hard</em> (in the cryptographic sense) to
   * derive any, past or future, value of the random sequence.
   * 
   */
  class RandomSeguro : public Random
  {
    public:
      /** Set the quality of the cryptographically secure random
       * numbers. 
       *
       * The methods for the generation of cryptographically secure
       * random numbers rely on the FACTORING problem. Therefore, they
       * generate prime numbers of a given bit-length. This method makes
       * it possible to set this bit-length: the greater the more
       * secure, but also slower generation.
       * If omitted, a value of \f$256$\f is considered.
       *
       * @param n Bit-length of the primes to use internally by the
       * CSPRNG process.
       *
       */
      virtual void ponerCalidad(size_t n) = 0;

      /** Default implementation */
      typedef BBSGen DFL;
  };

  /** Interfaz para los algoritmos que implementen tests de
   * aleatoreidad.
   *
   * Clase base para los algoritmos que implementen tests de
   * aleatoreidad.
   */
  class RandomnessTest : public AbstractMethod
  {
    public:
      /** Determinar si un generador de números pseudoaleatorios supera el tests.
       *
       * @param generadorRandom El generador a probar.
       *
       * @return true si el generador @a generadorRandom supera el
       * test.\n
       *         false si no.
       */
      virtual bool pruebaRandom(Random& generadorRandom) = 0;

      virtual ~RandomnessTest() {}


      typedef FIPS_140_1 DFL;
  };
  
  /* IMPLEMENTACIONES */
  /** Algoritmo NumThRC4 (RC4) para la generación rápida de números
   * pseudoaleatorios.
   *
   * Descrito en Applied Cryptography, página 397, punto 17.1\n
   * 
   * @note Es el método que la librería utiliza por omisión.
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

  /** Algoritmo para la generación rápida de números
   * pseudoaleatorios mediante congruencias lineales.
   *
   * Descrito en Applied Cryptography, página 369, punto 16.1\n
   * The Art of Computer Programming Vol. 2, pág. 9, punto 3.2.1
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

  /** Algoritmo Blum-Blum-Shub para la generación de números
   * pseudoaleatorios criptográficamente seguros.
   *
   * Descrito en Handbook of Applied Cryptography, página 186, algoritmo 5.40\n
   * Applied Cryptography, página 417, punto 17.9\n
   * Cryptographic Secure Pseudo-Random Bits Generation: The Blum-
   * Blum-Shub Generator, Pascal Junod, 1999
   *
   * @note Es el método que la librería utiliza por omisión.
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
  




  /** Implementación del conjunto de tests FIPS 140-1.
   *
   * Descrito en Handbook of Applied Cryptography, página 183, algoritmo 5.32\n
   *
   * @note Es el método que la librería utiliza por omisión.
   */
  class FIPS_140_1 : public RandomnessTest
  {
    public:
      virtual bool pruebaRandom(Random& generadorRandom);
      virtual ~FIPS_140_1(){}
      
    protected:
      size_t monobitTest_(Z muestraLocal);
      float pokerTest_(Z muestraLocal);
      size_t runTests_(Z muestraLocal, size_t* bloques, size_t* huecos);

  };
  
}
#endif

