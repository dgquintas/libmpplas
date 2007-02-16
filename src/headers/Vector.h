/* 
 * $Id$
 */


#ifndef __VECTOR_H
#define __VECTOR_H

#include <vector>
#include <algorithm>

namespace numth
{
  template<typename T>
    class Vector : public std::vector<T>
    {
      public:
        Vector();
        Vector(size_t size);
        Vector(size_t size, const T& ini);
 
        Vector(const Vector<T>& rhs); /**< Copy constructor */
        Vector(const std::vector<T>& rhs);

        Vector& operator=(const Vector<T>& rhs){ 
          std::vector<T>::operator=((std::vector<T>)rhs);
          return *this;
        }

        bool operator==(const Vector<T>& rhs) const;

#ifndef RELEASE
        T& operator[](size_t i){ return this->at(i);}
        const T& operator[](size_t i) const { return this->at(i); }
#endif
    };

  template<class T>
    Vector<T>::Vector()
    : std::vector<T>()
    {}
  template<class T>
    Vector<T>::Vector(size_t size)
    : std::vector<T>(size)
    {}
  template<class T>
    Vector<T>::Vector(size_t size, const T& ini)
    : std::vector<T>(size, ini)
    {}

  template<class T>
    Vector<T>::Vector(const Vector<T>& rhs)
    : std::vector<T>(rhs)
    {}
 
  template<class T>
    Vector<T>::Vector(const std::vector<T>& rhs)
    : std::vector<T>(rhs)
    {}

  template<class T>
    bool Vector<T>::operator==(const Vector<T>& rhs) const
    {
      if( this->size() != rhs.size() ){
        return false;
      }
      else{ //equal dimensions
        return std::equal(this->begin(), this->end(), rhs.begin());
      }
    }


}

#endif
