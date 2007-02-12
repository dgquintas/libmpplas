/*
 *  $Id$
 */

#include "NumthTestSuite.h"

#include <stdexcept>

using namespace com_uwyn_qtunit;

NumthTestSuite::NumthTestSuite() 
{
  addTestUnit(rsaTest_);
  addTestUnit(kernelTest_);
	addTestUnit(zTest_);
	addTestUnit(z_nTest_);
}
