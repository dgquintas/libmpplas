/*
 * $Id $
 */

#include <cppunit/TestCase.h>
#include <string>
#include "RandomTest.h"

CPPUNIT_TEST_SUITE_REGISTRATION( RandomTest );

void RandomTest::setUp(){
}
void RandomTest::tearDown(){
//empty. new is not used
}

void RandomTest::testRC4(){
  NumThRC4Gen rc4gen;
  CPPUNIT_ASSERT(fips.pruebaRandom(rc4gen));
}
void RandomTest::testCongruent(){
  congruentGen congruentGen;
  CPPUNIT_ASSERT(fips.pruebaRandom(congruentGen));
}
void RandomTest::testBBS(){
  BBSGen bbsgen;
  CPPUNIT_ASSERT(fips.pruebaRandom(bbsgen));
}
