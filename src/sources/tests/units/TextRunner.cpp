/*
 *  $Id$
 */

#include "qtunit/TextTestRunner.h"
#include "MPPLASTestSuite.h"
#include "SystemInfo.h"

#include <iostream>

using namespace com_uwyn_qtunit;

int main(int argc, char **argv) {
  
  if( mpplas::SystemInfo::isOpenMPEnabled() ){
    std::cout << "OpenMP enabled" << std::endl;
    std::cout << "(max) Number of threads: " 
      << mpplas::SystemInfo::getMaxNumberOfThreads() 
      << std::endl;
  }
  else{
    std::cout << "OpenMP disabled" << std::endl;
  }

  std::cout << "Opt. level: " 
    << mpplas::SystemInfo::getOptimizationLevel() 
    << std::endl;
   std::cout << "Release version?: " 
    << (mpplas::SystemInfo::isReleaseVersion() ? "true" : "false" )
    << std::endl;
 
	MPPLASTestSuite testsuite;
	TextTestRunner runner(argc, argv);
	runner.add(testsuite);
		
	runner.run();
	
	return 0;
}
