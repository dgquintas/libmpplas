#include "CRT.h"
#include "Z.h"
#include <iostream>
#include <vector>
#include "Funciones.h"

using namespace std;
using namespace numth;


int main()
{
  MiVec<Z> emes(4);
  MiVec<Z> uves(4);
  Funciones funcs;

  for(int i=0; i < 4; i++)
    cin >> emes[i] >> uves[i];

  Z result;

  result = funcs.crt()->crt(emes, uves);

  cout << result << endl;
  
  return 0;
}
  
