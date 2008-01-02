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
  
  /** Probabilistic primality testing.
   *
   * Base class for methods implementing composition tests.
   * 
   */
  class PrimeTest : public AbstractMethod {
    public:
      /** Primality test.
       *
       * @param integer integer to test for primality.
       * @param witness pointer to an integer that will contain a witness for the 
       *        @a integer composition. If @a integer is prime, it will be zero.
       *
       * @return true if @a integer is prime. false otherwise
       */
      virtual bool isPrime(const Z& integer, Z* witness=NULL) = 0;
      /** Number of iterations.
       *
       * Forzar el número de iteraciones del método probabilístico en
       * cuestión. 
       * Set the number of iterations for the probabilistic test.
       *
       * @param iterations number of iterations for the composition test to perform.
       *
       * @note This method should rarely be used. The optimal number
       * of iterations is determined automatically at runtime.
       */
      virtual void setIterations(int iterations) = 0;

      virtual ~PrimeTest(){}


      typedef RabinMiller DFL;
  };
 
  /** Primality tests for Mersenne primes.
   *
   *
   * Base class for methods implementing primality tests for Mersenne numbers
   * (number of the form \f$2^{p} -1\f$).
   */
  class MersennePrimeTest : public AbstractMethod {
    public:
      /** Mersenne numbers primality test.
       *
       * It is checked whether \f$2^{p}-1\f$ is prime.
       * 
       * @param p exponent to consider (must be prime itself).
       *
       * @return true if  \f$2^{p}-1\f$ is prime. false otherwise.
       */
      virtual bool isPrime(const SignedDigit p) = 0;

      virtual ~MersennePrimeTest(){}

      typedef TMersenneLucasLehmer DFL;
  };
 
  /** Prime number generator.
   *
   * Base class for methods implementing prime number generators.
   */
  class PrimeGen : public AbstractMethod {
    public:

      PrimeGen();

      /** Prime number generation.
       *
       * Generates a prime number of approximately @a bits bits.
       * 
       * @param bits bitlength of the generated prime.
       * @return the generated prime.
       */
      virtual Z getPrime(const int bits) const;

      /** Generation of the next prime after a given number.
       *
       * @param from integer from which to begin searching.
       * @return the first prime grater than @a from.
       */
      virtual Z getPrime(Z from) const;

      /** Strong prime generation.
       *
       * A strong prime of approximately @a bits bits is generated.
       * 
       * @param bits bitlength of the strong prime.
       * @return the strong prime generated.
       */
      virtual Z getPrimeStrong(const int bits) const ;

      virtual ~PrimeGen(){}

      virtual void setRandomSeed(const Z& seed) const; 

      typedef PrimeGen DFL;

    private:
      RandomFast* _rnd;
  };


  /* IMPLEMENTACIONES */
  /** Rabin-Miller composition test.
   *
   * Described in Handbook of Applied Cryptography, algorithm 4.24\n
   * Applied Cryptography, page 259\n
   * A Course ini Computational Algebraic Number Theory, algorithm
   * 8.2.2\n
   * 
   * @note This is the library's default method for prime testing.
   */
  class RabinMiller : public PrimeTest {
    public:
      RabinMiller();
      
      virtual bool isPrime(const Z& entero, Z* testigo=NULL);
      virtual void setIterations(int iteraciones);

      virtual ~RabinMiller(){}
      
    private:
      int iteraciones_;
  };
  
   /** Lucas-Lehmer primality test for Mersenne numbers.
   *
   * Described in Handbook of Applied Cryptography, algorithm 4.37
   * 
   * @note This is the library's default method for Mersenne number primality testing.
   */
  class TMersenneLucasLehmer : public MersennePrimeTest {
    public:
      virtual bool isPrime(const SignedDigit p) ;

      virtual ~TMersenneLucasLehmer(){}
  };


}
  
#endif
