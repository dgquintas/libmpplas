
#include "omp_mock.h"

#include <unistd.h>

//////////////////////////////////////////
//   IMPLEMENTATION
//////////////////////////////////////////

  template<typename T, typename Alloc>
  Matrix<T, Alloc>::Matrix()
: _dims(0,0)
{}

  template<typename T, typename Alloc>
  Matrix<T, Alloc>::Matrix(const size_t nAndm) 
: _dims(nAndm,nAndm), _data(nAndm*nAndm)
{} 

  template<typename T, typename Alloc>
  Matrix<T, Alloc>::Matrix(const size_t n, const size_t m)
: _dims(n,m), _data(n*m)
{} 

  template<typename T, typename Alloc>
  Matrix<T, Alloc>::Matrix(const Dimensions& dims)
: _dims(dims), _data(_dims.getProduct())
{}

  template<typename T, typename Alloc>
  Matrix<T, Alloc>::Matrix(const Matrix<T, Alloc>& rhs)
:  _dims(rhs._dims), _data(rhs._data)
{}

template<typename T, typename Alloc>
Matrix<T, Alloc>::Matrix(const std::string& str){
  std::istringstream inStream(str);
  operator>>(inStream,*this);
  return;
}

  template<typename T, typename Alloc>
  Matrix<T, Alloc>::Matrix(const std::vector<T, Alloc>& rhs, const Dimensions& dims)
: _data(rhs), _dims(dims)
{
  size_t const prod(_dims.getProduct());
  if( prod != _data.size() ){
    //fill with the element's default value or
    //discard extra values
    _data.resize( prod , T() );
  }
}



////////////////////////////////////////////////////



template<typename T, typename Alloc>
Matrix<T, Alloc>& Matrix<T, Alloc>::operator=(const Matrix<T, Alloc>& rhs){
  _data = rhs._data;
  _dims = rhs._dims;

  return *this;
}



template<typename T, typename Alloc>
inline T& Matrix<T, Alloc>::operator[](size_t i){
  return _data[i];
}
template<typename T, typename Alloc>
inline const T& Matrix<T, Alloc>::operator[](size_t i) const{
  return _data[i];
}


template<typename T, typename Alloc>
inline T& Matrix<T, Alloc>::operator()(size_t i){
  return _data[i];
}
template<typename T, typename Alloc>
inline const T& Matrix<T, Alloc>::operator()(size_t i) const{
  return _data[i];
}

template<typename T, typename Alloc>
inline T& Matrix<T, Alloc>::operator()(size_t i, size_t j){
  const size_t index( (i* _dims.getColumns() ) + j );
  return _data[ index ];
}
template<typename T, typename Alloc>
inline const T& Matrix<T, Alloc>::operator()(size_t i, size_t j) const{
  const size_t index( (i* _dims.getColumns() ) + j );
  return _data[ index ];

}


template<typename T, typename Alloc>
Matrix<T, Alloc> Matrix<T, Alloc>::operator()(size_t n1, size_t n2,
                                              size_t m1, size_t m2) const {
  if( n2 >= this->getNumRows() ){
    n2 = this->getNumRows()-1;
  }
  if( m2 >= this->getNumColumns() ){
    m2 = this->getNumColumns()-1;
  }


  if( (n1 > n2) || (m1 > m2) ){
    assert(false); //FIXME: raise exception instead
  }

  const size_t stride = this->getNumColumns();
  typename std::vector<T, Alloc>::const_iterator it(this->_data.begin());
  it += (n1 * stride)+m1;

  Matrix<T, Alloc> res;
  for(int i=0; i < (n2-n1+1); i++){
    const size_t colsSpan = (m2-m1+1);
    res._data.insert( res._data.end(), it, it+colsSpan );
    it += stride;
  }
  res._dims.setBoth( (n2-n1+1), (m2-m1+1) );

  return res;

}


//////////////////////////////////////////////


template<typename T, typename Alloc>
bool Matrix<T, Alloc>::operator==(const Matrix<T, Alloc>& rhs) const{
  if( this->getDimensions() != rhs.getDimensions() ){
    return false;
  }
  return std::equal(this->_data.begin(), this->_data.end(), rhs._data.begin());
}


//////////////////////////////////////////////

  template<typename T, typename Alloc>
Matrix<T, Alloc>& Matrix<T, Alloc>::operator+=(const Matrix<T, Alloc>& rhs) 
{
  //both matrices should have the same length (and shape!)
  if( this->getDimensions() != rhs.getDimensions() ){
    std::ostringstream oss;
    oss << "Right-hand-side operator size = " << rhs.getDimensions().toString();
    throw Errors::NonConformantDimensions(this->getDimensions(), rhs.getDimensions(),  oss.str());
  }
  const size_t length = this->getSize();
  if( length > 0 ){
    T* const thisMat = &(this->operator[](0));
    const T* const rhsMat  = &(rhs[0]);

#pragma omp parallel for
    for(int i=0; i < length; i++){
      thisMat[i] += rhsMat[i];
    }
  }

  return *this;
}

  template<typename T, typename Alloc>
Matrix<T, Alloc>& Matrix<T, Alloc>::operator+=(const T& rhs) 
{
  const size_t length = this->getSize();
  if( length > 0 ){
    T* const thisMat = &(this->operator[](0));

#pragma omp parallel for
    for(int i=0; i < length; i++){
      thisMat[i] += rhs;
    }
  }
  return *this;
}

  template<typename T, typename Alloc>
Matrix<T, Alloc>& Matrix<T, Alloc>::operator+=(const Digit rhs) 
{
  const size_t length = this->getSize();
  if( length > 0 ){
    T* const thisMat = &(this->operator[](0));

#pragma omp parallel for
    for(int i=0; i < length; i++){
      thisMat[i] += rhs;
    }
  }
  return *this;
}
  template<typename T, typename Alloc>
Matrix<T, Alloc>& Matrix<T, Alloc>::operator+=(const SignedDigit rhs) 
{
  const size_t length = this->getSize();
  if( length > 0 ){
    T* const thisMat = &(this->operator[](0));

#pragma omp parallel for
    for(int i=0; i < length; i++){
      thisMat[i] += rhs;
    }
  }
  return *this;
}





//////////////////////////////////////////////




  template<typename T, typename Alloc>
Matrix<T, Alloc>& Matrix<T, Alloc>::operator-=(const Matrix<T, Alloc>& rhs) 
{
  //both matrices should have the same length (and shape!)
  if( this->getDimensions() != rhs.getDimensions() ){
    throw Errors::NonConformantDimensions(this->getDimensions(), rhs.getDimensions());
  }
  const size_t length = this->getSize();
  if( length > 0 ){
  T* const thisMat = &(this->operator[](0));
  const T* const rhsMat  = &(rhs[0]);

#pragma omp parallel for
  for(int i=0; i < length; i++){
    thisMat[i] -= rhsMat[i];
  }
  }
  return *this;
}
  template<typename T, typename Alloc>
Matrix<T, Alloc>& Matrix<T, Alloc>::operator-=(const T& rhs) 
{
  const size_t length = this->getSize();

  if( length > 0 ){
  T* const thisMat = &(this->operator[](0));

#pragma omp parallel for
  for(int i=0; i < length; i++){
    thisMat[i] -= rhs;
  }
  }
  return *this;
}
  template<typename T, typename Alloc>
Matrix<T, Alloc>& Matrix<T, Alloc>::operator-=(const Digit rhs) 
{
  const size_t length = this->getSize();
  if( length > 0 ){
  T* const thisMat = &(this->operator[](0));

#pragma omp parallel for
  for(int i=0; i < length; i++){
    thisMat[i] -= rhs;
  }
  }
  return *this;
}
  template<typename T, typename Alloc>
Matrix<T, Alloc>& Matrix<T, Alloc>::operator-=(const SignedDigit rhs) 
{
  const size_t length = this->getSize();
  if( length > 0 ){
  T* const thisMat = &(this->operator[](0));

#pragma omp parallel for
  for(int i=0; i < length; i++){
    thisMat[i] -= rhs;
  }
  }
  return *this;
}


//////////////////////////////////////////////
template<typename T, typename Alloc>
Matrix<T, Alloc>& Matrix<T, Alloc>::operator*=(const Matrix<T, Alloc>& rhs) {

  (*this) = (*this) * rhs;
  return *this;
}


template<typename T, typename Alloc>
Matrix<T, Alloc>& Matrix<T, Alloc>::operator*=(const T& rhs){
  const size_t length = this->getSize();
  if( length > 0 ){
  T* const thisMat = &(this->operator[](0));
#pragma omp parallel for
  for(int i=0; i < length; i++){
    thisMat[i] *= rhs;
  }
  }
  return *this;
} 
template<typename T, typename Alloc>
Matrix<T, Alloc>& Matrix<T, Alloc>::operator*=(const Digit rhs){
  const size_t length = this->getSize();
  if( length > 0 ){
  T* const thisMat = &(this->operator[](0));
#pragma omp parallel for
  for(int i=0; i < length; i++){
    thisMat[i] *= rhs;
  }
  }
  return *this;
}
template<typename T, typename Alloc>
Matrix<T, Alloc>& Matrix<T, Alloc>::operator*=(const SignedDigit rhs){
  const size_t length = this->getSize();
  if( length > 0 ){
  T* const thisMat = &(this->operator[](0));
#pragma omp parallel for
  for(int i=0; i < length; i++){
    thisMat[i] *= rhs;
  }
  }
  return *this;
}
  template<typename T, typename Alloc>
Matrix<T, Alloc>& Matrix<T, Alloc>::byElementProd(const Matrix<T, Alloc>& rhs) 
{
  //both matrices should have the same length (and shape!)
  if( this->getDimensions() != rhs.getDimensions() ){
    throw Errors::NonConformantDimensions(this->getDimensions(), rhs.getDimensions());
  }
  const size_t length = this->getSize();
  if( length > 0 ){
  T* const thisMat = &(this->operator[](0));
  const T* const rhsMat  = &(rhs[0]);

#pragma omp parallel for
  for(int i=0; i < length; i++){
    thisMat[i] *= rhsMat[i];
  }
  }
  return *this;
}


//////////////////////////////////////////////

  template<typename T, typename Alloc>
Matrix<T, Alloc>& Matrix<T, Alloc>::operator/=(const Matrix<T, Alloc>& rhs){
  return *this; //TODO
}
  template<typename T, typename Alloc>
Matrix<T, Alloc>& Matrix<T, Alloc>::operator/=(const T&){
  return *this; //TODO
}
  template<typename T, typename Alloc>
Matrix<T, Alloc>& Matrix<T, Alloc>::operator/=(const Digit){
  return *this; //TODO
}
  template<typename T, typename Alloc>
Matrix<T, Alloc>& Matrix<T, Alloc>::operator/=(const SignedDigit){
  return *this; //TODO
}
  template<typename T, typename Alloc>
Matrix<T, Alloc>& Matrix<T, Alloc>::byElementDiv( const Matrix<T, Alloc>& rhs){
  //both matrices should have the same length (and shape!)
  if( this->getDimensions() != rhs.getDimensions() ){
    throw Errors::NonConformantDimensions(this->getDimensions(), rhs.getDimensions());
  }
  const size_t length = this->getSize();
  if( length > 0 ){
  T* const thisMat = &(this->operator[](0));
  const T* const rhsMat  = &(rhs[0]);

#pragma omp parallel for
  for(int i=0; i < length; i++){
    thisMat[i] /= rhsMat[i];
  }
  }
  return *this;


}



//////////////////////////////////////////////



template<typename T, typename Alloc>
Matrix<T, Alloc>& Matrix<T, Alloc>::transpose(){

  // if the matrix to transpose (ie, *this) is square
  // the tranposition can be easily done in place, saving
  // memory (but we still need to allocate space for the 
  // temporal values)
  if( this->isSquare() ){
    T tmp;
    register T *tmpPtr1, *tmpPtr2;
    const size_t numRows = this->getNumRows();
    const size_t numCols = this->getNumColumns();
#pragma omp parallel for schedule(guided) private(tmp)
    for( int row=0; row < numRows; row++){
      for( int col = row+1; col < numCols; col++){
        tmpPtr1 = &((*this)(row, col));
        tmpPtr2 = &((*this)(col, row));
        tmp = *tmpPtr1;
        (*tmpPtr1) = (*this)(col, row);
        (*tmpPtr2) = tmp;
      }
    }
  }
  else{
    // a non-member function is used because new space for the
    // transposed matrix has to be allocated anyway. Therefore 
    // in the case the most general approach is to "externalize" 
    // the method 
    (*this) = mpplas::transpose(*this);
  }
  return *this;


}

  template<typename T, typename Alloc>
Matrix<T, Alloc>& Matrix<T, Alloc>::diagonalize(){
  return *this; //TODO
}
  template<typename T, typename Alloc>
Matrix<T, Alloc>& Matrix<T, Alloc>::invert(){
  return *this; //TODO
}
  template<typename T, typename Alloc>
T Matrix<T, Alloc>::getDeterminant(){
  return T(); //TODO
}



template<typename T, typename Alloc>
void Matrix<T, Alloc>::setDiagonal(T n){
  typename std::vector<T, Alloc>::iterator it;
  for(it = _data.begin(); it < _data.end(); it+= _dims.getColumns() +1){
    *it = n;
  }
  return;
}

template<typename T, typename Alloc>
void Matrix<T, Alloc>::setAll(T n){
  std::fill( _data.begin(), _data.end(), n );
  return ;
}

template<typename T, typename Alloc>
void Matrix<T, Alloc>::setToZero(){
  this->setAll( T::ZERO );
  return;
}

////////////////////////////////////


template<typename T, typename Alloc>
inline size_t Matrix<T, Alloc>::getSize() const{
  //return this->getDimensions().getProduct();
  return this->_data.size();
}

template<typename T, typename Alloc>
inline const Dimensions& Matrix<T, Alloc>::getDimensions() const{
  return _dims;
}

template<typename T, typename Alloc>
inline size_t Matrix<T, Alloc>::getNumRows() const {
  return this->getDimensions().getRows();
}

template<typename T, typename Alloc>
inline size_t Matrix<T, Alloc>::getNumColumns() const {
  return this->getDimensions().getColumns();
}

template<typename T, typename Alloc>
inline bool Matrix<T, Alloc>::isSquare() const {
  return (this->getNumRows() == this->getNumColumns());
}




template<typename T, typename Alloc>
void Matrix<T, Alloc>::setDimensions(const Dimensions& dims){
  const size_t _n = _dims.getRows();
  const size_t _m = _dims.getColumns();
  //deal with the possible change in the # of rows
  const size_t newN = dims.getRows();
  if( newN != _n ){ 
    //the extra space will be filled with the default
    //constructor's value for the type T
    _data.resize( _m * newN );
    _dims.setRows(newN);
  }

  //deal with the possible change in the # of columns 
  const size_t newM = dims.getColumns();
  if( newM != _m ){
    typename std::vector<T, Alloc>::iterator it;
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
    _dims.setColumns(newM);
  }
}


template<typename T, typename Alloc>
std::string Matrix<T, Alloc>::toString() const { 
  const size_t _n = _dims.getRows();
  const size_t _m = _dims.getColumns();

  std::string res("[ ");
  for(int i=0; i < _n; i++){
    for(int j=0; j < _m; j++){
      std::ostringstream oss;
      oss << (this->operator()(i,j));
      res += oss.str();
      res += " ";
    }
    if( i != _n-1){
      res += "; ";
    }
  }
  res += " ]";

  return res;
}


////////////////////////////////////////////





template<typename T, typename Alloc>
void Matrix<T, Alloc>::_reset() {
  _data.clear();
  _dims.setBoth(0,0);
}

////////////////////////////////////////////





template<typename T, typename Alloc>
Matrix<T, Alloc> transpose(const Matrix<T, Alloc>& matrix){
  
  const size_t numRows = matrix.getNumRows();
  const size_t numCols = matrix.getNumColumns();
 
  mpplas::Matrix<T, Alloc> resMat( numCols, numRows );
  T* res( &(resMat(0,0)) );
  const T* src( &(matrix(0,0)) );

  bool firstIter = true;

  // the reason behind splitting the procedure is to minimize the number
  // of "short jumps" due to long strides. ie, the stride length is minimized
  // by making the "stride dimension" the smaller one. The longer the stride, 
  // the more likely the cache miss.
  //
  // There are no problems due to the sharing of the res array, as each write is 
  // performed to a single location. There are no updates coming from different 
  // threads to a single shared location.
  if( numRows >= numCols ){ 
    //if the matrix is square, both approaches are equivalent, so we may
    //as well use this one.
    const size_t stride = numRows;
#pragma omp parallel for firstprivate(res,src, firstIter) schedule(static)
    for(int row=0; row < numRows; row++){
      if(firstIter){
        res += row;
        src += (row * numCols);
        firstIter = false;
      }
      for(int i = 0; i < numCols; i++){
        res[(i*stride)] = src[i];
      }
      res += 1;
      src += numCols;
    }
  }
  else { // numRows < numCols 
    const size_t stride = numCols;
#pragma omp parallel for firstprivate(res,src, firstIter) schedule(static)
    for(int col=0; col < numCols; col++){
      if(firstIter){
        res += (col*numRows);
        src += col;
        firstIter = false;
      }
      for(int i = 0; i < numRows; i++){
        res[i] = src[(i*stride)];
      }
      res += numRows;
      src += 1;
    }
  }

  return resMat;
}


//same as for transposition: the operation cannot be perfomed "in place": *this 
//is modified in the process in a way that makes it necessary to create a copy of it 
//or, equivalently, store results in another location. In this case, storing the results
//in a newly allocated space is clearer
template<typename T, typename Alloc>
  Matrix<T, Alloc> operator*(const Matrix<T, Alloc>& lhs, const Matrix<T, Alloc>& rhs){

  const size_t ARows = lhs.getDimensions().getRows();
  const size_t ACols = lhs.getDimensions().getColumns();
  const size_t BCols = rhs.getDimensions().getColumns();

  Matrix<T, Alloc> res( lhs.getNumRows(), rhs.getNumColumns() );

  const int rowsPerBlock = 2; //FIXME
  const int colsPerBlock = 2;

  MatrixHelpers::Strassen<T> strassen(ACols, BCols);

#pragma omp parallel for schedule(static)
  for (int aRow = 0; aRow < ARows; aRow+= rowsPerBlock) {
    for (int bCol = 0; bCol < BCols; bCol += rowsPerBlock) {
      T* C( &(res( aRow, bCol )) );
      for (int aCol = 0; aCol < ACols; aCol +=colsPerBlock ) {
        const T* const A( &(lhs(aRow, aCol)) );
        const T* const B( &(rhs(aCol, bCol)) );
      
        strassen.run(C,A,B,
                     rowsPerBlock,
                     colsPerBlock,
                     colsPerBlock);

      }
    }
  }

  return res;
}



template<typename T, typename Alloc>
std::ostream& operator<<(std::ostream& out, const Matrix<T, Alloc>& m){
  const size_t COLS = m.getDimensions().getColumns();
  size_t maxWidth[COLS];
  memset(maxWidth, 0, COLS*sizeof(size_t));

  std::ostringstream oss;
  for(int i=0; i < m._data.size(); i++){
    oss.str("");
    oss << m._data[i];
    maxWidth[i % COLS] = std::max(oss.str().size()+2, maxWidth[i % COLS]);
  }

  const size_t _n = m.getDimensions().getRows();
  const size_t _m = m.getDimensions().getColumns();
  
  //first iteration: in case the matrix is "empty" (dims == 0), 
  //it'd still show "[ ]" on screen
  out << "[" ;
  for(int j=0; j < _m; j++ ){
    out << std::setw(maxWidth[j]) << std::right << m(0,j);
  }
  out << " ]\n" ;

  for(int i=1; i < _n; i++){
    out << "[" ;
    for(int j=0; j < _m; j++ ){
      out << std::setw(maxWidth[j]) << std::right << m(i,j);
    }
    out << " ]\n" ;
  }
  return out;
}

template<typename T, typename Alloc>
std::istream& operator>>(std::istream& in, Matrix<T, Alloc>& m) {

  m._reset();

  char c;
  size_t columnsIni, columnsRead, rows;
  columnsIni = columnsRead = rows = 0;
  bool firstRow = true;

  in >> c;
  if( !in.good() || c != '[' ){
    throw Errors::InvalidSymbol(std::string(1,c));
  }

  T valueRead;

  while(true){
    while( in >> valueRead ){
      m._data.push_back(valueRead);
//      std::cout << valueRead << std::endl;
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

/////////////////////////

namespace MatrixHelpers{

  template<typename T>
    Strassen<T>::Strassen(const size_t strideA, const size_t strideB)
    : _strideA(strideA), _strideB(strideB)
    {}


  template<typename T>
   void Strassen<T>::run(T* C, const T* const A, const T* const B, 
            const size_t numRowsA, 
            const size_t numColsA, 
            const size_t numColsB){

      _halfRowsA = numRowsA / 2;
      _halfColsA = numColsA / 2;
      _halfColsB = numColsB / 2;
      /* (numColsA = numRowsB) => (halfRowsB = halfColsA) 
       *
       * And the Q's would be ( halfRowsA x halfColsB ) 
       * */
      const size_t qsSize( _halfRowsA * _halfColsB );
      T   Q0[qsSize];
      T Q3_2[qsSize];
      T Q4_5[qsSize];
      T Q6_1[qsSize];

      _baseMult(C,A,B, numRowsA, numColsA, numColsB);
      return;

    }

  template<typename T>
    void Strassen<T>::_generateQ0(T* Q) const{

    }
  template<typename T>
    void Strassen<T>::_generateQ1(T* Q) const{

    }
  template<typename T>
    void Strassen<T>::_generateQ2(T* Q) const{

    }
  template<typename T>
    void Strassen<T>::_generateQ3(T* Q) const{

    }
  template<typename T>
    void Strassen<T>::_generateQ4(T* Q) const{

    }
  template<typename T>
    void Strassen<T>::_generateQ5(T* Q) const{

    }
  template<typename T>
    void Strassen<T>::_generateQ6(T* Q) const{

    }
  
  template<typename T>
  void Strassen<T>::_sumBlocks(T* res, 
      const T* const lhs, 
      const T* const rhs) const{}
  template<typename T>
  void Strassen<T>::_subsBlocks(T* res, 
      const T* const lhs, 
      const T* const rhs) const{}
  template<typename T>
  void Strassen<T>::_multBlocks(T* res, 
      const T* const lhs, 
      const T* const rhs) const{}

  template<typename T>
    void Strassen<T>::_baseMult(
        T* C, const T* const A, const T* const B,
        const size_t numRowsA, const size_t numColsA, 
        const size_t numColsB) const {

      for (size_t aRow = 0; aRow < numRowsA; aRow++) {
        for (size_t bCol = 0; bCol < numColsB; bCol++) {
          for (size_t aCol = 0; aCol < numColsA; aCol++) {
            C[aRow * _strideB + bCol] += A[ aRow * _strideA + aCol] * B[aCol * _strideA + bCol];
          }
        }
      }
      return;
    }
} /* namespace MatrixHelpers */

