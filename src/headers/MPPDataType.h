/* 
 * $Id$
 */

#ifndef __MPPDATATYPE_H
#define __MPPDATATYPE_H

#include <string>
#include <sstream>

namespace mpplas{

  class MPPDataType {
    public:
      /** Get a text representation of the data.
       *
       * @return A std::string representing the standard textual representation of the data.
       */
      virtual std::string toString() const = 0;

  };

}

#endif
