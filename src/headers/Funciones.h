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

#ifdef _OPENMP
#include <omp.h>
#endif

using namespace std;

namespace numth{

  /** Clase repositorio de funciones.
   *
   * Esta clase implementa los mecanismos expuestos en la
   * documentación de teoría (dentro del capítulo "Implementación de
   * algoritmos básicos") en lo relativo al repositorio de
   * funciones. 
   */
  class Funciones
  {
    public:

      static Funciones* getInstance() ;

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


      ~Funciones();

    private:
#ifdef _OPENMP
      omp_nest_lock_t lock;
#endif

      Funciones() {
#ifdef _OPENMP
        omp_init_nest_lock(&lock);
#endif
      };


      inline void _get_lock(){
#ifdef _OPENMP
        omp_set_nest_lock(&lock);
#endif
          //if not defined, there's no need to do anything
          return;
      }
      
      inline void _release_lock(){
#ifdef _OPENMP
        omp_unset_nest_lock(&lock);
#endif
          //if not defined, there's no need to do anything
          return;
      }



      static const auto_ptr< Funciones > singletonInstance;

      void _set(AbstractMethod* const m){
        const string name(typeid(*m).name());
        _methods[name] = m;
      };


      template<typename T>
        void _get(T* &m) {
          const string name(typeid(T).name());
          if( _methods.find(name) == _methods.end() ){
            T* newInstance = new typename T::DFL();
            _methods[name] = newInstance;
            m = newInstance;
          }
          else{
            m = dynamic_cast<T*>(_methods[name]);
            assert(m != 0);
          }
        }


      map<string, AbstractMethod* > _methods;

  };


}
      
#endif
    
