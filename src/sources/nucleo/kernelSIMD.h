/* 
 * $Id$
 */
#ifndef __KERNELSIMD_H
#define __KERNELSIMD_H

#include "constants.h"

/** Generic SIMD kernel 
 *
 * Design based on the guidelines given at:
 * \par Why Not Specialize Function Templates?
 *  C/C++ Users Journal, 19(7), July 2001.
 *
 * @sa http://www.gotw.ca/publications/mill17.htm
 */

namespace mpplas{

  namespace SIMDCPU {

    template<typename T>
      struct SIMDCPUImpl {
        static inline void Add(SIMDDigit& out, const SIMDDigit& arg1, const SIMDDigit& arg2);
        static inline void Sub(SIMDDigit& out, const SIMDDigit& arg1, const SIMDDigit& arg2);
        static inline void Mul(SIMDDigit& out, const SIMDDigit& arg1, const SIMDDigit& arg2);
        static inline void Div(SIMDDigit& out, const SIMDDigit& arg1, const SIMDDigit& arg2);

        static inline void Pack(SIMDDigit& out, const T* const src);
        static inline void Unpack(T* const out, const SIMDDigit& src);
      };


    template<typename T>
      inline void Add(SIMDDigit& out, const SIMDDigit& arg1, const SIMDDigit& arg2){
        SIMDCPUImpl<T>::Add(out,arg1,arg2); 
      }
    template<typename T>
      inline void Sub(SIMDDigit& out, const SIMDDigit& arg1, const SIMDDigit& arg2){
        SIMDCPUImpl<T>::Sub(out,arg1,arg2); 
      }
    template<typename T>
      inline void Mul(SIMDDigit& out, const SIMDDigit& arg1, const SIMDDigit& arg2){
        SIMDCPUImpl<T>::Mul(out,arg1,arg2); 
      }
    template<typename T>
      inline void Div(SIMDDigit& out, const SIMDDigit& arg1, const SIMDDigit& arg2){
        SIMDCPUImpl<T>::Div(out,arg1,arg2); 
      }

    template<typename T>
      inline void Pack(SIMDDigit& out, const T* const src){
        SIMDCPUImpl<T>::Pack(out,src); 
      }
    template<typename T>
      inline void Unpack(T* const out, const SIMDDigit& src){
        SIMDCPUImpl<T>::Unpack(out,src); 
      }

#ifdef USESIMD_nosimd
#pragma __libmpplas_manual_include nosimd 
  #include "kernelSIMDgeneric.h"
#endif

    
#ifdef USESIMD_sse
#pragma __libmpplas_manual_include sse
  #include "kernelSIMDSSE.h"
#endif

#ifdef USESIMD_sse2
#pragma __libmpplas_manual_include sse2
  #include "kernelSIMDSSE2.h"
#endif


  }
}


#endif
