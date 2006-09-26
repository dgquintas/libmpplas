/*
 * $Id: testDespR.cpp,v 1.1.1.1 2005/12/16 17:44:41 dgquintas Exp $
 */

#include "Z.h"
#include "R.h"
#include <iostream>
#include <stdexcept>
#include "err.h"

using namespace std;
using namespace numth;


int main()
{
  try{
    R x;
    cout << "Mete el real" << endl;
    cin >> x ;
    
    size_t n;
    cout << "Mete el desp" << endl;
    cin >> n;

    cout << (x << n) << endl;
    cout << (x >> n) << endl;
  }
  catch(numth::Errores::Excepcion &ex)
  {
    cerr << ex.info() << endl;
  }
  catch(std::out_of_range)
  {
    cerr << "vector de meirda" << endl;
  }

}
