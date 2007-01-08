/* 
 * $Id$
 */


#include "Potencia.h"
#include "Funciones.h"
#include "utils.h"

namespace numth{

  Z Potencia::potencia(Z base, CifraSigno exp)
  {
    this->potencia(&base, exp);
    return base;
  }

  Z PotModular::potModular(Z base, const Z& exp, const Z& mod)
  {
    this->potModular(&base, exp, mod);
    return base;
  }



  
  Z PotModular::inversa(const Z& base, const Z& mod)
  {
    Funciones funcs;

    Z inv;
    Z temp;
    if( !(funcs.getGCDExt()->gcdext(base, mod, inv, temp)).esUno() )
      throw Errores::ElementoNoInvertible();

    if( inv.signo() < 0 )
      inv += mod;

    return inv;
  }
  
  void PotVentanaDeslizante::potencia(Z* base, CifraSigno e)
  {
    if( e < 0 )
      throw Errores::ExponenteNegativo();

    if(e == 0){
      base->hacerUno();
      return;
    }

    if(e == 2){
      base->cuadrado();
      return;
    }

    Cifra k;
    size_t n = Z::convertir(e).numBits();

    //ver pagina 11 Cohen
    if( n <= 8 )
      k = 1;
    else if(n <= 24)
      k = 2;
    else 
      k = 3;

    //calculos previos
    Z g2(*base);
    g2.cuadrado();
    Cifra guarda = ( 1 << (k-1) ) - 1; // 2^{k-1} - 1
    std::vector<Z> ges(guarda+1); 

    // guarda >= 0 ; ges.size() >= 1
    ges.at(0) = *base; // g1

    if( guarda >= 1 ){ //ges.size() >= 2
      ges.at(1) = *base * g2;
      for(Cifra i = 2 ; i <= guarda; i++)
        ges.at(i) = ges.at(i - 1) * g2;
    }



    //  Z A; A.hacerUno();
    base->hacerUno();  
    long i = Z::convertir(e).numBits() - 1; // -1 por considerar el 0
    while(i >= 0){
      if( (e & (0x1 << i )) == 0 ){ // ¿ i-esimo bit == 0?
        base->cuadrado();
        i--;
      }
      else{ // i-esimo bit 1
        //obtenemos el intervalo de bits (acabado en 1) que nos conceda la ventana
        size_t indice=0;
        Cifra mask;
        long l;
        unsigned long cuadrados;
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
  
  void PotRightLeft::potencia(Z* base, CifraSigno exponente)
  {
    if( exponente < 0 )
      throw Errores::ExponenteNegativo();

    if( base == NULL )
      throw Errores::PunteroNulo();

    unsigned long doses = 0;
    Z acum;
    acum.hacerUno();

    //para trabajar con una base más pequeña => factores más pequeños
    //=> menor tiempo para las multiplicaciones. Obviamente luego se
    //vuelve a compensar esto con << doses
    while( base->esPar() ){
      doses++;
      base->operator>>=(1UL);
    }

    while( true ){
      if( exponente & 0x1 ){ // exponente impar
        acum *= (*base); 
        if(exponente == 0)
          break;
        base->cuadrado();  
      }
      else{ //exponente par
        if(exponente == 0)
          break;
        base->cuadrado();
      }
      exponente >>= 1;
    }

    if(doses){
      if( (Cifra)exponente > Constantes::SIZE_T_MAX/doses )
        throw Errores::DemasiadoGrande();
      acum <<= (exponente*doses);
    }

    base->operator=(acum); //FIXME

    return;
  }

  void PotMontgomery::potModular(Z* base, const Z& e, const Z& mod)
  {
    Funciones funcs;
    
    if( base == NULL )
      throw Errores::PunteroNulo();
    
    if( mod.esImpar()){ //modulo impar => montgomery
      Z R;  R.potenciaBase(mod.longitud());     
      Z R2; R2.potenciaBase(mod.longitud()*2); // R2 = R^2
      
      R %= mod;
      R2 %= mod;

      base->operator%=(mod);
      
      Z modPrima; 

      // modPrima = -mod^{-1} (mod base)
      modPrima = funcs.getMontgomeryReduction()->precomputaciones(mod); 
      
      Z xTilde(*base);
      montgomeryMult(&xTilde, R2,mod,modPrima ); // R2 = R^{2} mod n
      base->operator=(R); // R = R_inicial mod n

      for(long i = (e.numBits()-1); i >= 0 ; i--){
        montgomeryCuad(base, mod, modPrima);
        if( (e[(i / Constantes::BITS_EN_CIFRA)] & (1 << (i % Constantes::BITS_EN_CIFRA))) )
          //i-esimo bit de "e" es uno...
          montgomeryMult(base,xTilde, mod, modPrima);
      }

      Z uno; uno.hacerUno();

      montgomeryMult(base,uno,mod, modPrima);
    }
    else //modulo par => No puede aplicarse Montgomery
      throw Errores::ModuloParEnMontgomery();
    
    return;
  }

  void PotMontgomery::montgomeryMult(Z* x, const Z& y, const Z& mod, const Z& modPrima)
  {
    size_t n = mod.longitud() ; // exponente de R
    Z A; A.hacerCero(); 

    MiVec<Cifra> u(n);

    size_t i;

    for( i=0; i < x->longitud() ; i++){
      u[i] = ((A[0] + ((*x)[i]*y[0]))*modPrima)[0];
      A = ((A + ((*x)[i]*y) + (u[i]*mod)) >> Constantes::BITS_EN_CIFRA);
    }
    for( ; i < n ; i++){ // los x[i] serían 0
      u[i] = (A[0]*modPrima)[0];
      A += (u[i]*mod);
      A.divisionBase(1);
    }

    if( A >= mod )
      A -= mod;

    x->operator=(A);  // x·y·R^{-1} (mod mod)  /  R = base^{n}

  }

  void PotMontgomery::montgomeryCuad(Z* x, const Z& mod, const Z& modPrima)
  {
    //utilizar el metodo "clasico" (no modular) para cuadrado y luego
    //reducir con el metodo de reduccion de montgomery
    Funciones funcs;
    
    x->cuadrado();
    funcs.getMontgomeryReduction()->redMontgomery(x,mod, modPrima);

    return; 
    

  }





  
  void ClasicoConBarrett::potModular(Z* base, const Z& exp, const Z& mod)
  {
    if( base == NULL )
      throw Errores::PunteroNulo();

    Funciones funcs;
    RedBarrett* redbarrett = funcs.getBarrettReduction();
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

    for(long i = (e.numBits()-1); i >= 0 ; i--){
      base->cuadrado(); 
      redbarrett->redBarrett(base, mod, mu);
      if( (e[(i / Constantes::BITS_EN_CIFRA)] & (1 << (i % Constantes::BITS_EN_CIFRA))) ){ //si el i-esimo bit de "e" es uno...
        base->operator*=(valorInicial); 
        redbarrett->redBarrett(base, mod,mu);
      }
    }

    return;
  }

/**********************/
  
  void PotVentanaDeslizanteR::potenciaR(R* base, CifraSigno e)
  {
    if( e < 0 )
      throw Errores::NoImplementado();

    if(e == 0){
      base->hacerUno();
      return;
    }

    if(e == 2){
      base->cuadrado();
      return;
    }

    Cifra k;
    size_t n = Z::convertir(e).numBits();

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
    Cifra guarda = ( 1 << (k-1) ) - 1; // 2^{k-1} - 1
    std::vector<R> ges(guarda+1); 

    // guarda >= 0 ; ges.size() >= 1
    ges.at(0) = *base; // g1

    if( guarda >= 1 ){ //ges.size() >= 2
      ges.at(1) = *base * g2;
      for(Cifra i = 2 ; i <= guarda; i++)
        ges.at(i) = ges.at(i - 1) * g2;
    }



    //  Z A; A.hacerUno();
    base->hacerUno();  
    long i = Z::convertir(e).numBits() - 1; // -1 por considerar el 0
    while(i >= 0){
      if( (e & (0x1 << i )) == 0 ){ // ¿ i-esimo bit == 0?
        base->cuadrado();
        i--;
        base->normalizar();
      }
      else{ // i-esimo bit 1
        //obtenemos el intervalo de bits (acabado en 1) que nos conceda la ventana
        size_t indice=0;
        Cifra mask;
        long l;
        unsigned long cuadrados;
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
