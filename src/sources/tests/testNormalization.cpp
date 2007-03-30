#include "R.h"
#include <iostream>

using namespace mpplas;

int main(){

  R r1("0.123456789666");
  R r2("0.12345678966600000000");

  r1.normalizar();
  r2.normalizar();

  std::cout << (r1 == r2) << std::endl;

  return 0;
}
