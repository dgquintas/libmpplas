#include "Funciones.h"
#include <iostream>

using namespace std;
using namespace numth;

int main()
{
  Z a, b;
  Funciones funcs;
  cin >> a >> b;

  cout << funcs.lcm()->lcm(a,b) << endl;

  return 0;
}
