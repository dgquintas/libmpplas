/* 
 * $Id$ 
 */

#include "Trascendentes.h"
#include "MethodsFactory.h"
#include "Rx.h"
#include <cmath>

using namespace std;

namespace mpplas{

  R ExpTaylor::exponencial(const R& x)
  {
    R result, resultAntes;
    result.makeOne();
    R acum;
    acum.makeOne();


    if( x.exponente() == 0 ){
      result = this->e();
      result ^= x.mantisa();

      return result;
    }

    
    for(Digit i=1; ; i++ ){
      acum *= x;
      acum /= i;
      resultAntes = result;
      result += acum;
      if( result == resultAntes )
        break;
    }

    return result;
  }

  // vale pa algo esto? va ser que NO
  R ExpTaylor::e(void)
  {
    R result, resultAntes;
    result.makeOne();
    R acum;
    acum.makeOne();
    
    for(Digit i=1; ; i++ ){
      acum /= i;
      resultAntes = result;
      result += acum;
      if( result == resultAntes )
        break;
    }
    return result;
  }



  R LnTaylor::ln(const R& x)
  {
    if( x.isZero() )
      throw Errors::LogZero();

    //FIXME: a�adir soporte pa cuando x < 0 --> numeros complejos

    R result; result.makeZero();
    R dos;
    dos = R((Digit)2);

    if( x < dos ){
      R xMenosUno = x-1;
      R acum; 
      R resultAntes;

      /* ln(x) [ x > 0 ] = 2*( ((x-1)/(x+1) + (1/3)((x-1)/(x+1))^3 +
       * (1/5)....
       */
      R xMasUno = x + 1;
      acum = (xMenosUno/xMasUno);
      R xMenosUnoEntreXMasUno2= acum^2;

      Digit i;
      for(i=1; ; i+=2){
        resultAntes = result;
        result += (acum/i);
        if( resultAntes == result )
          break;

        acum *= xMenosUnoEntreXMasUno2;

      }
      result *= 2;
      return result;
    }
    else 
      if( x > dos ){ // x >= 2

        /* see written documentation for an in-depth discusion of this
         * 
         * Vale campeon, pero si cuando te tiras un moco como ese
         * despues lo escribe, bien. Pero es que ahora voy a tener que
         * volver a pensarlo porque, 15 dias despues, se me olvidaron
         * los "in-depth details"...
         * */
        int tamBits = x.floor().getBitLength();
        R f = x >> tamBits; // 0 < f <= 1
        R logDeF = this->ln(f); // logDeF <= 0
        result = (tamBits * this->ln2()) + logDeF;
        // Si x es un real, puede verse como  x = (m*10^n) + f  
        // en base 10, con m y n enteros
        // y f un real < 1. Pero tambi�n puede verse x como un entero
        // si, teniendo parte fraccionaria distinta de cero,
        // multiplicamos x por la potencia k-esima de la base de
        // represenacion en la que x nos venga dado, siendo k el
        // n�mero de posiciones decimales (fracionarias) de x. De
        // hecho, esto es lo que se hace para representar reales
        // utilizando solo enteros. En concreto, si la base es 2, 
        // x = m * 2^n con m y n enteros. 
        //
        //
        //  ln(x) = Ceil(ln(x)/ln(2)) + ln(f)
        //  x     =  2**   * f
        //
        // 
        // Entonces, Ln(x) = 
        //
        // 
        // Ln(x) = [ Ceil(Ln(x)/Ln(2)) * Ln(2) ] + Ln( Frac_2(x) ) 
        //
        // Frac_2(x) representa los digitos fraccionarios de x cuando
        // �ste se representa en base 2.
        return result;
      }
      else // x == 2
        return this->ln2();
  }

  R LnTaylor::ln2(void)
  {
    R xMenosUno; xMenosUno.makeOne();
    R acum; 
    R result; result.makeZero();
    R resultAntes;

    R xMasUno = R((Digit)3);
    acum = (xMenosUno/xMasUno);
    R xMenosUnoEntreXMasUno2= acum^2;

    Digit i;
    for(i=1; ; i+=2){
      resultAntes = result;
      result += (acum/i);
      if( resultAntes == result )
        break;
      acum *= xMenosUnoEntreXMasUno2;
    }

    result *= 2;
    return result;
  }

  R SenFase::seno(const R& x)
  {
    MethodsFactory *funcs = MethodsFactory::getInstance();
    Pi* pi; funcs->getFunc(pi);

    R piMedios = pi->pi();
    piMedios >>= 1;

    //FIXME: esto es una mierda que te cagas de ineficiente
    Cos* cos; funcs->getFunc(cos);
    return cos->coseno(piMedios - x);
  }
    


  R CosTaylor::coseno(const R& x)
  {
    MethodsFactory *funcs = MethodsFactory::getInstance();
    Pi* pi; funcs->getFunc(pi);

    int precVieja = R::precision();
    R::precision(2*precVieja);
    
    R DosPi = (pi->pi());
    DosPi <<= 1;
    Z cociente = (x / DosPi).floor();
    R xRed = x - (DosPi * R(cociente));
    
    R::precision(precVieja);
    
    R acum; acum.makeOne();
    R result,resultAntes; result.makeOne();
    R signo; signo.makeOne(); signo.invertSign();
    R xCuad = xRed^2;
    
    for(Digit i=1; ; i+=2 ){
      acum *= xCuad;
      acum /= i; acum /= (i+1);
      resultAntes = result;
      result += (acum * signo);
      if( result == resultAntes )
        break;
      signo.invertSign();
    }

    return result;
  }
  
  R ATanTaylor::arcotangente(const R& x)
  {
    R acum;
    R result,resultAntes; 
    
    //FIXME comprobar el valor absoluto de x
    if( x < R((Digit)1) ){
      acum = x;
      R signo; signo.makeOne(); signo.invertSign();
      R xCuad = x^2;
      result = x;

      for(Digit i=3; ; i+=2 ){
        acum *= xCuad;
        resultAntes = result;
        result += ((acum/i) * signo);
        if( result == resultAntes )
          break;
        signo.invertSign();
      }
      return result;
    }
    else{
      throw Errors::NotImplemented();
      return result;
    }
    
  }

  R PiMachin::pi(const int prec )
  {
    // We need to use the atan function. It suffices to use the
    // mclaurin expansion for |x| < 1, as both (1/5) and (1/239) are
    // less than 1.
    
    R result; 
    MethodsFactory *funcs = MethodsFactory::getInstance();
    ArcTan *arctan; funcs->getFunc(arctan);
    int precisionVieja=0;
    if( prec ){
      precisionVieja = R::precision();
      R::precision( (int)(prec * Constants::LOG_2_10) +1 );
    }
    R unQuinto; unQuinto.makeOne(); unQuinto /= 5;
    R un239avo; un239avo.makeOne(); un239avo /= 239;
 

    result = (4*arctan->arcotangente(unQuinto)) - arctan->arcotangente(un239avo);
    result <<= 2; // * 4

    //FIXME: esta precision deberia mantenerse, o guardarse dentro del R en si. 
    //porque luego, cuando se use el real que contiene a pi (el que se devuelve),
    //no se tiene acceso de forma directa a toda la precision con la que se esta trabajando 
    if(prec) 
      R::precision( precisionVieja );
    return result;
    
  }

  

  R SqrtNewton::sqrt(const R& A){
    static const int r = 4;
    static double precomps[] = { 1, 0.5, 0.375, 0.3125, 0.2734375, 0.24609375 };
    static const std::vector<mpplas::R> coeffs( precomps, precomps+r);

    static const mpplas::Rx P(coeffs);
    mpplas::R xn(1/std::sqrt(A.getSPApprox()));
    mpplas::R xn_1 = xn;
    xn.square();
    xn *= A;
    xn.invertSign();
    xn += mpplas::R::ONE;

    while(true){
      xn = P.evaluate(xn);
      xn *= xn_1;
      if( xn_1 == xn ) {
        break;
      }
      xn_1 = xn;
      //hn = 1-A*(xn.square());
      xn.square();
      xn *= A;
      xn.invertSign();
      xn += mpplas::R::ONE;
    }

    xn *= A;
    return xn;
  }

}
