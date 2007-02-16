/* 
 * $Id$
 */

#ifndef __MATRIX_H
#define __MATRIX_H


#include "err.h"
#include "Vector.h"

namespace numth
{
  template<typename T>
    class Matrix
    {
      public:
        Matrix()
          : _n(1), _m(1), _data(1) { };
        Matrix(const size_t nAndm) 
          : _n(nAndm), _m(nAndm), _data(nAndm*nAndm) {} ;
        Matrix(const size_t n, const size_t m)
          : _n(n), _m(m), _data(n*m) {} ;

        Matrix(const Matrix<T>& rhs)
          : _data(rhs._data) {}; //copy constr

        Matrix<T>& operator=(const Matrix<T>& rhs){
          _data = rhs._data;
        }

        Vector<T> operator[](size_t i) const; 

        inline T& operator()(size_t i, size_t j);
        inline const T& operator()(size_t i, size_t j) const;

        bool operator==(const Matrix<T>& rhs) const;

        Matrix<T>& transpose();

        void reset();


        size_t getNumberRows() const 
        {return _n;};
        size_t getNumberColumns() const
        {return _m;};

        void setNumberRows(const size_t newN)
        {
          if( newN == _n ){ //do nothing
            return;
          }
          else{
            //the extra space will be filled with the default
            //constructor's value for the type T
            _data.resize( _m * newN );
            _n = newN;
          }
        }

        void setNumberColumns(const size_t newM)
        {
          if(newM == _m ){ //do nothing
            return;
          }

          typename Vector<T>::iterator it;
          if( newM > _m) {
            _data.reserve( _n * newM );
            for(it = _data.begin() + _m; it <= _data.end(); it += (_m + (newM-_m))){
              _data.insert(it, newM - _m, T() );
            }
          }
          else{ //newM < _m
             for(it = _data.begin() + _m-1; it < _data.end(); it += _m - 1){
              _data.erase(it);
            }
          }
          _m = newM;
          
        }


      protected:
        size_t _n,_m;

        Vector<T> _data; /**< Row-major vector representation of the matrix */

        /** Matrix ouput operator */
        template<typename U> friend std::ostream& operator<<(std::ostream&, const Matrix<U>& );
        /** Matrix input operator */
        template<typename U> friend std::istream& operator>>(std::istream&, Matrix<U>& ) 
          throw (Errores::Sintactic);
    };

  template<typename T>
    Vector<T> Matrix<T>::operator[](size_t i) const{
      Vector<T> v(_m);

      typename Vector<T>::const_iterator it;
      it = _data.begin() + i*_m;
      v.insert(v.begin(), it, it + _m);

      return v;
    }


  template<typename T>
    inline T& Matrix<T>::operator()(size_t i, size_t j){
      return _data[(i*_m) + j];
    }
  template<typename T>
    inline const T& Matrix<T>::operator()(size_t i, size_t j) const{
      return _data[(i*_m) + j];
    }

  template<typename T>
    bool Matrix<T>::operator==(const Matrix<T>& rhs) const{
      return this->_data == rhs._data();
    }


  template<typename T>
    Matrix<T>& Matrix<T>::transpose(){
#pragma omp parallel for schedule(guided) 
      for(int i=0; i < _n-1; i++){
        for(int j=1; j < _m; j++){
          T tmp(this->operator()(i,j));
          this->operator()(i,j) = this->operator()(j,i);
          this->operator()(j,i) = tmp;
        }
      }
    }

  template<typename T>
  std::ostream& operator<<(std::ostream& out, const Matrix<T>& m){
    for(int i=0; i < m._n; i++){
      out << "[" ;
      for(int j=0; j < m._m; j++ ){
        out << " " << m(i,j);
      }
      out << " ]\n" ;
    }
    return out;
  }
 
  template<typename T>
  std::istream& operator>>(std::istream& in, Matrix<T>& m) throw (Errores::Sintactic){
    for(int i=0; i < (m._m * m._n) ; i++){
      in >> m._data[i];
    }

    return in;
  
  }


}

#endif
