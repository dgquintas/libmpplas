/*
 * $Id$
 */

#ifndef __UTILS_H
#define __UTILS_H

#include <vector>
#include <string>

#include "BasicTypedefs.h"

namespace mpplas{


  namespace Utils{

    /** Removes leading and trailing whitespaces.
     *
     * Returns a copy of the string @a str with leading and trailing
     * whitespace removed.
     *
     * @param str The string to strip
     * @param SEPSET The set of characters to be considered as whitespaces
     *
     * @return The stripped version of @a str.
     */
    std::string strip(const std::string& str, const std::string SEPSET = " \t");


    /** Splits an string by whitespaces.
     *
     * Returns a vector containing the substrings defined 
     * by the whitespaces in @a str.
     *
     * @param str the string to split.
     *
     * @return a vector containing the substrings defined 
     * by the whitespaces in @a str. */
    std::vector<std::string> split(const std::string& str);


    /** Computes the power of a Digit at compile time. 
     * Based on C++ Templates by David Vandevoorde and Nicolai M. Josuttis.
     * page 302.
     * http://www.josuttis.com/tmplbook/meta/pow3.hpp.html
     *
     * @note This check has no runtime cost whatsoever. */
    template<Digit B, Digit N>
      class CTPow {
        public:
          enum { result = B * CTPow<B,N-1>::result };
      };

    template<Digit B>
      class CTPow<B,1>{
        public:
          enum { result = B } ;
      };



  }
}
#endif
