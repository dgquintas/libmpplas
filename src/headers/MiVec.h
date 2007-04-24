/* 
 * $Id$
 */

#ifndef __MIVEC_H
#define __MIVEC_H

#include <vector>


namespace mpplas{

  /** Vector propio de la librería. */
  template<class T>
    class MiVec : public std::vector<T>
    {
      public:
        MiVec(); /**< Constructor por defecto. */
        MiVec(size_t tam); /**< Construir vector reservando @a tam posiciones */
        MiVec(size_t tam, const T& ini);/**< Construir vector reservando @a tam posiciones 
                                             y rellenándolas con el valor @a ini */

        MiVec(const MiVec<T>&); /**< Constructor de copia. */

        MiVec& operator=(const MiVec<T>& otro)
        { 
          std::vector<T>::operator=(otro);
          return *this;
        }


#ifndef RELEASE
        /** Operador de acceso.
         *
         * Acceso al elemento @a i del vector. Si tal posición no
         * existe, lanza una excepción de tipo std::out_of_range.
         *
        *  @par Complejidad:
       *       \f$O(1)\f$
        *
         * 
         * @param i La posición del vector a la que acceder.
         * @return Referencia al @a i -ésimo elemento del vector.
         * */
       T& operator[](size_t i){ return this->at(i);}
         /** Operador de acceso constante.
         *
         * Acceso al elemento @a i del vector. Si tal posición no
         * existe, lanza una excepción de tipo std::out_of_range.
         *  @par Complejidad:
         *      \f$O(1)\f$
         *
         * @param i La posición del vector a la que acceder.
         * @return Referencia constante al @a i -ésimo elemento del vector.
         * 
         */
       const T& operator[](size_t i) const { return this->at(i); }
#endif

    };


  template<class T>
    MiVec<T>::MiVec()
    : std::vector<T>()
    { }

  template<class T>
    MiVec<T>::MiVec(const MiVec<T>& otro)
    : std::vector<T>(otro)
    { }
 
  template<class T>
    MiVec<T>::MiVec(size_t tam)
    : std::vector<T>(tam)
    { }

  template<class T>
    MiVec<T>::MiVec(size_t tam, const T& inicio)
    : std::vector<T>(tam, inicio)
    { }

  

}

#endif
