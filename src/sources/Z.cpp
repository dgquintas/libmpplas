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
#include "Funciones.h"
#include "mp.h"
#include "Potencia.h"
#include "Primos.h"
#include "GCD.h"

namespace mpplas{

  size_t Z::precisionSalida_ = 0;

  Z Z::Zero((Digit)0);

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
    size_t inicio = cadena.find_first_of('.');
    cadena.erase(inicio);

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
        return vCPUVectorial::mayorque(coefPoliB_,der.coefPoliB_);
      else // der < 0
        return true;
    }
    else{ // this < 0
      if( (der.signo_ > 0) )
        return false;
      else // der < 0
        return vCPUVectorial::menorque(coefPoliB_, der.coefPoliB_);
    }
  }

  bool Z::operator<(const Z& der) const
  {


    if( (signo_ > 0) ){
      if( (der.signo_ > 0) )
        return vCPUVectorial::menorque(coefPoliB_,der.coefPoliB_);
      else // der < 0
        return false;
    }
    else{ // this < 0
      if( (der.signo_ > 0) )
        return true;
      else // der < 0
        return vCPUVectorial::mayorque(coefPoliB_, der.coefPoliB_);
    }

  }

  bool Z::operator==(const Z& der) const
  {


    if( signo_ == der.signo_ )
      if ( vCPUVectorial::igual(coefPoliB_, der.coefPoliB_) )
        return true;

    return false;
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
        return vCPUVectorial::mayorque( coefPoliB_, (Digit)der );
      else // der < 0
        return true;
    else // signo_ < 0 
      if( der >= 0)
        return false;
      else // der < 0
        // ambos son negativos. Por tanto el mayor ser� el menor
        // en valor absoluto
        return vCPUVectorial::menorque( coefPoliB_, (Digit)labs(der) );
  }  

  bool Z::operator<(const SignedDigit der) const
  {


    if( (signo_ > 0) )
      if(der >= 0)
        return vCPUVectorial::menorque( coefPoliB_, (Digit)der );
      else // der < 0
        return false;
    else // signo_ < 0 
      if( der >= 0)
        return true;
      else // der < 0
        // ambos son negativos. Por tanto el menor ser� el mayor
        // en valor absoluto
        return vCPUVectorial::mayorque( coefPoliB_, (Digit)labs(der) );
  }

  bool Z::operator==(const SignedDigit der) const
  {


    if( (signo_ > 0) )
      if(der >= 0)
        return vCPUVectorial::igual( coefPoliB_, (Digit)der );
      else // der < 0
        return false;
    else // signo_ < 0 
      if( der >= 0)
        return false;
      else // der < 0
        //ambos negativos; ser�n iguales si son iguales en valor
        //absoluto
        return vCPUVectorial::igual( coefPoliB_, (Digit)labs(der) );
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
      return vCPUVectorial::mayorque( coefPoliB_, der );
    else // signo_ < 0 
      return false;
  }  

  bool Z::operator<(const Digit der) const
  {


    if( (signo_ > 0) )
      return vCPUVectorial::menorque( coefPoliB_, der );
    else // signo_ < 0 
      return true;
  }

  bool Z::operator==(const Digit der) const
  {


    if( (signo_ > 0) )
      return vCPUVectorial::igual( coefPoliB_, der );
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
        this->coefPoliB_ = vCPUVectorial::sumaMP(coefPoliB_, sumandoDerecha.coefPoliB_);
        return *this;
      }
      else{ // sumandoDerecha < 0
        if( vCPUVectorial::mayorque(coefPoliB_, sumandoDerecha.coefPoliB_) )
          this->coefPoliB_ = vCPUVectorial::restaMP(coefPoliB_, sumandoDerecha.coefPoliB_);
        else{
          this->coefPoliB_ = vCPUVectorial::restaMP(sumandoDerecha.coefPoliB_, coefPoliB_);
          this->signo_ = -1;
        }
        return *this;
      }
    }
    else{ // this < 0
      if( (sumandoDerecha.signo_ > 0) ){
        // (-a) + b = b - a
        if( vCPUVectorial::mayorque(coefPoliB_,sumandoDerecha.coefPoliB_) )
          this->coefPoliB_ = vCPUVectorial::restaMP(coefPoliB_, sumandoDerecha.coefPoliB_);
        else{
          this->coefPoliB_ = vCPUVectorial::restaMP(sumandoDerecha.coefPoliB_, coefPoliB_);
          this->signo_ = 1;
        }
        return *this;
      }
      else{ // sumandoDerecha < 0
        this->coefPoliB_ = vCPUVectorial::sumaMP(this->coefPoliB_, sumandoDerecha.coefPoliB_);
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
        if( vCPUVectorial::mayorque(sustraendo.coefPoliB_, coefPoliB_) ){ // b > a
          this->coefPoliB_ = vCPUVectorial::restaMP(sustraendo.coefPoliB_, coefPoliB_);
          this->signo_ = -1;
        }
        else // b <= a
          this->coefPoliB_ = vCPUVectorial::restaMP(coefPoliB_, sustraendo.coefPoliB_);
        // se mantiene el signo +
      }
      else{ // sustraendo  < 0
        // a - (-b) = a + b
        this->coefPoliB_ = vCPUVectorial::sumaMP(coefPoliB_, sustraendo.coefPoliB_);
        //se mantiene el signo +
      }
    }
    else{ // this < 0
      if( (sustraendo.signo_ > 0) ){
        // (-a) - b = -(a + b)
        this->coefPoliB_ = vCPUVectorial::sumaMP(coefPoliB_, sustraendo.coefPoliB_);
        // se mantiene el signo -
      }
      else{ // sustraendo < 0
        // (-a) - (-b) = b - a
        if( vCPUVectorial::mayorque(sustraendo.coefPoliB_, coefPoliB_) ){ // b > a
          this->coefPoliB_ = vCPUVectorial::restaMP(sustraendo.coefPoliB_, coefPoliB_);
          this->signo_ = 1;
        }
        else // b <= a
          this->coefPoliB_ = vCPUVectorial::restaMP( coefPoliB_, sustraendo.coefPoliB_ );
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
        this->coefPoliB_ = vCPUVectorial::multMP(coefPoliB_, factorDer.coefPoliB_);
        // se mantiene el signo +
      }
      else{ // factorDer  < 0
        // a * (-b) = -(ab)
        this->coefPoliB_ = vCPUVectorial::multMP(coefPoliB_, factorDer.coefPoliB_);
        this->signo_ = -1;
      }
    }
    else{ // this < 0
      if( (factorDer.signo_ > 0) ){
        // (-a) * b = -(ab)
        this->coefPoliB_ = vCPUVectorial::multMP(coefPoliB_, factorDer.coefPoliB_);
        // se deja el signo -
      }
      else{ // factorDer < 0
        // (-a) * (-b) = ab
        this->coefPoliB_ = vCPUVectorial::multMP(coefPoliB_, factorDer.coefPoliB_);
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
        this->coefPoliB_ = (vCPUVectorial::divMP(coefPoliB_, divisor.coefPoliB_)).first;
        // se mantiene el signo +
      }
      else{ // divisor  < 0
        // a / (-b) = -(a / b)
        this->coefPoliB_ = (vCPUVectorial::divMP(coefPoliB_, divisor.coefPoliB_)).first;
        this->signo_ = -1;
      }
    }
    else{ // this < 0
      if( (divisor.signo_ > 0) ){
        // (-a) / b = -(a / b)
        this->coefPoliB_ = (vCPUVectorial::divMP(coefPoliB_, divisor.coefPoliB_)).first;
        // se deja el signo -
      }
      else{ // divisor < 0
        // (-a) / (-b) = a / b
        this->coefPoliB_ = (vCPUVectorial::divMP(coefPoliB_, divisor.coefPoliB_)).first;
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
        coefPoliB_ = (vCPUVectorial::divMP(coefPoliB_, divisor.coefPoliB_)).second;
        // se mantiene el signo +
      }
      else{ //signo_ < 0
        coefPoliB_ = (vCPUVectorial::divMP(coefPoliB_, divisor.coefPoliB_)).second;
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
        coefPoliB_ = (vCPUVectorial::divMP(coefPoliB_, divisor.coefPoliB_)).second;
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
        coefPoliB_ = (vCPUVectorial::divMP(coefPoliB_, divisor.coefPoliB_)).second;
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
      for(size_t i = 0; i < der.coefPoliB_.size(); i++)
        this->coefPoliB_[i] &= der.coefPoliB_[i];
    }
    else
      for(size_t i = 0; i < this->coefPoliB_.size(); i++)
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
      for(size_t i = 0; i < der.coefPoliB_.size(); i++)
        this->coefPoliB_[i] |= der.coefPoliB_[i];
    }
    else{
      size_t i;
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
      for(size_t i = 0; i < der.coefPoliB_.size(); i++)
        this->coefPoliB_[i] xor_eq der.coefPoliB_[i];
    }
    else{
      size_t i;
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
    coefPoliB_ = vCPUVectorial::cuadMP(coefPoliB_); 
    return *this;
  }

  Z& Z::cuadradoModular(const Z& mod)
  {

    (*this) %= mod;

    signo_ = 1; //el cuadrado siempre va a tener este efecto
    coefPoliB_ = vCPUVectorial::cuadMP(coefPoliB_); 

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


  Z& Z::raizCuadrada(void)
  {
    //cohen p 38
    if( (this->esUno()) || (this->esCero()) )
      return *this; //la parte entera de la raiz cuadrada de 1 es 1 y la de 0 es 0

    // this >= 2 => x/2 >= floor(sqrt(x))
    Z n(*this);
    (*this) >>= 1 ; // x = this / 2 (ver doc.)
    Z y;

    y = (*this) + (n/(*this)); y >>= 1;

    while( y < (*this) ){
      (*this) = y;
      y = (*this) + (n/(*this)); y >>= 1;
    }

    return *this;
  }

  bool Z::esCuadrado(Z* raiz)
  {
    if( raiz ){
      //se pone inicialmente el valor que tomara el entero "raiz" de
      //darse el caso de no ser *this un cuadrado perfecto
      raiz->hacerUno(); raiz->hacerNegativo(); 
    }

    // Cohen pag. 40
    size_t r, t;

    // Q11, Q63, Q64 y Q65 esta en constantes.h 

    t = (size_t)(*this)[0] % 64; // FIXME: hacer el n % 64 con ops de bits
    r = (size_t)(*this)[0] % 45045; // 45045 = 63*65*11

    if (Constants::Q64[t] == false) 
      return false;
    if (Constants::Q63[r % 63] == false)  
      return false;
    if (Constants::Q65[r % 65] == false) 
      return false;
    if (Constants::Q11[r % 11] == false)
      return false;

    Z raizCuad(*this);
    raizCuad.raizCuadrada();
    if( mpplas::cuadrado(raizCuad) != (*this) )
      return false;
    else{
      if( raiz )
        (*raiz) = raizCuad;
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
        coefPoliB_ = vCPUVectorial::sumaMP(coefPoliB_, cortoDigit);
      }
      else{ // corto  < 0
        if( vCPUVectorial::mayorque(coefPoliB_, cortoDigit) )
          coefPoliB_ = vCPUVectorial::restaMP(coefPoliB_, cortoDigit);
        else{
          coefPoliB_ = vCPUVectorial::restaMP(cortoDigit, coefPoliB_);
          signo_ = -1;
        }
      }
    }
    else{ // this < 0
      if( (corto > 0) ){
        // (-a) + b = b - a
        if( vCPUVectorial::mayorque(coefPoliB_, cortoDigit) )
          coefPoliB_ = vCPUVectorial::restaMP(coefPoliB_, cortoDigit);
        else{
          coefPoliB_ = vCPUVectorial::restaMP(cortoDigit, coefPoliB_);
          signo_ = 1;
        }
      }
      else{ // corto < 0
        coefPoliB_ = vCPUVectorial::sumaMP(coefPoliB_, cortoDigit);
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
        if(  vCPUVectorial::menorque(coefPoliB_, cortoDigit) ){ // a < b 
          coefPoliB_ = vCPUVectorial::restaMP(cortoDigit, coefPoliB_);
          signo_ = -1;
        }
        else // b <= a
          coefPoliB_ = vCPUVectorial::restaMP(coefPoliB_, cortoDigit);
        // se mantiene el signo +
      }
      else{ // corto  < 0
        // a - (-b) = a + b
        coefPoliB_ = vCPUVectorial::sumaMP(coefPoliB_, cortoDigit);
        //se mantiene el signo +
      }
    }
    else{ // this < 0
      if( (corto > 0) ){
        // (-a) - b = -(a + b)
        coefPoliB_ = vCPUVectorial::sumaMP(coefPoliB_, cortoDigit);
        // se mantiene el signo -
      }
      else{ // corto < 0
        // (-a) - (-b) = b - a
        if( vCPUVectorial::menorque(coefPoliB_, cortoDigit ) ){ // a < b
          coefPoliB_ = vCPUVectorial::restaMP(cortoDigit, coefPoliB_);
          signo_ = 1;
        }
        else // b <= a
          coefPoliB_ = vCPUVectorial::restaMP( coefPoliB_, cortoDigit );
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
        coefPoliB_ = vCPUVectorial::multMP(coefPoliB_, cortoDigit);
        // se mantiene el signo +
      }
      else{ // corto  < 0
        // a * (-b) = -(ab)
        coefPoliB_ = vCPUVectorial::multMP(coefPoliB_, cortoDigit);
        signo_ = -1;
      }
    }
    else{ // this < 0
      if( (corto > 0) ){
        // (-a) * b = -(ab)
        coefPoliB_ = vCPUVectorial::multMP(coefPoliB_, cortoDigit);
        // se deja el signo -
      }
      else{ // corto < 0
        // (-a) * (-b) = ab
        coefPoliB_ = vCPUVectorial::multMP(coefPoliB_, cortoDigit);
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
        coefPoliB_ = (vCPUVectorial::divMP(coefPoliB_, cortoDigit)).first;
        // se mantiene el signo +
      }
      else{ // corto  < 0
        // a / (-b) = -(a / b)
        coefPoliB_ = (vCPUVectorial::divMP(coefPoliB_, cortoDigit)).first;
        signo_ = -1;
      }
    }
    else{ // this < 0
      if( (corto > 0) ){
        // (-a) / b = -(a / b)
        coefPoliB_ = (vCPUVectorial::divMP(coefPoliB_, cortoDigit)).first;
        // se deja el signo -
      }
      else{ // corto < 0
        // (-a) / (-b) = a / b
        coefPoliB_ = (vCPUVectorial::divMP(coefPoliB_, cortoDigit)).first;
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
    //      coefPoliB_ = (vCPUVectorial::divMP(coefPoliB_, divisor)).second;
    //      // se mantiene el signo +
    //    }
    //    else{ //signo_ < 0
    //      coefPoliB_ = (vCPUVectorial::divMP(coefPoliB_, divisor)).second;
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
    //       coefPoliB_ = (vCPUVectorial::divMP(coefPoliB_, divisor)).second;
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
    //      coefPoliB_ = (vCPUVectorial::divMP(coefPoliB_, divisor)).second;
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
      coefPoliB_ = vCPUVectorial::sumaMP(coefPoliB_, cortoDigit);
      return *this;
    }
    else{ // signo_ < 0
      if( vCPUVectorial::mayorque(coefPoliB_, cortoDigit) )
        coefPoliB_ = vCPUVectorial::restaMP(coefPoliB_, cortoDigit);
      else{
        coefPoliB_ = vCPUVectorial::restaMP(cortoDigit, coefPoliB_);
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
      if(  vCPUVectorial::menorque(coefPoliB_, cortoDigit) ){ // a < b 
        coefPoliB_ = vCPUVectorial::restaMP(cortoDigit, coefPoliB_);
        signo_ = -1;
      }
      else // b <= a
        coefPoliB_ = vCPUVectorial::restaMP(coefPoliB_, cortoDigit);
      // se mantiene el signo +
      return *this;
    }
    else{ //signo_ < 0 
      coefPoliB_ = vCPUVectorial::sumaMP(coefPoliB_, cortoDigit);
      // se mantiene el signo -
      return *this;
    }
  }

  Z& Z::operator*=(const Digit corto)
  {


    Digit cortoDigit;
    cortoDigit = (Digit)corto;

    if( signo_ > 0 ){ // a * b
      coefPoliB_ = vCPUVectorial::multMP(coefPoliB_, cortoDigit);
      // se mantiene el signo +
      return *this;
    }
    else{ //signo_< 0
      // (-a) * b = -(ab)
      coefPoliB_ = vCPUVectorial::multMP(coefPoliB_, cortoDigit);
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
      coefPoliB_ = (vCPUVectorial::divMP(coefPoliB_, cortoDigit)).first;
      // se mantiene el signo +
      return *this;
    }
    else{ //signo_ < 0
      // (-a) / b = -(a / b)
      coefPoliB_ = (vCPUVectorial::divMP(coefPoliB_, cortoDigit)).first;
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
    //    coefPoliB_ = (vCPUVectorial::divMP(coefPoliB_, cortoDigit)).second;
    //    // se mantiene el signo +
    //  }
    //  else{ //signo_ < 0
    //    coefPoliB_ = (vCPUVectorial::divMP(coefPoliB_, cortoDigit)).second;
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

  

  Z& Z::operator^=(const Digit e)
  {
    Funciones *funcs = Funciones::getInstance();
    Potencia* p; funcs->getFunc(p);
    p->potencia(this, e);

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


  Z& Z::operator>>=(const size_t desp)
  {

    vCPUVectorial::rShift(coefPoliB_, desp);
    return *this;
  }

  Z& Z::operator<<=(const size_t desp)
  {

    vCPUVectorial::lShift(coefPoliB_, desp);
    return *this;
  }


  Z& Z::operator++(void)
  {


    if( esCero() ){
      hacerUno();
      return *this;
    }

    if(signo_ > 0){
      if(coefPoliB_[0] < Constants::CIFRA_MAX)
        coefPoliB_[0]++;
      else //habria acarreo, hacerlo de forma "standard"
        coefPoliB_ = vCPUVectorial::sumaMP(coefPoliB_, (Digit)1);
    }
    else{ //signo_ < 0
      if(coefPoliB_[0] > 0)
        coefPoliB_[0]--;
      else //habria acarreo, hacerlo de forma "standard"
        coefPoliB_ = vCPUVectorial::restaMP(coefPoliB_, (Digit)1);
    }


    return *this;
  }

  Z& Z::operator++(int)
  {
    if( esCero() ){
      hacerUno();
      return *this;
    }


    if(signo_ > 0){
      if(coefPoliB_[0] < Constants::CIFRA_MAX)
        coefPoliB_[0]++;
      else //habria acarreo, hacerlo de forma "standard"
        coefPoliB_ = vCPUVectorial::sumaMP(coefPoliB_, (Digit)1);
    }
    else{ //signo_ < 0
      if(coefPoliB_[0] > 0)
        coefPoliB_[0]--;
      else //habria acarreo, hacerlo de forma "standard"
        coefPoliB_ = vCPUVectorial::restaMP(coefPoliB_, (Digit)1);
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
        coefPoliB_ = vCPUVectorial::restaMP(coefPoliB_, (Digit)1);
    }
    else{ //signo_ < 0
      if(coefPoliB_[0] < Constants::CIFRA_MAX)
        coefPoliB_[0]++;
      else //habria acarreo, hacerlo de forma "standard"
        coefPoliB_ = vCPUVectorial::sumaMP(coefPoliB_, (Digit)1);
    }


    return *this;
  }

  Z& Z::operator--(int)
  {
    assert(coefPoliB_.size() >= 1 ); //FIXME
    if( esCero() ){
      hacerUno();
      signo_ = -1;
      return *this;
    }



    if(signo_ > 0){
      if(coefPoliB_[0] > 0)
        coefPoliB_[0]--;
      else //habria acarreo, hacerlo de forma "standard"
        coefPoliB_ = vCPUVectorial::restaMP(coefPoliB_, (Digit)1);
    }
    else{ //signo_ < 0
      if(coefPoliB_[0] < Constants::CIFRA_MAX)
        coefPoliB_[0]++;
      else //habria acarreo, hacerlo de forma "standard"
        coefPoliB_ = vCPUVectorial::sumaMP(coefPoliB_, (Digit)1);
    }


    return *this;
  }

  size_t Z::numBits(void) const
  {

    size_t componentes = coefPoliB_.size() - 1;
    return (( Constants::BITS_EN_CIFRA * componentes) + vCPUVectorial::numBits(coefPoliB_[componentes]));

  }

  SignedDigit Z::redondear(size_t exceso) 
  {

    return vCPUVectorial::redondear(coefPoliB_, exceso, signo_);
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


    vCPUVectorial::limpiarCeros(coefPoliB_);
    if( (coefPoliB_.size() == 1) && (coefPoliB_[0] == 0) )
      signo_ = 1; //POR CO 0NVENIO
    return;
  }


  size_t Z::numDoses(void) const
  {
    if ( this->esImpar() )
      return 0;

    Z temp(*this);
    size_t doses = 0;

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
    Funciones *funcs = Funciones::getInstance();
    TestPrimoProb* primTest; funcs->getFunc(primTest);
    GCD* gcd; funcs->getFunc(gcd);
    
    if( this->esPar() )
      p = Z((Digit)2);
    else{
      q = (*this);
      while(true){
        if(primTest->esPrimo(q, &a)){
          p = q;
          break;
        }
        else{
          Z d;
          d = gcd->gcd((a^q)-a,q);
          if( d.esUno() || (d == q) ){
            primo->hacerCero();
            return false;
          }
          else
            q = d;
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
        
      

    
      

  
  Z& Z::divisionBase(const size_t n)
  {
    if( coefPoliB_.size() > n ){
      coefPoliB_.erase(coefPoliB_.begin(), coefPoliB_.begin()+n);
    }
    else{
      hacerCero();
    }
    return *this;
  }

  Z& Z::moduloBase(const size_t n)
  {
    coefPoliB_.resize(n);
    limpiarCeros();

    return *this;
  }

  Z& Z::potenciaBase(const size_t n)
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


  std::string Z::toString(void) const {
    std::ostringstream oss;
    oss << *this;

    return oss.str().c_str();
  }

  /******************************/
  std::ostream& 
    operator<<(std::ostream& out, Z num) 
    {
      std::stack<Digit> pila;  
      Digit resto;
      std::ostringstream oss;


      if( num.signo_ < 0 ){
        oss << "-";
        num.hacerPositivo();
      }

      if( Z::precisionSalida_ == 0){ //sin limitacion
        Digit potenciaInicial = (Digit)pow(10.0,Constants::MAX_EXP10_CIFRA);
        while( num.longitud() > 1 ){
          resto = (num % potenciaInicial)[0]; 
          num /= potenciaInicial; 
          pila.push(resto);
        }

        //"num" es ahora la primera cifra del n� en base 10^{Constants::MAX_EXP10_CIFRA}
        
        oss << num[0];

        while( !pila.empty() ){
          oss << std::setfill('0') << setw(Constants::MAX_EXP10_CIFRA) <<  pila.top();
          pila.pop();
        }
      }
      else{ //precisionSalida_ > 0 ==> limitacion
        size_t digitos10 = (size_t)ceil(num.numBits() * Constants::LOG_10_2);
        size_t digitos10Mostrados = 0;

        if(num.esCero()){
          oss << "0";
        }
        else{
          Digit potenciaInicial = (Digit)10;
          while( !num.esCero() ){
            resto = (num % potenciaInicial)[0]; 
            num /= potenciaInicial; 
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
    static Digit const potenciaInicial = (Digit)pow(10.0,Constants::MAX_EXP10_CIFRA);

    while( in.get(c) ) {
      if( std::isdigit(c) ) {
        n *= 10;
        ++numDigits;
        n += c - '0';  //FIXME: is this portable?
        if( numDigits >= Constants::MAX_EXP10_CIFRA ){ //shouldn't ever be >
          //put into the number to return
          res *= potenciaInicial;
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


  
  Z operator>>(Z num, const size_t desp)
  {
    num >>= desp;
    return num;
  }

  Z operator<<(Z num, const size_t desp)
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
    //      if( largo.esNegativo() )
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
          resultados = vCPUVectorial::divMP(dividendo.coefPoliB_, divisor.coefPoliB_);

          cociente->coefPoliB_ = resultados.first;

          resto->coefPoliB_ = resultados.second;

        }
        else{ //dividendo < 0
          resultados = vCPUVectorial::divMP(dividendo.coefPoliB_, divisor.coefPoliB_);

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
          resultados = vCPUVectorial::divMP(dividendo.coefPoliB_, divisor.coefPoliB_);

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
          resultados = vCPUVectorial::divMP(dividendo.coefPoliB_, divisor.coefPoliB_);

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
          resultados = vCPUVectorial::divMP(dividendo.coefPoliB_, divisorDigit);

          cociente->coefPoliB_ = resultados.first;

          resto->coefPoliB_ = resultados.second;

        }
        else{ //dividendo < 0
          resultados = vCPUVectorial::divMP(dividendo.coefPoliB_, divisorDigit);

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
          resultados = vCPUVectorial::divMP(dividendo.coefPoliB_, divisorDigit);

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
          resultados = vCPUVectorial::divMP(dividendo.coefPoliB_, divisorDigit);

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
        resultados = vCPUVectorial::divMP(dividendo.coefPoliB_, divisor);

        cociente->coefPoliB_ = resultados.first;

        resto->coefPoliB_ = resultados.second;

      }
      else{ //dividendo < 0
        resultados = vCPUVectorial::divMP(dividendo.coefPoliB_, divisor);

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


  Z raizCuadrada(Z x)
  {
    x.raizCuadrada();
    return x;
  }

  Digit raizCuadrada(Digit x)
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

  bool esCuadrado(Z x)
  {
    return x.esCuadrado();
  }

  size_t numBits(const Z& x)
  {
    return x.numBits();
  }
  size_t numBits(const Digit x)
  {
    return vCPUVectorial::numBits(x);
  }
  size_t numBits(const SignedDigit x)
  {
    return vCPUVectorial::numBits((Digit)labs(x));
  }

}
