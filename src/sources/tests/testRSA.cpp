#include "Z.h"
#include "Random.h"
#include "Primos.h"
#include "Funciones.h"
#include "GCD.h"
#include "Potencia.h"
#include <iostream>
#include <string>

using namespace std;
using namespace numth;

int main()
{
  // objeto que aglutina las funciones 
  Funciones *funcs = Funciones::getInstance();
//  PotMontgomery *pm = new PotMontgomery();
//  funcs.ponerPotModular(pm);

  //esto no es estrictamente necesario: para acceder de forma resumida
  //al generador del numeros aleatorios en cuestion
  RandomRapido* genRandom; funcs->getFunc(genRandom);
  genRandom->ponerSemilla("34");
  //idem para el generador de primos
  GenPrimos* genPrimos; funcs->getFunc(genPrimos);
  genPrimos->setRandomSeed((Cifra)123);

  //se declaran 4 numeros enteros. 
  Z p,q,n,phi; 
 
  size_t tamPrimos;
  cout << "Tamaño en bits de los primos p y q: ";
  cin >> tamPrimos; cin.get();
  
  // cogemos los primos... del tamaño en bits que queramos
  p = genPrimos->leerPrimoProb(tamPrimos);
  q = genPrimos->leerPrimoProb(tamPrimos);

  cout << "Primo p escogido: " << p << endl;
  cout << "Primo q escogido: " << q << endl;
  
  //se sigue con las operaciones propias del RSA
  n = p*q;
  phi = (p-(Cifra)1)*(q-(Cifra)1);

  cout << "Prod. de p y q: " << n << endl;
  cout << "Phi de p y q: " << phi << endl;

  // y los enteros que representan las claves
  Z e, d;  
 
  //se busca una clave de encriptacion coprima con phi, como define
  //el algoritmo
  GCD*gcd; funcs->getFunc(gcd);
  PotModular* potMod; funcs->getFunc(potMod);
  do{
    e = genRandom->leerEntero(n);
  } while( !(gcd->gcd(e,phi).esUno()) );

  //y la clave de desencriptacion la inversa de "e" modulo "phi"
  d = potMod->inversa(e,phi);
  
  
  cout << "Clave encript.: " << e << endl;
  cout << "Clave decript.: " << d << endl;
 
  // y se lee lo que se quiere encriptar.
  // OJO!! no meter mas bits que la longitud de n. Obviamente 
  // esto en caso de implementar RSA bien bien habria que tratar esto
  // y dividir en cachos de forma acorde. PERO ESTO NO ES PAPEL DE LA
  // LIBRERIA, sino del usuario.
  string str;
  cout << "Introducir el mensaje a encriptar (menor de " << n.numBits() << " bits)" << endl;
  getline(cin, str);
  
  // y el entero "m" representa la cadena leida
  Z m;
  m.leerBytes(str.begin(), str.end());
  cout << m << endl;


  // se encripta con la exponenciacion modular 
  Z c;
  c = potMod->potModular(m,e,n);
  
  
  cout << "Mensaje encriptado: " << c << endl;

  // y el entero que representa el mensaje desencriptado
  Z mdesc;
  mdesc = potMod->potModular(c,d,n);
  
  cout << "Mensaje desencriptado: " << mdesc << endl;
  
  str.clear();
  size_t tam = (mdesc.numBits() >> 3)+1;
  str.resize(tam);
  mdesc.escribirBytes(str.begin(), str.end());
  cout << str << endl;


  return 0;
}
  
