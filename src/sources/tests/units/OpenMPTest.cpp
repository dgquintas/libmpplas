/*
 * $Id$
 */

#ifdef _OPENMP
#include <string>
#include "OpenMPTest.h"

#include <omp.h>

using namespace std;
using namespace mpplas;
using namespace com_uwyn_qtunit;

OpenMPTest::OpenMPTest()
  : funcs(MethodsFactory::getInstance()){
  addTest( OpenMPTest, testParallelFor);
}

void OpenMPTest::setUp(){
  funcs->getFunc(rnd);
  factor = rnd->getInteger(256);
  integers = new Z[NUM_THREADS];
  integersPAR = new Z[NUM_THREADS];
  integersSEQ = new Z[NUM_THREADS];
  for(int i = 0; i < NUM_THREADS; i++){
    integers[i] = rnd->getInteger(512);
  }

}
void OpenMPTest::tearDown(){
  delete [] integers;
  delete [] integersSEQ;
  delete [] integersPAR;
}

void OpenMPTest::testParallelFor(){

  const int num_threads_ini = omp_get_max_threads();

  for(int i = 0; i < NUM_THREADS; i++){
    integersSEQ[i] = integers[i] * factor;
  }

  omp_set_num_threads(NUM_THREADS);
#pragma omp parallel default(shared)
  {
    qassertEquals( omp_get_num_threads(), NUM_THREADS);
#pragma omp for 
    for(int i = 0; i < NUM_THREADS; i++){
      integersPAR[i] = integers[i] * factor;
    }
  }

  for(int i = 0; i < NUM_THREADS; i++){
    qassertTrue( integersSEQ[i] == integersPAR[i]);
  }

  omp_set_num_threads(num_threads_ini);
}


  

#endif
