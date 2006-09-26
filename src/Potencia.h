#ifndef __POTENCIA_H
#define __POTENCIA_H

#include "R.h"
#include "Z.h"

namespace numth{

  // la razon de que el exponente se considere con signo pese a no
  // poder realizarse exponenciaciones negativas en enteros es para
  // evitar que un número con signo se "colase" bajo la interpretacion
  // sin signo, obteniendo, por ejemplo, el valor 2^32-1 para -1
  /** Interfaz para potenciación en enteros.
   *
   * Clase base para algoritmos que implementen la potenciación sobre
   * enteros.
   * 
   */
  class Potencia
  {
    public:
      /** Potenciación "in-situ".
       *
       * Realizar una potenciación "in-situ". Es ligeramente más
       * eficiente al no necesitar operaciones de copia en el paso de
       * parametros y devolución del resultado.
       * 
       *  @param base Puntero a entero que inicialmente contiene la
       *  base de la operación y el cual se modifica para contener el
       *  resultado al final. 
       *   
       * @param exp Exponente de la operación de potenciación. 
       *
       * @exception Se devuelve Errores::PunteroNulo si @a n o @a
       *  factores son punteros iguales a NULL.

       * 
       *  @note La razón de que el argumento @a exp sea de tipo
       *  CifraSigno cuando no puede ser negativo es para evitar
       *  problemas de conversión automática por parte de C++ entre
       *  tipos con y sin signo.
       */
      virtual void potencia(Z* base,  CifraSigno exp) = 0; 

      /** Potenciación.
       *
       * Realiza una potenciación devolviendo el entero resultante.
       * 
       *  @param base Entero base de la potenciación.
       * 
       * @param exp Exponente de la operación de potenciación. El
       *  paso de un valor negativo provocará una excepción
       *  "ExponenteNegativo". 
       *
       * @return El entero resultado de \f$base^{exp}\f$.
       * 
       *  @note La razón de que el argumento @a exp sea de tipo
       *  CifraSigno cuando no puede ser negativo es para evitar
       *  problemas de conversión automática por parte de C++ entre
       *  tipos con y sin signo.
       */
      Z potencia(Z base,  CifraSigno exp); 

      virtual ~Potencia(){}
  };
 

  class PotenciaR
  {
    public:
      virtual void potenciaR(R* base,  CifraSigno exp) = 0; 
      R potenciaR(R base,  CifraSigno exp); 

      virtual ~PotenciaR(){}
  };
  
  
  /** Interfaz para potenciación modular.
   *
   * Clase base para algoritmos que implementen la potenciación
   * modular sobre enteros.
   * 
   */
  class PotModular
  {
    public:
       /** Potenciación modular "in-situ".
       *
       * Realizar una potenciación modular "in-situ". Es ligeramente más
       * eficiente al no necesitar operaciones de copia en el paso de
       * parametros y devolución del resultado.
       * 
       *  @param base Puntero a entero que inicialmente contiene la
       *  base de la operación y el cual se modifica para contener el
       *  resultado al final. El paso de un puntero nulo provocará una
       *  excepción de tipo "PunteroNulo"
       * 
       * @param exp Exponente de la operación de potenciación.
       * Si el módulo @a mod suministrado no es primo y se pasa un
       * valor de exponente negativo, se producirá un error de tipo
       * "ElementoNoInvertible".
       *
       * @param mod El módulo reductor.
       */
      virtual void potModular(Z* base, const Z& exp, const Z& mod) = 0; 
  
      /** Potenciación modular.
       *
       * Realizar una potenciación modular devolviendo el resultado.
       * 
       *  @param base Entero base de la potenciación.
       * 
       * @param exp Exponente de la operación de potenciación.
       * Si el módulo @a mod suministrado no es primo y se pasa un
       * valor de exponente negativo, se producirá un error de tipo
       * "ElementoNoInvertible".
       *
       * @param mod El módulo reductor.
       *
       * @return El entero resultado de \f$base^{exp} \bmod mod\f$.
       */
      Z potModular(Z base, const Z& exp, const Z& mod); 
 
      /** Cálculo de la inversa.
       *
       * Realizar el cálculo de la inversa en un cuerpo finito.
       * 
       * @param base Entero a invertir.
       * 
       * @param mod El módulo reductor. Si este valor no es primo, se
       * producirá un error de tipo "ElementoNoInvertible".
       *
       * @return El entero resultado de \f$base^{-1} \bmod mod\f$.
       */
      Z inversa(const Z& base, const Z& mod);

      virtual ~PotModular(){}
  };



  /* IMPLEMENTACIONES */
  /** Potenciación entera mediante el algoritmo de la ventana
   * deslizante.
   *
   * Descrito en Handbook of Applied Cryptography, algoritmo 14.85
   *
   * @note Es el método que la librería utiliza por omisión.
   */
  class PotVentanaDeslizante : public Potencia
  {
    public:
      virtual void potencia(Z* base,  CifraSigno exp);

      virtual ~PotVentanaDeslizante(){}
  };
  typedef PotVentanaDeslizante PotenciaDFL;

 
  
  class PotVentanaDeslizanteR : public PotenciaR
  {
    public:
      virtual void potenciaR(R* base,  CifraSigno exp);

      virtual ~PotVentanaDeslizanteR(){}
  };
  typedef PotVentanaDeslizanteR PotenciaRDFL;

  
  /** Potenciación entera mediante el algoritmo "Derecha a izquierda".
   *
   * Descrito en The Art of Computer Programming, Vol.2 pág. 8 \n
   *             Handbook of Applied Cryptography 614 \n
   *             A course in computational algebraic number theory,
   *             pág. 8
   *
   */
  class PotRightLeft : public Potencia
  {
    public:
      virtual void potencia(Z* base,  CifraSigno exp);

      virtual ~PotRightLeft(){}
  };
  


  /* modular */
  /** Potenciación modular entera mediante el método de Montgomery.
   * 
   * Descrito en Handbook of Applied Cryptography, algoritmo 14.94.
   *
   */
  class PotMontgomery : public PotModular
  {
    public:
      virtual void potModular(Z* base, const Z& exp, const Z& mod); 

      virtual ~PotMontgomery(){}
    protected:
      void montgomeryMult(Z* x, const Z& y,const Z& mod, const Z& modPrima);
      void montgomeryCuad(Z* x, const Z& mod, const Z& modPrima);
  };
 
  /** Potenciación modular entera utilizando reducción de Barrett.
   * 
   * Descrito en "Implementing the RSA public key encryption algorithm 
   * on a standard digital signal processor", Paul Barrett, 1986.
   *
   * @note Es el método que la librería utiliza por omisión.
   *
   */
  class ClasicoConBarrett : public PotModular
  {
    public:
      virtual void potModular(Z* base, const Z& exp, const Z& mod); 

      virtual ~ClasicoConBarrett(){}
  };
  typedef ClasicoConBarrett PotModularDFL;
};

    

#endif
