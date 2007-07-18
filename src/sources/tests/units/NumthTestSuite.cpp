/*
 *  $Id$
 */

#include "NumthTestSuite.h"

#include <stdexcept>
#include <pari/pari.h>


using namespace com_uwyn_qtunit;

NumthTestSuite::NumthTestSuite() 
{

  pari_init(10000000, 0);

//  addTestUnit(_randomTest);
//  addTestUnit(_kernelTest);
//	addTestUnit(_zTest);
//	addTestUnit(_z_nTest);
//	addTestUnit(_zM_nTest);
//  addTestUnit(_matrixZTest);
////  addTestUnit(_matrixRTest);
//  addTestUnit(_vectorZTest);
//  addTestUnit(_vectorRTest);
//  addTestUnit(_functionsTest);
//#ifdef _OPENMP
//  addTestUnit(_openMPTest);
//#endif
//  addTestUnit(_rsaTest);
//  addTestUnit(_reductionTest);
  addTestUnit(_exponentiationTest);

}
