/* 
 * $Id$
 */

#ifndef __MPPDATATYPE_H
#define __MPPDATATYPE_H

#include <string>
#include <sstream>

namespace mpplas{

  /** Base class for the library types. */
  class MPPDataType {
    public:
      /** Get a text representation of the data.
       *
       * @return A std::string representing the standard textual representation of the data.
       */
      virtual std::string toString() const = 0;
  
      /** Get a human readable representation of the data.
       *
       * @return A std::string representing a human readabldablee representation of the data.
       */
      virtual std::string toHRString() const = 0;


      virtual ~MPPDataType(){}
  };

}

#endif
