
   /******************************************************************
   *                                                                 *
   *             IMPLEMENTACIÓN PARA ARQUITECTURA X86-Prof           *
   *                                                                 *
   ******************************************************************/ 
  /** Constructor por defecto de la Cpu Básica para x86 con soporte de
   * perfilado. */
  template<>
    inline vCPUBasica<Arch::x86Prof>::vCPUBasica()
      : overflow(0), resto(0)
    {}
  
  
  /** Suma básica de dos Cifras para x86 con soporte de perfilado.
   *
   * @sa Add(Cifra arg1, Cifra arg2)
   */
  template<>
    inline Cifra vCPUBasica<Arch::x86Prof>::Add(Cifra arg1, Cifra arg2)
    {
      Cifra ret; 
      resultadosProf_.n_operaciones[Operaciones::Add]++;

      __asm__ ("xor %[_of], %[_of];"
               "addl %[_arg2], %[_arg1]; "
               "adcl $0, %[_of]; "
          : "=r" (ret), [_of] "=r" (overflow)
          : [_arg1] "0" (arg1), [_arg2] "g" (arg2), "1" (overflow)
          : "cc" /* modificamos eflags */
          );

      return ret; 
    }

  /** Suma básica extendida de dos Cifras para x86 con soporte de
   * perfilado.
   *
   * @sa Addx(Cifra arg1, Cifra arg2)
   */
  template<>
    inline Cifra vCPUBasica<Arch::x86Prof>::Addx(Cifra arg1, Cifra arg2) 
    { 
      Cifra ret; 
      resultadosProf_.n_operaciones[Operaciones::Addx]++;

      __asm__ ("btr $0, %[_of];"
               "adcl %[_arg2], %[_arg1];" 
               "adcl $0, %[_of]; "
          : "=r" (ret), [_of] "=r" (overflow) 
          : [_arg1] "0" (arg1), [_arg2] "g" (arg2), "1" (overflow) 
          : "cc" /* modificamos eflags */
          );

      return ret; 
    }

  /** Resta básica de dos Cifras para x86 con soporte de perfilado.
   *
   * @sa Sub(Cifra arg1, Cifra arg2)
   */
  template<>
    inline Cifra vCPUBasica<Arch::x86Prof>::Sub(Cifra arg1, Cifra arg2) 
    { 
      Cifra ret; 
      resultadosProf_.n_operaciones[Operaciones::Sub]++;

      __asm__ ("xor %[_of], %[_of];"
               "subl %[_arg2], %[_arg1];"
               "adcl $0, %[_of]; " 
          : "=r" (ret), [_of] "=r" (overflow) 
          : [_arg1] "0" (arg1), [_arg2] "g" (arg2)
          : "cc" /* modificamos eflags */
          ); 

      return ret; 
    }
 
  /** Resta básica extendida de dos Cifras para x86 con soporte de
   * perfilado.
   *
   * @sa Subx(Cifra arg1, Cifra arg2)
   */
  template<>
    inline Cifra vCPUBasica<Arch::x86Prof>::Subx(Cifra arg1, Cifra arg2) 
    { 
      Cifra ret; 
      resultadosProf_.n_operaciones[Operaciones::Subx]++;

      __asm__ ("btr $0, %[_of];" /* pone CF al valor del bit 0 de overflow */
               "sbbl %[_arg2], %[_arg1];"
               "adcl $0, %[_of];" 
          : "=r" (ret), [_of] "=r" (overflow) 
          : [_arg1] "0" (arg1), [_arg2] "g" (arg2), "1" (overflow) 
          : "cc" /* modificamos eflags */
          );
      return ret; 
    }

  
  /** Producto de dos Cifras para x86 con soporte de perfilado.
   *
   * @sa Mul(Cifra arg1,Cifra arg2)
   */
  template<>
    inline Cifra vCPUBasica<Arch::x86Prof>::Mul(Cifra arg1,Cifra arg2) 
    { 
      Cifra ret; 
      resultadosProf_.n_operaciones[Operaciones::Mul]++;

      __asm__ (" mull %[_arg2]" 
          : "=a" (ret), "=d" (resto) 
          : [_arg1] "0" (arg1), [_arg2] "rm" (arg2)
          ); 

      return ret; 
    }


  /** Producto de dos Cifras con suma para x86 con soporte de
   * perfilado.
   *
   * @sa Addmul(Cifra arg1,Cifra arg2) 
   */
  template<>
    inline Cifra vCPUBasica<Arch::x86Prof>::Addmul(Cifra arg1,Cifra arg2) 
    { 
      Cifra ret; 
      resultadosProf_.n_operaciones[Operaciones::Addmul]++;

      __asm__ (" mull %[_arg2];"
               "addl %[_restoViejo],%[_ret];" 
               "adcl $0, %%edx;"      
          : [_ret] "=a" (ret), "=&d" (resto) 
          : [_arg1] "0" (arg1), [_arg2] "rm" (arg2), [_restoViejo] "g" (resto) 
          ); 

      return ret; 
    }

  /** Cociente y resto de dos Cifras para x86 con soporte de
   * perfilado.
   *
   * @sa Div(Cifra arg1, Cifra arg2)
   */
  template<>
    inline Cifra vCPUBasica<Arch::x86Prof>::Div(Cifra arg1, Cifra arg2) 
    { 
      Cifra ret; 
      resultadosProf_.n_operaciones[Operaciones::Div]++;

      __asm__ (" divl %[_arg2]" 
          : "=a" (ret), "=d" (resto) 
          : [_arg1] "0" (arg1), [_arg2] "g" (arg2), "1" (resto)
          ); 

      return ret; 
    }


   /** Desplazamiento de bits a la izquierda para x86 con soporte de
    * perfilado.
    *
    *  @sa Shiftl(Cifra arg1,Cifra arg2)
    */
  template<>
    inline Cifra vCPUBasica<Arch::x86Prof>::Shiftl(Cifra arg1,Cifra arg2) 
    { 
      Cifra ret;
      resultadosProf_.n_operaciones[Operaciones::Shiftl]++;

      __asm__ ("xor %[_resto], %[_resto];"
               "shldl %%cl, %[_arg1], %[_resto]; "
               "shll %%cl, %[_arg1];"  
          : "=r" (ret), [_resto] "=r" (resto) 
          : [_arg1] "0" (arg1), "c" (arg2), "1" (resto)
          ); 

      return ret; 
    }


  /** Desplazamiento de bits de la derecha para x86 con soporte de
   * perfilado.
   *
   * @sa Shiftlr(Cifra arg1,Cifra arg2)
   */
  template<>
    inline Cifra vCPUBasica<Arch::x86Prof>::Shiftlr(Cifra arg1,Cifra arg2) 
    { 
      Cifra ret;
      resultadosProf_.n_operaciones[Operaciones::Shiftlr]++;

      __asm__ ("xor %[_resto], %[_resto];"
               "shrdl %%cl, %[_arg1], %[_resto];"
               "shrl %%cl, %[_arg1]" 
          : "=r" (ret), [_resto] "=r" (resto) 
          : [_arg1] "0" (arg1), "c" (arg2), "1" (resto)
          ); 

      return ret; 
    }


  /** Encabezado de ceros para x86 con soporte de perfilado.
   *
   * @sa Bfffo(Cifra arg1) 
   */
  template<>
    inline Cifra vCPUBasica<Arch::x86Prof>::Bfffo(Cifra arg1) 
    {
      Cifra ret = (Constantes::BITS_EN_CIFRA-1), temp; 
      resultadosProf_.n_operaciones[Operaciones::Bfffo]++;

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

  /** Reiniciar contadores.
   *
   * Esta función reinicia los contadores de perfilado.
   */
  template<>
    inline void vCPUBasica<Arch::x86Prof>::reiniciarContadores(void)
    {
      memset(resultadosProf_.n_operaciones,
          (int)0, sizeof(Cifra)*Constantes::NUM_OPERACIONES);
      
      resultadosProf_.ciclos = (clock_t)0;
      
      return;
    }

  /** Comenzar perfilado.
   *
   * Tras la invocación de esta función, se empieza a llevar la cuenta
   * de datos de perfilado.
   */
  template<>
    inline void vCPUBasica<Arch::x86Prof>::inicioProf(void)
    {
      resultadosProf_.ciclos = clock();
      return;
    }

   /** Finalizar perfilado.
   *
   * Tras la invocación de esta función, se deja de llevar la cuenta
   * de datos de perfilado.
   */
  template<>
    inline void vCPUBasica<Arch::x86Prof>::finProf(void)
    {
      resultadosProf_.ciclos = clock() - resultadosProf_.ciclos;
      return;
    }

  /** Obtener perfil.
   *
   * Obtener los datos recogidos en el intervalo de perfilado. Si no
   * ha habido tal intervalo previamente a la invocación de la
   * función, se devuelve una estructura con todos los datos de
   * perfilado a 0.
   *
   * @return Estructura ResultadosProf con los datos de perfilado
   * obtenidos.
   */
  template<>
    inline ResultadosProf vCPUBasica<Arch::x86Prof>::obtenerPerfil(void)
    {
      return resultadosProf_;
    }

