#include <iostream>
#include "Z.h"
#include "Random.h"
#include "Primos.h"
#include "Funciones.h"
#include <time.h>

using namespace std;
using namespace numth;

class MiGCD : public FBinarias
{
  Z gcd(Z x, Z y);
};

Z MiGCD::gcd(Z x, Z y)
{
  std::cout << "hola" << std::endl;
}


int main()
{
  Z n,m;

  Funciones funcs;
  MiGCD* migcd = new MiGCD();
  funcs.ponerFBinarias(migcd);
  
  cin >> n >> m;
 
  
  
  cout << funcs.fbinarias()->gcd(n,m) << endl;

  return 0;
}

