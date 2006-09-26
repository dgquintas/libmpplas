#include "Z.h"
#include "Factor.h"
#include "Funciones.h"
#include <iostream>

using namespace std;
using namespace numth;

int main()
{
  Z num;
  CadenaAlgFactor fac;
  Funciones funcs;
  NumThRC4Gen rnd;

  rnd.ponerSemilla(Z::convertir("825432553543523423472852"));
  for(size_t j = 0; j < 5; j++){
    num = rnd.leerBits(70);  
    cin >> num;    
    cout << num << endl;
    MiVec<Z> facs = fac.factoriza(num);
    if( facs.size() > 0 ){
      for(size_t i=0; i < facs.size()-1; i++)
        cout << facs[i] << " * " ;
      cout << facs.back() << endl;
    }
  }

  return 0;
}

  
