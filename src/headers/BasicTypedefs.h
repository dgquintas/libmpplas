/*
 * $Id$
 */

#ifndef __BASIC_TYPEDEFS
#define __BASIC_TYPEDEFS

namespace mpplas{

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

  //  /** Las arquitecturas soportadas */
  //  struct Arch {
  //    enum {
  //      x86,
  //      x86Prof,
  //      x86_64,
  //      x86_64Prof,
  //      generic,
  //      ppc
  //    };
  //  };
  //
  //  /** Las operaciones de la vCPUBasica */
  //  struct Operaciones {
  //    enum {
  //      Add, Addx, Sub, Subx, Addmul, Mul, Div, Shiftl, Shiftlr, Bfffo
  //    };
  //  };
}

#endif
