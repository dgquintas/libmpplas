/* 
 * $Id$
 */


#include "Potencia.h"
#include "GCD.h"
#include "DigitUtils.h"
#include "ZM_n.h"
#include "SystemInfo.h"

#include <iostream>

namespace mpplas{

  template<typename T>
  T ExponentiationBase<T>::exponentiation(T base, const Z& exp) {
    this->exponentiation(&base, exp);
    return base;
  }


  Exponentiation<Z_n>::Exponentiation()
    : funcs(MethodsFactory::getReference())
  {}

  void Exponentiation<Z_n>::invert(Z_n* const base) const {
    invert(base, base->getMod());
    return;
  }
  Z_n Exponentiation<Z_n>::inverse(Z_n base) const {
    invert(&base);
    return base;
  }
 
  void Exponentiation<Z_n>::invert(Z* const base, const Z& mod) const{
    Z temp;
    if( !(Z::gcd(*base, mod, base, &temp)).esUno() ){
      throw Errors::NonInvertibleElement();
    }

    if( base->signo() < 0 ){
      (*base) += mod;
    }
  }

  Z Exponentiation<Z_n>::inverse(Z base, const Z& mod) const{
    invert(&base, mod);
    return base;
  }

  



  ///////////////////////////////////////////////



  void PotVentanaDeslizante::exponentiation(Z* const base,const Z& exp) {
    if( base == NULL ){
      throw Errors::PunteroNulo();
    }
    if( exp.isNegative() ){
      throw Errors::ExponenteNegativo();
    }
    if( exp.longitud() > 1 ){
      throw Errors::TooBig();
    }

    const Digit e( exp[0] );

    if(e == 0){
      base->hacerUno();
      return;
    }

    if(e == 2){
      base->cuadrado();
      return;
    }

    Digit k;
    const int n = 1+(int)floor(log2(e)); 

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
        int indice=0;
        Digit mask;
        int l;
        int cuadrados;
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
  
  void PotLeftRight::exponentiation(Z* const base, const Z& exp)
  {
    if( base == NULL ){
      throw Errors::PunteroNulo();
    }
    if( exp.isNegative() ){
      throw Errors::ExponenteNegativo();
    }
    if( exp.longitud() > 1 ){
      throw Errors::TooBig();
    }

    const Digit e( exp[0] );

    const int t = 1+(int)floor(log2(e));
    const Z orig(*base);
    base->hacerUno();
    Digit mask( ((Digit)1) << (t+1));

    for(int i= t; i >= 0; i--){
      mask >>= 1; // mask = 1 << i
      base->cuadrado();
      if( e & mask ){
        (*base) *= orig;
      }
    }

    return;
  }

  void PotMontgomery::exponentiation(Z_n* const base, const Z& e) {
    if( base == NULL ){
      throw Errors::PunteroNulo();
    }

    if( base->getMod().esPar() ){ //modulo par => No puede aplicarse Montgomery
      throw Errors::ModuloParEnMontgomery();
    }

    ZM_n tmp(*base);
    tmp ^= e;
    
    base->operator=(tmp.toZ());

    return;
  }


 ///////////////////////////////////
 
  ClasicoConBarrett::ClasicoConBarrett(){
    MethodsFactory::getReference().getFunc(redbarrett);
  }
 
  void ClasicoConBarrett::exponentiation(Z_n* const base, const Z& exp) { 
    if( base == NULL ){
      throw Errors::PunteroNulo();
    }
    const Z mu(redbarrett->precomputaciones(base->getMod()));
    barrettStep(base, exp, base->getMod(), mu);
    return;
  }


  void ClasicoConBarrett::barrettStep(Z* const base, const Z& exp, const Z& mod, const Z& mu) const {

    if( exp.isNegative() ){
      invert(base, mod);
    }
    const Z orig(*base);
    base->hacerUno();

    Utils::BitChecker bc(exp);

    while( bc.hasPrevious() ){
      base->cuadrado();
      redbarrett->redBarrett(base, mod, mu);

      if( bc.checkPrevious() ){
        base->operator*=(orig); 
        redbarrett->redBarrett(base, mod,mu);
      }
    }
    return;
  }


/**********************/
  
  void PotVentanaDeslizanteR::exponentiation(R* const base, const Z& exp) {
    if( base == NULL ){
      throw Errors::PunteroNulo("NULL pointer at R exponentiation");
    }
    if( exp.isNegative() ){
      throw Errors::NoImplementado("Negative exponentiation for R not yet implemented");
    }
    if( exp.longitud() > 1 ){
      throw Errors::TooBig("Exponent for exp. in R must be < max(Digit)");
    }

    const Digit e( exp[0] );

    if(e == 0){
      base->hacerUno();
      return;
    }

    if(e == 2){
      base->cuadrado();
      return;
    }

    Digit k;
    const int n = getBitLength(e);

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
    mpplas::MiVec<R> ges(guarda+1); 

    // guarda >= 0 ; ges.size() >= 1
    ges[0] = *base; // g1

    if( guarda >= 1 ){ //ges.size() >= 2
      ges[1] = *base * g2;
      for(Digit i = 2 ; i <= guarda; i++)
        ges[i] = ges[i - 1] * g2;
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
        int indice=0;
        Digit mask;
        int l;
        int cuadrados;
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

  void TwoThreadedModularExp::exponentiation(Z_n* const base, const Z& exp){
    std::vector<int> diffsX;
    std::vector<int> diffsY;

    if( exp.esCero() ){
      base->hacerUno();
      return;
    }

    _getOnePartitions( exp, diffsX, diffsY );

    Z powOf2Exp;
    ZM_n tmpLeft(*base);
    assert( diffsX.size() > 0 );
    tmpLeft ^= powOf2Exp.powerOfTwo(diffsX[0]);
    ZM_n left(tmpLeft); 

    ZM_n tmpRight(*base);
    tmpRight.inverse();
    assert( diffsY.size() > 0 );
    tmpRight ^= powOf2Exp.powerOfTwo(diffsY[0]);
    ZM_n right(tmpRight);

#pragma omp parallel sections num_threads(2) private(powOf2Exp)
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

    ((Z*)base)->operator=(left.toZ());
  }
  
  void TwoThreadedModularExp::_getOnePartitions(const Z& e, 
       std::vector<int>& diffsX, 
       std::vector<int>& diffsY ){

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
  
  void MultiThreadedModularExp::exponentiation(Z_n* const base, const Z& exp){
    std::vector< Z > sections;
    const int sectionSizes( _getExponentSections(exp, sections));

    ClasicoConBarrett potMod;
    const int numSects = sections.size();
    const Z& mod(base->getMod());
    
    RedBarrett* redbarrett; funcs.getFunc(redbarrett);
    const Z mu(redbarrett->precomputaciones(mod));
    Z partialAllTwos(*base);

    potMod.barrettStep( &partialAllTwos, Z::getPowerOfTwo(sectionSizes),mod, mu);
    mpplas::MiVec< Z > partialResults(numSects, partialAllTwos); //pos 0 wont ever be used
#pragma omp parallel for shared(sections, potMod,partialResults)
    for(int i = 0 ; i < numSects;  i++){
      if( i == 0 ){
        potMod.barrettStep( base, sections[0], mod, mu);
      }
      else{
        sections[i] <<= ((i-1)*sectionSizes) ;
        std::cout << "thread " << omp_get_thread_num() << " IN: " << sections[i].getBitLength() <<std::endl;
        potMod.barrettStep( &(partialResults[i]), sections[i], mod, mu);
      }
    }


    for(int i = 1 ; i < numSects;  i++){
      ((Z*)base)->operator*=(partialResults[i]);
    }
    ((Z*)base)->operator%=(mod);
  }


  
  int MultiThreadedModularExp::_getExponentSections(Z e, std::vector< Z >& sections){
    const int eBitLength = e.getBitLength();
    const int numThreads = SystemInfo::getMaxNumberOfThreads();
    const int a = (int)floor( eBitLength / (double)numThreads );
    const int aLast = eBitLength % numThreads;
    sections.reserve( numThreads );
    
    for(int i = 0; i < numThreads-1; i++){
      sections.push_back(e.getRightshiftedBits(a));
    }
    sections.push_back(e.getRightshiftedBits(a+aLast));
    return a;
  }







  void SqrAndMultGFExp::exponentiation(GF* const base, const Z& k){
    // k should verify 0 <= k < p^m-1 ; m = deg(fx)
    GF g(*base);
    base->makeOne();
    if( k.esCero() ){
      return;
    }
    if( k.isNegative() ){
      g.invert();
    }
    
    Utils::BitChecker bc(k, true);
    if( bc.checkNext() ){
      (*base) = g;

    }
    while( bc.hasNext() ){
      g.square();
      if( bc.checkNext() ){
        (*base) *= g;
      }
    }
    return;
  }


} //namespace mpplas
