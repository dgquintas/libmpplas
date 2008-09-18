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
  Z_px fx = PolynomialUtils::generatePrimitive<mpplas::Z_px>((Digit)7,(Digit)3);

  std::cout << fx.toHRString() << std::endl;

  return 0;
}




