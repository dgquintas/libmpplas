/*
 * $Id$
 */

#include "ZTest.h"
#include "KernelTest.h"
#include "Z_nTest.h"
#include <qapplication.h>
//#include <cppunit/ui/qt/TestRunner.h>
#include <cppunit/ui/text/TestRunner.h>
#include <cppunit/extensions/TestFactoryRegistry.h>

int main( int argc, char **argv)
{
// QApplication app(argc, argv);
  CppUnit::TextUi::TestRunner runner;
//  CppUnit::QtTestRunner runner;
  CppUnit::TestFactoryRegistry &registry = CppUnit::TestFactoryRegistry::getRegistry();
  runner.addTest( registry.makeTest() );
  runner.run();
  return 0;
}
