/* 
 * $Id$
 */

#ifndef __MPPDATATYPE_H
#define __MPPDATATYPE_H

#include <string>

namespace mpplas{

  class MPPDataType {
    public:
      virtual std::string toString() const = 0;
  };

}

#endif
