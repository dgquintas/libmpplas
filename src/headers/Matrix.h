/* 
 * $Id$
 */

#ifndef __MATRIX_H
#define __MATRIX_H

#include <string>
#include <iterator>
#include <cassert>
#include <sstream>
#include <cstring>
#include <iomanip>

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

        Matrix(const std::string& str);

        Matrix<T>& operator=(const Matrix<T>& rhs){
          _data = rhs._data;
          _n = rhs._n;
          _m = rhs._m;
        }

        Vector<T> operator[](size_t i) const; 

        inline T& operator()(size_t i, size_t j);
        inline const T& operator()(size_t i, size_t j) const;

        bool operator==(const Matrix<T>& rhs) const;

        Matrix<T>& transpose();
        
        void setDiagonal(T n);

        std::string toString() const;

        size_t getNumRows() const 
        {return _n;};
        size_t getNumColumns() const
        {return _m;};

        void setNumRows(const size_t newN)
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

        void setNumColumns(const size_t newM)
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

        void reset();

        /** Matrix ouput operator */
        template<typename U> friend std::ostream& operator<<(std::ostream&, const Matrix<U>& );
        /** Matrix input operator */
        template<typename U> friend std::istream& operator>>(std::istream&, Matrix<U>& ) 
          throw (Errores::InvalidSymbol);
    };

  template<typename T>
    Matrix<T>::Matrix(const std::string& str){
      std::istringstream inStream(str);
      operator>>(inStream,*this);
      return;
    }

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
      return this->_data == rhs._data;
    }
 
  template<typename T>
    void Matrix<T>::reset() {
      _data.clear();
      _m = _n = 0;
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
    void Matrix<T>::setDiagonal(T n){
      typename Vector<T>::iterator it;
      for(it = _data.begin(); it < _data.end(); it+= _m +1){
        *it = n;
      }
      return;
    }



  template<typename T>
    std::string Matrix<T>::toString() const {
      std::string res("[ ");
      for(int i=0; i < this->_n; i++){
        for(int j=0; j < this->_m; j++){
          std::ostringstream oss;
          oss << (this->operator()(i,j));
          res += oss.str();
          res += " ";
        }
        if( i != this->_n-1){
          res += "; ";
        }
      }
      res += " ]";

      return res;
    }


  template<typename T>
  std::ostream& operator<<(std::ostream& out, const Matrix<T>& m){
    const size_t COLS = m.getNumColumns();
    size_t maxWidth[COLS];
    memset(maxWidth, 0, COLS*sizeof(size_t));

    for(int i=0; i < m._data.size(); i++){
      std::ostringstream oss;
      oss << m._data[i];
      maxWidth[i % COLS] = std::max(oss.str().size()+2, maxWidth[i % COLS]);
    }

    for(int i=0; i < m._n; i++){
      out << "[" ;
      for(int j=0; j < m._m; j++ ){
        out << std::setw(maxWidth[j]) << std::right << m(i,j);
      }
      out << " ]\n" ;
    }
    return out;
  }
 
  template<typename T>
  std::istream& operator>>(std::istream& in, Matrix<T>& m) throw (Errores::InvalidSymbol){
    
    m.reset();

    char c;
    size_t columnsIni, columnsRead, rows;
    columnsIni = columnsRead = rows = 0;

    in >> c;
    if( !in.good() || c != '[' ){
      throw Errores::InvalidSymbol(std::string(1,c));
    }
    
    T valueRead;


    while( in >> valueRead ){
      m._data.push_back(valueRead);
      columnsIni++;
    }
    in.clear();
    in >> c;
    if( c == ']' ){ // single-rowed matrix
      m._n = 1;
      m._m = columnsIni;
      return in;
    }
    if( c != ';' ){
      throw Errores::InvalidSymbol(std::string(1,c));
    }
    rows++;
    //finished reading first row
    //keep reading til we find the matching ]
    //attencion has to be paid to the number of 
    //elements per row, now the # of columns has been defined
    
    while(true){
      while( in >> valueRead ){
        m._data.push_back(valueRead);
        columnsRead++;
      }
      
      if( columnsRead != columnsIni ){
        throw Errores::Sintactic("Incoherent number of columns");
      }
      columnsRead = 0;
      in.clear();
      
      in >> c;

      if( c == ']' ){ 
        m._n = (rows+1);
        m._m = columnsIni;
        return in;
      }
      if( c != ';'){
        throw Errores::InvalidSymbol(std::string(1,c));
      }
      rows++;
    }

    assert(false); //shouldn't be reaching this point
    return in;
  
  }


}

#endif
