/*
 * $Id $
 */

#include <string>
#include "SystemInfoTest.h"

using namespace com_uwyn_qtunit;

SystemInfoTest::SystemInfoTest(){
  addTest(SystemInfoTest, testSystemInfo);
}

void SystemInfoTest::setUp(){
}
void SystemInfoTest::tearDown(){
//empty. new is not used
}

void SystemInfoTest::testSystemInfo(){

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
}

