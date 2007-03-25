#include <iostream>
#include "Random.h"

using namespace std;
using namespace mpplas;

int main()
{
  NumThRC4Gen rnd;

  cout << rnd.leerBits(128 * 1024 * 8) << endl; //16KB

  
  return 0;
}

