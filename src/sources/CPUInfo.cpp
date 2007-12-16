#include "CPUInfo.h"
#include "BasicTypedefs.h"
#include "CompilationConfig.h"
#include "omp_mock.h"

namespace mpplas{

  int CPUInfo::getCacheL1Size() const {
    return _l1Size;
  }
  int CPUInfo::getCacheL2Size() const {
    return _l2Size;
  }
  int CPUInfo::getCacheL3Size() const {
    return _l3Size;
  }

  std::string CPUInfo::getModelName() const {
    return _modelName;
  }

  std::string CPUInfo::getArchName() const {
    return std::string(CompilationConfig::TARGET_ARCH);
  }

  std::vector<std::string> CPUInfo::getSIMDCapabilities() const {
    return _simdCap;
  }

  int CPUInfo::getDigitBitWidth() const {
    return sizeof(Digit)*8;
  }

  int CPUInfo::getAvailableCPUs() const {
    return omp_get_num_procs();
  }

}
