#include "Polynomial.h"
#include "Z_p.h"
#include "MethodsFactory.h"
#include "Field.h"


#include <iostream>
#include <vector>


int main(){

  mpplas::Z_p x(3);
  std::cout << dynamic_cast<mpplas::Field<mpplas::Z_p>*>(&x) << std::endl;


//  std::vector<mpplas::Z> coefs;
//  coefs.push_back(mpplas::Z(1));
//  coefs.push_back(mpplas::Z(0));
//  coefs.push_back(mpplas::Z(3));
//  coefs.push_back(mpplas::Z(0));
//  coefs.push_back(mpplas::Z(4));
//
//  mpplas::Zx p(coefs);
//
//  coefs.push_back(mpplas::Z(-2));
//
//  mpplas::Zx p2(coefs);
//
//  std::cout << p << std::endl;
//  std::cout << p.evaluate(1488) << std::endl;
//  std::cout << p2 << std::endl;
//  std::cout << p2.evaluate(1488) << std::endl;
//
//  p *= p2;


  return 0;
}
