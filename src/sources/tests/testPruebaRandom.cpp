#include <iostream>
#include "Z.h"
#include "Funciones.h"
#include "Random.h"

using namespace std;
using namespace numth;

int main()
{
  BBSGen bbs;
  NumThRC4Gen rc4;
  congruentGen cong;
  Funciones funcs;
  PruebaRandom* fips = funcs.pruebaRandom();

  if( fips->pruebaRandom(bbs) )
    cout << "BBS pasa" << endl;
  else
    cout << "BBS no pasa" << endl;
 
  if( fips->pruebaRandom(rc4) )
    cout << "RC4 pasa" << endl;
  else
    cout << "RC4 no pasa" << endl;
  
  if( fips->pruebaRandom(cong) )
    cout << "congruentGen pasa" << endl;
  else
    cout << "congruentGen no pasa" << endl;

  return 0;
}
  
