/*
 * $Id$
 */

#ifndef __VECTORFLOAT_H
#define __VECTORFLOAT_H

#include <vector>
#include <string>

#include "Vector.h"

namespace mpplas
{
  class VectorFloat : public Vector<float>
  {
    public:
      VectorFloat();
      VectorFloat(const size_t size);
      VectorFloat(const size_t size, const Z& ini);
      VectorFloat(const VectorFloat& rhs); /**< Copy constructor */
      VectorFloat(const std::vector<float>& rhs); /**< Constructor from a std::vector */
      VectorFloat(const std::string &); /**< Parsing contructor from a textual representation */

      float dot(const VectorFloat& rhs);
  };



}

#endif
