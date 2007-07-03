/*
 * $Id: MethodsFactoryTest.cpp 338 2007-06-29 21:59:44Z dgquintas $
 */

#include "MethodsFactoryTest.h"
#include "Random.h"


using namespace com_uwyn_qtunit;

MethodsFactoryTest::MethodsFactoryTest()
  : _funcs(mpplas::MethodsFactory::getReference())
{
  addTest(MethodsFactoryTest, testSet);
  addTest(MethodsFactoryTest, testGet);
  addTest(MethodsFactoryTest, testReset);
}

void MethodsFactoryTest::setUp(){}
void MethodsFactoryTest::tearDown(){
  _funcs.reset();
}

void MethodsFactoryTest::testReset(){
  testSet();
  _funcs.reset();
  testGet();
}
void MethodsFactoryTest::testGet(){
  mpplas::RandomFast* rnd;
  mpplas::RandomFast* dflRnd = new mpplas::RandomFast::DFL();
  _funcs.getFunc(rnd);

  qassertEquals(typeid(*rnd).name(), typeid(*dflRnd).name());

}
void MethodsFactoryTest::testSet(){
  mpplas::RandomFast* rnd;

  mpplas::RandomFast* newRnd = new mpplas::CongruentGen();
  _funcs.setFunc(newRnd);
  _funcs.getFunc(rnd);
  
  qassertEquals(typeid(*rnd).name(), typeid(*newRnd).name());
}
