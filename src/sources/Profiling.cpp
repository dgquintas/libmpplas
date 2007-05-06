/*
 * $Id$
 */

#include "Profiling.h"

namespace mpplas {

  //static singleton initialization
  template<>
    const std::auto_ptr< Profiling > 
    SingletonMixIn< Profiling >::singletonInstance( new Profiling() );

  Profiling::Profiling() 
    : SingletonMixIn< Profiling >()  { 
      this->reset();
  }

  Profiling::~Profiling()
  {}

  void Profiling::reset(){
    _profResults.reset();
  }

  
  const ProfResult& Profiling::operator[](size_t thread) const {
    return _profResults[thread];
  }
  ProfResult& Profiling::operator[](size_t thread) {
    return _profResults[thread];
  }

  ProfResults& Profiling::getResults() {
    return _profResults;
  }
  const ProfResults& Profiling::getResults() const{
    return _profResults;
  }


  ////////////////////////////////////////
  
  std::ostream& operator<<(std::ostream& out,const Profiling& prof){
    out << prof._profResults << std::endl;
    return out;
  }

}



