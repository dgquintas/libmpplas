#include <iostream>
#include "Random.h"

using namespace std;
using namespace mpplas;

int main()
{
  NumThRC4Gen rnd;

  cout << rnd.getInteger(128 * 1024 * 8) << endl; //16KB
  cout << rnd.getInteger(0) << endl; //16KB

  
  return 0;
}

