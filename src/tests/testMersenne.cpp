#include <iostream>
#include "Funciones.h"

using namespace std;
using namespace numth;

int main()
{ 
  CifraSigno p;
  Funciones funcs;

  cin >> p;
  if( funcs.testprimomersenne()->testprimomersenne(p) )
    cout << "2**" << p << "-1" << " es primo" << endl;
  else
    cout << "2**" << p << "-1" << " NO es primo" << endl;

  return 0;
}
  
