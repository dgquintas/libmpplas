/*
 * $Id$
 */

#ifndef __BASIC_TYPEDEFS
#define __BASIC_TYPEDEFS


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

#ifdef USESIMD
  #include <xmmintrin.h>
#else
  typedef struct { float f[4]; } __attribute__ ((aligned (16))) __m128;
#endif
  typedef __m128 SIMDDigit;
}

#endif
