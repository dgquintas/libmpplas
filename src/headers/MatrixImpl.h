//////////////////////////////////////////
//   IMPLEMENTATION
//////////////////////////////////////////

  template<typename T>
  Matrix<T>::Matrix()
: _dims(1,1), _data(1) 
{}

  template<typename T>
  Matrix<T>::Matrix(const size_t nAndm) 
: _dims(nAndm,nAndm), _data(nAndm*nAndm) 
{} 

  template<typename T>
  Matrix<T>::Matrix(const size_t n, const size_t m)
: _dims(n,m), _data(n*m) 
{} 

  template<typename T>
  Matrix<T>::Matrix(const Dimensions& dims)
: _dims(dims), _data( _dims.getProduct() )
{}

  template<typename T>
  Matrix<T>::Matrix(const Matrix<T>& rhs)
: _data(rhs._data), _dims(rhs._dims) //copy constr
{}

template<typename T>
Matrix<T>::Matrix(const std::string& str){
  std::istringstream inStream(str);
  operator>>(inStream,*this);
  return;
}

  template<typename T>
  Matrix<T>::Matrix(const std::vector<T>& rhs, const Dimensions& dims)
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



template<typename T>
Matrix<T>& Matrix<T>::operator=(const Matrix<T>& rhs){
  _data = rhs._data;
  _dims = rhs._dims;
}



template<typename T>
inline T& Matrix<T>::operator[](size_t i){
  return _data._SAFE_GET(i);
}
template<typename T>
inline const T& Matrix<T>::operator[](size_t i) const{
  return _data._SAFE_GET(i);
}


template<typename T>
inline T& Matrix<T>::operator()(size_t i){
  return _data._SAFE_GET(i);
}
template<typename T>
inline const T& Matrix<T>::operator()(size_t i) const{
  return _data._SAFE_GET(i);
}

template<typename T>
inline T& Matrix<T>::operator()(size_t i, size_t j){
  const size_t index( (i* _dims.getColumns() ) + j );
  return _data._SAFE_GET( index );
}
template<typename T>
inline const T& Matrix<T>::operator()(size_t i, size_t j) const{
  const size_t index( (i* _dims.getColumns() ) + j );
  return _data._SAFE_GET( index );

}


//////////////////////////////////////////////


template<typename T>
bool Matrix<T>::operator==(const Matrix<T>& rhs) const{
  if( this->getDimensions() != rhs.getDimensions() ){
    return false;
  }
  return std::equal(this->_data.begin(), this->_data.end(), rhs._data.begin());
}


//////////////////////////////////////////////

  template<typename T>
Matrix<T>& Matrix<T>::operator+=(const Matrix<T>& rhs) 
{
  //both matrices should have the same length (and shape!)
  if( this->getDimensions() != rhs.getDimensions() ){
    std::ostringstream oss;
    oss << "Right-hand-side operator size = " << rhs.getDimensions().toString();
    throw Errors::NonConformantDimensions(this->getDimensions(), rhs.getDimensions(),  oss.str());
  }
  const size_t length = this->getSize();
  T* const thisMat = &(this->operator[](0));
  const T* const rhsMat  = &(rhs[0]);

#pragma omp parallel for
  for(int i=0; i < length; i++){
    thisMat[i] += rhsMat[i];
  }

  return *this;
}

  template<typename T>
Matrix<T>& Matrix<T>::operator+=(const T& rhs) 
{
  const size_t length = this->getSize();
  T* const thisMat = &(this->operator[](0));

#pragma omp parallel for
  for(int i=0; i < length; i++){
    thisMat[i] += rhs;
  }

  return *this;
}

  template<typename T>
Matrix<T>& Matrix<T>::operator+=(const Digit rhs) 
{
  const size_t length = this->getSize();
  T* const thisMat = &(this->operator[](0));

#pragma omp parallel for
  for(int i=0; i < length; i++){
    thisMat[i] += rhs;
  }

  return *this;
}
  template<typename T>
Matrix<T>& Matrix<T>::operator+=(const SignedDigit rhs) 
{
  const size_t length = this->getSize();
  T* const thisMat = &(this->operator[](0));

#pragma omp parallel for
  for(int i=0; i < length; i++){
    thisMat[i] += rhs;
  }

  return *this;
}





//////////////////////////////////////////////




  template<typename T>
Matrix<T>& Matrix<T>::operator-=(const Matrix<T>& rhs) 
{
  //both matrices should have the same length (and shape!)
  if( this->getDimensions() != rhs.getDimensions() ){
    throw Errors::NonConformantDimensions(this->getDimensions(), rhs.getDimensions());
  }
  const size_t length = this->getSize();
  T* const thisMat = &(this->operator[](0));
  const T* const rhsMat  = &(rhs[0]);

#pragma omp parallel for
  for(int i=0; i < length; i++){
    thisMat[i] -= rhsMat[i];
  }

  return *this;
}
  template<typename T>
Matrix<T>& Matrix<T>::operator-=(const T& rhs) 
{
  const size_t length = this->getSize();
  T* const thisMat = &(this->operator[](0));

#pragma omp parallel for
  for(int i=0; i < length; i++){
    thisMat[i] -= rhs;
  }

  return *this;
}
  template<typename T>
Matrix<T>& Matrix<T>::operator-=(const Digit rhs) 
{
  const size_t length = this->getSize();
  T* const thisMat = &(this->operator[](0));

#pragma omp parallel for
  for(int i=0; i < length; i++){
    thisMat[i] -= rhs;
  }

  return *this;
}
  template<typename T>
Matrix<T>& Matrix<T>::operator-=(const SignedDigit rhs) 
{
  const size_t length = this->getSize();
  T* const thisMat = &(this->operator[](0));

#pragma omp parallel for
  for(int i=0; i < length; i++){
    thisMat[i] -= rhs;
  }

  return *this;
}


//////////////////////////////////////////////
  template<typename T>
Matrix<T>& Matrix<T>::operator*=(const Matrix<T>& rhs) {
  return *this; //TODO
}


template<typename T>
Matrix<T>& Matrix<T>::operator*=(const T& rhs){
  const size_t length = this->getSize();
  T* const thisMat = &(this->operator[](0));
#pragma omp parallel for
  for(int i=0; i < length; i++){
    thisMat[i] *= rhs;
  }
  return *this;
} 
template<typename T>
Matrix<T>& Matrix<T>::operator*=(const Digit rhs){
  const size_t length = this->getSize();
  T* const thisMat = &(this->operator[](0));
#pragma omp parallel for
  for(int i=0; i < length; i++){
    thisMat[i] *= rhs;
  }
  return *this;
}
template<typename T>
Matrix<T>& Matrix<T>::operator*=(const SignedDigit rhs){
  const size_t length = this->getSize();
  T* const thisMat = &(this->operator[](0));
#pragma omp parallel for
  for(int i=0; i < length; i++){
    thisMat[i] *= rhs;
  }
  return *this;
}
  template<typename T>
Matrix<T>& Matrix<T>::byElementProd(const Matrix<T>& rhs) 
{
  //both matrices should have the same length (and shape!)
  if( this->getDimensions() != rhs.getDimensions() ){
    throw Errors::NonConformantDimensions(this->getDimensions(), rhs.getDimensions());
  }
  const size_t length = this->getSize();
  T* const thisMat = &(this->operator[](0));
  const T* const rhsMat  = &(rhs[0]);

#pragma omp parallel for
  for(int i=0; i < length; i++){
    thisMat[i] *= rhsMat[i];
  }

  return *this;
}


//////////////////////////////////////////////

  template<typename T>
Matrix<T>& Matrix<T>::operator/=(const Matrix<T>& rhs){
  return *this; //TODO
}
  template<typename T>
Matrix<T>& Matrix<T>::operator/=(const T&){
  return *this; //TODO
}
  template<typename T>
Matrix<T>& Matrix<T>::operator/=(const Digit){
  return *this; //TODO
}
  template<typename T>
Matrix<T>& Matrix<T>::operator/=(const SignedDigit){
  return *this; //TODO
}
  template<typename T>
Matrix<T>& Matrix<T>::byElementDiv( const Matrix<T>& rhs){
  //both matrices should have the same length (and shape!)
  if( this->getDimensions() != rhs.getDimensions() ){
    throw Errors::NonConformantDimensions(this->getDimensions(), rhs.getDimensions());
  }
  const size_t length = this->getSize();
  T* const thisMat = &(this->operator[](0));
  const T* const rhsMat  = &(rhs[0]);

#pragma omp parallel for
  for(int i=0; i < length; i++){
    thisMat[i] /= rhsMat[i];
  }

  return *this;


}



//////////////////////////////////////////////


template<typename T>
Matrix<T>& Matrix<T>::transpose(){
  const size_t _n = _dims.getRows();
  const size_t _m = _dims.getColumns();
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
Matrix<T>& Matrix<T>::diagonalize(){
  return *this; //TODO
}
  template<typename T>
Matrix<T>& Matrix<T>::invert(){
  return *this; //TODO
}
  template<typename T>
T Matrix<T>::getDeterminant(){
  return T(); //TODO
}



template<typename T>
void Matrix<T>::setDiagonal(T n){
  typename std::vector<T>::iterator it;
  for(it = _data.begin(); it < _data.end(); it+= _dims.getColumns() +1){
    *it = n;
  }
  return;
}

template<typename T>
void Matrix<T>::setAll(T n){
  std::fill( _data.begin(), _data.end(), n );
  return ;
}

////////////////////////////////////


template<typename T>
size_t Matrix<T>::getSize() const{
  return this->getDimensions().getProduct();
}

template<typename T>
Dimensions Matrix<T>::getDimensions() const{
  return _dims;
}


template<typename T>
void Matrix<T>::setDimensions(const Dimensions& dims){
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
    typename std::vector<T>::iterator it;
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


template<typename T>
std::string Matrix<T>::toString() const { 
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

template<typename T>
void Matrix<T>::_reset() {
  _data.clear();
  _dims.setBoth(0,0);
}

////////////////////////////////////////////

template<typename T>
std::ostream& operator<<(std::ostream& out, const Matrix<T>& m){
  const size_t COLS = m.getDimensions().getColumns();
  size_t maxWidth[COLS];
  memset(maxWidth, 0, COLS*sizeof(size_t));

  for(int i=0; i < m._data.size(); i++){
    std::ostringstream oss;
    oss << m._data[i];
    maxWidth[i % COLS] = std::max(oss.str().size()+2, maxWidth[i % COLS]);
  }

  const size_t _n = m.getDimensions().getRows();
  const size_t _m = m.getDimensions().getColumns();
  for(int i=0; i < _n; i++){
    out << "[" ;
    for(int j=0; j < _m; j++ ){
      out << std::setw(maxWidth[j]) << std::right << m(i,j);
    }
    out << " ]\n" ;
  }
  return out;
}

template<typename T>
std::istream& operator>>(std::istream& in, Matrix<T>& m) {

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


