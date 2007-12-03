#include <cassert>
#include <sstream>
#include <iterator>


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

    std::vector<std::string> split(const std::string& str) {
      std::istringstream is(str);
      return std::vector<std::string> (std::istream_iterator<std::string>(is),
          std::istream_iterator<std::string>());
    }

  
  } // namespace Utils
} //namespace mpplas

