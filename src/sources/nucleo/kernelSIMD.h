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



    ////////////////////////////////

    //FIXME: sacar a .h aparte


#ifdef USESIMD
#include <xmmintrin.h>
#endif

    template<>
      inline void SIMDCPUImpl<float>::Add(SIMDDigit& out,const SIMDDigit& arg1, const SIMDDigit& arg2){
#ifdef USESIMD
        out = _mm_add_ps(arg1, arg2);
#else
        const float* const a( &(arg1.f[0]) );
        const float* const b( &(arg2.f[0]) );
        float* c( &(out.f[0]) );

        c[0] = a[0] + b[0];
        c[1] = a[1] + b[1];
        c[2] = a[2] + b[2];
        c[3] = a[3] + b[3];

#endif
      }


    template<>
      inline void SIMDCPUImpl<float>::Sub(SIMDDigit& out,const SIMDDigit& arg1, const SIMDDigit& arg2){
#ifdef USESIMD
        out = _mm_sub_ps(arg1, arg2);
#else
        const float* const a( &(arg1.f[0]) );
        const float* const b( &(arg2.f[0]) );
        float* c( &(out.f[0]) );

        c[0] = a[0] - b[0];
        c[1] = a[1] - b[1];
        c[2] = a[2] - b[2];
        c[3] = a[3] - b[3];

#endif
      }



    template<>
      inline void SIMDCPUImpl<float>::Mul(SIMDDigit& out,const SIMDDigit& arg1, const SIMDDigit& arg2){
#ifdef USESIMD
        out = _mm_mul_ps(arg1, arg2);
#else
        const float* const a( &(arg1.f[0]) );
        const float* const b( &(arg2.f[0]) );
        float* c( &(out.f[0]) );

        c[0] = a[0] * b[0];
        c[1] = a[1] * b[1];
        c[2] = a[2] * b[2];
        c[3] = a[3] * b[3];

#endif
      }

    template<>
      inline void SIMDCPUImpl<float>::Div(SIMDDigit& out,const SIMDDigit& arg1, const SIMDDigit& arg2){
#ifdef USESIMD
        out = _mm_div_ps(arg1, arg2);
#else
        const float* const a( &(arg1.f[0]) );
        const float* const b( &(arg2.f[0]) );
        float* c( &(out.f[0]) );

        c[0] = a[0] / b[0];
        c[1] = a[1] / b[1];
        c[2] = a[2] / b[2];
        c[3] = a[3] / b[3];

#endif
      }



    /** 
     * @pre @a src must be 16-byte aligned 
     */
    template<>
      inline void SIMDCPUImpl<float>::Pack(SIMDDigit& out, const float* const src){
#ifdef USESIMD
        out = _mm_load_ps(src);
#else
        float* c( &(out.f[0]) );

        c[0] = src[0];
        c[1] = src[1];
        c[2] = src[2];
        c[3] = src[3];

#endif
      }


    /** 
     * @pre @a out must be 16-byte aligned 
     */
    template<>
      inline void SIMDCPUImpl<float>::Unpack(float* const out, const SIMDDigit& src ){
#ifdef USESIMD
        _mm_store_ps(out,src);
#else
        const float* const c( &(src.f[0]) );

        out[0] = c[0];
        out[1] = c[1];
        out[2] = c[2];
        out[3] = c[3];

#endif
      }
  }
}


#endif
