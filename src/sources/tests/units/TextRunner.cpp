/*
 *  $Id$
 */

#include "qtunit/TextTestRunner.h"
#include "NumthTestSuite.h"

using namespace com_uwyn_qtunit;

int main(int argc, char **argv)
{
	NumthTestSuite testsuite;
	TextTestRunner runner(argc, argv);
	runner.add(testsuite);
		
	runner.run();
	
	return 0;
}
