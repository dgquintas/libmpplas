/*
 * $Id$
 */

#ifndef __UTILS_H
#define __UTILS_H

#include <string>

namespace mpplas{

  namespace Utils{

    /** Returns a copy of the string @a str with leading and trailing
     * whitespace removed.
     *
     * @param str The string to strip
     * @param SEPSET The set of characters to be considered as whitespaces
     *
     * @return The stripped version of @a str.
     */
    std::string strip(const std::string& str, const std::string SEPSET = " \t"){

      const std::string::size_type first = str.find_first_not_of(SEPSET);
      return ( first==std::string::npos ) ? 
        std::string()  
        :
        str.substr(first, str.find_last_not_of(SEPSET)-first+1);
    }

  }
}
#endif
