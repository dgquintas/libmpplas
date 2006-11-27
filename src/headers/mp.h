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

namespace numth{

  /** Procesador que trabaja con vectores de Cifras */
  class vCPUVectorial  {
   
    public:
      vCPUVectorial(int numCPUs);
      ~vCPUVectorial();

    /* de desplazamiento */
    void lShift(numth::MiVec <Cifra>& a, size_t n);
    void rShift(numth::MiVec <Cifra>& a, size_t n);


    /* misc. */
    //funcion de redondeo
    long redondear(const numth::MiVec<Cifra>& a, size_t exceso, const int8_t signo);
    
    size_t numBits(const Cifra num);
    
    /* de comparacion */

    //paso por valor ya que debemos modificarlos en la funcion para
    //quitar posibles ceros
    bool mayorque(numth::MiVec<Cifra> a, numth::MiVec<Cifra> b, bool limpiar=false )  ;
    // idem
    bool menorque(numth::MiVec<Cifra> a, numth::MiVec<Cifra> b, bool limpiar=false ) ;
    //idem
    bool igual(numth::MiVec<Cifra> a, numth::MiVec<Cifra> b, bool limpiar=false ) ;

    /* versiones para uso con longs */
    bool mayorque(numth::MiVec<Cifra> vec, Cifra num, bool limpiar=false )  ;
    bool menorque(numth::MiVec<Cifra> vec, Cifra num, bool limpiar=false )  ;
    bool igual(numth::MiVec<Cifra> vec, Cifra num, bool limpiar=false )  ;


    /* aritmeticas */
    numth::MiVec<Cifra> sumaMP(const numth::MiVec<Cifra>& a,
        const numth::MiVec<Cifra>& b ) ;
    numth::MiVec<Cifra> restaMP(const numth::MiVec<Cifra>& a,
        const numth::MiVec<Cifra>& b ) ;
    numth::MiVec<Cifra> multMP(const numth::MiVec<Cifra>& a,
        const numth::MiVec<Cifra>& b ) ;
    /*         cociente            modulo              */
    //argumentos por valor ya que necesitamos copiarlos de todas formas
    //en el algoritmo para trabajar localmente con ellos
    std::pair< numth::MiVec<Cifra>, numth::MiVec<Cifra> > 
      divMP(numth::MiVec<Cifra> a,
          numth::MiVec<Cifra> b );

    /* version de uso con precision simple */
    MiVec<Cifra> sumaMP(const numth::MiVec<Cifra>& a, const Cifra b ) ;
    MiVec<Cifra> restaMP(const numth::MiVec<Cifra>& a, const Cifra b ) ;
    MiVec<Cifra> restaMP(const Cifra a, const numth::MiVec<Cifra>& b ) ;
    MiVec<Cifra> multMP(const numth::MiVec<Cifra>& a, const Cifra b ) ;
    std::pair< numth::MiVec<Cifra>, numth::MiVec<Cifra> > divMP(const numth::MiVec<Cifra>& a, const Cifra b ) ;


    /** Calculo eficiente del cuadrado. */
    MiVec<Cifra> cuadMP(const numth::MiVec<Cifra>& x);

    void limpiarCeros(numth::MiVec<Cifra>&) throw (Errores::NumeroVacio);

    protected:
    void karatsuba(MiVec<Cifra>& resultado, const MiVec<Cifra>& x, const MiVec<Cifra>& y);
    void cuadKaratsuba(MiVec<Cifra>& resultado, const MiVec<Cifra>& x);
    
    private:
    vCPUBasica<Arch::ARCH> *basicCPUs_; 

  };
}


#endif
