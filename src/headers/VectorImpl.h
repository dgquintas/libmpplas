

//////////////////////////////////////////
//   IMPLEMENTATION
//////////////////////////////////////////

  template<typename T, typename Alloc>
  Vector<T, Alloc>::Vector()
: Matrix<T, Alloc>()
{}
  template<typename T, typename Alloc>
  Vector<T, Alloc>::Vector(const int size)
: Matrix<T, Alloc>(1,size)
{}
  template<typename T, typename Alloc>
  Vector<T, Alloc>::Vector(const int size, const T& ini)
: Matrix<T, Alloc>(1, size)
{
  this->setAll(ini);
}

  template<typename T, typename Alloc>
  Vector<T, Alloc>::Vector(const Vector<T, Alloc>& rhs)
: Matrix<T, Alloc>(rhs)
{}

  template<typename T, typename Alloc>
  Vector<T, Alloc>::Vector(const std::vector<T, Alloc>& rhs)
: Matrix<T, Alloc>(rhs, Dimensions(1, rhs.size() ))
{}

  template<typename T, typename Alloc>
Vector<T, Alloc>::Vector(const std::string& str)
{
  std::istringstream inStream(str);
  operator>>(inStream,*this);
  return;
}



template<typename T, typename Alloc>
std::istream& operator>>(std::istream& in, Vector<T, Alloc>& v) {

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


template<typename T, typename Alloc>
Vector<T, Alloc>& Vector<T, Alloc>::operator=(const Vector<T, Alloc>& rhs){
  Matrix<T, Alloc>::operator=(rhs);
  return *this;
}



template<typename T, typename Alloc>
Vector<T, Alloc>& Vector<T, Alloc>::transpose(){
  this->_dims.swap();

  return *this;
}

//template<typename T, typename Alloc>
//Vector<T, Alloc>& Vector<T, Alloc>::normalize(){
//  return *this; //TODO
//}


template<typename T, typename Alloc>
R Vector<T, Alloc>::norm(const int p){
  
  return T(); //TODO
}


template<typename T, typename Alloc>
Vector<T, Alloc>& Vector<T, Alloc>::cross(const Vector<T, Alloc>& rhs){
  //both vectors should have three dimensions
  if( this->getSize() != 3 || rhs.getSize() != 3 ){
    std::ostringstream oss;
    oss << "Cross product operators should have three dimensions.";
    throw Errors::NonConformantDimensions(this->getDimensions(), rhs.getDimensions(), oss.str());
  }
  
  //it is not worth making this parallel, as the we will always have 
  //a fixed (and small) number of operations

  const Vector<T, Alloc> thisCopy(*this);

  (*this)(0) = (thisCopy(1) * rhs(2)) - (thisCopy(2) * rhs(1));
  (*this)(1) = (thisCopy(2) * rhs(0)) - (thisCopy(0) * rhs(2));
  (*this)(2) = (thisCopy(0) * rhs(1)) - (thisCopy(1) * rhs(0));

  return *this;
}

template<typename T, typename Alloc>
T Vector<T, Alloc>::dot( const Vector<T, Alloc>& rhs) {
  //both vectors should have the same length
  const int length = this->getSize();
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
  sum.makeZero();
  for(int i=0; i < length; i++){
    sum += thisVec[i];
  }

  return sum;
}


/////////////////////////////////////////
//  Non-modifying versions
/////////////////////////////////////////

template<typename T, typename Alloc>
Vector<T, Alloc> transpose( Vector<T, Alloc> src ){
  return src.transpose();
}

template<typename T, typename Alloc>
T dot( Vector<T, Alloc> lhs, const Vector<T, Alloc>& rhs ){
  return lhs.dot(rhs);
}

template<typename T, typename Alloc>
Vector<T, Alloc> cross( Vector<T, Alloc> lhs, const Vector<T, Alloc>& rhs ){
  return lhs.cross(rhs);
}

//template<typename T, typename Alloc>
//Vector<T, Alloc> normalize( Vector<T, Alloc> src ){
//  return src.normalize();
//}

template<typename T, typename Alloc>
R norm( Vector<T, Alloc> src ){
  return src.norm();
}

