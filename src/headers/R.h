/* 
 * $Id$
 */

/************************ R.h ***************************************
 * Cabecera que define el tipo de dato para un número en coma       *
 * flotante.                                                        *
 * *****************************************************************/

#ifndef __R_H
#define __R_H

#include <vector>
#include <string>
#include <iostream>
#include <utility>
#include <cmath>
#include <limits>
#include <sstream>

#include "MPPDataType.h"
#include "Constants.h"
#include "Errors.h"
#include "Z.h"
#include "Field.h"

namespace mpplas {

/** Clase para la representación de enteros. */
  class R: public Field<R>, public MPPDataType {
    public:
      // constructores
      R() /**< constructor por defecto */;
      R( const R& ); /**< constructor de copia */
      R( const SignedDigit ); /**< construccion desde simple precision */
      R( const Digit ); /**< construccion desde 'token' básico */
      explicit R( const char* ); /**< construccion desde cadena de caracteres */
      explicit R( const std::string& str ); /**< construction from a std::string */ 
      explicit R( const double ); /**< construccion desde double */
      explicit R( const Z& ); /**< constructor desde Z */


      /** Función de conversión de tipo Digit a R (real).
       *
       *  @par Complejidad:
       *       \f$O(1)\f$
       * 
       *  @param numSimple Número de precisión simple a convertir a real.
       *
       *  @return El real correspondiente a la conversión.
       */
      //    static R convertir(const Digit numSimple);
      /** Función de conversión de tipo SignedDigit a R (real).
       *
       *  @par Complejidad:
       *       \f$O(1)\f$
       * 
       *  @param numSimple Número de precisión simple con signo a convertir a real.
       *
       *  @return El real correspondiente a la conversión.
       */  
      //    static R convertir(const SignedDigit numSimple);
      /** Función de conversión de tipo cadena de caracteres a R (real).
       * 
       *  @par Complejidad:
       *       \f$O(n)\f$
       * 
       *  @param cadena Vector de caracteres que representa el número a
       *  convertir a real.
       *
       *  @exception mpplas::Errores::Sintactico Error sintáctico en la
       *  cadena.
       *
       *  @return El real correspondiente a la conversión.
       */
      //   static R convertir(const char* cadena);
      /** Función de conversión de tipo double a R (real).
       *
       *  @par Complejidad:
       *       \f$O(1)\f$
       * 
       *  @param numFlotante Número flotante de precisión simple a convertir a real.
       *
       *  @return El real correspondiente a la conversión.
       */
      //   static R convertir(const double numFlotante);
      /** Función de conversión de Z (entero) a R (real).
       *
       *  @par Complejidad:
       *       \f$O(1)\f$
       * 
       *  @param entero Número entero a convertir a real.
       *
       *  @return El real correspondiente a la conversión.
       */
      //   static R convertir(const Z& entero);

      /** Operador de asignación desde R.
       *
       *  @par Complejidad:
       *       \f$O(n)\f$
       * 
       * @param origen Real a asignar a la instancia invocadora. 
       *
       * @return Referencia a *this 
       */
      R& operator=(const R& origen);

      // OPERADORES ARITMETICOS
      /** Operador de suma acumulada.
       *
       * @pre *this y sumandoDerecha reales válidos.
       * @post *this sumado el valor del real sumandoDerecha.
       * 
       *  @par Complejidad:
       *       \f$O(n)\f$
       * 
       * @param sumandoDerecha Real a sumar a la instancia del número real invocadora *this. 
       *
       * @return Referencia a *this.
       */
      R& operator+=(const R& sumandoDerecha);
      /** Operador de resta acumulada.
       *
       * @pre *this y sustraendo reales válidos.
       * @post *this restado el valor del real sustraendo.
       * 
       *  @par Complejidad:
       *       \f$O(n)\f$
       * 
       * @param sustraendo Real a restar a la instancia del número real invocadora *this. 
       *
       * @return Referencia a *this.
       */
      R& operator-=(const R& sustraendo);
      /** Operador de producto acumulado.
       *
       * @pre *this y factorDer reales válidos.
       * @post *this multiplicado por el valor del real factorDer.
       * 
       *  @par Complejidad:
       *       \f$O(n^{\log_2(3)})\f$     
       * 
       * @param factorDer Real a multiplicar por la instancia del número real invocadora *this. 
       *
       * @return Referencia a *this.
       */
      R& operator*=(const R& factorDer);
      /** Operador de cociente acumulado.
       *
       * @pre *this y divisor reales válidos.
       * @post *this cociente de la división de si mismo por el valor del Entero divisor.
       * 
       *  @par Complejidad:
       *       \f$O(n \cdot m)\f$
       *       con \f$n\f$ y \f$m\f$ tamaños de dividendo y divisor.      
       *       
       * @param divisor Real a actuar de divisor de *this. 
       *
       * @return Referencia a *this.
       */
      R& operator/=(const R& divisor);

      /******************/
      /** Versión de precisión simple de suma. @sa operator+=(const R&)*/
      R& operator+=(const double);
      /** Versión de precisión simple de resta. @sa operator-=(const R&)*/
      R& operator-=(const double);
      /** Versión de precisión simple de producto. @sa operator*=(const R&)*/
      R& operator*=(const double);
      /** Versión de precisión simple de división. @sa operator/=(const R&)*/
      R& operator/=(const double);

      /*************/
      /** Operador de potenciación acumulada.
       *
       * @param exp Entero reprensentado el exponente al que elevar.
       *
       * @return *this, instancia de la clase actual tras elevarla a
       * exp.
       * 
       * Se realiza la operación \f$(*this) = (*this)^{exp}\f$
       *
       * \exception 
       * Errores::DemasiadoGrande Si el entero que
       * representa el exponente exp es demasiado grande ( mayor que
       * CIFRA_MAX )
       *
       * \note
       * Esta función invoca a la versión con argumento SignedDigit. En
       * cualquier caso, depende de la implementación particular de la
       * clase Potencia accesible mediante la clase MethodsFactory.
       * 
       */
      R& operator^=(const Z& exp); 

      /** Operador de potenciación acumulada.
       *
       * @param exp Dato SignedDigit reprensentado el exponente al que elevar.
       *
       * @return *this, instancia de la clase actual tras elevarla a
       * exp.
       * 
       * Se realiza la operación \f$(*this) = (*this)^{exp}\f$
       *
       * \exception 
       * Errores::ExponenteNegativo Si el entero que
       * representa el exponente exp es negativo.
       */
      R& operator^=(SignedDigit exp); 


      R& abs();

      R& square(void);

      ////////////////////////////////////
      //   OPERADORES DE DESPLAZAMIENTO //
      ////////////////////////////////////
      /** Operador de desplazamiento a la derecha acumulado.
       *
       * @param n Exponente de la potencia de 2 entre la que dividir
       * *this.
       * @return *this, instancia de la clase actual tras la división.
       *
       * Se "desplaza" (*this) un numero @a n de bits hacia la derecha.
       * Esta analogía no es del todo precisa, al estar trabajando en
       * reales, no en enteros. En cualquier caso, se trata de una
       * división entre una potencia de 2.
       * 
       * \note
       * En la representación actual de reales (i.e, \f$ mantisa \times 2^k \f$), esta 
       * operación es equivalente a restar @a n a \f$ k \f$. <B> NO
       * DEPENDER DE ESTO</B>: es un detalle particular de la 
       * representación actual, que no tiene porque cumplirse en
       * posteriores revisiones.
       */
      R& operator>>=(const int n);

      /** Operador de desplazamiento a la izquierda acumulado.
       *
       * @param n Exponente de la potencia de 2 por la que multiplicar
       * *this.
       * @return *this, instancia de la clase actual tras la
       * multiplicación.
       *
       * Se "desplaza" (*this) un numero @a n de bits hacia la
       * izquierda.
       * Esta analogía no es del todo precisa, al estar trabajando en
       * reales, no en enteros. En cualquier caso, se trata de una
       * multiplicación por una potencia de 2.
       * 
       * \note
       * En la representación actual de reales (i.e, \f$ mantisa \times 2^k \f$), esta 
       * operación es equivalente a sumar @a n a \f$ k \f$. <B> NO
       * DEPENDER DE ESTO</B>: es un detalle particular de la 
       * representación actual, que no tiene porque cumplirse en
       * posteriores revisiones.
       */
      R& operator<<=(const SignedDigit n);



      // OPERADORES DE COMPARACION
      //
      /** Operador "Mayor que".
       *
       * @param der real a comparar con *this. 
       * @return "true" o "false"
       *
       * La comparación se correspondería con el predicado \f$(*this) > der\f$
       */
      bool operator>(const R& der) const;
      /** Operador "Menor que".
       *
       * @param der real a comparar con *this. 
       * @return "true" o "false"
       *
       * La comparación se correspondería con el predicado \f$(*this) < der\f$
       */
      bool operator<(const R& der) const;
      /** Operador "Igual a".
       *
       * @param der real a comparar con *this. 
       * @return "true" o "false"
       *
       * La comparación se correspondería con el predicado \f$(*this) = der\f$
       */
      bool operator==(const R& der) const;
      /** Operador "Distinto de".
       *
       * @param der real a comparar con *this. 
       * @return "true" o "false"
       *
       * La comparación se correspondería con el predicado \f$(*this) \neq der\f$
       */
      bool operator!=(const R& der) const;
      /** Operador "Mayor o igual que".
       *
       * @param der real a comparar con *this. 
       * @return "true" o "false"
       *
       * La comparación se correspondería con el predicado \f$(*this) \geq der\f$
       */
      bool operator>=(const R& der) const;
      /** Operador "Menor o igual que".
       *
       * @param der real a comparar con *this. 
       * @return "true" o "false"
       *
       * La comparación se correspondería con el predicado \f$(*this) \leq der\f$
       */
      bool operator<=(const R& der) const;


      ~R();

      //funciones utiles

      virtual std::string toString() const;
      virtual std::string toHRString() const;
      std::string toString(int decimalPlaces) const;

      /** Hacer cero.
       * 
       * \par Complejidad:
       *      \f$ O(1) \f$
       *
       * @return Referencia a *this.
       *  
       * Hace que el real sobre el que se invoca el método pase a ser
       * igual a 0.\n
       *  El objetivo de este método es ser un atajo para la frecuente 
       *  operacion \f$ x = 0 \f$ para el real \f$x\f$
       *
       * \note Se fuerza asimismo el signo positivo, aunque pueda carecer de 
       * sentido el poner un signo al cero.
       */
      R& makeZero();
      /** Hacer uno.
       * 
       * \par Complejidad:
       *      \f$ O(1) \f$
       *
       * @return Referencia a *this.
       *  
       * Hace que el real sobre el que se invoca el método pase a ser
       * igual a 1.
       *  El objetivo de este método es ser un atajo para la frecuente 
       *  operacion \f$ x = 1 \f$ para el real \f$x\f$
       *
       */
      R& makeOne();

      /** Comprobar igualdad a cero.
       * 
       * \par Complejidad:
       *      \f$ O(1) \f$
       *
       * @return true si *this es un real igual a 0\n 
       *         false si no.
       *  
       *  El objetivo de este método es ser un atajo para la frecuente 
       *  operacion de comprobar si un número es cero.
       */
      bool isZero(void) const;

      bool isOne(void) const;


      /** Número de bits en la mantisa.
       *
       * @par Complejidad:
       *      \f$O(1)\f$
       * 
       * @return El número de bits de la mantisa de (*this).
       *
       * Se devuelve un dato de tipo int con valor el número de
       * bits que ocupa la mantisa del real sobre la que se aplica 
       * el método.
       */ 
      inline int getBitLength(void) const { return mantisa_.getBitLength(); }

      /** Cambiar el signo.
       * 
       * \par Complejidad:
       *      \f$ O(1) \f$
       *
       * @return Referencia a *this.
       *  
       * Hace que el real sobre el que se invoca el método cambie de signo.
       *  El objetivo de este método es ser un atajo para la frecuente 
       *  operacion \f$ x = -x \f$ para el real \f$x\f$
       *
       */
      virtual R& invertSign(void) { mantisa_.invertSign(); return *this; }



      inline bool isPositive(void) const { return this->signo() > 0; }
      inline bool isNegative(void) const { return this->signo() < 0; }

      inline R& makePositive(void) { mantisa_.hacerPositivo(); return *this; } 
      inline R& makeNegative(void) { mantisa_.hacerPositivo(); return *this; } 


      //funciones relativas a precision
      /** Ver precisión actual de salida.
       *
       *  Este método estático muestra el valor actual de la precisión de
       *  salida para reales.
       *
       * @par Complejidad:
       *      \f$O(1)\f$
       *  
       * @return El valor actual de la precisión de salida para
       * reales.
       *
       */
      inline 
        static int precisionSalida(void) { 
          if( precisionSalida_ == 0 ){
            return (int)std::floor(Constants::LOG_10_2 * R::precision() )-3;
          }
          else{
            return precisionSalida_; 
          }
        }

      /** Ver precisión interna considerada.
       *
       *  Este método estático muestra el valor actual de la precisión interna (en bits)
       *  utilizada para representar los reales.
       *
       * @par Complejidad:
       *      \f$O(1)\f$
       *  
       * @return El valor actual de la precisión interna utilizada
       * para representar los reales.
       *
       */
      inline 
        static int precision(void) { return precision_; }

      /** Establecer precisión de salida.
       *
       *  Este método estático establece el valor actual de la precisión de
       *  salida para rales.
       *
       * @par Complejidad:
       *      \f$O(1)\f$
       *  
       *  @param nueva La nueva precisión a utilizar.
       *
       */
      inline 
        static void precisionSalida(int nueva) 
        { precisionSalida_ = nueva; return;}

      /** Establecer precisión interna considerada.
       *
       *  Este método estático establece el valor actual de la precisión interna (en bits)
       *  utilizada para representar los reales.
       *
       * @par Complejidad:
       *      \f$O(1)\f$
       *  
       *  @param nueva La nueva precisión a utilizar.
       */
      inline 
        static void precision(int nueva) 
        { precision_ = nueva; return; }


      //funciones relacionadas con los R
      /** Función suelo.
       *
       * Realiza el cálculo de la función suelo sobre *this. Esta
       * función se define como el mayor entero menor que su argumento.
       *
       * @par Complejidad:
       *      \f$O(1)\f$
       *
       * @return Entero representando el mayor entero menor que el real *this.
       */
      Z floor(void) const;

      /** Función techo.
       *
       * Realiza el cálculo de la función techo sobre *this. Esta
       * función se define como el menor entero mayor que su argumento.
       *
       * @par Complejidad:
       *      \f$O(1)\f$
       *
       * @return Entero representando el menor entero mayor que el real *this.
       */
      Z ceil(void) const;

      /** Normalización.
       *
       * Se normaliza *this en base a la precisión @a nprec.
       * Esto implica lo siguiente:
       *
       * <ul>
       * <li>  Asegurar la unicidad de la representación del cero:
       *       \f$ (mantisa = 0) \Longrightarrow (exponente = 0) \f$.
       * <li>  Ajuste de la longitud de la mantisa a la precisión de
       *       trabajo o a @a nprec si se especifica.
       * <li>  Eliminación de las potencias de 2 de la mantisa y su
       *       traslado al exponente.
       * </ul>
       *
       * @par Complejidad:
       *      \f$O(n)\f$
       *
       * @param nprec La precisión a considerar.
       */
      void normalizar(int nprec = R::precision_);

      //funcciones de informacion

      /** Valor del exponente.
       *
       * Devuelve un dato SignedDigit con el valor del exponente de la
       * representación del real.
       * @par Complejidad:
       *      \f$O(1)\f$
       *
       * @return Valor del exponente de la representación del real.
       */
      inline
        SignedDigit exponente() const { return exponente_; }
      inline
        /** Valor de la mantisa.
         *
         * Devuelve un entero con el valor de la mantisa de la
         * representación del real.
         * @par Complejidad:
         *      \f$O(1)\f$
         *
         * @return Valor de la mantisa de la representación del real.
         */
        Z mantisa() const { return mantisa_; }


      inline double getSPApprox() const { return _spApprox; }

      /** Signo del real. 
       * 
       * @par Complejidad:
       *      \f$O(1)\f$
       *
       *  @return Un valor mayor que 0 (típicamente "1")
       *          si el real es mayor o igual que 0.\n
       *          Un valor menor que 0 (típicamente "-1") si no.
       */
      inline 
        int8_t signo(void) const { return mantisa_.signo(); }


      static const R ZERO;
      static const R ONE;

      /* Ring, Group and Field methods */

      static const bool addCommutative;
      static const bool groupCyclic;

      static const bool unitaryRing;
      static const bool multCommutative;
      static const bool multAssociative;
      static const bool divisionRing;


      R getMultInverse() const {
        R tmp(ONE);
        tmp /= (*this);
        return tmp;
      }
      static const R& getMultIdentity() {
        return ONE ;
      };
      static const R& getAddIdentity() {
        return ZERO;
      };
      R getAddInverse()  const{
        R tmp(*this);
        tmp.invertSign();
        return tmp;
      };
      static const R& getGroupGenerator() {
        return ONE;
      } 
      Z getCharacteristic() const {
        return Z::ZERO;
      }

    protected:
      SignedDigit exponente_;
      Z mantisa_;
      static int precision_; /**< Valor por defecto = 300. @sa R::precision() */
      static int precisionSalida_;/**< Valor por defecto = 20. @sa R::precisionSalida() */

    private:
      double _spApprox;

      /** Operador de salida del número */
      friend std::ostream& operator<<(std::ostream&, R);
      /** Operador obtencion del número */
      friend std::istream& operator>>(std::istream&, R&); 

  };
  
  //se devuelve un objeto (y no una referencia) debido a lo
  //expuesto en stroustrup pág. 297 ultimo parrafo.
  //
  //Estas funciones no son amigas de class Z por lo expuesto
  //en stroustrup 11.3.1 (pag 282)
  
  /** Suma no acumulativa de reales.
   *
   * @param a Sumando izquierdo.
   * @param b Sumando derecho.
   * 
   * @return El real suma de los argumentos. 
   */
  R operator+(R a, const R &b);
  
  /** Resta no acumulativa de reales.
   *
   * @param a Minuendo.
   * @param b Sustraendo.
   * 
   * @return El real resta de los argumentos. 
   */
  R operator-(R a, const R &b);
  
  
  
  
  /** Producto no acumulativa de reales.
   *
   * @param a Factor izquierdo.
   * @param b Factor derecho.
   * 
   * @return El real producto de los argumentos. 
  */
  R operator*(R a, const R &b);
  
  /** División no acumulativa de reales.
   *
   * @param a Dividendo.
   * @param b Divisor.
   * 
   * @return El real cociente \f$\lfloor(a/b)\rfloor\f$. 
   */
  R operator/(R a, const R &b);

  /** Versión de precisión simple de operator+(R, const R&)*/
  R operator+(const double, R);
  /** Versión de precisión simple de operator-(R, const R&)*/
  R operator-(const double, R);
  /** Versión de precisión simple de operator*(R, const R&)*/
  R operator*(const double, R);
  /** Versión de precisión simple de operator/(R, const R&)*/
  R operator/(const double, const R&);

  /** Versión de precisión simple de operator+(R, const R&)*/
  R operator+(R, const double);
  /** Versión de precisión simple de operator-(R, const R&)*/
  R operator-(R, const double);
  /** Versión de precisión simple de operator*(R, const R&)*/
  R operator*(R, const double);
  /** Versión de precisión simple de operator/(R, const R&)*/
  R operator/(R, const double);

  
  /** Operator - unario -> cambio de signo */
  R operator-(R);     
  
  /** Operador de potenciación.
   *
   * @param base Real base de la potenciación.
   * @param exp Entero exponente.
   *
   * @return Real igual a \f$base^{exp}\f$
   * @sa class Potencia.
   *
   * @note El exponente ha de ser \f$\leq 2^{BASE}\f$ o se lanzará un
   * error de tipo Errores::DemasiadoGrande
   *
   */
  R operator^(R base, const Z& exp); 

   /** Operador de potenciación.
   *
   * @param base Real base de la potenciación.
   * @param exp SignedDigit exponente.
   *
   * @return Real igual a \f$base^{exp}\f$
   * @sa class Potencia.
   *
   */
  R operator^(R base, SignedDigit exp); 


  /** Operador de "desplazamiento" a la derecha no acumulativo.
   *
   * @param real El real a "desplazar".
   * @param n El número de posiciones a "desplazar".
   *
   * @return El real "desplazado" @a n posiciones a la
   * derecha.
   *
   * @sa R::operator>>=(const int n) */
  R operator>>(R real, const int n);

  /** Operador de "desplazamiento" a la izquierda no acumulativo.
   *
   * @param real El real a desplazar.
   * @param n El número de posiciones a "desplazar".
   *
   * @return El real desplazado @a n posiciones a la
   * izquierda.
   *
   * @sa R::operator<<=(const int n) */
  R operator<<(R real, const int n);


  inline R abs(R x){
    x.abs();
    return x;
  }


  
}
#endif

