#include "Funciones.h"
#include "Z.h"
#include <iostream>

using namespace std;
using namespace numth;


int main()
{
  Funciones funcs;
  RandomFast* rnd = funcs.getRandomFast();
  PrimeTest* test = funcs.testPrimoProb();
  GCD* gcd = funcs.getGCD();
  PotModular* potMod = funcs.getPotModular();

  size_t k;
  Z numKBits; numKBits.hacerUno();
  rnd->ponerSemilla(Z::convertir("123"));
  numKBits = rnd->leerBits(512);
  Z a = rnd->leerBits(6);
 
//  for(k=0; k < 200000; k++)
//    gcd->gcd(numKBits, (Cifra)2000);
  
  for(k=0; k < 10; k++)
    potMod->potModular(a, numKBits, numKBits  );

}
  
