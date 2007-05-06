/* 
 * $Id$
 */

#include "Funciones.h"

namespace mpplas{

  //static singleton initialization
  template<>
    const std::auto_ptr< Funciones > 
    SingletonMixIn< Funciones >::singletonInstance( new Funciones() );

  Funciones::Funciones()
    : SingletonMixIn<Funciones>()
  {}


  /** Destructor.
   * This is called from within the auto_ptr mecanisms, presumably when the 
   * program is about to finish.
   */
  Funciones::~Funciones()
  { 
    std::map<std::string, AbstractMethod* >::iterator it;
    for(it = _methods.begin(); it != _methods.end(); it++){
      delete (*it).second;
      (*it).second = 0;
    }
  }

}
