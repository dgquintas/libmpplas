/* 
 * $Id$
 */
//////////////////////////////////////////
//   IMPLEMENTATION
//////////////////////////////////////////



  template<typename S>
  Polynomial<S>::Polynomial(const S& ini)
: _data(1,ini), _ini(ini) {
  _isSaField = bool(dynamic_cast<mpplas::Field<S>*>(&(_data[0])));
}

  template<typename S>
  Polynomial<S>::Polynomial(const Polynomial<S>& src )
  : _data(src._data), _isSaField(src._isSaField), _ini(src._ini){}

  template<typename S>
  Polynomial<S>::Polynomial(const std::string& str, const S& ini):
    _ini(ini) {

    std::istringstream inStream(str);
    operator>>(inStream,*this);

    if( this->_data.empty() ){
      this->_data.push_back(ini);
    }

    _isSaField = bool(dynamic_cast<mpplas::Field<S>*>(&(_data[0])));
    return;

  }


  template<typename S>
  Polynomial<S>::Polynomial(const std::vector<S>& coeffs, const S& ini)
  : _data(coeffs), _ini(ini) { 
    if( this->_data.empty() ){
      this->_data.push_back(ini);
    }

    _isSaField = bool(dynamic_cast<mpplas::Field<S>*>(&(_data[0])));
    _eraseLeadingZeros();
  }

  template<typename S>
Polynomial<S>::Polynomial(const S& coeff, const int exp, const S& ini) 
  : _ini(ini) {
    if( exp < 0 ){
      throw Errors::ExponenteNegativo();
    }
    _data.resize(exp+1, ini);
    _data.back() = coeff;

    _isSaField = bool(dynamic_cast<mpplas::Field<S>*>(&(_data[0])));
  }


////////////////////////////


template<typename S>
Polynomial<S>& Polynomial<S>::operator=(const Polynomial<S>& src){
  this->_data = src._data;
  this->_isSaField = src._isSaField;
  this->_ini = src._ini;

  return *this;
}

template<typename S>
Polynomial<S>& Polynomial<S>::fromString(const std::string& str){

    std::istringstream inStream(str);
    operator>>(inStream,*this);

    if( this->_data.empty() ){
      this->_data.push_back(this->_ini);
    }

    return *this;
}


template<typename S>
inline int Polynomial<S>::getDegree() const {

  return _data.size()-1;
}

template<typename S>
inline const S& Polynomial<S>::getLeadingCoefficient() const{
  assert( !_data.empty() );
  return _data.back();
}

template<typename S>
inline bool Polynomial<S>::isMonic() const {
  return this->_data.back() == S::getMultIdentity();
}

template<typename S>
  Polynomial<S>& Polynomial<S>::makeMonic(){

    Constraints::must_have_base<S, Field<S> > dummy __attribute__ ((__unused__));

    const S& leadingCoeff(this->getLeadingCoefficient());
    if( !(this->isMonic()) ){
      for( int i = 0 ; i < this->_data.size() ; i++){
        if( ! this->_data[i].esCero() ){
          this->_data[i] /= leadingCoeff;
        }
      }
    }
      
    return *this;
  }

template<typename S>
inline const S& Polynomial<S>::getIni() const {
  return this->_ini;
}


template<typename S>
bool Polynomial<S>::isCoeffsDomainAField() const {
  return _isSaField;
}


template<typename S>
inline void Polynomial<S>::makeZero() {
  this->_data.resize(1, this->_ini);
  this->_data[0] = S::getAddIdentity();
}
template<typename S>
inline void Polynomial<S>::makeOne() {
  this->_data.resize(1, this->_ini);
  this->_data[0] = S::getMultIdentity();
}
template<typename S>
inline bool Polynomial<S>::isZero () const {
  if( this->_data.empty() || 
      ((this->_data.size() == 1) && ( this->_data[0] == S::getAddIdentity() ) ) ){
    return true;
  }
  else{
    return false;
  }
}
template<typename S>
inline bool Polynomial<S>::isOne() const {
  if( (this->_data.size() == 1) && ( this->_data[0] == S::getMultIdentity() ) ){
    return true;
  }
  else{
    return false;
  }
}


template<typename S>
void Polynomial<S>::changeSign() {
  for(int i = 0; i < this->_data.size(); i++){
    this->_data[i] = -(this->_data[i]);
  }
}



template<typename S>
inline S& Polynomial<S>::operator[](int i){
  return _data[i];
}

template<typename S>
inline const S& Polynomial<S>::operator[](int i) const{
  return _data[i];
}

template<typename S>
bool Polynomial<S>::operator==(const Polynomial<S>& rhs) const{ 
  return this->_data == rhs._data;
}

template<typename S>
bool Polynomial<S>::operator<(const Polynomial<S>& rhs) const{
  if( this->getDegree() < rhs.getDegree()){
    return true;
  }
  else if( this->getDegree() > rhs.getDegree() ){
    return false;
  }
  else{
    for(int i = this->_data.size()-1; i >= 0; i--){
      if( (*this)._data[i] < rhs._data[i] ){
        return true;
      }
      else if( (*this)._data[i] > rhs._data[i] ){
        return false;
      }
    }
  }
  return false;
}

template<typename S>
Polynomial<S>& Polynomial<S>::operator+=(const Polynomial<S>& rhs){
  //element-wise addition on S
  //of course, if deg(this) > deg(rhs) (or viceversa), the elements
  //of the polynomial of lesser degree are considered to be 0 (ie, the
  //identity element for addition)
  const bool thisDegLessThanRhsDeg(this->getDegree() < rhs.getDegree());
  const int limitDeg = thisDegLessThanRhsDeg ? this->_data.size() : rhs._data.size();
  if( thisDegLessThanRhsDeg ){
    //copy the coefficients from rhs 'till we reach
    //this' degree
    typename MiVec<S>::const_iterator rhsIt(rhs._data.begin());
    rhsIt += this->_data.size();
    this->_data.insert( this->_data.end(), rhsIt, rhs._data.end() );
  }
#pragma omp parallel for
    for(int i=0; i < limitDeg; i++){
      _data[i] += rhs._data[i];
    }

    _eraseLeadingZeros();
    return *this;
  }


template<typename S>
Polynomial<S>& Polynomial<S>::operator+=(const S& s){
  this->_data[0] += s;
  return *this;

}

template<typename S>
Polynomial<S>& Polynomial<S>::operator-=(const Polynomial<S>& rhs){
  //element-wise substraction on S
  //of course, if deg(this) > deg(rhs) (or viceversa), the elements
  //of the polynomial of lesser degree are considered to be 0 (ie, the
  //identity element for addition)
  const bool thisDegLessThanRhsDeg(this->getDegree() < rhs.getDegree());
  const int limitDeg = thisDegLessThanRhsDeg ? this->_data.size() : rhs._data.size();
  if( thisDegLessThanRhsDeg ){
    //copy the coefficients from rhs 'till we reach
    //this' degree, INVERTING THEIR SIGN
    typename MiVec<S>::const_iterator rhsIt(rhs._data.begin());
    const int iniSize(this->_data.size());
    this->_data.resize( rhs._data.size(), this->_ini );
    typename MiVec<S>::iterator thisIt(this->_data.begin());
    rhsIt += iniSize; thisIt+= iniSize;
    for( ; rhsIt != rhs._data.end(); rhsIt++, thisIt++){
      (*thisIt) = (*rhsIt).getAddInverse();
    }
//    std::transform( rhsIt, rhs._data.end(), thisIt, std::negate<S>());
  }
#pragma omp parallel for
  for(int i=0; i < limitDeg; i++){
    _data[i] -= rhs._data[i];
  }

  _eraseLeadingZeros();
  return *this;
}
template<typename S>
Polynomial<S>& Polynomial<S>::operator-=(const S& s){
  this->_data[0] -= s;
  return *this;
}

template<typename S>
Polynomial<S>& Polynomial<S>::operator*=(const Polynomial<S>& rhs){
  mpplas::MiVec<S> dataOrig(this->_data);
  const int k(this->_data.size());
  const int l(rhs._data.size());
  this->_data.clear();
  this->_data.resize( k+l-1, this->_ini );
  
  //TODO: optimize: karatsuba
  for(int i = 0; i < k; i++){
    for( int j = 0; j < l; j++) {
      this->_data[i+j] += dataOrig[i] * rhs._data[j];
    }
  }

  _eraseLeadingZeros();
  return *this;
}
template<typename S>
Polynomial<S>& Polynomial<S>::operator*=(const S& s){
  for(int i = 0; i < this->_data.size(); i++){
    this->_data[i] *= s;
  }

  _eraseLeadingZeros();
  return *this;
}

template<typename S>
void Polynomial<S>::_divide(const Polynomial<S>& rhs){

  Polynomial<S> tmp(*this);
  if( this->isCoeffsDomainAField()){
    tmp._fieldDivide(rhs, this, false);
  }
  else{
    tmp._ufdDivide(rhs, this, false);
  }
}

template<typename S>
Polynomial<S>& Polynomial<S>::square(){
  //TODO: optimize: karatsuba
  const Polynomial<S> tmp(*this);
  this->operator*=(tmp);

  return *this;
}




template<typename S>
void Polynomial<S>::_reduce(const Polynomial<S>& rhs){

  if( this->isCoeffsDomainAField() ){
    this->_fieldDivide(rhs, NULL, true);
  }
  else{
    this->_ufdDivide(rhs, NULL, true);
  }
}


// knuth 421
template<typename S>
void Polynomial<S>::_fieldDivide(const Polynomial<S>& rhs, Polynomial<S>* const q, const bool reduce) {
  const int m = this->getDegree();
  const int n = rhs.getDegree();
 
  if( m < n ){ 
    if( q != NULL ){
      q->_data.clear();
      q->_data.push_back( this->_ini );
    }
    return;
  }


  Polynomial<S>& u(*this);
  S* qk;
  if( q != NULL ){
    q->_data.clear();
    q->_data.resize(m-n+1, this->_ini);
    qk = &(q->_data[m-n]);
  }
  else{
    qk = new S(this->_ini); 
  }

  const Polynomial<S>& v(rhs);
  const S& vn(rhs.getLeadingCoefficient()); 

  for(int k = m-n; k >= 0; k--){
    (*qk) = u[n+k] / vn;
    int j;
    for(j = n+k-1; j >= k; j--){
      u[j] -= (*qk)*v[j-k];
    } 
    if( q != NULL ){
      qk--;
    }

  }

  if( reduce ){
    this->_data.resize(n, this->_ini);
    if( n == 0 ){
      this->_data.push_back( this->_ini );
    }
    this->_eraseLeadingZeros();
  }
  if( q != NULL ){
    q->_eraseLeadingZeros(); 
  }
  else{
    delete qk;
  }

}


// knuth 425
template<typename S>
void Polynomial<S>::_ufdDivide(const Polynomial<S>& rhs, Polynomial<S>* const q, const bool reduce) {
  const int m = this->getDegree();
  const int n = rhs.getDegree();

  if( m < n ){ 
    if( q != NULL ){
      q->_data.clear();
      q->_data.push_back(this->_ini);
    }
    return;
  }
  
  Polynomial<S>& u(*this);
  if( q != NULL ){
    q->_data.clear();
    q->_data.resize(m-n+1, this->_ini);
  }
  const Polynomial<S>& v(rhs);
  const S& vn(rhs.getLeadingCoefficient()); 
  S vnK( vn ^ (Digit)(m-n) ); 

  for(int k = m-n; k >= 0; k--){
    if( q != NULL ){
      (*q)[k] = u[n+k] * vnK;
    }
    vnK /= vn;
    int j;
    for(j = n+k-1; j >= k; j--){
      u[j] *= vn;
      u[j] -= u[n+k]*v[j-k];
    }
    for( ; j >= 0; j--){
      u[j] *= vn;
    }
  }

  if( reduce ){
    this->_data.resize(n, this->_ini);
    if( n == 0 ){
      this->_data.push_back(this->_ini);
    }
    this->_eraseLeadingZeros();
  }
  if( q != NULL ){
    q->_eraseLeadingZeros(); 
  }

}

template<typename S>
Polynomial<S>& Polynomial<S>::operator/=(const Polynomial<S>& rhs){

  this->_divide(rhs);
  return *this;
}


template<typename S>
Polynomial<S>& Polynomial<S>::operator/=(const S& s){
  
  const int dataSize( this->_data.size() );
#pragma omp parallel for
  for(int i = 0; i < dataSize; i++){
    this->_data[i] /= s;
  }
  _eraseLeadingZeros();
  return *this;
}

template<typename S>
Polynomial<S>& Polynomial<S>::operator%=(const Polynomial<S>& rhs){
  this->_reduce(rhs);
  _eraseLeadingZeros();
  return *this;
}

template<typename S>
Polynomial<S>& Polynomial<S>::operator%=(const S& rhs){
  Polynomial<S> tmp( rhs, 0, this->_ini );
  this->operator%=(tmp);
  _eraseLeadingZeros();
  return *this;
}




template<typename S>
void Polynomial<S>::divAndMod(Polynomial<S> lhs, const Polynomial<S>& rhs, Polynomial<S>* q, Polynomial<S>* r){
  if( lhs.isCoeffsDomainAField() ){
    if( !rhs.isCoeffsDomainAField() ){
      throw Errors::FieldRequired("RHS polynomial at 'divAndMod' does not have coeffs. on a field");
    }
    lhs._fieldDivide(rhs, q, true);
    *r = lhs;
  }
  else{
    lhs._ufdDivide(rhs, q, true);
    *r = lhs;
  }

  return;
}



template<typename S>
S Polynomial<S>::getContent() const {
  GCD<Z>* gcd;
  MethodsFactory::getReference().getFunc(gcd);

  const S res( gcd->gcd( this->_data ) );

  return res;
}

template<typename S>
Polynomial<S>& Polynomial<S>::makePrimitive(){

  //sign issue: knuth 4.6.1, pag 423, last paragraph
  if( this->getLeadingCoefficient().isNegative() ){
    this->operator/=( -this->getContent() );
  }
  else{
    this->operator/=( this->getContent() );
  }

  return *this;
}

template<typename S>
std::string Polynomial<S>::toString() const {
  // presents the polynomial as [(coeff_n, exp_n)...(coeff_0, 0)]
  std::ostringstream oss;
  oss << "[";
  for(int i = this->_data.size()-1; i >= 0; i--){
    if( this->_data[i] != S::getAddIdentity() ){
      oss << "(" << this->_data[i] << "," << i << ")";
    }
  }
  oss << "]";
  
  return oss.str();
}

template<typename S>
std::string Polynomial<S>::toHRString() const {
  std::ostringstream oss;
  oss << *this;
  return oss.str();
}


template<typename S>
template<typename T>
T Polynomial<S>::evaluate(const T& x0) const {
  if( this->getDegree() == 0 ){
    return this->_data[0];
  }
  T result(this->_ini);
  this->_horner2ndOrder(&result, x0);
  return result;
}


template<typename S>
template<typename T>
void Polynomial<S>::_horner2ndOrder(T* const result, const T& x0) const {
  //described in [knuth] 4.6.4, page 487
  //and [dorn] 
  const int n = this->getDegree();
  const T x0Sqr( x0 ^ (Digit)2 ); 

  T res1(_ini), res2(_ini);

#pragma omp parallel sections 
{
#pragma omp section
{
  //even coefficients
  int idx = 2*(int)floor(n/2.0);
  res1 = this->_data[idx];
  while( idx >= 2 ){
    res1 *= x0Sqr;
    idx -= 2;
    res1 += this->_data[idx];
  } 
}
#pragma omp section
{
  //odd coefficients
  int idx = 2*(int)ceil(n/2.0)-1;
  res2 = this->_data[idx];
  while( idx >= 3 ){
    res2 *= x0Sqr;
    idx -= 2;
    res2 += this->_data[idx];
  }
  res2 *= x0;
}
}

  (*result) = res1;
  (*result) += res2;

  return;
}

template<typename S>
void Polynomial<S>::_eraseLeadingZeros(){
  typename mpplas::MiVec<S>::iterator it = this->_data.end()-1;
  for( ; ((*it) == S::getAddIdentity() ) && (it != this->_data.begin()); 
      it--) ;
  it++;
  this->_data.erase(it, this->_data.end());

  return;
}

      

template<typename S>
std::ostream& operator<<(std::ostream& out, const Polynomial<S>& p){
  std::ostringstream oss;
  for(int i = p.getDegree(); i > 0; i--){
    if( p[i] != S::getAddIdentity() /* zero */ ){
      oss.setf(std::ios::showpos);
      oss << " " << p[i] << "*x^";
      oss.unsetf(std::ios::showpos);
      oss << i ;
    }
  }
  //the independent coeff
  if( p[0] != S::getAddIdentity() || p.getDegree() == 0 ){
    //if the polynomial only has the constant coeff, it is displayed,
    //even if it's zero
    oss.setf(std::ios::showpos);
    oss << " " << p[0] ;
    oss.unsetf(std::ios::showpos);
  }

  out << oss.str();
  return out;
}

template<typename S>
std::istream& operator>>(std::istream& in, Polynomial<S>& p) {

  p._data.resize(1, p._ini);

  char c;
  std::pair<S, int> coeffAndExp(p._ini,0); //has to be initialized in case S doesn't have a dfl const
  std::vector< std::pair<S, int> > coeffsAndExps;
  int maxExp = 0;
  S coef(p._ini);
  int exp;

  in >> c;
  if( !in.good() || c != '[' ){
    throw Errors::InvalidSymbol(std::string(1,c));
  }
  while( in >> c ){
    if( c != '('){
      in.putback(c);
      break;
    }
    if( !in.good() || c != '(' ){
      throw Errors::InvalidSymbol(std::string(1,c));
    }
    in >> coef;
    coeffAndExp.first = coef;
    in >> c;
    if( !in.good() || c != ',' ){
      throw Errors::InvalidSymbol(std::string(1,c));
    }
    in >> exp;
    if( exp < 0 ){
      throw Errors::ExponenteNegativo();
    }
    if( exp > maxExp ){
      maxExp = exp;
    }
    in >> c;
    coeffAndExp.second = exp;
    coeffsAndExps.push_back(coeffAndExp);
    if( !in.good() || c != ')' ){
      throw Errors::InvalidSymbol(std::string(1,c));
    }
  }
  if( !in.good() || c != ']' ){
    throw Errors::InvalidSymbol(std::string(1,c));
  }

  p._data.resize(maxExp+1, p._ini);
  for(int i = 0; i < (int)coeffsAndExps.size(); i++){
    const std::pair<S, int>& tmpPair(coeffsAndExps[i]);
    p._data[ tmpPair.second ] = tmpPair.first;
  }

  p._eraseLeadingZeros();
  return in;
}


  template<typename S>
    Polynomial<S> operator-(Polynomial<S> m){
      m.changeSign();
      return m;
    }

     

  template<typename S>
    Polynomial<S> operator+(Polynomial<S> lhs, const Polynomial<S>& rhs){
      lhs += rhs;
      return lhs;
    }
  template<typename S>
    Polynomial<S> operator-(Polynomial<S> lhs, const Polynomial<S>& rhs){
      lhs -= rhs;
      return lhs;
    }
  template<typename S>
    Polynomial<S> operator*(Polynomial<S> lhs, const Polynomial<S>& rhs){
      lhs *= rhs;
      return lhs;
    }
  template<typename S>
    Polynomial<S> operator/(Polynomial<S> lhs, const Polynomial<S>& rhs){
      lhs /= rhs;
      return lhs;
    }
  template<typename S>
    Polynomial<S> operator%(Polynomial<S> lhs, const Polynomial<S>& rhs){
      lhs %= rhs;
      return lhs;
    }

  template<typename S>
    Polynomial<S> operator+(Polynomial<S> lhs, const S& rhs){
      lhs += rhs;
      return lhs;
    }
  template<typename S>
    Polynomial<S> operator-(Polynomial<S> lhs, const S& rhs){
      lhs -= rhs;
      return lhs;
    }
  template<typename S>
    Polynomial<S> operator*(Polynomial<S> lhs, const S& rhs){
      lhs *= rhs;
      return lhs;
    }
  template<typename S>
    Polynomial<S> operator/(Polynomial<S> lhs, const S& rhs){
      lhs /= rhs;
      return lhs;
    }
  template<typename S>
    Polynomial<S> operator%(Polynomial<S> lhs, const S& rhs){
      lhs %= rhs;
      return lhs;
    }

  template<typename S>
    Polynomial<S> operator+(const S& lhs, Polynomial<S> rhs){
      rhs += lhs;
      return rhs;
    }
  template<typename S>
    Polynomial<S> operator-(const S& lhs, Polynomial<S> rhs){
      rhs = -rhs;
      rhs += lhs;
      return rhs;
    }
  template<typename S>
    Polynomial<S> operator*(const S& lhs, Polynomial<S> rhs){
      rhs *= lhs;
      return rhs;
    }
  template<typename S>
    Polynomial<S> operator/(const S& lhs, Polynomial<S> rhs){
      const Polynomial<S> tmp( lhs, 0, rhs._ini);
      rhs /= tmp;
      return rhs;
    }
  template<typename S>
    Polynomial<S> operator%(const S& lhs, Polynomial<S> rhs){
      const Polynomial<S> tmp( lhs, 0, rhs._ini);
      rhs %= tmp;
      return rhs;
    }


//XXX: The reason why these methods are here instead of in GCD.cpp/h is because
//this file itself uses GCD.h, thus creating a circulan dependency. Why this 
//doesn't usually happen is because the "executable" code is in a .cpp file.
//this can't be done in this case because of the use of templates
  template<typename S>
    Polynomial<S> GCDPolyKnuth<S>::gcd(Polynomial<S> u, Polynomial<S> v){
      GCD<Z>* gcd;
      MethodsFactory::getReference().getFunc(gcd);

      if( u.getDegree() < v.getDegree() ){
        std::swap(u,v);
      }
      const S d( gcd->gcd( u.getContent(), v.getContent() ) );

      u.makePrimitive();
      v.makePrimitive();
      
      while (true) {
        Polynomial<S> r(u);
        r %= v;
        if ( r.getDegree() == 0){
          if( !r.isZero() ){
            // contant polynomial
            v.makeOne();
          }
          break;
        }
        else{ //iterate, euclidean step
          u = v;
          r.makePrimitive();
          v = r;
        }
      }

      v *= d;
      return v;


  }

  template<typename S>
    Polynomial<S> GCDPolyCollins<S>::gcd(Polynomial<S> u, Polynomial<S> v){
    GCD<Z>* gcd;
    MethodsFactory::getReference().getFunc(gcd);
    
    if( u.getDegree() < v.getDegree() ){
      std::swap(u,v);
    }
    const S d( gcd->gcd( u.getContent(), v.getContent() ) );

    u.makePrimitive();
    v.makePrimitive();

    S g(S::getMultIdentity());
    S h(S::getMultIdentity());

    while (true) { // C2
      int const delta( u.getDegree() - v.getDegree() );
      Polynomial<S> r( u % v );
      if ( r.getDegree() == 0){
        if( !r.isZero() ){
          // contant polynomial
          v.makeOne();
        }
        break;
      }
      else{ //adjust remainder. C3
        u = v;
        r /= (g*(h ^ (Digit)delta));
        v = r;
        g = u.getLeadingCoefficient();
        if( delta == 0 ){
          h *= (g ^ ((Digit)delta));
        }
        else if( delta == 1) {
          h = (g ^ ((Digit)delta));
        }
        else{ // delta > 1
          h = (g ^ ((Digit)delta)) / ( h ^ (Digit)(delta-1) ) ;
        }
      }
    }

    v.makePrimitive();
    v *= d;
    return v;
  }

  template<typename S>
    Polynomial<S> GCDExtPoly<S>::gcdext(Polynomial<S> g, Polynomial<S> h, Polynomial<S>* const s, Polynomial<S>* const t){
 
      Constraints::must_have_base<S, Field<S> > dummy __attribute__ ((__unused__));

      assert( s && t);
      if( h.isZero() ){
        s->makeOne();
        t->makeZero();
        return g;
      }
      Polynomial<S> s1(g.getIni());
      Polynomial<S> s2(g.getIni());
      Polynomial<S> t1(g.getIni());
      Polynomial<S> t2(g.getIni());
      s2.makeOne();
      s1.makeZero();
      t2.makeZero();
      t1.makeOne();

      Polynomial<S> q(g.getIni()),r(g.getIni());
      while( !h.isZero() ){
        Polynomial<S>::divAndMod(g,h, &q, &r);
        (*s) = s2 - q*s1;
        (*t) = t2 - q*t1;
        g = h;
        h = r;
        s2 = s1;
        s1 = (*s);
        t2 = t1;
        t1 = (*t);
      }

      (*s) = s2;
      (*t) = t2;

      g.makeMonic();
      return g;
    }

  template<typename S>
    Polynomial<S> GCDEuclid4Fields<S>::gcd(Polynomial<S> u, Polynomial<S> v){
      
      Constraints::must_have_base<S, Field<S> > dummy __attribute__ ((__unused__));
      if( u.isOne() ){
        return u;
      }
      if( v.isOne() ){
        return v;
      }

      Polynomial<S> r;
      while( !v.isZero() ){
        r = u % v;
        u = v;
        v = r;
      }
      u.makeMonic();
      return u;
    }



