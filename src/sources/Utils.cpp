#include <cassert>

#include "Utils.h"
#include "Constants.h"

namespace mpplas{ 
  namespace Utils {
    std::string strip(const std::string& str, 
        const std::string SEPSET){

      const std::string::size_type first = str.find_first_not_of(SEPSET);
      return ( first==std::string::npos ) ? 
        std::string()  
        :
        str.substr(first, str.find_last_not_of(SEPSET)-first+1);
    }


    ///////////////////////////////////////////////


  
  } // namespace Utils
} //namespace mpplas

