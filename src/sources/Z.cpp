/*
 * $Id$
 */

#include <cstring>
#include <sstream>
#include <stack>
#include <cassert>
#include <cstdlib>
#include <cmath>
#include <string>
#include <utility>
#include <iomanip>
#include <cctype> //for isdigit


#include "Z.h"
#include "MethodsFactory.h"
#include "VectorialCPU.h"
#include "Potencia.h"
#include "Primos.h"
#include "GCD.h"

namespace mpplas{

  int Z::precisionSalida_ = 0;
  
  const bool Z::addCommutative(true); 
  const bool Z::groupCyclic(true);

  const bool Z::divisionRing(false);
  const bool Z::multAssociative(true);
  const bool Z::multCommutative(true);
  const bool Z::unitaryRing(true);

  const Z Z::ZERO((Digit)0);
  const Z Z::ONE((Digit)1);

  // implementacion constructores
  Z::Z()
    : coefPoliB_(1,(Digit)0), signo_(1) 
  {}

  Z::Z(const Z& otro)
    : coefPoliB_(otro.coefPoliB_), signo_(otro.signo_)
    {}

//  Z Z::convertir(const Digit origen)
//  {
//    Z temp(origen);
//    return temp;
//  }
//
//  Z Z::convertir(const SignedDigit origen)
//  {
//    Z temp(origen);
//    return temp;
//  }
//
//  Z Z::convertir(const char* origen) throw (Errors::Sintactico)
//  {
//    Z temp(origen);
//    return temp;
//  }
//
//
//  Z Z::convertir(const double origen)
//  {
//    Z temp(origen);
//    return temp;
//  }
//
//  Z Z::convertir(const MiVec<Digit>& vec)
//  {
//    Z temp; temp.coefPoliB_ = vec;
//    temp.limpiarCeros();
//    return temp;
//  }

  /* constructores privados para el uso de la funcion de conversion */
  Z::Z(const SignedDigit otro)
    : coefPoliB_(1)
    {
      coefPoliB_[0] = labs(otro);
      if(otro < 0)
        signo_ = -1;
      else 
        signo_ = 1;
    }

  Z::Z(const Digit otro)
    : coefPoliB_(1,otro)
    {
      signo_ = 1;
    }

  Z::Z(const double otro)
  {
    std::ostringstream cadStream;
    cadStream.setf(std::ios_base::fixed);
    cadStream.unsetf(std::ios_base::showpoint);
    cadStream.precision(Constants::MAX_EXP10_DOUBLE); 
    cadStream << floor(otro);
    std::string cadena = cadStream.str();
    cadena.erase(cadena.find_first_of('.'));

    Z temp(cadena.c_str());

    this->operator=(temp);

    limpiarCeros();

    return;
  }

  Z::Z(const char* strC)
  {
    std::string temp(strC);
    std::istringstream flujoEntrada(temp);
    operator>>(flujoEntrada,*this);
    return;
  }
 

  Z::Z(const std::string& str)
  {
    std::istringstream flujoEntrada(str);
    operator>>(flujoEntrada,*this);
    return;
  }
  
  Z::Z(const MiVec<Digit>& vec)
    : coefPoliB_(vec)
  {
    signo_ = 1;
    this->limpiarCeros();
  }

  

  Z::~Z()
  {
    //nada q hacer: no ha habido nada reservado con new
  }


  /*** OPERADORES DE ASIGNACION ***/

  Z& Z::operator=(const Z& drcha)
  {
    coefPoliB_ = drcha.coefPoliB_;
    signo_ = drcha.signo_;

    return *this;
  }

  Z& Z::operator=(const Digit der)
  {
    coefPoliB_.clear();
    coefPoliB_.push_back(der);
    signo_ = 1;
    return *this;
  }

  /******************************/

  /*** OPERADORES DE COMPARACION ***/
  bool Z::operator>(const Z& der) const
  {


    if( (signo_ > 0) ){
      if( (der.signo_ > 0) )
        return VectorialCPU::mayorque(coefPoliB_,der.coefPoliB_);
      else // der < 0
        return true;
    }
    else{ // this < 0
      if( (der.signo_ > 0) )
        return false;
      else // der < 0
        return VectorialCPU::menorque(coefPoliB_, der.coefPoliB_);
    }
  }

  bool Z::operator<(const Z& der) const
  {


    if( (signo_ > 0) ){
      if( (der.signo_ > 0) )
        return VectorialCPU::menorque(coefPoliB_,der.coefPoliB_);
      else // der < 0
        return false;
    }
    else{ // this < 0
      if( (der.signo_ > 0) )
        return true;
      else // der < 0
        return VectorialCPU::mayorque(coefPoliB_, der.coefPoliB_);
    }

  }

  bool Z::operator==(const Z& der) const {
    if( signo_ == der.signo_ ){
      if ( VectorialCPU::igual(coefPoliB_, der.coefPoliB_) ){
        return true;
      }
      else{
        return false;
      }
    }
    else{
      //the only case in which with different signs we still
      //can have == numbers is if both are 0
     return this->esCero() && der.esCero();
    }
  }

  bool Z::operator!=(const Z& der) const
  {
    return !(operator==(der));
  }

  bool Z::operator>=(const Z& der) const
  {
    return !(operator<(der));
  }
  bool Z::operator<=(const Z& der) const
  {
    return !(operator>(der));
  }

  bool Z::operator>(const SignedDigit der) const
  {


    if( (signo_ > 0) )
      if(der >= 0)
        return VectorialCPU::mayorque( coefPoliB_, (Digit)der );
      else // der < 0
        return true;
    else // signo_ < 0 
      if( der >= 0)
        return false;
      else // der < 0
        // ambos son negativos. Por tanto el mayor ser� el menor
        // en valor absoluto
        return VectorialCPU::menorque( coefPoliB_, (Digit)labs(der) );
  }  

  bool Z::operator<(const SignedDigit der) const
  {


    if( (signo_ > 0) )
      if(der >= 0)
        return VectorialCPU::menorque( coefPoliB_, (Digit)der );
      else // der < 0
        return false;
    else // signo_ < 0 
      if( der >= 0)
        return true;
      else // der < 0
        // ambos son negativos. Por tanto el menor ser� el mayor
        // en valor absoluto
        return VectorialCPU::mayorque( coefPoliB_, (Digit)labs(der) );
  }

  bool Z::operator==(const SignedDigit der) const
  {


    if( (signo_ > 0) )
      if(der >= 0)
        return VectorialCPU::igual( coefPoliB_, (Digit)der );
      else // der < 0
        return false;
    else // signo_ < 0 
      if( der >= 0)
        return false;
      else // der < 0
        //ambos negativos; ser�n iguales si son iguales en valor
        //absoluto
        return VectorialCPU::igual( coefPoliB_, (Digit)labs(der) );
  }
  bool Z::operator!=(const SignedDigit der) const
  {
    return !(operator==(der));
  }
  bool Z::operator>=(const SignedDigit der) const
  {
    if( operator>(der) || operator==(der) )
      return true;
    else
      return false;
  }
  bool Z::operator<=(const SignedDigit der) const
  {
    if( operator<(der) || operator==(der) )
      return true;
    else
      return false;
  }

  bool Z::operator>(const Digit der) const
  {


    if( (signo_ > 0) )
      return VectorialCPU::mayorque( coefPoliB_, der );
    else // signo_ < 0 
      return false;
  }  

  bool Z::operator<(const Digit der) const
  {


    if( (signo_ > 0) )
      return VectorialCPU::menorque( coefPoliB_, der );
    else // signo_ < 0 
      return true;
  }

  bool Z::operator==(const Digit der) const
  {


    if( (signo_ > 0) )
      return VectorialCPU::igual( coefPoliB_, der );
    else // signo_ < 0 
      return false;
  }
  bool Z::operator!=(const Digit der) const
  {
    return !(operator==(der));
  }
  bool Z::operator>=(const Digit der) const
  {
    if( operator>(der) || operator==(der) )
      return true;
    else
      return false;
  }
  bool Z::operator<=(const Digit der) const
  {
    if( operator<(der) || operator==(der) )
      return true;
    else
      return false;
  }




  Z& Z::operator+=(const Z& sumandoDerecha)
  {

    if( (signo_ > 0) ){
      if( (sumandoDerecha.signo_ > 0) ){
        this->coefPoliB_ = VectorialCPU::sumaMP(coefPoliB_, sumandoDerecha.coefPoliB_);
        return *this;
      }
      else{ // sumandoDerecha < 0
        if( VectorialCPU::mayorque(coefPoliB_, sumandoDerecha.coefPoliB_) )
          this->coefPoliB_ = VectorialCPU::restaMP(coefPoliB_, sumandoDerecha.coefPoliB_);
        else{
          this->coefPoliB_ = VectorialCPU::restaMP(sumandoDerecha.coefPoliB_, coefPoliB_);
          this->signo_ = -1;
        }
        return *this;
      }
    }
    else{ // this < 0
      if( (sumandoDerecha.signo_ > 0) ){
        // (-a) + b = b - a
        if( VectorialCPU::mayorque(coefPoliB_,sumandoDerecha.coefPoliB_) )
          this->coefPoliB_ = VectorialCPU::restaMP(coefPoliB_, sumandoDerecha.coefPoliB_);
        else{
          this->coefPoliB_ = VectorialCPU::restaMP(sumandoDerecha.coefPoliB_, coefPoliB_);
          this->signo_ = 1;
        }
        return *this;
      }
      else{ // sumandoDerecha < 0
        this->coefPoliB_ = VectorialCPU::sumaMP(this->coefPoliB_, sumandoDerecha.coefPoliB_);
        //mantener el signo "-"
        return *this;
      }
    }
  }

  Z& Z::operator-=(const Z&sustraendo)
  {

    if( (signo_ > 0) ){
      if( (sustraendo.signo_ > 0) ){
        // a - b
        if( VectorialCPU::mayorque(sustraendo.coefPoliB_, coefPoliB_) ){ // b > a
          this->coefPoliB_ = VectorialCPU::restaMP(sustraendo.coefPoliB_, coefPoliB_);
          this->signo_ = -1;
        }
        else // b <= a
          this->coefPoliB_ = VectorialCPU::restaMP(coefPoliB_, sustraendo.coefPoliB_);
        // se mantiene el signo +
      }
      else{ // sustraendo  < 0
        // a - (-b) = a + b
        this->coefPoliB_ = VectorialCPU::sumaMP(coefPoliB_, sustraendo.coefPoliB_);
        //se mantiene el signo +
      }
    }
    else{ // this < 0
      if( (sustraendo.signo_ > 0) ){
        // (-a) - b = -(a + b)
        this->coefPoliB_ = VectorialCPU::sumaMP(coefPoliB_, sustraendo.coefPoliB_);
        // se mantiene el signo -
      }
      else{ // sustraendo < 0
        // (-a) - (-b) = b - a
        if( VectorialCPU::mayorque(sustraendo.coefPoliB_, coefPoliB_) ){ // b > a
          this->coefPoliB_ = VectorialCPU::restaMP(sustraendo.coefPoliB_, coefPoliB_);
          this->signo_ = 1;
        }
        else // b <= a
          this->coefPoliB_ = VectorialCPU::restaMP( coefPoliB_, sustraendo.coefPoliB_ );
        // se deja el signo -

      }
    }

    return *this;

  }

  Z& Z::operator*=(const Z& factorDer)
  {

    if( (signo_ > 0) ){
      if( (factorDer.signo_ > 0) ){
        // a * b
        this->coefPoliB_ = VectorialCPU::multMP(coefPoliB_, factorDer.coefPoliB_);
        // se mantiene el signo +
      }
      else{ // factorDer  < 0
        // a * (-b) = -(ab)
        this->coefPoliB_ = VectorialCPU::multMP(coefPoliB_, factorDer.coefPoliB_);
        this->signo_ = -1;
      }
    }
    else{ // this < 0
      if( (factorDer.signo_ > 0) ){
        // (-a) * b = -(ab)
        this->coefPoliB_ = VectorialCPU::multMP(coefPoliB_, factorDer.coefPoliB_);
        // se deja el signo -
      }
      else{ // factorDer < 0
        // (-a) * (-b) = ab
        this->coefPoliB_ = VectorialCPU::multMP(coefPoliB_, factorDer.coefPoliB_);
        this->signo_ = 1;
      }
    }

    return *this;
  } 


  Z& Z::operator/=(const Z& divisor)
  {

    if( divisor.esCero() )
      throw Errors::DivisionPorCero();

    if( (signo_ > 0) ){
      if( (divisor.signo_ > 0) ){
        // a / b
        this->coefPoliB_ = (VectorialCPU::divMP(coefPoliB_, divisor.coefPoliB_)).first;
        // se mantiene el signo +
      }
      else{ // divisor  < 0
        // a / (-b) = -(a / b)
        this->coefPoliB_ = (VectorialCPU::divMP(coefPoliB_, divisor.coefPoliB_)).first;
        this->signo_ = -1;
      }
    }
    else{ // this < 0
      if( (divisor.signo_ > 0) ){
        // (-a) / b = -(a / b)
        this->coefPoliB_ = (VectorialCPU::divMP(coefPoliB_, divisor.coefPoliB_)).first;
        // se deja el signo -
      }
      else{ // divisor < 0
        // (-a) / (-b) = a / b
        this->coefPoliB_ = (VectorialCPU::divMP(coefPoliB_, divisor.coefPoliB_)).first;
        this->signo_ = 1;
      }
    }

    return *this;
  }

  Z& Z::operator%=(const Z& divisor)
  {
    if( divisor.esCero() )
      throw Errors::DivisionPorCero();

    if( divisor.signo_ > 0){ // divisor.signo_ > 0
      if( signo_ > 0 ){
        coefPoliB_ = (VectorialCPU::divMP(coefPoliB_, divisor.coefPoliB_)).second;
        // se mantiene el signo +
      }
      else{ //signo_ < 0
        coefPoliB_ = (VectorialCPU::divMP(coefPoliB_, divisor.coefPoliB_)).second;
        if( !(this->esCero()) )
          this->operator+=(divisor); // ajuste por dividendo negativo
        signo_ = 1;
        //El "floor" de la def del modulo(m,n) = m - (floor(m,n) * n)
        //ser�a una unidad menor que la parte entera, ya que ser�a
        //negativo. Por tanto, esto es equivalente a:
        // modulo(m,n) / n < 0 = modulo(m,-n) + n 
        //
        // Por otra parte, el modulo siempre tiene el signo del divisor

      }
    }
    else{ // divisor.signo_ < 0
      if( signo_ > 0){
        coefPoliB_ = (VectorialCPU::divMP(coefPoliB_, divisor.coefPoliB_)).second;
        if( !(this->esCero()) )
          this->operator+=(divisor); //ajuste por ser divisor negativo
        //El "floor" de la def del modulo(m,n) = m - (floor(m,n) * n)
        //ser�a una unidad menor que la parte entera, ya que ser�a
        //negativo. Por tanto, esto es equivalente a:
        // modulo(m,n) / n < 0 = modulo(m,-n) + n (esto seria una resta,
        // recordar que n es < 0 ).
        //
        // Por otra parte, el modulo siempre tiene el signo del divisor
      }
      else{ // signo_ < 0
        coefPoliB_ = (VectorialCPU::divMP(coefPoliB_, divisor.coefPoliB_)).second;
        signo_ = -1;
      }
    }

    return *this;
  }


  Z& Z::operator&=(const Z& der)
  {
    bool derMenor;
    if( this->coefPoliB_.size() > der.coefPoliB_.size() )
      derMenor = true;
    else // cifras de this <= cifras de der
      derMenor = false;     
    
    if( derMenor ){
      this->coefPoliB_.resize(der.coefPoliB_.size(),(Digit)0);
      for(int i = 0; i < der.coefPoliB_.size(); i++)
        this->coefPoliB_[i] &= der.coefPoliB_[i];
    }
    else
      for(int i = 0; i < this->coefPoliB_.size(); i++)
        this->coefPoliB_[i] &= der.coefPoliB_[i];

    return *this;
  }

  Z& Z::operator|=(const Z& der)
  {
    bool derMenor;
    if( this->coefPoliB_.size() > der.coefPoliB_.size() )
      derMenor = true;
    else // cifras de this <= cifras de der
      derMenor = false;     
    
    if( derMenor ){
      for(int i = 0; i < der.coefPoliB_.size(); i++)
        this->coefPoliB_[i] |= der.coefPoliB_[i];
    }
    else{
      int i;
      for(i = 0; i < this->coefPoliB_.size(); i++)
        this->coefPoliB_[i] |= der.coefPoliB_[i];
      for( ; i < der.coefPoliB_.size(); i++)
        this->coefPoliB_.push_back(der.coefPoliB_[i]);
    }

    return *this;

  } 

  Z& Z::XOR(const Z& der)
  {
    bool derMenor;
    if( this->coefPoliB_.size() > der.coefPoliB_.size() )
      derMenor = true;
    else // cifras de this <= cifras de der
      derMenor = false;     
    
    if( derMenor ){
      for(int i = 0; i < der.coefPoliB_.size(); i++)
        this->coefPoliB_[i] xor_eq der.coefPoliB_[i];
    }
    else{
      int i;
      for(i = 0; i < this->coefPoliB_.size(); i++)
        this->coefPoliB_[i] xor_eq der.coefPoliB_[i];
      for( ; i < der.coefPoliB_.size(); i++)
        this->coefPoliB_.push_back(der.coefPoliB_[i]);
    }

    return *this;

  } 




  Z& Z::cuadrado(void)
  {

    signo_ = 1; //el cuadrado siempre va a tener este efecto
    coefPoliB_ = VectorialCPU::cuadMP(coefPoliB_); 
    return *this;
  }

  Z& Z::cuadradoModular(const Z& mod)
  {

    (*this) %= mod;

    signo_ = 1; //el cuadrado siempre va a tener este efecto
    coefPoliB_ = VectorialCPU::cuadMP(coefPoliB_); 

    (*this) %= mod;

    return *this;
  }
  Z& Z::factorial(void) 
  {
    if( this->coefPoliB_.size() > 1 ){
      throw Errors::TooBig();
    }

    Digit n = coefPoliB_[0];
    Digit m;
    Digit mTemp = 1;
    this->hacerUno();

    unsigned long doses = 0;

    for( ; n > 1; n-- ){
      for( m = n; (m & 0x1) == 0; m >>= 1 ){
        doses++;
      }
      // m is now odd
      
      if( mTemp <= Constants::CIFRA_MAX/m ){
        //mTemp * m fits inside a basic word
        mTemp *= m;
        continue;
      }
      else{
        (*this) *= mTemp;
        mTemp = m;
      }
    }
    if(mTemp > 1) // Hay valores acumulados en la Digit mTemp. Incoporarlos
      (*this) *= mTemp;

    (*this) <<= doses;

    return *this;

  }


  Z& Z::iSquareRoot(void)
  {
    //cohen p 38
    if( (this->esUno()) || (this->esCero()) ){
      return *this; //la parte entera de la raiz cuadrada de 1 es 1 y la de 0 es 0
    }

    const Z n(*this);

    //this method is no more than a Newton iteration.
    //Therefore, the choice of the initial point is basic
    //in order to minimize the number of steps.
    //It suffices that the initial point be > than the
    //integer sqrt. 
    const int e( (this->getBitLength() /2) + 1 );
    this->hacerUno(); 
    (*this) <<= e;

    Z y((*this) + (n/(*this))); 
    y >>= 1;
    while( y < (*this) ){
      (*this) = y;
      y = (*this) + (n/(*this)); 
      y >>= 1;
    }

    return *this;
  }

  bool Z::isPerfectSquare(Z* root) const
  {
    if( root ){
      //se pone inicialmente el valor que tomara el entero "root" de
      //darse el caso de no ser *this un cuadrado perfecto
      root->hacerUno(); root->hacerNegativo(); 
    }

    // Cohen pag. 40
    // Q11, Q63, Q64 y Q65 esta en constantes.h 
    const int t = ((*this)[0] & (64-1));  // equivalent to reduction modulo 64
    const int r = (int)((*this) % (Digit)45045)[0]; // 45045 = 63*65*11

    if (Constants::Q64[t] == false) {
      return false;
    }
    if (Constants::Q63[r % 63] == false)  {
      return false;
    }
    if (Constants::Q65[r % 65] == false) {
      return false;
    }
    if (Constants::Q11[r % 11] == false){
      return false;
    }

    Z sqRoot(*this);
    sqRoot.iSquareRoot();
    if( mpplas::cuadrado(sqRoot) != (*this) ){
      return false;
    }
    else{
      if( root ){
        (*root) = sqRoot;
      }
      return true;
    }

  }


//  Z& Z::operator+=(const double flotante)
//  {
    //TODO
//  }

  Z& Z::operator+=(const SignedDigit corto)
  {


    Digit cortoDigit;
    if( corto >= 0 )
      cortoDigit = (Digit)corto;
    else //corto < 0
      cortoDigit = (Digit)labs(corto);

    if( (signo_ > 0) ){
      if( (corto > 0) ){
        coefPoliB_ = VectorialCPU::sumaMP(coefPoliB_, cortoDigit);
      }
      else{ // corto  < 0
        if( VectorialCPU::mayorque(coefPoliB_, cortoDigit) )
          coefPoliB_ = VectorialCPU::restaMP(coefPoliB_, cortoDigit);
        else{
          coefPoliB_ = VectorialCPU::restaMP(cortoDigit, coefPoliB_);
          signo_ = -1;
        }
      }
    }
    else{ // this < 0
      if( (corto > 0) ){
        // (-a) + b = b - a
        if( VectorialCPU::mayorque(coefPoliB_, cortoDigit) )
          coefPoliB_ = VectorialCPU::restaMP(coefPoliB_, cortoDigit);
        else{
          coefPoliB_ = VectorialCPU::restaMP(cortoDigit, coefPoliB_);
          signo_ = 1;
        }
      }
      else{ // corto < 0
        coefPoliB_ = VectorialCPU::sumaMP(coefPoliB_, cortoDigit);
        //mantener el signo "-"
      }
    }

    return *this;

  }


  Z& Z::operator-=(const SignedDigit corto)
  {


    Digit cortoDigit;
    if( corto >= 0 )
      cortoDigit = (Digit)corto;
    else //corto < 0
      cortoDigit = (Digit)labs(corto);

    if( (signo_ > 0) ){
      if( (corto > 0) ){
        // a - b
        if(  VectorialCPU::menorque(coefPoliB_, cortoDigit) ){ // a < b 
          coefPoliB_ = VectorialCPU::restaMP(cortoDigit, coefPoliB_);
          signo_ = -1;
        }
        else // b <= a
          coefPoliB_ = VectorialCPU::restaMP(coefPoliB_, cortoDigit);
        // se mantiene el signo +
      }
      else{ // corto  < 0
        // a - (-b) = a + b
        coefPoliB_ = VectorialCPU::sumaMP(coefPoliB_, cortoDigit);
        //se mantiene el signo +
      }
    }
    else{ // this < 0
      if( (corto > 0) ){
        // (-a) - b = -(a + b)
        coefPoliB_ = VectorialCPU::sumaMP(coefPoliB_, cortoDigit);
        // se mantiene el signo -
      }
      else{ // corto < 0
        // (-a) - (-b) = b - a
        if( VectorialCPU::menorque(coefPoliB_, cortoDigit ) ){ // a < b
          coefPoliB_ = VectorialCPU::restaMP(cortoDigit, coefPoliB_);
          signo_ = 1;
        }
        else // b <= a
          coefPoliB_ = VectorialCPU::restaMP( coefPoliB_, cortoDigit );
        // se deja el signo -
      }
    }

    return *this;

  }

  Z& Z::operator*=(const SignedDigit corto)
  {


    Digit cortoDigit;
    if( corto >= 0 )
      cortoDigit = (Digit)corto;
    else //corto < 0
      cortoDigit = (Digit)labs(corto);

    if( (signo_ > 0) ){
      if( (corto > 0) ){
        // a * b
        coefPoliB_ = VectorialCPU::multMP(coefPoliB_, cortoDigit);
        // se mantiene el signo +
      }
      else{ // corto  < 0
        // a * (-b) = -(ab)
        coefPoliB_ = VectorialCPU::multMP(coefPoliB_, cortoDigit);
        signo_ = -1;
      }
    }
    else{ // this < 0
      if( (corto > 0) ){
        // (-a) * b = -(ab)
        coefPoliB_ = VectorialCPU::multMP(coefPoliB_, cortoDigit);
        // se deja el signo -
      }
      else{ // corto < 0
        // (-a) * (-b) = ab
        coefPoliB_ = VectorialCPU::multMP(coefPoliB_, cortoDigit);
        signo_ = 1;
      }
    }

    return *this;

  } 


  Z& Z::operator/=(const SignedDigit corto)
  {
    if( corto == 0 ){
      throw Errors::DivisionPorCero();
    }


    Digit cortoDigit;
    if( corto >= 0 ){
      cortoDigit = (Digit)corto;
    }
    else{ //corto < 0
      cortoDigit = (Digit)labs(corto);
    }

    if( (signo_ > 0) ){
      if( (corto > 0) ){
        // a / b
        coefPoliB_ = (VectorialCPU::divMP(coefPoliB_, cortoDigit)).first;
        // se mantiene el signo +
      }
      else{ // corto  < 0
        // a / (-b) = -(a / b)
        coefPoliB_ = (VectorialCPU::divMP(coefPoliB_, cortoDigit)).first;
        signo_ = -1;
      }
    }
    else{ // this < 0
      if( (corto > 0) ){
        // (-a) / b = -(a / b)
        coefPoliB_ = (VectorialCPU::divMP(coefPoliB_, cortoDigit)).first;
        // se deja el signo -
      }
      else{ // corto < 0
        // (-a) / (-b) = a / b
        coefPoliB_ = (VectorialCPU::divMP(coefPoliB_, cortoDigit)).first;
        signo_ = 1;
      }
    }

    return *this;

  }

  Z& Z::operator%=(const SignedDigit divisorSigned)
  {
    if( divisorSigned == 0 ){
      throw Errors::DivisionPorCero();
    }

    this->operator%=(Z(divisorSigned));

    //  Digit divisor;
    //  if( divisorSigned >= 0 )
    //    divisor = (Digit)divisorSigned;
    //  else
    //    divisor = (Digit)labs(divisorSigned);
    //  
    //  if( divisorSigned > 0){ // divisor > 0
    //    if( signo_ > 0 ){
    //      coefPoliB_ = (VectorialCPU::divMP(coefPoliB_, divisor)).second;
    //      // se mantiene el signo +
    //    }
    //    else{ //signo_ < 0
    //      coefPoliB_ = (VectorialCPU::divMP(coefPoliB_, divisor)).second;
    //      if( !(this->esCero()) )
    //        this->operator+=(divisor); // ajuste por dividendo negativo
    //      signo_ = 1;
    //      //El "floor" de la def del modulo(m,n) = m - (floor(m,n) * n)
    //      //ser�a una unidad menor que la parte entera, ya que ser�a
    //      //negativo. Por tanto, esto es equivalente a:
    //      // modulo(m,n) / n < 0 = modulo(m,-n) + n 
    //      //
    //      // Por otra parte, el modulo siempre tiene el signo del divisor
    //
    //    }
    //  }
    //  else{ // divisor_ < 0
    //    if( signo_ > 0){
    //       coefPoliB_ = (VectorialCPU::divMP(coefPoliB_, divisor)).second;
    //      if( !(this->esCero()) )
    //        this->operator-=(divisor); //ajuste por ser divisor negativo
    //      //El "floor" de la def del modulo(m,n) = m - (floor(m,n) * n)
    //      //ser�a una unidad menor que la parte entera, ya que ser�a
    //      //negativo. Por tanto, esto es equivalente a:
    //      // modulo(m,n) / n < 0 = modulo(m,-n) + n (esto seria una resta,
    //      // recordar que n es < 0 ).
    //      //
    //      // Por otra parte, el modulo siempre tiene el signo del divisor
    //    }
    //    else{ // signo_ < 0
    //      coefPoliB_ = (VectorialCPU::divMP(coefPoliB_, divisor)).second;
    //      signo_ = -1;
    //    }
    //  }
    //  
    return *this;

  }  



  Z& Z::operator&=(const SignedDigit derSigno)
  {
    Digit der = (Digit)labs(derSigno);

    this->coefPoliB_.resize(1,(Digit)0);
    this->coefPoliB_[0] &= der;

    return *this;
  }  

  Z& Z::operator|=(const SignedDigit derSigno)
  {
    Digit der = (Digit)labs(derSigno);

    this->coefPoliB_[0] |= der;

    return *this;
  }  

   Z& Z::XOR(const SignedDigit derSigno)
   {
     Digit der = (Digit)labs(derSigno);

     this->coefPoliB_[0] xor_eq der;

     return *this;
   }  

  

  Z& Z::operator+=(const Digit corto)
  {


    Digit cortoDigit;
    cortoDigit = (Digit)corto;

    if( signo_ > 0 ){
      coefPoliB_ = VectorialCPU::sumaMP(coefPoliB_, cortoDigit);
      return *this;
    }
    else{ // signo_ < 0
      if( VectorialCPU::mayorque(coefPoliB_, cortoDigit) )
        coefPoliB_ = VectorialCPU::restaMP(coefPoliB_, cortoDigit);
      else{
        coefPoliB_ = VectorialCPU::restaMP(cortoDigit, coefPoliB_);
        signo_ = 1;
      }
      return *this;
    }
  }
  Z& Z::operator-=(const Digit corto)
  {
    Digit cortoDigit;
    cortoDigit = (Digit)corto;


    if( signo_ > 0 ){ // a - b
      if(  VectorialCPU::menorque(coefPoliB_, cortoDigit) ){ // a < b 
        coefPoliB_ = VectorialCPU::restaMP(cortoDigit, coefPoliB_);
        signo_ = -1;
      }
      else // b <= a
        coefPoliB_ = VectorialCPU::restaMP(coefPoliB_, cortoDigit);
      // se mantiene el signo +
      return *this;
    }
    else{ //signo_ < 0 
      coefPoliB_ = VectorialCPU::sumaMP(coefPoliB_, cortoDigit);
      // se mantiene el signo -
      return *this;
    }
  }

  Z& Z::operator*=(const Digit corto)
  {


    Digit cortoDigit;
    cortoDigit = (Digit)corto;

    if( signo_ > 0 ){ // a * b
      coefPoliB_ = VectorialCPU::multMP(coefPoliB_, cortoDigit);
      // se mantiene el signo +
      return *this;
    }
    else{ //signo_< 0
      // (-a) * b = -(ab)
      coefPoliB_ = VectorialCPU::multMP(coefPoliB_, cortoDigit);
      // se deja el signo -
      return *this;
    }
  } 


  Z& Z::operator/=(const Digit corto)
  {
    if( corto == 0 )
      throw Errors::DivisionPorCero();



    Digit cortoDigit;
    cortoDigit = (Digit)corto;

    if( signo_ > 0 ){ // a / b
      coefPoliB_ = (VectorialCPU::divMP(coefPoliB_, cortoDigit)).first;
      // se mantiene el signo +
      return *this;
    }
    else{ //signo_ < 0
      // (-a) / b = -(a / b)
      coefPoliB_ = (VectorialCPU::divMP(coefPoliB_, cortoDigit)).first;
      // se deja el signo -
      return *this;
    }
  }

  Z& Z::operator%=(const Digit corto)
  {
    if( corto == 0 )
      throw Errors::DivisionPorCero();

    this->operator%=(Z(corto));

    //  Digit cortoDigit;
    //  cortoDigit = (Digit)corto;
    //
    //  if( signo_ > 0 ){
    //    coefPoliB_ = (VectorialCPU::divMP(coefPoliB_, cortoDigit)).second;
    //    // se mantiene el signo +
    //  }
    //  else{ //signo_ < 0
    //    coefPoliB_ = (VectorialCPU::divMP(coefPoliB_, cortoDigit)).second;
    //    if( !(this->esCero()) )
    //      this->operator+=(cortoDigit); // ajuste por dividendo negativo
    //    signo_ = 1;
    //    //El "floor" de la def del modulo(m,n) = m - (floor(m,n) * n)
    //    //ser�a una unidad menor que la parte entera, ya que ser�a
    //    //negativo. Por tanto, esto es equivalente a:
    //    // modulo(m,n) / n < 0 = modulo(m,-n) + n 
    //    //
    //    // Por otra parte, el modulo siempre tiene el signo del divisor
    //  }
    //
    return *this;
  }  


  Z& Z::operator&=(const Digit der)
  {
    this->coefPoliB_.resize(1,(Digit)0);
    this->coefPoliB_[0] &= der;

    return *this;
  }  

  Z& Z::operator|=(const Digit der)
  {
    this->coefPoliB_[0] |= der;

    return *this;
  }  

  Z& Z::XOR(const Digit der)
  {
    this->coefPoliB_[0] xor_eq der;

    return *this;
  }  

  

  Z& Z::operator^=(const Digit e) {
    if( e == 2 ){
      this->cuadrado();
    }
    else{
      MethodsFactory& funcs = MethodsFactory::getReference();
      Exponentiation<Z>* p; funcs.getFunc(p);
      p->exponentiation(this, e);
    }

    return *this; 

  }

  Z& Z::operator^=(const Z& exp)
  {
    if( exp.longitud() > 1 ){
      throw Errors::TooBig();
    }

    Digit exponente = exp[0];

    return operator^=(exponente);
  }

  Z& Z::operator^=(const SignedDigit exp)
  {
    if( exp < 0 ){
      throw Errors::ExponenteNegativo();
    }

    return operator^=((Digit)labs(exp));
  }


  Z& Z::operator>>=(const int desp)
  {

    VectorialCPU::rShift(coefPoliB_, desp);
    return *this;
  }

  Z& Z::operator<<=(const int desp)
  {

    VectorialCPU::lShift(coefPoliB_, desp);
    return *this;
  }


  Z& Z::operator++(void) {
    if( esCero() ){
      hacerUno();
      return *this;
    }

    if(signo_ > 0){
      if(coefPoliB_[0] < Constants::CIFRA_MAX){
        coefPoliB_[0]++;
      }
      else{ //habria acarreo, hacerlo de forma "standard"
        coefPoliB_ = VectorialCPU::sumaMP(coefPoliB_, (Digit)1);
      }
    }
    else{ //signo_ < 0
      if(coefPoliB_[0] > 0){
        coefPoliB_[0]--;
      }
      else { //habria acarreo, hacerlo de forma "standard"
        coefPoliB_ = VectorialCPU::restaMP(coefPoliB_, (Digit)1);
      }
    }

    return *this;
  }

  Z& Z::operator++(int) {
    if( esCero() ){
      hacerUno();
      return *this;
    }


    if(signo_ > 0){
      if(coefPoliB_[0] < Constants::CIFRA_MAX){
        coefPoliB_[0]++;
      }
      else{ //habria acarreo, hacerlo de forma "standard"
        coefPoliB_ = VectorialCPU::sumaMP(coefPoliB_, (Digit)1);
      }
    }
    else{ //signo_ < 0
      if(coefPoliB_[0] > 0){
        coefPoliB_[0]--;
      }
      else { //habria acarreo, hacerlo de forma "standard"
        coefPoliB_ = VectorialCPU::restaMP(coefPoliB_, (Digit)1);
      }
    }


    return *this;
  }

  Z& Z::operator--(void)
  {
    if( esCero() ){
      hacerUno();
      signo_ = -1;
      return *this;
    }



    if(signo_ > 0){
      if(coefPoliB_[0] > 0)
        coefPoliB_[0]--;
      else //habria acarreo, hacerlo de forma "standard"
        coefPoliB_ = VectorialCPU::restaMP(coefPoliB_, (Digit)1);
    }
    else{ //signo_ < 0
      if(coefPoliB_[0] < Constants::CIFRA_MAX)
        coefPoliB_[0]++;
      else //habria acarreo, hacerlo de forma "standard"
        coefPoliB_ = VectorialCPU::sumaMP(coefPoliB_, (Digit)1);
    }


    return *this;
  }

  Z& Z::operator--(int){
    if( esCero() ){
      hacerUno();
      signo_ = -1;
      return *this;
    }

    if(signo_ > 0){
      if(coefPoliB_[0] > 0)
        coefPoliB_[0]--;
      else //habria acarreo, hacerlo de forma "standard"
        coefPoliB_ = VectorialCPU::restaMP(coefPoliB_, (Digit)1);
    }
    else{ //signo_ < 0
      if(coefPoliB_[0] < Constants::CIFRA_MAX)
        coefPoliB_[0]++;
      else //habria acarreo, hacerlo de forma "standard"
        coefPoliB_ = VectorialCPU::sumaMP(coefPoliB_, (Digit)1);
    }


    return *this;
  }

  int Z::getBitLength(void) const {
    const int componentes = coefPoliB_.size() - 1;
    return (( Constants::BITS_EN_CIFRA * componentes) + VectorialCPU::getBitLength(coefPoliB_[componentes]));
  }
 
  int Z::getBase10Length(void) const {
    return (int)floor(this->getBitLength() * Constants::LOG_10_2);
  }


  SignedDigit Z::redondear(int exceso) 
  {

    return VectorialCPU::redondear(coefPoliB_, exceso, signo_);
  }

  Z& Z::hacerCero(void)
  {
    coefPoliB_.clear();
    coefPoliB_.push_back(0);

    signo_ = 1;
    return *this;
  }

  Z& Z::hacerUno(void)
  {
    coefPoliB_.clear();
    coefPoliB_.push_back(1);

    signo_ = 1;
    return *this;
  }

  bool Z::esCero(void) const
  {
    if( coefPoliB_.size() > 1 ){
      return false;
    }

    if( coefPoliB_[0] != 0 ){
      return false;
    }

    return true;
  }

  bool Z::esUno(void) const
  {
    if( coefPoliB_.size() > 1 )
      return false;

    if( coefPoliB_[0] != 1 )
      return false;

    if( signo_ != 1 )
      return false;

    return true;
  }

  void Z::limpiarCeros(void)
  {


    VectorialCPU::limpiarCeros(coefPoliB_);
    if( (coefPoliB_.size() == 1) && (coefPoliB_[0] == 0) )
      signo_ = 1; //POR CO 0NVENIO
    return;
  }


  int Z::numDoses(void) const
  {
    if ( this->esImpar() ){
      return 0;
    }

    Z temp(*this);
    int doses = 0;

    while( temp.esPar() ){
      if( !(temp.coefPoliB_[0] & 0x3) ){ //dos ultimos bits 0 ( ...00 )
        doses += 2;
        temp >>= 2;
      }
      else{
        doses++;
        temp >>= 1;
        break; // ya que si hemos entrado aqui es porque el n� es de la forma
        // ...10 , que tras el >>= 1 ser� ....1
      }
    }

    return doses;
  }

  Z& Z::abs(void) 
  {
    this->hacerPositivo();
    return *this; 
  }
  Z abs(Z num) 
  {
    num.hacerPositivo();
    return num; 
  }


  bool Z::esPotenciaPrima(Z* primo)
  {
    //cohen p 42
    Z p,q;
    Z a;
    TestPrimoProb* primTest; 
    MethodsFactory::getReference().getFunc(primTest);
    
    if( this->esPar() ){
      p = Z((Digit)2);
    }
    else{
      q = (*this);
      while(true){
        if(primTest->esPrimo(q, &a)){
          p = q;
          break;
        }
        else{
          const Z d(Z::gcd((a^q)-a,q));
          if( d.esUno() || (d == q) ){
            primo->hacerCero();
            return false;
          }
          else{
            q = d;
          }
        }
      }
    }
    Z r;
    Z n(*this);
    do{
      divMod(n,p,&n,&r);
    } while( (r.esCero()) && (!n.esUno()) );
    if(n.esUno()){
      (*primo) = p;
      return true;
    }
    else{
      primo->hacerCero();
      return false;
    }
  }
        
      

  Z Z::getRightshiftedBits(const int n) {
    assert( n <= this->getBitLength() );
    const int bitPos = n;
    const int digitPos =  bitPos >> Constants::LOG_2_BITS_EN_CIFRA;
    const int inDigitPos = ( bitPos & Constants::DIGIT_MOD_MASK );
    const Digit inDigitPosMask = ((Digit)1 << inDigitPos)-1;

    Z res;
    res.coefPoliB_.clear();
    res.coefPoliB_.insert(res.coefPoliB_.end(), this->coefPoliB_.begin(), this->coefPoliB_.begin()+digitPos);
    const Digit lastDigit = *(this->coefPoliB_.begin()+digitPos) & inDigitPosMask;
    res.coefPoliB_.push_back(lastDigit);
    
    (*this) >>= n;

    return res;
  }

    
      

  
  Z& Z::divisionBase(const int n)
  {
    if( coefPoliB_.size() > n ){
      coefPoliB_.erase(coefPoliB_.begin(), coefPoliB_.begin()+n);
    }
    else{
      hacerCero();
    }
    return *this;
  }

  Z& Z::moduloBase(const int n)
  {
    coefPoliB_.resize(n);
    limpiarCeros();

    return *this;
  }

  Z& Z::powerOfTwo(const int n){
    const int digits = n >> Constants::LOG_2_BITS_EN_CIFRA;

    //has to be a Digit because it's a index that can have bits
    //up to the Digit's bitlength
    const Digit inDigitPosMask((Digit)1 << ( n & Constants::DIGIT_MOD_MASK ));

    this->coefPoliB_.clear();
    this->coefPoliB_.resize(digits+1,(Digit)0);
    this->coefPoliB_[digits] |= inDigitPosMask;

    return *this;
  }



  Z& Z::potenciaBase(const int n)
  {
//    coefPoliB_.clear();
//    coefPoliB_.resize(n+1,0); 
//    coefPoliB_[n] = 1;
    if( this->esCero() ){
      this->hacerUno();
    };
    coefPoliB_.insert(coefPoliB_.begin(), n, (Digit)0);
    
    return *this;
  }



  Digit Z::getBitsInADigit(const int ini) const {
    if( ini+Constants::BITS_EN_CIFRA > this->getBitLength() ){
      return 0;
    }
    Digit res;
    // digitPos = ini / BITS_EN_CIFRA
    const int digitPos(ini >> Constants::LOG_2_BITS_EN_CIFRA);
    // inDigitShift = ini % BITS_IN_DIGIT
    const int inDigitShift(ini & Constants::DIGIT_MOD_MASK);
    Digit inDigitMask( ~((((Digit)1) << ( inDigitShift )) -1));
    res = (coefPoliB_[digitPos] & inDigitMask) >> inDigitShift;
    inDigitMask = ~inDigitMask;
    if( inDigitMask ){
      res |= ((coefPoliB_[digitPos+1] & inDigitMask) << ( Constants::BITS_EN_CIFRA - inDigitShift));
    }

    return res;
  }


Z& Z::fromString(const std::string& str){

    std::istringstream inStream(str);
    operator>>(inStream,*this);

    return *this;
}



  std::string Z::toString(void) const {
    std::ostringstream oss;
    oss << *this;

    return oss.str().c_str();
  }

  std::string Z::toHRString(void) const {
    return this->toString();
  }

  Z Z::gcd(const Z& u, const Z& v, Z* const s, Z* const t){
    if( s && t ){
      GCDExt<Z>* gcdext;
      MethodsFactory::getReference().getFunc(gcdext);
      return gcdext->gcdext(u,v,s,t);
    }
    else{
      GCD<Z>* gcd;
      MethodsFactory::getReference().getFunc(gcd);
      return gcd->gcd(u,v);
    }
  }





  /******************************/
  std::ostream& 
    operator<<(std::ostream& out, Z num) 
    {
      std::stack<Digit> pila;  
      Digit resto;
      std::ostringstream oss;

      //we assume 0 has always + sign
      if( (num.signo_ < 0) && (!num.esCero()) ){
        oss << "-";
        num.hacerPositivo();
      }
      else{
        const std::ios_base::fmtflags ff(out.flags());
        if( ff & std::ios_base::showpos ){
          oss << "+";
        }
      }


      if( Z::precisionSalida_ == 0){ //sin limitacion
        while( num.longitud() > 1 ){
          resto = (num % Constants::MAX_BASE10_POWER_DIGIT)[0]; 
          num /= Constants::MAX_BASE10_POWER_DIGIT; 
          pila.push(resto);
        }

        //"num" es ahora la primera cifra del n� en base 10^{Constants::MAX_EXP10_CIFRA}
        
        oss << num[0];

        while( !pila.empty() ){
          oss << std::setfill('0') << std::setw(Constants::MAX_EXP10_CIFRA) <<  pila.top();
          pila.pop();
        }
      }
      else{ //precisionSalida_ > 0 ==> limitacion
        int digitos10 = (int)ceil(num.getBitLength() * Constants::LOG_10_2);
        int digitos10Mostrados = 0;

        if(num.esCero()){
          oss << "0";
        }
        else{
          const Digit ten(10);
          while( !num.esCero() ){
            resto = (num % ten)[0]; 
            num /= ten; 
            pila.push(resto);
            //      digitos10++;
          }
          if( Z::precisionSalida_ < digitos10 )
            //si se sacan menos digitos de los que hay...
            oss << "~" ;

          //"num" es ahora la primera cifra del n� en base 10
          //    oss << num[0];
          //    digitos10Mostrados++;
          while( (!pila.empty()) && (digitos10Mostrados < Z::precisionSalida_) ){
            oss  << pila.top();
            pila.pop();
            digitos10Mostrados++;
          }
          if( !pila.empty() ) //hemos salido por precision
            oss << "e" << (digitos10 - digitos10Mostrados);
        }
      }


      /*
       * mientras( numero_grande > 0 ){
       *  r = DividirYDevolverResto(numero_grande, numero_grande, digitos_en_tipo_de_B);
       *  apilar(r)
       * }
       *
       *
       * -----------------
       * |               | primeros digitos del n�      (MSG) -> most sig. "group"
       * -----------------
       * |               | segundo grupo de digitos
       * -----------------
       *      ...
       * -----------------
       * |               | ultimos digitos              (LSG) -> least sig. "group"
       * -----------------
       * 
       * mientras(haya elementos en la pila){
       *  desapilar y sacar por cout n� a n� (ir convirtiendo 
       *  cada cifra del n� a caracter (utilizando % 10 sobre el n� 
       *  seguido de un d /= 10 ) )
       * } 
       *
       * TODO: david tio tu eres tonto... ES SACAR EL VECTOR AL REVESSSSSS
       * directamente, sin estas milongas, usando iteradores. Solo hay q
       * tener el cuenta si el n� es + o -
       * TODO 2: si, es verdad, eres mongol. Y la base gallo? Esa mierda
       * de ahi arriba solo vale cuando estas en una base q sea potencia
       * de diez. Cada dia me das mas asco joder
       * 
       */
      out << oss.str();
      return out;
    }

  
  void _parseNumber( std::istream &in, Z& res ){
    char c;
    Digit n = 0;
    int numDigits = 0;
    res.hacerCero();

    while( in.get(c) ) {
      if( std::isdigit(c) ) {
        n *= 10;
        ++numDigits;
        n += c - '0';  
        if( numDigits >= Constants::MAX_EXP10_CIFRA ){ //shouldn't ever be >
          //put into the number to return
          res *= Constants::MAX_BASE10_POWER_DIGIT;
          res += n;
          n = numDigits = 0;
        }
      }
      else{ //not a digit
        in.putback(c);
        //we have to flush what we might have read so far
        break;
      }
    } //while

    if( numDigits > 0 ){ //still sth to process: flush it
      res *= (Digit)pow(10.0,numDigits);
      res += n;
    }
  
    return;
  }


  std::istream& 
    operator>>(std::istream& in, Z& numero) 
    {
      bool negative = false;
      char c;

      in >> c;

      if( c == '-' ){
        negative = true;
      }
      else if (c == '+' ){
        ;
      }
      else{
        in.putback(c);
      }

      _parseNumber(in, numero);

      if( negative ){
        numero.cambiarSigno();
      }

      return in;
    }



  Z operator+(Z izq, const Z& der)
  {
    izq += der;

    return izq;
  }

  Z operator-(Z izq, const Z& der)
  {
    izq -= der;

    return izq;
  } 

  Z operator*(Z izq, const Z& der)
  {
    izq *= der;

    return izq;
  }

  Z operator/(Z izq, const Z& der)
  {
    if( der.esCero() )
      throw Errors::DivisionPorCero();

    izq /= der;

    return izq;
  }

  Z operator%(Z izq, const Z& der)
  {
    if( der.esCero() )
      throw Errors::DivisionPorCero();

    izq %= der;

    return izq;
  }

  Z operator&(Z izq, const Z& der)
  {
    izq &= der;
    return izq;
  }
  
  Z operator|(Z izq, const Z& der)
  {
    izq |= der;
    return izq;
  }

  Z XOR(Z izq, const Z& der)
  {
    izq.XOR(der);
    return izq;
  }


  
  Z operator>>(Z num, const int desp)
  {
    num >>= desp;
    return num;
  }

  Z operator<<(Z num, const int desp)
  {
    num <<= desp;
    return num;
  }


  /* ahora operaciones con longs implicados */
  Z operator+(const SignedDigit corto, Z largo)
  {
    largo += corto;
    return largo;
  }

  Z operator-(const SignedDigit corto, Z largo)
  {
    largo -= corto;
    largo.cambiarSigno();
    return largo;
  }

  Z operator*(const SignedDigit corto, Z largo)
  {
    largo *= corto;
    return largo;
  }

  Z operator/(const SignedDigit corto, const Z& largo)
  {
    if( largo.esCero() )
      throw Errors::DivisionPorCero();

    return ( Z(corto) / largo );

    //  if( largo > corto) {
    //    Z cero;
    //    cero.hacerCero();
    //    return cero;
    //  }
    //  else 
    //  if( largo < corto ){
    //    Z cociente = Z::convertir((Digit)labs(corto) / largo[0]); 
    //    //if( corto < 0 ) // => largo tb sera negativo, asi q cociente positivo FIXME: PROBAR TO ESTO
    //    if( corto >= 0) 
    //      if( largo.isNegative() )
    //        cociente.hacerNegativo();
    //      
    //    return cociente;
    //  }
    //  else{ //iguales
    //    Z uno;
    //    uno.hacerUno();
    //    return uno;
    //  }
  }

  Z operator%(const SignedDigit corto, const Z& largo)
  {
    if( largo.esCero() )
      throw Errors::DivisionPorCero();

    return( (Z(corto) % largo ) );
  }

  Z operator&(const SignedDigit corto, Z largo)
  {
    largo &= corto;
    return largo;
  }
  Z operator|(const SignedDigit corto, Z largo)
  {
    largo |= corto;
    return largo;
  }
  Z XOR(const SignedDigit corto, Z largo)
  {
    largo.XOR(corto);
    return largo;
  }


  Z operator+(Z largo, const SignedDigit corto)
  {
    largo += corto;
    return largo;
  }
  Z operator-(Z largo, const SignedDigit corto)
  {
    largo -= corto;
    return largo;
  }
  Z operator*(Z largo, const SignedDigit corto)
  {
    largo *= corto;
    return largo;
  }
  Z operator/(Z largo, const SignedDigit corto)
  {
    if( corto == 0 )
      throw Errors::DivisionPorCero();

    largo /= corto;
    return largo;
  }
  Z operator%(Z largo, const SignedDigit corto)
  {
    if( corto == 0 )
      throw Errors::DivisionPorCero();

    largo %= corto;
    return largo;
  }
  Z operator&(Z largo, const SignedDigit corto)
  {
    largo &= corto;
    return largo;
  }
  Z operator|(Z largo, const SignedDigit corto)
  {
    largo |= corto;
    return largo;
  }
  Z XOR(Z largo, const SignedDigit corto)
  {
    largo.XOR(corto);
    return largo;
  }



  Z operator+(const Digit corto, Z largo)
  {
    largo += corto;
    return largo;
  }

  Z operator-(const Digit corto, Z largo)
  {
    largo -= corto;
    largo.cambiarSigno();
    return largo;
  }

  Z operator*(const Digit corto, Z largo)
  {
    largo *= corto;
    return largo;
  }

  Z operator/(const Digit corto, const Z& largo)
  {
    if( largo.esCero() )
      throw Errors::DivisionPorCero();

    if( largo > corto) {
      Z cero;
      cero.hacerCero();
      return cero;
    }
    else 
      if( largo < corto ){
        return Z(corto / (largo[0]));
      }
      else{ //iguales
        Z uno;
        uno.hacerUno();
        return uno;
      }
  }

  Z operator%(const Digit corto, const Z& largo)
  {
    if( largo.esCero() )
      throw Errors::DivisionPorCero();

    if( largo > corto ){
      return Z(corto);
    }
    else 
      if( largo < corto ){
        return Z(corto % (largo[0]));
      }
      else{ //iguales
        Z cero;
        cero.hacerCero();
        return cero;
      }
  }
  Z operator&(const Digit corto, Z largo)
  {
    largo &= corto;
    return largo;
  }
  Z operator|(const Digit corto, Z largo)
  {
    largo |= corto;
    return largo;
  }
  Z XOR(const Digit corto, Z largo)
  {
    largo.XOR(corto);
    return largo;
  }


  

  Z operator+(Z largo, const Digit corto)
  {
    largo += corto;
    return largo;
  }
  Z operator-(Z largo, const Digit corto)
  {
    largo -= corto;
    return largo;
  }
  Z operator*(Z largo, const Digit corto)
  {
    largo *= corto;
    return largo;
  }
  Z operator/(Z largo, const Digit corto)
  {
    if( corto == 0 )
      throw Errors::DivisionPorCero();

    largo /= corto;
    return largo;
  }
  Z operator%(Z largo, const Digit corto)
  {
    if( corto == 0 )
      throw Errors::DivisionPorCero();

    largo %= corto;
    return largo;
  }
  Z operator&(Z largo, const Digit corto)
  {
    largo &= corto;
    return largo;
  }
  Z operator|(Z largo, const Digit corto)
  {
    largo |= corto;
    return largo;
  }
  Z XOR(Z largo, const Digit corto)
  {
    largo.XOR(corto);
    return largo;
  }





  /* comparacion */
  bool operator<(const SignedDigit corto, const Z& largo)
  {
    if( (largo < corto) || (largo == corto) )
      return false;
    else 
      return true;
  }

  bool operator>(const SignedDigit corto, const Z& largo)
  {
    if( (largo > corto) || (largo == corto) )
      return false;
    else 
      return true;
  }

  bool operator<=(const SignedDigit corto, const Z& largo)
  {
    if( (largo < corto) )
      return false;
    else 
      return true;
  }

  bool operator>=(const SignedDigit corto, const Z& largo)
  {
    if( (largo > corto) )
      return false;
    else 
      return true;
  }

  bool operator==(const SignedDigit corto, const Z& largo)
  {
    if( (largo == corto) )
      return true;
    else 
      return false;
  }

  bool operator!=(const SignedDigit corto, const Z& largo)
  {
    if( (largo != corto) )
      return true;
    else 
      return false;
  }




  bool operator<(const Digit corto, const Z& largo)
  {
    if( (largo < corto) || (largo == corto) )
      return false;
    else 
      return true;
  }

  bool operator>(const Digit corto, const Z& largo)
  {
    if( (largo > corto) || (largo == corto) )
      return false;
    else 
      return true;
  }

  bool operator<=(const Digit corto, const Z& largo)
  {
    if( (largo < corto) )
      return false;
    else 
      return true;
  }

  bool operator>=(const Digit corto, const Z& largo)
  {
    if( (largo > corto) )
      return false;
    else 
      return true;
  }

  bool operator==(const Digit corto, const Z& largo)
  {
    if( (largo == corto) )
      return true;
    else 
      return false;
  }

  bool operator!=(const Digit corto, const Z& largo)
  {
    if( (largo != corto) )
      return true;
    else 
      return false;
  }


  /* operator - unario */
  Z operator-(Z entero)
  {
    entero.cambiarSigno();
    return entero;
  }

  Z operator^(Z base, const Z& exp)
  {
    if( exp.longitud() > 1 )
      throw Errors::TooBig();

    base ^= exp;
    return base;
  }

  Z operator^(Z base, const Digit exp)
  {
    base ^= exp;
    return base;
  }

  Z operator^(Z base, const SignedDigit exp)
  {
    if( exp < 0 ){
      throw Errors::ExponenteNegativo();
    }

    base ^= ((Digit)labs(exp));
    return base;
  }





  void divMod(const Z& dividendo, const Z& divisor, Z* cociente, Z* resto)
    throw (Errors::DivisionPorCero)
    {

      if( divisor.esCero() )
        throw Errors::DivisionPorCero();

      //por precaucion, no sea que se hayan pasado cosas ya trajinadas
      cociente->hacerPositivo();
      resto->hacerPositivo();

      std::pair< MiVec<Digit>, MiVec<Digit> > resultados;

      if( divisor.isPositive() ){ 
        if( dividendo.isPositive() ){
          resultados = VectorialCPU::divMP(dividendo.coefPoliB_, divisor.coefPoliB_);

          cociente->coefPoliB_ = resultados.first;

          resto->coefPoliB_ = resultados.second;

        }
        else{ //dividendo < 0
          resultados = VectorialCPU::divMP(dividendo.coefPoliB_, divisor.coefPoliB_);

          cociente->coefPoliB_ = resultados.first;
          cociente->hacerNegativo();

          resto->hacerNegativo();
          resto->coefPoliB_ = resultados.second;
          (*resto )+= divisor; // ajuste por dividendo negativo
          //El "floor" de la def del modulo(m,n) = m - (floor(m,n) * n)
          //ser�a una unidad menor que la parte entera, ya que ser�a
          //negativo. Por tanto, esto es equivalente a:
          // modulo(m,n) / n < 0 = modulo(m,-n) + n 
          //
          // Por otra parte, el modulo siempre tiene el signo del divisor

        }
      }
      else{ // divisor negativo
        if( dividendo.isPositive()){
          resultados = VectorialCPU::divMP(dividendo.coefPoliB_, divisor.coefPoliB_);

          cociente->coefPoliB_ = resultados.first;
          cociente->hacerNegativo();

          resto->coefPoliB_ = resultados.second;
          (*resto) += divisor; //ajuste por ser divisor negativo
          //El "floor" de la def del modulo(m,n) = m - (floor(m,n) * n)
          //ser�a una unidad menor que la parte entera, ya que ser�a
          //negativo. Por tanto, esto es equivalente a:
          // modulo(m,n) / n < 0 = modulo(m,-n) + n (esto seria una resta,
          // recordar que n es < 0 ).
          //
          // Por otra parte, el modulo siempre tiene el signo del divisor
        }
        else{ // dividendo negativo
          resultados = VectorialCPU::divMP(dividendo.coefPoliB_, divisor.coefPoliB_);

          cociente->coefPoliB_ = resultados.first;

          resto->coefPoliB_ = resultados.second;
          resto->hacerNegativo();
        }
      }

      return;
    }

  void divMod(const Z& dividendo, const SignedDigit divisor, Z* cociente, Z* resto)
    throw (Errors::DivisionPorCero)
    {

      bool divisorPositivo;
      Digit divisorDigit;

      if( divisor == 0 )
        throw Errors::DivisionPorCero();

      if( divisor < 0 ){
        divisorPositivo = false;
        divisorDigit = (Digit)labs(divisor);
      }
      else{
        divisorPositivo = true;
        divisorDigit = (Digit)divisor;
      }

      //por precaucion, no sea que se hayan pasado cosas ya trajinadas
      cociente->hacerPositivo();
      resto->hacerPositivo();

      std::pair< MiVec<Digit>, MiVec<Digit> > resultados;

      if( divisorPositivo ){ 
        if( dividendo.isPositive() ){
          resultados = VectorialCPU::divMP(dividendo.coefPoliB_, divisorDigit);

          cociente->coefPoliB_ = resultados.first;

          resto->coefPoliB_ = resultados.second;

        }
        else{ //dividendo < 0
          resultados = VectorialCPU::divMP(dividendo.coefPoliB_, divisorDigit);

          cociente->coefPoliB_ = resultados.first;
          cociente->hacerNegativo();

          resto->hacerNegativo();
          resto->coefPoliB_ = resultados.second;
          (*resto) += divisor; // ajuste por dividendo negativo
          //El "floor" de la def del modulo(m,n) = m - (floor(m,n) * n)
          //ser�a una unidad menor que la parte entera, ya que ser�a
          //negativo. Por tanto, esto es equivalente a:
          // modulo(m,n) / n < 0 = modulo(m,-n) + n 
          //
          // Por otra parte, el modulo siempre tiene el signo del divisor

        }
      }
      else{ // divisor negativo
        if( dividendo.isPositive()){
          resultados = VectorialCPU::divMP(dividendo.coefPoliB_, divisorDigit);

          cociente->coefPoliB_ = resultados.first;
          cociente->hacerNegativo();

          resto->coefPoliB_ = resultados.second;
          (*resto) += divisor; //ajuste por ser divisor negativo
          //El "floor" de la def del modulo(m,n) = m - (floor(m,n) * n)
          //ser�a una unidad menor que la parte entera, ya que ser�a
          //negativo. Por tanto, esto es equivalente a:
          // modulo(m,n) / n < 0 = modulo(m,-n) + n (esto seria una resta,
          // recordar que n es < 0 ).
          //
          // Por otra parte, el modulo siempre tiene el signo del divisor
        }
        else{ // dividendo negativo
          resultados = VectorialCPU::divMP(dividendo.coefPoliB_, divisorDigit);

          cociente->coefPoliB_ = resultados.first;

          resto->coefPoliB_ = resultados.second[0];
          resto->hacerNegativo();
        }
      }

      return;
    }


  void divMod(const Z& dividendo, const Digit divisor, Z* cociente, Z* resto)
    throw (Errors::DivisionPorCero)
    {


      if( divisor == 0 )
        throw Errors::DivisionPorCero();

      //por precaucion, no sea que se hayan pasado cosas ya trajinadas
      cociente->hacerPositivo();
      resto->hacerPositivo();

      std::pair< MiVec<Digit>, MiVec<Digit> > resultados;

      if( dividendo.isPositive() ){
        resultados = VectorialCPU::divMP(dividendo.coefPoliB_, divisor);

        cociente->coefPoliB_ = resultados.first;

        resto->coefPoliB_ = resultados.second;

      }
      else{ //dividendo < 0
        resultados = VectorialCPU::divMP(dividendo.coefPoliB_, divisor);

        cociente->coefPoliB_ = resultados.first;
        cociente->hacerNegativo();

        resto->hacerNegativo();
        resto->coefPoliB_ = resultados.second;
        (*resto) += divisor; // ajuste por dividendo negativo
        //El "floor" de la def del modulo(m,n) = m - (floor(m,n) * n)
        //ser�a una unidad menor que la parte entera, ya que ser�a
        //negativo. Por tanto, esto es equivalente a:
        // modulo(m,n) / n < 0 = modulo(m,-n) + n 
        //
        // Por otra parte, el modulo siempre tiene el signo del divisor

      }

      return;
    }


  Z cuadrado(Z x)
  {
    x.cuadrado();
    return x;
  }
  Z cuadradoModular(Z x, const Z& mod)
  {
    x.cuadradoModular(mod);
    return x;
  }
  Z factorial(Z x)
  {
    x.factorial();
    return x;
  }


  Z iSquareRoot(Z x)
  {
    x.iSquareRoot();
    return x;
  }

  Digit iSquareRoot(Digit x)
  {
    if( (x == 1) || (x == 0 ) )
      return x;

    Digit n = (x >> 1);
    Digit y;

    y = (n + (x/n)) >> 1;

    while( y < n ){
      n = y;
      y = (n + (x/n)) >> 1;
    }

    // y >= x
    return n;
  } 

  bool isPerfectSquare(const Z& x)
  {
    return x.isPerfectSquare();
  }

  int getBitLength(const Z& x)
  {
    return x.getBitLength();
  }
  int getBitLength(const Digit x)
  {
    return VectorialCPU::getBitLength(x);
  }
  int getBitLength(const SignedDigit x)
  {
    return VectorialCPU::getBitLength((Digit)labs(x));
  }

  int getBase10Length(const Z& x){
    return x.getBase10Length();
  }
  int getBase10Length(const Digit x){
    return (int)floor(Constants::LOG_10_2 * getBitLength(x));
  }
  int getBase10Length(const SignedDigit x){
    return (int)floor(Constants::LOG_10_2 * getBitLength(x));
  }

}
