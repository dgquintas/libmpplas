

//////////////////////////////////////////
//   IMPLEMENTATION
//////////////////////////////////////////

  template<typename T>
  Vector<T>::Vector()
: Matrix<T>()
{}
  template<typename T>
  Vector<T>::Vector(const int size)
: Matrix<T>(1,size)
{}
  template<typename T>
  Vector<T>::Vector(const int size, const T& ini)
: Matrix<T>(1, size)
{
  this->setAll(ini);
}

  template<typename T>
  Vector<T>::Vector(const Vector<T>& rhs)
: Matrix<T>(rhs)
{}

  template<typename T>
  Vector<T>::Vector(const std::vector<T>& rhs)
: Matrix<T>(rhs, Dimensions(1, rhs.size() ))
{}

  template<typename T>
Vector<T>::Vector(const std::string& str)
{
  std::istringstream inStream(str);
  operator>>(inStream,*this);
  return;
}



template<typename T>
std::istream& operator>>(std::istream& in, Vector<T>& v) {

  v._reset();

  char c;
  int numColsRead(0);

  in >> c;
  if( !in.good() || c != '[' ){
    throw Errors::InvalidSymbol(std::string(1,c));
  }

  T valueRead;

  while( in >> valueRead ){
    v._data.push_back(valueRead);
    numColsRead++;
    in >> std::ws >> c;
    if( c != ']' ){
      in.putback(c); 
    }
    else{ //reached the final ]
      break; 
    }
  }

  if( in.fail() ){
    throw Errors::InvalidSymbol(std::string(1,c));
  }

  v._dims.setBoth(1,numColsRead);
  return in;

}


template<typename T>
Vector<T>& Vector<T>::operator=(const Vector<T>& rhs){
  Matrix<T>::operator=(rhs);
  return *this;
}



template<typename T>
Vector<T>& Vector<T>::transpose(){
  this->_dims.swap();

  return *this;
}

//template<typename T>
//Vector<T>& Vector<T>::normalize(){
//  return *this; //TODO
//}


template<typename T>
R Vector<T>::norm(const int p){
  
  return T(); //TODO
}


template<typename T>
Vector<T>& Vector<T>::cross(const Vector<T>& rhs){
  //both vectors should have three dimensions
  if( this->getSize() != 3 || rhs.getSize() != 3 ){
    std::ostringstream oss;
    oss << "Cross product operators should have three dimensions.";
    throw Errors::NonConformantDimensions(this->getDimensions(), rhs.getDimensions(), oss.str());
  }
  
  //it is not worth making this parallel, as the we will always have 
  //a fixed (and small) number of operations

  const Vector<T> thisCopy(*this);

  (*this)(0) = (thisCopy(1) * rhs(2)) - (thisCopy(2) * rhs(1));
  (*this)(1) = (thisCopy(2) * rhs(0)) - (thisCopy(0) * rhs(2));
  (*this)(2) = (thisCopy(0) * rhs(1)) - (thisCopy(1) * rhs(0));

  return *this;
}

template<typename T>
T Vector<T>::dot( const Vector<T>& rhs) {
  //both vectors should have the same length
  const size_t length = this->getSize();
  if( length != rhs.getSize() ){
    std::ostringstream oss;
    oss << "for the dot product.";
    throw Errors::NonConformantDimensions(this->getDimensions(), rhs.getDimensions(), oss.str());
  }
  T* const thisVec = &(this->operator[](0));
  const T* const rhsVec  = &(rhs[0]);
#pragma omp parallel for 
  for(int i=0; i < length; i++){
    thisVec[i] *= rhsVec[i];
  }

  T sum;
  sum.hacerCero();
  for(int i=0; i < length; i++){
    sum += thisVec[i];
  }

  return sum;
}


/////////////////////////////////////////
//  Non-modifying versions
/////////////////////////////////////////

template<typename T>
Vector<T> transpose( Vector<T> src ){
  return src.transpose();
}

template<typename T>
T dot( Vector<T> lhs, const Vector<T>& rhs ){
  return lhs.dot(rhs);
}

template<typename T>
Vector<T> cross( Vector<T> lhs, const Vector<T>& rhs ){
  return lhs.cross(rhs);
}

//template<typename T>
//Vector<T> normalize( Vector<T> src ){
//  return src.normalize();
//}

template<typename T>
R norm( Vector<T> src ){
  return src.norm();
}

