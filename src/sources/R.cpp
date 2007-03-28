/*
 * $Id$
 */

#include "R.h"
#include <inttypes.h>
#include "Funciones.h" 
#include "Potencia.h"

namespace mpplas{

  size_t R::precision_ = 300;
  size_t R::precisionSalida_ = 20;

  R::R() 
    : exponente_(0)  
  {
    mantisa_.hacerCero();
  }

  R::R( const R& otro)
    : exponente_(otro.exponente_), mantisa_(otro.mantisa_)
  {}

//  R R::convertir(const Cifra origen)
//  {
//    R temp(origen);
//    return temp;
//  }
//  R R::convertir(const CifraSigno origen)
//  {
//    R temp(origen);
//    return temp;
//  }
//  R R::convertir(const char* origen)
//  {
//    R temp(origen);
//    return temp;
//  } 
//  R R::convertir(const double origen)
//  {
//    R temp(origen);
//    return temp;
//  } 
//  R R::convertir(const Z& origen)
//  {
//    R temp(origen);
//    return temp;
//  } 

  R::R(const CifraSigno otro)
    : exponente_(0), mantisa_(otro)
  {
    normalizar();
  }

  R::R(const Cifra otro)
    : exponente_(0), mantisa_(otro)
  {
    normalizar();
  }

  R::R(const char* strC)
  {
    std::string temp(strC);
    std::istringstream flujoEntrada(temp);
    operator>>(flujoEntrada,*this);
    return;
  }

  R::R(double otro)
  {
    if(otro == 0){
      hacerCero();
      return;
    }

    if( otro == 1){
      hacerUno();
      return;
    }


    // La idea es la misma que cuando trabajamos con un char*
    double suelo;
    Cifra sueloEntero;
    Cifra sueloEnteroAlto = 0;
    Cifra sueloDecimal1 = 0;
    Cifra sueloDecimal2;
    Cifra potenciaInicial = (Cifra)pow(10.0,Constantes::MAX_EXP10_CIFRA);
    Cifra potenciaFinal;
    bool negativo = false;
    size_t cifrasEnteras = 0;

    if( otro < 0){
      negativo = true;
      otro *= -1;
    }

    suelo = std::floor(otro);
    if( suelo > Constantes::CIFRA_MAX ){ //"partir el suelo en 2"
      sueloEntero = (Cifra)std::fmod(suelo, potenciaInicial);
      cifrasEnteras += (Cifra)std::ceil(log10(sueloEntero));
      sueloEnteroAlto = (Cifra)(suelo / potenciaInicial);
      cifrasEnteras += (Cifra)std::ceil(log10(sueloEnteroAlto));
    }
    else{ //cabe todo en uno
      sueloEntero = (Cifra)suelo;
      cifrasEnteras += (Cifra)std::ceil(log10(sueloEntero));
    }

    otro -= suelo;

    int cifrasRestantes = (Constantes::MAX_EXP10_DOUBLE+2)-cifrasEnteras;

    if( cifrasRestantes > (long)Constantes::MAX_EXP10_CIFRA ){
      potenciaFinal = (Cifra)pow(10.0,Constantes::MAX_EXP10_CIFRA);
      otro *= potenciaFinal;
      suelo = std::floor(otro);
      otro -= suelo;
      sueloDecimal1 = (Cifra)suelo;

      cifrasRestantes -= Constantes::MAX_EXP10_CIFRA;
    }

    potenciaFinal = (Cifra)pow(10.0,cifrasRestantes);
    otro *= potenciaFinal;
    suelo = std::floor(otro);
    sueloDecimal2 = (Cifra)suelo;

    //FIXME: ESTO ES UNA GRAN CHAPUZA
    if(sueloDecimal2){
      this->operator=(sueloDecimal2);
      this->operator/=(R((CifraSigno)potenciaFinal));

      this->operator+=(R((CifraSigno)sueloDecimal1));
      this->operator/=(R((CifraSigno)potenciaInicial));
      this->operator+=(R((CifraSigno)sueloEntero));
    }
    else{
      this->operator=(sueloDecimal1);
      this->operator/=(R((CifraSigno)potenciaFinal));
      this->operator+=(R((CifraSigno)sueloEntero));
    }

    if(sueloEnteroAlto){
      this->operator/=(R((CifraSigno)potenciaInicial));
      this->operator+=(R((CifraSigno)sueloEnteroAlto));
      this->operator*=(R((CifraSigno)potenciaInicial));
    }

    if(negativo)
      cambiarSigno();

    normalizar();


    //  int exp;
    //  double frac;
    //  
    //  frac = frexp(otro, &exp);
    //  frac = ldexp(frac, BITS_EN_DOUBLE); 
    //  exp -= BITS_EN_DOUBLE;
    //
    //  mantisa_ = Z::convertir(frac); // atencion a conversion desde double a Z
    //  exponente_ = (long)exp;
    //  
    ///*  unsigned long k = R::precision_ - BITS_EN_DOUBLE;
    //  exponente_ -= k;
    //  mantisa_ <<= k;
    //*/  
    //  //Ahora habria que "poner ceros" hasta extendernos a la precision de
    //  //trabajo. Claro que esos ceros serian en base 10. 
    //  
    //  normalizar();
  }

  R::R( const Z& entero )
    : exponente_(0), mantisa_(entero)
  {
    normalizar();
  }

  R::~R()
  {
    //nada
  }

  R& R::operator=(const R& otro)
  {
    mantisa_ = otro.mantisa_;
    exponente_ = otro.exponente_;

    return *this;
  }

  R& R::operator+=(const R& otro)
  {
    unsigned long difTam = labs(mantisa_.numBits() - otro.mantisa_.numBits());

    //comprobamos si uno es "despreciable" frete al otro en funci�n de
    //si la diferencia de sus respectivos exponentes sobrepasa la
    //precisi�n de trabajo
    if( exponente_ > otro.exponente_ ){
      unsigned long difExp = exponente_ - otro.exponente_;
      if( difExp >= (R::precision_ + difTam)){
        // "otro" es mucho menor que "this" -> no se suma nada, ya que
        // de todas formas, lo ibamos a perder por precisi�n.
        return *this;
      }
      else{
        //equilibrar exponentes
        mantisa_ <<= difExp;
        exponente_ = otro.exponente_;
        mantisa_ += otro.mantisa_;
        normalizar();
        return *this;
      }
    }

    if( exponente_ < otro.exponente_ ){
      unsigned long difExp = otro.exponente_ - exponente_;
      if( difExp >= (R::precision_ + difTam)){
        // "this" es mucho menor que "otro" -> no se suma nada, ya que
        // de todas formas, lo ibamos a perder por precisi�n.
        // En este caso, esto supone que "this" pasa a ser "otro"
        this->operator=(otro);
        return *this;
      }
      else{
        //equilibrar exponentes
        Z temp(otro.mantisa_); //ya que "otro" es const
        temp <<= difExp;
        mantisa_ += temp;
        normalizar();
        return *this;
      }
    }
    //si estamos aqui, es que los exponentes son iguales.
    //Se suman las mantisas.
    mantisa_ += otro.mantisa_;
    normalizar();

    return *this;

  }

  R& R::operator-=(const R& otro)
  {
    unsigned long difTam = labs(mantisa_.numBits() - otro.mantisa_.numBits());

    //comprobamos si uno es "despreciable" frete al otro en funci�n de
    //si la diferencia de sus respectivos exponentes sobrepasa la
    //precisi�n de trabajo
    if( exponente_ > otro.exponente_ ){
      unsigned long difExp = exponente_ - otro.exponente_;
      if( difExp >= (R::precision_ + difTam)){
        // "otro" es mucho menor que "this" -> no se resta nada, ya que
        // de todas formas, lo ibamos a perder por precisi�n.
        return *this;
      }
      else{
        //equilibrar exponentes
        mantisa_ <<= difExp;
        exponente_ = otro.exponente_;
        mantisa_ -= otro.mantisa_;
        normalizar();
        return *this;
      }
    }

    if( exponente_ < otro.exponente_ ){
      unsigned long difExp = otro.exponente_ - exponente_;
      if( difExp >= (R::precision_ + difTam) ){
        // "this" es mucho menor que "otro" -> no se resta nada, ya que
        // de todas formas, lo ibamos a perder por precisi�n.
        // En este caso, esto supone que "this" pasa a ser "otro" con
        // cambio de signo.
        this->operator=(otro);
        mantisa_.cambiarSigno();
        return *this;
      }
      else{
        //equilibrar exponentes
        Z temp(otro.mantisa_); //ya que "otro" es const
        temp <<= difExp;
        mantisa_ -= temp;
        normalizar();
        return *this;
      }
    }
    //si estamos aqui, es que los exponentes son iguales.
    //Se suman las mantisas.
    mantisa_ -= otro.mantisa_;
    normalizar();

    return *this;

  }



  R& R::operator*=(const R& otro)
  {
    mantisa_ *= otro.mantisa_;
    exponente_ += otro.exponente_;

    normalizar();

    return *this;
  }

  R& R::operator/=(const R& otro)
  {
    if( otro.esCero() )
      throw Errores::DivisionPorCero();

    long k = precision_ - mantisa_.numBits() + otro.mantisa_.numBits() -1;
    k = k < 0 ? 0 : k ;

    mantisa_ <<= k ;
    mantisa_ /= otro.mantisa_;

    exponente_ = exponente_ - k - otro.exponente_;

    normalizar();

    return *this;  
  }

  R& R::operator+=(const double corto)
  {
    R realDouble(corto);
    this->operator+=(realDouble);

    return *this;
  }


  /************/
  R& R::operator-=(const double corto)
  {
    R realDouble(corto);
    this->operator-=(realDouble);

    return *this;
  }

  R& R::operator*=(const double corto)
  {
    R realDouble(corto);
    this->operator*=(realDouble);

    return *this;
  }

  R& R::operator/=(const double corto)
  {
    R realDouble(corto);
    this->operator/=(realDouble);

    return *this;
  }

  //R& R::operator%=(const double corto)
  //{
  //  R realDouble(corto);
  //  this->operator%=(realDouble);
  //
  //  return *this;
  //}

  R& R::operator^=(CifraSigno exponente)
  {
    //  mantisa_ ^= exponente;
    //  exponente_ *= exponente;

    Funciones *funcs = Funciones::getInstance();
    PotenciaR *potR; funcs->getFunc(potR);
      
    potR->potenciaR(this, exponente);

    normalizar();

    return *this;
  }

  R& R::operator^=(const Z& exp)
  {
    if( exp.longitud() > 1 )
      throw Errores::DemasiadoGrande();

    Cifra exponente = exp[0];

    return operator^=(exponente);

  }


  R& R::cuadrado(void)
  {
    mantisa_.cuadrado();
    exponente_ <<= 1;

    normalizar();

    return *this;
  }

  R& R::operator>>=(const size_t n)
  {
    if( n > Cifra(Constantes::CIFRASIGNO_MAX) )
      throw Errores::OverflowExpReales();

    if( exponente_ - (CifraSigno)n > exponente_ )
      throw Errores::OverflowExpReales();

    exponente_ -= n;

    normalizar();

    return *this;
  }

  std::string R::toString(void) const {
    std::ostringstream oss;
    oss << *this;

    return oss.str().c_str();
  }


  R& R::operator<<=(const size_t n)
  {
    if( n > Cifra(Constantes::CIFRASIGNO_MAX) )
      throw Errores::OverflowExpReales();

    if( exponente_ + (CifraSigno)n < exponente_ )
      throw Errores::OverflowExpReales();

    exponente_ += n;

    normalizar();

    return *this;
  }


  bool R::operator>(const R& der) const
  {
    if( (signo() > 0) && (der.signo() < 0) )
      return true;
    if( (signo() < 0) && (der.signo() > 0) )
      return false;

    // se pasa de la casuistica de signos porque ya se encarga de ella
    // la comparaci�n de Z subyacente
    //  if( (signo() > 0) && (der.signo() > 0) ){
    if( exponente_ > der.exponente_ ){
      Z mantTemp(mantisa_);
      mantTemp <<= (exponente_ - der.exponente_);
      return (mantTemp > der.mantisa_);
    }
    else // exponente_ <= der.exponente 
      if( exponente_ < der.exponente_ ){
        Z mantTemp(der.mantisa_);
        mantTemp <<= (der.exponente_ - exponente_);
        return (mantisa_ > mantTemp);
      }
      else // exponentes iguales
        return (mantisa_ > der.mantisa_);
    //  }
    //  if( (signo() < 0) && (der.signo() < 0) ){
    //    if( exponente_ > der.exponente_ ){
    //      Z mantTemp(mantisa_);
    //      mantTemp <<= (exponente_ - der.exponente_);
    //      return (mantTemp > der.mantisa_);
    //    }
    //    else // exponente_ <= der.exponente 
    //      if( exponente_ < der.exponente_ ){
    //        Z mantTemp(der.mantisa_);
    //        mantTemp <<= (der.exponente_ - exponente_);
    //        return (mantisa_ > mantTemp);
    //      }
    //      else // exponentes iguales
    //        return (mantisa_ > der.mantisa_);
    //
  }   

  bool R::operator==(const R& der) const
  {
    if( exponente_ != der.exponente_ )
      return false;
    else
      return (mantisa_ == der.mantisa_);
  }

  bool R::operator!=(const R& der) const
  {
    return !operator==(der);
  }

  bool R::operator<(const R& der) const
  {
    if( operator>(der) )
      return false;

    if( operator==(der) )
      return false;

    return true;
  }


  bool R::operator>=(const R& der) const
  {
    if( operator<(der) )
      return false;

    return true;
  }

  bool R::operator<=(const R& der) const
  {
    if( operator>(der) )
      return false;

    return true;
  }


  void R::hacerCero(void)
  {
    exponente_ = 0;
    mantisa_.hacerCero();
    return;
  }

  void R::hacerUno(void)
  {
    exponente_ = 0;
    mantisa_.hacerUno();
    return;
  }

  bool R::esCero(void) const
  {
    if( mantisa_.esCero() && exponente_ == 0 )
      return true;
    else
      return false;
  }

  bool R::esUno(void) const
  {
    if( mantisa_.esUno() && exponente_ == 0 )
      return true;
    else
      return false;
  }



  Z R::floor(void) const
  {
    if( exponente_ == 0 )
      return mantisa_;

    if( exponente_ > 0 ){
      Z temp(mantisa_);
      temp <<= exponente_;
      return temp;
    }

    //exponente_ < 0
    if( signo() >= 0 ){
      if( mantisa_.numBits() <= (unsigned long)labs(exponente_) ){ //FIXME
        //"no hay nada" por delante del . 
        Z cero;
        cero.hacerCero();    
        return cero;
      }
      else{
        Z temp(mantisa_);
        temp >>= labs(exponente_);
        return temp;
      }
    }
    //  signo() < 0 
    if( mantisa_.numBits() <= (unsigned long)labs(exponente_)){ //FIXME
      //"no hay nada" por delante del . 
      Z menosUno;
      menosUno.hacerUno();
      menosUno.cambiarSigno();
      return menosUno;
    }
    else{
      Z temp(mantisa_);
      temp >>= labs(exponente_);
      Z uno; 
      uno.hacerUno();
      temp -= uno;
      return Z(temp);
    }
  }

  Z R::ceil(void) const
  {
    if( exponente_ == 0 )
      return mantisa_;

    if( exponente_ > 0 ){
      Z temp(mantisa_);
      temp <<= exponente_;
      return temp;
    }

    //exponente_ < 0
    if( signo() >= 0 ){
      if( mantisa_.numBits() <= (unsigned long)labs(exponente_) ){ //FIXME
        //"no hay nada" por delante del . 
        Z uno;
        uno.hacerUno();
        return uno;
      }
      else{ 
        Z temp(mantisa_);
        temp >>= labs(exponente_);
        Z uno; 
        uno.hacerUno();
        temp += uno;
        return temp;
      }
    }
    //  signo() < 0 
    if( mantisa_.numBits() <= (unsigned long)labs(exponente_)){
      //"no hay nada" por delante del . 
      Z cero;
      cero.hacerCero();
      return cero;
    }
    else{
      Z temp(mantisa_);
      temp >>= labs(exponente_);
      return Z(temp);
    }
  }

  void R::normalizar(size_t nprec)
  {
    if( mantisa_.esCero() ){
      exponente_ = 0; //hacer que la representacion del 0 real sea �nica.
      return;
    }

    //comprobar la precision
    size_t tam = mantisa_.numBits();
    long exceso = tam - nprec -1; // el -1 es para que no se traten de redondear 
    // numeros del estilo (2^n)-1 (todos
    // 1's) que harian que cosas como
    // sacar 1.999 con 3 digitos frac. de
    // prec. de salida salieran mal.

    if( exceso > 0 ){
      CifraSigno correccion = mantisa_.redondear(exceso);
      mantisa_ >>= exceso;
      mantisa_ += correccion;
      exponente_ += exceso;
    }

    //quitar doses de la mantisa
    size_t doses = mantisa_.numDoses();  
    mantisa_ >>= doses;  

    exponente_ += doses;


    return;
  }

  R operator+(R izq, const R& der)
  {
    izq += der;
    return izq;
  }

  R operator-(R izq, const R& der)
  {
    izq -= der;
    return izq;
  }

  R operator*(R izq, const R& der)
  {
    izq *= der;
    return izq;
  }

  R operator/(R izq, const R& der)
  {
    if( der.esCero() )
      throw Errores::DivisionPorCero();

    izq /= der;
    return izq;
  }

  R operator+(const double corto, R largo)
  {
    largo += corto;
    return largo;
  }
  R operator-(const double corto, R largo)
  {
    largo -= corto;
    largo.cambiarSigno();
    return largo;
  }
  R operator*(const double corto, R largo)
  {
    largo *= corto;
    return largo;
  }

  R operator/(const double corto, const R& largo)
  {
    if( largo.esCero() )
      throw Errores::DivisionPorCero();

    if( largo > R(corto)) { //FIXME
      R cero;
      cero.hacerCero();
      return cero;
    }
    else 
      if( largo < R(corto) ){ //FIXME
        R cociente = corto / largo;
        return cociente;
      }
      else{ //iguales
        R uno;
        uno.hacerUno();
        return uno;
      }
  }

  //R mpplas::operator%(const double corto, const R& largo)
  //{
  //  if( largo.esCero() )
  //    throw Errores::DivisionPorCero();
  //
  //  if( largo > corto ){
  //    return R::convertir(corto);
  //  }
  //  else 
  //  if( largo < corto ){
  //    R resto = corto % largo;
  //    return resto;
  //  }
  //  else{ //iguales
  //    R cero;
  //    cero.hacerCero();
  //    return cero;
  //  }
  //}
  //
  R operator+(R largo, const double corto)
  {
    largo += corto;
    return largo;
  }
  R operator-(R largo, const double corto)
  {
    largo -= corto;
    return largo;
  }
  R operator*(R largo, const double corto)
  {
    largo *= corto;
    return largo;
  }
  R operator/(R largo, const double corto)
  {
    if( corto == 0 )
      throw Errores::DivisionPorCero();

    largo /= corto;
    return largo;
  }
  //R mpplas::operator%(R largo, const double corto)
  //{
  //  if( corto == 0 )
  //    throw Errores::DivisionPorCero();
  //
  //  largo %= corto;
  //  return largo;
  //}





  std::ostream& 
    operator<<(std::ostream& out, R numero)
    {
      //  ____________________________     _____
      // |_kb_|__32b__|__32b__|__32b__|   |_exp_|   
      //                                    ^^^
      //  <----- l bits ---> < k bits->   valor -k    
      //  p ej.             ^
      //  La posicion del "punto binario" seria la indicada.
      //  Asi que separo en un Z los "l" bits indicados y eso se
      //  interpreta por operator<< de salida de Z.
      //  Para los "k" bits "fraccionarios" se aplica el proceso sgte:
      //  
      //  (.u-1 u-2 u-3 ... u-p) con "p" la precision;
      //  u-1 = floor(u*10)
      //  u-2 = floor({u*10}*10)
      //  u-3 = floor({{u*10}*10}*10)
      //  ...
      //
      //  con {k} = k - floor(k); esto es, la parte fraccionaria

      Z entero;
      Z enteroAux;

      std::ostringstream oss;


      if(numero.signo() < 0){
        numero.cambiarSigno();
        oss << "-";
      }

      if( numero.exponente_ >= 0 ){
        size_t limitePrec = (size_t)floor(R::precision() / Constantes::LOG_2_10);
        size_t precEntAntigua = Z::precisionSalida();
        Z::precisionSalida(limitePrec);
        oss << (numero.mantisa_ << (size_t)numero.exponente_ );
        Z::precisionSalida(precEntAntigua);
  
        out << oss.str();
        return out;
      }

      R numeroRed(numero);

      entero = numero.floor();
      //out << entero ;
      numero -= R(entero);

      //  if( R::precisionSalida() > 0 ){ //FIXME: forzar q siempre lo sea

      //    out << "." ;

      size_t precisionUsada;
      size_t limitePrec = 
        (size_t)floor((R::precision()-entero.numBits()) / Constantes::LOG_2_10);
      if( (limitePrec < R::precisionSalida()) ){
        precisionUsada = limitePrec;
        // limitePrec < R::precisionSalida. Es decir, la precision
        // de salida es mayor que la que se puede conseguir con la
        // precision interna del n�mero: se producirian digitos no
        // exactos

        oss << "~";
      }
      else
        precisionUsada = R::precisionSalida();

      R redondeo;
      redondeo.hacerUno();

      for(size_t i = 0; i < precisionUsada; i++){
        numero *= (Cifra)10;  
        entero = numero.floor();  
        numero -= R(entero);  
        redondeo /= (Cifra)10;  
      }

      numero *= (Cifra)10;
      entero = numero.floor();  

      if( entero > (Cifra)5)
        numeroRed += redondeo;
      else //entero == 5
        if( entero == (Cifra)5 )
          if( entero.esImpar() ) 
            numeroRed += redondeo;

      entero = numeroRed.floor();
      //    size_t precEntAntigua = Z::precisionSalida();
      //    Z::precisionSalida(limitePrec);
      oss << entero ;
      //    Z::precisionSalida(precEntAntigua);
      numeroRed -= R(entero);
      oss << "." ;
      for(size_t i = 0; i < precisionUsada; i++){
        //FIXME: se puede hacer que, tras haber sacado cant_cifras_frac % max_pot_9_en_long,
        //se saquen los numeros de 10^(max_pot_9_en_long) en idem como con los Z
        numeroRed *= (Cifra)10;
        entero = numeroRed.floor();
        oss << entero ;
        numeroRed -= R(entero);
      }
      //	}

      out << oss.str();
      return out;
    }

  void _parseNumber( std::istream &in, R& res, bool decimalPart ){
    static Cifra const potenciaInicial = (Cifra)pow(10.0,Constantes::MAX_EXP10_CIFRA);
    char c;
    Cifra n = 0;
    int numDigits = 0;
    res.hacerCero();

    while( in.get(c) ) {
      if( std::isdigit(c) ) {
        n *= 10;
        ++numDigits;
        n += c - '0';  //FIXME: is this portable?
        if( numDigits >= Constantes::MAX_EXP10_CIFRA ){ //shouldn't ever be >
          //put into the number to return
          if( decimalPart ){
            res += n;
            res /= potenciaInicial;
          }
          else{ //still on the "integer" part
            res *= potenciaInicial;
            res += n;
          }
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
      if( decimalPart ){
        res += n;
        res /= (Cifra)pow(10.0,numDigits);
      }
      else{ //still on the "integer" part
        res *= (Cifra)pow(10.0,numDigits);
        res += n;
      }
    }


  
    return;
  }


  std::istream& 
    operator>>(std::istream& in, R& numero) 
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

      //_parseNumber(in, numero, false);
      Z integer;
      in >> integer;
      //was the offending character a dot?
      in.get(c);
      if( c != '.' ){
        throw Errores::InvalidSymbol(std::string(1,c));
      }
      else{ //somewhat redundant: would have left the function by the throw already
        _parseNumber(in, numero, true);
      }
      
      numero += R(integer);

      if( negative ){
        numero.cambiarSigno();
      }

      numero.normalizar();
      return in;
    }





  R operator-(R real)
  {
    real.cambiarSigno();
    return real;
  }

  R operator^(R base, const Z& exp)
  {
    if( exp.longitud() > 1 )
      throw Errores::DemasiadoGrande();

    base ^= exp;
    return base;
  }

  R operator^(R base, CifraSigno exp)
  {
    base ^= exp;
    return base;
  }

  R operator>>(R real, const size_t n)
  {
    real >>= n;
    return real;
  }

  R operator<<(R real, const size_t n)
  {
    real <<= n;
    return real;
  }
  }
