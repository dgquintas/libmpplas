/* 
 * $Id$
 */


  /******************************************************************
   *                                                                 *
   *               IMPLEMENTACI�N PARA ARQUITECTURA X86              *
   *                                                                 *
   ******************************************************************/ 
 

  /** Suma b�sica de dos Cifras para x86.
   *
   * @sa Add(Cifra arg1, Cifra arg2)
   */
    inline Cifra Add(Cifra arg1, Cifra arg2, Cifra& overflow)
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

  /** Suma b�sica extendida de dos Cifras para x86.
   *
   * @sa Addx(Cifra arg1, Cifra arg2)
   */
    inline Cifra Addx(Cifra arg1, Cifra arg2, Cifra& overflow) 
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


  /** Resta b�sica de dos Cifras para x86.
   *
   * @sa Sub(Cifra arg1, Cifra arg2)
   */
    inline Cifra Sub(Cifra arg1, Cifra arg2, Cifra& overflow) 
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
  /** Resta b�sica extendida de dos Cifras para x86.
   *
   * @sa Subx(Cifra arg1, Cifra arg2)
   */
    inline Cifra Subx(Cifra arg1, Cifra arg2, Cifra& overflow) 
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

  /** Producto de dos Cifras para x86.
   *
   * @sa Mul(Cifra arg1,Cifra arg2)
   */
    inline Cifra Mul(Cifra arg1,Cifra arg2, Cifra& resto) 
    { 
      __asm__ (" mull %[_arg2]" 
          : "=a" (arg1), "=d" (resto) 
          : [_arg1] "0" (arg1), [_arg2] "rm" (arg2)
          ); 

      return arg1; 
    }

  /** Producto de dos Cifras con suma para x86.
   *
   * @sa Addmul(Cifra arg1,Cifra arg2) 
   */
    inline Cifra Addmul(Cifra arg1,Cifra arg2, Cifra& resto) 
    { 
      __asm__ (" mull %[_arg2];"
               "addl %[_restoViejo],%[_ret];" 
               "adcl $0, %%edx;"      
          : [_ret] "=a" (arg1), "=&d" (resto) 
          : [_arg1] "0" (arg1), [_arg2] "rm" (arg2), [_restoViejo] "g" (resto) 
          ); 

      return arg1; 
    }

  /** Cociente y resto de dos Cifras para x86. 
   *
   * @sa Div(Cifra arg1, Cifra arg2)
   */
    inline Cifra Div(Cifra arg1, Cifra arg2, Cifra& resto) 
    { 
      __asm__ (" divl %[_arg2]" 
          : "=a" (arg1), "=d" (resto) 
          : [_arg1] "0" (arg1), [_arg2] "g" (arg2), "1" (resto)
          ); 

      return arg1;
    }


   /** Desplazamiento de bits a la izquierda para x86.
    *
    *  @sa Shiftl(Cifra arg1,Cifra arg2)
    */
    inline Cifra Shiftl(Cifra arg1,Cifra arg2, Cifra& resto) 
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
   * @sa Shiftlr(Cifra arg1,Cifra arg2)
   */
    inline Cifra Shiftlr(Cifra arg1,Cifra arg2, Cifra& resto) 
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
   * @sa Bfffo(Cifra arg1) 
   */
    inline Cifra Bfffo(Cifra arg1) 
    {
      Cifra ret = (Constantes::BITS_EN_CIFRA-1), temp; 

      if( (arg1) != (0))  { 
        __asm__ (" bsrl %[_arg1], %[_temp]; " 
            : [_temp] "=r" (temp) 
            : [_arg1] "g" (arg1) 
            ); 
        ret -= temp; 
      }
      else ret++; 

      return ret; 
    }



