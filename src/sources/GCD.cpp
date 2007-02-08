/* 
 * $Id$
 */


#include "GCD.h"
#include <cstdlib>

namespace numth{


  Z GCD::gcd(Z u, Cifra v)
  {
    if( u.esNegativo() )
      u.hacerPositivo();

    Cifra r;
    while( v != 0 ){
      r = (u % v)[0];
      u = v;
      v = r;
    }
    // v == 0
    return u;
  }

  Z GCD::gcd(Z u, CifraSigno v)
  {
    v = labs(v);
    return gcd(u, (Cifra)v);
  }
  
  
  Z GCDLehmer::gcd(Z u, Z v)
  {
    if( u.esNegativo() )
      u.hacerPositivo();
    if( v.esNegativo() )
      v.hacerPositivo();

    // "u" ha de ser >= que "v"
    if( u < v ){
      Z temp(u);
      u = v;
      v = temp;
    }

    Cifra uHat;
    Cifra vHat;
    CifraSigno A,B,C,D,T;
    Cifra q,q2;
    Cifra THat;
    Z t;
    Z w;
    Cifra uPrima;
    Cifra vPrima;
    Cifra uPrimaSegunda;
    Cifra vPrimaSegunda;


    while(true){
      if( v.longitud() == 1)
        return GCD::gcd(u,v[0]);
      else{
        size_t p = u.numBits() - Constantes::BITS_EN_CIFRA;
        uHat = (u >> p)[0];
        vHat = (v >> p)[0];

        A=1; B=0; C=0; D=1;

        while(true){
          uPrima = uHat + B;
          vPrima = vHat + D; /* OF! */ bool vPrimaOF = false;
          if( vPrima < vHat )
            vPrimaOF = true;

          uPrimaSegunda = uHat + A; /* OF! */ bool uPrimaSegundaOF = false;
          if( uPrima < uHat )  
            uPrimaSegundaOF = true;

          vPrimaSegunda = vHat + C;

          if( vPrima == 0 || vPrimaSegunda == 0)
            break;

          if ( vPrimaOF )
            q = 0; // el hecho de que el divisor sea mayor que la base 
                  //(en la que SI esta dividendo) implica necesariamente 
                  //que el floor del cociente es 0 
          else
            q = uPrima / vPrima;

          if( uPrimaSegundaOF ){
            if( vPrimaSegunda == 1 )
              break; 
              // ya que el cociente uPrimaSegunda / vPrimaSegunda 
              //seria igual a la base y dado que uPrima / vPrima es 
              //siempre < base, es imposible que sean  iguales 
            else{
              Z uZ = Z(Constantes::CIFRA_MAX); uZ++;
              q2 = (uZ/vPrimaSegunda)[0]; /* el resultado de esa div sera siempre < base
                                             ya que uZ == base y vPrimaSegunda > 1 */
            }
          }
          else
            q2 = uPrimaSegunda / vPrimaSegunda;

          if( q != q2 )
            break;
          else{
            T = A - q*C;
            A = C;
            C = T;

            T = B - q*D;
            B = D;
            D = T;

            THat = uHat - q*vHat;
            uHat = vHat;
            vHat = THat;
          }
        }
        // q != q2
        if( B == 0 ){
          t = u % v;
          u = v;
          v = t;
        }
        else{
          t = A*u;
          t += B*v;

          w = C*u;
          w += D*v;

          u = t;
          v = w;
        }
      }
    }
  }


  Z GCDExtBinario::gcdext(Z x, Z y, Z& C, Z& D)
  {
    Z A, B;

    bool xNegativo = false;
    bool yNegativo = false;
    
    if( x.esNegativo() ){
      xNegativo = true;
      x.hacerPositivo();
    }
    if( y.esNegativo() ){
      yNegativo = true;
      y.hacerPositivo();
    }

    unsigned long g; g = 0;
    while( x.esPar() && y.esPar() ){
      x >>= 1; // x = x/2;
      y >>= 1; // y = y/2;
      g++; 
    }

    Z u(x);
    Z v(y);

    A.hacerUno(); B.hacerCero(); C.hacerCero(); D.hacerUno();
    while( !u.esCero() ){
      while( u.esPar() ){
        u >>= 1;
        if( A.esPar() && B.esPar() ){
          A >>= 1;
          B >>= 1;
        }
        else{
          A += y; A >>= 1; // A = (A+y)/2;
          B -= x; B >>= 1; // B = (B-x)/2;
        }
      }
      while( v.esPar() ){
        v >>= 1;
        if( C.esPar() && D.esPar() ){
          C >>= 1;
          D >>= 1;
        }
        else{
          C += y; C >>= 1; // C = (C+y)/2;
          D -= x; D >>= 1; // D = (D-x)/2;
        }
      }
      if( u >= v ){
        u -= v;
        A -= C;
        B -= D;
      }
      else{
        v -= u;
        C -= A;
        D -= B;
      }
    }
    // aqui u == 0

    //para que todo funcione correctamente con negativos y se 
    //verifique la ecuacion gcd(x,y) = xC + yD
    if( xNegativo )
      C.cambiarSigno();
    if( yNegativo )
      D.cambiarSigno();

    return ( v <<= g );
  }

}
