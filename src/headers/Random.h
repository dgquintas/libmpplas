/*
 * $Id$
 */

#ifndef __RANDOM_H
#define __RANDOM_H

#include "MiVec.h"
#include "Z.h"
#include "Constants.h"
#include "AbstractMethod.h"
#include <cassert>

namespace mpplas{
 
  class NumThRC4Gen ;
  class BBSGen;
  class FIPS_140_1 ;

  /** (Pseudo)Random number generator (PRNG).
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
      virtual Z getInteger(int n) = 0;
      /** Get a random Digit
       *
       * @return A random Digit.
       *
       */
      Digit getDigit(void);
 
      /** Get a random SignedDigit
       *
       * @return A random SignedDigit.
       *
       */
      SignedDigit getSignedDigit(void);

      /** Get a bounded random integer.
       *
       * @param bound The upper bound integer.
       *
       * @return A random integer less than @a bound.
       */
      Z getIntegerBounded(const Z& bound);

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
  class RandomFast : public Random
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
      virtual void setSeed(const Z& seed) = 0;

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
  class RandomSecure : public Random
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
      virtual void setQuality(int n) = 0;

      /** Default implementation */
      typedef BBSGen DFL;
  };

  /** Randomness test.
   *
   * Base class for methods implementing tests of randomness.
   *
   */
  class RandomnessTest : public AbstractMethod
  {
    public:
      /** Test if a given (pseudo)random number generator (PRNG) passes the test.
       *
       * @param prng The PRNG to test.
       *
       * @return @a true if the generator @a prng passes the test. @a false otherwise. */
      virtual bool testRandom(Random& prng) = 0;

      virtual ~RandomnessTest() {}

      /** Default implementation */
      typedef FIPS_140_1 DFL;
  };
  
  /* CONCRETE METHODS */
  /** NumThRC4 (RC4) algorithm for the fast (pseudo)random number generation.
   *
   * Described in Applied Cryptography, page 397, section 17.1
   * 
   * @note This is the library's default method for RandomFast 
   */
  class NumThRC4Gen : public RandomFast
  {
    public:
      NumThRC4Gen();

      virtual ~NumThRC4Gen(){}
      
      virtual Z getInteger(int n);
      virtual void setSeed(const Z& semilla);
      
    private:
      uint8_t _s[256];
      uint8_t _k[256];
      int _i;
      int _j;
      Z _seed;
      void _initialize(void);
  };

  /** Fast linear congruences (pseudo)random number generator.
   *
   * Described in 
   * <ul>
   * <li>Applied Cryptography, page 369, section 16.1</li>
   * <li>The Art of Computer Programming Vol. 2, page 9, section 3.2.1</li>
   * </ul>  */
  class CongruentGen : public RandomFast
  {
    public:
      CongruentGen(void);

      virtual ~CongruentGen(){}

      virtual Z getInteger(int n);
      virtual void setSeed(const Z& seed);

      //FIXME: dar la opcion de modificar la "a", "b", "m" del metodo?
      
    private:
      unsigned long _a;
      unsigned long _b;
      unsigned long _m;

      unsigned long _Xi;
  };

  /** Blum-Blum-Shub algorithm for the generation of 
   * cryptographic secure (pseudo)random numbers.
   *
   * Described in 
   * <ul>
   * <li>Handbook of Applied Cryptography, page 186, algorithm 5.40</li>
   * <li>Applied Cryptography, page 417, section 17.9</li>
   * <li>Cryptographic Secure Pseudo-Random Bits Generation: 
   * The Blum-Blum-Shub Generator, Pascal Junod, 1999</li>
   * </ul>
   *
   * @note This is the library's default method for RandomFast  */
  class BBSGen : public RandomSecure
  {
    public:
      BBSGen(void);
      
      virtual Z getInteger(int n);
      virtual void setQuality(int n);

      virtual ~BBSGen(){}

    private:
      int _quality;
      Z _n; // producto de los primos p y q de la inicializacion
      Z _Xi;

      void _initialize(void);
  };
  




  /** FIPS 140-1 randomness tests implementation.
   *
   * Described in Handbook of Applied Cryptography, page 183, algorithm 5.32
   *
   * @note This is the library's default method for RandomFast 
   */
  class FIPS_140_1 : public RandomnessTest
  {
    public:
      virtual bool testRandom(Random& generadorRandom);
      virtual ~FIPS_140_1(){}
      
    protected:
      int monobitTest_(Z muestraLocal);
      float pokerTest_(Z muestraLocal);
      int runTests_(Z muestraLocal, int* bloques, int* huecos);

  };
  
}
#endif

