/*
 * $Id$
 */

#ifndef __VECTORZ_H
#define __VECTORZ_H

#include "Vector.h"
#include "Z.h"
#include <vector>

namespace mpplas
{
  class VectorZ : public Vector<Z>
  {
    public:
      VectorZ();
      VectorZ(const int size);
      VectorZ(const int size, const Z& ini);
      VectorZ(const VectorZ& rhs); /**< Copy constructor */
      VectorZ(const std::vector<Z>& rhs); /**< Constructor from a std::vector */
      VectorZ(const std::string &); /**< Parsing contructor from a textual representation */

  };



}

#endif
