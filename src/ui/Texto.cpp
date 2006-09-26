#include <iostream>
#include "calculadora.h"
#include <string>
#include "Perfil.h"
#include <cstring>

using namespace std;

int main(int argc, char* argv[])
{
  if( argc < 2 )
    return -1;

  string entrada;
  Calculadora calc;
  numth::Perfil perfil;
  char delim = ';';
  char* foo;
  
  
  
  perfil.iniciar();
  foo = strtok(argv[1], &delim);
    do {
    entrada = (char*)foo;
    cout << entrada << endl;
    string resultado = calc.procesar(entrada+";");
    for(unsigned j=0; j <= resultado.length()/60; j++)
      cout << resultado.substr(j*60, 60) << endl;

    cout << "---" << endl;

    }  while(  (foo = strtok(NULL, &delim)) ) ;
  perfil.finalizar();
  cout << perfil.leerSegundos() << " segundos" << endl;

  cout << perfil.leerVectorOperaciones()[numth::Operaciones::Add] 
    << "\t\tsumas" << endl;
  cout << perfil.leerVectorOperaciones()[numth::Operaciones::Addx] 
    << "\t\tsumas con acarreo" << endl;
  cout << perfil.leerVectorOperaciones()[numth::Operaciones::Sub] 
    << "\t\trestas" << endl;
  cout << perfil.leerVectorOperaciones()[numth::Operaciones::Subx] 
    << "\t\trestas con acarreo " << endl;
  cout << perfil.leerVectorOperaciones()[numth::Operaciones::Addmul] 
    << "\t\tmult. \"con acarreo\"" << endl;
  cout << perfil.leerVectorOperaciones()[numth::Operaciones::Mul] 
    << "\t\tmultiplicaciones" << endl; 
  cout << perfil.leerVectorOperaciones()[numth::Operaciones::Div] 
    << "\t\tdivisiones" << endl;
  cout << perfil.leerVectorOperaciones()[numth::Operaciones::Shiftl] 
    << "\t\tdesp. izq." << endl;
  cout << perfil.leerVectorOperaciones()[numth::Operaciones::Shiftlr] 
    << "\t\tdesp. der." << endl;
  cout << perfil.leerVectorOperaciones()[numth::Operaciones::Bfffo] 
    << "\t\tconteo de ceros" << endl;


  return 0;
}

    
