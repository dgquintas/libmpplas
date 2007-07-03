/*
 * $Id$
 */

#ifndef __DIGITUTILS_H
#define __DIGITUTILS_H

#include <cmath>

#include "Constants.h"
#include "VectorialCPU.h"

namespace mpplas{

  inline size_t getBitLength(const Digit d) __FUNC_CONST_ATTRIB; 
  inline size_t getBitLength(const Digit d){
    return VectorialCPU::getBitLength(d); 
  }
  inline size_t getBitLength(const SignedDigit d) __FUNC_CONST_ATTRIB;
  inline size_t getBitLength(const SignedDigit d)  {
    return VectorialCPU::getBitLength(std::abs(d)); 
  }


}

#endif
