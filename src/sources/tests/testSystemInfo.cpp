#include <iostream>
#include "SystemInfo.h"
#include "Funciones.h"

int main(){
  numth::Funciones * const funcs(numth::Funciones::getInstance());

  numth::SystemInfo* si;
  funcs->getFunc(si);

  std::cout << si->getArchitecture() << std::endl;

}
