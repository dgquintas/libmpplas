#include <iostream>
#include "Z.h"

using namespace std;
using namespace numth;

int main()
{
  Z z1;
  unsigned long z2;

  Z q;
  Z r;
  
  cin >> z1;
  cin >> z2;

  divMod(z1, z2, q, r);

  cout << q << endl << r << endl;

  return 0;
}
  
