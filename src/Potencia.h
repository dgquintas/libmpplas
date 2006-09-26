#ifndef __POTENCIA_H
#define __POTENCIA_H

#include "R.h"
#include "Z.h"

namespace numth{

  // la razon de que el exponente se considere con signo pese a no
  // poder realizarse exponenciaciones negativas en enteros es para
  // evitar que un n�mero con signo se "colase" bajo la interpretacion
  // sin signo, obteniendo, por ejemplo, el valor 2^32-1 para -1
  /** Interfaz para potenciaci�n en enteros.
   *
   * Clase base para algoritmos que implementen la potenciaci�n sobre
   * enteros.
   * 
   */
  class Potencia
  {
    public:
      /** Potenciaci�n "in-situ".
       *
       * Realizar una potenciaci�n "in-situ". Es ligeramente m�s
       * eficiente al no necesitar operaciones de copia en el paso de
       * parametros y devoluci�n del resultado.
       * 
       *  @param base Puntero a entero que inicialmente contiene la
       *  base de la operaci�n y el cual se modifica para contener el
       *  resultado al final. 
       *   
       * @param exp Exponente de la operaci�n de potenciaci�n. 
       *
       * @exception Se devuelve Errores::PunteroNulo si @a n o @a
       *  factores son punteros iguales a NULL.

       * 
       *  @note La raz�n de que el argumento @a exp sea de tipo
       *  CifraSigno cuando no puede ser negativo es para evitar
       *  problemas de conversi�n autom�tica por parte de C++ entre
       *  tipos con y sin signo.
       */
      virtual void potencia(Z* base,  CifraSigno exp) = 0; 

      /** Potenciaci�n.
       *
       * Realiza una potenciaci�n devolviendo el entero resultante.
       * 
       *  @param base Entero base de la potenciaci�n.
       * 
       * @param exp Exponente de la operaci�n de potenciaci�n. El
       *  paso de un valor negativo provocar� una excepci�n
       *  "ExponenteNegativo". 
       *
       * @return El entero resultado de \f$base^{exp}\f$.
       * 
       *  @note La raz�n de que el argumento @a exp sea de tipo
       *  CifraSigno cuando no puede ser negativo es para evitar
       *  problemas de conversi�n autom�tica por parte de C++ entre
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
  
  
  /** Interfaz para potenciaci�n modular.
   *
   * Clase base para algoritmos que implementen la potenciaci�n
   * modular sobre enteros.
   * 
   */
  class PotModular
  {
    public:
       /** Potenciaci�n modular "in-situ".
       *
       * Realizar una potenciaci�n modular "in-situ". Es ligeramente m�s
       * eficiente al no necesitar operaciones de copia en el paso de
       * parametros y devoluci�n del resultado.
       * 
       *  @param base Puntero a entero que inicialmente contiene la
       *  base de la operaci�n y el cual se modifica para contener el
       *  resultado al final. El paso de un puntero nulo provocar� una
       *  excepci�n de tipo "PunteroNulo"
       * 
       * @param exp Exponente de la operaci�n de potenciaci�n.
       * Si el m�dulo @a mod suministrado no es primo y se pasa un
       * valor de exponente negativo, se producir� un error de tipo
       * "ElementoNoInvertible".
       *
       * @param mod El m�dulo reductor.
       */
      virtual void potModular(Z* base, const Z& exp, const Z& mod) = 0; 
  
      /** Potenciaci�n modular.
       *
       * Realizar una potenciaci�n modular devolviendo el resultado.
       * 
       *  @param base Entero base de la potenciaci�n.
       * 
       * @param exp Exponente de la operaci�n de potenciaci�n.
       * Si el m�dulo @a mod suministrado no es primo y se pasa un
       * valor de exponente negativo, se producir� un error de tipo
       * "ElementoNoInvertible".
       *
       * @param mod El m�dulo reductor.
       *
       * @return El entero resultado de \f$base^{exp} \bmod mod\f$.
       */
      Z potModular(Z base, const Z& exp, const Z& mod); 
 
      /** C�lculo de la inversa.
       *
       * Realizar el c�lculo de la inversa en un cuerpo finito.
       * 
       * @param base Entero a invertir.
       * 
       * @param mod El m�dulo reductor. Si este valor no es primo, se
       * producir� un error de tipo "ElementoNoInvertible".
       *
       * @return El entero resultado de \f$base^{-1} \bmod mod\f$.
       */
      Z inversa(const Z& base, const Z& mod);

      virtual ~PotModular(){}
  };



  /* IMPLEMENTACIONES */
  /** Potenciaci�n entera mediante el algoritmo de la ventana
   * deslizante.
   *
   * Descrito en Handbook of Applied Cryptography, algoritmo 14.85
   *
   * @note Es el m�todo que la librer�a utiliza por omisi�n.
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

  
  /** Potenciaci�n entera mediante el algoritmo "Derecha a izquierda".
   *
   * Descrito en The Art of Computer Programming, Vol.2 p�g. 8 \n
   *             Handbook of Applied Cryptography 614 \n
   *             A course in computational algebraic number theory,
   *             p�g. 8
   *
   */
  class PotRightLeft : public Potencia
  {
    public:
      virtual void potencia(Z* base,  CifraSigno exp);

      virtual ~PotRightLeft(){}
  };
  


  /* modular */
  /** Potenciaci�n modular entera mediante el m�todo de Montgomery.
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
 
  /** Potenciaci�n modular entera utilizando reducci�n de Barrett.
   * 
   * Descrito en "Implementing the RSA public key encryption algorithm 
   * on a standard digital signal processor", Paul Barrett, 1986.
   *
   * @note Es el m�todo que la librer�a utiliza por omisi�n.
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
