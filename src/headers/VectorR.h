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
      VectorR(const size_t size);
      VectorR(const size_t size, const R& ini);
      VectorR(const VectorR& rhs); /**< Copy constructor */
      VectorR(const std::vector<R>& rhs); /**< Constructor from a std::vector */
      VectorR(const std::string &); /**< Parsing contructor from a textual representation */
      //VectorR(const VectorZ&); TODO

  };



}

#endif
