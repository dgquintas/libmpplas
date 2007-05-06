/* 
 * $Id$
 */

#ifndef __FUNCIONES_H
#define __FUNCIONES_H

#include "AbstractMethod.h"
#include <map>
#include <string>
#include <typeinfo>
#include <iostream>
#include <cassert>
#include <memory>

#include "SingletonMixIn.h"

namespace mpplas{

  /** Clase repositorio de funciones.
   *
   * Esta clase implementa los mecanismos expuestos en la
   * documentación de teoría (dentro del capítulo "Implementación de
   * algoritmos básicos") en lo relativo al repositorio de
   * funciones. 
   */
  class Funciones : public SingletonMixIn<Funciones>
  {
    public:

      void setFunc(AbstractMethod* const m){
        _get_lock();
        _set(m);
        _release_lock(); 
        return;
      }

      template<typename T>
        void getFunc(T* &m) {
          _get_lock();
          _get(m);
          _release_lock();
          return;
        }

      virtual ~Funciones();

    private:
      Funciones();

      void _set(AbstractMethod* const m){
        const std::string name(typeid(*m).name());
        _methods[name] = m;
      };


      template<typename T>
        void _get(T* &m) {
          const std::string name(typeid(T).name());
          if( _methods.find(name) == _methods.end() ){
            // if not method instance has been set for method type,
            // its default (::DFL type) one is used.
            T* newInstance = new typename T::DFL(); 
            _methods[name] = newInstance;
            m = newInstance;
          }
          else{
            m = dynamic_cast<T*>(_methods[name]);
            assert(m != 0);
          }
        }


      std::map<std::string, AbstractMethod* > _methods;

      friend class SingletonMixIn< Funciones >;

  };


}
      
#endif
    
