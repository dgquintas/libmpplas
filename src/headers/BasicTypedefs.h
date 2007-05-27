/*
 * $Id$
 */

#ifndef __BASIC_TYPEDEFS
#define __BASIC_TYPEDEFS

#include <stdint.h> //C99

#ifdef __GNUC__
  #define __FUNC_CONST_ATTRIB __attribute__ ((const))
#else
  #define __FUNC_CONST_ATTRIB 
#endif

namespace mpplas{

#ifndef ARCHBITS
  #warning "Architecture bits not defined. Using 32"
  #define ARCHBITS 32
#endif

  /** Basic data type. 
   *
   * It represents the base considered for Z, and will be the 
   * type used wherever a positive (machine-width) integer is needed.
   */
#if ARCHBITS == 64
  typedef uint64_t Digit;
#elif ARCHBITS == 32
  typedef uint32_t Digit;
#else 
#error Unsupported number of bits ARCHBITS
#endif

  /** Signed basic data type.
   *
   * It is the signed version of Digit. Will be used where signed single-precision
   * integers are needed.
   */
#if ARCHBITS == 64
  typedef int64_t SignedDigit;
#elif ARCHBITS == 32
  typedef int32_t SignedDigit;
#else 
  #error Unsupported number of bits ARCHBITS
#endif

#ifdef USESIMD_nosimd
  typedef struct { float f[4]; } __attribute__ ((aligned (16))) __m128;
  typedef struct { double d[2]; } __attribute__ ((aligned (16))) __m128d;
  typedef struct { char int32_t[4]; } __attribute__ ((aligned (16))) __m128i;
#endif

#ifdef USESIMD_sse
  #include <xmmintrin.h>
  typedef struct { double d[2]; } __attribute__ ((aligned (16))) __m128d;
  typedef struct { char int32_t[4]; } __attribute__ ((aligned (16))) __m128i;
#endif

#ifdef USESIMD_sse2
  #include <emmintrin.h>
#endif

  union SIMDDigit {
    __m128 f;
    __m128d d;
    __m128i i;
  };



}

#endif
