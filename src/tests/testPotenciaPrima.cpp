#include <iostream>
#include "Z.h"

using namespace std;
using namespace numth;

int main()
{
  Z num;
  Z p;

  cin >> num;

  cout << num.esPotenciaPrima(&p) << endl;
  cout << p << endl;

  return 0;
}
