#include "Primos.h"
#include <iostream>

using namespace std;
using namespace numth;

int main()
{
  RabinMiller rm;
  Z num, testigo; 

  cin >> num;
  cout << rm.esPrimo(num) << endl;
  rm.esPrimo(num,&testigo);
  cout << testigo << endl;
  
  
  while(true){
    if(rm.esPrimo(num))
      cout << num << endl;
    num+=(Cifra)1000;
  }

  return 0;
}

  
