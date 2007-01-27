#include <iostream>
#include <unistd.h>
#include <stdlib.h>
/* 
 * $Id$
 */


  /******************************************************************
   *                                                                 *
   *            IMPLEMENTACI�N PARA ARQUITECTURA X86_64              *
   *                                                                 *
   ******************************************************************/ 
  /** Constructor por defecto de la Cpu B�sica para x86_64 */
  template<>
    inline vCPUBasica<Arch::x86_64>::vCPUBasica()
      : overflow(0), resto(0)
    {
    }
 

  /** Suma b�sica de dos Cifras para x86_64.
   *
   * @sa Add(Cifra arg1, Cifra arg2)
   */
  template<>
    inline Cifra vCPUBasica<Arch::x86_64>::Add(Cifra arg1, Cifra arg2)
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

  /** Suma b�sica extendida de dos Cifras para x86_64.
   *
   * @sa Addx(Cifra arg1, Cifra arg2)
   */
  template<>
    inline Cifra vCPUBasica<Arch::x86_64>::Addx(Cifra arg1, Cifra arg2) 
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


  /** Resta b�sica de dos Cifras para x86_64.
   *
   * @sa Sub(Cifra arg1, Cifra arg2)
   */
  template<>
    inline Cifra vCPUBasica<Arch::x86_64>::Sub(Cifra arg1, Cifra arg2) 
    { 
      __asm__ ("xorq %[_of], %[_of];"
               "subq %[_arg2], %[_arg1];"
               "adcq $0, %[_of]; " 
          : "=r" (arg1), [_of] "=r" (overflow) 
          : [_arg1] "0" (arg1), [_arg2] "r" (arg2)
          : "cc" /* modificamos eflags */
          ); 

      return arg1; 
    }
  /** Resta b�sica extendida de dos Cifras para x86_64.
   *
   * @sa Subx(Cifra arg1, Cifra arg2)
   */
  template<>
    inline Cifra vCPUBasica<Arch::x86_64>::Subx(Cifra arg1, Cifra arg2) 
    { 
      __asm__ ("btrq $0, %[_of];" /* pone CF al valor del bit 0 de overflow */
               "sbbq %[_arg2], %[_arg1];"
               "adcq $0, %[_of];" 
          : "=r" (arg1), [_of] "=r" (overflow) 
          : [_arg1] "0" (arg1), [_arg2] "r" (arg2), "1" (overflow) 
          : "cc" /* modificamos eflags */
          );
      return arg1; 
    }

  /** Producto de dos Cifras para x86_64.
   *
   * @sa Mul(Cifra arg1,Cifra arg2)
   */
  template<>
    inline Cifra vCPUBasica<Arch::x86_64>::Mul(Cifra arg1,Cifra arg2) 
    { 
      __asm__ (" mulq %[_arg2]" 
          : "=a" (arg1), "=d" (resto) 
          : [_arg1] "0" (arg1), [_arg2] "rm" (arg2)
          ); 

      return arg1; 
    }

  /** Producto de dos Cifras con suma para x86_64.
   *
   * @sa Addmul(Cifra arg1,Cifra arg2) 
   */
  template<>
    inline Cifra vCPUBasica<Arch::x86_64>::Addmul(Cifra arg1,Cifra arg2) 
    { 
      __asm__ (" mulq %[_arg2];"
               "addq %[_restoViejo],%[_ret];" 
               "adcq $0, %%rdx;"      
          : [_ret] "=a" (arg1), "=&d" (resto) 
          : [_arg1] "0" (arg1), [_arg2] "rm" (arg2), [_restoViejo] "rm" (resto) 
          ); 

      return arg1; 
    }

  /** Cociente y resto de dos Cifras para x86_64. 
   *
   * @sa Div(Cifra arg1, Cifra arg2)
   */
   template<>
    inline Cifra vCPUBasica<Arch::x86_64>::Div(Cifra arg1, Cifra arg2) 
    { 
      __asm__ (" divq %[_arg2]" 
          : "=a" (arg1), "=d" (resto) 
          : [_arg1] "0" (arg1), [_arg2] "r" (arg2), "1" (resto)
          ); 

      return arg1;
    }


   /** Desplazamiento de bits a la izquierda para x86_64.
    *
    *  @sa Shiftl(Cifra arg1,Cifra arg2)
    */
  template<>
    inline Cifra vCPUBasica<Arch::x86_64>::Shiftl(Cifra arg1,Cifra arg2) 
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
   * @sa Shiftlr(Cifra arg1,Cifra arg2)
   */
  template<>
    inline Cifra vCPUBasica<Arch::x86_64>::Shiftlr(Cifra arg1,Cifra arg2) 
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
   * @sa Bfffo(Cifra arg1) 
   */
  template<>
    inline Cifra vCPUBasica<Arch::x86_64>::Bfffo(Cifra arg1) 
    {
      Cifra ret = (Constantes::BITS_EN_CIFRA-1), temp; 

      if( (arg1) != (0))  { 
        __asm__ (" bsrq %[_arg1], %[_temp]; " 
            : [_temp] "=r" (temp) 
            : [_arg1] "r" (arg1) 
            ); 
        ret -= temp; 
      }
      else ret++; 

      return ret; 
    }

  /** Funci�n de perfilado en x86_64 (inv�lido).
   *
   * Invicar esta funci�n produce que se lance una excepci�n de tipo 
   * Errores::ArchNoProfiling
   */
  template<>
    inline void vCPUBasica<Arch::x86_64>::reiniciarContadores(void)
    {
      throw Errores::ArchNoProfiling();
    }

   /** Funci�n de perfilado en x86_64 (inv�lido).
   *
   * Invicar esta funci�n produce que se lance una excepci�n de tipo 
   * Errores::ArchNoProfiling
   */
 template<>
    inline void vCPUBasica<Arch::x86_64>::inicioProf(void)
    {
      throw Errores::ArchNoProfiling();
    }

   /** Funci�n de perfilado en x86_64 (inv�lido).
   *
   * Invicar esta funci�n produce que se lance una excepci�n de tipo 
   * Errores::ArchNoProfiling
   */
 template<>
    inline void vCPUBasica<Arch::x86_64>::finProf(void)
    {
      throw Errores::ArchNoProfiling();
    }

   /** Funci�n de perfilado en x86_64 (inv�lido).
   *
   * Invicar esta funci�n produce que se lance una excepci�n de tipo 
   * Errores::ArchNoProfiling
   */
 template<>
    inline ResultadosProf vCPUBasica<Arch::x86_64>::obtenerPerfil(void)
    {
      throw Errores::ArchNoProfiling();
    }


