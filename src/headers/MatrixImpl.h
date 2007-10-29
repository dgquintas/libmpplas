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
: _data(rhs), _dims(dims)
{
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
  const int index( (i* _dims.getColumns() ) + j );
  return _data[ index ];
}
template<typename T, typename Alloc>
inline const T& Matrix<T, Alloc>::operator()(int i, int j) const{
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


  if( (n1 > n2) || (m1 > m2) ){
    assert(false); //FIXME: raise exception instead
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
  this->setAll( T::ZERO );
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

  const int rowsPerBlock = 16; //FIXME
  const int colsPerBlock = 16;

  const int aRowBlocks = aRows / rowsPerBlock;
  const int aColBlocks = aCols / colsPerBlock;
  const int bColBlocks = bCols / colsPerBlock;

  const int aRowsExtra = aRows % rowsPerBlock;
  const int aColsExtra = aCols % colsPerBlock;
  const int bColsExtra = bCols % colsPerBlock;

  MatrixHelpers::Strassen<T> strassen;

#pragma omp parallel for schedule(static)
  for (int aRow = 0; aRow < aRows; aRow += rowsPerBlock) {
    for (int bCol = 0; bCol < bCols; bCol += colsPerBlock) {
      T* C( &(res( aRow, bCol )) );
      for (int aCol = 0; aCol < aCols; aCol += colsPerBlock ) {
        const T* const A( &(lhs(aRow, aCol)) );
        const T* const B( &(rhs(aCol, bCol)) );

        const bool aRowsOF = ((aRow + rowsPerBlock) > aRows);
        const bool aColsOF = ((aCol + colsPerBlock) > aCols);
        const bool bColsOF = ((bCol + colsPerBlock) > bCols);

        if( aRowsOF || aColsOF || bColsOF ){
          strassen.baseMult(C,A,B,
              aRowsOF ? aRowsExtra : rowsPerBlock,
              aColsOF ? aColsExtra : colsPerBlock,
              bColsOF ? bColsExtra : rowsPerBlock,
              bCols, aCols, bCols);
        }
        else {
          strassen.run(C,A,B,
              rowsPerBlock,colsPerBlock,rowsPerBlock,
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

  template<typename T>
   void Strassen<T>::run(T* C, const T* const A, const T* const B, 
            const int numRowsA, const int numColsA, const int numColsB,
            const int strideC, const int strideA, const int strideB) const{

      const int halfRowsA = numRowsA / 2;
      const int halfColsA = numColsA / 2;
      const int halfColsB = numColsB / 2;
      const int halfRowsB = halfColsA; // it's redundant, but makes things clearer

      /* (numColsA = numRowsB) => (halfRowsB = halfColsA) 
       *
       * And the Q's would be ( halfRowsA x halfColsB ) 
       * */
      const int qsSize( halfRowsA * halfColsB );

      //space for the 7 Q's is reserved right away and contiguously 
      //just for performance reasons
      T Qs[qsSize*7];

      _generateQs(Qs, A, B, halfRowsA, halfColsA, halfColsB, strideA, strideB);
      
      const T* const Q0(Qs); 
      const T* const Q1(Qs + 1*qsSize);
      const T* const Q2(Qs + 2*qsSize);
      const T* const Q3(Qs + 3*qsSize);
      const T* const Q4(Qs + 4*qsSize);
      const T* const Q5(Qs + 5*qsSize);
      const T* const Q6(Qs + 6*qsSize);

      T* const C00(C);
      T* const C01(C + halfColsB );
      T* const C10(C + (strideC * halfRowsA) );
      T* const C11( C10 + halfColsB );

      // C00
      _addBlocks(C00, C00, Q0,
          halfRowsA, halfColsB,
          strideC, strideC, halfColsB);
      _addBlocks(C00, C00, Q3,
          halfRowsA, halfColsB,
          strideC, strideC, halfColsB);
      _subBlocks(C00, C00, Q4,
          halfRowsA, halfColsB,
          strideC, strideC, halfColsB);
      _addBlocks(C00, C00, Q6,
          halfRowsA, halfColsB,
          strideC, strideC, halfColsB);
 
      // C01
      _addBlocks(C01, C01, Q2,
          halfRowsA, halfColsB,
          strideC, strideC, halfColsB);
      _addBlocks(C01, C01, Q4,
          halfRowsA, halfColsB,
          strideC, strideC, halfColsB);

 
      // C10
      _addBlocks(C10, C10, Q1,
          halfRowsA, halfColsB,
          strideC, strideC, halfColsB);
      _addBlocks(C10, C10, Q3,
          halfRowsA, halfColsB,
          strideC, strideC, halfColsB);


      // C11
      _addBlocks(C11, C11, Q0,
          halfRowsA, halfColsB,
          strideC, strideC, halfColsB);
      _addBlocks(C11, C11, Q2,
          halfRowsA, halfColsB,
          strideC, strideC, halfColsB);
      _subBlocks(C11, C11, Q1,
          halfRowsA, halfColsB,
          strideC, strideC, halfColsB);
      _addBlocks(C11, C11, Q5,
          halfRowsA, halfColsB,
          strideC, strideC, halfColsB);

      return;

    }

  template<typename T>
    void Strassen<T>::_generateQs(T* Q, const T* const A, const T* const B, const int halfRowsA, const int halfColsA, const int halfColsB,
        const int strideA, const int strideB) const {
      const int halfRowsB = halfColsA; // it's redundant, but makes things clearer

      const int qsSize = halfRowsA * halfColsB;

      const T* const a00 = A;
      const T* const a01 = (A + halfColsA);
      const T* const a10 = (A + (halfRowsA * strideA));
      const T* const a11 = (a10 + halfColsA);

      const T* const b00 = B;
      const T* const b01 = (B + halfColsB);
      const T* const b10 = (B + (halfRowsB * strideB));
      const T* const b11 = (b10 + halfColsB);

      T tmpAs[halfRowsA * halfColsA];
      T tmpBs[halfRowsB * halfColsB];
 
      T* const Q0(Q); 
      T* const Q1(Q + 1*qsSize);
      T* const Q2(Q + 2*qsSize);
      T* const Q3(Q + 3*qsSize);
      T* const Q4(Q + 4*qsSize);
      T* const Q5(Q + 5*qsSize);
      T* const Q6(Q + 6*qsSize);

      // Q0
      _addBlocks(tmpAs, a00, a11,
          halfRowsA, halfColsA,
          halfColsA, strideA, strideA);
      _addBlocks(tmpBs, b00, b11,
          halfRowsB, halfColsB,
          halfColsB, strideB, strideB);
      _multBlocks(Q0, tmpAs, tmpBs,
          halfRowsA, halfColsA, halfColsB,
          halfColsB, halfColsA, halfColsB);
      // Q1 
       _addBlocks(tmpAs, a10, a11,
          halfRowsA, halfColsA,
          halfColsA, strideA, strideA);
      _multBlocks(Q1, tmpAs, b00,
          halfRowsA, halfColsA, halfColsB,
          halfColsB, halfColsA, strideB);
      // Q2 
      _subBlocks(tmpBs, b01, b11,
          halfRowsB, halfColsB,
          halfColsB, strideB, strideB);
      _multBlocks(Q2, a00, tmpBs,
          halfRowsA, halfColsA, halfColsB,
          halfColsB, strideA, halfColsB);
      // Q3  
      _subBlocks(tmpBs, b10, b00,
          halfRowsB, halfColsB,
          halfColsB, strideB, strideB);
      _multBlocks(Q3, a11, tmpBs,
          halfRowsA, halfColsA, halfColsB,
          halfColsB, strideA, halfColsB);
      // Q4 
      _addBlocks(tmpAs, a00, a01,
          halfRowsA, halfColsA,
          halfColsA, strideA, strideA);
      _multBlocks(Q4, tmpAs, b11,
          halfRowsA, halfColsA, halfColsB,
          halfColsB, halfColsA, strideB);
      // Q5 
       _subBlocks(tmpAs, a10, a00,
          halfRowsA, halfColsA,
          halfColsA, strideA, strideA);
      _addBlocks(tmpBs, b00, b01,
          halfRowsB, halfColsB,
          halfColsB, strideB, strideB);
      _multBlocks(Q5, tmpAs, tmpBs,
          halfRowsA, halfColsA, halfColsB,
          halfColsB, halfColsA, halfColsB);
      // Q6 
      _subBlocks(tmpAs, a01, a11,
          halfRowsA, halfColsA,
          halfColsA, strideA, strideA);
      _addBlocks(tmpBs, b10, b11,
          halfRowsB, halfColsB,
          halfColsB, strideB, strideB);
      _multBlocks(Q6, tmpAs, tmpBs,
          halfRowsA, halfColsA, halfColsB,
          halfColsB, halfColsA, halfColsB);
    }
  
  template<typename T>
    void Strassen<T>::_addBlocks(T* res, const T* const A, const T* const B, 
        const int rows, const int cols,
        const int strideRes, const int strideA, const int strideB) const {

      for(int row=0; row < rows; row++){
        for(int col=0; col < cols; col++){
          res[row * strideRes + col] = A[ (row * strideA) + col ] + B[(row * strideB) + col];
        }
      }
    }

  template<typename T>
    void  Strassen<T>::_subBlocks(T* res,const T* const A, const T* const B,
        const int rows, const int cols,
        const int strideRes, const int strideA, const int strideB) const {
      for(int row=0; row < rows; row++){
        for(int col=0; col < cols; col++){
          res[row * strideRes + col] = A[ (row * strideA) + col ] - B[(row * strideB) + col];
        }
      }
    }

  template<typename T>
    void Strassen<T>::_multBlocks(
        T* C, const T* const A, const T* const B,
        const int numRowsA, const int numColsA, const int numColsB,
        const int strideC, const int strideA, const int strideB) const {

      if( numRowsA <= 16){ //FIXME: esto ha de pulirse, no se puede comprobar solo una dim
        baseMult(C,A,B,
            numRowsA, numColsA, numColsB,
            strideC, strideA, strideB);
        return;
      }
      else{
        run(C, A, B,
            numRowsA, numColsA, numColsB,
            strideC, strideA, strideB);
      }
      return;
    }

  template<typename T>
    void Strassen<T>::baseMult(
        T* C, const T* const A, const T* const B,
        const int numRowsA, const int numColsA, const int numColsB,
        const int strideC, const int strideA, const int strideB) const {

        for (int aRow = 0; aRow < numRowsA; aRow++) {
          for (int bCol = 0; bCol < numColsB; bCol++) {
            for (int aCol = 0; aCol < numColsA; aCol++) {
              C[aRow * strideC + bCol] += 
                A[ aRow * strideA + aCol] * B[aCol * strideB + bCol];
            }
          }
        }

        return;
    }  

} /* namespace MatrixHelpers */

