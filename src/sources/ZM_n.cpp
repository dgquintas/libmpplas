/*
 * $Id$
 */

#include <cassert>

#include "ZM_n.h"
#include "MethodsFactory.h"
#include "Potencia.h"
#include "BitChecker.h"


namespace mpplas{

  ZM_n::ZM_n(const Z& mod) 
    : _mod(mod) 
  {
    _r.potenciaBase( _mod.longitud() );
    _r %= _mod;
    _rSqr.potenciaBase( _mod.longitud() * 2 );
    _rSqr %= _mod;
    _precomputations();
  }

  ZM_n::ZM_n( const Z& num, const Z& mod ) 
    : _mod(mod), Z(num) 
  {
    _r.potenciaBase( _mod.longitud() );
    _r %= _mod;
    _rSqr.potenciaBase( _mod.longitud() * 2 );
    _rSqr %= _mod;

    _precomputations();
    this->operator%=(_mod);
    *this = _montgomeryProd(*this,_rSqr);
  }

  ZM_n::ZM_n( const Z_n& num ) 
    : _mod(num.getMod()), Z(num) 
  {
    _r.potenciaBase( _mod.longitud() );
    _r %= _mod;
    _rSqr.potenciaBase( _mod.longitud() * 2 );
    _rSqr %= _mod;

    _precomputations();
    this->operator%=(_mod);
    *this = _montgomeryProd(*this,_rSqr);
  }


  ZM_n::ZM_n( const ZM_n& rhs) 
    : Z(rhs), _mod(rhs._mod), _r(rhs._r), _rSqr(rhs._rSqr), _mPrime(rhs._mPrime)
  {}


  ZM_n::ZM_n() {}

  //////////////////////////////////////

  ZM_n& ZM_n::operator=(const Z& rhs) {
    Z* const thisAsZ(this);
    thisAsZ->operator=(rhs);
    this->operator%=(_mod);
    *this = _montgomeryProd(*this,_rSqr);

    return *this;
  }

  ZM_n& ZM_n::operator=(const ZM_n& rhs) {
    this->_clone(rhs);
    ((Z*)this)->operator=((const Z&)rhs);

    return *this;
  }


////////////////////////////////////////////////////////



  ZM_n& ZM_n::operator+=(const ZM_n& rhs){
    Z& thisAsZ(*this);
    const Z& rhsAsZ(rhs);

    thisAsZ += rhsAsZ;
    if( thisAsZ >= this->_mod ){
      thisAsZ -= this->_mod;
    }

    return *this;
  }
  ZM_n& ZM_n::operator+=(const Z& rhs){
    ZM_n tmp;
    tmp._clone( *this);
    tmp = rhs;

    this->operator+=(tmp);
    
    return *this;
  }



  ZM_n& ZM_n::operator-=(const ZM_n& rhs){
    Z& thisAsZ(*this);
    const Z& rhsAsZ(rhs);

    thisAsZ -= rhsAsZ;
    while( thisAsZ.isNegative() ){
      thisAsZ += this->_mod;
    }

    return *this;
  } 
  ZM_n& ZM_n::operator-=(const Z& rhs){
    ZM_n tmp;
    tmp._clone( *this);
    tmp = rhs;

    this->operator-=(tmp);
    
    return *this;
  }


  ZM_n& ZM_n::operator*=(const ZM_n& rhs){
    assert( this->_mod == rhs._mod );

    *this = _montgomeryProd(*this, rhs );

    return *this;
  } 
  ZM_n& ZM_n::operator*=(const Z& rhs){
    ZM_n tmp;
    tmp._clone( *this);
    tmp = rhs;

    this->operator*=(tmp);
    
    return *this;
  }


  ZM_n& ZM_n::operator^=(const Z& e){
    const ZM_n original(*this);
    ((Z*)this)->operator=(_r);

    Utils::BitChecker bc(e);

    while( bc.hasPrevious() ) {
      this->square();
      if( bc.checkPrevious() ){
        *this = _montgomeryProd(*this, original);
      }
    }

    return *this;
  }

  ZM_n& ZM_n::operator^=(const SignedDigit e){
    this->operator^=( Z(e) );
    return *this;
  }



  ZM_n& ZM_n::inverse(){
    //FIXME : no comprueba si la inversa existe!!!
    *this = _newMontgomeryInverse(*this);

    return *this;
  }

  ZM_n& ZM_n::square(){
    this->cuadrado();

    _montgomeryRed( *this );

    return *this;
  }

  Z ZM_n::toZ() const {
    Z res(_montgomeryProd(*this,(Digit)1));
    return res;
  }

  ///////////////////////////////////////

  ZM_n operator+(ZM_n lhs, const Z& rhs){
    lhs += rhs;

    return lhs;
  }
  ZM_n operator+(ZM_n lhs, const ZM_n& rhs){
    lhs += rhs;

    return lhs;
  }

  ZM_n operator-(ZM_n lhs, const Z& rhs){
    lhs -= rhs;

    return lhs;
  }
  ZM_n operator-(ZM_n lhs, const ZM_n& rhs){
    lhs -= rhs;

    return lhs;
  }

  ZM_n operator*(ZM_n lhs, const Z& rhs){
    lhs *= rhs;

    return lhs;
  }
  ZM_n operator*(ZM_n lhs, const ZM_n& rhs){
    lhs *= rhs;

    return lhs;
  }

  ZM_n operator^(ZM_n base, const Z& exp){
    base ^= exp;

    return base;
  }
 
  ZM_n operator^(ZM_n base, const SignedDigit exp){
    base ^= exp;

    return base;
  }


  ///////////////////////////////////////


  void ZM_n::_precomputations() {
    MethodsFactory* const funcs(MethodsFactory::getInstance());
    
    _mPrime.hacerUno();
    _mPrime.potenciaBase(1);
    Exponentiation<Z_n>* potMod; 
    funcs->getFunc(potMod);

    _mPrime -= potMod->inverse(_mod, _mPrime); // m' = -mod^{-1} (mod base)

    return;
  }

  void ZM_n::_montgomeryRed(Z& toReduce) {
    const int n = _mod.longitud();
    if( toReduce.longitud() > 2*n){
      throw Errors::TooBig();
    }
//    Digit u;
    Z tmp;
    for(int i=0; i < n; i++){
      tmp = toReduce[i];
      tmp *= _mPrime;
      tmp.moduloBase(1);
      tmp *= _mod;
      tmp.potenciaBase(i);
      toReduce += tmp;
//      u = ( toReduce[i] * _mPrime)[0];
//      toReduce += ( (u*_mod).potenciaBase(i) );
    }

    toReduce.divisionBase(n);
    if( toReduce >= _mod ){
      toReduce -= _mod;
    }
   
    return;
  }

  ZM_n ZM_n::_montgomeryProd(const ZM_n& lhs, const Z& rhs){ 
    if( rhs.longitud() > lhs.getMod().longitud() ){
      throw Errors::TooBig();
    }

    const int n = lhs.getMod().longitud() ; 
    ZM_n A; 
    A.hacerCero(); 
    A._clone(lhs);


   Digit u; 

    Z& aZ(A);
    const Z& lhsZ(lhs);
    int i;

    Z tmp;
    Z tmp2;
    Digit tmpDigit;

    for( i=0; i < lhsZ.longitud() ; i++){
      tmpDigit = (aZ[0] + (lhsZ[i] * rhs[0]));
      tmp = lhs._mPrime;
      tmp *= tmpDigit;
      tmp.moduloBase(1);
      tmp *= lhs.getMod();
      tmp2 = rhs;
      tmp2 *= lhsZ[i];
      aZ += tmp2;
      aZ += tmp;
      aZ.divisionBase(1);
//      u = ( (aZ[0] + (lhsZ[i] * rhs[0]))* lhs._mPrime)[0];
//      aZ = ((aZ + (lhsZ[i] * rhs) + (u * lhs.getMod())) >> Constants::BITS_EN_CIFRA);
    }
    for( ; i < n ; i++){ // los x[i] serían 0
      tmp = lhs._mPrime;
      tmp *= aZ[0];
      tmp.moduloBase(1);
      tmp *= lhs.getMod();
      aZ += tmp;
      //u = (aZ[0] * lhs._mPrime)[0];
      //aZ += (u*lhs.getMod());
      aZ.divisionBase(1);
    }

    if( aZ >= lhs.getMod() ){
      aZ -= lhs.getMod();
    }

    return A;  // x·y·R^{-1} (mod mod)  /  R = base^{n}

  }

  void ZM_n::_almostMontgomeryInverse(const ZM_n& a, Z& r, Digit& k) {
    Z u(a.getMod());
    Z v(a);
    r.hacerCero();
    Z s((Digit)1);

    k = 0;
    while( v > (Digit)0 ){
      if( u.esPar() ){
        u >>= 1; // u = u / 2
        s <<= 1; // s = s * 2
      } 
      else if( v.esPar() ){
        v >>= 1;
        r <<= 1;
      }
      else if( u > v ){
        u -= v; 
        u >>= 1;
        r += s;
        s <<= 1;
      }
      else { // v >= u
        v -= u; 
        v >>= 1;
        s += r;
        r <<= 1;
      }
      k++;
    }
    if( r >= a.getMod()){
      r -= a.getMod();
    }
    r  = a.getMod() -r;
    return;
  }

  ZM_n ZM_n::_newMontgomeryInverse(const ZM_n& a){
    ZM_n r;
    r._clone(a);
    Digit k;
    const Digit n = a.getMod().getBitLength();
    const Digit m = a.getMod().longitud() * Constants::BITS_EN_CIFRA;

    _almostMontgomeryInverse(a, r, k);

    if( (n <= k) && (k <= m) ){
      r = _montgomeryProd(r, r._rSqr);
      k += m;
    }
    r = _montgomeryProd( r, r._rSqr );
    Z tmp((Digit)1);
    tmp <<= (2*m-k);
    r = _montgomeryProd( r, tmp );

    return r;

  }


  /** Copies into @a this the precomputed constants of @a src.
   *
   * @param src the source Montgomery integer from which to
   * copy the precomputed constants. */
  void ZM_n::_clone(const ZM_n& src){
    this->_mod = src._mod;
    this->_r = src._r;
    this->_rSqr = src._rSqr;
    this->_mPrime = src._mPrime;

    return;
  }



  
}



