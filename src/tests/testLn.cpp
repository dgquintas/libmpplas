/*
 * $Id: testLn.cpp,v 1.1.1.1 2005/12/16 17:44:42 dgquintas Exp $
 */

#include "Z.h"
#include "R.h"
#include <iostream>
#include <stdexcept>
#include "err.h"
#include "Funciones.h"
#include "Transcendentes.h"

using namespace std;
using namespace numth;


int main()
{
  try{
    Funciones funcs;
    LnTaylor log;
 //   R::precision(100);
    R::precisionSalida(60);
    
    R x;
    cout << "Mete el x pa Ln(x)" << endl;
    cin >> x ;

    cout << log.ln(x) << endl;
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
