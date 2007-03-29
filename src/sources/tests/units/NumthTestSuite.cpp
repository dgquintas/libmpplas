/*
 *  $Id$
 */

#include "NumthTestSuite.h"

#include <stdexcept>

using namespace com_uwyn_qtunit;

NumthTestSuite::NumthTestSuite() 
{
  addTestUnit(randomTest_);
  addTestUnit(kernelTest_);
	addTestUnit(zTest_);
	addTestUnit(z_nTest_);
  addTestUnit(matrixZTest_);
  addTestUnit(matrixRTest_);
  addTestUnit(vectorZTest_);
  addTestUnit(functionsTest_);
#ifdef _OPENMP
  addTestUnit(openMPTest_);
#endif
  addTestUnit(rsaTest_);
}
