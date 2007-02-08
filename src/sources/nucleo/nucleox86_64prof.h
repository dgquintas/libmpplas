#include <iostream>
#include <unistd.h>
#include <stdlib.h>
/* 
 * $Id$
 */


  /******************************************************************
   *                                                                 *
   *            IMPLEMENTACIï¿½N PARA ARQUITECTURA X86_64              *
   *                                                                 *
   ******************************************************************/ 
  /** Constructor por defecto de la Cpu Bï¿½sica para x86_64Prof */
  template<>
    inline vCPUBasica<Arch::x86_64Prof>::vCPUBasica()
      : overflow(0), resto(0)
    {
    }
 

  /** Suma bï¿½sica de dos Cifras para x86_64Prof.
   *
   * @sa Add(Cifra arg1, Cifra arg2)
   */
  template<>
    inline Cifra vCPUBasica<Arch::x86_64Prof>::Add(Cifra arg1, Cifra arg2)
    {
      
      resultadosProf_.n_operaciones[Operaciones::Add]++;
      __asm__ ("xorq %[_of], %[_of];"
               "addq %[_arg2], %[_arg1]; "
               "adcq $0, %[_of]; "
          : "=r" (arg1), [_of] "=r" (overflow)
          : [_arg1] "0" (arg1), [_arg2] "r" (arg2), "1" (overflow)
          : "cc" /* modificamos eflags */
          );

      return arg1; 
    }

  /** Suma bï¿½sica extendida de dos Cifras para x86_64Prof.
   *
   * @sa Addx(Cifra arg1, Cifra arg2)
   */
  template<>
    inline Cifra vCPUBasica<Arch::x86_64Prof>::Addx(Cifra arg1, Cifra arg2) 
    { 
      resultadosProf_.n_operaciones[Operaciones::Addx]++;
      __asm__ ("btrq $0, %[_of];"
               "adcq %[_arg2], %[_arg1];" 
               "adcq $0, %[_of]; "
          : "=r" (arg1), [_of] "=r" (overflow) 
          : [_arg1] "0" (arg1), [_arg2] "r" (arg2), "1" (overflow) 
          : "cc" /* modificamos eflags */
          );

      return arg1; 
    }


  /** Resta bï¿½sica de dos Cifras para x86_64Prof.
   *
   * @sa Sub(Cifra arg1, Cifra arg2)
   */
  template<>
    inline Cifra vCPUBasica<Arch::x86_64Prof>::Sub(Cifra arg1, Cifra arg2) 
    { 
      resultadosProf_.n_operaciones[Operaciones::Sub]++;
      __asm__ ("xorq %[_of], %[_of];"
               "subq %[_arg2], %[_arg1];"
               "adcq $0, %[_of]; " 
          : "=r" (arg1), [_of] "=r" (overflow) 
          : [_arg1] "0" (arg1), [_arg2] "r" (arg2)
          : "cc" /* modificamos eflags */
          ); 

      return arg1; 
    }
  /** Resta bï¿½sica extendida de dos Cifras para x86_64Prof.
   *
   * @sa Subx(Cifra arg1, Cifra arg2)
   */
  template<>
    inline Cifra vCPUBasica<Arch::x86_64Prof>::Subx(Cifra arg1, Cifra arg2) 
    { 

      resultadosProf_.n_operaciones[Operaciones::Subx]++;
      __asm__ ("btrq $0, %[_of];" /* pone CF al valor del bit 0 de overflow */
               "sbbq %[_arg2], %[_arg1];"
               "adcq $0, %[_of];" 
          : "=r" (arg1), [_of] "=r" (overflow) 
          : [_arg1] "0" (arg1), [_arg2] "r" (arg2), "1" (overflow) 
          : "cc" /* modificamos eflags */
          );
      return arg1; 
    }

  /** Producto de dos Cifras para x86_64Prof.
   *
   * @sa Mul(Cifra arg1,Cifra arg2)
   */
  template<>
    inline Cifra vCPUBasica<Arch::x86_64Prof>::Mul(Cifra arg1,Cifra arg2) 
    { 
      resultadosProf_.n_operaciones[Operaciones::Mul]++;
      __asm__ (" mulq %[_arg2]" 
          : "=a" (arg1), "=d" (resto) 
          : [_arg1] "0" (arg1), [_arg2] "rm" (arg2)
          ); 

      return arg1; 
    }

  /** Producto de dos Cifras con suma para x86_64Prof.
   *
   * @sa Addmul(Cifra arg1,Cifra arg2) 
   */
  template<>
    inline Cifra vCPUBasica<Arch::x86_64Prof>::Addmul(Cifra arg1,Cifra arg2) 
    { 

      resultadosProf_.n_operaciones[Operaciones::Addmul]++;
      __asm__ (" mulq %[_arg2];"
               "addq %[_restoViejo],%[_ret];" 
               "adcq $0, %%rdx;"      
          : [_ret] "=a" (arg1), "=&d" (resto) 
          : [_arg1] "0" (arg1), [_arg2] "rm" (arg2), [_restoViejo] "rm" (resto) 
          ); 

      return arg1; 
    }

  /** Cociente y resto de dos Cifras para x86_64Prof. 
   *
   * @sa Div(Cifra arg1, Cifra arg2)
   */
   template<>
    inline Cifra vCPUBasica<Arch::x86_64Prof>::Div(Cifra arg1, Cifra arg2) 
    {

      resultadosProf_.n_operaciones[Operaciones::Div]++;
      __asm__ (" divq %[_arg2]" 
          : "=a" (arg1), "=d" (resto) 
          : [_arg1] "0" (arg1), [_arg2] "r" (arg2), "1" (resto)
          ); 

      return arg1;
    }


   /** Desplazamiento de bits a la izquierda para x86_64Prof.
    *
    *  @sa Shiftl(Cifra arg1,Cifra arg2)
    */
  template<>
    inline Cifra vCPUBasica<Arch::x86_64Prof>::Shiftl(Cifra arg1,Cifra arg2) 
    {

      resultadosProf_.n_operaciones[Operaciones::Shiftl]++;
      __asm__ ("xorq %[_resto], %[_resto];"
               "shldq %%cl, %[_arg1], %[_resto]; "
               "shlq %%cl, %[_arg1];"  
          : "=r" (arg1), [_resto] "=r" (resto) 
          : [_arg1] "0" (arg1), "c" (arg2), "1" (resto)
          ); 

      return arg1; 
    }

  /** Desplazamiento de bits de la derecha para x86_64Prof.
   *
   * @sa Shiftlr(Cifra arg1,Cifra arg2)
   */
  template<>
    inline Cifra vCPUBasica<Arch::x86_64Prof>::Shiftlr(Cifra arg1,Cifra arg2) 
    {

      resultadosProf_.n_operaciones[Operaciones::Shiftlr]++;
      __asm__ ("xorq %[_resto], %[_resto];"
               "shrdq %%cl, %[_arg1], %[_resto];"
               "shrq %%cl, %[_arg1]" 
          : "=r" (arg1), [_resto] "=r" (resto) 
          : [_arg1] "0" (arg1), "c" (arg2), "1" (resto)
          ); 

      return arg1; 
    }

  /** Encabezado de ceros para x86_64Prof.
   *
   * @sa Bfffo(Cifra arg1) 
   */
  template<>
    inline Cifra vCPUBasica<Arch::x86_64Prof>::Bfffo(Cifra arg1) 
    {

      resultadosProf_.n_operaciones[Operaciones::Bfffo]++;
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

  /** Reiniciar contadores.
   *
   * Esta función reinicia los contadores de perfilado.
   */
  template<>
    inline void vCPUBasica<Arch::x86_64Prof>::reiniciarContadores(void)
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
    inline void vCPUBasica<Arch::x86_64Prof>::inicioProf(void)
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
    inline void vCPUBasica<Arch::x86_64Prof>::finProf(void)
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
    inline ResultadosProf vCPUBasica<Arch::x86_64Prof>::obtenerPerfil(void)
    {
      return resultadosProf_;
    }

