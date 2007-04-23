#ifndef __ALGEBRAUTILS_H
#define __ALGEBRAUTILS_H

#include <string>
#include <sstream>

namespace mpplas{

  class Dimensions {
    public:
      Dimensions();
      Dimensions(size_t n, size_t m);
      Dimensions(const Dimensions&);

      inline size_t getRows() const;
      inline size_t getColumns() const;
      inline size_t getProduct() const;

      inline void setRows(size_t n);
      inline void setColumns(size_t m);
      inline void setBoth(size_t n, size_t m);

      inline void swap();

      inline bool operator==(const Dimensions& rhs) const;
      inline bool operator!=(const Dimensions& rhs) const;

      std::string toString() const;

    protected:
      size_t _n;
      size_t _m;

  };



  inline size_t Dimensions::getRows() const{
    return _n;
  }

  inline size_t Dimensions::getColumns() const{
    return _m;
  }

  inline void Dimensions::setRows(size_t n){
    _n = n;
  }
  inline void Dimensions::setColumns(size_t m){
    _m = m;
  }

  inline void Dimensions::setBoth(size_t n, size_t m){
    _n = n;
    _m = m;
  }

  inline void Dimensions::swap(){
    const size_t tmp( _n );
    _n = _m ;
    _m = tmp;

    return;
  }



  inline size_t Dimensions::getProduct() const{
    return _n * _m;
  }


  inline bool Dimensions::operator==(const Dimensions& rhs) const{
    return (_n == rhs._n) && (_m == rhs._m);
  }
  inline bool Dimensions::operator!=(const Dimensions& rhs) const{
    return !(this->operator==(rhs));
  }


}

#endif
