/* 
 * $Id$
 */

#ifndef __CRT_H
#define __CRT_H

#include "Z.h"
#include "AbstractMethod.h"

namespace mpplas{
  
  class CRTGarner;

  /**  Chinese Remainder Theory interface. */
  class CRT : public AbstractMethod {
    public:
      /** Calculation of the Chinese Remainder Theorem.
       *
       * @param y a vector of mpplas::Z representing the right side of the 
       * congruencies.
       * @param m a vector containing the moduli of the congruences.
       *
       * @return the mpplas::Z satisfying \f$ x \equiv y_i \pmod{m_i}\f$
       * for each \f$i\f$ of the vectors @a y and @a m.
       * */
      virtual Z crt(MiVec<Z> y, MiVec<Z> m) = 0;

      virtual ~CRT(){}

      typedef CRTGarner DFL;
  };


  /* IMPLEMENTATIONS */

   /** Garnet algorithm for the Chinese Remainder Theorem.
   *
   * Described in Handbook of Applied Cryptography, algorithm 14.71
   * 
   * @note This is the library's default implementation for the CRT.
   */
  class CRTGarner : public CRT
  {
    public:
      virtual Z crt(MiVec<Z> y, MiVec<Z> m);

      virtual ~CRTGarner(){}
  };

}

#endif
