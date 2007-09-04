/* 
 * $Id: MethodsFactory.cpp 282 2007-05-06 17:12:14Z dgquintas $
 */

#include "MethodsFactory.h"

namespace mpplas{

  //static singleton initialization
  template<>
    std::auto_ptr< MethodsFactory > 
    SingletonMixIn< MethodsFactory >::_singletonInstance(SingletonMixIn< MethodsFactory >::_singletonInstance);

  MethodsFactory::MethodsFactory()
    : SingletonMixIn<MethodsFactory>()
  {}
 

  void MethodsFactory::reset(){
    _methods.clear();
    return;
  }


  /** Destructor.
   * This is called from within the auto_ptr mecanisms, presumably when the 
   * program is about to finish.
   */
  MethodsFactory::~MethodsFactory()
  { 
    std::map<std::string, AbstractMethod* >::iterator it;
    for(it = _methods.begin(); it != _methods.end(); it++){
      delete (*it).second;
      (*it).second = 0;
    }
  }

}
