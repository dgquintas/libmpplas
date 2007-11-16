#include "MatrixGFx.h"
#include "MatrixZ.h"


namespace mpplas{

  MatrixGFx::MatrixGFx(const GF& generator)
    : Matrix<GFx>(), _gfGenerator(generator)  {
    }

  MatrixGFx::MatrixGFx(const int nAndm, const GF& generator)
    : Matrix<GFx>(nAndm) , _gfGenerator(generator) {
      for(int i = 0; i < this->_data.size(); i++){
        this->_data[i] = _gfGenerator.getElement(Z::ZERO);
      }
    }

  MatrixGFx::MatrixGFx(const int n, const int m, const GF& generator)
    : Matrix<GFx>(n,m), _gfGenerator(generator)  {
      for(int i = 0; i < this->_data.size(); i++){
        this->_data[i] = _gfGenerator.getElement(Z::ZERO);
      }
    }

  MatrixGFx::MatrixGFx(const Dimensions& dims, const GF& generator)
    : Matrix<GFx>(dims), _gfGenerator(generator)  {
          for(int i = 0; i < this->_data.size(); i++){
        this->_data[i] = _gfGenerator.getElement(Z::ZERO);
      }

    }
  
  MatrixGFx::MatrixGFx(const MatrixGFx& m)
    : Matrix<GFx>(m), _gfGenerator(m._gfGenerator)  {}
  
  MatrixGFx::MatrixGFx(const Matrix<GFx>& m)
    : Matrix<GFx>(m), _gfGenerator(m(0,0).getGenerator())  {
          for(int i = 0; i < this->_data.size(); i++){
        this->_data[i] = _gfGenerator.getElement( this->operator[](i).getIntegerValue() );
      }
    }
  
  MatrixGFx::MatrixGFx(const std::string& str, const GF& generator)
    : Matrix<GFx>() , _gfGenerator(generator) {
      MatrixZ tmp(str);
      for(int i = 0; i < tmp.getSize(); i++){
        this->_data.push_back(_gfGenerator.getElement( tmp[i] ));
      }
      this->_dims = tmp.getDimensions();
    }

  MatrixGFx& MatrixGFx::operator=(const MatrixGFx& src){
    Matrix<GFx>::operator=(src);
    return *this;
  }


}
  

