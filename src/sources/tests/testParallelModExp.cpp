#include "ZM_n.h"
#include <iostream>

using namespace std;
using namespace mpplas;

int main(){

  ZM_n base(3,32027);
  ZM_n inv(base); inv.inverse();

  cout << (base^2).toZ() << endl;
  cout << ((base^2)^16).toZ() << endl;
  cout << (((base^2)^16)^4).toZ() << endl;

  return 0;
}


