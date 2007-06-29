/* 
 * $Id: Functions.cpp 282 2007-05-06 17:12:14Z dgquintas $
 */

#include "Functions.h"

namespace mpplas{

  //static singleton initialization
  template<>
    const std::auto_ptr< Functions > 
    SingletonMixIn< Functions >::singletonInstance( new Functions() );

  Functions::Functions()
    : SingletonMixIn<Functions>()
  {}


  /** Destructor.
   * This is called from within the auto_ptr mecanisms, presumably when the 
   * program is about to finish.
   */
  Functions::~Functions()
  { 
    std::map<std::string, AbstractMethod* >::iterator it;
    for(it = _methods.begin(); it != _methods.end(); it++){
      delete (*it).second;
      (*it).second = 0;
    }
  }

}
