#include <iostream>
#include "ZM_n.h"

using namespace mpplas;
using namespace std;

int main(){

  ZM_n zm1(Z("15024375908237405982794024423521"),Z("3202342424227"));
  ZM_n zm2(Z("43531213242235236235325"),Z("3202342424227"));

  cout << zm1 << endl;
  cout << zm2 << endl;
  cout << zm1.toZ() << endl;
  cout << zm2.toZ() << endl;

  zm1 *= zm2;
  cout << zm1 << endl;
  cout << zm1.toZ() << endl;

  cout << endl;
  zm2.inverse();

  cout << zm2 << endl;
  cout << zm2.toZ() << endl;





  return 0;
}
