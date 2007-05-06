/* 
 * $Id$
 */
#ifdef ARCH_x86
namespace mpplas{

  namespace BasicCPU{

   /**********************************
   *   IMPLEMENTATION FOR X86
   **********************************/ 


    inline Digit Add(Digit arg1, Digit arg2, Digit& overflow)
    {
      __asm__ ("xor %[_of], %[_of];"
               "addl %[_arg2], %[_arg1]; "
               "adcl $0, %[_of]; "
          : "=r" (arg1), [_of] "=r" (overflow)
          : [_arg1] "0" (arg1), [_arg2] "g" (arg2), "1" (overflow)
          : "cc" /* modificamos eflags */
          );

      return arg1; 
    }

    inline Digit Addx(Digit arg1, Digit arg2, Digit& overflow) 
    { 
      __asm__ ("btr $0, %[_of];"
               "adcl %[_arg2], %[_arg1];" 
               "adcl $0, %[_of]; "
          : "=r" (arg1), [_of] "=r" (overflow) 
          : [_arg1] "0" (arg1), [_arg2] "g" (arg2), "1" (overflow) 
          : "cc" /* modificamos eflags */
          );

      return arg1; 
    }


    inline Digit Sub(Digit arg1, Digit arg2, Digit& overflow) 
    { 
      __asm__ ("xor %[_of], %[_of];"
               "subl %[_arg2], %[_arg1];"
               "adcl $0, %[_of]; " 
          : "=r" (arg1), [_of] "=r" (overflow) 
          : [_arg1] "0" (arg1), [_arg2] "g" (arg2)
          : "cc" /* modificamos eflags */
          ); 

      return arg1; 
    }
    inline Digit Subx(Digit arg1, Digit arg2, Digit& overflow) 
    { 
      __asm__ ("btr $0, %[_of];" /* pone CF al valor del bit 0 de overflow */
               "sbbl %[_arg2], %[_arg1];"
               "adcl $0, %[_of];" 
          : "=r" (arg1), [_of] "=r" (overflow) 
          : [_arg1] "0" (arg1), [_arg2] "g" (arg2), "1" (overflow) 
          : "cc" /* modificamos eflags */
          );
      return arg1; 
    }

    inline Digit Mul(Digit arg1,Digit arg2, Digit& resto) 
    { 
      __asm__ (" mull %[_arg2]" 
          : "=a" (arg1), "=d" (resto) 
          : [_arg1] "0" (arg1), [_arg2] "rm" (arg2)
          ); 

      return arg1; 
    }

    inline Digit Addmul(Digit arg1,Digit arg2, Digit& resto) 
    { 
      __asm__ (" mull %[_arg2];"
               "addl %[_restoViejo],%[_ret];" 
               "adcl $0, %%edx;"      
          : [_ret] "=a" (arg1), "=&d" (resto) 
          : [_arg1] "0" (arg1), [_arg2] "rm" (arg2), [_restoViejo] "g" (resto) 
          ); 

      return arg1; 
    }

    inline Digit Div(Digit arg1, Digit arg2, Digit& resto) 
    { 
      __asm__ (" divl %[_arg2]" 
          : "=a" (arg1), "=d" (resto) 
          : [_arg1] "0" (arg1), [_arg2] "g" (arg2), "1" (resto)
          ); 

      return arg1;
    }


    inline Digit Shiftl(Digit arg1,Digit arg2, Digit& resto) 
    { 
      __asm__ ("xor %[_resto], %[_resto];"
               "shldl %%cl, %[_arg1], %[_resto]; "
               "shll %%cl, %[_arg1];"  
          : "=r" (arg1), [_resto] "=r" (resto) 
          : [_arg1] "0" (arg1), "c" (arg2), "1" (resto)
          ); 

      return arg1; 
    }

    inline Digit Shiftlr(Digit arg1,Digit arg2, Digit& resto) 
    { 
      __asm__ ("xor %[_resto], %[_resto];"
               "shrdl %%cl, %[_arg1], %[_resto];"
               "shrl %%cl, %[_arg1]" 
          : "=r" (arg1), [_resto] "=r" (resto) 
          : [_arg1] "0" (arg1), "c" (arg2), "1" (resto)
          ); 

      return arg1; 
    }

    inline Digit Mnob(Digit arg) 
    {
      Digit ret;
      if( arg == 0 ){
        return 1;
      }
      else{
        __asm__ (" bsrl %[_arg], %[_ret]; \n\t" 
                 " incl %[_ret]; \n\t"
            : [_ret] "=r" (ret) 
            : [_arg] "rm" (arg) 
            ); 

        return ret; 
      }
    }
  }
}

#endif
