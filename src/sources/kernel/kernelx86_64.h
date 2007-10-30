/* 
 * $Id$
 */

#ifdef ARCH_x86_64

namespace mpplas{

  namespace BasicCPU{


  /**********************************
   *   IMPLEMENTATION FOR X86_64
   **********************************/ 

    inline Digit Add(Digit arg1, Digit arg2, Digit& overflow)
    {
      __asm__ ("xorq %[_of], %[_of];"
               "addq %[_arg2], %[_arg1]; "
               "adcq $0, %[_of]; "
          : "=r" (arg1), [_of] "=r" (overflow)
          : [_arg1] "0" (arg1), [_arg2] "g" (arg2), "1" (overflow)
          : "cc" /* modificamos eflags */
          );

      return arg1; 
    }

    inline Digit Addx(Digit arg1, Digit arg2, Digit& overflow) 
    { 
      __asm__ ("btrq $0, %[_of];"
               "adcq %[_arg2], %[_arg1];" 
               "adcq $0, %[_of]; "
          : "=r" (arg1), [_of] "=r" (overflow) 
          : [_arg1] "0" (arg1), [_arg2] "g" (arg2), "1" (overflow) 
          : "cc" /* modificamos eflags */
          );

      return arg1; 
    }


    inline Digit Sub(Digit arg1, Digit arg2, Digit& overflow) 
    { 
      __asm__  ("xorq %[_of], %[_of];"
               "subq %[_arg2], %[_arg1];"
               "adcq $0, %[_of]; " 
          : "=r" (arg1), [_of] "=r" (overflow) 
          : [_arg1] "0" (arg1), [_arg2] "g" (arg2)
          : "cc" /* modificamos eflags */
          ); 

      return arg1; 
    }
    inline Digit Subx(Digit arg1, Digit arg2, Digit& overflow) 
    { 
      __asm__  ("btrq $0, %[_of];" /* pone CF al valor del bit 0 de overflow */
               "sbbq %[_arg2], %[_arg1];"
               "adcq $0, %[_of];" 
          : "=r" (arg1), [_of] "=r" (overflow) 
          : [_arg1] "0" (arg1), [_arg2] "g" (arg2), "1" (overflow) 
          : "cc" /* modificamos eflags */
          );
      return arg1; 
    }

    inline Digit Mul(Digit arg1,Digit arg2, Digit& resto) 
    { 
      __asm__ (" mulq %[_arg2]" 
          : "=a" (arg1), "=d" (resto) 
          : [_arg1] "0" (arg1), [_arg2] "rm" (arg2)
          ); 

      return arg1; 
    }

    inline Digit Addmul(Digit arg1,Digit arg2, Digit& resto) 
    { 
      __asm__ (" mulq %[_arg2];"
               "addq %[_restoViejo],%[_ret];" 
               "adcq $0, %%rdx;"      
          : [_ret] "=a" (arg1), "=&d" (resto) 
          : [_arg1] "0" (arg1), [_arg2] "rm" (arg2), [_restoViejo] "g" (resto) 
          ); 

      return arg1; 
    }

    inline Digit Div(Digit arg1, Digit arg2, Digit& resto) 
    { 
      __asm__ (" divq %[_arg2]" 
          : "=a" (arg1), "=d" (resto) 
          : [_arg1] "0" (arg1), [_arg2] "g" (arg2), "1" (resto)
          ); 

      return arg1;
    }


    inline Digit Shiftl(Digit arg1,Digit arg2, Digit& resto) 
    { 
      __asm__ ("xorq %[_resto], %[_resto];"
               "shldq %%cl, %[_arg1], %[_resto]; "
               "shlq %%cl, %[_arg1];"  
          : "=r" (arg1), [_resto] "=r" (resto) 
          : [_arg1] "0" (arg1), "c" (arg2), "1" (resto)
          ); 

      return arg1; 
    }

    inline Digit Shiftlr(Digit arg1,Digit arg2, Digit& resto) 
    { 
      __asm__ ("xorq %[_resto], %[_resto];"
               "shrdq %%cl, %[_arg1], %[_resto];"
               "shrq %%cl, %[_arg1]" 
          : "=r" (arg1), [_resto] "=r" (resto) 
          : [_arg1] "0" (arg1), "c" (arg2), "1" (resto)
          ); 

      return arg1; 
    }

    inline Digit Mnob(Digit arg1) 
    {
      Digit ret;
      if( arg1 == 0 ){
        return 1;
      }
      else{
        __asm__ (" bsrq %[_arg1], %[_ret]; " 
                 " incq %[_ret]; "
            : [_ret] "=r" (ret) 
            : [_arg1] "rm" (arg1) 
            ); 

        return ret; 
      }
    }
  }
}

#endif
