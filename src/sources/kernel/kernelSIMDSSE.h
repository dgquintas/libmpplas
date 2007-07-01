/* 
 * $Id$
 *
 */

#ifndef __KERNELSIMDSSE_H
#define __KERNELSIMDSSE_H

namespace mpplas{

  namespace SIMDCPU{ 


#include <xmmintrin.h>




    /* FLOAT */
#define __FLOAT_SIMD
    template<> 
      const short SIMDCPUImpl<float>::ELEMENTS_PER_DIGIT= 4;

    template<>
      inline void SIMDCPUImpl<float>::Add(SIMDDigit& out,const SIMDDigit& arg1, const SIMDDigit& arg2){
        out.f = _mm_add_ps(arg1.f, arg2.f);
      }


    template<>
      inline void SIMDCPUImpl<float>::Sub(SIMDDigit& out,const SIMDDigit& arg1, const SIMDDigit& arg2){
        out.f = _mm_sub_ps(arg1.f, arg2.f);
      }



    template<>
      inline void SIMDCPUImpl<float>::Mul(SIMDDigit& out,const SIMDDigit& arg1, const SIMDDigit& arg2){
        out.f = _mm_mul_ps(arg1.f, arg2.f);
      }

    template<>
      inline void SIMDCPUImpl<float>::Div(SIMDDigit& out,const SIMDDigit& arg1, const SIMDDigit& arg2){
        out.f = _mm_div_ps(arg1.f, arg2.f);
      }

    template<>
      inline void SIMDCPUImpl<float>::Sum(float& out,SIMDDigit arg1){
        arg1.f= _mm_add_ps(arg1.f, _mm_movehl_ps(arg1.f,arg1.f));
        arg1.f= _mm_add_ps(arg1.f, _mm_shuffle_ps(arg1.f, arg1.f, _MM_SHUFFLE(3, 2, 1, 1)));
        _mm_store_ss(&out, arg1.f);
      }

    /** 
     * @pre @a src must be 16-byte aligned 
     */
    template<>
      inline void SIMDCPUImpl<float>::Pack(SIMDDigit& out, const float* const src){
        out.f = _mm_load_ps(src);
      }

    /** 
     * @pre @a out must be 16-byte aligned 
     */
    template<>
      inline void SIMDCPUImpl<float>::Unpack(float* const out, const SIMDDigit& src ){
        _mm_store_ps(out,src.f);
      }


    /* DOUBLE */
    /* it's not supported by SSE, therefore the generic version has to be used */


    /* INT */
    /* it's not supported by SSE, therefore the generic version has to be used */

  }
}
#pragma __libmpplas_manual_include 
  #include "kernelSIMDgeneric.h"


#endif
