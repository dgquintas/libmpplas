/* 
 * $Id$ 
 */

#include "SimbolosLegendre.h"
#include "Funciones.h"

namespace numth{

  Z SLegendreViaJacobi::simboloLegendre(Z a, Z p)
  {
    // NO se comprueba la primalidad de "p" por
    // cuestiones de eficiencia
    
    Funciones *funcs = Funciones::getInstance();
    SimboloJacobi *sJacobi; funcs->getFunc(sJacobi);
    return sJacobi->simboloJacobi(a,p);
  }

  
  Z SJacobiViaKronecker::simboloJacobi(Z a, Z b)
  {
    if( b.esPar() )
      throw Errores::ParEnSimboloJacobi();
   
    Funciones *funcs = Funciones::getInstance();
    
    SimboloKronecker *sKronecker; funcs->getFunc(sKronecker);
    return sKronecker->simboloKronecker(a,b);
  }
    
  SKroneckerCohen::SKroneckerCohen(void)
  {
    tabla[0] = (CifraSigno)0;
    tabla[1] = (CifraSigno)1;
    tabla[2] = (CifraSigno)0;
    tabla[3] = (CifraSigno)-1;
    tabla[4] = (CifraSigno)0;
    tabla[5] = (CifraSigno)-1;
    tabla[6] = (CifraSigno)0;
    tabla[7] = (CifraSigno)1;

    return;
  }

  Z SKroneckerCohen::simboloKronecker(Z a, Z b)
  {
    Z uno; uno.hacerUno();
    Z cero; cero.hacerCero();
    Z menosUno; menosUno.hacerUno(); menosUno.hacerNegativo();
    size_t v;
    CifraSigno k;
    Z r;
    
    if( b.esCero() )
      if( (a.abs()).esUno() )
        return uno;
      else // |a| != 1
        return cero;

    if( (a.esPar()) && (b.esPar()) )
      return cero;
    
    v = b.numDoses();
    b >>= v;

    if ( v & 0x1 ) //v impar
      k = tabla[(a[0])&0x7];
    else //v par
      k = 1;

    if( b.esNegativo() ){
      b.hacerPositivo();
      if( a.esNegativo() )
        k = -k;
    }

    while( !(a.esCero()) ){
      v = a.numDoses();
      a >>= v;
      if( v & 0x1 ) 
        k *= tabla[b[0] & 0x7];

      //reciprocidad
      if( a.esNegativo() ){
        Cifra aTemp = ~a[0]; //no hace falta sumarle 1 para completar la "complementacion a dos" 
                             //ya que el ...&0x2 no lo iba a tener en
                             //cuenta de todas formas
        if( aTemp & b[0] & 0x2 )
          k = -k;
      }
      else
        if( a[0] & b[0] & 0x2 )
          k = -k;

      r = a.abs();
      a = b % r;
      b = r;
    }
    // a es cero
    if ( b.esUno() )
      return Z(k);
    else // b > 1 , ya que b en este punto es impar y > 0 (cohen p. 29)
      return cero;
  }


}
