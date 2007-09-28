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
    template<>
      inline void Add<float4xSIMD_t>(SIMDDigit<float4xSIMD_t>& out,const SIMDDigit<float4xSIMD_t>& arg1, const SIMDDigit<float4xSIMD_t>& arg2){
        out.data = _mm_add_ps(arg1.data, arg2.data);
      }


    template<>
      inline void Sub<float4xSIMD_t>(SIMDDigit<float4xSIMD_t>& out,const SIMDDigit<float4xSIMD_t>& arg1, const SIMDDigit<float4xSIMD_t>& arg2){
        out.data = _mm_sub_ps(arg1.data, arg2.data);
      }



    template<>
      inline void Mul<float4xSIMD_t>(SIMDDigit<float4xSIMD_t>& out,const SIMDDigit<float4xSIMD_t>& arg1, const SIMDDigit<float4xSIMD_t>& arg2){
        out.data = _mm_mul_ps(arg1.data, arg2.data);
      }

    template<>
      inline void Div<float4xSIMD_t>(SIMDDigit<float4xSIMD_t>& out,const SIMDDigit<float4xSIMD_t>& arg1, const SIMDDigit<float4xSIMD_t>& arg2){
        out.data = _mm_div_ps(arg1.data, arg2.data);
      }

    template<>
      inline void Sum<float4xSIMD_t>(SIMDDigit<float4xSIMD_t>::BasicType& out,SIMDDigit<float4xSIMD_t> arg1){
        arg1.data= _mm_add_ps(arg1.data, _mm_movehl_ps(arg1.data,arg1.data));
        arg1.data= _mm_add_ps(arg1.data, _mm_shuffle_ps(arg1.data, arg1.data, _MM_SHUFFLE(3, 2, 1, 1)));
        _mm_store_ss(&out, arg1.data);
      }

    /** 
     * @pre @a src must be 16-byte aligned 
     */
    template<>
      inline void Pack<float4xSIMD_t>(SIMDDigit<float4xSIMD_t>& out, const SIMDDigit<float4xSIMD_t>::BasicType* const src){
        out.data = _mm_load_ps(src);
      }

    /** 
     * @pre @a out must be 16-byte aligned 
     */
    template<>
      inline void Unpack<float4xSIMD_t>(SIMDDigit<float4xSIMD_t>::BasicType* const out, const SIMDDigit<float4xSIMD_t>& src ){
        _mm_store_ps(out,src.data);
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
