/*
 *  $Id$
 */

#include "NumthTestSuite.h"

#include <stdexcept>

using namespace com_uwyn_qtunit;

NumthTestSuite::NumthTestSuite() 
{
  addTestUnit(_randomTest);
  addTestUnit(_kernelTest);
	addTestUnit(_zTest);
	addTestUnit(_z_nTest);
  addTestUnit(_matrixZTest);
  addTestUnit(_matrixRTest);
  addTestUnit(_vectorZTest);
  addTestUnit(_functionsTest);
#ifdef _OPENMP
  addTestUnit(_openMPTest);
#endif
  addTestUnit(_rsaTest);
  addTestUnit(_reductionTest);
  addTestUnit(_exponentiationTest);

}
