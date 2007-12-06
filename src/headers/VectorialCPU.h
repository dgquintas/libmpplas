/* 
 * $Id$
 */

#ifndef __MP_H
#define __MP_H

#include <vector>
#include <utility>
#include <limits>
#include <cassert>

#include "Errors.h"
#include "MiVec.h"
#include "Constants.h"

namespace mpplas{

  /** Virtual CPU that deals with vectors of Digit(s) */
  namespace VectorialCPU  {
   
    //funcion de redondeo
    SignedDigit round(const mpplas::MiVec<Digit>& a, int exceso, const int8_t signo);

    /** Gets the bit length of a Digit.
     *
     * In this context, the bit length is defined as the smaller
     * number of bits needed to represent @a num.
     *
     * @param num The Digit to consider
     * @return The smaller number of bits needed to represent @a num */
    int getBitLength(const Digit num) __FUNC_CONST_ATTRIB;
    

    //paso por valor ya que debemos modificarlos en la funcion para
    //quitar posibles ceros
    bool mayorque(mpplas::MiVec<Digit> a, mpplas::MiVec<Digit> b, const bool limpiar=false ) ;
    // idem
    bool menorque(mpplas::MiVec<Digit> a, mpplas::MiVec<Digit> b, const bool limpiar=false ) ;
    //idem
    bool igual(mpplas::MiVec<Digit> a, mpplas::MiVec<Digit> b, const bool limpiar=false ) ;

    /* versiones para uso con longs */
    bool mayorque(mpplas::MiVec<Digit> vec, Digit num, const bool limpiar=false )  ;
    bool menorque(mpplas::MiVec<Digit> vec, Digit num, const bool limpiar=false ) ;
    bool igual(mpplas::MiVec<Digit> vec, Digit num, const bool limpiar=false ) ;


    /* aritmeticas */
    mpplas::MiVec<Digit> 
      sumaMP(const mpplas::MiVec<Digit>& a, const mpplas::MiVec<Digit>& b ) ;
    mpplas::MiVec<Digit> 
      restaMP(const mpplas::MiVec<Digit>& a, const mpplas::MiVec<Digit>& b ) ;
    mpplas::MiVec<Digit> 
      multMP(const mpplas::MiVec<Digit>& a,const mpplas::MiVec<Digit>& b ) ;
    //argumentos por valor ya que necesitamos copiarlos de todas formas
    //en el algoritmo para trabajar localmente con ellos
    std::pair< mpplas::MiVec<Digit> , mpplas::MiVec<Digit> >  /* ( quotient , remainder ) */
      divMP(mpplas::MiVec<Digit> a, mpplas::MiVec<Digit> b ) ;

    /* version de uso con precision simple */
    MiVec<Digit> sumaMP(const mpplas::MiVec<Digit>& a, const Digit b ) ;
    MiVec<Digit> restaMP(const mpplas::MiVec<Digit>& a, const Digit b ) ;
    MiVec<Digit> restaMP(const Digit a, const mpplas::MiVec<Digit>& b ) ;
    MiVec<Digit> multMP(const mpplas::MiVec<Digit>& a, const Digit b ) ;
    std::pair< mpplas::MiVec<Digit>, mpplas::MiVec<Digit> > divMP(const mpplas::MiVec<Digit>& a, const Digit b ) ;
    /* de desplazamiento */
    void lShift(mpplas::MiVec <Digit>& a, int n);
    void rShift(mpplas::MiVec <Digit>& a, int n);
    /** Calculo eficiente del cuadrado. */
    MiVec<Digit> cuadMP(const mpplas::MiVec<Digit>& x);
    void karatsuba(MiVec<Digit>& resultado, const MiVec<Digit>& x, const MiVec<Digit>& y);
    void cuadKaratsuba(MiVec<Digit>& resultado, const MiVec<Digit>& x);


    void limpiarCeros(mpplas::MiVec<Digit>&) throw();
  }
}


#endif
