#include "SystemInfo.h"
#include "CPUInfo_x86.h"
#include "CPUInfo_x86_64.h" 
#include "CompilationConfig.h"

namespace mpplas{
 
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


  const char* const SystemInfo::getBuildDate(){
    return CompilationConfig::BUILD_DATE;
  }
  const char* const SystemInfo::getBuildTime(){
    return CompilationConfig::BUILD_TIME;
  }
  const int SystemInfo::getRevisionNumber(){
    return CompilationConfig::SOURCE_REVISION;
  }
  const int  SystemInfo::getOptimizationLevel(){
    return CompilationConfig::OPT_LEVEL;
  }

  const bool SystemInfo::isProfilingEnabled(){
    return CompilationConfig::PROFILING_ENABLED;
  }

  const bool SystemInfo::isOpenMPEnabled(){
    return CompilationConfig::OPENMP_ENABLED;
  }

  const bool SystemInfo::isReleaseVersion(){
    return CompilationConfig::RELEASE_VERSION;
  }

  const std::string SystemInfo::getSIMDKernel(){
    return CompilationConfig::SIMD_KERNEL;
  }

  const std::string SystemInfo::getCompilerCmd(){
    return CompilationConfig::COMPILER_CMD;
  }

}
