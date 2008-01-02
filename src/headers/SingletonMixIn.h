/*
 * $Id$
 */


#ifndef __SINGLETONMIXIN_H
#define __SINGLETONMIXIN_H

#include <memory>
#include <cassert>


namespace mpplas{

  /** Singleton mixin template.
   *
   * It exports the methods @a getInstance and @a getReference, which return a pointer
   * and a reference, respectively, to the singleton instance of class that has been 
   * "mixed in" with this template.
   *
   * This singleton mixin implementation takes care of OpenMP synchronization issues.
   * It is therefore @e thread-safe in an OpenMP context.
   */
  template<typename T>
    class SingletonMixIn{
      public:
        /** Get a pointer to the singleton instance.
         *
         * @return A pointer to the singleton instance.
         */
        static T* getInstance(){
          T* const ptr = (_getInstanceAutoPtr()).get(); 
          assert( ptr != 0 );
          return ptr;
        }
        
        /** Get a reference to the singleton instance.
         *
         * @return A reference to the singleton instance.
         */
        static T& getReference(){
          return *(_getInstanceAutoPtr());
        }


        virtual ~SingletonMixIn(){
        }

        
      protected:
        SingletonMixIn() {
        };



      private:

        /** Returns the smart pointer to the singleton instance. 
         *
         * Because the smart pointer is itself statically initialized,
         * there are not thread-safety issues.
         */
        static const std::auto_ptr< T >& _getInstanceAutoPtr(){
//          pthread_mutex_lock( &mutex );
//          if( _singletonInstance.get() == 0 ){
//            _singletonInstance.reset( new T );
//          }
//          pthread_mutex_unlock( &mutex );

          return _singletonInstance;
        }

        static std::auto_ptr< T > _singletonInstance;
        static pthread_mutex_t mutex;

        

  };
}


#endif
