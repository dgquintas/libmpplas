/*
 * $Id$
 */

#include "constantes.h"
#include "SystemInfo.h"

namespace mpplas{

  std::string SystemInfo::getArchitecture() const{
    return std::string(Constantes::ARCH_STRING);
  }

  size_t SystemInfo::getBasicTypeBitLength() const{
    return Constantes::BITS_EN_CIFRA;
  }

}
  
