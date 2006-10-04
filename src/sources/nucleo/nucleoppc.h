/* 
 * $Id$
 */


//
//
//   /******************************************************************
//   *                                                                 *
//   *               IMPLEMENTACIÓN PARA ARQUITECTURA PPC              *
//   *                                                                 *
//   ******************************************************************/ 
//
//  template<>
//    inline Cifra vCPUBasica<Arch::ppc>::Add(Cifra a, Cifra b)
//    {
//      Cifra ret;
//      __asm__ ( "li %[_of], 0\n"
//          "addc %[_ret], %[_a], %[_b]\n"
//          "addze %[_of], %[_of]\n"
//          : [_ret] "=&r"(ret), [_of] "=&r"(overflow)
//          : [_a] "r"(a) , [_b] "r"(b)
//          );
//      return ret;
//    }
//
//  template<>
//    inline Cifra vCPUBasica<Arch::ppc>::Addx(Cifra a, Cifra b)
//    {
//      Cifra ret;
//      __asm__ ( "addc %[_a], %[_a], %[_of]\n"
//          "adde %[_ret], %[_a], %[_b]\n"
//          "li %[_of], 0\n"
//          "addze %[_of], %[_of]\n"
//          : [_ret] "=&r"(ret), [_of] "=&r"(overflow)
//          : [_a] "r"(a) , [_b] "r"(b), "1" (overflow)
//          );
//      return ret;
//    }
//
//  template<>
//    inline Cifra vCPUBasica<Arch::ppc>::Sub(Cifra a, Cifra b)
//    {
//      Cifra ret;
//      __asm__ ( "subfc %[_ret], %[_b], %[_a]\n"
//          "subfe %[_of], %[_of], %[_of]\n"
//          "neg %[_of], %[_of]\n"
//          : [_ret] "=&r"(ret), [_of] "=&r"(overflow)
//          : [_a] "r"(a) , [_b] "r"(b)
//          );
//      return ret;
//    }
//
//  template<>
//    inline Cifra vCPUBasica<Arch::ppc>::Subx(Cifra a, Cifra b)
//    {
//      Cifra ret;
//
//      __asm__ ( "subfc %[_ret], %[_b], %[_a]\n"
//          "subfe r3, r3, r3\n"
//          "subfc %[_ret], %[_of], %[_ret]\n"
//          "subfe %[_of], %[_of], %[_of]\n"
//          "or %[_of], %[_of], r3\n"
//          "neg %[_of], %[_of]\n"
//          : [_ret] "=&r"(ret), [_of] "=&r"(overflow)
//          : [_a] "r"(a) , [_b] "r"(b), "1" (overflow)  
//          : "r3"
//          );
//
//      return ret;
//    }
//
//  template<>
//    inline Cifra vCPUBasica<Arch::ppc>::Mul(Cifra a, Cifra b)
//    {
//      Cifra ret;
//
//      __asm__ ( "mullw %[_ret], %[_a],%[_b]\n"
//          "mulhwu %[_resto], %[_a], %[_b]\n"
//          : [_ret] "=&r"(ret), [_resto] "=&r"(resto)
//          : [_a] "r"(a) , [_b] "r"(b)  
//          );
//
//      return ret;
//    }
//
//  template<>
//    inline Cifra vCPUBasica<Arch::ppc>::Addmul(Cifra a, Cifra b)
//    {
//      Cifra ret;
//
//      __asm__ ( "mullw %[_ret], %[_a],%[_b]\n"
//          "mulhwu r3, %[_a], %[_b]\n"
//          "addc %[_ret], %[_ret], %[_resto]\n"
//          "addze %[_resto], r3\n" 
//          : [_ret] "=&r"(ret), [_resto] "=&r"(resto)
//          : [_a] "r"(a) , [_b] "r"(b),  "1" (resto)
//          : "r3" );
//
//      return ret;
//    }
//
//  template<>
//    inline Cifra vCPUBasica<Arch::ppc>::Bfffo(Cifra a)
//    {
//      Cifra ret;
//
//      __asm__ ( "cntlzw %[_ret], %[_a]\n"
//          : [_ret] "=&r"(ret) 
//          : [_a] "r"(a)
//          );
//
//      return ret;
//    }
//

