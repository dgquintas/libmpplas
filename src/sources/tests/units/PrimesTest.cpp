/*
 * $Id$
 */

#include "PrimesTest.h"
#include "aux.h"

#include <pari/pari.h>

using namespace com_uwyn_qtunit;

PrimesTest::PrimesTest(){
  addTest(PrimesTest, testRabinMiller);
  addTest(PrimesTest, testMersenneLucasLehmer);
  addTest(PrimesTest, testGenerator);
}
void PrimesTest::setUp(){
}
void PrimesTest::tearDown(){
//empty. new is not used
}

void PrimesTest::testRabinMiller(){
  const Z prime( _primeGen.getPrime( brand(128,512) ) );
  const bool res = _rm.isPrime(prime) ;
  const GEN p = gp_read_str(const_cast<char*>(prime.toString().c_str()));
  long pariRes = isprime(p);
  qassertEquals( res, (bool)pariRes);
  qassertTrue( res );
}
void PrimesTest::testMersenneLucasLehmer(){
}
void PrimesTest::testGenerator(){
  const Z prime( _primeGen.getPrime( brand(128,512) ) );
  const GEN p = gp_read_str(const_cast<char*>(prime.toString().c_str()));
  long pariRes = isprime(p);
  qassertTrue( pariRes );

}
