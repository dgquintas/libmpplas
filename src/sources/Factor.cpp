/* 
 * $Id$
 */


#include <set> //para set de metodo SQUFOF
#include "Factor.h"
#include "Functions.h"
#include "constants.h"
#include "Primos.h"
#include "GCD.h"
#include "RedModular.h"

namespace mpplas{

  MiVec<Z> CadenaAlgFactor::factoriza(const Z& n)
  {
    Functions* const funcs = Functions::getInstance();
    TestPrimoProb* test; funcs->getFunc(test);
    MiVec<Z> factores; factores.clear();
    Trial trial;
    RhoPollard rho;
//    SQUFOF squfof;
    Z num(n);

    Z factor;
    if( !test->esPrimo(num) ){
      if( !trial.factorZ(&num,&factores) ){ // si el trial no ha factorizado por completo...
//        if(!squfof.factorZ(&num, &factores)){
          if( !rho.factorZ(&num,&factores) )
           ; //pondriase aqui lo siguiente a probar si lo hubiera
        }
 //     }
    }
    else // es primo
      factores.push_back(num);

    return factores;
  }  

  //  bool RhoPollard::factorZ(Z* n, MiVec<Z>* factores)
  //  {
  //    Functions funcs;
  //    RedBarrett* reduccion = funcs.getBarrettReduction();
  //    Z mu = reduccion->precomputaciones(*n);
  //    GCD* gcd = funcs.getGCD();
  ////    TestPrimoProb* test = funcs.getTestPrimoProb();
  //
  //    Z y, x, x1;
  //    size_t k, l, c;
  //    Z P;
  //    Z g;
  //
  //    y = Z::convertir((Digit)2);
  //    x = Z::convertir((Digit)2);
  //    x1 = Z::convertir((Digit)2);
  // 
  //    k = 1; l = 1; c= 0;
  //    P.hacerUno();
  //
  //p2:
  //    x.cuadrado(); x++;
  //    P *= (x1-x) % (*n);
  //    c++;
  //    if ( c == 20 ){
  //      g = gcd->gcd(P, *n);
  //      if ( g > (Digit)1 )
  //        goto p4;
  //      else{
  //        y = x;
  //        c = 0;
  //      }
  //    }
  //
  //    k--;
  //    if( k )
  //      goto p2;
  //    g = gcd->gcd(P, *n);
  //    if ( g > (Digit)1 )
  //      goto p4;
  //    else{
  //      x1 = x;
  //      k = l;
  //      l = 2*l;
  //      for(size_t i = 0; i < k; i++){
  //        x.cuadrado(); x++;
  //        reduccion->redBarrett(&x, *n, mu);
  //      }
  //      y = x; 
  //      c = 0;
  //      goto p2;
  //    }
  //  
  //p4:
  //    do{
  //      y.cuadrado(); y++;
  //      reduccion->redBarrett(&y, *n, mu);
  //      g = gcd->gcd(x1-y, *n);
  //    } while( g == (Digit)1);
  //
  //    if( g < (*n ))
  //      factores->push_back(g);
  //    else
  //      assert(false);
  //
  //    return true;
  //  }


//  void SQUFOF::reduccionRho(Z& A, Z& B, Z& C, const Z& D, const Z& d)
//  {
//    Z c, r;
//
//    c = abs(C);
//    if (c < (d >> 1)){ // c < sqrt(D) / 2
//      r = -B;
//      r += ( (c << 1) * ((B + d) / (c << 1)) );
//    }
//    else{
//      r = -B;
//      r += (c << 1);
//    }
//    A = C;
//    B = r;
//    C = (r.cuadrado() - D) / ( C << 2 ); // C = (r^2 - D)/(4C)
//
//    return;
//  }
//
//  void SQUFOF::reducir(Z& A, Z& B, Z& C, const Z& D, const Z& d)
//  {
//    Z c;
//    c = abs(C);
//
//    if (B < (Digit)0){
//      B.cambiarSigno();
//      A.cambiarSigno();
//      C.cambiarSigno();
//    }
//    
//    while ( (B <= abs(d - (abs(A) << 1))) || (B > d) ) {
//      // pag 257 cohen, def 5.6.2  (negada por el while)
//      if (B < (Digit)0){
//        B.cambiarSigno();
//        A.cambiarSigno();
//        C.cambiarSigno();
//      }
//      reduccionRho(A,B,C,D,d);
//    }
//
//    return;
//  }
//
//  bool SQUFOF::factorZ(Z* n, MiVec<Z>* factores)
//  {
//
//    if( n == NULL )
//      throw Errors::PunteroNulo();
//    if( factores == NULL )
//      throw Errors::PunteroNulo();
//
//    
//    // pag 430 cohen
//    Functions funcs;
//    GCD* gcd = funcs.getGCD();
//    TestPrimoProb* test = funcs.getTestPrimoProb();
//
//    Z D,d,L; // d = sqrt(D) , L = sqrt(d) = sqrt(sqrt(D))
//    Z a,b,c; //representacion de la forma cuadratica f = (a,b,c)
//    Z A,B,C; //representacion de la forma cuadratica f = (A,B,C)
//    std::set<Z> Q; 
//    Z raiz;
//    bool factorCuadrado=false;
//    MiVec<Z>::iterator it; //para guardar la posicion a partir de la cual se iran añadiendo
//                           //factores para el caso en el que se
//                           //detecta un cuadrado perfecto y luego hay
//                           //que duplicar los primos de la factorización
//                           //de éste
//      
//    for(size_t iteraciones = 0; iteraciones < Constants::COTA_FACTORIZACION_SQUFOF; iteraciones++){
//      //1
//      if( test->esPrimo(*n) ){
//        factores->push_back(*n);
//        return true;
//      }
//
//      //2
//      Z raiz;
//      if( n->esCuadrado(&raiz) ){
//        //para recordar que hay que duplicar los factores primos que
//        //salgan de la raiz
//        factorCuadrado=true;                 
//        it = factores->end();
//        (*n) = raiz;
//      }
//
//      //3
//      D = (*n);
//      if( ((*n)[0] & 0x3) == 1 ){ // n = 1 (mod 4)
//        // D = n
//        d = raizCuadrada(D);
//        b = d; b--; b[0] &= (Constants::CIFRA_MAX-1); b++; // b = 2*floor((d-1)/2) + 1
//                  //^^^^^^^^^^^^^^^^^^^^^^//
//                  //  para hacer "b" par  //
//      }
//      else{
//        D <<= 2; // D = 4n
//        d = raizCuadrada(D);
//        b = d; b[0] &= (Constants::CIFRA_MAX-1); // b = 2*floor(d/2) 
//      }
//      a.hacerUno();
//      // b ya esta
//      c = b; c.cuadrado(); c -= D; c >>= 2; // c = (b^2 - D)/4
//      Q.clear();
//      L = raizCuadrada(d);
//      size_t i = 0;
//
//      //4
//      A = a; B = b; C = c;
//      while(true){
//        while(true){
//          reduccionRho(A,B,C,D,d);
//          i++;
//          if( i & 0x1 ){ //i impar
//            //7   
//            if( abs(A) <= L )
//              Q.insert(A);//esto es una modificacion sobre el alg. de cohen... de no hacerse
//                           //la factorización sale incorrecta. P ej
//                           //para 987161
//
//          }
//          else break;
//        }
//
//        //5
//        if( A.esCuadrado(&raiz) ){
//          a = raiz;
//          if(Q.find(a) != Q.end()){  // encontrado; a \in Q
//            //6
//            if( A.esUno() )
//              //se han recorrido los i elementos del ciclo principal sin
//              //encontrar una forma cuadratica no trivial.
//              return false;
//
//            //7
//            if( abs(A) <= L )
//              Q.insert(A); //esto es una modificacion sobre el alg. de cohen... de no hacerse
//                           //la factorización sale incorrecta. P ej
//                           //para 987161
//          }
//          else break; // no encontrado; => 8
//        } // A no es cuadrado
//        else{
//          //6
//          if( A.esUno() )
//            //se han recorrido los i elementos del ciclo principal sin
//            //encontrar una forma cuadratica no trivial.
//            return false;
//
//          //7
//          if( abs(A) <= L )
//            Q.insert(A);//esto es una modificacion sobre el alg. de cohen... de no hacerse
//                        //la factorización sale incorrecta. P ej
//                        //para 987161
//
//        }
//
//      }// del paso 4
//
//      //8
//      //aqui se ha encontrado una forma cuadratica no trivial
//      Z s;
//      s = gcd->gcd(B,D);
//      s = gcd->gcd(a, s); // s = gcd(raiz, B, D)
//      if( s > (Digit)1 ){
//        // s^2 es factor 
//        factores->push_back(s);
//        factores->push_back(s);
//        (*n) /= cuadrado(s);
//      }
//      else{
//        // a = a
//        b = -B;
//        c = a*C;
//        reducir(a,b,c,D,d);
//        //9
//        while(true){
//          Z b1(b);
//          A = a; B = b; C = c;
//          reduccionRho(a,b,c,D,d);
//          if( a.esUno() ){
//            a = A; b = B; c = C;
//            break;
//          }
//          if( b1 == b ) 
//            break;
//        }
//        
//        if( a.esUno() ) // no se ha conseguido factorizar
//          return false;
//        a.abs();
//        if( a.esImpar() ){
//          if( a.esUno() || ( a == (*n) ) )
//            return false; //divisor TRIVIAL
////          std::cout << "." << std::endl;
//          factores->push_back(a);
//          (*n) /= a;
//        }
//        else{ // a es par
//          a >>= 1;
//          if( a.esUno() || ( a == (*n) ) )
//            return false; //divisor TRIVIAL
////          std::cout << "." << std::endl;
//          factores->push_back(a);
//          (*n) /= a;
//        }
//      }
//
//    } // del for mas externo
//    if( factorCuadrado )
//      if( it != factores->end() ) //se han añadido factores primos
//        factores->insert( factores->end(), it, factores->end() );
//
//    return false;
//
//  } 

  bool RhoPollard::factorZ(Z* n, MiVec<Z>* factores)
  {
    if( n == NULL )
      throw Errors::PunteroNulo();
    if( factores == NULL )
      throw Errors::PunteroNulo();

    // pag 91 Menezes
    Functions* const funcs = Functions::getInstance();
    RedBarrett* reduccion; funcs->getFunc(reduccion);
    Z mu = reduccion->precomputaciones(*n);
    GCD* gcd;funcs->getFunc(gcd);
    TestPrimoProb* test; funcs->getFunc(test);
    Z a((Digit)2);
    Z b((Digit)2);
    Z d;
//    size_t numFactoresIni = factores->size();

    if( test->esPrimo(*n) ){
      factores->push_back(*n);
      return true;
    }
    size_t iteraciones = 0;
    while(++iteraciones <= Constants::COTA_FACTORIZACION_RHO){
      a.cuadrado();
      a++;
      reduccion->redBarrett(&a,*n,mu);

      b.cuadrado();
      b++;
      reduccion->redBarrett(&b,*n,mu);
      b.cuadrado();
      b++;
      reduccion->redBarrett(&b,*n,mu);

      d = gcd->gcd( a - b, *n );

      if( (d > (Digit)1) && (d < (*n)) ){
        factores->push_back(d);
        (*n) /= d;
        if( test->esPrimo(*n) ){
          factores->push_back(*n);
          return true;
        }
        mu = reduccion->precomputaciones(*n);
      }
      else if ( d == (*n) )
        assert(false); //FIXME
    }

    return false;

  }

  //  bool RhoPollard::factorZ(Z* n, MiVec<Z>* factores)
  //  {
  //    // pag 91 Menezes
  //    Functions funcs;
  //    RedBarrett* reduccion = funcs.getBarrettReduction();
  //    Z mu = reduccion->precomputaciones(*n);
  //    GCD* gcd = funcs.getGCD();
  //    //    TestPrimoProb* test = funcs.getTestPrimoProb();
  //
  //    Z x, x0;
  //    Z y, ys;
  //    Z q; 
  //    Z G;
  //    size_t r,k,m;
  //    r=1; m = 1;
  //    x0 = Z::convertir((Digit)2); y = x0;
  //    q.hacerUno();
  //
  //    do{
  //      x = y;
  //      for(size_t i = 0; i < r; i++){
  //        y.cuadrado(); 
  //        y++;
  //        reduccion->redBarrett( &y, *n, mu );
  //      }
  //      k = 0;
  //      do{
  //        ys = y;
  //        size_t cota = std::min(m, r-k);
  //        assert( cota <= 10 );
  //        assert( cota > 0);
  //        for(size_t j = 0; j < cota; j++){
  //          y.cuadrado(); y++;
  //          reduccion->redBarrett( &y, *n, mu );
  //          q *= ((x-y).abs());
  //          reduccion->redBarrett( &q, *n, mu );
  //        }
  //        G = gcd->gcd(q,*n);
  //        k += m;
  //      } while( (k < r) && (G == 1) );
  //      r *= 2;      
  //    } while( G == 1 );
  //
  //    if( G == (*n) ){
  //      do{ 
  //        ys.cuadrado();
  //        ys++;
  //        reduccion->redBarrett( &ys, *n, mu );
  //        G = gcd->gcd((x-ys).abs(),*n);
  //      } while ( G == 1 );
  //    }
  //    if( G == (*n) )
  //    {
  //      assert(false);
  //    }
  //    else{ // 1 < G < N
  //      factores->push_back(G);
  //    }
  //    return true;
  //
  //  }
  //  MiVec<Z> RhoPollard::factorZ(const Z& num)
  //  {
  //    // pag. 370 Knuth
  //    Functions funcs;
  //    MiVec<Z> factores; factores.clear();
  //    Z n(num);
  //    Z x;
  //    x = Z::convertir((Digit)5); 
  //    Z xPrima;
  //    xPrima = Z::convertir((Digit)2); 
  //    Z k; k.hacerUno();
  //    Z l; l.hacerUno();
  //    RedBarrett* reduccion = funcs.getBarrettReduction();
  //    GCD* gcd = funcs.getGCD();
  //    Z mu = reduccion->precomputaciones(n);
  //    Z g;
  //
  ////    Trial trial;
  //    
  //    while(true){
  //      if( funcs.getTestPrimoProb()->esPrimo(n) ){
  //        factores.push_back(n);
  //        return factores;
  //      }
  //
  ////      if( n.numBits() <= 32){
  ////        std::cout << "hola" << std::endl;
  ////        MiVec<Z> factoresTrial; factoresTrial.clear();
  ////        factoresTrial = trial.factorZ(n);
  ////
  ////        factores.insert(factores.end(), factoresTrial.begin(), factoresTrial.end());
  ////        return factores;
  ////      }
  //        
  //      
  //      while(true){
  //        g = gcd->gcd( xPrima - x, n );
  //
  //        if( g == n )
  //          abort();
  //        else if( g > (Digit)1 ){
  //          factores.push_back(g);
  //          n /= g;
  //          mu = reduccion->precomputaciones(n);
  //          reduccion->redBarrett(&x,n,mu);
  //          reduccion->redBarrett(&xPrima,n,mu);
  ////          x %= n;
  ////          xPrima %= n;
  //          break;
  //        }
  //        else{ // g == 1
  //          k--;
  //          if( k.esCero() ){
  //            xPrima = x;
  //            l <<= 1;
  //            k = l;
  //          }
  //          x.cuadrado();
  //          x++;
  //          reduccion->redBarrett(&x,n,mu);
  ////          x %= n;
  //        }
  //      }
  //    }
  //  }



  bool Trial::factorZ(Z* n, MiVec<Z>* factores)
  {

    if( n == NULL )
      throw Errors::PunteroNulo();
    if( factores == NULL )
      throw Errors::PunteroNulo();

    //pag. 364 Knuth
    
    if( n->esUno() ){
      factores->push_back( Z((Digit)1) );
      return true;
    }

    //antes de empezar, quitar los doses pudiera tener el
    //número en su descomposición prima. Esto se hace por ser algo
    //directo y rápido.
    size_t doses = n->numDoses();
    if(doses){
      (*n) >>= doses;
      factores->insert(factores->end(), doses, Z((Digit)2));
    }

    Z q,r;
    size_t i = 1; //empezar en el 3, no en el 2 (ya se han quitado)
    while( i < Constants::COTA_FACTORIZACION_TRIAL ){
      divMod( *n, Constants::TABLA_PRIMOS_2000[i], &q, &r );
      if( r.esCero() ){
        factores->push_back(Z(Constants::TABLA_PRIMOS_2000[i]));
        (*n) = q;
        if( n->esUno() ) return true;
      }
      else{ // r != 0
        if( q <= Constants::TABLA_PRIMOS_2000[i] ){
          factores->push_back(*n);
          return true;
        }
        else // q > primos[k]
          i++;
      }
    }

    return false;

    }



  }
