#include <iostream>
#include "Funciones.h"

using namespace std;
using namespace numth;

int main()
{
  Z a, b;
  Z c;
  Funciones funcs;
  
  cin >> a >> b;
  c = funcs.simbolokronecker()->simbolokronecker(a,b);

  cout << c << endl;
  
  return 0;
}
