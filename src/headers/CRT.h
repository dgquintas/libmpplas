/* 
 * $Id$
 */

#ifndef __CRT_H
#define __CRT_H

#include "Z.h"
#include "AbstractMethod.h"

namespace mpplas{
  
  class CRTGarner;

  /** Interfaz para implementaciones para el c�lculo del Teorema del
   * Resto Chino (CRT de sus siglas en ingl�s).
   *
   * Clase base para algoritmos que implementen el Teorema del Resto
   * Chino.
   * 
   */
  class CRT : public AbstractMethod {
    public:
      /** C�lculo del Teorema del Resto Chino.
       *
       * @param y Vector de enteros representando las partes derechas
       * de las congruencias a satisfacer.
       * @param m Vector de m�dulos de las congruencias. 
       *
       * @return Entero que satisfaga \f$ x \equiv y_i \pmod{m_i}\f$
       * para cada \f$i\f$ de los vectores @a y y @a m.
       * */
      virtual Z crt(MiVec<Z> y, MiVec<Z> m) = 0;

      virtual ~CRT(){}

      typedef CRTGarner DFL;
  };


  /* IMPLEMENTACIONES */

   /** Algoritmo de Garnet para el Teorema del Resto Chino.
   *
   * Descrito en Handbook of Applied Cryptography, algoritmo 14.71
   * 
   * @note Es el m�todo que la librer�a utiliza por omisi�n.
   */
  class CRTGarner : public CRT
  {
    public:
      virtual Z crt(MiVec<Z> y, MiVec<Z> m);

      virtual ~CRTGarner(){}
  };

}

#endif
