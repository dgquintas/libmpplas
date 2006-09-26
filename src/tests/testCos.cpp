/*
 * $Id: testCos.cpp,v 1.1.1.1 2005/12/16 17:44:40 dgquintas Exp $
 */

#include "Z.h"
#include "R.h"
#include <iostream>
#include <stdexcept>
#include "err.h"
#include "Transcendentes.h"

using namespace std;
using namespace numth;


int main()
{
  try{
    CosTaylor cosT;
    R::precisionSalida(70);
    
    R x;
    cout << "Mete el x pa Cos(x)" << endl;
    cin >> x ;

    cout << cosT.coseno(x) << endl;
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
