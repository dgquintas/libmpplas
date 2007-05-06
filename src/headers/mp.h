/* 
 * $Id$
 */

#ifndef __MP_H
#define __MP_H

#include <vector>
#include <utility>
#include <limits>
#include <cassert>

#include "err.h"
#include "MiVec.h"
#include "constants.h"

namespace mpplas{

  /** Procesador que trabaja con vectores de Digits */
  namespace vCPUVectorial  {
   
    /* de desplazamiento */
    void lShift(mpplas::MiVec <Digit>& a, size_t n);
    void rShift(mpplas::MiVec <Digit>& a, size_t n);

    /* misc. */
    //funcion de redondeo
    long redondear(const mpplas::MiVec<Digit>& a, size_t exceso, const int8_t signo);
    
    size_t numBits(const Digit num) __FUNC_CONST_ATTRIB;

    
    /* de comparacion */

    //paso por valor ya que debemos modificarlos en la funcion para
    //quitar posibles ceros
    bool mayorque(mpplas::MiVec<Digit> a, mpplas::MiVec<Digit> b, bool limpiar=false ) ;
    // idem
    bool menorque(mpplas::MiVec<Digit> a, mpplas::MiVec<Digit> b, bool limpiar=false ) ;
    //idem
    bool igual(mpplas::MiVec<Digit> a, mpplas::MiVec<Digit> b, bool limpiar=false ) ;

    /* versiones para uso con longs */
    bool mayorque(mpplas::MiVec<Digit> vec, Digit num, bool limpiar=false )  ;
    bool menorque(mpplas::MiVec<Digit> vec, Digit num, bool limpiar=false ) ;
    bool igual(mpplas::MiVec<Digit> vec, Digit num, bool limpiar=false ) ;


    /* aritmeticas */
    mpplas::MiVec<Digit> sumaMP(const mpplas::MiVec<Digit>& a,
        const mpplas::MiVec<Digit>& b ) ;
    mpplas::MiVec<Digit> restaMP(const mpplas::MiVec<Digit>& a,
        const mpplas::MiVec<Digit>& b ) ;
    mpplas::MiVec<Digit> multMP(const mpplas::MiVec<Digit>& a,
        const mpplas::MiVec<Digit>& b ) ;
    /*         cociente            modulo              */
    //argumentos por valor ya que necesitamos copiarlos de todas formas
    //en el algoritmo para trabajar localmente con ellos
    std::pair< mpplas::MiVec<Digit>, mpplas::MiVec<Digit> > 
      divMP(mpplas::MiVec<Digit> a,
          mpplas::MiVec<Digit> b ) ;

    /* version de uso con precision simple */
    MiVec<Digit> sumaMP(const mpplas::MiVec<Digit>& a, const Digit b ) ;
    MiVec<Digit> restaMP(const mpplas::MiVec<Digit>& a, const Digit b ) ;
    MiVec<Digit> restaMP(const Digit a, const mpplas::MiVec<Digit>& b ) ;
    MiVec<Digit> multMP(const mpplas::MiVec<Digit>& a, const Digit b ) ;
    std::pair< mpplas::MiVec<Digit>, mpplas::MiVec<Digit> > divMP(const mpplas::MiVec<Digit>& a, const Digit b ) ;


    /** Calculo eficiente del cuadrado. */
    MiVec<Digit> cuadMP(const mpplas::MiVec<Digit>& x);

    void limpiarCeros(mpplas::MiVec<Digit>&) throw();

    void karatsuba(MiVec<Digit>& resultado, const MiVec<Digit>& x, const MiVec<Digit>& y);
    void cuadKaratsuba(MiVec<Digit>& resultado, const MiVec<Digit>& x);
    
    void ProfStats();
    void ProfReset();
  }
}


#endif
