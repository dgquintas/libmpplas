/* 
 * $Id$
 */
#ifndef __KERNELSIMD_H
#define __KERNELSIMD_H

#include <ostream>

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
        /** SIMD addition.
         *
         * Add two SIMDDigit.
         *
         * @param out The resulting SIMDDigit containing the sums
         * @param arg1 SIMDDigit containing the first addend
         * @param arg2 SIMDDigit containing the second addend  */
        static inline void Add(SIMDDigit& out, const SIMDDigit& arg1, const SIMDDigit& arg2);

        /** SIMD subtraction.
         *
         * Subtract two SIMDDigit.
         *
         * @param out The resulting SIMDDigit containing the differences
         * @param arg1 SIMDDigit containig the minuends
         * @param arg2 SIMDDigit containig the subtrahends  */
        static inline void Sub(SIMDDigit& out, const SIMDDigit& arg1, const SIMDDigit& arg2);

        /** SIMD multiplication.
         *
         * Multiply two SIMDDigit.
         *
         * @param out The resulting SIMDDigit containing the products
         * @param arg1 SIMDDigit containing the first factors
         * @param arg2 SIMDDigit containing the second factors  */
        static inline void Mul(SIMDDigit& out, const SIMDDigit& arg1, const SIMDDigit& arg2);

        /** SIMD division.
         *
         * Divide two SIMDDigit.
         *
         * @param out The resulting SIMDDigit containig the quotients
         * @param arg1 SIMDDigit containig the dividends
         * @param arg2 SIMDDigit containig the divisors */
        static inline void Div(SIMDDigit& out, const SIMDDigit& arg1, const SIMDDigit& arg2);

        /** Horizontal addition.
         *
         * Sums the individual values packed in @a arg1: \f$out = \sum_{e \in arg1} e$\f 
         *
         * @param out The resulting sum.
         * @param arg1 The SIMDDigit whose elements to sum. */
        static inline void Sum(T& out, SIMDDigit arg1);

        /** Convert from an array of standard C++ types to SIMDDigit.
         *
         * @param out The resulting SIMDDigit containing the elements from @a src.
         * @param src An array of standard C++ type values   */
        static inline void Pack(SIMDDigit& out, const T* const src);

        /** Convert from SIMDDigit to an array of standard C++ types.
         *
         * @param out An array of standard C++ type values containing
         * the values packed in @a src.
         * @param src A SIMDDigit. */
        static inline void Unpack(T* const out, const SIMDDigit& src);

        /** Number of basic elements per SIMDDigit */
        static const short ELEMENTS_PER_DIGIT;  
      };




    //////////////////////////////////////////////////////////////////////////////
    

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
      inline void Sum(T& out, const SIMDDigit& arg1){
        SIMDCPUImpl<T>::Sum(out,arg1); 
      }

    template<typename T>
      inline void Pack(SIMDDigit& out, const T* const src){
        SIMDCPUImpl<T>::Pack(out,src); 
      }
    template<typename T>
      inline void Unpack(T* const out, const SIMDDigit& src){
        SIMDCPUImpl<T>::Unpack(out,src); 
      }



  }

  std::ostream& operator<<(std::ostream& out, const __m128& v){
    float x[4] __attribute__((aligned(16)));
    SIMDCPU::Unpack<float>(x,static_cast< SIMDDigit >(v));
    out << x[0] << " " << x[1] << " " << x[2] << " " << x[3];
    return out;
  } 
  std::ostream& operator<<(std::ostream& out, const __m128d& v){
    double x[2] __attribute__((aligned(16)));
    SIMDCPU::Unpack<double>(x,static_cast< SIMDDigit >(v));
    out << x[0] << " " << x[1] ;
    return out;
  }
  std::ostream& operator<<(std::ostream& out, const __m128i& v){
    int16_t x[8] __attribute__((aligned(16)));
    SIMDCPU::Unpack<int16_t>(x,static_cast< SIMDDigit >(v));
    out << x[0] << " " << x[1] << " " << x[2] << " " << x[3] << " " 
      << x[4] << " " << x[5] << " " << x[6] << " " << x[7] ;
    return out;
  }
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



#endif
