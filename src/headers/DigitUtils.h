/*
 * $Id$
 */

#ifndef __DIGITUTILS_H
#define __DIGITUTILS_H

#include <cmath>

#include "Constants.h"
#include "VectorialCPU.h"

namespace mpplas{

  inline int getBitLength(const Digit d) __FUNC_CONST_ATTRIB; 

  /** Precise bit length of a @a Digit 
   * 
   *
   * That is \f$ \lceil \lg_2(d) \rceil \f$.
   *
   * @param d the Digit to consider.
   *
   * @return the minimum number of bits needed to represent @a d.
   * */
  inline int getBitLength(const Digit d){
    return VectorialCPU::getBitLength(d); 
  }
  inline int getBitLength(const SignedDigit d) __FUNC_CONST_ATTRIB;

  /** Precise bit length of a @a SignedDigit
   * 
   * That is \f$ \lceil \lg_2(d) \rceil \f$.
   *
   * @param d the SignedDigit to consider.
   *
   * @return the minimum number of bits needed to represent @a d.
   * */
  inline int getBitLength(const SignedDigit d)  {
    return VectorialCPU::getBitLength(std::abs(d)); 
  }


}

#endif
