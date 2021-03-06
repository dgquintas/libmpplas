/*
 * $Id $
 */

#include <string>
#include "RSATest.h"
#include "MethodsFactory.h"
#include "Z.h"
#include "Z_n.h"
#include "Random.h"
#include "Primos.h"
#include "GCD.h"
#include "Potencia.h"
//#include <ctime>

using namespace std;
using namespace mpplas;
using namespace com_uwyn_qtunit;

RSATest::RSATest(){
  addTest(RSATest, testRSA);
}

void RSATest::setUp(){
  time_t now = time(NULL);
  sourceString = asctime(localtime(&now));
}
void RSATest::tearDown(){
//empty. new is not used
}

void RSATest::testRSA(){

  MethodsFactory* const funcs = MethodsFactory::getInstance();
  RandomFast* genRandom;
  PrimeGen* genPrimos;
  funcs->getFunc(genRandom);
  funcs->getFunc(genPrimos);

  genPrimos->setRandomSeed((Digit)123);
  //se declaran 4 numeros enteros. 
  Z p,q,n,phi; 
 
  int tamPrimos = 128;
  
//  const clock_t t1 = clock();
  // cogemos los primos... del tama�o en bits que queramos
  p = genPrimos->getPrime(tamPrimos);
  q = genPrimos->getPrime(tamPrimos);

  //se sigue con las operaciones propias del RSA
  n = p*q;
  phi = (p-(Digit)1)*(q-(Digit)1);

  // y los enteros que representan las claves
  Z e, d;  
 
  //se busca una clave de encriptacion coprima con phi, como define
  //el algoritmo
  GCD<Z>* gcd; funcs->getFunc(gcd);
  Exponentiation<Z_n>* potMod; funcs->getFunc(potMod);
  do{
    e = genRandom->getIntegerBounded(n);
  } while( !(gcd->gcd(e,phi).isOne()) );

  //y la clave de desencriptacion la inversa de "e" modulo "phi"
  d = potMod->inverse(e,phi);
  
  // y se lee lo que se quiere encriptar.
  // OJO!! no meter mas bits que la longitud de n. Obviamente 
  // esto en caso de implementar RSA bien bien habria que tratar esto
  // y dividir en cachos de forma acorde. PERO ESTO NO ES PAPEL DE LA
  // LIBRERIA, sino del usuario.
  
  // y el entero "m" representa la cadena leida
  Z m;
  m.leerBytes(sourceString.begin(), sourceString.end());

  // se encripta con la exponenciacion modular 
  Z_n c(m,n);
  potMod->exponentiation(&c,e);
 
  // y el entero que representa el mensaje desencriptado
  Z_n mdesc(c,n);
  potMod->exponentiation(&mdesc,d);
  
  const int tam = (mdesc.getBitLength() >> 3)+1;
  resString.resize(tam);
  mdesc.escribirBytes(resString.begin(), resString.end());

//  cout << "(partial) Time for RSATest: " << (clock()-t1)/(float)CLOCKS_PER_SEC << "s. " << endl;

  qassertTrue( sourceString == resString );

  return;
}
