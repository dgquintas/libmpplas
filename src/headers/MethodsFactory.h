/* 
 * $Id: MethodsFactory.h 282 2007-05-06 17:12:14Z dgquintas $
 */

#ifndef __METHODSFACTORY_H
#define __METHODSFACTORY_H

#include <map>
#include <typeinfo>
#include <cassert>
#include <string>

#include "AbstractMethod.h"
#include "Constraints.h"
#include "SingletonMixIn.h"

namespace mpplas{

  /** Library methods repository.
   *
   * Esta clase implementa los mecanismos expuestos en la
   * documentación de teoría (dentro del capítulo "Implementación de
   * algoritmos básicos") en lo relativo al repositorio de
   * funciones. 
   */
  class MethodsFactory : public SingletonMixIn<MethodsFactory> {
    public:
      
      template<typename T> void setFunc(T* const m);
      template<typename T> void getFunc(T* &m) ;

      /** Resets all the methods to their default implementation */
      void reset();

      virtual ~MethodsFactory();

    private:
      MethodsFactory();

      template<typename T> void _set(T* const m);
      template<typename T> void _get(T* &m) ;

      std::map<std::string, AbstractMethod* > _methods;
      friend class SingletonMixIn< MethodsFactory >;
  };



  ///////////////////////////////
  // Templates implementation

  template<typename T>
    void MethodsFactory::getFunc(T* &m) {
      Constraints::must_have_base<T,AbstractMethod>();
      _get_lock();
      _get(m);
      _release_lock();
      return;
    }
  template<typename T>
    void MethodsFactory::setFunc(T* const m){
      Constraints::must_have_base<T,AbstractMethod>();
      _get_lock();
      _set(m);
      _release_lock(); 
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
        assert(m != 0);
      }
    }


  template<typename T>
    void MethodsFactory::_set(T* const m){
      const std::string name(typeid(T).name());
      _methods[name] = m;
    };


}

#endif
    
