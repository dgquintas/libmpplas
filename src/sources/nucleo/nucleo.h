/* 
 * $Id$
 */

#ifndef __NUCLEO_H
#define __NUCLEO_H

#include "constantes.h"
#include "err.h"
#include <cstring>
#include <ctime>


namespace numth{

  namespace vCPUBasica{



    /** Suma b�sica de dos Cifras
     *
     * \par Definici�n:
     *   \f$ Add(a,b) + (overflow \cdot BASE) = a + b \f$
     *   con \f$ overflow \in \{0,1\} \f$
     * 
     * @param arg1 Primer sumando
     * @param arg2 Segundo sumando
     *
     * @return Parte baja de la suma de arg1 y arg2
     */
    inline Cifra Add(Cifra arg1, Cifra arg2, Cifra& overflow);
    
    /** Suma b�sica extendida de dos Cifras
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
    inline Cifra Addx(Cifra arg1, Cifra arg2, Cifra& overflow);


    /** Resta b�sica de dos Cifras
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
    inline Cifra Sub(Cifra arg1, Cifra arg2, Cifra& overflow);

    /** Resta b�sica extendida de dos Cifras
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
      inline Cifra Subx(Cifra arg1, Cifra arg2, Cifra& overflow);
      
    /** Producto de dos Cifras
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
    inline  Cifra Mul(Cifra arg1,Cifra arg2, Cifra& overflow);

    /** Producto de dos Cifras con suma.
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
    inline Cifra Addmul(Cifra arg1,Cifra arg2, Cifra& resto) ;

    /** Cociente y resto de dos Cifras.
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
    inline Cifra Div(Cifra arg1, Cifra arg2, Cifra& resto);

    /** Desplazamiento de bits a la izquierda.
     *
     * Desplaza una Cifra una cantidad de bits a la izquierda. Esto es
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
     inline Cifra Shiftl(Cifra arg1,Cifra arg2, Cifra& resto) ;
   
    
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
    inline Cifra Shiftlr(Cifra arg1,Cifra arg2, Cifra& resto) ;
 
    
    /** Encabezado de ceros.
     *
     * Devuelve en el n�mero de ceros binarios a la izquierda del primer uno.
     *  Esto es, el n�mero de posiciones que habria que desplazar el n�mero binario
     *  hacia la izquierda para que su cifra m�s significativa fuera 1. 
     *
     * \par Definici�n:
     *    Bfffo(a) = Menor natural \f$ n \f$ tal que \f$ a \cdot
     *    2^{n} \geq BASE/2 \f$
     * 
     * @param arg1 Entero a considerar.
     *
     * @return El n�mero de ceros binarios a la izquierda del primer uno.
     */
    /* c = Bfffo(a) devuelve en c el n�mero de ceros binarios a la izquierda del primer uno.
       Esto es, el n�mero de posiciones que habria que desplazar el n�mero binario
       hacia la izquierda para que su cifra m�s significativa fuera 1. */
    inline Cifra Bfffo(Cifra arg1) ;



#ifdef ARCH_x86
  #include "nucleox86.h"
#endif

#ifdef ARCH_x86_64
  #include "nucleox86_64.h"
#endif

#ifdef ARCH_generic
  #include "nucleogeneric.h"
#endif

#ifdef ARCH_ppc
  #include "nucleoppc.h"
#endif



  };


//    protected:
    /** Cifra que representa el acarreo en las operaciones de suma y
     * resta. */
//    Cifra overflow; 

    /** 
     * Cifra que representa:
     * <ul>
     * <li> Parte alta del resultado de una multiplicaci�n
     * <li> Parte alta del dividendo previamente a la divisi�n
     * <li> Resto de una divisi�n tras la misma
     * <li> Parte baja tras un desplazamiento hacia la izquierda
     * <li> Parte alta tras un desplazamiento hacia la derecha
     * </ul>
     */
//    Cifra resto;
 
  
}

#endif
