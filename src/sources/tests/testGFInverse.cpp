#include <iostream>
#include "MethodsFactory.h"
#include "Factor.h"
#include "Potencia.h"
#include "GF.h"
#include "GFx.h"
#include "PolynomialUtils.h"

#include <set>
#include <string>

using namespace mpplas;


int main(){

  GF gf(3,Z_px("[(1, 1)(2, 0)]",(Digit)3));
  
  std::cout << gf.toHRString() << std::endl;
  GFx e( gf.getElement() );
//  e.setIntegerValue(Z("123"));
//
//  std::cout << e << std::endl;
//  std::cout << e.getInverse() << std::endl;
//  std::cout << e * e.getInverse() << std::endl;

  e = gf.getElement(Z("7946347312809721327"));
  GFx eInv(e.getInverse());

  std::cout << e << std::endl;
  std::cout << eInv << std::endl;
  std::cout << e*eInv << std::endl;

  return 0;
}




