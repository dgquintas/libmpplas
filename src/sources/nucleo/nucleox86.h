/* 
 * $Id$
 */


  /******************************************************************
   *                                                                 *
   *               IMPLEMENTACIÓN PARA ARQUITECTURA X86              *
   *                                                                 *
   ******************************************************************/ 
  /** Constructor por defecto de la Cpu Básica para x86 */
  template<>
    inline vCPUBasica<Arch::x86>::vCPUBasica()
      : overflow(0), resto(0)
    {}
 

  /** Suma básica de dos Cifras para x86.
   *
   * @sa Add(Cifra arg1, Cifra arg2)
   */
  template<>
    inline Cifra vCPUBasica<Arch::x86>::Add(Cifra arg1, Cifra arg2)
    {
      Cifra ret; 

      __asm__ ("xor %[_of], %[_of];"
               "addl %[_arg2], %[_arg1]; "
               "adcl $0, %[_of]; "
          : "=r" (ret), [_of] "=r" (overflow)
          : [_arg1] "0" (arg1), [_arg2] "g" (arg2), "1" (overflow)
          : "cc" /* modificamos eflags */
          );

      return ret; 
    }

  /** Suma básica extendida de dos Cifras para x86.
   *
   * @sa Addx(Cifra arg1, Cifra arg2)
   */
  template<>
    inline Cifra vCPUBasica<Arch::x86>::Addx(Cifra arg1, Cifra arg2) 
    { 
      Cifra ret; 

      __asm__ ("btr $0, %[_of];"
               "adcl %[_arg2], %[_arg1];" 
               "adcl $0, %[_of]; "
          : "=r" (ret), [_of] "=r" (overflow) 
          : [_arg1] "0" (arg1), [_arg2] "g" (arg2), "1" (overflow) 
          : "cc" /* modificamos eflags */
          );

      return ret; 
    }


  /** Resta básica de dos Cifras para x86.
   *
   * @sa Sub(Cifra arg1, Cifra arg2)
   */
  template<>
    inline Cifra vCPUBasica<Arch::x86>::Sub(Cifra arg1, Cifra arg2) 
    { 
      Cifra ret; 

      __asm__ ("xor %[_of], %[_of];"
               "subl %[_arg2], %[_arg1];"
               "adcl $0, %[_of]; " 
          : "=r" (ret), [_of] "=r" (overflow) 
          : [_arg1] "0" (arg1), [_arg2] "g" (arg2)
          : "cc" /* modificamos eflags */
          ); 

      return ret; 
    }
  /** Resta básica extendida de dos Cifras para x86.
   *
   * @sa Subx(Cifra arg1, Cifra arg2)
   */
  template<>
    inline Cifra vCPUBasica<Arch::x86>::Subx(Cifra arg1, Cifra arg2) 
    { 
      Cifra ret; 
      __asm__ ("btr $0, %[_of];" /* pone CF al valor del bit 0 de overflow */
               "sbbl %[_arg2], %[_arg1];"
               "adcl $0, %[_of];" 
          : "=r" (ret), [_of] "=r" (overflow) 
          : [_arg1] "0" (arg1), [_arg2] "g" (arg2), "1" (overflow) 
          : "cc" /* modificamos eflags */
          );
      return ret; 
    }

  /** Producto de dos Cifras para x86.
   *
   * @sa Mul(Cifra arg1,Cifra arg2)
   */
  template<>
    inline Cifra vCPUBasica<Arch::x86>::Mul(Cifra arg1,Cifra arg2) 
    { 
      Cifra ret; 

      __asm__ (" mull %[_arg2]" 
          : "=a" (ret), "=d" (resto) 
          : [_arg1] "0" (arg1), [_arg2] "rm" (arg2)
          ); 

      return ret; 
    }

  /** Producto de dos Cifras con suma para x86.
   *
   * @sa Addmul(Cifra arg1,Cifra arg2) 
   */
  template<>
    inline Cifra vCPUBasica<Arch::x86>::Addmul(Cifra arg1,Cifra arg2) 
    { 
      Cifra ret; 

      __asm__ (" mull %[_arg2];"
               "addl %[_restoViejo],%[_ret];" 
               "adcl $0, %%edx;"      
          : [_ret] "=a" (ret), "=&d" (resto) 
          : [_arg1] "0" (arg1), [_arg2] "rm" (arg2), [_restoViejo] "g" (resto) 
          ); 

      return ret; 
    }

  /** Cociente y resto de dos Cifras para x86. 
   *
   * @sa Div(Cifra arg1, Cifra arg2)
   */
   template<>
    inline Cifra vCPUBasica<Arch::x86>::Div(Cifra arg1, Cifra arg2) 
    { 
      Cifra ret; 
      __asm__ (" divl %[_arg2]" 
          : "=a" (ret), "=d" (resto) 
          : [_arg1] "0" (arg1), [_arg2] "g" (arg2), "1" (resto)
          ); 

      return ret;
    }


   /** Desplazamiento de bits a la izquierda para x86.
    *
    *  @sa Shiftl(Cifra arg1,Cifra arg2)
    */
  template<>
    inline Cifra vCPUBasica<Arch::x86>::Shiftl(Cifra arg1,Cifra arg2) 
    { 
      Cifra ret;

      __asm__ ("xor %[_resto], %[_resto];"
               "shldl %%cl, %[_arg1], %[_resto]; "
               "shll %%cl, %[_arg1];"  
          : "=r" (ret), [_resto] "=r" (resto) 
          : [_arg1] "0" (arg1), "c" (arg2), "1" (resto)
          ); 

      return ret; 
    }

  /** Desplazamiento de bits de la derecha para x86.
   *
   * @sa Shiftlr(Cifra arg1,Cifra arg2)
   */
  template<>
    inline Cifra vCPUBasica<Arch::x86>::Shiftlr(Cifra arg1,Cifra arg2) 
    { 
      Cifra ret;

      __asm__ ("xor %[_resto], %[_resto];"
               "shrdl %%cl, %[_arg1], %[_resto];"
               "shrl %%cl, %[_arg1]" 
          : "=r" (ret), [_resto] "=r" (resto) 
          : [_arg1] "0" (arg1), "c" (arg2), "1" (resto)
          ); 

      return ret; 
    }

  /** Encabezado de ceros para x86.
   *
   * @sa Bfffo(Cifra arg1) 
   */
  template<>
    inline Cifra vCPUBasica<Arch::x86>::Bfffo(Cifra arg1) 
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

  /** Función de perfilado en x86 (inválido).
   *
   * Invicar esta función produce que se lance una excepción de tipo 
   * Errores::ArchNoProfiling
   */
  template<>
    inline void vCPUBasica<Arch::x86>::reiniciarContadores(void)
    {
      throw Errores::ArchNoProfiling();
    }

   /** Función de perfilado en x86 (inválido).
   *
   * Invicar esta función produce que se lance una excepción de tipo 
   * Errores::ArchNoProfiling
   */
 template<>
    inline void vCPUBasica<Arch::x86>::inicioProf(void)
    {
      throw Errores::ArchNoProfiling();
    }

   /** Función de perfilado en x86 (inválido).
   *
   * Invicar esta función produce que se lance una excepción de tipo 
   * Errores::ArchNoProfiling
   */
 template<>
    inline void vCPUBasica<Arch::x86>::finProf(void)
    {
      throw Errores::ArchNoProfiling();
    }

   /** Función de perfilado en x86 (inválido).
   *
   * Invicar esta función produce que se lance una excepción de tipo 
   * Errores::ArchNoProfiling
   */
 template<>
    inline ResultadosProf vCPUBasica<Arch::x86>::obtenerPerfil(void)
    {
      throw Errores::ArchNoProfiling();
    }


