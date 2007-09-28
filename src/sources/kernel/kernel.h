/* 
 * $Id$
 */

#ifndef __KERNEL_H
#define __KERNEL_H

#include "BasicTypedefs.h"
#include "CPUInfo.h"

namespace mpplas{

  namespace BasicCPU{

    /** Basic summation of two Digits
     *
     * \par Definition:
     *   \f$ Add(a,b) + (overflow \cdot BASE) = a + b \f$
     *   con \f$ overflow \in \{0,1\} \f$
     * 
     * @param arg1 First addend
     * @param arg2 Second addend
     *
     * @return Parte baja de la suma de arg1 y arg2
     */
    inline Digit Add(Digit arg1, Digit arg2, Digit& overflow) ;
    
    /** Suma b�sica extendida de dos Digits
     *
     * Esta funci�n tiene en cuenta el valor
     * de @e overflow presente en el momento de llamar a la funcion.
     * Esto no impide que tras el c�lculo se coloque en overflow el
     * valor que corresponda.
     * 
     * \par Definici�n:
     *   \f$ Addx(a,b) + (overflow \cdot BASE) = a + b + overflow_{inicial} \f$
     *   con \f$ overflow \in \{0,1\} \f$
     * 
     * @param arg1 Primer sumando
     * @param arg2 Segundo sumando
     *
     * @return Parte baja de la suma de arg1, arg2 y overflow inicial
     */
    inline Digit Addx(Digit arg1, Digit arg2, Digit& overflow);


    /** Resta b�sica de dos Digits
     *
     * El significado de @e overflow en esta funci�n no ser�a correcto
     * como tal, ya que se trata m�s bien de un desbordamiento "por
     * abajo".
     *
     * \par Definici�n:
     *   \f$ Sub(a,b) - (overflow \cdot BASE) = a - b \f$
     *   con \f$ overflow \in \{0,1\} \f$
     * 
     * @param arg1 Minuendo
     * @param arg2 Sustraendo
     *
     * @return Resta de arg1 y arg2 
     */
    inline Digit Sub(Digit arg1, Digit arg2, Digit& overflow);

    /** Resta b�sica extendida de dos Digits
     *
     * Esta funci�n tiene en cuenta el valor
     * de @e overflow presente en el momento de llamar a la funcion.
     * Esto no impide que tras el c�lculo se coloque en overflow el
     * valor que corresponda.
     * 
     * \par Definici�n:
     *   \f$ Subx(a,b) + (overflow \cdot BASE) = a - b - overflow_{inicial} \f$
     *   con \f$ overflow \in \{0,1\} \f$
     * 
     * @param arg1 Primer sumando
     * @param arg2 Segundo sumando
     *
     * @return Parte baja de la resta de arg1, arg2 y overflow inicial
     */
    /* Subx(a,b) + (base�overflow) = a - b - overflow_ini 
     * overflow = {0,1} */
      inline Digit Subx(Digit arg1, Digit arg2, Digit& overflow);
      
    /** Producto de dos Digits
     *
     * \par Definici�n:
     *   \f$ Mul(a,b) = {a \cdot b} \bmod {BASE} \f$ \n
     *   y \f$ resto = \frac{a \cdot b}{BASE} \f$
     * 
     * @param arg1 Primer factor
     * @param arg2 Segundo factor
     *
     * @return Parte baja del producto de arg1, arg2 y asigna a @e resto
     * la parte alta.
     */
    /* c = mul(a,b)
     * Dejando resto = parte alta del resultado */
    inline  Digit Mul(Digit arg1,Digit arg2, Digit& overflow);

    /** Producto de dos Digits con suma.
     * 
     * Suma al producto de @e arg1 por @e arg2 el contenido de @e resto, devolviendo
     *  los @e BITS_EN_CIFRA de la parte baja del resultado y almacenando en @e resto
     *  la parte alta. 
     *
     * \par Definici�n:
     *   \f$ Addmul(a,b) = ({a \cdot b}+resto_{inicial}) \bmod {BASE} \f$ \n
     *   y \f$ resto = \frac{(a \cdot b)+resto_{inicial}}{BASE} \f$
     * 
     * @param arg1 Primer factor
     * @param arg2 Segundo factor
     *
     * @return Parte baja del producto de arg1, arg2 m�s @e resto y asigna a @e resto
     * la parte alta.
     */
    /* c = addmul(a,b)
     * Suma al producto de a por b el contenido de resto, devolviendo
     los BITS_EN_CIFRA de la parte baja del resultado y almacenando en 
     resto la parte alta. */
    inline Digit Addmul(Digit arg1,Digit arg2, Digit& resto) ;

    /** Cociente y resto de dos Digits.
     *
     * Realiza la divisi�n entera del entero de "doble precisi�n"
     * formado por la concatenaci�n de @e resto y @e arg1 entre @e arg2, obteniendo
     * el cociente y el resto de la misma.
     *
     * \pre @e arg2 > @e resto, para que el cociente sea un entero de
     * precisi�n simple.
     * 
     * \par Definici�n:
     *   \f$ resto \cdot BASE + a = Div(a,b) \cdot b + resto \f$ 
     * 
     * @param arg1 Dividendo
     * @param arg2 Divisor
     *
     * @return Cociente entero de @e resto:arg1 entre @e arg2. Deja el resto en @e resto.
     */
    /* c = div(a, b) 
     * Dejando el resto de la divisi�n de (resto:a / b) en resto. 
     * Se asume que inicialmente b > resto. */
    inline Digit Div(Digit arg1, Digit arg2, Digit& resto);

    /** Desplazamiento de bits a la izquierda.
     *
     * Desplaza una Digit una cantidad de bits a la izquierda. Esto es
     * an�logo a la multiplicaci�n por una potencia de 2 igual al n�mero
     * de posiciones desplazadas.
     *
     * \pre N�mero \f$ n \f$ de bits de desplazar cumple \f$ 0 \leq n <
     * \log_{2}BASE \f$.
     * 
     * \par Definici�n:
     *   \f$ Shiftl(a,b) = \lfloor a \cdot 2^{b} \rfloor \bmod BASE \f$ \n
     *   \f$ resto = \lfloor(a \cdot 2^{b}) / BASE \rfloor \f$
     * 
     * @param arg1 Entero a desplazar
     * @param arg2 N�mero de desplazamientos
     *
     * @return La parte baja del n�mero desplazado. Deja en @e resto la parte alta.
     */
    /* c = shiftl(a, b) 
     * Dejando en resto los la parte alta. Se asume que 0 <= b < lg2 B. */
     inline Digit Shiftl(Digit arg1,Digit arg2, Digit& resto) ;
   
    
    /** Desplazamiento de bits a la derecha.
     *
     * Desplaza un Entero una cantidad de bits a la derecha. Esto es
     * an�logo a la divisi�n entera por una potencia de 2 igual 
     * al n�mero de posiciones desplazadas.
     *
     * \pre N�mero \f$ n \f$ de bits de desplazar cumple \f$ 0 \leq n <
     * \log_{2}BASE \f$.
     * 
     * \par Definici�n:
     *   \f$ Shiftlr(a,b) = \lfloor a / 2^{b} \rfloor \bmod BASE \f$ \n
     *   \f$ resto = \lfloor a / 2^{b} \rfloor / BASE \f$
     * 
     * @param arg1 Entero a desplazar
     * @param arg2 N�mero de desplazamientos
     *
     * @return La parte alta del n�mero desplazado. Deja en @e resto la parte baja.
     */
    /* c = shiftlr(a, b) 
     * devuelve en c los BITS_EN_CIFRA de la parte alta de a << BITS_EN_CIFRA entre 2^b y
     almacena en resto los BITS_EN_CIFRA de la parte baja. Se asume que 0 <= b < lg2 B.*/
    inline Digit Shiftlr(Digit arg1,Digit arg2, Digit& resto) ;
 
    /** Minimum number of bits.
     *
     * Returns the minimum number of bits needed to represent @arg.
     *
     * \par Definition:
     *  \$f Nnob(x) = \floor{ \log_2{arg} } + 1 \$f
     *
     * @param arg The Digit to consider.
     *
     * @return The minimum number of bits needed to represent @arg.
     */
    inline Digit Mnob(Digit arg1) __FUNC_CONST_ATTRIB;


    


  };


}
#ifdef ARCH_x86
  #define ARCH_DEFINED
#endif

#ifdef ARCH_x86_64
  #define ARCH_DEFINED
#endif

#ifdef ARCH_generic
  #define ARCH_DEFINED
#endif

#ifndef ARCH_DEFINED
  #warning "ARCH not supported or not defined. Using x86"
  #define ARCH_DEFINED
  #define ARCHBITS 32
#endif


#pragma __libmpplas_manual_include x86
  #include "kernelx86.h"

#pragma __libmpplas_manual_include x86_64
  #include "kernelx86_64.h"

#pragma __libmpplas_manual_include generic
  #include "kernelgeneric.h"

#pragma __libmpplas_manual_include 
  #include "kernelSIMD.h"


#endif
