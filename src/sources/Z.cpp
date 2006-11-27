/*
 * $Id$
 */

#include "Z.h"
#include "Funciones.h"
#include <cstring>
#include <sstream>
#include <stack>
#include <cassert>
#include <cstdlib>
#include <cmath>
#include <string>
#include <utility>
#include "mp.h"

namespace numth{

  size_t Z::precisionSalida_ = 0;
  vCPUVectorial cpuVectorial_(1);

  // implementacion constructores
  Z::Z()
    : coefPoliB_(1,(Cifra)0), signo_(1)
    {}

  Z::Z(const Z& otro)
    : coefPoliB_(otro.coefPoliB_), signo_(otro.signo_)
    {}

  Z Z::convertir(const Cifra origen)
  {
    Z temp(origen);
    return temp;
  }

  Z Z::convertir(const CifraSigno origen)
  {
    Z temp(origen);
    return temp;
  }

  Z Z::convertir(const char* origen) throw (Errores::Sintactico)
  {
    Z temp(origen);
    return temp;
  }


  Z Z::convertir(const double origen)
  {
    Z temp(origen);
    return temp;
  }

  Z Z::convertir(const MiVec<Cifra>& vec)
  {
    Z temp; temp.coefPoliB_ = vec;
    temp.limpiarCeros();
    return temp;
  }

  /* constructores privados para el uso de la funcion de conversion */
  Z::Z(const CifraSigno otro)
    : coefPoliB_(1)
    {
      coefPoliB_[0] = labs(otro);
      if(otro < 0)
        signo_ = -1;
      else 
        signo_ = 1;
    }

  Z::Z(const Cifra otro)
    : coefPoliB_(1,otro)
    {
      signo_ = 1;
    }

  Z::Z(const double otro)
  {
    std::ostringstream cadStream;
    cadStream.setf(std::ios_base::fixed);
    cadStream.unsetf(std::ios_base::showpoint);
    cadStream.precision(Constantes::MAX_EXP10_DOUBLE); 
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

  Z& Z::operator=(const Cifra der)
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
        return cpuVectorial_.mayorque(coefPoliB_,der.coefPoliB_);
      else // der < 0
        return true;
    }
    else{ // this < 0
      if( (der.signo_ > 0) )
        return false;
      else // der < 0
        return cpuVectorial_.menorque(coefPoliB_, der.coefPoliB_);
    }
  }

  bool Z::operator<(const Z& der) const
  {


    if( (signo_ > 0) ){
      if( (der.signo_ > 0) )
        return cpuVectorial_.menorque(coefPoliB_,der.coefPoliB_);
      else // der < 0
        return false;
    }
    else{ // this < 0
      if( (der.signo_ > 0) )
        return true;
      else // der < 0
        return cpuVectorial_.mayorque(coefPoliB_, der.coefPoliB_);
    }

  }

  bool Z::operator==(const Z& der) const
  {


    if( signo_ == der.signo_ )
      if ( cpuVectorial_.igual(coefPoliB_, der.coefPoliB_) )
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

  bool Z::operator>(const CifraSigno der) const
  {


    if( (signo_ > 0) )
      if(der >= 0)
        return cpuVectorial_.mayorque( coefPoliB_, (Cifra)der );
      else // der < 0
        return true;
    else // signo_ < 0 
      if( der >= 0)
        return false;
      else // der < 0
        // ambos son negativos. Por tanto el mayor será el menor
        // en valor absoluto
        return cpuVectorial_.menorque( coefPoliB_, (Cifra)labs(der) );
  }  

  bool Z::operator<(const CifraSigno der) const
  {


    if( (signo_ > 0) )
      if(der >= 0)
        return cpuVectorial_.menorque( coefPoliB_, (Cifra)der );
      else // der < 0
        return false;
    else // signo_ < 0 
      if( der >= 0)
        return true;
      else // der < 0
        // ambos son negativos. Por tanto el menor será el mayor
        // en valor absoluto
        return cpuVectorial_.mayorque( coefPoliB_, (Cifra)labs(der) );
  }

  bool Z::operator==(const CifraSigno der) const
  {


    if( (signo_ > 0) )
      if(der >= 0)
        return cpuVectorial_.igual( coefPoliB_, (Cifra)der );
      else // der < 0
        return false;
    else // signo_ < 0 
      if( der >= 0)
        return false;
      else // der < 0
        //ambos negativos; serán iguales si son iguales en valor
        //absoluto
        return cpuVectorial_.igual( coefPoliB_, (Cifra)labs(der) );
  }
  bool Z::operator!=(const CifraSigno der) const
  {
    return !(operator==(der));
  }
  bool Z::operator>=(const CifraSigno der) const
  {
    if( operator>(der) || operator==(der) )
      return true;
    else
      return false;
  }
  bool Z::operator<=(const CifraSigno der) const
  {
    if( operator<(der) || operator==(der) )
      return true;
    else
      return false;
  }

  bool Z::operator>(const Cifra der) const
  {


    if( (signo_ > 0) )
      return cpuVectorial_.mayorque( coefPoliB_, der );
    else // signo_ < 0 
      return false;
  }  

  bool Z::operator<(const Cifra der) const
  {


    if( (signo_ > 0) )
      return cpuVectorial_.menorque( coefPoliB_, der );
    else // signo_ < 0 
      return true;
  }

  bool Z::operator==(const Cifra der) const
  {


    if( (signo_ > 0) )
      return cpuVectorial_.igual( coefPoliB_, der );
    else // signo_ < 0 
      return false;
  }
  bool Z::operator!=(const Cifra der) const
  {
    return !(operator==(der));
  }
  bool Z::operator>=(const Cifra der) const
  {
    if( operator>(der) || operator==(der) )
      return true;
    else
      return false;
  }
  bool Z::operator<=(const Cifra der) const
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
        this->coefPoliB_ = cpuVectorial_.sumaMP(coefPoliB_, sumandoDerecha.coefPoliB_);
        return *this;
      }
      else{ // sumandoDerecha < 0
        if( cpuVectorial_.mayorque(coefPoliB_, sumandoDerecha.coefPoliB_) )
          this->coefPoliB_ = cpuVectorial_.restaMP(coefPoliB_, sumandoDerecha.coefPoliB_);
        else{
          this->coefPoliB_ = cpuVectorial_.restaMP(sumandoDerecha.coefPoliB_, coefPoliB_);
          this->signo_ = -1;
        }
        return *this;
      }
    }
    else{ // this < 0
      if( (sumandoDerecha.signo_ > 0) ){
        // (-a) + b = b - a
        if( cpuVectorial_.mayorque(coefPoliB_,sumandoDerecha.coefPoliB_) )
          this->coefPoliB_ = cpuVectorial_.restaMP(coefPoliB_, sumandoDerecha.coefPoliB_);
        else{
          this->coefPoliB_ = cpuVectorial_.restaMP(sumandoDerecha.coefPoliB_, coefPoliB_);
          this->signo_ = 1;
        }
        return *this;
      }
      else{ // sumandoDerecha < 0
        this->coefPoliB_ = cpuVectorial_.sumaMP(this->coefPoliB_, sumandoDerecha.coefPoliB_);
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
        if( cpuVectorial_.mayorque(sustraendo.coefPoliB_, coefPoliB_) ){ // b > a
          this->coefPoliB_ = cpuVectorial_.restaMP(sustraendo.coefPoliB_, coefPoliB_);
          this->signo_ = -1;
        }
        else // b <= a
          this->coefPoliB_ = cpuVectorial_.restaMP(coefPoliB_, sustraendo.coefPoliB_);
        // se mantiene el signo +
      }
      else{ // sustraendo  < 0
        // a - (-b) = a + b
        this->coefPoliB_ = cpuVectorial_.sumaMP(coefPoliB_, sustraendo.coefPoliB_);
        //se mantiene el signo +
      }
    }
    else{ // this < 0
      if( (sustraendo.signo_ > 0) ){
        // (-a) - b = -(a + b)
        this->coefPoliB_ = cpuVectorial_.sumaMP(coefPoliB_, sustraendo.coefPoliB_);
        // se mantiene el signo -
      }
      else{ // sustraendo < 0
        // (-a) - (-b) = b - a
        if( cpuVectorial_.mayorque(sustraendo.coefPoliB_, coefPoliB_) ){ // b > a
          this->coefPoliB_ = cpuVectorial_.restaMP(sustraendo.coefPoliB_, coefPoliB_);
          this->signo_ = 1;
        }
        else // b <= a
          this->coefPoliB_ = cpuVectorial_.restaMP( coefPoliB_, sustraendo.coefPoliB_ );
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
        this->coefPoliB_ = cpuVectorial_.multMP(coefPoliB_, factorDer.coefPoliB_);
        // se mantiene el signo +
      }
      else{ // factorDer  < 0
        // a * (-b) = -(ab)
        this->coefPoliB_ = cpuVectorial_.multMP(coefPoliB_, factorDer.coefPoliB_);
        this->signo_ = -1;
      }
    }
    else{ // this < 0
      if( (factorDer.signo_ > 0) ){
        // (-a) * b = -(ab)
        this->coefPoliB_ = cpuVectorial_.multMP(coefPoliB_, factorDer.coefPoliB_);
        // se deja el signo -
      }
      else{ // factorDer < 0
        // (-a) * (-b) = ab
        this->coefPoliB_ = cpuVectorial_.multMP(coefPoliB_, factorDer.coefPoliB_);
        this->signo_ = 1;
      }
    }

    return *this;
  } 


  Z& Z::operator/=(const Z& divisor)
  {

    if( divisor.esCero() )
      throw Errores::DivisionPorCero();

    if( (signo_ > 0) ){
      if( (divisor.signo_ > 0) ){
        // a / b
        this->coefPoliB_ = (cpuVectorial_.divMP(coefPoliB_, divisor.coefPoliB_)).first;
        // se mantiene el signo +
      }
      else{ // divisor  < 0
        // a / (-b) = -(a / b)
        this->coefPoliB_ = (cpuVectorial_.divMP(coefPoliB_, divisor.coefPoliB_)).first;
        this->signo_ = -1;
      }
    }
    else{ // this < 0
      if( (divisor.signo_ > 0) ){
        // (-a) / b = -(a / b)
        this->coefPoliB_ = (cpuVectorial_.divMP(coefPoliB_, divisor.coefPoliB_)).first;
        // se deja el signo -
      }
      else{ // divisor < 0
        // (-a) / (-b) = a / b
        this->coefPoliB_ = (cpuVectorial_.divMP(coefPoliB_, divisor.coefPoliB_)).first;
        this->signo_ = 1;
      }
    }

    return *this;
  }

  Z& Z::operator%=(const Z& divisor)
  {


    if( divisor.esCero() )
      throw Errores::DivisionPorCero();

    if( divisor.signo_ > 0){ // divisor.signo_ > 0
      if( signo_ > 0 ){
        coefPoliB_ = (cpuVectorial_.divMP(coefPoliB_, divisor.coefPoliB_)).second;
        // se mantiene el signo +
      }
      else{ //signo_ < 0
        coefPoliB_ = (cpuVectorial_.divMP(coefPoliB_, divisor.coefPoliB_)).second;
        if( !(this->esCero()) )
          this->operator+=(divisor); // ajuste por dividendo negativo
        signo_ = 1;
        //El "floor" de la def del modulo(m,n) = m - (floor(m,n) * n)
        //sería una unidad menor que la parte entera, ya que sería
        //negativo. Por tanto, esto es equivalente a:
        // modulo(m,n) / n < 0 = modulo(m,-n) + n 
        //
        // Por otra parte, el modulo siempre tiene el signo del divisor

      }
    }
    else{ // divisor.signo_ < 0
      if( signo_ > 0){
        coefPoliB_ = (cpuVectorial_.divMP(coefPoliB_, divisor.coefPoliB_)).second;
        if( !(this->esCero()) )
          this->operator+=(divisor); //ajuste por ser divisor negativo
        //El "floor" de la def del modulo(m,n) = m - (floor(m,n) * n)
        //sería una unidad menor que la parte entera, ya que sería
        //negativo. Por tanto, esto es equivalente a:
        // modulo(m,n) / n < 0 = modulo(m,-n) + n (esto seria una resta,
        // recordar que n es < 0 ).
        //
        // Por otra parte, el modulo siempre tiene el signo del divisor
      }
      else{ // signo_ < 0
        coefPoliB_ = (cpuVectorial_.divMP(coefPoliB_, divisor.coefPoliB_)).second;
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
      this->coefPoliB_.resize(der.coefPoliB_.size(),(Cifra)0);
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
    coefPoliB_ = cpuVectorial_.cuadMP(coefPoliB_); 
    return *this;
  }

  Z& Z::cuadradoModular(const Z& mod)
  {

    (*this) %= mod;

    signo_ = 1; //el cuadrado siempre va a tener este efecto
    coefPoliB_ = cpuVectorial_.cuadMP(coefPoliB_); 

    (*this) %= mod;

    return *this;
  }
  Z& Z::factorial(void) 
  {
    if( this->coefPoliB_.size() > 1 )
      throw Errores::DemasiadoGrande();

    Cifra n = coefPoliB_[0];
    Cifra m;
    Cifra mTemp = 1;
    this->hacerUno();

    unsigned long doses = 0;

    for( ; n > 1; n-- ){
      for( m = n; (m & 0x1) == 0; m >>= 1 )
        doses++;


      if( mTemp <= Constantes::CIFRA_MAX/m ){
        mTemp *= m;
        continue;
      }
      else{
        (*this) *= mTemp;
        mTemp = m;
      }
    }
    if(mTemp > 1) // Hay valores acumulados en la Cifra mTemp. Incoporarlos
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

    if (Constantes::Q64[t] == false) 
      return false;
    if (Constantes::Q63[r % 63] == false)  
      return false;
    if (Constantes::Q65[r % 65] == false) 
      return false;
    if (Constantes::Q11[r % 11] == false)
      return false;

    Z raizCuad(*this);
    raizCuad.raizCuadrada();
    if( numth::cuadrado(raizCuad) != (*this) )
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

  Z& Z::operator+=(const CifraSigno corto)
  {


    Cifra cortoCifra;
    if( corto >= 0 )
      cortoCifra = (Cifra)corto;
    else //corto < 0
      cortoCifra = (Cifra)labs(corto);

    if( (signo_ > 0) ){
      if( (corto > 0) ){
        coefPoliB_ = cpuVectorial_.sumaMP(coefPoliB_, cortoCifra);
      }
      else{ // corto  < 0
        if( cpuVectorial_.mayorque(coefPoliB_, cortoCifra) )
          coefPoliB_ = cpuVectorial_.restaMP(coefPoliB_, cortoCifra);
        else{
          coefPoliB_ = cpuVectorial_.restaMP(cortoCifra, coefPoliB_);
          signo_ = -1;
        }
      }
    }
    else{ // this < 0
      if( (corto > 0) ){
        // (-a) + b = b - a
        if( cpuVectorial_.mayorque(coefPoliB_, cortoCifra) )
          coefPoliB_ = cpuVectorial_.restaMP(coefPoliB_, cortoCifra);
        else{
          coefPoliB_ = cpuVectorial_.restaMP(cortoCifra, coefPoliB_);
          signo_ = 1;
        }
      }
      else{ // corto < 0
        coefPoliB_ = cpuVectorial_.sumaMP(coefPoliB_, cortoCifra);
        //mantener el signo "-"
      }
    }

    return *this;

  }


  Z& Z::operator-=(const CifraSigno corto)
  {


    Cifra cortoCifra;
    if( corto >= 0 )
      cortoCifra = (Cifra)corto;
    else //corto < 0
      cortoCifra = (Cifra)labs(corto);

    if( (signo_ > 0) ){
      if( (corto > 0) ){
        // a - b
        if(  cpuVectorial_.menorque(coefPoliB_, cortoCifra) ){ // a < b 
          coefPoliB_ = cpuVectorial_.restaMP(cortoCifra, coefPoliB_);
          signo_ = -1;
        }
        else // b <= a
          coefPoliB_ = cpuVectorial_.restaMP(coefPoliB_, cortoCifra);
        // se mantiene el signo +
      }
      else{ // corto  < 0
        // a - (-b) = a + b
        coefPoliB_ = cpuVectorial_.sumaMP(coefPoliB_, cortoCifra);
        //se mantiene el signo +
      }
    }
    else{ // this < 0
      if( (corto > 0) ){
        // (-a) - b = -(a + b)
        coefPoliB_ = cpuVectorial_.sumaMP(coefPoliB_, cortoCifra);
        // se mantiene el signo -
      }
      else{ // corto < 0
        // (-a) - (-b) = b - a
        if( cpuVectorial_.menorque(coefPoliB_, cortoCifra ) ){ // a < b
          coefPoliB_ = cpuVectorial_.restaMP(cortoCifra, coefPoliB_);
          signo_ = 1;
        }
        else // b <= a
          coefPoliB_ = cpuVectorial_.restaMP( coefPoliB_, cortoCifra );
        // se deja el signo -
      }
    }

    return *this;

  }

  Z& Z::operator*=(const CifraSigno corto)
  {


    Cifra cortoCifra;
    if( corto >= 0 )
      cortoCifra = (Cifra)corto;
    else //corto < 0
      cortoCifra = (Cifra)labs(corto);

    if( (signo_ > 0) ){
      if( (corto > 0) ){
        // a * b
        coefPoliB_ = cpuVectorial_.multMP(coefPoliB_, cortoCifra);
        // se mantiene el signo +
      }
      else{ // corto  < 0
        // a * (-b) = -(ab)
        coefPoliB_ = cpuVectorial_.multMP(coefPoliB_, cortoCifra);
        signo_ = -1;
      }
    }
    else{ // this < 0
      if( (corto > 0) ){
        // (-a) * b = -(ab)
        coefPoliB_ = cpuVectorial_.multMP(coefPoliB_, cortoCifra);
        // se deja el signo -
      }
      else{ // corto < 0
        // (-a) * (-b) = ab
        coefPoliB_ = cpuVectorial_.multMP(coefPoliB_, cortoCifra);
        signo_ = 1;
      }
    }

    return *this;

  } 


  Z& Z::operator/=(const CifraSigno corto)
  {
    if( corto == 0 )
      throw Errores::DivisionPorCero();


    Cifra cortoCifra;
    if( corto >= 0 )
      cortoCifra = (Cifra)corto;
    else //corto < 0
      cortoCifra = (Cifra)labs(corto);

    if( (signo_ > 0) ){
      if( (corto > 0) ){
        // a / b
        coefPoliB_ = (cpuVectorial_.divMP(coefPoliB_, cortoCifra)).first;
        // se mantiene el signo +
      }
      else{ // corto  < 0
        // a / (-b) = -(a / b)
        coefPoliB_ = (cpuVectorial_.divMP(coefPoliB_, cortoCifra)).first;
        signo_ = -1;
      }
    }
    else{ // this < 0
      if( (corto > 0) ){
        // (-a) / b = -(a / b)
        coefPoliB_ = (cpuVectorial_.divMP(coefPoliB_, cortoCifra)).first;
        // se deja el signo -
      }
      else{ // corto < 0
        // (-a) / (-b) = a / b
        coefPoliB_ = (cpuVectorial_.divMP(coefPoliB_, cortoCifra)).first;
        signo_ = 1;
      }
    }

    return *this;

  }

  Z& Z::operator%=(const CifraSigno divisorSigned)
  {
    if( divisorSigned == 0 )
      throw Errores::DivisionPorCero();

    this->operator%=(Z::convertir(divisorSigned));

    //  Cifra divisor;
    //  if( divisorSigned >= 0 )
    //    divisor = (Cifra)divisorSigned;
    //  else
    //    divisor = (Cifra)labs(divisorSigned);
    //  
    //  if( divisorSigned > 0){ // divisor > 0
    //    if( signo_ > 0 ){
    //      coefPoliB_ = (cpuVectorial_.divMP(coefPoliB_, divisor)).second;
    //      // se mantiene el signo +
    //    }
    //    else{ //signo_ < 0
    //      coefPoliB_ = (cpuVectorial_.divMP(coefPoliB_, divisor)).second;
    //      if( !(this->esCero()) )
    //        this->operator+=(divisor); // ajuste por dividendo negativo
    //      signo_ = 1;
    //      //El "floor" de la def del modulo(m,n) = m - (floor(m,n) * n)
    //      //sería una unidad menor que la parte entera, ya que sería
    //      //negativo. Por tanto, esto es equivalente a:
    //      // modulo(m,n) / n < 0 = modulo(m,-n) + n 
    //      //
    //      // Por otra parte, el modulo siempre tiene el signo del divisor
    //
    //    }
    //  }
    //  else{ // divisor_ < 0
    //    if( signo_ > 0){
    //       coefPoliB_ = (cpuVectorial_.divMP(coefPoliB_, divisor)).second;
    //      if( !(this->esCero()) )
    //        this->operator-=(divisor); //ajuste por ser divisor negativo
    //      //El "floor" de la def del modulo(m,n) = m - (floor(m,n) * n)
    //      //sería una unidad menor que la parte entera, ya que sería
    //      //negativo. Por tanto, esto es equivalente a:
    //      // modulo(m,n) / n < 0 = modulo(m,-n) + n (esto seria una resta,
    //      // recordar que n es < 0 ).
    //      //
    //      // Por otra parte, el modulo siempre tiene el signo del divisor
    //    }
    //    else{ // signo_ < 0
    //      coefPoliB_ = (cpuVectorial_.divMP(coefPoliB_, divisor)).second;
    //      signo_ = -1;
    //    }
    //  }
    //  
    return *this;

  }  



  Z& Z::operator&=(const CifraSigno derSigno)
  {
    Cifra der = (Cifra)labs(derSigno);

    this->coefPoliB_.resize(1,(Cifra)0);
    this->coefPoliB_[0] &= der;

    return *this;
  }  

  Z& Z::operator|=(const CifraSigno derSigno)
  {
    Cifra der = (Cifra)labs(derSigno);

    this->coefPoliB_[0] |= der;

    return *this;
  }  

   Z& Z::XOR(const CifraSigno derSigno)
   {
     Cifra der = (Cifra)labs(derSigno);

     this->coefPoliB_[0] xor_eq der;

     return *this;
   }  

  

  Z& Z::operator+=(const Cifra corto)
  {


    Cifra cortoCifra;
    cortoCifra = (Cifra)corto;

    if( signo_ > 0 ){
      coefPoliB_ = cpuVectorial_.sumaMP(coefPoliB_, cortoCifra);
      return *this;
    }
    else{ // signo_ < 0
      if( cpuVectorial_.mayorque(coefPoliB_, cortoCifra) )
        coefPoliB_ = cpuVectorial_.restaMP(coefPoliB_, cortoCifra);
      else{
        coefPoliB_ = cpuVectorial_.restaMP(cortoCifra, coefPoliB_);
        signo_ = 1;
      }
      return *this;
    }
  }
  Z& Z::operator-=(const Cifra corto)
  {
    Cifra cortoCifra;
    cortoCifra = (Cifra)corto;


    if( signo_ > 0 ){ // a - b
      if(  cpuVectorial_.menorque(coefPoliB_, cortoCifra) ){ // a < b 
        coefPoliB_ = cpuVectorial_.restaMP(cortoCifra, coefPoliB_);
        signo_ = -1;
      }
      else // b <= a
        coefPoliB_ = cpuVectorial_.restaMP(coefPoliB_, cortoCifra);
      // se mantiene el signo +
      return *this;
    }
    else{ //signo_ < 0 
      coefPoliB_ = cpuVectorial_.sumaMP(coefPoliB_, cortoCifra);
      // se mantiene el signo -
      return *this;
    }
  }

  Z& Z::operator*=(const Cifra corto)
  {


    Cifra cortoCifra;
    cortoCifra = (Cifra)corto;

    if( signo_ > 0 ){ // a * b
      coefPoliB_ = cpuVectorial_.multMP(coefPoliB_, cortoCifra);
      // se mantiene el signo +
      return *this;
    }
    else{ //signo_< 0
      // (-a) * b = -(ab)
      coefPoliB_ = cpuVectorial_.multMP(coefPoliB_, cortoCifra);
      // se deja el signo -
      return *this;
    }
  } 


  Z& Z::operator/=(const Cifra corto)
  {
    if( corto == 0 )
      throw Errores::DivisionPorCero();



    Cifra cortoCifra;
    cortoCifra = (Cifra)corto;

    if( signo_ > 0 ){ // a / b
      coefPoliB_ = (cpuVectorial_.divMP(coefPoliB_, cortoCifra)).first;
      // se mantiene el signo +
      return *this;
    }
    else{ //signo_ < 0
      // (-a) / b = -(a / b)
      coefPoliB_ = (cpuVectorial_.divMP(coefPoliB_, cortoCifra)).first;
      // se deja el signo -
      return *this;
    }
  }

  Z& Z::operator%=(const Cifra corto)
  {
    if( corto == 0 )
      throw Errores::DivisionPorCero();

    this->operator%=(Z::convertir(corto));

    //  Cifra cortoCifra;
    //  cortoCifra = (Cifra)corto;
    //
    //  if( signo_ > 0 ){
    //    coefPoliB_ = (cpuVectorial_.divMP(coefPoliB_, cortoCifra)).second;
    //    // se mantiene el signo +
    //  }
    //  else{ //signo_ < 0
    //    coefPoliB_ = (cpuVectorial_.divMP(coefPoliB_, cortoCifra)).second;
    //    if( !(this->esCero()) )
    //      this->operator+=(cortoCifra); // ajuste por dividendo negativo
    //    signo_ = 1;
    //    //El "floor" de la def del modulo(m,n) = m - (floor(m,n) * n)
    //    //sería una unidad menor que la parte entera, ya que sería
    //    //negativo. Por tanto, esto es equivalente a:
    //    // modulo(m,n) / n < 0 = modulo(m,-n) + n 
    //    //
    //    // Por otra parte, el modulo siempre tiene el signo del divisor
    //  }
    //
    return *this;
  }  


  Z& Z::operator&=(const Cifra der)
  {
    this->coefPoliB_.resize(1,(Cifra)0);
    this->coefPoliB_[0] &= der;

    return *this;
  }  

  Z& Z::operator|=(const Cifra der)
  {
    this->coefPoliB_[0] |= der;

    return *this;
  }  

  Z& Z::XOR(const Cifra der)
  {
    this->coefPoliB_[0] xor_eq der;

    return *this;
  }  

  

  Z& Z::operator^=(const Cifra e)
  {
    Funciones funcs;
    funcs.potencia()->potencia(this, e);

    return *this; 

  }

  Z& Z::operator^=(const Z& exp)
  {
    if( exp.longitud() > 1 )
      throw Errores::DemasiadoGrande();

    Cifra exponente = exp[0];

    return operator^=(exponente);
  }

  Z& Z::operator^=(const CifraSigno exp)
  {
    if( exp < 0 )
      throw Errores::ExponenteNegativo();

    return operator^=((Cifra)labs(exp));
  }


  Z& Z::operator>>=(const size_t desp)
  {

    cpuVectorial_.rShift(coefPoliB_, desp);
    return *this;
  }

  Z& Z::operator<<=(const size_t desp)
  {

    cpuVectorial_.lShift(coefPoliB_, desp);
    return *this;
  }


  Z& Z::operator++(void)
  {


    if( esCero() ){
      hacerUno();
      return *this;
    }

    if(signo_ > 0){
      if(coefPoliB_[0] < Constantes::CIFRA_MAX)
        coefPoliB_[0]++;
      else //habria acarreo, hacerlo de forma "standard"
        coefPoliB_ = cpuVectorial_.sumaMP(coefPoliB_, (Cifra)1);
    }
    else{ //signo_ < 0
      if(coefPoliB_[0] > 0)
        coefPoliB_[0]--;
      else //habria acarreo, hacerlo de forma "standard"
        coefPoliB_ = cpuVectorial_.restaMP(coefPoliB_, (Cifra)1);
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
      if(coefPoliB_[0] < Constantes::CIFRA_MAX)
        coefPoliB_[0]++;
      else //habria acarreo, hacerlo de forma "standard"
        coefPoliB_ = cpuVectorial_.sumaMP(coefPoliB_, (Cifra)1);
    }
    else{ //signo_ < 0
      if(coefPoliB_[0] > 0)
        coefPoliB_[0]--;
      else //habria acarreo, hacerlo de forma "standard"
        coefPoliB_ = cpuVectorial_.restaMP(coefPoliB_, (Cifra)1);
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
        coefPoliB_ = cpuVectorial_.restaMP(coefPoliB_, (Cifra)1);
    }
    else{ //signo_ < 0
      if(coefPoliB_[0] < Constantes::CIFRA_MAX)
        coefPoliB_[0]++;
      else //habria acarreo, hacerlo de forma "standard"
        coefPoliB_ = cpuVectorial_.sumaMP(coefPoliB_, (Cifra)1);
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
        coefPoliB_ = cpuVectorial_.restaMP(coefPoliB_, (Cifra)1);
    }
    else{ //signo_ < 0
      if(coefPoliB_[0] < Constantes::CIFRA_MAX)
        coefPoliB_[0]++;
      else //habria acarreo, hacerlo de forma "standard"
        coefPoliB_ = cpuVectorial_.sumaMP(coefPoliB_, (Cifra)1);
    }


    return *this;
  }

  size_t Z::numBits(void) const
  {

    size_t componentes = coefPoliB_.size() - 1;
    return (( Constantes::BITS_EN_CIFRA * componentes) + cpuVectorial_.numBits(coefPoliB_[componentes]));

  }

  CifraSigno Z::redondear(size_t exceso) 
  {

    return cpuVectorial_.redondear(coefPoliB_, exceso, signo_);
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
    if( coefPoliB_.size() > 1 )
      return false;

    if( coefPoliB_[0] != 0 )
      return false;

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


    cpuVectorial_.limpiarCeros(coefPoliB_);
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
        break; // ya que si hemos entrado aqui es porque el nº es de la forma
        // ...10 , que tras el >>= 1 será ....1
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
    Funciones funcs;
    
    if( this->esPar() )
      p = Z::convertir((Cifra)2);
    else{
      q = (*this);
      while(true){
        if(funcs.testPrimoProb()->esPrimo(q, &a)){
          p = q;
          break;
        }
        else{
          Z d;
          d = funcs.gcd()->gcd((a^q)-a,q);
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
    if( coefPoliB_.size() > n )
      coefPoliB_.erase(coefPoliB_.begin(), coefPoliB_.begin()+n);
    else
      hacerCero();
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
    coefPoliB_.clear();
    coefPoliB_.resize(n+1,0); 
    coefPoliB_[n] = 1;

    return *this;
  }





  /******************************/
  std::ostream& 
    operator<<(std::ostream& out, Z num)
    {
      std::stack<Cifra> pila;  
      Cifra resto;

      if( num.signo_ < 0 ){
        out << "-";
        num.hacerPositivo();
      }

      if( Z::precisionSalida_ == 0){ //sin limitacion
        Cifra potenciaInicial = (Cifra)pow(10,Constantes::MAX_EXP10_CIFRA);
        while( num.longitud() > 1 ){
          resto = (num % potenciaInicial)[0]; 
          num /= potenciaInicial; 
          pila.push(resto);
        }

        //"num" es ahora la primera cifra del nº en base 10^{Constantes::MAX_EXP10_CIFRA}
        out << num[0];
        while( !pila.empty() ){
          out.width(Constantes::MAX_EXP10_CIFRA);
          out.fill('0');
          out  << pila.top();
          pila.pop();
        }
      }
      else{ //precisionSalida_ > 0 ==> limitacion
        size_t digitos10 = (size_t)ceil(num.numBits() * Constantes::LOG_10_2);
        size_t digitos10Mostrados = 0;

        if(num.esCero())
          out << "0";
        else{
          Cifra potenciaInicial = (Cifra)10;
          while( !num.esCero() ){
            resto = (num % potenciaInicial)[0]; 
            num /= potenciaInicial; 
            pila.push(resto);
            //      digitos10++;
          }
          if( Z::precisionSalida_ < digitos10 )
            //si se sacan menos digitos de los que hay...
            out << "~" ;

          //"num" es ahora la primera cifra del nº en base 10
          //    out << num[0];
          //    digitos10Mostrados++;
          while( (!pila.empty()) && (digitos10Mostrados < Z::precisionSalida_) ){
            out  << pila.top();
            pila.pop();
            digitos10Mostrados++;
          }
          if( !pila.empty() ) //hemos salido por precision
            out << "e" << (digitos10 - digitos10Mostrados);
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
       * |               | primeros digitos del nº      (MSG) -> most sig. "group"
       * -----------------
       * |               | segundo grupo de digitos
       * -----------------
       *      ...
       * -----------------
       * |               | ultimos digitos              (LSG) -> least sig. "group"
       * -----------------
       * 
       * mientras(haya elementos en la pila){
       *  desapilar y sacar por cout nº a nº (ir convirtiendo 
       *  cada cifra del nº a caracter (utilizando % 10 sobre el nº 
       *  seguido de un d /= 10 ) )
       * } 
       *
       * TODO: david tio tu eres tonto... ES SACAR EL VECTOR AL REVESSSSSS
       * directamente, sin estas milongas, usando iteradores. Solo hay q
       * tener el cuenta si el nº es + o -
       * TODO 2: si, es verdad, eres mongol. Y la base gallo? Esa mierda
       * de ahi arriba solo vale cuando estas en una base q sea potencia
       * de diez. Cada dia me das mas asco joder
       * 
       */

      return out;
    }

  std::istream& 
    operator>>(std::istream& is, Z& numero) throw(Errores::Sintactico)
    {
      std::string entrada;
      Cifra num;
      char *error;
      char temp;
      Cifra potenciaInicial = (Cifra)pow(10,Constantes::MAX_EXP10_CIFRA);

      numero = 0L;

      is >> entrada;

      size_t posError = entrada.find_first_not_of("0123456789",1);
      if ( posError != std::string::npos )
        throw Errores::SimboloInvalido(entrada[posError]);


      temp = entrada[0];

      if( temp == '-' ){
        entrada.erase(0,1);
      }
      else if (temp == '+' ){
        entrada.erase(0,1);
      }
      else if ((temp < '0') || (temp > '9') )
        throw Errores::SimboloInvalido(temp);

      unsigned long tam = entrada.size();

      if( tam % Constantes::MAX_EXP10_CIFRA ){
        num = strtoul((entrada.substr(0, tam % Constantes::MAX_EXP10_CIFRA)).c_str(), &error, 10);
        if(*error != '\0')
          throw Errores::Sintactico();

        numero = num;
        if( tam > Constantes::MAX_EXP10_CIFRA )
          numero *= potenciaInicial; 
      }

      if( tam > Constantes::MAX_EXP10_CIFRA){ 
        for(long i = (tam % Constantes::MAX_EXP10_CIFRA); 
            i+Constantes::MAX_EXP10_CIFRA < tam ; 
            i += Constantes::MAX_EXP10_CIFRA){

          num = strtoul((entrada.substr(i,Constantes::MAX_EXP10_CIFRA)).c_str(), &error, 10);
          if(*error != '\0')
            throw Errores::Sintactico();

          numero += num; 
          numero *= potenciaInicial; 
        }

        //ultima cifra
        assert(tam >= Constantes::MAX_EXP10_CIFRA ); //FIXME
        num = strtoul((entrada.substr(tam-Constantes::MAX_EXP10_CIFRA,Constantes::MAX_EXP10_CIFRA)).c_str(), &error, 10);
        if(*error != '\0')
          throw Errores::Sintactico();

        numero += num; 
      }
      else{ // tam <= Constantes::MAX_EXP10_CIFRA => todo cabe en uno
        num = strtoul(entrada.c_str(), &error, 10);
        if(*error != '\0')
          throw Errores::Sintactico();

        numero = num; 
      }
      if( temp == '-' ) // si el numero era negativo
        numero.signo_ = -1;
      else
        numero.signo_ = 1; //por omision, positivo

      return is;
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
      throw Errores::DivisionPorCero();

    izq /= der;

    return izq;
  }

  Z operator%(Z izq, const Z& der)
  {
    if( der.esCero() )
      throw Errores::DivisionPorCero();

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
  Z operator+(const CifraSigno corto, Z largo)
  {
    largo += corto;
    return largo;
  }

  Z operator-(const CifraSigno corto, Z largo)
  {
    largo -= corto;
    largo.cambiarSigno();
    return largo;
  }

  Z operator*(const CifraSigno corto, Z largo)
  {
    largo *= corto;
    return largo;
  }

  Z operator/(const CifraSigno corto, const Z& largo)
  {
    if( largo.esCero() )
      throw Errores::DivisionPorCero();

    return ( Z::convertir(corto) / largo );

    //  if( largo > corto) {
    //    Z cero;
    //    cero.hacerCero();
    //    return cero;
    //  }
    //  else 
    //  if( largo < corto ){
    //    Z cociente = Z::convertir((Cifra)labs(corto) / largo[0]); 
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

  Z operator%(const CifraSigno corto, const Z& largo)
  {
    if( largo.esCero() )
      throw Errores::DivisionPorCero();

    return( (Z::convertir(corto) % largo ) );
  }

  Z operator&(const CifraSigno corto, Z largo)
  {
    largo &= corto;
    return largo;
  }
  Z operator|(const CifraSigno corto, Z largo)
  {
    largo |= corto;
    return largo;
  }
  Z XOR(const CifraSigno corto, Z largo)
  {
    largo.XOR(corto);
    return largo;
  }


  Z operator+(Z largo, const CifraSigno corto)
  {
    largo += corto;
    return largo;
  }
  Z operator-(Z largo, const CifraSigno corto)
  {
    largo -= corto;
    return largo;
  }
  Z operator*(Z largo, const CifraSigno corto)
  {
    largo *= corto;
    return largo;
  }
  Z operator/(Z largo, const CifraSigno corto)
  {
    if( corto == 0 )
      throw Errores::DivisionPorCero();

    largo /= corto;
    return largo;
  }
  Z operator%(Z largo, const CifraSigno corto)
  {
    if( corto == 0 )
      throw Errores::DivisionPorCero();

    largo %= corto;
    return largo;
  }
  Z operator&(Z largo, const CifraSigno corto)
  {
    largo &= corto;
    return largo;
  }
  Z operator|(Z largo, const CifraSigno corto)
  {
    largo |= corto;
    return largo;
  }
  Z XOR(Z largo, const CifraSigno corto)
  {
    largo.XOR(corto);
    return largo;
  }



  Z operator+(const Cifra corto, Z largo)
  {
    largo += corto;
    return largo;
  }

  Z operator-(const Cifra corto, Z largo)
  {
    largo -= corto;
    largo.cambiarSigno();
    return largo;
  }

  Z operator*(const Cifra corto, Z largo)
  {
    largo *= corto;
    return largo;
  }

  Z operator/(const Cifra corto, const Z& largo)
  {
    if( largo.esCero() )
      throw Errores::DivisionPorCero();

    if( largo > corto) {
      Z cero;
      cero.hacerCero();
      return cero;
    }
    else 
      if( largo < corto ){
        return Z::convertir(corto / (largo[0]));
      }
      else{ //iguales
        Z uno;
        uno.hacerUno();
        return uno;
      }
  }

  Z operator%(const Cifra corto, const Z& largo)
  {
    if( largo.esCero() )
      throw Errores::DivisionPorCero();

    if( largo > corto ){
      return Z::convertir(corto);
    }
    else 
      if( largo < corto ){
        return Z::convertir(corto % (largo[0]));
      }
      else{ //iguales
        Z cero;
        cero.hacerCero();
        return cero;
      }
  }
  Z operator&(const Cifra corto, Z largo)
  {
    largo &= corto;
    return largo;
  }
  Z operator|(const Cifra corto, Z largo)
  {
    largo |= corto;
    return largo;
  }
  Z XOR(const Cifra corto, Z largo)
  {
    largo.XOR(corto);
    return largo;
  }


  

  Z operator+(Z largo, const Cifra corto)
  {
    largo += corto;
    return largo;
  }
  Z operator-(Z largo, const Cifra corto)
  {
    largo -= corto;
    return largo;
  }
  Z operator*(Z largo, const Cifra corto)
  {
    largo *= corto;
    return largo;
  }
  Z operator/(Z largo, const Cifra corto)
  {
    if( corto == 0 )
      throw Errores::DivisionPorCero();

    largo /= corto;
    return largo;
  }
  Z operator%(Z largo, const Cifra corto)
  {
    if( corto == 0 )
      throw Errores::DivisionPorCero();

    largo %= corto;
    return largo;
  }
  Z operator&(Z largo, const Cifra corto)
  {
    largo &= corto;
    return largo;
  }
  Z operator|(Z largo, const Cifra corto)
  {
    largo |= corto;
    return largo;
  }
  Z XOR(Z largo, const Cifra corto)
  {
    largo.XOR(corto);
    return largo;
  }





  /* comparacion */
  bool operator<(const CifraSigno corto, const Z& largo)
  {
    if( (largo < corto) || (largo == corto) )
      return false;
    else 
      return true;
  }

  bool operator>(const CifraSigno corto, const Z& largo)
  {
    if( (largo > corto) || (largo == corto) )
      return false;
    else 
      return true;
  }

  bool operator<=(const CifraSigno corto, const Z& largo)
  {
    if( (largo < corto) )
      return false;
    else 
      return true;
  }

  bool operator>=(const CifraSigno corto, const Z& largo)
  {
    if( (largo > corto) )
      return false;
    else 
      return true;
  }

  bool operator==(const CifraSigno corto, const Z& largo)
  {
    if( (largo == corto) )
      return true;
    else 
      return false;
  }

  bool operator!=(const CifraSigno corto, const Z& largo)
  {
    if( (largo != corto) )
      return true;
    else 
      return false;
  }




  bool operator<(const Cifra corto, const Z& largo)
  {
    if( (largo < corto) || (largo == corto) )
      return false;
    else 
      return true;
  }

  bool operator>(const Cifra corto, const Z& largo)
  {
    if( (largo > corto) || (largo == corto) )
      return false;
    else 
      return true;
  }

  bool operator<=(const Cifra corto, const Z& largo)
  {
    if( (largo < corto) )
      return false;
    else 
      return true;
  }

  bool operator>=(const Cifra corto, const Z& largo)
  {
    if( (largo > corto) )
      return false;
    else 
      return true;
  }

  bool operator==(const Cifra corto, const Z& largo)
  {
    if( (largo == corto) )
      return true;
    else 
      return false;
  }

  bool operator!=(const Cifra corto, const Z& largo)
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
      throw Errores::DemasiadoGrande();

    base ^= exp;
    return base;
  }

  Z operator^(Z base, const Cifra exp)
  {
    base ^= exp;
    return base;
  }

  Z operator^(Z base, const CifraSigno exp)
  {
    if( exp < 0 )
      throw Errores::ExponenteNegativo();

    base ^= ((Cifra)labs(exp));
    return base;
  }

  void divMod(const Z& dividendo, const Z& divisor, Z* cociente, Z* resto)
    throw (Errores::DivisionPorCero)
    {

      if( divisor.esCero() )
        throw Errores::DivisionPorCero();

      //por precaucion, no sea que se hayan pasado cosas ya trajinadas
      cociente->hacerPositivo();
      resto->hacerPositivo();

      std::pair< MiVec<Cifra>, MiVec<Cifra> > resultados;

      if( divisor.esPositivo() ){ 
        if( dividendo.esPositivo() ){
          resultados = cpuVectorial_.divMP(dividendo.coefPoliB_, divisor.coefPoliB_);

          cociente->coefPoliB_ = resultados.first;

          resto->coefPoliB_ = resultados.second;

        }
        else{ //dividendo < 0
          resultados = cpuVectorial_.divMP(dividendo.coefPoliB_, divisor.coefPoliB_);

          cociente->coefPoliB_ = resultados.first;
          cociente->hacerNegativo();

          resto->hacerNegativo();
          resto->coefPoliB_ = resultados.second;
          (*resto )+= divisor; // ajuste por dividendo negativo
          //El "floor" de la def del modulo(m,n) = m - (floor(m,n) * n)
          //sería una unidad menor que la parte entera, ya que sería
          //negativo. Por tanto, esto es equivalente a:
          // modulo(m,n) / n < 0 = modulo(m,-n) + n 
          //
          // Por otra parte, el modulo siempre tiene el signo del divisor

        }
      }
      else{ // divisor negativo
        if( dividendo.esPositivo()){
          resultados = cpuVectorial_.divMP(dividendo.coefPoliB_, divisor.coefPoliB_);

          cociente->coefPoliB_ = resultados.first;
          cociente->hacerNegativo();

          resto->coefPoliB_ = resultados.second;
          (*resto) += divisor; //ajuste por ser divisor negativo
          //El "floor" de la def del modulo(m,n) = m - (floor(m,n) * n)
          //sería una unidad menor que la parte entera, ya que sería
          //negativo. Por tanto, esto es equivalente a:
          // modulo(m,n) / n < 0 = modulo(m,-n) + n (esto seria una resta,
          // recordar que n es < 0 ).
          //
          // Por otra parte, el modulo siempre tiene el signo del divisor
        }
        else{ // dividendo negativo
          resultados = cpuVectorial_.divMP(dividendo.coefPoliB_, divisor.coefPoliB_);

          cociente->coefPoliB_ = resultados.first;

          resto->coefPoliB_ = resultados.second;
          resto->hacerNegativo();
        }
      }

      return;
    }

  void divMod(const Z& dividendo, const CifraSigno divisor, Z* cociente, Z* resto)
    throw (Errores::DivisionPorCero)
    {

      bool divisorPositivo;
      Cifra divisorCifra;

      if( divisor == 0 )
        throw Errores::DivisionPorCero();

      if( divisor < 0 ){
        divisorPositivo = false;
        divisorCifra = (Cifra)labs(divisor);
      }
      else{
        divisorPositivo = true;
        divisorCifra = (Cifra)divisor;
      }

      //por precaucion, no sea que se hayan pasado cosas ya trajinadas
      cociente->hacerPositivo();
      resto->hacerPositivo();

      std::pair< MiVec<Cifra>, MiVec<Cifra> > resultados;

      if( divisorPositivo ){ 
        if( dividendo.esPositivo() ){
          resultados = cpuVectorial_.divMP(dividendo.coefPoliB_, divisorCifra);

          cociente->coefPoliB_ = resultados.first;

          resto->coefPoliB_ = resultados.second;

        }
        else{ //dividendo < 0
          resultados = cpuVectorial_.divMP(dividendo.coefPoliB_, divisorCifra);

          cociente->coefPoliB_ = resultados.first;
          cociente->hacerNegativo();

          resto->hacerNegativo();
          resto->coefPoliB_ = resultados.second;
          (*resto) += divisor; // ajuste por dividendo negativo
          //El "floor" de la def del modulo(m,n) = m - (floor(m,n) * n)
          //sería una unidad menor que la parte entera, ya que sería
          //negativo. Por tanto, esto es equivalente a:
          // modulo(m,n) / n < 0 = modulo(m,-n) + n 
          //
          // Por otra parte, el modulo siempre tiene el signo del divisor

        }
      }
      else{ // divisor negativo
        if( dividendo.esPositivo()){
          resultados = cpuVectorial_.divMP(dividendo.coefPoliB_, divisorCifra);

          cociente->coefPoliB_ = resultados.first;
          cociente->hacerNegativo();

          resto->coefPoliB_ = resultados.second;
          (*resto) += divisor; //ajuste por ser divisor negativo
          //El "floor" de la def del modulo(m,n) = m - (floor(m,n) * n)
          //sería una unidad menor que la parte entera, ya que sería
          //negativo. Por tanto, esto es equivalente a:
          // modulo(m,n) / n < 0 = modulo(m,-n) + n (esto seria una resta,
          // recordar que n es < 0 ).
          //
          // Por otra parte, el modulo siempre tiene el signo del divisor
        }
        else{ // dividendo negativo
          resultados = cpuVectorial_.divMP(dividendo.coefPoliB_, divisorCifra);

          cociente->coefPoliB_ = resultados.first;

          resto->coefPoliB_ = resultados.second[0];
          resto->hacerNegativo();
        }
      }

      return;
    }


  void divMod(const Z& dividendo, const Cifra divisor, Z* cociente, Z* resto)
    throw (Errores::DivisionPorCero)
    {


      if( divisor == 0 )
        throw Errores::DivisionPorCero();

      //por precaucion, no sea que se hayan pasado cosas ya trajinadas
      cociente->hacerPositivo();
      resto->hacerPositivo();

      std::pair< MiVec<Cifra>, MiVec<Cifra> > resultados;

      if( dividendo.esPositivo() ){
        resultados = cpuVectorial_.divMP(dividendo.coefPoliB_, divisor);

        cociente->coefPoliB_ = resultados.first;

        resto->coefPoliB_ = resultados.second;

      }
      else{ //dividendo < 0
        resultados = cpuVectorial_.divMP(dividendo.coefPoliB_, divisor);

        cociente->coefPoliB_ = resultados.first;
        cociente->hacerNegativo();

        resto->hacerNegativo();
        resto->coefPoliB_ = resultados.second;
        (*resto) += divisor; // ajuste por dividendo negativo
        //El "floor" de la def del modulo(m,n) = m - (floor(m,n) * n)
        //sería una unidad menor que la parte entera, ya que sería
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

  Cifra raizCuadrada(Cifra x)
  {
    if( (x == 1) || (x == 0 ) )
      return x;

    Cifra n = (x >> 1);
    Cifra y;

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
  size_t numBits(const Cifra x)
  {
    return cpuVectorial_.numBits(x);
  }
  size_t numBits(const CifraSigno x)
  {
    return cpuVectorial_.numBits((Cifra)labs(x));
  }

}
