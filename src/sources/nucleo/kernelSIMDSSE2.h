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

        c[0] = a[0] / b[0];
        c[1] = a[1] / b[1];
        c[2] = a[2] / b[2];
        c[3] = a[3] / b[3];
        c[4] = a[4] / b[4];
        c[5] = a[5] / b[5];
        c[6] = a[6] / b[6];
        c[7] = a[7] / b[7];

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



#pragma __libmpplas_manual_include 
  #include "kernelSIMDSSE.h"
