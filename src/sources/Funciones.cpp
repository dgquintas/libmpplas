/* 
 * $Id$
 */

#include <memory> //for auto_ptr
#include <algorithm> //for for_each
#include "Funciones.h"

namespace mpplas{
  template<class T> struct destroyerFunctor: public unary_function<T, void>
  {
    destroyerFunctor(ostream& out) : os(out), count(0) {}
    void operator() (T x) { os << x << ' '; ++count; }
    ostream& os;
    int count;
  };

  //static singleton initialization
  const auto_ptr< Funciones > Funciones::singletonInstance( new Funciones() );

  Funciones* Funciones::getInstance() {
    return singletonInstance.get();
  }

  /** Destructor.
   * This is called from within the auto_ptr mecanisms, presumably when the 
   * program is about to finish.
   */
  Funciones::~Funciones()
  { 
    map<string, AbstractMethod* >::iterator it;
    for(it = _methods.begin(); it != _methods.end(); it++){
      delete (*it).second;
      (*it).second = 0;
    }
#ifdef _OPENMP
      omp_destroy_nest_lock(&lock);
#endif


  }


  //_____________________________________________________________________//

}
