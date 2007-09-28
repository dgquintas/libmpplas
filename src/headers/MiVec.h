/* 
 * $Id$
 */

#ifndef __MIVEC_H
#define __MIVEC_H

#include <vector>


namespace mpplas{

  /** Vector propio de la librería. */
  template<typename T, typename Alloc = std::allocator<T> >
    class MiVec : private std::vector<T, Alloc>
    {
      public:
        MiVec(); /**< Constructor por defecto. */
        MiVec(size_t tam); /**< Construir vector reservando @a tam posiciones */
        MiVec(size_t tam, const T& ini);/**< Construir vector reservando @a tam posiciones 
                                             y rellenándolas con el valor @a ini */

        MiVec(const std::vector<T, Alloc>&); /**< Constructor de copia. */

        MiVec& operator=(const MiVec<T, Alloc>& rhs);

        using std::vector<T, Alloc>::size;
        using std::vector<T, Alloc>::clear;
        using std::vector<T, Alloc>::push_back;
        using std::vector<T, Alloc>::insert;
        using std::vector<T, Alloc>::front;
        using std::vector<T, Alloc>::back;
        using std::vector<T, Alloc>::begin;
        using std::vector<T, Alloc>::end;
        using std::vector<T, Alloc>::pop_back;
        using std::vector<T, Alloc>::erase;
        using std::vector<T, Alloc>::iterator;
        using std::vector<T, Alloc>::const_iterator;
        using std::vector<T, Alloc>::resize;
        using std::vector<T, Alloc>::reverse_iterator;
        using std::vector<T, Alloc>::rbegin;
        using std::vector<T, Alloc>::rend;
        using std::vector<T, Alloc>::reference;
        using std::vector<T, Alloc>::const_reference;
        using std::vector<T, Alloc>::reserve;
//        using std::vector<T, Alloc>::


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


  template<typename T, typename Alloc>
    MiVec<T, Alloc>::MiVec()
    : std::vector<T, Alloc>()
    { }

  template<typename T, typename Alloc>
    MiVec<T, Alloc>::MiVec(const std::vector<T, Alloc>& src)
    : std::vector<T, Alloc>(src)
    { }
 
  template<typename T, typename Alloc>
    MiVec<T, Alloc>::MiVec(size_t tam)
    : std::vector<T, Alloc>(tam)
    { }

  template<typename T, typename Alloc>
    MiVec<T, Alloc>::MiVec(size_t tam, const T& inicio)
    : std::vector<T, Alloc>(tam, inicio)
    { }
  
  template<typename T, typename Alloc>
  MiVec<T, Alloc>& MiVec<T, Alloc>::operator=(const MiVec<T, Alloc>& rhs) { 
    std::vector<T,Alloc>::operator=(rhs);
    return *this;
  }

  

}

#endif
