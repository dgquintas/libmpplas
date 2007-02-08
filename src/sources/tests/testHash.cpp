#include <iostream>
#include <iomanip>
#include "Funciones.h"
#include "Hash.h"
#include <string>

using namespace std;
using namespace numth;

int main()
{
  MiVec<uint32_t> res;
  Funciones* funcs = Funciones::getInstance();
  Hash* hash=0;
  funcs->getFunc(hash);
  MiVec<uint8_t> vec;
  string str;

  cin >> str;
  for(size_t i=0; i < str.size(); i++)
    vec.push_back(str[i]);
  
  hash->actualizar(vec); 
  res = hash->obtenerVectorResumen();
  cout.width(8);
  cout.fill('0');
  cout << hex << res[0] << res[1] << res[2] << res[3] << endl;
  return 0;
}

