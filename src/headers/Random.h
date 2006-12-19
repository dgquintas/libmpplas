/*
 * $Id$
 */

#ifndef __RANDOM_H
#define __RANDOM_H

#include "MiVec.h"
#include "Z.h"
#include "constantes.h"
#include <cassert>

namespace numth{
 
  /** Interfaz para la generación de números aleatorios.
   *
   * Clase base para métodos de generación de números aleatorios.
   * 
   */
  class Random
  {
    public:
      /** Obtención de un número determinado de bits aleatorios.
       *
       * @param n Número de bits aleatorios a obtener.
       *
       * @return Un entero formado a partir de la concatenación de los
       * @a n bits aleatorios.
       */
      virtual Z leerBits(size_t n) = 0;
      /** Obtención de una Cifra aleatoria.
       *
       * @return Una Cifra aleatoria.
       *
       * @note Esto es solo una atajo de para cuando se quieren
       * generar un número aleatorio de \f$BASE\f$ bits.
       */
      virtual Cifra leerCifra(void);
 
      /** Get a random CifraSigno
       *
       * @return A random CifraSigno.
       *
       */
      virtual CifraSigno leerCifraSigno(void);

      /** Obtención de un número aleatorio menor que otro dado.
       *
       * @param cota El entero representando la cota a no superar.
       *
       * @return Un entero aleatorio menor que @a cota.
       */
      virtual Z leerEntero(Z cota);

      virtual ~Random() {}
  };
 
  /** Interfaz para la generación rápida de números aleatorios.
   *
   * Clase base para métodos de generación rápida de números aleatorios.
   * 
   */
  class RandomRapido : public Random
  {
    public:
      /** Establecer la semilla para los generadores.
       *
       * Establece la semilla que los generadores rápidos de números
       * aleatorios necesitan como estado inicial. De no
       * proporcionarse una, se tomaría automáticamente del Semillero.
       *
       * @param semilla Entero representando la semilla.
       *
       */
      virtual void ponerSemilla(const Z& semilla) = 0;
  };
   
  /** Interfaz para la generación de números aleatorios
   * criptográficamente seguros.
   *
   * Clase base para métodos de generación de números aleatorios
   * criptográficamente seguros.
   * 
   */
  class RandomSeguro : public Random
  {
    public:
      /** Establecer la calidad de los números criptográficamente
       * seguros generados.
       *
       * Los métodos de generación de números criptográficamente
       * seguros se basan en todos los casos considerados en el
       * problema FACTORING, teniendo que generar factores primos de
       * un determinado tamaño. Este método permite especificar dicho
       * tamaño: a mayor tamaño, mayor seguridad  pero también más
       * lentitud a la hora de instanciar las clases generadoras.
       * Si no se especifica, se utiliza un valor de 256 bits por
       * omisión.
       *
       * @param n Tamaño de los primos a generar internamente por los algoritmos.
       *
       */
      virtual void ponerCalidad(size_t n) = 0;
  };

  /** Interfaz para los algoritmos que implementen tests de
   * aleatoreidad.
   *
   * Clase base para los algoritmos que implementen tests de
   * aleatoreidad.
   */
  class PruebaRandom
  {
    public:
      /** Determinar si un generador de números pseudoaleatorios supera el tests.
       *
       * @param generadorRandom El generador a probar.
       *
       * @return true si el generador @a generadorRandom supera el
       * test.\n
       *         false si no.
       */
      virtual bool pruebaRandom(Random& generadorRandom) = 0;

      virtual ~PruebaRandom() {}
  };
  
  /* IMPLEMENTACIONES */
  /** Algoritmo NumThRC4 (RC4) para la generación rápida de números
   * pseudoaleatorios.
   *
   * Descrito en Applied Cryptography, página 397, punto 17.1\n
   * 
   * @note Es el método que la librería utiliza por omisión.
   */
  class NumThRC4Gen : public RandomRapido
  {
    public:
      NumThRC4Gen();

      virtual ~NumThRC4Gen(){}
      
      virtual Z leerBits(size_t n);
      virtual void ponerSemilla(const Z& semilla);
      
    private:
      uint8_t s_[256];
      uint8_t k_[256];
      size_t i_;
      size_t j_;
      Z semilla_;
      void inicializar_(void);
  };
  typedef NumThRC4Gen RandomRapidoDFL;
  typedef NumThRC4Gen RandomDFL;

  /** Algoritmo para la generación rápida de números
   * pseudoaleatorios mediante congruencias lineales.
   *
   * Descrito en Applied Cryptography, página 369, punto 16.1\n
   * The Art of Computer Programming Vol. 2, pág. 9, punto 3.2.1
   * 
   */
  class congruentGen : public RandomRapido
  {
    public:
      congruentGen(void);

      virtual ~congruentGen(){}

      virtual Z leerBits(size_t n);
      virtual void ponerSemilla(const Z& semilla);

      //FIXME: dar la opcion de modificar la "a", "b", "m" del metodo?
      
    private:
      unsigned long a_;
      unsigned long b_;
      unsigned long m_;

      unsigned long Xi_;
  };

  /** Algoritmo Blum-Blum-Shub para la generación de números
   * pseudoaleatorios criptográficamente seguros.
   *
   * Descrito en Handbook of Applied Cryptography, página 186, algoritmo 5.40\n
   * Applied Cryptography, página 417, punto 17.9\n
   * Cryptographic Secure Pseudo-Random Bits Generation: The Blum-
   * Blum-Shub Generator, Pascal Junod, 1999
   *
   * @note Es el método que la librería utiliza por omisión.
   */
  class BBSGen : public RandomSeguro
  {
    public:
      BBSGen(void);
      
      virtual Z leerBits(size_t n);
      virtual void ponerCalidad(size_t n);

      virtual ~BBSGen(){}

    private:
      size_t calidad_;
      Z n_; // producto de los primos p y q de la inicializacion
      Z Xi_;

      void inicializar_(void);
  };
  typedef BBSGen RandomSeguroDFL;
  




  /** Implementación del conjunto de tests FIPS 140-1.
   *
   * Descrito en Handbook of Applied Cryptography, página 183, algoritmo 5.32\n
   *
   * @note Es el método que la librería utiliza por omisión.
   */
  class FIPS_140_1 : public PruebaRandom
  {
    public:
      virtual bool pruebaRandom(Random& generadorRandom);
      virtual ~FIPS_140_1(){}
      
    protected:
      size_t monobitTest_(Z muestraLocal);
      float pokerTest_(Z muestraLocal);
      size_t runTests_(Z muestraLocal, size_t* bloques, size_t* huecos);

  };
  typedef FIPS_140_1 PruebaRandomDFL;
  
}
#endif

