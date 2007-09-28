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
    template<>
      inline void Add<double2xSIMD_t>(SIMDDigit<double2xSIMD_t>& out,const SIMDDigit<double2xSIMD_t>& arg1, const SIMDDigit<double2xSIMD_t>& arg2){
        out.data = _mm_add_pd(arg1.data, arg2.data);
      }


    template<>
      inline void Sub<double2xSIMD_t>(SIMDDigit<double2xSIMD_t>& out,const SIMDDigit<double2xSIMD_t>& arg1, const SIMDDigit<double2xSIMD_t>& arg2){
        out.data = _mm_sub_pd(arg1.data, arg2.data);
      }



    template<>
      inline void Mul<double2xSIMD_t>(SIMDDigit<double2xSIMD_t>& out,const SIMDDigit<double2xSIMD_t>& arg1, const SIMDDigit<double2xSIMD_t>& arg2){
        out.data = _mm_mul_pd(arg1.data, arg2.data);
      }

    template<>
      inline void Div<double2xSIMD_t>(SIMDDigit<double2xSIMD_t>& out,const SIMDDigit<double2xSIMD_t>& arg1, const SIMDDigit<double2xSIMD_t>& arg2){
        out.data = _mm_div_pd(arg1.data, arg2.data);
      }

    template<>
      inline void Sum<double2xSIMD_t>(SIMDDigit<double2xSIMD_t>::BasicType& out, SIMDDigit<double2xSIMD_t> arg1){
        arg1.data = _mm_add_pd(arg1.data, _mm_shuffle_pd(arg1.data, arg1.data, _MM_SHUFFLE2(0, 1)));
        _mm_store_sd(&out, arg1.data);

      }

    /** 
     * @pre @a src must be 16-byte aligned 
     */
    template<>
      inline void Pack<double2xSIMD_t>(SIMDDigit<double2xSIMD_t>& out, const SIMDDigit<double2xSIMD_t>::BasicType* const src){
        out.data = _mm_load_pd(src);
      }

    /** 
     * @pre @a out must be 16-byte aligned 
     */
    template<>
      inline void Unpack(SIMDDigit<double2xSIMD_t>::BasicType* const out, const SIMDDigit<double2xSIMD_t>& src ){
        _mm_store_pd(out,src.data);
      }






    /* INT 16 */

    template<>
      inline void Add<int8xSIMD_t>(SIMDDigit<int8xSIMD_t>& out,const SIMDDigit<int8xSIMD_t>& arg1, const SIMDDigit<int8xSIMD_t>& arg2){
        out.data = _mm_add_epi16(arg1.data, arg2.data);
      }


    template<>
      inline void Sub<int8xSIMD_t>(SIMDDigit<int8xSIMD_t>& out,const SIMDDigit<int8xSIMD_t>& arg1, const SIMDDigit<int8xSIMD_t>& arg2){
        out.data = _mm_sub_epi16(arg1.data, arg2.data);
      }


    template<>
      inline void Mul<int8xSIMD_t>(SIMDDigit<int8xSIMD_t>& out,const SIMDDigit<int8xSIMD_t>& arg1, const SIMDDigit<int8xSIMD_t>& arg2){
        out.data = _mm_mullo_epi16(arg1.data, arg2.data);
      }

    template<>
      inline void Div<int8xSIMD_t>(SIMDDigit<int8xSIMD_t>& out,const SIMDDigit<int8xSIMD_t>& arg1, const SIMDDigit<int8xSIMD_t>& arg2){
        // not supported. ad-hoc method
        const int16_t* const a( (const int16_t* const)(&(arg1.data)) );
        const int16_t* const b( (const int16_t* const)(&(arg2.data)) );
        int16_t* const c( (int16_t* const)(&(out.data)) );

        for( int i = 0; i < 8 ; ++i){
          c[i] = a[i] / b[i];
        }

      }

    template<>
      inline void Sum<int8xSIMD_t>(SIMDDigit<int8xSIMD_t>::BasicType& out,SIMDDigit<int8xSIMD_t> arg1){
        arg1.data = _mm_add_epi16(arg1.data, _mm_shuffle_epi32(arg1.data, _MM_SHUFFLE(1,0,0,0)) );
        arg1.data = _mm_add_epi16(arg1.data, _mm_shuffle_epi32( arg1.data, _MM_SHUFFLE(2,2,2,2) ));
        arg1.data = _mm_add_epi16(arg1.data, _mm_shufflehi_epi16( arg1.data, _MM_SHUFFLE(2,2,2,2) ));
        out = _mm_extract_epi16(arg1.data, 7);
      }

    /** 
     * @pre @a src must be 16-byte aligned 
     */
    template<>
      inline void Pack<int8xSIMD_t>(SIMDDigit<int8xSIMD_t>& out, const SIMDDigit<int8xSIMD_t>::BasicType* const src){
        out.data = _mm_load_si128((__m128i const*)src);
      }

    /** 
     * @pre @a out must be 16-byte aligned 
     */
    template<>
      inline void Unpack<int8xSIMD_t>(SIMDDigit<int8xSIMD_t>::BasicType* const out, const SIMDDigit<int8xSIMD_t>& src ){
        _mm_store_si128((__m128i*)out,src.data);
      }
  }
}


#pragma __libmpplas_manual_include 
  #include "kernelSIMDSSE.h"


#endif
