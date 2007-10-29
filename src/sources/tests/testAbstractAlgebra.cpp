#include "Z.h"
#include "Z_n.h"
#include "R.h"

#include <iostream>

int main(){

  mpplas::R r1;
  mpplas::Z z1;
  mpplas::Z_n zn(3);

//  std::cout << r1.isDivisionRing() << std::endl;
//  std::cout << zn.isDivisionRing() << std::endl;
//  std::cout << r1.getAddInverse() << std::endl;
  std::cout << mpplas::R::getAddIdentity() << std::endl;
  std::cout << mpplas::R::getMultIdentity() << std::endl;

  return 0;
}
