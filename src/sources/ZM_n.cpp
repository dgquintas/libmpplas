/*
 * $Id$
 */

#include <cassert>

#include "ZM_n.h"
#include "Funciones.h"
#include "Potencia.h"


namespace mpplas{

  ZM_n::ZM_n(const Z& mod) 
    : _mod(mod) 
  {
    _r.potenciaBase( _mod.longitud() );
    _r %= _mod;
    _rSqr.potenciaBase( _mod.longitud() * 2 );
    _rSqr %= _mod;
    _precomputations(_mPrime);
  }

  ZM_n::ZM_n( const Z& num, const Z& mod ) 
    : _mod(mod), Z(num) 
  {
    _r.potenciaBase( _mod.longitud() );
    _r %= _mod;
    _rSqr.potenciaBase( _mod.longitud() * 2 );
    _rSqr %= _mod;

    _precomputations(_mPrime);
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
    *this = _r;
    static const Digit BASEMASK = ((Digit)1) << (Constants::BITS_EN_CIFRA -1);

    const int initialBitPos = (e.numBits()-1);
    int cifraPos = initialBitPos >> Constants::LOG_2_BITS_EN_CIFRA;
    Digit inDigitPosMask = 1;
    inDigitPosMask <<= ( initialBitPos & ((1<<Constants::LOG_2_BITS_EN_CIFRA)-1) ); //ie, i % BITS_EN_CIFRA
    for(int i = initialBitPos; i >= 0 ; i--){
      this->square();
      if( (e[cifraPos] & inDigitPosMask ) ){ 
        //si el i-esimo bit de "e" es uno...
        *this = _montgomeryProd(*this, original);
      }
      inDigitPosMask >>= 1;
      if( !inDigitPosMask ){
        cifraPos--;
        inDigitPosMask = BASEMASK;
      }
    }

    return *this;
  }




  ZM_n& ZM_n::inverse(){
    *this = _newMontgomeryInverse(*this);

    return *this;
  }

  ZM_n& ZM_n::square(){
    this->cuadrado();

    _montgomeryRed( *this );

    return *this;
  }

  Z ZM_n::toZ(){
    Z res(_montgomeryProd(*this,1));
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

  ///////////////////////////////////////


  void ZM_n::_precomputations(Z& mPrime) {
    Funciones* const funcs(Funciones::getInstance());
    
    mPrime.hacerUno();
    mPrime.potenciaBase(1);
    PotModular* potMod; 
    funcs->getFunc(potMod);

    mPrime -= potMod->inversa(_mod, _mPrime); // m' = -mod^{-1} (mod base)

    return;
  }

  void ZM_n::_montgomeryRed(Z& toReduce) {
    const size_t n = _mod.longitud();
    if( toReduce.longitud() > 2*n){
      throw Errors::TooBig();
    }
    Digit u;
    
    for(size_t i=0; i < n; i++){
      u = ( toReduce[i] * _mPrime)[0];
      toReduce += ( (u*_mod).potenciaBase(i) );
    }

    toReduce.divisionBase(n);
    if( toReduce >= _mod ){
      toReduce -= _mod;
    }
   
    return;
  }

  ZM_n ZM_n::_montgomeryProd(const ZM_n& lhs, const Z& rhs){ 
    if( rhs.longitud() > _mod.longitud() ){
      throw Errors::TooBig();
    }

    const size_t n = _mod.longitud() ; 
    ZM_n A; 
    A.hacerCero(); 
    A._clone(lhs);


   Digit u; 

    Z& aZ(A);
    const Z& lhsZ(lhs);
    size_t i;

    for( i=0; i < lhsZ.longitud() ; i++){
      u = ((aZ[0] + (lhsZ[i] * rhs[0])) * _mPrime)[0];
      aZ = ((aZ + (lhsZ[i] * rhs) + (u * _mod)) >> Constants::BITS_EN_CIFRA);
    }
    for( ; i < n ; i++){ // los x[i] serían 0
      u = (aZ[0] * _mPrime)[0];
      aZ += (u*_mod);
      aZ.divisionBase(1);
    }

    if( aZ >= _mod ){
      aZ -= _mod;
    }

    return A;  // x·y·R^{-1} (mod mod)  /  R = base^{n}

  }

  void ZM_n::_almostMontgomeryInverse(const ZM_n& a, Z& r, Digit& k)
  {
    Z u(a._mod);
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
    if( r >= a._mod){
      r -= a._mod;
    }
    r  = a._mod -r;
    return;
  }

  ZM_n ZM_n::_newMontgomeryInverse(const ZM_n& a){
    ZM_n r;
    r._clone(a);
    Digit k;
    const Digit n = a.getMod().numBits();
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


  void ZM_n::_clone(const ZM_n& src){
    this->_mod = src._mod;
    this->_r = src._r;
    this->_rSqr = src._rSqr;
    this->_mPrime = src._mPrime;

    return;
  }



  
}



