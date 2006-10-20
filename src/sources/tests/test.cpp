/*
 * $Id: test.cpp,v 1.1.1.1 2005/12/16 17:44:39 dgquintas Exp $
 */

#include "Z.h"
#include "R.h"
#include <iostream>
#include <stdexcept>
#include "err.h"

using namespace std;
using namespace numth;

int main()
{
  try{
    Cifra exp;
    numth::Z foo;
    numth::Z bar;
//    long bar;

    cout << "mete foo: ";
    cin >> foo;

    numth::Z::precisionSalida(10);
    ++foo;
    cout << foo << endl;
    foo++;
    cout << foo << endl;
    --foo;
    cout << foo << endl;
    foo--;
    cout << foo << endl;

    numth::Z::precisionSalida(0);

    cout << "mete bar: ";
    cin >> bar;



    // cout << "mete bar: ";
    // cin >> bar;
    //
    // bar *= bar;

    cout << endl;

    if((foo > bar))
      cout << foo << " > " << bar << endl;
    if((foo < bar))
      cout << foo << " < " << bar << endl;
    if((foo != bar))
      cout << foo << " != " << bar << endl;
    if((foo == bar))
      cout << foo << " == " << bar << endl;
    if((foo >= bar))
      cout << foo << " >= " << bar << endl;
    if((foo <= bar))
      cout << foo << " <= " << bar << endl;

    cout << endl;
    cout << endl;

    if((bar > foo))
      cout << bar << " > " << foo << endl;
    if((bar < foo))
      cout << bar << " < " << foo << endl;
    if((bar != foo))
      cout << bar << " != " << foo << endl;
    if((bar == foo))
      cout << bar << " == " << foo << endl;
    if((bar >= foo))
      cout << bar << " >= " << foo << endl;
    if((bar <= foo))
      cout << bar << " <= " << foo << endl;

    cout << endl;


    cout << foo << " + " << bar << endl; ;
    cout << foo + bar << endl;
    cout << foo << " - " << bar << endl; ;
    cout << foo - bar << endl;
    cout << foo << " * " << bar << endl; ;
    cout << foo * bar << endl;
    cout << foo << " / " << bar << endl; ;
    cout << foo / bar << endl;
    cout << foo << " % " << bar << endl; ;
    cout << foo % bar << endl;

//    while(true)
//      foo %= bar;
    
//    numth::Z fac = numth::factorial(foo);
//
//    cout << fac << endl;

    cout << "mete exp: ";
    cin >> exp;
 
    cout << (foo^exp) << endl;
  
    
    // foo = bar << 78;

    // cout << foo << endl;
    // cout << foo.numBits() << endl;

    // long sumando = foo.redondear(40);
    //
    // foo >>= 40;
    // 
    // foo += sumando;

    // cout << foo << endl;

    cout << endl;

    numth::R::precisionSalida(20);
//    numth::R::precision(500);

    numth::R real;
    numth::R real2;
    cin >> real;
    cin >> real2;

//    cout << endl;
//    real += 3.141592;
//    cout << real << endl;
    cout << "mete exp: ";
    cin >> exp;
    
   numth::R potR = real^exp;

   cout << potR.numBits() << endl;
   
    cout << potR << endl;
//    cout << real + real2 << endl;
//    cout << real - real2 << endl;
//    cout << real * real2 << endl;
//    cout << real / real2 << endl;


//    numth::R expR = numth::exponencial(real);
//    cout << expR << endl;




    
    //  cout << real.numBits() << endl
    //       << real2.numBits() << endl;

    if((real > real2))
      cout << real << " > " << real2 << endl;
    if((real < real2))
      cout << real << " < " << real2 << endl;
    if((real != real2))
      cout << real << " != " << real2 << endl;
    if((real == real2))
      cout << real << " == " << real2 << endl;
    if((real >= real2))
      cout << real << " >= " << real2 << endl;
    if((real <= real2))
      cout << real << " <= " << real2 << endl;

    cout << endl;

    cout << real << " + " << real2 << endl;
    cout << real << " - " << real2 << endl;
    cout << real << " * " << real2 << endl;
    cout << real << " / " << real2 << endl;

    // for(int i = 0; i< 1000; i++){
    cout << real + real2 << endl;
    cout << real - real2 << endl;
    cout << real * real2 << endl;
    cout << real / real2 << endl;
    // }
    return 0;
  }
  catch(numth::Errores::Excepcion &ex)
  {
    cerr << ex.info() << endl;
  }
  catch(std::out_of_range)
  {
    cerr << "vector de meirda" << endl;
  }

}
