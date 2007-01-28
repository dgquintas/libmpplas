/*
 * $Id$
 */

#ifdef _OPENMP
#include <cppunit/TestCase.h>
#include <string>
#include "OpenMPTest.h"

  #include <omp.h>
  CPPUNIT_TEST_SUITE_REGISTRATION( OpenMPTest );

using namespace std;
using namespace numth;


void OpenMPTest::setUp(){
  factor = funcs.getRandomRapido()->leerBits(256);
  integers = new Z[NUM_THREADS];
  integersPAR = new Z[NUM_THREADS];
  integersSEQ = new Z[NUM_THREADS];
  for(int i = 0; i < NUM_THREADS; i++){
    integers[i] = funcs.getRandomRapido()->leerBits(512);
  }

}
void OpenMPTest::tearDown(){
  delete [] integers;
  delete [] integersSEQ;
  delete [] integersPAR;
}

void OpenMPTest::testParallelFor(){

  for(int i = 0; i < NUM_THREADS; i++){
     integersSEQ[i] = integers[i] * factor;
  }

  omp_set_num_threads(NUM_THREADS);
#pragma omp parallel for default(shared)
  for(int i = 0; i < NUM_THREADS; i++){
     integersPAR[i] = integers[i] * factor;
  }

  for(int i = 0; i < NUM_THREADS; i++){
    CPPUNIT_ASSERT_EQUAL(integersSEQ[i],integersPAR[i]);
  }

}

#endif
