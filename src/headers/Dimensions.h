#ifndef __DIMENSIONS_H
#define __DIMENSIONS_H

#include <string>

namespace mpplas{

  class Dimensions {
    public:
      Dimensions();
      Dimensions(int n, int m);
      Dimensions(const Dimensions&);

      inline int getRows() const;
      inline int getColumns() const;
      inline int getProduct() const;

      inline void setRows(int n);
      inline void setColumns(int m);
      inline void setBoth(int n, int m);

      inline void swap();

      inline bool operator==(const Dimensions& rhs) const;
      inline bool operator!=(const Dimensions& rhs) const;

      std::string toString() const;

    protected:
      int _n;
      int _m;

  };



  inline int Dimensions::getRows() const{
    return _n;
  }

  inline int Dimensions::getColumns() const{
    return _m;
  }

  inline void Dimensions::setRows(int n){
    _n = n;
  }
  inline void Dimensions::setColumns(int m){
    _m = m;
  }

  inline void Dimensions::setBoth(int n, int m){
    _n = n;
    _m = m;
  }

  inline void Dimensions::swap(){
    const int tmp( _n );
    _n = _m ;
    _m = tmp;

    return;
  }



  inline int Dimensions::getProduct() const{
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
