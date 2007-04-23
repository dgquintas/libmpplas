/* 
 * $Id$
 */


  /******************************************************************
   *                                                                 *
   *            IMPLEMENTACI�N PARA ARQUITECTURA X86_64              *
   *                                                                 *
   ******************************************************************/ 

  /** Suma b�sica de dos Digits para x86_64.
   *
   * @sa Add(Digit arg1, Digit arg2)
   */
    inline Digit Add(Digit arg1, Digit arg2, Digit& overflow)
    {
      __asm__ ("xorq %[_of], %[_of];"
               "addq %[_arg2], %[_arg1]; "
               "adcq $0, %[_of]; "
          : "=r" (arg1), [_of] "=r" (overflow)
          : [_arg1] "0" (arg1), [_arg2] "r" (arg2), "1" (overflow)
          : "cc" /* modificamos eflags */
          );

      return arg1; 
    }

  /** Suma b�sica extendida de dos Digits para x86_64.
   *
   * @sa Addx(Digit arg1, Digit arg2)
   */
    inline Digit Addx(Digit arg1, Digit arg2, Digit& overflow) 
    { 
      __asm__ ("btrq $0, %[_of];"
               "adcq %[_arg2], %[_arg1];" 
               "adcq $0, %[_of]; "
          : "=r" (arg1), [_of] "=r" (overflow) 
          : [_arg1] "0" (arg1), [_arg2] "r" (arg2), "1" (overflow) 
          : "cc" /* modificamos eflags */
          );

      return arg1; 
    }


  /** Resta b�sica de dos Digits para x86_64.
   *
   * @sa Sub(Digit arg1, Digit arg2)
   */
    inline Digit Sub(Digit arg1, Digit arg2, Digit& overflow) 
    { 
      __asm__  ("xorq %[_of], %[_of];"
               "subq %[_arg2], %[_arg1];"
               "adcq $0, %[_of]; " 
          : "=r" (arg1), [_of] "=r" (overflow) 
          : [_arg1] "0" (arg1), [_arg2] "rm" (arg2)
          : "cc" /* modificamos eflags */
          ); 

      return arg1; 
    }
  /** Resta b�sica extendida de dos Digits para x86_64.
   *
   * @sa Subx(Digit arg1, Digit arg2)
   */
    inline Digit Subx(Digit arg1, Digit arg2, Digit& overflow) 
    { 
      __asm__  ("btrq $0, %[_of];" /* pone CF al valor del bit 0 de overflow */
               "sbbq %[_arg2], %[_arg1];"
               "adcq $0, %[_of];" 
          : "=r" (arg1), [_of] "=r" (overflow) 
          : [_arg1] "0" (arg1), [_arg2] "rm" (arg2), "1" (overflow) 
          : "cc" /* modificamos eflags */
          );
      return arg1; 
    }

  /** Producto de dos Digits para x86_64.
   *
   * @sa Mul(Digit arg1,Digit arg2)
   */
    inline Digit Mul(Digit arg1,Digit arg2, Digit& resto) 
    { 
      __asm__ (" mulq %[_arg2]" 
          : "=a" (arg1), "=d" (resto) 
          : [_arg1] "0" (arg1), [_arg2] "rm" (arg2)
          ); 

      return arg1; 
    }

  /** Producto de dos Digits con suma para x86_64.
   *
   * @sa Addmul(Digit arg1,Digit arg2) 
   */
    inline Digit Addmul(Digit arg1,Digit arg2, Digit& resto) 
    { 
      __asm__ (" mulq %[_arg2];"
               "addq %[_restoViejo],%[_ret];" 
               "adcq $0, %%rdx;"      
          : [_ret] "=a" (arg1), "=&d" (resto) 
          : [_arg1] "0" (arg1), [_arg2] "rm" (arg2), [_restoViejo] "rm" (resto) 
          ); 

      return arg1; 
    }

  /** Cociente y resto de dos Digits para x86_64. 
   *
   * @sa Div(Digit arg1, Digit arg2)
   */
    inline Digit Div(Digit arg1, Digit arg2, Digit& resto) 
    { 
      __asm__ (" divq %[_arg2]" 
          : "=a" (arg1), "=d" (resto) 
          : [_arg1] "0" (arg1), [_arg2] "r" (arg2), "1" (resto)
          ); 

      return arg1;
    }


   /** Desplazamiento de bits a la izquierda para x86_64.
    *
    *  @sa Shiftl(Digit arg1,Digit arg2)
    */
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

  /** Desplazamiento de bits de la derecha para x86_64.
   *
   * @sa Shiftlr(Digit arg1,Digit arg2)
   */
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

  /** Encabezado de ceros para x86_64.
   *
   * @sa Bfffo(Digit arg1) 
   */
    inline Digit Bfffo(Digit arg1) 
    {
      Cifra ret;
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



