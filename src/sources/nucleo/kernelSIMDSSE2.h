/* 
 * $Id$
 *
 */

#ifndef __KERNELSIMDSSE2_H
#define __KERNELSIMDSSE2_H

namespace mpplas{

  namespace SIMDCPU{ 


#include <emmintrin.h>


    /* DOUBLE */
#define __DOUBLE_SIMD

    template<>
      inline void SIMDCPUImpl<double>::Add(SIMDDigit& out,const SIMDDigit& arg1, const SIMDDigit& arg2){
        out.d = _mm_add_pd(arg1.d, arg2.d);
      }


    template<>
      inline void SIMDCPUImpl<double>::Sub(SIMDDigit& out,const SIMDDigit& arg1, const SIMDDigit& arg2){
        out.d = _mm_sub_pd(arg1.d, arg2.d);
      }



    template<>
      inline void SIMDCPUImpl<double>::Mul(SIMDDigit& out,const SIMDDigit& arg1, const SIMDDigit& arg2){
        out.d = _mm_mul_pd(arg1.d, arg2.d);
      }

    template<>
      inline void SIMDCPUImpl<double>::Div(SIMDDigit& out,const SIMDDigit& arg1, const SIMDDigit& arg2){
        out.d = _mm_div_pd(arg1.d, arg2.d);
      }

    template<>
      inline void SIMDCPUImpl<double>::Sum(double& out,SIMDDigit arg1){
        arg1.d = _mm_add_pd(arg1.d, _mm_shuffle_pd(arg1.d, arg1.d, _MM_SHUFFLE2(0, 1)));
        _mm_store_sd(&out, arg1.d);

      }

    /** 
     * @pre @a src must be 16-byte aligned 
     */
    template<>
      inline void SIMDCPUImpl<double>::Pack(SIMDDigit& out, const double* const src){
        out.d = _mm_load_pd(src);
      }

    /** 
     * @pre @a out must be 16-byte aligned 
     */
    template<>
      inline void SIMDCPUImpl<double>::Unpack(double* const out, const SIMDDigit& src ){
        _mm_store_pd(out,src.d);
      }






    /* INT 16 */
#define __INT_SIMD

    template<>
      inline void SIMDCPUImpl<int16_t>::Add(SIMDDigit& out,const SIMDDigit& arg1, const SIMDDigit& arg2){
        out.i = _mm_add_epi16(arg1.i, arg2.i);
      }


    template<>
      inline void SIMDCPUImpl<int16_t>::Sub(SIMDDigit& out,const SIMDDigit& arg1, const SIMDDigit& arg2){
        out.i = _mm_sub_epi16(arg1.i, arg2.i);
      }


    template<>
      inline void SIMDCPUImpl<int16_t>::Mul(SIMDDigit& out,const SIMDDigit& arg1, const SIMDDigit& arg2){
        out.i = _mm_mullo_epi16(arg1.i, arg2.i);
      }

    template<>
      inline void SIMDCPUImpl<int16_t>::Div(SIMDDigit& out,const SIMDDigit& arg1, const SIMDDigit& arg2){
        // not supported. ad-hoc method
        const int16_t* const a( (const int16_t* const)(&(arg1.i)) );
        const int16_t* const b( (const int16_t* const)(&(arg2.i)) );
        int16_t* const c( (int16_t* const)(&(out.i)) );

        for( int i = 0; i < 8 ; ++i){
          c[i] = a[i] / b[i];
        }

      }

    template<>
      inline void SIMDCPUImpl<int16_t>::Sum(int16_t& out,SIMDDigit arg1){
        arg1.i = _mm_add_epi16(arg1.i, _mm_shuffle_epi32(arg1.i, _MM_SHUFFLE(1,0,0,0)) );
        arg1.i = _mm_add_epi16(arg1.i, _mm_shuffle_epi32( arg1.i, _MM_SHUFFLE(2,2,2,2) ));
        arg1.i = _mm_add_epi16(arg1.i, _mm_shufflehi_epi16( arg1.i, _MM_SHUFFLE(2,2,2,2) ));
        out = _mm_extract_epi16(arg1.i, 7);
      }

    /** 
     * @pre @a src must be 16-byte aligned 
     */
    template<>
      inline void SIMDCPUImpl<int16_t>::Pack(SIMDDigit& out, const int16_t* const src){
        out.i = _mm_load_si128((__m128i const*)src);
      }

    /** 
     * @pre @a out must be 16-byte aligned 
     */
    template<>
      inline void SIMDCPUImpl<int16_t>::Unpack(int16_t* const out, const SIMDDigit& src ){
        _mm_store_si128((__m128i*)out,src.i);
      }
  }
}


#pragma __libmpplas_manual_include 
  #include "kernelSIMDSSE.h"


#endif
