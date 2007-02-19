/*
 * $Id $
 */

#include <string>
#include "RandomTest.h"

using namespace com_uwyn_qtunit;

RandomTest::RandomTest()
  : fips_()
{
  addTest(RandomTest, testRC4);
  addTest(RandomTest, testCongruent);
  addTest(RandomTest, testBBS);
  
}
void RandomTest::setUp(){
}
void RandomTest::tearDown(){
//empty. new is not used
}

void RandomTest::testRC4(){
  NumThRC4Gen rc4gen;
  qassertTrue(fips_.pruebaRandom(rc4gen));
}
void RandomTest::testCongruent(){
  congruentGen congruentGen;
  qassertTrue(fips_.pruebaRandom(congruentGen));
}
void RandomTest::testBBS(){
  BBSGen bbsgen;
  qassertTrue(fips_.pruebaRandom(bbsgen));
}
