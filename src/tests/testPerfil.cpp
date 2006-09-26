#include <iostream>
#include "Z.h"
#include "Perfil.h"

using namespace std;
using namespace numth;

int main()
{
  Z foo;
  Cifra exp;
  Perfil perfil;
  
  perfil.iniciar();
  cin >> foo;
  cin >> exp;
  cout << (foo^exp) << endl;
  perfil.finalizar();

  cout << perfil.leerSegundos() << " segundos" << endl;
  MiVec<Z> ops = perfil.leerVectorOperaciones();
  MiVec<R> perc = perfil.leerVectorPorcentajes();

  for(size_t i=0; i < NUM_OPERACIONES; i++)
    cout << ops[i] << " ";
 
  cout << endl;
  
  for(size_t i=0; i < NUM_OPERACIONES; i++)
    cout << perc[i] << " ";

  return 0;
}
  
