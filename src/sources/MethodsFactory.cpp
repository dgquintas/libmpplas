/* 
 * $Id: MethodsFactory.cpp 282 2007-05-06 17:12:14Z dgquintas $
 */

#include "MethodsFactory.h"


namespace mpplas{

  //static singleton initialization
  template<>
    std::auto_ptr< MethodsFactory > 
     SingletonMixIn< MethodsFactory >::_singletonInstance( new MethodsFactory() );

  template<>
    pthread_mutex_t SingletonMixIn< MethodsFactory >::mutex = PTHREAD_MUTEX_INITIALIZER;


  MethodsFactory::MethodsFactory()
    : SingletonMixIn<MethodsFactory>(){
      pthread_mutexattr_t mutattr;
      pthread_mutexattr_init(&mutattr);
      pthread_mutexattr_settype(&mutattr, PTHREAD_MUTEX_RECURSIVE);
      pthread_mutex_init(&_mutex, &mutattr);

    }
  
 

  void MethodsFactory::reset(){
#pragma omp critical
    {
      pthread_mutex_lock( &_mutex);
      _methods.clear();
      pthread_mutex_unlock( &_mutex);
    }
    return;
  }


  /** Destructor.
   * This is called from within the auto_ptr mecanisms, presumably when the 
   * program is about to finish.
   */
  MethodsFactory::~MethodsFactory() { 
    std::map<std::string, AbstractMethod* >::iterator it;
    for(it = _methods.begin(); it != _methods.end(); it++){
      delete (*it).second;
      (*it).second = 0;
    }
  }

}
