#include "SystemInfo.h"
#include "CPUInfo_x86.h"
#include "CPUInfo_x86_64.h" 
#include "CPUInfo_generic.h"
#include "CompilationConfig.h"
#include "omp_mock.h"


namespace mpplas{
 
  const CPUInfo& SystemInfo::getCPUInfo() {
#ifdef ARCH_x86
        return CPUInfo_x86::getReference();
#endif

#ifdef ARCH_x86_64
        return CPUInfo_x86_64::getReference();
#endif

#ifdef ARCH_generic
        return CPUInfo_generic::getReference();
#endif
      }; 


  const char* SystemInfo::getBuildDate(){
    return CompilationConfig::BUILD_DATE;
  }
  const char* SystemInfo::getBuildTime(){
    return CompilationConfig::BUILD_TIME;
  }
  int SystemInfo::getRevisionNumber(){
    return CompilationConfig::SOURCE_REVISION;
  }
  int  SystemInfo::getOptimizationLevel(){
    return CompilationConfig::OPT_LEVEL;
  }

  bool SystemInfo::isProfilingEnabled(){
    return CompilationConfig::PROFILING_ENABLED;
  }

  int SystemInfo::getCurrentNumberOfThreads(){
    return omp_get_num_threads();
  }

  int SystemInfo::getMaxNumberOfThreads(){
    return omp_get_max_threads();
  }

  bool SystemInfo::isOpenMPEnabled(){
    return CompilationConfig::OPENMP_ENABLED;
  }

  bool SystemInfo::isReleaseVersion(){
    return CompilationConfig::RELEASE_VERSION;
  }

  std::string SystemInfo::getSIMDKernel(){
    return CompilationConfig::SIMD_KERNEL;
  }

  std::string SystemInfo::getCompilerCmd(){
    return CompilationConfig::COMPILER_CMD;
  }

}
