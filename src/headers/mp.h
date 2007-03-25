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
#include "constantes.h"
#include "nucleo.h"

namespace mpplas{

  /** Procesador que trabaja con vectores de Cifras */
  namespace vCPUVectorial  {
   
    /* de desplazamiento */
    void lShift(mpplas::MiVec <Cifra>& a, size_t n);
    void rShift(mpplas::MiVec <Cifra>& a, size_t n);

    /* misc. */
    //funcion de redondeo
    long redondear(const mpplas::MiVec<Cifra>& a, size_t exceso, const int8_t signo);
    
    size_t numBits(const Cifra num) __FUNC_CONST_ATTRIB;
    
    /* de comparacion */

    //paso por valor ya que debemos modificarlos en la funcion para
    //quitar posibles ceros
    bool mayorque(mpplas::MiVec<Cifra> a, mpplas::MiVec<Cifra> b, bool limpiar=false ) ;
    // idem
    bool menorque(mpplas::MiVec<Cifra> a, mpplas::MiVec<Cifra> b, bool limpiar=false ) ;
    //idem
    bool igual(mpplas::MiVec<Cifra> a, mpplas::MiVec<Cifra> b, bool limpiar=false ) ;

    /* versiones para uso con longs */
    bool mayorque(mpplas::MiVec<Cifra> vec, Cifra num, bool limpiar=false )  ;
    bool menorque(mpplas::MiVec<Cifra> vec, Cifra num, bool limpiar=false ) ;
    bool igual(mpplas::MiVec<Cifra> vec, Cifra num, bool limpiar=false ) ;


    /* aritmeticas */
    mpplas::MiVec<Cifra> sumaMP(const mpplas::MiVec<Cifra>& a,
        const mpplas::MiVec<Cifra>& b ) ;
    mpplas::MiVec<Cifra> restaMP(const mpplas::MiVec<Cifra>& a,
        const mpplas::MiVec<Cifra>& b ) ;
    mpplas::MiVec<Cifra> multMP(const mpplas::MiVec<Cifra>& a,
        const mpplas::MiVec<Cifra>& b ) ;
    /*         cociente            modulo              */
    //argumentos por valor ya que necesitamos copiarlos de todas formas
    //en el algoritmo para trabajar localmente con ellos
    std::pair< mpplas::MiVec<Cifra>, mpplas::MiVec<Cifra> > 
      divMP(mpplas::MiVec<Cifra> a,
          mpplas::MiVec<Cifra> b ) ;

    /* version de uso con precision simple */
    MiVec<Cifra> sumaMP(const mpplas::MiVec<Cifra>& a, const Cifra b ) ;
    MiVec<Cifra> restaMP(const mpplas::MiVec<Cifra>& a, const Cifra b ) ;
    MiVec<Cifra> restaMP(const Cifra a, const mpplas::MiVec<Cifra>& b ) ;
    MiVec<Cifra> multMP(const mpplas::MiVec<Cifra>& a, const Cifra b ) ;
    std::pair< mpplas::MiVec<Cifra>, mpplas::MiVec<Cifra> > divMP(const mpplas::MiVec<Cifra>& a, const Cifra b ) ;


    /** Calculo eficiente del cuadrado. */
    MiVec<Cifra> cuadMP(const mpplas::MiVec<Cifra>& x);

    void limpiarCeros(mpplas::MiVec<Cifra>&) throw();

    void karatsuba(MiVec<Cifra>& resultado, const MiVec<Cifra>& x, const MiVec<Cifra>& y);
    void cuadKaratsuba(MiVec<Cifra>& resultado, const MiVec<Cifra>& x);
    
  }
}


#endif
