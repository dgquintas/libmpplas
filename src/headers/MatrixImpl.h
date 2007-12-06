/* 
 * $Id$
 */

//////////////////////////////////////////
//   IMPLEMENTATION
//////////////////////////////////////////

  template<typename T, typename Alloc>
  Matrix<T, Alloc>::Matrix()
: _dims(0,0)
{}

  template<typename T, typename Alloc>
  Matrix<T, Alloc>::Matrix(const int nAndm) 
: _dims(nAndm,nAndm), _data(nAndm*nAndm)
{} 

  template<typename T, typename Alloc>
  Matrix<T, Alloc>::Matrix(const int n, const int m)
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
: _data(rhs), _dims(dims) {
  int const prod(_dims.getProduct());
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
inline T& Matrix<T, Alloc>::operator[](int i){
  return _data[i];
}
template<typename T, typename Alloc>
inline const T& Matrix<T, Alloc>::operator[](int i) const{
  return _data[i];
}


template<typename T, typename Alloc>
inline T& Matrix<T, Alloc>::operator()(int i){
  return _data[i];
}
template<typename T, typename Alloc>
inline const T& Matrix<T, Alloc>::operator()(int i) const{
  return _data[i];
}

template<typename T, typename Alloc>
inline T& Matrix<T, Alloc>::operator()(int i, int j){
  if( i >= this->getRows() || j >= this->getColumns() ){
    throw Errors::InvalidRange();
  }
  const int index( (i* _dims.getColumns() ) + j );
  return _data[ index ];
}
template<typename T, typename Alloc>
inline const T& Matrix<T, Alloc>::operator()(int i, int j) const{
  if( i >= this->getRows() || j >= this->getColumns() ){
    throw Errors::InvalidRange();
  }
  const int index( (i* _dims.getColumns() ) + j );
  return _data[ index ];

}


template<typename T, typename Alloc>
Matrix<T, Alloc> Matrix<T, Alloc>::operator()(int n1, int n2,
                                              int m1, int m2) const {
  if( n2 >= this->getRows() ){
    n2 = this->getRows()-1;
  }
  if( m2 >= this->getColumns() ){
    m2 = this->getColumns()-1;
  }


  if( (n1 > n2) ){
    std::ostringstream oss;
    oss << "Invalid interval for submatrix operator (rows)";
    throw Errors::InvalidRange(oss.str());
  }

  if( (m1 > m2) ){
    std::ostringstream oss;
    oss << "Invalid interval for submatrix operator (columns)";
    throw Errors::InvalidRange(oss.str());
  }

  const int stride = this->getColumns();
  typename mpplas::MiVec<T, Alloc>::const_iterator it(this->_data.begin());
  it += (n1 * stride)+m1;

  Matrix<T, Alloc> res;
  for(int i=0; i < (n2-n1+1); i++){
    const int colsSpan = (m2-m1+1);
    res._data.insert( res._data.end(), it, it+colsSpan );
    it += stride;
  }
  res._dims.setBoth( (n2-n1+1), (m2-m1+1) );

  return res;

}

template<typename T, typename Alloc>
Matrix<T, Alloc>& Matrix<T, Alloc>::fromString(const std::string& str){
  std::istringstream inStream(str);
  operator>>(inStream,*this);

  return *this;
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
  const int length = this->getSize();
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
  const int length = this->getSize();
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
  const int length = this->getSize();
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
  const int length = this->getSize();
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
  const int length = this->getSize();
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
  const int length = this->getSize();

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
  const int length = this->getSize();
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
  const int length = this->getSize();
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
  const int length = this->getSize();
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
  const int length = this->getSize();
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
  const int length = this->getSize();
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
  const int length = this->getSize();
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
  Matrix<T, Alloc>& Matrix<T, Alloc>::operator/=(Matrix<T, Alloc> rhs){
    //invert rhs and then multiply it by *this
    rhs.invert();
    (*this) *= rhs;
    return *this;
  }


//template<typename T, typename Alloc>
//  std::vector< const MPPDataType& > Matrix<T, Alloc>::getLUPDecomposition() const{
//    std::vector<const MPPDataType& > lup;
//    
//    Matrix<T,Alloc> m(*this);
//    const std::vector<int> p(MatrixHelpers::LUDoolittle::makeDoolittleCombinedMatrix(m));
//    lup.push_back(MatrixHelpers::LUDoolittle::_getL(m));
//    lup.push_back(MatrixHelpers::LUDoolittle::_getU(m));
//    lup.push_back(MatrixHelpers::LUDoolittle::_getPermutationsMatrix<T,Alloc>(p));
//
//    return lup;
//  
//  }

  template<typename T, typename Alloc>
Matrix<T, Alloc>& Matrix<T, Alloc>::operator/=(const T& rhs){
  const int length = this->getSize();
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
Matrix<T, Alloc>& Matrix<T, Alloc>::operator/=(const Digit rhs){
  const int length = this->getSize();
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
Matrix<T, Alloc>& Matrix<T, Alloc>::operator/=(const SignedDigit rhs){
  const int length = this->getSize();
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
  Matrix<T, Alloc>& Matrix<T, Alloc>::byElementDiv( const Matrix<T, Alloc>& rhs){
    //both matrices should have the same length (and shape!)
    if( this->getDimensions() != rhs.getDimensions() ){
      throw Errors::NonConformantDimensions(this->getDimensions(), rhs.getDimensions());
    }
    const int length = this->getSize();
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
    const int numRows = this->getRows();
    const int numCols = this->getColumns();
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
Matrix<T, Alloc>& Matrix<T, Alloc>::invert(){
    const int n = this->getRows();
    const std::vector<int> p(MatrixHelpers::LUDoolittle::makeDoolittleCombinedMatrix(*this));

    const Matrix<T, Alloc> orig(*this); 
#pragma omp parallel for schedule(static,1)
    for(int j = 0; j < n; j++){
      MatrixHelpers::solveForInv(orig,*this,j,p[j]);
    }

    return *this; 
}



template<typename T, typename Alloc>
Matrix<T, Alloc> Matrix<T, Alloc>::solveFor(const Matrix<T, Alloc>& b) const{

  return MatrixHelpers::solve(*this, b);

}

  template<typename T, typename Alloc>
T Matrix<T, Alloc>::getDeterminant() const {
  if( !this->isSquare() ){
    throw Errors::SquareMatrixRequired();
  }
  if( this->getRows() == 1 ){
    return _data[0];
  }

  const bool isTaField(dynamic_cast<const Field<T>* >(&_data[0]));

  if(isTaField){
    Matrix<T, Alloc> m(*this);
    int sign;
    MatrixHelpers::LUDoolittle::makeDoolittleCombinedMatrix(m, &sign);
  
    T determinant( m[0] );
    for( int i = 1; i < m.getRows(); i++){
      determinant *= m(i,i);
    }
    if( sign < 0 ){
      return determinant = determinant.getAddInverse();
    }
    return determinant;
  }
  else{
    return MatrixHelpers::GaussBareiss::getGaussBareissDeterminant(*this);
  }

}



template<typename T, typename Alloc>
void Matrix<T, Alloc>::setDiagonal(const T& n){
#undef min //pari lib might interfere
  const int diagElems( std::min( this->getRows(), this->getColumns() ) );

  typename mpplas::MiVec<T, Alloc>::iterator it( _data.begin() );
  for(int i = 0; i < diagElems; i++ ){
    (*it) = n;
    it += (_dims.getColumns()+1);
  }
  return;
}

template<typename T, typename Alloc>
void Matrix<T, Alloc>::setAll(const T& n){
  std::fill( _data.begin(), _data.end(), n );
  return ;
}

template<typename T, typename Alloc>
void Matrix<T, Alloc>::setToZero(){
  T& z(_data[0]);
  z.makeZero();
  this->setAll(z);
  return;
}

////////////////////////////////////


template<typename T, typename Alloc>
inline int Matrix<T, Alloc>::getSize() const{
  //return this->getDimensions().getProduct();
  return this->_data.size();
}

template<typename T, typename Alloc>
inline const Dimensions& Matrix<T, Alloc>::getDimensions() const{
  return _dims;
}

template<typename T, typename Alloc>
inline int Matrix<T, Alloc>::getRows() const {
  return this->getDimensions().getRows();
}

template<typename T, typename Alloc>
inline int Matrix<T, Alloc>::getColumns() const {
  return this->getDimensions().getColumns();
}

template<typename T, typename Alloc>
inline bool Matrix<T, Alloc>::isSquare() const {
  return (this->getRows() == this->getColumns());
}




template<typename T, typename Alloc>
void Matrix<T, Alloc>::setDimensions(const Dimensions& dims){
  const int _n = _dims.getRows();
  const int _m = _dims.getColumns();
  //deal with the possible change in the # of rows
  const int newN = dims.getRows();
  if( newN != _n ){ 
    //the extra space will be filled with the default
    //constructor's value for the type T
    _data.resize( _m * newN );
    _dims.setRows(newN);
  }

  //deal with the possible change in the # of columns 
  const int newM = dims.getColumns();
  if( newM != _m ){
    typename mpplas::MiVec<T, Alloc>::iterator it;
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
  const int _n = _dims.getRows();
  const int _m = _dims.getColumns();

  std::ostringstream oss;
  oss << "[ ";
  for(int i=0; i < _n; i++){
    for(int j=0; j < _m; j++){
      oss << (this->operator()(i,j));
      oss << " ";
    }
    if( i != _n-1){
      oss << "; ";
    }
  }
  oss << " ]";

  return oss.str();
}

template<typename T, typename Alloc>
std::string Matrix<T, Alloc>::toHRString() const { 
  std::ostringstream oss;
  oss << *this;
  return oss.str();
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
  
  const int numRows = matrix.getRows();
  const int numCols = matrix.getColumns();
 
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
    const int stride = numRows;
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
    const int stride = numCols;
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

  const int aCols = lhs.getColumns();
  const int bRows = rhs.getRows();

  if( aCols != bRows ){
    std::ostringstream oss;
    oss << "Left-hand-side operator size = " << lhs.getDimensions().toString() << "\n";
    oss << "Right-hand-side operator size = " << rhs.getDimensions().toString();
    throw Errors::NonConformantDimensions(lhs.getDimensions(), rhs.getDimensions(),  oss.str());
  }
  const int aRows = lhs.getRows();
  const int bCols = rhs.getColumns();

  Matrix<T, Alloc> res( aRows, bCols );

  //  MatrixHelpers::Strassen<T> strassen;
  MatrixHelpers::Winograd<T> strassen;

  if( aRows == 1 || aCols == 1 || bCols == 1 ){
    strassen.baseMult(&res[0],&lhs[0],&rhs[0],
        aRows, aCols, bCols,
        bCols, aCols, bCols);

    return res;
  }



//  const int rowsPerBlock = 1 << (getBitLength(aRows)-1); //FIXME
  int aRowsPerBlock = aRows/2 ; 
  if( aRowsPerBlock & 0x1 ) aRowsPerBlock++;
  int aColsPerBlock = aCols/2 ; 
  if( aColsPerBlock & 0x1 ) aColsPerBlock++;
  const int bRowsPerBlock = aColsPerBlock;
  int bColsPerBlock = bCols/2 ;
  if( bColsPerBlock & 0x1 ) bColsPerBlock++;

  const int aRowsExtra = aRows % aRowsPerBlock;
  const int aColsExtra = aCols % aColsPerBlock;
  const int bColsExtra = bCols % bColsPerBlock;

 
//  T* C( &(res( 0, 0 )) );
//  const T* const A( &(lhs(0, 0)) );
//  const T* const B( &(rhs(0, 0)) );
//  strassen.baseMult(C,A,B,
//      aRows, aCols, bCols,
//      bCols, aCols, bCols);

#pragma omp parallel for schedule(static,1)
  for (int aRow = 0; aRow < aRows; aRow += aRowsPerBlock) {
    const bool aRowsOF = ((aRow + aRowsPerBlock) > aRows);
    for (int bCol = 0; bCol < bCols; bCol += bColsPerBlock) {
      T* C( &(res( aRow, bCol )) );
      const bool bColsOF = ((bCol + bColsPerBlock) > bCols);
      for (int aCol = 0; aCol < aCols; aCol += aColsPerBlock ) {
        const T* A( &(lhs(aRow, aCol)) );
        const T* B( &(rhs(aCol, bCol)) );

        const bool aColsOF = ((aCol + aColsPerBlock) > aCols);

        if( aRowsOF || aColsOF || bColsOF ){
          strassen.baseMult(C,A,B,
              aRowsOF ? aRowsExtra : aRowsPerBlock,
              aColsOF ? aColsExtra : aColsPerBlock,
              bColsOF ? bColsExtra : bColsPerBlock,
              bCols, aCols, bCols);
        }
        else {

          strassen.run(C,A,B,
              aRowsPerBlock,aColsPerBlock,bColsPerBlock,
              bCols, aCols, bCols);
        }
      }
    }
  }


  //there might still be some rows/columns left, if the dimensions of the
  //matrices weren't multiples of the respective block sizes

  return res;
}



template<typename T, typename Alloc>
std::ostream& operator<<(std::ostream& out, const Matrix<T, Alloc>& m){
  const int COLS = m.getDimensions().getColumns();
  size_t maxWidth[COLS]; //size_t used because string::size() returns size_t
  memset(maxWidth, 0, COLS*sizeof(size_t));

  std::ostringstream oss;
  for(int i=0; i < m._data.size(); i++){
    oss.str("");
    oss << m._data[i];
#undef max //pari lib might interfere
    maxWidth[i % COLS] = std::max(oss.str().size()+2, maxWidth[i % COLS]);
  }

  const int _n = m.getDimensions().getRows();
  const int _m = m.getDimensions().getColumns();
  
  oss.str("");
  //first iteration: in case the matrix is "empty" (dims == 0), 
  //it'd still show "[ ]" on screen
  oss << "[" ;
  for(int j=0; j < _m; j++ ){
    oss << std::setw(maxWidth[j]) << std::right << m(0,j);
  }
  oss << " ]\n" ;

  for(int i=1; i < _n; i++){
    oss << "[" ;
    for(int j=0; j < _m; j++ ){
      oss << std::setw(maxWidth[j]) << std::right << m(i,j);
    }
    oss << " ]\n" ;
  }
  out << oss.str();
  return out;
}


template<typename U, typename V, typename Composed_t>
void _parseMatrixInput(std::istream& in, Matrix<U, V>& m){

  char c;
  int columnsIni, columnsRead, rows;
  columnsIni = columnsRead = rows = 0;
  bool firstRow = true;

  int elemsPerSlot = sizeof(Composed_t)/sizeof(U);

  m._reset();
  in >> c;
  if( !in.good() || c != '[' ){
    throw Errors::InvalidSymbol(std::string(1,c));
  }

  U valueRead;
  m._data.insert( m._data.end(), elemsPerSlot, U());
  int availableSlots = elemsPerSlot;
  U* mData = &(m._data[0]) ;

  for(int i=0; ; ){
    while( in >> valueRead ){
      if( availableSlots <= 0 ){
        m._data.insert( m._data.end(), elemsPerSlot, U());
        mData = &(m._data[0]) ;
        availableSlots = elemsPerSlot;
      }
      mData[i] = valueRead;
      availableSlots--;
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
      return ;
    }
    rows++;
    firstRow = false;
  } //while(true)

  return;

}

template<typename T, typename Alloc>
std::istream& operator>>(std::istream& in, Matrix<T, Alloc>& m) {

  _parseMatrixInput<T, Alloc, T>(in,m);

  return in;
}

/////////////////////////

namespace MatrixHelpers{

  namespace DodgsonCondensation{

    template<typename T, typename Alloc>
      T getDodgsonDeterminant(Matrix<T, Alloc> m){

        if( !m.isSquare() ){
          throw Errors::SquareMatrixRequired();
        }

        const int mCols = m.getColumns();
        if( mCols == 2 ){
          _get2x2Determinants(&m[0], &m[0], 1, 2);
        }
        else{
          //some T's may not have empty constructors. Rely on copy ctors.
          //these pointers are initialized to zero to avoid
          //a segfault when deleting a possibly not allocated
          //pointer (for instance, for 3x3 matrices.
          //Recall that delete on a null pointer has no
          //effect
          Matrix<T, Alloc>* inner[2] = {0,0}; 

          int innerBound = mCols-2;
          _pivot(m, mCols);
          inner[0] = new Matrix<T,Alloc>(m(1, innerBound ,1, innerBound));
          T* res;

          Matrix<T,Alloc> orig(m);
          const T* origP( &orig[0] );
          for( int k = 1; k < mCols; k++){
            res = &(m[0]) ;

            if( SystemInfo::getMaxNumberOfThreads() > 1 ){
              orig = m;
              origP = &orig[0];
            }
            else{
              origP = res;
            }

#pragma omp parallel for 
            for(int i = 0; i < mCols-k; i++){
              const int shift(i*mCols);
              _get2x2Determinants(res+shift, origP+shift, mCols-k, mCols);
            }


            if( k > 1 ){
              _elementWiseInnerDiv(m,*inner[ k & 0x1]);
            }
            if( innerBound > 1 ){
              innerBound--;
              inner[ k & 0x1 ] = new Matrix<T,Alloc>(m(1,innerBound,1,innerBound));
            }
          }
          delete inner[0];
          delete inner[1];

        }
        return m[0];

      };

    template<typename T>
      void _get2x2Determinants(T* const res, const T* const orig, const int n, const int stride){
        const T* const upperRow(orig);
        const T* const lowerRow(orig + stride);
        for(int i = 0; i < n; i++){
          res[i] = upperRow[i]*lowerRow[i+1] - upperRow[i+1]*lowerRow[i];
        }
      }

    template<typename T, typename Alloc>
      bool _pivot(Matrix<T,Alloc>& m, const int lim){
        for(int i=1; i < lim-1; i++){
          for(int j = 1 ; j < lim-1 ; j++){
            if( m(i,j).isZero() ){


              //////////////////////////
              int k;
              for( k = 0; k < lim; k++){
                if( k == i ) continue;
                if( !m(k,j).isZero()){
                  for( int l = 0; l < lim; l++){
                    m(i,l) += m(k,l);
                  }
                  break;
                } 
              }
              if( k == lim ){
                return false;
              }
              ////////////////////////////

            
            
            }
          }
        }

        return true;

      }



    template<typename T, typename Alloc>
      void _elementWiseInnerDiv(Matrix<T,Alloc>& lhs, const Matrix<T,Alloc>& rhs){
        const int n = rhs.getRows();

        for(int i = 0; i < n; i++){
          for(int j = 0 ; j < n; j++) {
            lhs(i,j) /= rhs(i,j);
          }
        }
      }

  }

  namespace GaussBareiss{
    template<typename T, typename Alloc>
      T getGaussBareissDeterminant(Matrix<T, Alloc> m){
        const int n = m.getRows();
        int sign = 1;
        const T* p;
        T* m_jk;
        const T* m_ji;
        const T* m_i1i1;

        for (int i = 0; i < n-1; i++) {
          p = &(m(i,i));
          if( i ){
            m_i1i1 = &(m(i-1,i-1));
          }
          if( p->isZero() ){
            if( !_pivot(m,i) ){
              sign = 1;
              m(n-1,n-1).makeZero();
              break;
            }
            // m(i,i) != zero here
            sign *= -1;
            p = &(m(i,i));
          }
#pragma omp parallel private(m_ji)
          {
      
            for (int j = i + 1; j < n; j++){
              m_ji = &m(j,i);

#pragma omp for nowait firstprivate(i) private(m_jk)
              for (int k = i + 1; k < n; k++) {
                m_jk = &( m(j,k) );
                m_jk->operator*=(*p);
                m_jk->operator-=(*m_ji * m(i,k));
                if (i){
                  m_jk->operator/=( *m_i1i1 );
                }
              } 
            }

          } /* implicit parallel barrier */
        }

        if( sign < 0 ){
          m(n-1,n-1).invertSign();
        }
        return m(n-1,n-1);
      }

    template<typename T, typename Alloc>
      bool _pivot(Matrix<T,Alloc>& m, const int k){
        for(int i=k+1; i < m.getRows(); i++){
          if( ! m(i,k).isZero() ){
            for( int j = k; j < m.getColumns(); j++){
              std::swap( m(i,j), m(k,j) );
            }
            return true;
          }
        }
        return false;
      }


  }

  namespace LUDoolittle{

    template<typename T, typename Alloc>
      std::vector<int> makeDoolittleCombinedMatrix(Matrix<T, Alloc>& a, int* const sign){
        if( !a.isSquare() ){
          throw Errors::SquareMatrixRequired();
        }
        std::vector<int> p(a.getRows());
        for(int i = 0 ; i < p.size(); i++) {
          p[i] = i;
        }
        const int rows = a.getRows();
        const int cols = a.getColumns();
        int sgn = 1;
        for(int k=0; k<rows-1; k++) {
          if( a(k,k).isZero() ){
            const int rowPivot(_pivot(a,k));
            if( rowPivot == 0 ){
              throw Errors::NonInvertibleElement();
            }
            std::swap(p[k],p[rowPivot]);
            sgn *= -1;
          }
#pragma omp parallel for schedule(static,1)
          for (int i=k+1; i<rows; i++) {
            a(i,k) /= a(k,k);

            for (int j=k+1; j<cols; j++){ 
              a(i,j) -= a(i,k)*a(k,j);
            }
          }
        }

        if( sign ){
          *sign = sgn;
        }
        //return _getPermutationsMatrix<T,Alloc>(p);
        return p;
      }

    template<typename T, typename Alloc>
      int _pivot(Matrix<T,Alloc>& m, const int j){
        for(int k = j+1; k < m.getRows(); k++){
          if( !m(k,j).isZero()){
            for( int l = 0; l < m.getColumns(); l++){
              std::swap(m(j,l), m(k,l));
            }
            return k;
          } 
        }

        return 0;

      }


    template<typename T, typename Alloc>
      Matrix<T, Alloc> _getPermutationsMatrix(const std::vector<int>& p){
        const int n = p.size();
        Matrix<T, Alloc> pId(n,n);

        for(int i = 0; i < n; i++){
          pId(i,p[i]).makeOne();
        }

        return pId;
      }

    template<typename T, typename Alloc>
      Matrix<T, Alloc> _getL(const Matrix<T,Alloc>& combined){
        Matrix<T,Alloc> l(combined.getDimensions());
        l(0,0).makeOne();
        l.setDiagonal(l(0,0));
        for(int i=1; i < l.getRows(); i++){
          for(int j=0; j < i; j++){
            l(i,j) = combined(i,j);
          }
        }
        return l;
      }


    template<typename T, typename Alloc>
      Matrix<T, Alloc> _getU(const Matrix<T,Alloc>& combined){
        Matrix<T,Alloc> u(combined.getDimensions());
        for(int i=0; i < u.getRows(); i++){
          for(int j=i; j < u.getColumns(); j++){
            u(i,j) = combined(i,j);
          }
        }
        return u;

      }

  }


  template<typename T, typename Alloc>
    Matrix<T,Alloc> solve(Matrix<T, Alloc> m, Matrix<T, Alloc> b){
      const int n = m.getRows();
      std::vector<int> p(MatrixHelpers::LUDoolittle::makeDoolittleCombinedMatrix(m));
      for(int i = 0; i < p.size(); i++){
          if( i != p[i] ){
            std::swap(b[i], b[p[i]]);

            //once the swap has been done, the reverse operation 
            //has to be "disabled". For example, if p = {2, 1, 0}
            //it first swaps row 0 with row 2. But when it reaches
            //p[2] = 0, it should NOT swap row 2 with row 0. Therefore,
            //we set p[2] = 2 to avoid getting into the if.
            p[p[i]] = p[i];
          }
      }

      forwardSubstitution(m, b);
      backwardSubstitution(m, b);

      return b;
    }

  template<typename T, typename Alloc>
    void solveForInv(Matrix<T, Alloc> m, Matrix<T, Alloc>& inv, const int currCol, const int perm){
      const int n = m.getRows();

      T sum(m(0,0));
      for(int i = 0; i < n; i++){
        if(i == perm){
          sum.makeOne();
        }
        else{
          sum.makeZero();
        } 
        for(int j = 0; j < i; j++){
          sum -= m(i,j)*inv(j,currCol);
        }
        inv(i,currCol) = sum;
      }
      try{
      inv(n-1,currCol) /= m(n-1,n-1);
      for(int i = n-2; i >= 0; i--){
        sum = inv(i,currCol);
        for(int j = i+1; j < n; j++){
          sum -=  m(i,j) * inv(j,currCol);
        }
        sum /= m(i,i);
        inv(i,currCol) = sum;
      }
      }
      catch( const Errors::DivisionPorCero& e){
        throw Errors::NonInvertibleElement();
      }
      return ;
    }




  template<typename T, typename Alloc>
      void forwardSubstitution(const Matrix<T, Alloc>& l, Matrix<T, Alloc>& b){
        const int n = l.getRows();
        T sum(l(0,0));
        for(int i = 1; i < n; i++){
          sum = b(i);
          for(int j = 0; j < i; j++){
            sum -=  l(i,j)*b(j);
          }
          b(i) = sum;
        }
      }


  template<typename T, typename Alloc>
      void backwardSubstitution(const Matrix<T, Alloc>& u, Matrix<T, Alloc>& y){
        const int n = u.getRows();
        T sum(u(0,0));
        y(n-1) /= u(n-1,n-1);
        for(int i = n-2; i >= 0; i--){
          sum = y(i);
          for(int j = i+1; j < n; j++){
            sum -=  u(i,j)*y(j);
          }
          sum /= u(i,i);
          y(i) = sum;
        }
      }






  template<typename T>
   void Winograd<T>::run(T* C, const T* const A, const T* const B, 
            const int numRowsA, const int numColsA, const int numColsB,
            const int strideC, const int strideA, const int strideB, bool reset) const{


      const int halfRowsA = numRowsA / 2;
      const int halfColsA = numColsA / 2;
      const int halfRowsB = halfColsA;
      const int halfColsB = numColsB / 2;

      T* r1 = new T[halfRowsA * halfColsA];
      T* r2 = new T[halfRowsB * halfColsB];
      T* r3 = new T[halfRowsA * halfColsB];
      T* r32 = new T[halfRowsA * halfColsB];

      const T* const a11 = A;
      const T* const a12 = (A + halfColsA);
      const T* const a21 = (A + (halfRowsA * strideA));
      const T* const a22 = (a21 + halfColsA);

      const T* const b11 = B;
      const T* const b12 = (B + halfColsB);
      const T* const b21 = (B + (halfRowsB * strideB));
      const T* const b22 = (b21 + halfColsB);

      T* const c11(C);
      T* const c12(C + halfColsB );
      T* const c21(C + (strideC * halfRowsA) );
      T* const c22( c21 + halfColsB );

      // R1 <- (A21 + A22)
      _addBlocks(r1, a21, a22,
          halfRowsA, halfColsA,
          halfColsA, strideA, strideA);

      // R2 <- B12 - B11 
      _subBlocks(r2, b12, b11,
          halfRowsB, halfColsB,
          halfColsB, strideB, strideB);

      // R3 <- R1 R2
      _multBlocks(r3, r1, r2,
          halfRowsA, halfColsA, halfColsB,
          halfColsB, halfColsA, halfColsB);

      // C12 <- R3
      _accumBlocks(c12, r3,
          halfRowsA, halfColsB,
          strideC, halfColsB, reset);
      // C22 <- R3
      _accumBlocks(c22, r3,
          halfRowsA, halfColsB,
          strideC, halfColsB, reset);


      //R1 <- R1 - A11
       _subBlocks(r1, r1, a11,
          halfRowsA, halfColsA,
          halfColsA, halfColsA, strideA);

      //R2 <- B22 - R2
       _subBlocks(r2, b22, r2,
          halfRowsB, halfColsB,
          halfColsB, strideB, halfColsB);

      // R3 <- (A11 B11)
      _multBlocks(r3, a11, b11,
          halfRowsA, halfColsA, halfColsB,
          halfColsB, strideA, strideB);

      // C11 <- R3
      _accumBlocks(c11, r3,
          halfRowsA, halfColsB,
          strideC, halfColsB, reset);

      //R3 <- R3 + R1 R2
        //R32 <- R1 R2
        _multBlocks(r32, r1, r2,
           halfRowsA, halfColsA, halfColsB,
           halfColsB, halfColsA, halfColsB);
        //R3 <- R3 + R32
      _addBlocks(r3, r3, r32,
          halfRowsA, halfColsB,
          halfColsB, halfColsB, halfColsB);

      // C11 <- C11 + (A12 B21)  
        // R32 <- A12 B21
         _multBlocks(r32, a12, b21,
           halfRowsA, halfColsA, halfColsB,
           halfColsB, strideA, strideB);
        // C11 <- C11 + R32
        _addBlocks(c11, c11, r32,
          halfRowsA, halfColsB,
          strideC, strideC, halfColsB);

      //R1 <- A12 - R1
       _subBlocks(r1, a12, r1,
          halfRowsA, halfColsA,
          halfColsA, strideA, halfColsA);

      //R2 <- (B21 - R2)
       _subBlocks(r2, b21, r2,
          halfRowsB, halfColsB,
          halfColsB, strideB, halfColsB);
         
      // C12 <- C12 + (R1 B22)  
        // R32 <- R1 B22
         _multBlocks(r32, r1, b22,
           halfRowsA, halfColsA, halfColsB,
           halfColsB, halfColsA, strideB);
        // C12 <- C12 + R32
        _addBlocks(c12, c12, r32,
          halfRowsA, halfColsB,
          strideC, strideC, halfColsB);

      // C12 <- C12 + R3   
       _addBlocks(c12, c12, r3,
          halfRowsA, halfColsB,
          strideC, strideC, halfColsB);


      // C21 <- beta C21 + (A22 R2)  
        // R32 <- A22 R2
         _multBlocks(r32, a22, r2,
           halfRowsA, halfColsA, halfColsB,
           halfColsB, strideA, halfColsB);
        // C21 <- beta C21 + R32
        _accumBlocks(c21, r32,
          halfRowsA, halfColsB,
          strideC, halfColsB, reset);

       //R1 <- (A11 - A21)
       _subBlocks(r1, a11, a21,
          halfRowsA, halfColsA,
          halfColsA, strideA, strideA);
     
      //R2 <- B22 - B12
       _subBlocks(r2, b22, b12,
          halfRowsB, halfColsB,
          halfColsB, strideB, strideB);
 
      // R3 <- R3 + R1 R2  
        // R32 <- R1 R2
         _multBlocks(r32, r1, r2,
           halfRowsA, halfColsA, halfColsB,
           halfColsB, halfColsA, halfColsB);
        // R3 <- R3 + R32
        _addBlocks(r3, r3, r32,
          halfRowsA, halfColsB,
          halfColsB, halfColsB, halfColsB);

     // C21 <- C21 + R3
     _addBlocks(c21, c21, r3,
       halfRowsA, halfColsB,
       strideC, strideC, halfColsB);

     // C22 <- C22 + R3
     _addBlocks(c22, c22, r3,
       halfRowsA, halfColsB,
       strideC, strideC, halfColsB);


      delete[] r1;
      delete[] r2;
      delete[] r3;
      delete[] r32;

      return;

    }
 
  template<typename T>
    void Winograd<T>::_addBlocks(T* res, const T* const A, const T* const B, 
        const int rows, const int cols,
        const int strideRes, const int strideA, const int strideB) const {

      int rowStrideC = 0;
      int rowStrideA = 0;
      int rowStrideB = 0;
      for(int row=0; row < rows; row++){
        for(int col=0; col < cols; col++){
          res[rowStrideC + col] = A[ rowStrideA + col ];
          res[rowStrideC + col] += B[rowStrideB + col];
        }
        rowStrideC += strideRes;
        rowStrideA += strideA;
        rowStrideB += strideB;
      }
    }

  template<typename T>
    void  Winograd<T>::_subBlocks(T* res,const T* const A, const T* const B,
        const int rows, const int cols,
        const int strideRes, const int strideA, const int strideB) const {
      int rowStrideC = 0;
      int rowStrideA = 0;
      int rowStrideB = 0;
 
      T tmp;

      for(int row=0; row < rows; row++){
        for(int col=0; col < cols; col++){
          tmp = A[ rowStrideA + col ];
          tmp -= B[rowStrideB + col];
          res[rowStrideC + col] = tmp;
        }
        rowStrideC += strideRes;
        rowStrideA += strideA;
        rowStrideB += strideB;
      }
    }

  template<typename T>
    void Winograd<T>::_multBlocks(
        T* C, const T* const A, const T* const B,
        const int numRowsA, const int numColsA, const int numColsB,
        const int strideC, const int strideA, const int strideB) const {

      if( numRowsA < 64 || ( (numRowsA & 0x1) || numColsB & 0x1) ){ //FIXME: esto ha de pulirse, no se puede comprobar solo una dim
        baseMult(C,A,B,
            numRowsA, numColsA, numColsB,
            strideC, strideA, strideB, true);
        return;
      }
      else{
        run(C, A, B,
            numRowsA, numColsA, numColsB,
            strideC, strideA, strideB,true);
      }
      return;
    }
  template<typename T>
    void Winograd<T>::_accumBlocks(T* res, const T* const A, 
        const int rows, const int cols,
        const int strideRes, const int strideA, const bool reset) const {

      if( reset ){
        for(int row=0; row < rows; row++){
          for(int col=0; col < cols; col++){
            res[row * strideRes + col] = A[ (row * strideA) + col ];
          }
        }
      }
      else{
        for(int row=0; row < rows; row++){
          for(int col=0; col < cols; col++){
            res[row * strideRes + col] += A[ (row * strideA) + col ];
          }
        }
      }
    }


  template<typename T>
    void Winograd<T>::baseMult(
        T* C, const T* const A, const T* const B,
        const int numRowsA, const int numColsA, const int numColsB,
        const int strideC, const int strideA, const int strideB, const bool reset) const {

      if( reset ){
        T tmp, tmp2;
        for (int aRow = 0; aRow < numRowsA; aRow++) {
          for (int bCol = 0; bCol < numColsB; bCol++) {
            tmp2 = A[aRow * strideA ];
            tmp2 *= B[ bCol];
            for (int aCol = 1; aCol < numColsA; aCol++) {
               tmp = A[ aRow * strideA + aCol];
               tmp *= B[aCol * strideB + bCol];
               tmp2 += tmp;
            }
            C[aRow * strideC + bCol] = tmp2;
          }
        }
      }
      else{

        T tmp, tmp2;
        for (int aRow = 0; aRow < numRowsA; aRow++) {
          for (int bCol = 0; bCol < numColsB; bCol++) {
            tmp2 = A[aRow * strideA ];
            tmp2 *= B[ bCol];
            for (int aCol = 1; aCol < numColsA; aCol++) {
               tmp = A[ aRow * strideA + aCol];
               tmp *= B[aCol * strideB + bCol];
               tmp2 += tmp;
            }
            C[aRow * strideC + bCol] += tmp2;
          }
        }
      }

        return;
    }  



















//  template<typename T>
//   void Strassen<T>::run(T* C, const T* const A, const T* const B, 
//            const int numRowsA, const int numColsA, const int numColsB,
//            const int strideC, const int strideA, const int strideB) const{
//
//      const int halfRowsA = numRowsA / 2;
//      const int halfColsA = numColsA / 2;
//      const int halfColsB = numColsB / 2;
//
//      /* (numColsA = numRowsB) => (halfRowsB = halfColsA) 
//       *
//       * And the Q's would be ( halfRowsA x halfColsB ) 
//       * */
//      const int qsSize( halfRowsA * halfColsB );
//
//      //space for the 7 Q's is reserved right away and contiguously 
//      //just for performance reasons
//      T* Qs = new T[qsSize*7];
//
//      _generateQs(Qs, A, B, halfRowsA, halfColsA, halfColsB, strideA, strideB);
//      
//      const T* const Q0(Qs); 
//      const T* const Q1(Qs + 1*qsSize);
//      const T* const Q2(Qs + 2*qsSize);
//      const T* const Q3(Qs + 3*qsSize);
//      const T* const Q4(Qs + 4*qsSize);
//      const T* const Q5(Qs + 5*qsSize);
//      const T* const Q6(Qs + 6*qsSize);
//
//      T* const C00(C);
//      T* const C01(C + halfColsB );
//      T* const C10(C + (strideC * halfRowsA) );
//      T* const C11( C10 + halfColsB );
//
//      // C00
//      _addBlocks(C00, C00, Q0,
//          halfRowsA, halfColsB,
//          strideC, strideC, halfColsB);
//      _addBlocks(C00, C00, Q3,
//          halfRowsA, halfColsB,
//          strideC, strideC, halfColsB);
//      _subBlocks(C00, C00, Q4,
//          halfRowsA, halfColsB,
//          strideC, strideC, halfColsB);
//      _addBlocks(C00, C00, Q6,
//          halfRowsA, halfColsB,
//          strideC, strideC, halfColsB);
// 
//      // C01
//      _addBlocks(C01, C01, Q2,
//          halfRowsA, halfColsB,
//          strideC, strideC, halfColsB);
//      _addBlocks(C01, C01, Q4,
//          halfRowsA, halfColsB,
//          strideC, strideC, halfColsB);
//
// 
//      // C10
//      _addBlocks(C10, C10, Q1,
//          halfRowsA, halfColsB,
//          strideC, strideC, halfColsB);
//      _addBlocks(C10, C10, Q3,
//          halfRowsA, halfColsB,
//          strideC, strideC, halfColsB);
//
//
//      // C11
//      _addBlocks(C11, C11, Q0,
//          halfRowsA, halfColsB,
//          strideC, strideC, halfColsB);
//      _addBlocks(C11, C11, Q2,
//          halfRowsA, halfColsB,
//          strideC, strideC, halfColsB);
//      _subBlocks(C11, C11, Q1,
//          halfRowsA, halfColsB,
//          strideC, strideC, halfColsB);
//      _addBlocks(C11, C11, Q5,
//          halfRowsA, halfColsB,
//          strideC, strideC, halfColsB);
//
//      delete[] Qs;
//
//      return;
//
//    }
//
//  template<typename T>
//    void Strassen<T>::_generateQs(T* Q, const T* const A, const T* const B, const int halfRowsA, const int halfColsA, const int halfColsB,
//        const int strideA, const int strideB) const {
//      const int halfRowsB = halfColsA; // it's redundant, but makes things clearer
//
//      const int qsSize = halfRowsA * halfColsB;
//
//      const T* const a00 = A;
//      const T* const a01 = (A + halfColsA);
//      const T* const a10 = (A + (halfRowsA * strideA));
//      const T* const a11 = (a10 + halfColsA);
//
//      const T* const b00 = B;
//      const T* const b01 = (B + halfColsB);
//      const T* const b10 = (B + (halfRowsB * strideB));
//      const T* const b11 = (b10 + halfColsB);
//
//      T* tmpAs = new T[halfRowsA * halfColsA];
//      T* tmpBs = new T[halfRowsB * halfColsB];
// 
//      T* const Q0(Q); 
//      T* const Q1(Q + 1*qsSize);
//      T* const Q2(Q + 2*qsSize);
//      T* const Q3(Q + 3*qsSize);
//      T* const Q4(Q + 4*qsSize);
//      T* const Q5(Q + 5*qsSize);
//      T* const Q6(Q + 6*qsSize);
//
//      // Q0
//      _addBlocks(tmpAs, a00, a11,
//          halfRowsA, halfColsA,
//          halfColsA, strideA, strideA);
//      _addBlocks(tmpBs, b00, b11,
//          halfRowsB, halfColsB,
//          halfColsB, strideB, strideB);
//      _multBlocks(Q0, tmpAs, tmpBs,
//          halfRowsA, halfColsA, halfColsB,
//          halfColsB, halfColsA, halfColsB);
//      // Q1 
//       _addBlocks(tmpAs, a10, a11,
//          halfRowsA, halfColsA,
//          halfColsA, strideA, strideA);
//      _multBlocks(Q1, tmpAs, b00,
//          halfRowsA, halfColsA, halfColsB,
//          halfColsB, halfColsA, strideB);
//      // Q2 
//      _subBlocks(tmpBs, b01, b11,
//          halfRowsB, halfColsB,
//          halfColsB, strideB, strideB);
//      _multBlocks(Q2, a00, tmpBs,
//          halfRowsA, halfColsA, halfColsB,
//          halfColsB, strideA, halfColsB);
//      // Q3  
//      _subBlocks(tmpBs, b10, b00,
//          halfRowsB, halfColsB,
//          halfColsB, strideB, strideB);
//      _multBlocks(Q3, a11, tmpBs,
//          halfRowsA, halfColsA, halfColsB,
//          halfColsB, strideA, halfColsB);
//      // Q4 
//      _addBlocks(tmpAs, a00, a01,
//          halfRowsA, halfColsA,
//          halfColsA, strideA, strideA);
//      _multBlocks(Q4, tmpAs, b11,
//          halfRowsA, halfColsA, halfColsB,
//          halfColsB, halfColsA, strideB);
//      // Q5 
//       _subBlocks(tmpAs, a10, a00,
//          halfRowsA, halfColsA,
//          halfColsA, strideA, strideA);
//      _addBlocks(tmpBs, b00, b01,
//          halfRowsB, halfColsB,
//          halfColsB, strideB, strideB);
//      _multBlocks(Q5, tmpAs, tmpBs,
//          halfRowsA, halfColsA, halfColsB,
//          halfColsB, halfColsA, halfColsB);
//      // Q6 
//      _subBlocks(tmpAs, a01, a11,
//          halfRowsA, halfColsA,
//          halfColsA, strideA, strideA);
//      _addBlocks(tmpBs, b10, b11,
//          halfRowsB, halfColsB,
//          halfColsB, strideB, strideB);
//      _multBlocks(Q6, tmpAs, tmpBs,
//          halfRowsA, halfColsA, halfColsB,
//          halfColsB, halfColsA, halfColsB);
//
//
//      delete[] tmpAs;
//      delete[] tmpBs;
//    }
//  
//  template<typename T>
//    void Strassen<T>::_addBlocks(T* res, const T* const A, const T* const B, 
//        const int rows, const int cols,
//        const int strideRes, const int strideA, const int strideB) const {
//
//      for(int row=0; row < rows; row++){
//        for(int col=0; col < cols; col++){
//          res[row * strideRes + col] = A[ (row * strideA) + col ] + B[(row * strideB) + col];
//        }
//      }
//    }
//
//  template<typename T>
//    void  Strassen<T>::_subBlocks(T* res,const T* const A, const T* const B,
//        const int rows, const int cols,
//        const int strideRes, const int strideA, const int strideB) const {
//      for(int row=0; row < rows; row++){
//        for(int col=0; col < cols; col++){
//          res[row * strideRes + col] = A[ (row * strideA) + col ] - B[(row * strideB) + col];
//        }
//      }
//    }
//
//  template<typename T>
//    void Strassen<T>::_multBlocks(
//        T* C, const T* const A, const T* const B,
//        const int numRowsA, const int numColsA, const int numColsB,
//        const int strideC, const int strideA, const int strideB) const {
//
//      if( numRowsA < 4 ){ //FIXME: esto ha de pulirse, no se puede comprobar solo una dim
//        baseMult(C,A,B,
//            numRowsA, numColsA, numColsB,
//            strideC, strideA, strideB);
//        return;
//      }
//      else{
//        run(C, A, B,
//            numRowsA, numColsA, numColsB,
//            strideC, strideA, strideB);
//      }
//      return;
//    }
//
//  template<typename T>
//    void Strassen<T>::baseMult(
//        T* C, const T* const A, const T* const B,
//        const int numRowsA, const int numColsA, const int numColsB,
//        const int strideC, const int strideA, const int strideB) const {
//
//        for (int aRow = 0; aRow < numRowsA; aRow++) {
//          for (int bCol = 0; bCol < numColsB; bCol++) {
//            for (int aCol = 0; aCol < numColsA; aCol++) {
//              C[aRow * strideC + bCol] += 
//                A[ aRow * strideA + aCol] * B[aCol * strideB + bCol];
//            }
//          }
//        }
//
//        return;
//    }  

} /* namespace MatrixHelpers */

