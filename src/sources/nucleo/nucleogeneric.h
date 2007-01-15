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
      const Cifra ret = arg1 + arg2;
      overflow = ( ret < arg1 );
      return ret; 
    }

  /** Suma básica extendida de dos Cifras para generic.
   *
   * @sa Addx(Cifra arg1, Cifra arg2)
   */
  template<>
    inline Cifra vCPUBasica<Arch::generic>::Addx(Cifra arg1, Cifra arg2) 
    { 
      const Cifra ret = arg1 + arg2 + overflow;
      overflow = (ret < arg1 || (ret==arg1 && overflow));
      return ret; 
    }


  /** Resta básica de dos Cifras para generic.
   *
   * @sa Sub(Cifra arg1, Cifra arg2)
   */
  template<>
    inline Cifra vCPUBasica<Arch::generic>::Sub(Cifra arg1, Cifra arg2) 
    { 
      const Cifra ret = arg1-arg2;
      overflow = ( ret > arg1 );
      return ret; 
    }
  /** Resta básica extendida de dos Cifras para generic.
   *
   * @sa Subx(Cifra arg1, Cifra arg2)
   */
  template<>
    inline Cifra vCPUBasica<Arch::generic>::Subx(Cifra arg1, Cifra arg2) 
    { 
      const Cifra ret = arg1-arg2-overflow;
      overflow = (ret > arg1 || (ret == arg1 && overflow) );

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

//      Cifra arg1_1, arg1_2;
//      Cifra arg2_1, arg2_2;
//
//      Cifra temp1,temp2,temp3,temp4;
//
//      arg1_1 = arg1 & ((Constantes::CIFRA_MAX >> 1)-1);
//      arg1_2 = ( arg1 >> (Constantes::BITS_EN_CIFRA >> 1));
// 
//      arg2_1 = arg2 & ((Constantes::CIFRA_MAX >> 1)-1);
//      arg2_2 = ( arg2 >> (Constantes::BITS_EN_CIFRA >> 1));
//
//      temp1 = arg1_1 * arg2_1;
//      temp2 = arg1_1 * arg2_2;
//      temp3 = arg1_2 * arg2_1;
//      temp4 = arg1_2 * arg2_2;
//      
//      arg1_1 = temp1 & ((Constantes::CIFRA_MAX >> 1)-1);
//      arg1_2 = ( temp1 >> (Constantes::BITS_EN_CIFRA >> 1));
//      
//      arg2_1 = temp2 & ((Constantes::CIFRA_MAX >> 1)-1);
//      arg2_2 = ( temp2 >> (Constantes::BITS_EN_CIFRA >> 1));
//     
//      arg2_1 <<= (Constantes::BITS_EN_CIFRA >> 1);
//      temp1 = Add(temp1, arg2_1);
//      temp2 = Addx(0, arg2_2);
//      
//
//      ///////////////
//      
//      arg1_1 = temp3 & ((Constantes::CIFRA_MAX >> 1)-1);
//      arg1_2 = ( temp3 >> (Constantes::BITS_EN_CIFRA >> 1));
//      
//      arg2_1 = temp4 & ((Constantes::CIFRA_MAX >> 1)-1);
//      arg2_2 = ( temp4 >> (Constantes::BITS_EN_CIFRA >> 1));
//     
//      arg2_1 <<= (Constantes::BITS_EN_CIFRA >> 1);
//      temp3 = Add(temp3, arg2_1);
//      temp4 = Addx(0, arg2_2);

      
      uint64_t res = arg1;
      res *= arg2;

      resto = ((res>> 32) & Constantes::CIFRA_MAX );
      ret = res & (Constantes::CIFRA_MAX) ;

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
      resto = arg1 >> (Constantes::BITS_EN_CIFRA-arg2);
      return (arg1 << arg2) ; 
    }

  /** Desplazamiento de bits de la derecha para generic.
   *
   * @sa Shiftlr(Cifra arg1,Cifra arg2)
   */
  template<>
    inline Cifra vCPUBasica<Arch::generic>::Shiftlr(Cifra arg1,Cifra arg2) 
    { 
      resto = arg1 << (Constantes::BITS_EN_CIFRA-arg2);
      return (arg1 >> arg2);
    }

  /** Encabezado de ceros para generic.
   *
   * @sa Bfffo(Cifra arg1) 
   */
  template<>
    inline Cifra vCPUBasica<Arch::generic>::Bfffo(Cifra arg1) 
    {
      int res = Constantes::BITS_EN_CIFRA;

      static const Cifra masks[] = { 0x2, 0xc, 0xf0, 0xff00, 0xffff0000 }; //FIXME:generate at compiletime

      if( arg1 & masks[4] ){
        arg1 >>= 16;
        res -= 16;
      }
      if( arg1 & masks[3] ){
        arg1 >>= 8;
        res -= 8;
      }
      if( arg1 & masks[2] ){
        arg1 >>= 4;
        res -= 4;
      }
      if(arg1 & masks[1] ){
        arg1 >>= 2;
        res -= 2;
      }
      switch(arg1){
        case 3:
        case 2:
          return res -2 ;
        case 1:
          return res - 1;
        case 0:
          return res ;
      }
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


