/* 
 * $Id$
 */

#ifndef __CRT_H
#define __CRT_H

#include "Z.h"

namespace numth{
   
  /** Interfaz para implementaciones para el cálculo del Teorema del
   * Resto Chino (CRT de sus siglas en inglés).
   *
   * Clase base para algoritmos que implementen el Teorema del Resto
   * Chino.
   * 
   */
  class CRT{
    public:
      /** Cálculo del Teorema del Resto Chino.
       *
       * @param y Vector de enteros representando las partes derechas
       * de las congruencias a satisfacer.
       * @param m Vector de módulos de las congruencias. 
       *
       * @return Entero que satisfaga \f$ x \equiv y_i \pmod{m_i}\f$
       * para cada \f$i\f$ de los vectores @a y y @a m.
       * */
      virtual Z crt(MiVec<Z> y, MiVec<Z> m) = 0;

      virtual ~CRT(){}
  };


  /* IMPLEMENTACIONES */

   /** Algoritmo de Garnet para el Teorema del Resto Chino.
   *
   * Descrito en Handbook of Applied Cryptography, algoritmo 14.71
   * 
   * @note Es el método que la librería utiliza por omisión.
   */
  class CRTGarner : public CRT
  {
    public:
      virtual Z crt(MiVec<Z> y, MiVec<Z> m);

      virtual ~CRTGarner(){}
  };
  typedef CRTGarner CRTDFL;

}

#endif
