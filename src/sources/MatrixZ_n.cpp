#include "MatrixZ_n.h"
#include "MatrixZ.h"


namespace mpplas{

  MatrixZ_n::MatrixZ_n(const Z& mod)
    : Matrix<Z_n>(), _mod(mod)  {
    }

  MatrixZ_n::MatrixZ_n(const int nAndm, const Z& mod)
    : Matrix<Z_n>(), _mod(mod) {
      this->_dims.setBoth(nAndm, nAndm);
      this->_data.resize(nAndm*nAndm, Z_n(Z::ZERO, mod));
    }

  MatrixZ_n::MatrixZ_n(const int n, const int m, const Z& mod)
    : Matrix<Z_n>(), _mod(mod)  { 
      this->_dims.setBoth(n, m);
      this->_data.resize(n*m, Z_n(Z::ZERO, mod));
    }

  MatrixZ_n::MatrixZ_n(const Dimensions& dims, const Z& mod)
    : Matrix<Z_n>(), _mod(mod)  {
      this->_dims = dims;
      this->_data.resize(dims.getProduct(), Z_n(Z::ZERO, mod));
    }
  
  MatrixZ_n::MatrixZ_n(const MatrixZ_n& m)
    : Matrix<Z_n>(m), _mod(m._mod)  {}
  
  MatrixZ_n::MatrixZ_n(const Matrix<Z_n>& m)
    : Matrix<Z_n>(m), _mod(m(0,0).getMod())  { }
  
  MatrixZ_n::MatrixZ_n(const std::string& str, const Z& mod)
    : Matrix<Z_n>() , _mod(mod) {
      MatrixZ tmp(str);
      for(int i = 0; i < tmp.getSize(); i++){
        this->_data.push_back(Z_n( tmp[i], mod ));
      }
      this->_dims = tmp.getDimensions();
    }

  MatrixZ_n& MatrixZ_n::operator=(const MatrixZ_n& src){
    Matrix<Z_n>::operator=(src);
    return *this;
  }


}
  

