/*
 * $Id$
 */

#ifndef __VECTORR_H
#define __VECTORR_H

#include "Vector.h"
#include "R.h"
#include <vector>

namespace mpplas 
{
  class VectorR : public Vector<R>
  {
    public:
      VectorR();
      VectorR(size_t n);
      VectorR(const VectorR&);
      VectorR(const VectorZ&);
      VectorR(const std::vector<R>&);
      VectorR(const std::vector<Z>&);
      VectorR(const std::string &);

      VectorR& operator+=(const VectorR&) throw (Errores::NonConformantDimensions);
      VectorR& operator+=(const R&);
      VectorR& operator+=(const Cifra);
      VectorR& operator+=(const CifraSigno);

      VectorR& operator-=(const VectorR&);
      VectorR& operator-=(const Z&);
      VectorR& operator-=(const Cifra);
      VectorR& operator-=(const CifraSigno);

      VectorR& operator*=(const Z&);
      VectorR& operator*=(const Cifra);
      VectorR& operator*=(const CifraSigno);

      VectorR& cross(const VectorR&);
      VectorR& dot(const VectorR&);

      VectorR& normalize();

      R& norm();

  };



}

#endif
