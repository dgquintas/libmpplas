#include "CPUInfo_x86_64.h"

namespace mpplas{

  //static singleton initialization
  template<>
    const std::auto_ptr< CPUInfo_x86_64 > 
    SingletonMixIn< CPUInfo_x86_64 >::singletonInstance( new CPUInfo_x86_64() );


  CPUInfo_x86_64::CPUInfo_x86_64()
    : SingletonMixIn< CPUInfo_x86_64 >(), CPUInfo_x86::CPUInfo_x86()
  { }

  
  std::string CPUInfo_x86_64::getArchName() const {
    return std::string("x86_64");
  }

  int CPUInfo_x86_64::getDigitBitWidth() const {
    return 64;
  }
}

