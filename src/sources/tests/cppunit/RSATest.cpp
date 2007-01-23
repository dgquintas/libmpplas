/*
 * $Id $
 */

#include <cppunit/TestCase.h>
#include <string>
#include "RSATest.h"
#include "Funciones.h"
#include "Z.h"
#include <ctime>

using namespace std;
using namespace numth;

CPPUNIT_TEST_SUITE_REGISTRATION( RSATest );

void RSATest::setUp(){
  time_t now = time(NULL);
  sourceString = asctime(localtime(&now));
}
void RSATest::tearDown(){
//empty. new is not used
}

void RSATest::testRSA(){

  Funciones funcs;


  //esto no es estrictamente necesario: para acceder de forma resumida
  //al generador del numeros aleatorios en cuestion
  RandomRapido* genRandom = funcs.getRandomRapido();
  //idem para el generador de primos
  GenPrimos* genPrimos = funcs.getGenPrimos();
  genPrimos->setRandomSeed(Z::convertir((Cifra)123));
  //se declaran 4 numeros enteros. 
  Z p,q,n,phi; 
 
  size_t tamPrimos = 1024;
  
  const clock_t t1 = clock();
  // cogemos los primos... del tamaño en bits que queramos
  p = genPrimos->leerPrimoProb(tamPrimos);
  q = genPrimos->leerPrimoProb(tamPrimos);

  //se sigue con las operaciones propias del RSA
  n = p*q;
  phi = (p-(Cifra)1)*(q-(Cifra)1);

  // y los enteros que representan las claves
  Z e, d;  
 
  //se busca una clave de encriptacion coprima con phi, como define
  //el algoritmo
  do{
    e = genRandom->leerEntero(n);
  } while( !(funcs.getGCD()->gcd(e,phi).esUno()) );

  //y la clave de desencriptacion la inversa de "e" modulo "phi"
  d = funcs.getPotModular()->inversa(e,phi);
  
  // y se lee lo que se quiere encriptar.
  // OJO!! no meter mas bits que la longitud de n. Obviamente 
  // esto en caso de implementar RSA bien bien habria que tratar esto
  // y dividir en cachos de forma acorde. PERO ESTO NO ES PAPEL DE LA
  // LIBRERIA, sino del usuario.
  
  // y el entero "m" representa la cadena leida
  Z m;
  m.leerBytes(sourceString.begin(), sourceString.end());

  // se encripta con la exponenciacion modular 
  Z c;
  c = funcs.getPotModular()->potModular(m,e,n);
 
  // y el entero que representa el mensaje desencriptado
  Z mdesc;
  mdesc = funcs.getPotModular()->potModular(c,d,n);
  
  size_t tam = (mdesc.numBits() >> 3)+1;
  resString.resize(tam);
  mdesc.escribirBytes(resString.begin(), resString.end());

  cout << "(partial) Time for RSATest: " << (clock()-t1)/(float)CLOCKS_PER_SEC << "s. " << endl;

  CPPUNIT_ASSERT( sourceString == resString );

  return;
}
