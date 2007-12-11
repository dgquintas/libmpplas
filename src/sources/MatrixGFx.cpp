#include "MatrixGFx.h"
#include "MatrixZ.h"


namespace mpplas{

  MatrixGFx::MatrixGFx(const GF& generator)
    : Matrix<GFx>(), _gfGenerator(generator)  {
    }

  MatrixGFx::MatrixGFx(const int nAndm, const GF& generator)
    : Matrix<GFx>() , _gfGenerator(generator) {
      this->_dims.setBoth(nAndm, nAndm);
      this->_data.resize(nAndm*nAndm, _gfGenerator.getElement());
    }

  MatrixGFx::MatrixGFx(const int n, const int m, const GF& generator)
    : Matrix<GFx>(), _gfGenerator(generator)  { 
      this->_dims.setBoth(n, m);
      this->_data.resize(n*m, _gfGenerator.getElement());
    }

  MatrixGFx::MatrixGFx(const Dimensions& dims, const GF& generator)
    : Matrix<GFx>(), _gfGenerator(generator)  {

      this->_dims = dims;
      this->_data.resize(dims.getProduct(), _gfGenerator.getElement());
    }
  
  MatrixGFx::MatrixGFx(const MatrixGFx& m)
    : Matrix<GFx>(m), _gfGenerator(m._gfGenerator)  {}
  
  MatrixGFx::MatrixGFx(const Matrix<GFx>& m)
    : Matrix<GFx>(m), _gfGenerator(m(0,0).getGenerator())  { }
  
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
  

