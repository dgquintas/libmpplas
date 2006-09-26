#include <iostream>
#include "Z_n.h"
#include "err.h"

using namespace std;
using namespace numth;
int main()
{
  try{
  numth::Z mod;
  CifraSigno k;

  cin >> mod;
  cin >> k;

  numth::Z_n enteroModular(mod);

  cin >> enteroModular;

  numth::Z_n bis(mod);
  bis = enteroModular;

  if( (enteroModular +k) > enteroModular)
    cout << "foo" << endl;
  
  cout << enteroModular +k << endl;

//  enteroModular = bis;
//  enteroModular -= k;
  cout << enteroModular - k << endl;

//  enteroModular = bis;
//  enteroModular *= k;
  cout << enteroModular *k << endl;

//  enteroModular = bis;
//  enteroModular /= k;
  cout << enteroModular/k << endl;
  }
   catch(numth::Errores::Excepcion &ex)
  {
    cerr << ex.info() << endl;
  }


}
