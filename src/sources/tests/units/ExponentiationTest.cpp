/*
 * $Id $
 */

#include <string>
#include "ExponentiationTest.h"

using namespace com_uwyn_qtunit;

ExponentiationTest::ExponentiationTest()
{
  addTest(ExponentiationTest, testMontgomeryPrecomp);
  addTest(ExponentiationTest, testMontgomeryReduction);

  addTest(ExponentiationTest, testBarrettPrecomp  );
  addTest(ExponentiationTest, testBarrettReduction );

  addTest(ExponentiationTest, testALaMersenneReduction);

  addTest(ExponentiationTest, testClassicMontgomeryInverse);
  
}
void ExponentiationTest::setUp(){
}
void ExponentiationTest::tearDown(){
//empty. new is not used
}


void ExponentiationTest::testMontgomeryPrecomp(){
}
void ExponentiationTest::testMontgomeryReduction(){
}

void ExponentiationTest::testBarrettPrecomp(){
}
void ExponentiationTest::testBarrettReduction(){
}

void ExponentiationTest::testALaMersenneReduction(){
}

void ExponentiationTest::testClassicMontgomeryInverse(){
}  

