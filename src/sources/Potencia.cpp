/* 
 * $Id$
 */


#include "Potencia.h"
#include "RedModular.h"
#include "Potencia.h"
#include "GCD.h"
#include "DigitUtils.h"
#include "BitChecker.h"
#include "ZM_n.h"
#include "SystemInfo.h"

#include <iostream>

namespace mpplas{

  Potencia::Potencia()
    : funcs(MethodsFactory::getInstance())
  {}

  Z Potencia::potencia(Z base, SignedDigit exp)
  {
    this->potencia(base, exp);
    return base;
  }



  PotModular::PotModular()
    : funcs(MethodsFactory::getInstance())
  {}

  Z PotModular::potModular(Z base, const Z& exp, const Z& mod)
  {
    this->potModular(&base, exp, mod);
    return base;
  }

  Z PotModular::inversa(const Z& base, const Z& mod) const {
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

    int i = getBitLength(e) - 1; // -1 por considerar el 0
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
    if( base == NULL ){
      throw Errors::PunteroNulo();
    }

    if( mod.esPar() ){ //modulo par => No puede aplicarse Montgomery
      throw Errors::ModuloParEnMontgomery();
    }

    
    ZM_n tmp(*base, mod);
    tmp ^= e;
    
    base->operator=(tmp.toZ());

    return;
  }


 ///////////////////////////////////
 
  void ClasicoConBarrett::potModular(Z* const base, const Z& exp, const Z& mod) {
    RedBarrett* redbarrett; funcs->getFunc(redbarrett);
    const Z mu(redbarrett->precomputaciones(mod));
    potModular(base, exp, mod, mu);
    return;
  }


  void ClasicoConBarrett::potModular(Z* const base, const Z& exp, const Z& mod, const Z& mu) const {
    if( base == NULL ){
      throw Errors::PunteroNulo();
    }

    RedBarrett* redbarrett; funcs->getFunc(redbarrett);
    bool eNegativo = false;

    if( *base >= mod){
      base->operator%=(mod);
    }

    Z e(exp);

    if( e.esNegativo() ){
      eNegativo = true;
      base->operator=(inversa(*base, mod));
      e.hacerPositivo();
    }

    Z valorInicial(*base);

    base->hacerUno();

    Utils::BitChecker bc(e);

    while( bc.hasPrevious() ){
      base->cuadrado();
      redbarrett->redBarrett(base, mod, mu);

      if( bc.checkPrevious() ){
        base->operator*=(valorInicial); 
        redbarrett->redBarrett(base, mod,mu);
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
    const size_t n = getBitLength(e);

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
    int i = getBitLength(e) - 1; // -1 por considerar el 0
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


//////////////////////////////////////////////////////////7

  void TwoThreadedModularExp::potModular(Z* const base, const Z& exp, const Z& mod){
    std::vector<size_t> diffsX;
    std::vector<size_t> diffsY;

    if( exp.esCero() ){
      base->hacerUno();
      return;
    }

    _getOnePartitions( exp, diffsX, diffsY );

    Z powOf2Exp;
    ZM_n tmpLeft(*base, mod);
    assert( diffsX.size() > 0 );
    tmpLeft ^= powOf2Exp.powerOfTwo(diffsX[0]);
    ZM_n left(tmpLeft); 

    ZM_n tmpRight(*base, mod);
    tmpRight.inverse();
    assert( diffsY.size() > 0 );
    tmpRight ^= powOf2Exp.powerOfTwo(diffsY[0]);
    ZM_n right(tmpRight);

#pragma omp parallel sections num_threads(2)
    {
#pragma omp section
      {
        for( int i =1 ; i < diffsX.size(); i++){
          tmpLeft ^= powOf2Exp.powerOfTwo(diffsX[i]);
          left *= tmpLeft;
        }
      }
#pragma omp section
      {
        for( int i =1 ; i < diffsY.size(); i++){
          tmpRight ^= powOf2Exp.powerOfTwo(diffsY[i]);
          right *= tmpRight;
        }
      }
    }

    left *= right;

    base->operator=(left.toZ());
  }
  
  void TwoThreadedModularExp::_getOnePartitions(const Z& e, 
       std::vector<size_t>& diffsX, 
       std::vector<size_t>& diffsY ){

    std::vector< std::pair<int, int> > xys;
    std::pair<int, int> xy;
    bool insideWin = false;
  
    Utils::BitChecker bc(e, true /* right to left */);
    while( bc.hasNext() ){
      if( bc.checkNext() ){
        if( !insideWin ){
          xy.second = bc.getPosition();
          insideWin = true;
        }
      } else if( insideWin ){
        //end of the window
        xy.first = bc.getPosition()-1;
        insideWin = false;
        xys.push_back(xy);
      }
    }
    if( insideWin ){
      xy.first = bc.getPosition();
      xys.push_back(xy);
    }

    assert( xys.size() > 0 );
    diffsX.push_back(xys[0].first + 1);
    for( int i = 1; i < xys.size(); i++ ){
      diffsX.push_back(xys[i].first - xys[i-1].first);
    }
    diffsY.push_back(xys[0].second );
    for( int i = 1; i < xys.size(); i++ ){
      diffsY.push_back(xys[i].second - xys[i-1].second);
    }

    return;
  }

  //////////////////////////////////////
  
  void MultiThreadedModularExp::potModular(Z* const base,
      const Z& exp, const Z& mod){
    std::vector< Z > sections;
    const size_t sectionSizes( _getExponentSections(exp, sections));

    ClasicoConBarrett potMod;
    const size_t numSects = sections.size();
    std::vector< Z > partialResults(numSects, *base);
    
    RedBarrett* redbarrett; funcs->getFunc(redbarrett);
    const Z mu(redbarrett->precomputaciones(mod));
#pragma omp parallel for shared(sections, partialResults, mod, potMod)
    for(int i = 0 ; i < numSects;  i++){
      sections[i] <<= (i*sectionSizes) ;
      potMod.potModular( &(partialResults[i]), sections[i], mod, mu);
    }


    *base = partialResults[0];

    for(int i = 1 ; i < numSects;  i++){
      (*base) *= partialResults[i];
    }

    (*base) %= mod;

  }


  
  size_t MultiThreadedModularExp::_getExponentSections(Z e, std::vector< Z >& sections){
    const size_t eBitLength = e.getBitLength();
    const size_t numThreads = SystemInfo::getMaxNumberOfThreads();
    const size_t a = (size_t)floor( eBitLength / (double)numThreads );
    const size_t aLast = eBitLength % numThreads;
    sections.reserve( numThreads );
    
    for(int i = 0; i < numThreads-1; i++){
      sections.push_back(e.getRightshiftedBits(a));
    }
    sections.push_back(e.getRightshiftedBits(a+aLast));
    return a;
  }

} //namespace mpplas
