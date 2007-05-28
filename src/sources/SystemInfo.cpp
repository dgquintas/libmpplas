#include "SystemInfo.h"
#include "CPUInfo_x86.h"
#include "CPUInfo_x86_64.h" 

#ifndef SVN_REV
  #define SVN_REV -1
#endif

namespace mpplas{
 
  const char* const BUILD_DATE = __DATE__;
  const char* const BUILD_TIME = __TIME__;
  const int REVISION_VER = SVN_REV;


  const char* const SystemInfo::getBuildDate(){
    return BUILD_DATE;
  }
  const char* const SystemInfo::getBuildTime(){
    return BUILD_TIME;
  }
  const int SystemInfo::getRevisionNumber(){
    return REVISION_VER;
  }

  const CPUInfo& SystemInfo::getCPUInfo() {
#ifdef ARCH_x86
        return CPUInfo_x86::getReference();
#endif

#ifdef ARCH_x86_64
        return CPUInfo_x86_64::getReference();
#endif

#ifdef ARCH_generic
        //TODO
#endif
      }; 


}
