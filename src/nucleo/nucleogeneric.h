/* 
 * $Id$
 */


  /******************************************************************
   *                                                                 *
   *          IMPLEMENTACIÓN PARA ARQUITECTURA GENERICA              *
   *                                                                 *
   ******************************************************************/ 
  /** Constructor por defecto de la Cpu Básica para generic */
  template<>
    inline vCPUBasica<Arch::generic>::vCPUBasica()
      : overflow(0), resto(0)
    {}
 

  /** Suma básica de dos Cifras para generic.
   *
   * @sa Add(Cifra arg1, Cifra arg2)
   */
  template<>
    inline Cifra vCPUBasica<Arch::generic>::Add(Cifra arg1, Cifra arg2)
    {
      Cifra ret; 

      ret = arg1 + arg2;
      if( ret < arg1 )
        overflow = 1;
      else
        overflow = 0;

      return ret; 
    }

  /** Suma básica extendida de dos Cifras para generic.
   *
   * @sa Addx(Cifra arg1, Cifra arg2)
   */
  template<>
    inline Cifra vCPUBasica<Arch::generic>::Addx(Cifra arg1, Cifra arg2) 
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


  /** Resta básica de dos Cifras para generic.
   *
   * @sa Sub(Cifra arg1, Cifra arg2)
   */
  template<>
    inline Cifra vCPUBasica<Arch::generic>::Sub(Cifra arg1, Cifra arg2) 
    { 
      Cifra ret; 
//     __asm__ ("xor %[_of], %[_of];"
//               "subl %[_arg2], %[_arg1];"
//               "adcl $0, %[_of]; " 
//          : "=r" (ret), [_of] "=r" (overflow) 
//          : [_arg1] "0" (arg1), [_arg2] "g" (arg2)
//          : "cc" /* modificamos eflags */
//          ); 
//
        if( arg2 > arg1 )
          overflow = 1;
        else
          overflow = 0;
       ret = arg1-arg2;
     
      return ret; 
    }
  /** Resta básica extendida de dos Cifras para generic.
   *
   * @sa Subx(Cifra arg1, Cifra arg2)
   */
  template<>
    inline Cifra vCPUBasica<Arch::generic>::Subx(Cifra arg1, Cifra arg2) 
    { 
      Cifra ret; 
      ret = arg1-arg2;

//        __asm__ ("btr $0, %[_of];" /* pone CF al valor del bit 0 de overflow */
//               "sbbl %[_arg2], %[_arg1];"
//               "adcl $0, %[_of];" 
//          : "=r" (ret), [_of] "=r" (overflow) 
//          : [_arg1] "0" (arg1), [_arg2] "g" (arg2), "1" (overflow) 
//          : "cc" /* modificamos eflags */
//          );

      if( overflow ){
        if ( arg1 > arg2 )
          overflow = 0;
        //no hay else, el overflow seguiria siendo 1
        ret--;
      } 
      else //overflow == 0
        if( arg2 > arg1 )
          overflow = 1;
 

      return ret; 
    }

  /** Producto de dos Cifras para generic.
   *
   * @sa Mul(Cifra arg1,Cifra arg2)
   */
  template<>
    inline Cifra vCPUBasica<Arch::generic>::Mul(Cifra arg1,Cifra arg2) 
    { 
      Cifra ret; 

//      __asm__ (" mull %[_arg2]" 
//          : "=a" (ret), "=d" (resto) 
//          : [_arg1] "0" (arg1), [_arg2] "rm" (arg2)
//          ); 

      Cifra arg1_1, arg1_2;
      Cifra arg2_1, arg2_2;

      Cifra temp1,temp2,temp3,temp4;

      arg1_1 = arg1 & ((Constantes::CIFRA_MAX >> 1)-1);
      arg1_2 = ( arg1 >> (Constantes::BITS_EN_CIFRA >> 1));
 
      arg2_1 = arg2 & ((Constantes::CIFRA_MAX >> 1)-1);
      arg2_2 = ( arg2 >> (Constantes::BITS_EN_CIFRA >> 1));

      temp1 = arg1_1 * arg2_1;
      temp2 = arg1_1 * arg2_2;
      temp3 = arg1_2 * arg2_1;
      temp4 = arg1_2 * arg2_2;
      
      arg1_1 = temp1 & ((Constantes::CIFRA_MAX >> 1)-1);
      arg1_2 = ( temp1 >> (Constantes::BITS_EN_CIFRA >> 1));
      
      arg2_1 = temp2 & ((Constantes::CIFRA_MAX >> 1)-1);
      arg2_2 = ( temp2 >> (Constantes::BITS_EN_CIFRA >> 1));
     
      arg2_1 <<= (Constantes::BITS_EN_CIFRA >> 1);
      temp1 = Add(temp1, arg2_1);
      temp2 = Addx(0, arg2_2);
      

      ///////////////
      
      arg1_1 = temp3 & ((Constantes::CIFRA_MAX >> 1)-1);
      arg1_2 = ( temp3 >> (Constantes::BITS_EN_CIFRA >> 1));
      
      arg2_1 = temp4 & ((Constantes::CIFRA_MAX >> 1)-1);
      arg2_2 = ( temp4 >> (Constantes::BITS_EN_CIFRA >> 1));
     
      arg2_1 <<= (Constantes::BITS_EN_CIFRA >> 1);
      temp3 = Add(temp3, arg2_1);
      temp4 = Addx(0, arg2_2);

      
      
      
      return ret; 
    }

  /** Producto de dos Cifras con suma para generic.
   *
   * @sa Addmul(Cifra arg1,Cifra arg2) 
   */
  template<>
    inline Cifra vCPUBasica<Arch::generic>::Addmul(Cifra arg1,Cifra arg2) 
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

  /** Cociente y resto de dos Cifras para generic. 
   *
   * @sa Div(Cifra arg1, Cifra arg2)
   */
   template<>
    inline Cifra vCPUBasica<Arch::generic>::Div(Cifra arg1, Cifra arg2) 
    { 
      Cifra ret; 
      __asm__ (" divl %[_arg2]" 
          : "=a" (ret), "=d" (resto) 
          : [_arg1] "0" (arg1), [_arg2] "g" (arg2), "1" (resto)
          ); 

      return ret;
    }


   /** Desplazamiento de bits a la izquierda para generic.
    *
    *  @sa Shiftl(Cifra arg1,Cifra arg2)
    */
  template<>
    inline Cifra vCPUBasica<Arch::generic>::Shiftl(Cifra arg1,Cifra arg2) 
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

  /** Desplazamiento de bits de la derecha para generic.
   *
   * @sa Shiftlr(Cifra arg1,Cifra arg2)
   */
  template<>
    inline Cifra vCPUBasica<Arch::generic>::Shiftlr(Cifra arg1,Cifra arg2) 
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

  /** Encabezado de ceros para generic.
   *
   * @sa Bfffo(Cifra arg1) 
   */
  template<>
    inline Cifra vCPUBasica<Arch::generic>::Bfffo(Cifra arg1) 
    {
      Cifra ret = (Constantes::BITS_EN_CIFRA-1), temp; 

      if( (arg1) != (0))  { 
//        __asm__ (" bsrl %[_arg1], %[_temp]; " 
//            : [_temp] "=r" (temp) 
//            : [_arg1] "g" (arg1) 
//            ); 
        ret -= temp; 
      }
      else ret++; 

      return ret; 
    }

  /** Función de perfilado en generic (inválido).
   *
   * Invicar esta función produce que se lance una excepción de tipo 
   * Errores::ArchNoProfiling
   */
  template<>
    inline void vCPUBasica<Arch::generic>::reiniciarContadores(void)
    {
      throw Errores::ArchNoProfiling();
    }

   /** Función de perfilado en generic (inválido).
   *
   * Invicar esta función produce que se lance una excepción de tipo 
   * Errores::ArchNoProfiling
   */
 template<>
    inline void vCPUBasica<Arch::generic>::inicioProf(void)
    {
      throw Errores::ArchNoProfiling();
    }

   /** Función de perfilado en generic (inválido).
   *
   * Invicar esta función produce que se lance una excepción de tipo 
   * Errores::ArchNoProfiling
   */
 template<>
    inline void vCPUBasica<Arch::generic>::finProf(void)
    {
      throw Errores::ArchNoProfiling();
    }

   /** Función de perfilado en generic (inválido).
   *
   * Invicar esta función produce que se lance una excepción de tipo 
   * Errores::ArchNoProfiling
   */
 template<>
    inline ResultadosProf vCPUBasica<Arch::generic>::obtenerPerfil(void)
    {
      throw Errores::ArchNoProfiling();
    }


