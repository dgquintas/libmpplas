/*
 * $Id$
 */

#ifndef __DIGITUTILS_H
#define __DIGITUTILS_H

#include <cmath>

#include "constants.h"
#include "mp.h"

namespace mpplas{

  inline size_t numBits(const Digit d) __FUNC_CONST_ATTRIB; 
  inline size_t numBits(const Digit d){
    return vCPUVectorial::numBits(d); 
  }
  inline size_t numBits(const SignedDigit d) __FUNC_CONST_ATTRIB;
  inline size_t numBits(const SignedDigit d)  {
    return vCPUVectorial::numBits(std::abs(d)); 
  }


}

#endif
