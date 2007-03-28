/* 
 * $Id$
 */


#ifndef __VECTOR_H
#define __VECTOR_H

#include <vector>
#include <algorithm>
#include <sstream>


#include "err.h"
#include "AlgebraUtils.h"

namespace mpplas 
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

        Vector(const std::string &);

        Vector& operator=(const Vector<T>& rhs){ 
          std::vector<T>::operator=((std::vector<T>)rhs);
          return *this;
        }

        size_t length() const  { return this->size(); }

        Dimensions getDimensions() const;

        std::string toString() const;

        bool operator==(const Vector<T>& rhs) const;

#ifndef RELEASE
        T& operator[](size_t i){ return this->at(i);}
        const T& operator[](size_t i) const { return this->at(i); }
#endif

      protected:
        /** Matrix ouput operator */
        template<typename U> friend std::ostream& operator<<(std::ostream&, const Vector<U>& );
        /** Matrix input operator */
        template<typename U> friend std::istream& operator>>(std::istream&, Vector<U>& ) 
          throw (Errores::InvalidSymbol);
    };

  template<typename T>
    Vector<T>::Vector()
    : std::vector<T>()
    {}
  template<typename T>
    Vector<T>::Vector(size_t size)
    : std::vector<T>(size)
    {}
  template<typename T>
    Vector<T>::Vector(size_t size, const T& ini)
    : std::vector<T>(size, ini)
    {}

  template<typename T>
    Vector<T>::Vector(const Vector<T>& rhs)
    : std::vector<T>(rhs)
    {}
 
  template<typename T>
    Vector<T>::Vector(const std::vector<T>& rhs)
    : std::vector<T>(rhs)
    {}

  template<typename T>
    Vector<T>::Vector(const std::string& str)
    {
      std::istringstream inStream(str);
      operator>>(inStream,*this);
      return;
    }


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

  template<typename T>
    Dimensions Vector<T>::getDimensions() const {
      return Dimensions(1, this->length() );
    }


  template<typename T>
  std::ostream& operator<<(std::ostream& out, const Vector<T>& v){
    typename Vector<T>::const_iterator it;
    out << "[ " ;
    for(it=v.begin(); it != v.end()-1; it++){
      out << *it << " ";
    }
    out << *it << " ]\n" ;
    return out;
  }
 
  template<typename T>
  std::istream& operator>>(std::istream& in, Vector<T>& v) throw (Errores::InvalidSymbol){
    
    v.clear();

    char c;

    in >> c;
    if( !in.good() || c != '[' ){
      throw Errores::InvalidSymbol(std::string(1,c));
    }
    
    T valueRead;

    while( in >> valueRead ){
      v.push_back(valueRead);
      in >> std::ws >> c;
      if( c != ']' ){
        in.putback(c); 
      }
      else{ //reached the final ]
        break; 
      }
    }
  
    return in;
  
  }
 
  
  template<typename T>
    std::string Vector<T>::toString() const {
      std::ostringstream oss;
      oss << (*this);
      return oss.str();
    }


}

#endif
