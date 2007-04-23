/*
 * $Id$
 */

#include <string>
#include "FunctionsTest.h"

using namespace com_uwyn_qtunit;

FunctionsTest::FunctionsTest()
  : funcs(mpplas::Funciones::getInstance())
{
  addTest(FunctionsTest, test);
}

void FunctionsTest::setUp(){}
void FunctionsTest::tearDown(){}

void FunctionsTest::test(){

}
