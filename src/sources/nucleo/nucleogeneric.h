/* 
 * $Id$
 */

inline Cifra HIGHHALF(Cifra x) { return (x >> Constantes::BITS_IN_HALFCIFRA); }
inline Cifra LOWHALF(Cifra x) { return (x & Constantes::MASK_CIFRALOW); }


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
      // based on pari-gp's implementation by Peter Montgomery
      const Cifra xlo = LOWHALF(arg1), xhi = HIGHHALF(arg1);
      const Cifra ylo = LOWHALF(arg2), yhi = HIGHHALF(arg2);
      Cifra xylo,xymid,xyhi,xymidhi,xymidlo;
      Cifra xhl,yhl;

      xylo = xlo*ylo; xyhi = xhi*yhi;
      xhl = xhi+xlo; yhl = yhi+ylo;
      xymid = xhl*yhl - (xyhi+xylo);

      xymidhi = HIGHHALF(xymid);
      xymidlo = xymid << Constantes::BITS_IN_HALFCIFRA;

      xylo += xymidlo;
      resto = xyhi + xymidhi + (xylo < xymidlo)
         + ((((xhl + yhl) >> 1) - xymidhi) & Constantes::MASK_CIFRAHIGH);

      return xylo;
    }

  /** Producto de dos Cifras con suma para generic.
   *
   * @sa Addmul(Cifra arg1,Cifra arg2) 
   */
  template<>
    inline Cifra vCPUBasica<Arch::generic>::Addmul(Cifra arg1,Cifra arg2) 
    { 
      // based on pari-gp's implementation by Peter Montgomery
        const Cifra xlo = LOWHALF(arg1), xhi = HIGHHALF(arg1);
        const Cifra ylo = LOWHALF(arg2), yhi = HIGHHALF(arg2);
        Cifra xylo,xymid,xyhi,xymidhi,xymidlo;
        Cifra xhl,yhl;

        xylo = xlo*ylo; xyhi = xhi*yhi;
        xhl = xhi+xlo; yhl = yhi+ylo;
        xymid = xhl*yhl - (xyhi+xylo);

        xylo += resto; xyhi += (xylo < resto);

        xymidhi = HIGHHALF(xymid);
        xymidlo = xymid << Constantes::BITS_IN_HALFCIFRA;

        xylo += xymidlo;
        resto = xyhi + xymidhi + (xylo < xymidlo)
          + ((((xhl + yhl) >> 1) - xymidhi) & Constantes::MASK_CIFRAHIGH);

        return xylo;
    }

  /** Cociente y resto de dos Cifras para generic. 
   *
   * @sa Div(Cifra arg1, Cifra arg2)
   */
   template<>
    inline Cifra vCPUBasica<Arch::generic>::Div(Cifra arg1, Cifra arg2) 
    { 
      //FIXME!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
      uint64_t x = resto;
      x <<= Constantes::BITS_EN_CIFRA;
      x |= arg1;
      const Cifra ret = x/arg2; 
      resto = x % arg2;
//      __asm__ (" divl %[_arg2]" 
//          : "=a" (ret), "=d" (resto) 
//          : [_arg1] "0" (arg1), [_arg2] "g" (arg2), "1" (resto)
//          ); 

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


