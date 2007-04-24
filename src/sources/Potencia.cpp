/* 
 * $Id$
 */


#include "Potencia.h"
#include "RedModular.h"
#include "Potencia.h"
#include "GCD.h"
#include "DigitUtils.h"

namespace mpplas{

  Potencia::Potencia()
    : funcs(Funciones::getInstance())
  {}

  Z Potencia::potencia(Z base, SignedDigit exp)
  {
    this->potencia(base, exp);
    return base;
  }



  PotModular::PotModular()
    : funcs(Funciones::getInstance())
  {}

  Z PotModular::potModular(Z base, const Z& exp, const Z& mod)
  {
    this->potModular(&base, exp, mod);
    return base;
  }

  Z PotModular::inversa(const Z& base, const Z& mod)
  {
    Z inv;
    Z temp;
    GCDExt *gcdext; funcs->getFunc(gcdext);
    if( !(gcdext->gcdext(base, mod, inv, temp)).esUno() ){
      throw Errors::NonInvertibleElement();
    }

    if( inv.signo() < 0 ){
      inv += mod;
    }

    return inv;
  }
  



  ///////////////////////////////////////////////



  void PotVentanaDeslizante::potencia(Z* const base,const SignedDigit e)
  {
    if( e < 0 ){
      throw Errors::ExponenteNegativo();
    }

    if(e == 0){
      base->hacerUno();
      return;
    }

    if(e == 2){
      base->cuadrado();
      return;
    }

    Digit k;
    const size_t n = 1+(int)floor(log2(e)); 

    //ver pagina 11 Cohen
    if( n <= 8 ){
      k = 1;
    }
    else if(n <= 24){
      k = 2;
    }
    else {
      k = 3;
    }

    //calculos previos
    Z g2(*base);
    g2.cuadrado();
    Digit guarda = ( 1 << (k-1) ) - 1; // 2^{k-1} - 1
    std::vector<Z> ges(guarda+1); 

    // guarda >= 0 ; ges.size() >= 1
    ges.at(0) = *base; // g1

    if( guarda >= 1 ){ //ges.size() >= 2
      ges.at(1) = *base * g2;
      for(Digit i = 2 ; i <= guarda; i++)
        ges.at(i) = ges.at(i - 1) * g2;
    }



    //  Z A; A.hacerUno();
    base->hacerUno();  
    int i = numBits(e) - 1; // -1 por considerar el 0
    while(i >= 0){
      if( (e & (0x1 << i )) == 0 ){ // ¿ i-esimo bit == 0?
        base->cuadrado();
        i--;
      }
      else{ // i-esimo bit 1
        //obtenemos el intervalo de bits (acabado en 1) que nos conceda la ventana
        size_t indice=0;
        Digit mask;
        int l;
        size_t cuadrados;
        for( l = i+1-k; l <= i; l++){
          if( l < 0) {
            l = 0;
          }
          if( (e & (0x1 << l) ) ){ // sera cierto al menos cuando n == i
            //se extraen los bits del intervalo [i,l] y se meten en
            //"indice"
            mask = i - l + 1; mask = (0x1 << mask)-1; mask <<= l;
            indice = ((e & mask) >> l);
            break;
          }
        }

        cuadrados = (i - l + 1);
        if( !base->esUno() ){
          while(cuadrados){
            base->cuadrado();  
            cuadrados--;
          }
        }
        indice--; indice >>= 1;
        base->operator*=(ges[indice]);
        i = (l-1);
      }
    }
    return;
  }
  
  void PotLeftRight::potencia(Z* const base, SignedDigit exponente)
  {
    if( exponente < 0 ){
      throw Errors::ExponenteNegativo();
    }

    if( base == NULL ){
      throw Errors::PunteroNulo();
    }

    const int t = 1+(int)floor(log2(exponente));
    Z acum;
    acum.hacerUno();
    Digit mask;

    for(int i= t; i >= 0; i--){
      mask = 1 << i;
      acum.cuadrado();
      if( exponente & mask ){
        acum *= (*base);
      }
    }

    base->operator=(acum); //FIXME

    return;
  }

  void PotMontgomery::potModular(Z* const base, const Z& e, const Z& mod)
  {
    static const Digit BASEMASK = ((Digit)1) << (Constants::BITS_EN_CIFRA -1);
    
    if( base == NULL ){
      throw Errors::PunteroNulo();
    }

    if( mod.esPar() ){ //modulo par => No puede aplicarse Montgomery
      throw Errors::ModuloParEnMontgomery();
    }

    Z r;  r.potenciaBase(mod.longitud());     
    Z r2; r2.potenciaBase(mod.longitud()*2); // r2 = r^2
    
    r %= mod;
    r2 %= mod;

    base->operator%=(mod);
    
    Z modPrima; 

    // modPrima = -mod^{-1} (mod base)
    RedMontgomery *rm; funcs->getFunc(rm);
    modPrima = rm->precomputaciones(mod); 
    
    Z xTilde(*base);
    montgomeryMult(&xTilde, r2,mod,modPrima ); // r2 = r^{2} mod n
    base->operator=(r); // r = r_inicial mod n


    const int initialBitPos = (e.numBits()-1);
    int cifraPos = initialBitPos >> Constants::LOG_2_BITS_EN_CIFRA;
    Digit inDigitPosMask = 1;
    inDigitPosMask <<= ( initialBitPos & ((1<<Constants::LOG_2_BITS_EN_CIFRA)-1) ); //ie, i % BITS_EN_CIFRA
    for(int i = initialBitPos; i >= 0 ; i--){
      montgomeryCuad(base, mod, modPrima);
      if( (e[cifraPos] & inDigitPosMask ) ){ 
        //si el i-esimo bit de "e" es uno...
        montgomeryMult(base,xTilde, mod, modPrima);
      }
      inDigitPosMask >>= 1;
      if( !inDigitPosMask ){
        cifraPos--;
        inDigitPosMask = BASEMASK;
      }
    }

    Z uno; uno.hacerUno();

    montgomeryMult(base,uno,mod, modPrima);
    
    
    return;
  }

  void PotMontgomery::montgomeryMult(Z* const x, const Z& y, const Z& mod, const Z& modPrima)
  {
    size_t n = mod.longitud() ; // exponente de R
    Z A; A.hacerCero(); 

    MiVec<Digit> u(n);

    size_t i;

    for( i=0; i < x->longitud() ; i++){
      u[i] = ((A[0] + ((*x)[i]*y[0]))*modPrima)[0];
      A = ((A + ((*x)[i]*y) + (u[i]*mod)) >> Constants::BITS_EN_CIFRA);
    }
    for( ; i < n ; i++){ // los x[i] serían 0
      u[i] = (A[0]*modPrima)[0];
      A += (u[i]*mod);
      A.divisionBase(1);
    }

    if( A >= mod ){
      A -= mod;
    }

    x->operator=(A);  // x·y·R^{-1} (mod mod)  /  R = base^{n}

  }

  void PotMontgomery::montgomeryCuad(Z* const x, const Z& mod, const Z& modPrima)
  {
    //utilizar el metodo "clasico" (no modular) para cuadrado y luego
    //reducir con el metodo de reduccion de montgomery
    
    x->cuadrado();
    RedMontgomery* rm; funcs->getFunc(rm);
    rm->redMontgomery(x,mod, modPrima);

    return; 
  }

  Z PotMontgomery::montInverse(const Z&a, const Z& mod){
    Z r;
    Digit k;
    Z dummyOne((Digit)1);
    const Digit n = mod.numBits();
    const Digit m = mod.longitud() * Constants::BITS_EN_CIFRA;
    if( a.numBits() > m ){
      throw Errors::TooBig();
    }
    RedMontgomery *rm; funcs->getFunc(rm);
    const Z modPrima( rm->precomputaciones(mod) ); 
    almostMontgomeryInverse(a,mod, r, k);
    if( k > m ){
      montgomeryMult( &r, dummyOne, mod, modPrima);
      k -= m;
    }
    dummyOne <<= (m-k);
     montgomeryMult(&r, dummyOne, mod, modPrima);
    return r;
  }
   
  
  void PotMontgomery::almostMontgomeryInverse(
      const Z& a, const Z& mod, Z& r, Digit& k)
  {
    Z u(mod);
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
    if( r >= mod){
      r -= mod;
    }
    r  = mod -r;
    return;
  }
           
      

  

 ///////////////////////////////////
 
  void ClasicoConBarrett::potModular(Z* const base, const Z& exp, const Z& mod)
  {

    static const Digit BASEMASK = ((Digit)1) << (Constants::BITS_EN_CIFRA -1);

    if( base == NULL ){
      throw Errors::PunteroNulo();
    }

    RedBarrett* redbarrett; funcs->getFunc(redbarrett);
    bool eNegativo = false;
    base->operator%=(mod);
    Z mu = redbarrett->precomputaciones(mod);
    
    Z e(exp);

    if( e.esNegativo() ){
      eNegativo = true;
      base->operator=(inversa(*base, mod));
      e.hacerPositivo();
    }

    Z valorInicial(*base);

    base->hacerUno();

    const int initialBitPos = (e.numBits()-1);
    int cifraPos = initialBitPos >> Constants::LOG_2_BITS_EN_CIFRA;
    Digit inDigitPosMask = 1;
    inDigitPosMask <<= ( initialBitPos & ((1<<Constants::LOG_2_BITS_EN_CIFRA)-1) ); //ie, i % BITS_EN_CIFRA
    for(int i = initialBitPos; i >= 0 ; i--){
      base->cuadrado(); 
      redbarrett->redBarrett(base, mod, mu);
      
      if( (e[cifraPos] & inDigitPosMask ) ){ //si el i-esimo bit de "e" es uno...
        base->operator*=(valorInicial); 
        redbarrett->redBarrett(base, mod,mu);
      }
      inDigitPosMask >>= 1;
      if( !inDigitPosMask ){
        cifraPos--;
        inDigitPosMask = BASEMASK;
      }
    }

    return;
  }

/**********************/
  
  void PotVentanaDeslizanteR::potenciaR(R* base, SignedDigit e)
  {
    if( e < 0 )
      throw Errors::NoImplementado();

    if(e == 0){
      base->hacerUno();
      return;
    }

    if(e == 2){
      base->cuadrado();
      return;
    }

    Digit k;
    const size_t n = numBits(e);

    //ver pagina 11 Cohen
    if( n <= 8 )
      k = 1;
    else if(n <= 24)
      k = 2;
    else 
      k = 3;

    //calculos previos
    R g2(*base);
    g2.cuadrado();
    Digit guarda = ( 1 << (k-1) ) - 1; // 2^{k-1} - 1
    std::vector<R> ges(guarda+1); 

    // guarda >= 0 ; ges.size() >= 1
    ges.at(0) = *base; // g1

    if( guarda >= 1 ){ //ges.size() >= 2
      ges.at(1) = *base * g2;
      for(Digit i = 2 ; i <= guarda; i++)
        ges.at(i) = ges.at(i - 1) * g2;
    }



    //  Z A; A.hacerUno();
    base->hacerUno();  
    int i = numBits(e) - 1; // -1 por considerar el 0
    while(i >= 0){
      if( (e & (0x1 << i )) == 0 ){ // ¿ i-esimo bit == 0?
        base->cuadrado();
        i--;
        base->normalizar();
      }
      else{ // i-esimo bit 1
        //obtenemos el intervalo de bits (acabado en 1) que nos conceda la ventana
        size_t indice=0;
        Digit mask;
        int l;
        size_t cuadrados;
        for( l = i+1-k; l <= i; l++){
          if( l < 0) 
            l = 0;
          if( (e & (0x1 << l) ) ){ // sera cierto al menos cuando n == i
            //se extraen los bits del intervalo [i,l] y se meten en
            //"indice"
            mask = i - l + 1; mask = (0x1 << mask)-1; mask <<= l;
            indice = ((e & mask) >> l);
            break;
          }
        }

        cuadrados = (i - l + 1);
        if( !base->esUno() ){
          while(cuadrados){
            base->cuadrado();  
            cuadrados--;
          }
        }
        indice--; indice >>= 1;
        base->operator*=(ges[indice]);
        i = (l-1);
      }
    }
    return;
  }
}
