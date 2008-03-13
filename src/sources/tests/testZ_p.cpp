#include "Z_p.h"
#include "Random.h"
#include "Primos.h"

#include <iostream>

int main(){

  mpplas::RandomFast::DFL rnd;
  mpplas::PrimeGen::DFL genPrimes;

  const mpplas::Z n(4);
  const mpplas::Z p(5);

  mpplas::Z_p zp(n, p);
  mpplas::Z_p zp2(n+3874, p);

  std::cout << zp << std::endl;
  std::cout << zp2 << std::endl;

  std::cout << std::endl;
  std::cout << mpplas::Z_p::getAddIdentity() << std::endl;
  std::cout << mpplas::Z_p::ZERO *zp<< std::endl;
  std::cout << mpplas::Z_p::ONE *zp<< std::endl;
  std::cout <<zp* mpplas::Z_p::ONE << std::endl;
  std::cout << mpplas::Z_p::getMultIdentity() << std::endl;


  return 0;
}
