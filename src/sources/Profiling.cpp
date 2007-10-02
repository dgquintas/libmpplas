/*
 * $Id$
 */

#include "Profiling.h"
#include "SystemInfo.h"

namespace mpplas {

  //static singleton initialization
  template<>
    std::auto_ptr< Profiling > 
    SingletonMixIn< Profiling >::_singletonInstance(SingletonMixIn< Profiling >::_singletonInstance);

  Profiling::Profiling() 
    : SingletonMixIn< Profiling >()  { 
      this->reset();
  }

  Profiling::~Profiling()
  {}

  void Profiling::reset(){
    _profResults.reset();
  }

  
  const ProfResult& Profiling::operator[](int thread) const {
    return _profResults[thread];
  }
  ProfResult& Profiling::operator[](int thread) {
    return _profResults[thread];
  }

  ProfResults& Profiling::getResults() {
    return _profResults;
  }
  const ProfResults& Profiling::getResults() const{
    return _profResults;
  }

  bool Profiling::isEnabled() const {
    return SystemInfo::isProfilingEnabled();
  }


  ////////////////////////////////////////
  
  std::ostream& operator<<(std::ostream& out,const Profiling& prof){
    out << prof._profResults << std::endl;
    return out;
  }

}



