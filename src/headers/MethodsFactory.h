/* 
 * $Id: MethodsFactory.h 282 2007-05-06 17:12:14Z dgquintas $
 */

#ifndef __METHODSFACTORY_H
#define __METHODSFACTORY_H

#include <map>
#include <typeinfo>
#include <string>
#include <pthread.h>

#include "AbstractMethod.h"
#include "Constraints.h"
#include "SingletonMixIn.h"
#include "Errors.h"

namespace mpplas{

  /** Library methods repository.
   *
   */
  class MethodsFactory : public SingletonMixIn<MethodsFactory> {
    public:

      /** Sets an instance of a method. 
       *
       * Establishes an AbstractMethod instance to use as T's default implementation.
       *
       * @pre T must inherit from AbstractMethod.
       *
       * @param[in] m the instance to use as T's implementation henceforth. */
      template<typename T> void setFunc(T* const m);

      /** Retrieve method implementing T's functionality.
       *
       * @pre T must inherit from AbstractMethod.
       *
       * @param[out] m pointer to a reference of T, where the method for T will be returned. */
      template<typename T> void getFunc(T* &m) ;

      /** Resets all the methods to their default implementation */
      void reset();

      virtual ~MethodsFactory();

    private:
      MethodsFactory();
      pthread_mutex_t _mutex;
      /** Thread-safe setting of a method's instance */
      template<typename T> void _set(T* const m);

      /** Thread-safe retrieval of a method's instance */
      template<typename T> void _get(T* &m) ;


      /** Table relating the abstract method T to its actual current implementation. */
      std::map<std::string, AbstractMethod* > _methods;
      friend class SingletonMixIn< MethodsFactory >;
  };



  ///////////////////////////////
  // Templates implementation

  template<typename T>
    void MethodsFactory::getFunc(T* &m) {
      Constraints::must_have_base<T,AbstractMethod>();
#pragma omp critical 
      {
        pthread_mutex_lock( &_mutex);
        _get(m);
        pthread_mutex_unlock( &_mutex);
      }
      return;
    }
  template<typename T>
    void MethodsFactory::setFunc(T* const m){
      Constraints::must_have_base<T,AbstractMethod>();
#pragma omp critical 
      {
        pthread_mutex_lock( &_mutex);
        _set(m);
        pthread_mutex_unlock( &_mutex);
      }
      return;
    }

  template<typename T>
    void MethodsFactory::_get(T* &m) {
      const std::string name(typeid(T).name());
      if( _methods.find(name) == _methods.end() ){
        // if no method instance has been set for method type,
        // its default (::DFL type) one is used.
        T* const newInstance = new typename T::DFL(); 
        _methods[name] = newInstance;
        m = newInstance;
      }
      else{
        m = dynamic_cast<T*>(_methods[name]);
        if(m == NULL){
          throw Errors::Internal("dynamic_cast failed while retrieving method at MethodsFactory");
        }
      }
    }


  template<typename T>
    void MethodsFactory::_set(T* const m){
      const std::string name(typeid(T).name());
      _methods[name] = m;
    };


}

#endif
    
