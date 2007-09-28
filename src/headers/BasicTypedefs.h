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


#ifdef USESIMD_sse
  #include <xmmintrin.h>
  typedef struct { double d[2]; } __attribute__ ((aligned (16))) __m128d;
  typedef struct { char int32_t[4]; } __attribute__ ((aligned (16))) __m128i;
#elif USESIMD_sse2
  #include <emmintrin.h>
#else  // USESIMD_nosimd or nothing
  typedef struct { float f[4]; } __attribute__ ((aligned (16))) __m128;
  typedef struct { double d[2]; } __attribute__ ((aligned (16))) __m128d;
  typedef struct { char int32_t[4]; } __attribute__ ((aligned (16))) __m128i;
#endif

typedef __m128 float4xSIMD_t;
typedef __m128d double2xSIMD_t;
typedef __m128i int8xSIMD_t;

template<typename T>
class SIMDtoBasicTypes;


//FIXME: make this configurable at compile time?
template<>
class SIMDtoBasicTypes<float4xSIMD_t>{
  public:
  typedef float BasicType;
};
template<>
class SIMDtoBasicTypes<double2xSIMD_t>{
  public:
  typedef double BasicType;
};
template<>
class SIMDtoBasicTypes<int8xSIMD_t>{
  public:
  typedef int16_t BasicType;
};


  namespace BasicCPU{

    enum OpsEnum { 
      ADD = 0, ADDX, 
      SUB, SUBX, 
      MUL, ADDMUL, 
      DIV, SHIFTL, SHIFTLR, 
      MNOB,
      __OpsEnum_SIZE
        //    /* SIMD OPS */
        //    SIMDADD, SIMDSUB,
        //    SIMDMUL, SIMDDIV,
        //    SIMDSUM,
        //    SIMDPACK, SIMDUNPACK,
        //    __OpsEnum_SIZE
    };
    static const char* const OpsNames[] = {
      "ADD", "ADDX",
      "SUB", "SUBX",
      "MUL", "ADDMUL",
      "DIV", "SHIFTL", "SHIFTLR",
      "MNOB" };
  };

}

#endif
