/*
 * $Id$
 */

#ifndef __VECTORZ_H
#define __VECTORZ_H

#include "Vector.h"
#include "Z.h"
#include <vector>

namespace numth
{
  class VectorZ : public Vector<Z>
  {
    public:
      VectorZ();
      VectorZ(size_t n);
      VectorZ(const VectorZ&);
      VectorZ(const std::vector<Z>&);
      VectorZ(const std::string &);

      VectorZ& operator+=(const VectorZ&) throw (Errores::NonConformantDimensions);
      VectorZ& operator+=(const Z&);
      VectorZ& operator+=(const Cifra);
      VectorZ& operator+=(const CifraSigno);

      VectorZ& operator-=(const VectorZ&);
      VectorZ& operator-=(const Z&);
      VectorZ& operator-=(const Cifra);
      VectorZ& operator-=(const CifraSigno);

      VectorZ& operator*=(const Z&);
      VectorZ& operator*=(const Cifra);
      VectorZ& operator*=(const CifraSigno);

      VectorZ& cross(const VectorZ&);
      VectorZ& dot(const VectorZ&);

      VectorZ& normalize();

      Z& norm();

  };



}

#endif
