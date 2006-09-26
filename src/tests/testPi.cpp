/*
 * $Id: testPi.cpp,v 1.1.1.1 2005/12/16 17:44:43 dgquintas Exp $
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
    PiMachin piM;
    R::precisionSalida(60);
    
    R x;

    cout << piM.pi(10) << endl;
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
