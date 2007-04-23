/* 
 * $Id$
 */

  /******************************************************************
   *                                                                 *
   *               IMPLEMENTACI�N PARA ARQUITECTURA X86              *
   *                                                                 *
   ******************************************************************/ 
 

  /** Suma b�sica de dos Digits para x86.
   *
   * @sa Add(Digit arg1, Digit arg2)
   */
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

  /** Suma b�sica extendida de dos Digits para x86.
   *
   * @sa Addx(Digit arg1, Digit arg2)
   */
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


  /** Resta b�sica de dos Digits para x86.
   *
   * @sa Sub(Digit arg1, Digit arg2)
   */
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
  /** Resta b�sica extendida de dos Digits para x86.
   *
   * @sa Subx(Digit arg1, Digit arg2)
   */
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

  /** Producto de dos Digits para x86.
   *
   * @sa Mul(Digit arg1,Digit arg2)
   */
    inline Digit Mul(Digit arg1,Digit arg2, Digit& resto) 
    { 
      __asm__ (" mull %[_arg2]" 
          : "=a" (arg1), "=d" (resto) 
          : [_arg1] "0" (arg1), [_arg2] "rm" (arg2)
          ); 

      return arg1; 
    }

  /** Producto de dos Digits con suma para x86.
   *
   * @sa Addmul(Digit arg1,Digit arg2) 
   */
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

  /** Cociente y resto de dos Digits para x86. 
   *
   * @sa Div(Digit arg1, Digit arg2)
   */
    inline Digit Div(Digit arg1, Digit arg2, Digit& resto) 
    { 
      __asm__ (" divl %[_arg2]" 
          : "=a" (arg1), "=d" (resto) 
          : [_arg1] "0" (arg1), [_arg2] "g" (arg2), "1" (resto)
          ); 

      return arg1;
    }


   /** Desplazamiento de bits a la izquierda para x86.
    *
    *  @sa Shiftl(Digit arg1,Digit arg2)
    */
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

  /** Desplazamiento de bits de la derecha para x86.
   *
   * @sa Shiftlr(Digit arg1,Digit arg2)
   */
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

  /** Encabezado de ceros para x86.
   *
   * @sa Bfffo(Digit arg1) 
   */
    inline Digit Bfffo(Digit arg1) 
    {
      Digit ret;
      if( arg1 == 0 ){
        return 1;
      }
      else{
        __asm__ (" bsrl %[_arg1], %[_ret]; \n\t" 
                 " incl %[_ret]; \n\t"
            : [_ret] "=r" (ret) 
            : [_arg1] "rm" (arg1) 
            ); 

        return ret; 
      }
    }



