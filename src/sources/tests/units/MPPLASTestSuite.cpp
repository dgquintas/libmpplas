/*
 *  $Id$
 */

#include "MPPLASTestSuite.h"

#include <pari/pari.h>

using namespace com_uwyn_qtunit;

MPPLASTestSuite::MPPLASTestSuite() {

  pari_init(10000000, 0);

  addTestUnit(_randomTest);
  addTestUnit(_primesTest);
  addTestUnit(_kernelTest);
  addTestUnit(_zTest);
	addTestUnit(_z_nTest);
	addTestUnit(_zM_nTest);
  addTestUnit(_matrixZTest);
//  addTestUnit(_matrixRTest);
  addTestUnit(_vectorZTest);
  addTestUnit(_vectorRTest);
addTestUnit(_functionsTest);
#ifdef _OPENMP
  addTestUnit(_openMPTest);
#endif
  addTestUnit(_rsaTest);
  addTestUnit(_reductionTest);
  addTestUnit(_exponentiationTest);
  addTestUnit(_systemInfoTest);
  addTestUnit(_gcdTest);

}
