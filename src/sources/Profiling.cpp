/*
 * $Id$
 */

#include "Profiling.h"
#include "SystemInfo.h"

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

  size_t Profiling::getNumThreads() const{
    return _profResults.getNumThreads();
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


