#include "MatrixFloat.h"

#include <cmath>

namespace mpplas
{
  MatrixFloat::MatrixFloat()
    : Matrix< SIMDDigit< float4xSIMD_t> , 
              SSEAlloc< SIMDDigit< float4xSIMD_t >, 16 >   
            >()
  {}
  MatrixFloat::MatrixFloat(const MatrixFloat& mat)
    : Matrix< SIMDDigit< float4xSIMD_t> , 
              SSEAlloc< SIMDDigit< float4xSIMD_t >, 16 >   
            >(mat)
  {}

  MatrixFloat::MatrixFloat(const size_t nAndm) {
    _realNumOfCols = 
      (size_t)ceil(((double)nAndm)/SIMDCPU::getElementsPerSIMDDigit< float4xSIMD_t >());
    _data.resize( nAndm * _realNumOfCols );
    _dims.setBoth(nAndm,nAndm);
  }
  MatrixFloat::MatrixFloat(const size_t n, const size_t m) {
    _realNumOfCols = 
      (size_t)ceil(((double)m)/SIMDCPU::getElementsPerSIMDDigit< float4xSIMD_t >());
    _data.resize( n * _realNumOfCols );
    _dims.setBoth(n,m);
  }

  MatrixFloat::MatrixFloat(const std::string& str) {
    std::istringstream inStream(str);
    operator>>(inStream,*this);
    return;
  }

  
  //////////////////////////////////////////////

  MatrixFloat operator-(MatrixFloat m){
//    m *= ((SignedDigit)-1);
    return m;
  }

  std::istream& operator>>(std::istream& in, MatrixFloat& m){

    m._reset();
    m._data.resize(3);
    float* const mData( (float*)&(m._data[0]) );
    char c;
    size_t columnsIni, columnsRead, rows;
    columnsIni = columnsRead = rows = 0;
    bool firstRow = true;

    in >> c;
    if( !in.good() || c != '[' ){
      throw Errors::InvalidSymbol(std::string(1,c));
    }

    float valueRead;

    for(int i=0; ; ){
      while( in >> valueRead ){
        mData[i] = valueRead;
        i++;
        if( firstRow ) {
          columnsIni++;
        }
        else{
          columnsRead++;
          if( columnsRead > columnsIni ){
            throw Errors::Sintactic("Inconsistent number of columns");
          }
        }
        in >> std::ws >> c;
        if( c != ';' && c != ']' ){
          in.putback(c);
        }
        else{ //reached the final ] or ; 
          break; 
        }
      }// inner while
      if( in.fail() ){
        throw Errors::InvalidSymbol(std::string(1,c));
      }

      if( (!firstRow) && (columnsRead != columnsIni) ){
        throw Errors::Sintactic("Inconsistent number of columns");
      }
      columnsRead = 0;

      if( c == ']' ){ 
        m._dims.setRows(rows+1);
        m._dims.setColumns(columnsIni);
        return in;
      }
      rows++;
      firstRow = false;
    } //while(true)




    return in;
  }

  std::ostream& operator<<(std::ostream& out, const MatrixFloat& m){
    Matrix<float,SSEAlloc< SIMDDigit< float4xSIMD_t >, 16 > >* 
      mf( (Matrix<float,SSEAlloc< SIMDDigit< float4xSIMD_t >, 16 > >*)(&m));

    out << (*mf);

    return out;
  }

}
  

