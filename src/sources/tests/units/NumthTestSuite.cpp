/*
 *  $Id$
 */

#include "NumthTestSuite.h"

#include <stdexcept>

using namespace com_uwyn_qtunit;

NumthTestSuite::NumthTestSuite() 
{
  addTestUnit(kernelTest_);
	addTestUnit(zTest_);
  addTestUnit(rsaTest_);
}
