#include "Z.h"
#include <iostream>

using namespace std;
using namespace numth;

int main()
{
  Z foo;
  while(true){
    cin >> foo;
    cout << foo.numBits() << endl;
  }

  return 0;
}
