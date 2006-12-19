/*
 * $Id $
 */

#include <cppunit/TestCase.h>
#include <string>
#include "OpenMPTest.h"
#include <omp.h>

using namespace std;
using namespace numth;


#ifdef _OPENMP
CPPUNIT_TEST_SUITE_REGISTRATION( OpenMPTest );
#endif

void OpenMPTest::setUp(){
  factor = funcs.randomRapido()->leerBits(256);
  integers = new Z[NUM_THREADS];
  integersPAR = new Z[NUM_THREADS];
  integersSEQ = new Z[NUM_THREADS];
  for(int i = 0; i < NUM_THREADS; i++){
    integers[i] = funcs.randomRapido()->leerBits(512);
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
