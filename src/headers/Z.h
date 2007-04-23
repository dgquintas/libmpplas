/* 
 * $Id$
 */

/************************ Z.h ***************************************
 * Cabecera que define el tipo de dato para un número entero.       *
 * El 'token' básico será el tipo 'Digit' definido en el núcleo.    *
 * *****************************************************************/

#ifndef __Z_H
#define __Z_H


#include <string>
#include "MiVec.h"
#include "err.h"
#include "constants.h"

namespace mpplas
{
  /** Clase para la representación de enteros. */
  class Z 
  {

    public:
      /////////////////////
      //   CONSTRUCTORES //
      /////////////////////
      Z() /**< constructor por defecto */;
      Z( const Z& otro); /**< Constructor de copia.
                           @param otro Entero a copiar. */

      explicit Z( const SignedDigit ); /**< construccion desde simple precision */
      Z( const Digit ); /**< construccion desde 'token' básico */
      explicit Z( const double ); /**< construccion desde double  */
      explicit Z( const char* ); /**< construccion desde cadena de caracteres */
      explicit Z(const std::string& str); /**< construction from a std::string */

      Z( const MiVec<Digit>& vec);

      ////////////////////////////////
      //   OPERADORES DE CONVERSION //
      ////////////////////////////////
      //se devuelve un objeto (y no una referencia) debido a lo
      //expuesto en stroustrup pág. 297 ultimo parrafo.
      //
      //Estas funciones no son amigas de class Z por lo expuesto
      //en stroustrup 11.3.1 (pag 282)

      /** Función de conversión de tipo Digit a Z (entero).
       *
       *  @par Complejidad:
       *       \f$O(1)\f$
       * 
       *  @param numSimple Número de precisión simple a convertir a entero.
       *
       *  @return El entero correspondiente a la conversión.
       */
//      static Z convertir(const Digit numSimple);


      /** Función de conversión de tipo long a Z (entero).
       *
       *  @par Complejidad:
       *       \f$O(1)\f$
       * 
       *  @param numSimple Número de precisión simple a convertir a entero.
       *
       *  @return El entero correspondiente a la conversión.
       */
//      static Z convertir(const SignedDigit numSimple);


      /** Función de conversión de tipo cadena de caracteres a Z (entero).
       * 
       *  @par Complejidad:
       *       \f$O(n)\f$
       * 
       *  @param cadena Vector de caracteres que representa el número a
       *  convertir a entero.
       *
       *  @exception mpplas::Errors::Sintactico Error sintáctico en la
       *  cadena.
       *
       *  @return El entero correspondiente a la conversión.
       */
//      static Z convertir(const char* cadena) throw(Errors::Sintactic);


      /** Función de conversión de tipo double a Z (entero).
       *
       *  @note La conversión trunca el número double.
       *  @par Complejidad:
       *       \f$O(1)\f$
       * 
       *  @param numFlotante Número de precisión simple a convertir a entero.
       *
       *  @return El entero correspondiente a la conversión.
       */
//      static Z convertir(const double numFlotante);

      /** Función de conversión de tipo MiVec<Digit> a Z (entero).
       *
       *  @par Complejidad:
       *       \f$O(1)\f$
       * 
       *  @param vec Vector de Digit 's representando un entero
       *  positivo en base sizeof(Digit)*8 
       *
       *  @return El entero correspondiente a la conversión.
       */
//      static Z convertir(const MiVec<Digit>& vec);


      /** Operador de asignación desde Z.
       *
       *  @par Complejidad:
       *       \f$O(n)\f$
       * 
       * @param origen Entero a asignar a la instancia invocadora. 
       *
       * @return Referencia a *this 
       */
      Z& operator=(const Z& origen);


      /** Operador de asignación desde Digit.
       *
       *  @par Complejidad:
       *       \f$O(1)\f$
       * 
       * @param origenSimple Número simple a asignar a la instancia invocadora. 
       *
       * @return Referencia a *this 
       */
      Z& operator=(const Digit origenSimple);

      
      //////////////////////////////
      //   OPERADORES ARITMETICOS //
      //////////////////////////////
      /** Operador de suma acumulada.
       *
       * @pre *this y sumandoDerecha Enteros válidos.
       * @post *this sumado el valor del Entero sumandoDerecha.
       * 
       *  @par Complejidad:
       *       \f$O(n)\f$
       * 
       * @param sumandoDerecha Entero a sumar a la instancia de Entero invocadora *this. 
       *
       * @return Referencia a *this.
       */
     Z& operator+=(const Z& sumandoDerecha);

      /** Operador de resta acumulada.
       *
       * @pre *this y sustraendo Enteros válidos.
       * @post *this restado el valor del Entero sustraendo.
       * 
       *  @par Complejidad:
       *       \f$O(n)\f$
       * 
       * @param sustraendo Entero a restar a la instancia de Entero invocadora *this. 
       *
       * @return Referencia a *this.
       */
      Z& operator-=(const Z& sustraendo);

     /** Operador de producto acumulado.
       *
       * @pre *this y factorDer Enteros válidos.
       * @post *this multiplicado por el valor del Entero factorDer.
       * 
       *  @par Complejidad:
       *       \f$O(n^{\log_2(3)})\f$
       *        
       * @param factorDer Entero a multiplicar por la instancia de Entero invocadora *this. 
       *
       * @return Referencia a *this.
       */
      Z& operator*=(const Z& factorDer);

      /** Operador de cociente acumulado.
       *
       * @pre *this y divisor Enteros válidos.
       * @post *this cociente de la división de si mismo por el valor del Entero divisor.
       * 
       *  @par Complejidad:
       *       \f$O(n \cdot m)\f$
       *       con \f$n\f$ y \f$m\f$ tamaños de dividendo y divisor.
       *
       * @param divisor Entero a actuar de divisor de *this. 
       *
       * @return Referencia a *this.
       */
      Z& operator/=(const Z& divisor);
 
      /** Operador de resto acumulado.
       *
       * @pre *this y divisor Enteros válidos.
       * @post *this resto de la división de si mismo por el valor del Entero divisor.
       * 
       *  @par Complejidad:
       *       \f$O(n \cdot m)\f$
       *       con \f$n\f$ y \f$m\f$ tamaños de dividendo y divisor.
       *       
       * @param divisor Entero a actuar de divisor de *this. 
       *
       * @return Referencia a *this.
       */
      Z& operator%=(const Z& divisor);


      /** Operador de AND lógico a nivel de bits acumulado.
       *
       * @par Complejidad:
       *      \f$O(n)\f$
       *      con \f$n\f$ las cifras en base BASE.
       *
       *  Realiza una operacion AND lógica a nivel de bits entre el
       *  entero sobre el que se invoca el método y el parámetro dado.
       * 
       *  @param der Operando de la derecha en la operación AND.
       *
       *  @return Referencia a *this.
       */
      Z& operator&=(const Z& der);
  
      /** Operador de OR lógico a nivel de bits acumulado.
       *
       * @par Complejidad:
       *      \f$O(n)\f$
       *      con \f$n\f$ las cifras en base BASE.
       *
       *  Realiza una operacion OR lógica a nivel de bits entre el
       *  entero sobre el que se invoca el método y el parámetro dado.
       * 
       *  @param der Operando de la derecha en la operación OR.
       *
       *  @return Referencia a *this.
       */
       Z& operator|=(const Z& der);

       /** Operación de XOR lógico a nivel de bits acumulado.
       *
       * @par Complejidad:
       *      \f$O(n)\f$
       *      con \f$n\f$ las cifras en base BASE.
       *
       *  Realiza una operacion XOR lógica a nivel de bits entre el
       *  entero sobre el que se invoca el método y el parámetro dado.
       * 
       *  @param der Operando de la derecha en la operación XOR.
       *
       *  @return Referencia a *this.
       */
       Z& XOR(const Z& der);

      /** Hacer el cuadrado.
       *  
       *  Versión especializada de la multiplicación con una mayor
       *  eficiencia en el calculo del cuadrado de un número.
       *
       *  @post *this es el cuadrado de su valor original.
       *  
       *  @param x Entero a elevar al cuadrado.
       *
       *  @return Referencia a *this.
       */
      Z& cuadrado(void);

       /** Hacer el cuadrado modular.
       *  
       *  Versión especializada de la multiplicación y posterior
       *  reducción modular con una mayor eficiencia en el calculo 
       *  del cuadrado de un número.
       *
       *  @post *this es el cuadrado de su valor original reducido
       *  módulo @e mod. \f$ x^{2} \bmod mod \f$
       *  
       *  @param x Entero a elevar al cuadrado.
       *  @param mod Módulo reductor.
       *
       *  @return Referencia a *this.
       */
      Z& cuadradoModular(const Z& mod);
    
      /** Factorial.
       *  
       *  @pre *this ha de ser \f$ \leq BASE \f$.
       *  
       *  @par Complejidad:
       *    \f$ O(n^{3}) \f$
       *
       *  Cálculo del factorial con algunas optimizaciones.
       *
       *  @return Referencia a *this.
       */
      Z& factorial(void);
      
      /** Raiz cuadrada.
       *
       *  @par Complejidad:
       *        \f$ O(\log^{2}{n}) \f$
       * 
       *  Hace la raiz cuadrada entera del número entero sobre el que
       *  se aplique el método. 
       *
       *  @return Entero verificando ser igual a \f$
       *  \lfloor\sqrt{x}\rfloor \f$.
       */
      Z& raizCuadrada(void);
      
      /** Determinar si es cuadrado perfecto.
       * 
       *  @par Complejidad:
       *        \f$ O(\log^{2}{n}) \f$
       *
       * Se determina si el entero sobre el que se invoca el método es
       * un cuadrado perfecto (esto es, si su raíz cuadrada es un
       * entero)
       *
       * @param raiz Argumento opcional que se rellenará con la raiz
       * cuadrada en caso de ser el entero sobre el que se invoca el
       * método un cuadrado perfecto. \n
       * En caso de no serlo, tomará el valor -1
       * 
       * @return @e true si es cuadrado perfecto.\n
       *         @e false si no es cuadrado perfecto.
       *
       * @note La raíz devuelta será la positiva. De ahí que se
       * utilice a -1 como indicador de no existencia de raiz para el
       * parametro opcional @e raíz
       */
      bool esCuadrado(Z* raiz = NULL);
      
      /** Versión de precisión simple de suma. @sa operator+=(const Z&)*/
      Z& operator+=(const SignedDigit); 
      /** Versión de precisión simple de resta. @sa operator-=(const Z&)*/
      Z& operator-=(const SignedDigit); 
      /** Versión de precisión simple de multiplicacion. @sa operator*=(const Z&)*/
      Z& operator*=(const SignedDigit); 
      /** Versión de precisión simple de división. @sa operator/=(const Z&)*/
      Z& operator/=(const SignedDigit); 
      /** Versión de precisión simple de resto. @sa operator%=(const Z&)*/
      Z& operator%=(const SignedDigit); 
      /** Versión de precisión simple de AND. @sa operator&=(const Z&)*/
      Z& operator&=(const SignedDigit);
      /** Versión de precisión simple de OR. @sa operator|=(const Z&)*/
      Z& operator|=(const SignedDigit);
      /** Versión de precisión simple de XOR. @sa XOR(const Z&)*/
      Z& XOR(const SignedDigit);
      
      
      /** Versión de precisión simple de suma. @sa operator+=(const Z&)*/
      Z& operator+=(const Digit); 
      /** Versión de precisión simple de resta. @sa operator-=(const Z&)*/
      Z& operator-=(const Digit); 
      /** Versión de precisión simple de multiplicacion. @sa operator*=(const Z&)*/
      Z& operator*=(const Digit); 
      /** Versión de precisión simple de división. @sa operator/=(const Z&)*/
      Z& operator/=(const Digit); 
      /** Versión de precisión simple de resto. @sa operator%=(const Z&)*/
      Z& operator%=(const Digit); 
      /** Versión de precisión simple de AND. @sa operator&=(const Z&)*/
      Z& operator&=(const Digit);
      /** Versión de precisión simple de OR. @sa operator|=(const Z&)*/
      Z& operator|=(const Digit);
      /** Versión de precisión simple de XOR. @sa XOR(const Z&)*/
      Z& XOR(const Digit);


      //////////////////////////////////
      //   OPERADORES DE POTENCIACION //
      //////////////////////////////////
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
       * Errors::TooBig Si el entero que
       * representa el exponente exp es demasiado grande ( mayor que
       * CIFRA_MAX )
       *
       * \note
       * Esta función invoca a la versión con argumento Digit. En
       * cualquier caso, depende de la implementación particular de la
       * clase Potencia accesible mediante la clase Funciones.
       * 
       */
      Z& operator^=(const Z& exp); 
       /** Operador de potenciación acumulada.
       *
       * @param exp Dato Digit reprensentado el exponente al que elevar.
       *
       * @return *this, instancia de la clase actual tras elevarla a
       * exp.
       * 
       * Se realiza la operación \f$(*this) = (*this)^{exp}\f$
       *
       * \note
       * Esta función depende de la implementación particular de la
       * clase Potencia accesible mediante la clase Funciones.
       */
      Z& operator^=(Digit exp); 

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
       * Errors::ExponenteNegativo Si el entero que
       * representa el exponente exp es negativo.
       *
       * \note
       * Esta función invoca a la versión con argumento Digit. En
       * cualquier caso, depende de la implementación particular de la
       * clase Potencia accesible mediante la clase Funciones.
       * 
       */
      Z& operator^=(SignedDigit exp); 

      /////////////////////////////////
      //   OPERADORES DE COMPARACION //
      /////////////////////////////////
      /** Operador "Mayor que".
       *
       * @param der Entero a comparar con *this. 
       * @return "true" o "false"
       *
       * La comparación se correspondería con el predicado \f$(*this) > der\f$
       *
       * \note
       * Esta función delega la comparación en la familia de rutinas
       * de comparacion de la clase vCPUVectorial. Por tanto, La cota
       * de complejidad de esta función sera una constante de éstas.
       * Ver grafo de dependencias para determinar qué funciones de
       * vCPUVectorial se utilizan en concreto.
       */ 
      bool operator>(const Z& der) const;

      
      /** Operador "Menor que".
       *
       * @param der Entero a comparar con *this. 
       * @return "true" o "false"
       *
       * La comparación se correspondería con el predicado \f$(*this) < der\f$
       *
       * \note
       * Esta función delega la comparación en la familia de rutinas
       * de comparacion de la clase vCPUVectorial. Por tanto, La cota
       * de complejidad de esta función sera una constante de éstas.
       * Ver grafo de dependencias para determinar qué funciones de
       * vCPUVectorial se utilizan en concreto.
       */ 
      bool operator<(const Z& der) const;
  
      
      /** Operador "Igual".
       *
       * @param der Entero a comparar con *this. 
       * @return "true" o "false"
       *
       * La comparación se correspondería con el predicado \f$(*this) = der\f$
       *
       * \note
       * Esta función delega la comparación en la familia de rutinas
       * de comparacion de la clase vCPUVectorial. Por tanto, La cota
       * de complejidad de esta función sera una constante de éstas.
       * Ver grafo de dependencias para determinar qué funciones de
       * vCPUVectorial se utilizan en concreto.
       */ 
      bool operator==(const Z& der) const;
      
      /** Operador "Distinto".
       *
       * @param der Entero a comparar con *this. 
       * @return "true" o "false"
       *
       * La comparación se correspondería con el predicado \f$(*this) \neq der\f$
       *
       * \note
       * Esta función delega la comparación en la familia de rutinas
       * de comparacion de la clase vCPUVectorial. Por tanto, La cota
       * de complejidad de esta función sera una constante de éstas.
       * Ver grafo de dependencias para determinar qué funciones de
       * vCPUVectorial se utilizan en concreto.
       */ 
      bool operator!=(const Z& der) const;
      
      /** Operador "Mayor o igual que".
       *
       * @param der Entero a comparar con *this. 
       * @return "true" o "false"
       *
       * La comparación se correspondería con el predicado \f$(*this) \geq der\f$
       *
       * \note
       * Esta función delega la comparación en la familia de rutinas
       * de comparacion de la clase vCPUVectorial. Por tanto, La cota
       * de complejidad de esta función sera una constante de éstas.
       * Ver grafo de dependencias para determinar qué funciones de
       * vCPUVectorial se utilizan en concreto.
       */ 
      bool operator>=(const Z& der) const;
      
      
      /** Operador "Menor o igual que".
       *
       * @param der Entero a comparar con *this. 
       * @return "true" o "false"
       *
       * La comparación se correspondería con el predicado \f$(*this) \leq der\f$
       *
       * \note
       * Esta función delega la comparación en la familia de rutinas
       * de comparacion de la clase vCPUVectorial. Por tanto, La cota
       * de complejidad de esta función sera una constante de éstas.
       * Ver grafo de dependencias para determinar qué funciones de
       * vCPUVectorial se utilizan en concreto.
       */ 
      bool operator<=(const Z& der) const;

      /** Versión de precisión simple de "Mayor que"
       *
       * @par Complejidad:
       *      \f$O(1)\f$
       * 
       * @sa operator>(const Z&) const*/
      bool operator>(const SignedDigit der) const;  
      
     
      /** Versión de precisión simple de "Menor que"
       *
       * @par Complejidad:
       *      \f$O(1)\f$
       * 
       * @sa operator<(const Z&) const*/
     bool operator<(const SignedDigit der) const;

     
     /** Versión de precisión simple de "Igual"
       *
       * @par Complejidad:
       *      \f$O(1)\f$
       * 
       * @sa operator==(const Z&) const*/
     bool operator==(const SignedDigit der) const;
      
     
     /** Versión de precisión simple de "Distinto"
       *
       * @par Complejidad:
       *      \f$O(1)\f$
       * 
       * @sa operator!=(const Z&) const*/
     bool operator!=(const SignedDigit der) const;
     
     
     /** Versión de precisión simple de "Mayor o igual que"
       *
       * @par Complejidad:
       *      \f$O(1)\f$
       * 
       * @sa operator>=(const Z&) const*/
     bool operator>=(const SignedDigit der) const;
     
     
     /** Versión de precisión simple de "Menor o igual que"
       *
       * @par Complejidad:
       *      \f$O(1)\f$
       * 
       * @sa operator<=(const Z&) const*/
     bool operator<=(const SignedDigit der) const;

     
     /** Versión de precisión simple de "Mayor que"
       *
       * @par Complejidad:
       *      \f$O(1)\f$
       * 
       * @sa operator>(const Z&) const*/
     bool operator>(const Digit der) const;
     
     
     /** Versión de precisión simple de "Menor que"
       *
       * @par Complejidad:
       *      \f$O(1)\f$
       * 
       * @sa operator<(const Z&) const*/
     bool operator<(const Digit der) const;
     
     
     /** Versión de precisión simple de "Igual"
       *
       * @par Complejidad:
       *      \f$O(1)\f$
       * 
       * @sa operator==(const Z&) const*/
     bool operator==(const Digit der) const;
     
     
     /** Versión de precisión simple de "Distinto"
       *
       * @par Complejidad:
       *      \f$O(1)\f$
       * 
       * @sa operator!=(const Z&) const*/
     bool operator!=(const Digit der) const;
     
     
     /** Versión de precisión simple de "Mayor o igual que"
       *
       * @par Complejidad:
       *      \f$O(1)\f$
       * 
       * @sa operator>=(const Z&) const*/
     bool operator>=(const Digit der) const;
     
     
     /** Versión de precisión simple de "Menor o igual que"
       *
       * @par Complejidad:
       *      \f$O(1)\f$
       * 
       * @sa operator<=(const Z&) const*/
     bool operator<=(const Digit der) const;


     
      ////////////////////////////////////
      //   OPERADORES DE DESPLAZAMIENTO //
      ////////////////////////////////////
      /** Operador de desplazamiento a la derecha acumulado.
      *
      * @param n Número de bits a desplazar hacia la derecha.
      * @return *this, instancia de la clase actual tras el
      * desplazamiento
      *
      * Se desplaza (*this) un numero n de bits hacia la derecha.
      * Esto es equivalente a \f$(*this) = \lfloor(*this) / 2^{n}\rfloor\f$
      * 
      * \note
      * Esta función delega el desplazamiento en la familia de rutinas
      * de desplazamiento de la clase vCPUVectorial. Por tanto, la cota
      * de complejidad de esta función sera una constante de éstas.
      * Ver grafo de dependencias para determinar qué funciones de
      * vCPUVectorial se utilizan en concreto.
      */
      Z& operator>>=(const size_t n);
      
      /** Operador de desplazamiento a la izquierda acumulado.
      *
      * @param n Número de bits a desplazar hacia la izquierda.
      * @return *this, instancia de la clase actual tras el
      * desplazamiento
      *
      * Se desplaza (*this) un numero n de bits hacia la izquieda.
      * Esto es equivalente a \f$(*this) = (*this) \cdot 2^{n}\f$
      * 
      * \note
      * Esta función delega el desplazamiento en la familia de rutinas
      * de desplazamiento de la clase vCPUVectorial. Por tanto, la cota
      * de complejidad de esta función sera una constante de éstas.
      * Ver grafo de dependencias para determinar qué funciones de
      * vCPUVectorial se utilizan en concreto.
      */
      Z& operator<<=(const size_t n);

      
      //////////////////////////////
      //   OPERADORES "REDUCIDOS" //
      //////////////////////////////
      Z& operator++(void); /**< Operador de preincremento. @par Complejidad \f$O(1)\f$ */
      Z& operator++(int); /**< Operador de postincremento. @par Complejidad \f$O(1)\f$ */
      Z& operator--(void); /**< Operador de predecremento. @par Complejidad \f$O(1)\f$ */
      Z& operator--(int); /**< Operador de postdecremento. @par Complejidad \f$O(1)\f$ */

 
      /////////////////////////////
      //   FUNCIONES MISCELANEA  //
      /////////////////////////////
      /** Número de bits.
       *
       * @par Complejidad:
       *      \f$O(1)\f$
       * 
       * @return El número de bits de (*this).
       *
       * Se devuelve un dato de tipo size_t con valor el número de
       * bits que ocupa la instancia del entero sobre la que se aplica 
       * el método.
       * Por definición el número de bits de un entero N será
       * \f$\lceil \log_{2} N \rceil \f$
       * 
       */ 
      size_t numBits(void) const;
 
      //redondeo
      SignedDigit redondear(size_t exceso) ;

      /** Hacer cero.
       * 
       * \par Complejidad:
       *      \f$ O(1) \f$
       *
       * @return Referencia a *this.
       *  
       * Hace que el entero sobre el que se invoca el método pase a ser
       * igual a 0.\n
       *  El objetivo de este método es ser un atajo para la frecuente 
       *  operacion \f$ x = 0 \f$ para el entero \f$x\f$
       *
       * \note Se fuerza asimismo el signo positivo, aunque pueda carecer de 
       * sentido el poner un signo al cero.
       */
      Z& hacerCero(void);
 
      /** Hacer uno.
       * 
       * \par Complejidad:
       *      \f$ O(1) \f$
       *
       * @return Referencia a *this.
       *  
       * Hace que el entero sobre el que se invoca el método pase a ser
       * igual a 1.
       *  El objetivo de este método es ser un atajo para la frecuente 
       *  operacion \f$ x = 1 \f$ para el entero \f$x\f$
       *
       */
      Z& hacerUno(void);
  
      /** Hacer el número positivo.
       * 
       * \par Complejidad:
       *      \f$ O(1) \f$
       *
       * @return Referencia a *this.
       *  
       * Hace que el entero sobre el que se invoca el método pase a ser
       * positivo.
       */
      inline Z& hacerPositivo(void) { signo_ = 1; return *this; } 
      
      /** Hacer el número negativo.
       * 
       * \par Complejidad:
       *      \f$ O(1) \f$
       *
       * @return Referencia a *this.
       *  
       * Hace que el entero sobre el que se invoca el método pase a ser
       * negativo.
       */
      inline Z& hacerNegativo(void) { signo_ = -1; return *this; }

       /** Cambiar el signo.
       * 
       * \par Complejidad:
       *      \f$ O(1) \f$
       *
       * @return Referencia a *this.
       *  
       * Hace que el entero sobre el que se invoca el método cambie de signo.
       *  El objetivo de este método es ser un atajo para la frecuente 
       *  operacion \f$ x = -x \f$ para el entero \f$x\f$
       *
       */
      inline Z& cambiarSigno(void) { signo_ *= -1; return *this; }

      
      /** Comprobar igualdad a cero.
       * 
       * \par Complejidad:
       *      \f$ O(1) \f$
       *
       * @return true si *this es un entero igual a 0\n 
       *         false si no.
       *  
       *  El objetivo de este método es ser un atajo para la frecuente 
       *  operacion de comprobar si un número es cero.
       */
      bool esCero(void) const;  
 
      /** Comprobar igualdad a uno.
       * 
       * \par Complejidad:
       *      \f$ O(1) \f$
       *
       * @return true si *this es un entero igual a 1\n 
       *         false si no.
       *  
       *  El objetivo de este método es ser un atajo para la frecuente 
       *  operacion de comprobar si un número es uno.
       */
      bool esUno(void) const;  
      
      /** Comprobar signo positivo.
       * 
       * \par Complejidad:
       *      \f$ O(1) \f$
       *
       * @return true si *this es un entero positivo o cero\n 
       *         false si no.
       *  
       *  El objetivo de este método es ser un atajo para la frecuente 
       *  operacion de comprobar si un número es positivo.
       */
      inline bool esPositivo(void) const { return signo_ > 0; }

      /** Comprobar signo negativo.
       * 
       * \par Complejidad:
       *      \f$ O(1) \f$
       *
       * @return true si *this es un entero negativo\n 
       *         false si no.
       *  
       *  El objetivo de este método es ser un atajo para la frecuente 
       *  operacion de comprobar si un número es negativo.
       */
     inline bool esNegativo(void) const { return signo_ < 0; }
 
      /** Eliminar ceros no significativos.
       * 
       * \par Complejidad:
       *      \f$ O(n) \f$
       *
       *  Este método elimina los ceros a la izquierda (no
       *  significativos) del entero sobre el que es invocado.
       *  Pese a que no hacerlo teoricamente no plantea problemas, en
       *  la práctica es mejor, desde el punto de vista del rendimiento y 
       *  gestión de la memoria, hacerlo.
       *
       *  @note El usuario no debería tener la necesidad de utilizar
       *  este método, ya que es utilizado internamente por la
       *  librería de forma automática. Se proporciona para
       *  posibilitar al usuario el reimplementar sus propios
       *  algoritmos utilizando el mecanismo de funciones enchufables.
       */
      void limpiarCeros(void);

      /** Comprobar paridar par.
       * 
       * \par Complejidad:
       *      \f$ O(1) \f$
       *
       * @return true si *this es un entero par\n 
       *         false si no.
       *  
       *  El objetivo de este método es ser un atajo para la frecuente 
       *  operacion de comprobar si un número es par.
       */
      inline bool esPar(void) const { return (!(coefPoliB_[0] & 0x1)); }
      
      /** Comprobar paridad impar.
       * 
       * \par Complejidad:
       *      \f$ O(1) \f$
       *
       * @return true si *this es un entero impar\n 
       *         false si no.
       *  
       *  El objetivo de este método es ser un atajo para la frecuente 
       *  operacion de comprobar si un número es impar.
       */
     inline bool esImpar(void) const { return ((coefPoliB_[0] & 0x1)); }
  
     /** Mayor potencia de 2.
       *
       * Este método devuelve el exponente de la mayor potencia de 2
       * contenida en el entero sobre el que se aplica. Esto es,
       * devuelve \f$r\f$ para \f$ n = 2^{r} \times d \quad / \quad \textrm{d impar}\f$.
       * 
       * \par Complejidad:
       *      \f$ O(n) \f$
       *
       * @return Exponente de la mayor potencia de 2 contenida en el
       * número.
       */
     size_t numDoses(void) const;
      /** Valor absoluto.
       *
       * Este método devuelve el valor absoluto del entero sobre el
       * que se aplica.
       * 
       * \par Complejidad:
       *      \f$ O(1) \f$
       *
       * @return Referencia al entero valor absoluto de *this.
       */
     Z& abs(void);

     /** Valor absoluto.
       *
       * Determina si el entero sobre el que se aplica el método es
       * una potencia de primo, y de serlo, da el primo base de dicha
       * potencia.  
       *
       *
       * 
       * \par Complejidad:
       *      \f$ O(1) \f$
       *
       * @param primo Puntero a entero en el que se almacena la base
       * de la potencia de primo de serlo o 0 en otro caso. Si su
       * valor es NULL, no se utiliza.
       * 
       * @return true si *this es una potencia de primo. \n
       *         false si no.
       */
      bool esPotenciaPrima(Z* primo = NULL);
        
      /** Leer un entero de una ristra de bytes.
       *
       * Este método define el entero sobre el que se aplica como
       * concatenación de 
       * la ristra de bytes definida por los dos iteradores @a ini y
       * @a fin, que se suponen iteran sobre un tipo de dato de
       * longitud 1 byte (8 bits). De no ser así, en tan sólo se
       * considerarían los 8 bits de menos peso de cada elemento.
       *
       * \note De apuntar @a ini a una posición posterior a @a fin, no
       * se realizará ninguna acción.
       *
       * @param ini Iterador apuntando al comienzo de la ristra a
       * considerar.
       * @param fin Iterador apuntando al final de la ristra a
       * considerar.
       */
      template< class iterator >
        void leerBytes(iterator ini, iterator fin);
 
      /** Escribir desde un entero a ristra de bytes.
       *
       * Este método vuelca la representación del entero sobre el que
       * se aplica en la ristra de bytes definida por 
       * los dos iteradores @a ini y
       * @a fin, que se suponen iteran sobre un tipo de dato de
       * longitud 1 byte (8 bits). De no ser así, en tan sólo serán 
       * escritos los 8 bits de menos peso de cada elemento.
       *
       * \note De apuntar @a ini a una posición posterior a @a fin, no
       * se realizará ninguna acción. Asimismo, si 
       * la distancia entre iteradores es menor que el número de bytes
       * que pudiera contener el entero, se devolveran sólo los \f$|ini - fin|\f$
       * bytes menores del entero.

       *
       * @param ini Iterador apuntando al comienzo de la ristra a
       * considerar.
       * @param fin Iterador apuntando al final de la ristra a
       * considerar.
       */
      template< class iterator >
        void escribirBytes(iterator ini, iterator fin) const;

      /** Dividir entre \f$BASE^{n}\f$ 
       *
       * @param n La potencia de la base entre la que se divide el
       * entero sobre el que se invoca el método.
       *
       * @return Una referencia a *this.
       * 
       * Se divide el entero actual (*this) entre la potencia n-esima
       * de la base; \f$(*this) = (*this) / BITS\_EN\_CIFRA^{n}\f$.\n
       * Es decir, se dejan los dígitos siguientes al n-esimo en base BITS_EN_CIFRA.
       *
       * */
      Z& divisionBase(const size_t n);

      /** Modulo entre \f$BASE^{n}\f$ 
       *
       * @param n La potencia de la base entre la que se realiza la
       * reduccion del entero sobre el que se invoca el método.
       * 
       * @return Una referencia a *this.
       *
       * Se reduce el entero actual (*this) por la potencia n-esima
       * de la base; \f$(*this) = (*this) \bmod (BITS\_EN\_CIFRA^{n})\f$.\n
       * 
       * Es decir, se dejan los n dígitos de menor peso en base
       * BITS_EN_CIFRA.
       * */
      Z& moduloBase(const size_t n);
      
      /** Iguala a \f$BASE^{n}\f$.
       * 
       * @param n La potencia de la base a la que se
       * iguala el entero sobre el que se invoca el método.
       * 
       * @return Una referencia a *this.
       *
       * El entero actual (*this) toma el valor \f$2^{BITS_EN_BASE \cdot n}\f$.
       */
      Z& potenciaBase(const size_t n);


      /////////////////////////////////
      //      CONVERSION METHODS     //
      /////////////////////////////////

      /** Get a text representation of the integer.
       *
       * @return A constant char[] representing the base-10 conversion of *this
       */
      std::string toString(void) const;


      /** Get the Z as a single precision signed type.
       *
       * If the conversion cannot be performed (the actual Z being
       * larger than mpplas::Constants::CIFRASIGNO_MAX), only the first
       * mpplas::Constructor::BITS_EN_CIFRASIGNO are considered.
       *
       * @return A SignedDigit representing (a possibly truncated) *this.
       */
      inline SignedDigit toSignedDigit(void) throw(){
        Digit c = coefPoliB_[0] & (Constants::CIFRASIGNO_MAX-1);
        SignedDigit ret = (SignedDigit)c;
        if(signo_ < 0 ){
          return -ret;
        }
        else{
          return ret;
        }
      }; 

      /** Get the Z as a single precision unsigned type.
       *
       * If the conversion cannot be performed (the actual Z being
       * larger than mpplas::Constants::CIFRA_MAX), only the first
       * mpplas::Constructor::BITS_EN_CIFRA are considered.
       *
       * @return A Digit representing (a possibly truncated) *this.
       */
      inline Digit toDigit(void) throw(){
        return coefPoliB_[0];
      };

      
      //destructor
      ~Z();

      /////////////////////////////////
      //   FUNCIONES DE INFORMACIÓN  //
      /////////////////////////////////
      /** Digits en base BITS_EN_CIFRA 
       *
       * @par Complejidad:
       *      \f$O(1)\f$
       *
       * @return El número de cifras del entero sobre el que se invoca
       *         el método en base BITS_EN_CIFRA.
       *
       */
      inline
        size_t longitud(void) const  {   return coefPoliB_.size();  }

      /** Acceso a cifra.
       *  
       *  Acceso con posibilidad de @e modificacion a una cifra del
       *  entero (recordando que el entero se representa en base
       *  \f$2^{BITS\_EN\_CIFRA}\f$
       * 
       * @par Complejidad:
       *      \f$O(1)\f$
       *
       * @param i Digit a considerar (desde 0 hasta
       * \f$longitud()-1\f$).
       *
       * @return Referencia a la i-ésima cifra del entero en base 
       * \f$2^{BITS\_EN\_CIFRA}\f$.
       *
       */
      inline
        Digit& operator[](size_t i) { return coefPoliB_[i]; }
 
      /** Acceso constante a cifra.
       *  
       *  Acceso a una cifra del  entero 
       *  (recordando que el entero se representa en base
       *  \f$2^{BITS\_EN\_CIFRA}\f$
       * 
       * @par Complejidad:
       *      \f$O(1)\f$
       *
       * @param i Digit a considerar (desde 0 hasta
       * \f$longitud()-1\f$).
       * 
       * @return Copia de la i-ésima cifra del entero en base 
       * \f$2^{BITS\_EN\_CIFRA}\f$.
       *
       */
      inline
        Digit operator[](size_t i) const { return coefPoliB_[i]; }

      /** Signo del entero. 
       * 
       * @par Complejidad:
       *      \f$O(1)\f$
       *
       *  @return Un valor mayor que 0 (típicamente "1")
       *          si el entero es mayor o igual que 0.\n
       *          Un valor menor que 0 (típicamente "-1") si no.
       */
      inline 
        long signo(void) const { return signo_; }


      //relativas a precision de salida
      /** Ver precisión actual de salida.
       *
       *  Este método estático muestra el valor actual de la precisión de
       *  salida para enteros.
       *
       * \note Un valor de \f$0\f$ representa precisión ilimitada.
       *
       * @par Complejidad:
       *      \f$O(1)\f$
       *  
       * @return El valor actual de la precisión de salida para
       * enteros.
       *
       */
      inline 
        static size_t precisionSalida(void) { return precisionSalida_; }

      /** Establecer precisión de salida.
       *
       *  Este método estático establece el valor actual de la precisión de
       *  salida para enteros.
       *
       * \note Un valor de \f$0\f$ representa precisión ilimitada.
       * 
       * @par Complejidad:
       *      \f$O(1)\f$
       *  
       *  @param nueva La nueva precisión a utilizar.
       *
       */
      inline 
        static void precisionSalida(size_t nueva) 
        { precisionSalida_ = nueva; return;}


      /** TODO */
      static Z Zero;

    protected:

      /** Vector de coeficientes del polinomio que representa el número en base B */
      mpplas::MiVec<Digit> coefPoliB_; 
      int8_t signo_; /**< Indica el signo del numero largo representado. \n
                     Valor positivo \f$\Rightarrow\f$ entero positivo. \n
                     valor negativo \f$\Rightarrow\f$ entero negativo.
                     */
      static size_t precisionSalida_; /**< Indica la precisión de salida a utilizar. 

      Esto es, no se presentarán mas que \f$precisionSalida\_\f$ digitos decimales, 
      representandose en resto del número con notación "eN" siendo "N" el exponente
      de la potencia de 10 adecuada.
      
      \note Un valor de \f$0\f$ representa precisión ilimitada.

      */

      /** Operador de salida del número */
      friend std::ostream& operator<<(std::ostream&, Z);
      /** Operador obtencion del número */
      friend std::istream& operator>>(std::istream&, Z&); 

      /** Funciones (procedimientos) para el calculo simultaneao de cociente y módulo.
       *
       *  @par Complejidad:
       *       \f$O(n \cdot m) \quad / \quad n=tam(dividendo) y m=tam(divisor)\f$
       * 
       * @param dividendo Entero a dividir.
       * @param divisor Entero que divide.
       * @param cociente Dirección del Entero para el cociente.
       * @param resto Direccion del Entero para el resto.
       *
       * @return Los valores devueltos son los parametris "cociente" y
       * "resto".
       */
      friend void divMod(const Z& dividendo, const Z& divisor, Z* cociente, Z* resto) 
        throw (Errors::DivisionPorCero);
      friend void divMod(const Z& dividendo, const SignedDigit divisor, Z* cociente, Z* resto) 
        throw (Errors::DivisionPorCero);
      friend void divMod(const Z& dividendo, const Digit divisor, Z* cociente, Z* resto) 
        throw (Errors::DivisionPorCero);


  };

  /** Versión de precisión simple con signo del operador "<" */
  bool operator<(const SignedDigit, const Z&);
  /** Versión de precisión simple con signo del operador ">" */
  bool operator>(const SignedDigit, const Z&);
  /** Versión de precisión simple con signo del operador "<=" */
  bool operator<=(const SignedDigit, const Z&);
  /** Versión de precisión simple con signo del operador ">=" */
  bool operator>=(const SignedDigit, const Z&);
  /** Versión de precisión simple con signo del operador "==" */
  bool operator==(const SignedDigit, const Z&);
  /** Versión de precisión simple con signo del operador "!=" */
  bool operator!=(const SignedDigit, const Z&);


  /** Versión de precisión simple sin signo del operador "<" */
  bool operator<(const Digit, const Z&);
  /** Versión de precisión simple sin signo del operador ">" */
  bool operator>(const Digit, const Z&);
  /** Versión de precisión simple sin signo del operador "<=" */
  bool operator<=(const Digit, const Z&);
  /** Versión de precisión simple sin signo del operador ">=" */
  bool operator>=(const Digit, const Z&);
  /** Versión de precisión simple sin signo del operador "==" */
  bool operator==(const Digit, const Z&);
  /** Versión de precisión simple sin signo del operador "!=" */
  bool operator!=(const Digit, const Z&);

  //se devuelve un objeto (y no una referencia) debido a lo
  //expuesto en stroustrup pág. 297 ultimo parrafo.
  //
  //Estas funciones no son amigas de class Z por lo expuesto
  //en stroustrup 11.3.1 (pag 282)
  //
  //Asimismo, su parametro de la izq. es pasa por valor ya que de
  //todas formas habriamos de copiarlo dentro del cuerpo (haciendo por
  //tanto trabajo doble de no haberlo pasado por valor)

  /** Suma no acumulativa de enteros.
   *
   * @param a Sumando izquierdo.
   * @param b Sumando derecho.
   * 
   * @return El entero suma de los argumentos. 
   */
  Z operator+(Z a, const Z& b);
  /** Resta no acumulativa de enteros.
   *
   * @param a Minuendo.
   * @param b Sustraendo.
   * 
   * @return El entero resta de los argumentos. 
   */
  Z operator-(Z a, const Z& b);
  /** Producto no acumulativa de enteros.
   *
   * @param a Factor izquierdo.
   * @param b Factor derecho.
   * 
   * @return El entero producto de los argumentos. 
   */
  Z operator*(Z a, const Z& b);
  /** División no acumulativa de enteros.
   *
   * @param a Dividendo.
   * @param b Divisor.
   * 
   * @return El entero cociente \f$\lfloor(a/b)\rfloor\f$. 
   */
  Z operator/(Z a, const Z& b);
  /** Resto no acumulativo de la división entera.
   *
   * @param a Dividendo.
   * @param b Divisor.
   * 
   * @return El entero resto de la división \f$\lfloor(a/b)\rfloor\f$. 
   */
  Z operator%(Z a, const Z& b);
  /** Operación AND a nivel de bits no acumulativa.
   *
   * @param a Operando izquierdo.
   * @param b Operando derecho.
   * 
   * @return El entero resultado de la operación AND a nivel de bits
   * de @a a y @a b. 
   */
  Z operator&(Z a, const Z& b);
  /** Operación OR a nivel de bits no acumulativa.
   *
   * @param a Operando izquierdo.
   * @param b Operando derecho.
   * 
   * @return El entero resultado de la operación OR a nivel de bits
   * de @a a y @a b. 
   */
  Z operator|(Z a, const Z& b);

  /** Operación XOR a nivel de bits no acumulativa.
   *
   * @param a Operando izquierdo.
   * @param b Operando derecho.
   * 
   * @return El entero resultado de la operación XOR a nivel de bits
   * de @a a y @a b. 
   */
  Z XOR(Z a, const Z &b);

  /** Versión de precisión simple de operator+(Z, const Z&)*/
  Z operator+(const SignedDigit, Z); 
  /** Versión de precisión simple de operator-(Z, const Z&)*/
  Z operator-(const SignedDigit, Z);
  /** Versión de precisión simple de operator*(Z, const Z&)*/
  Z operator*(const SignedDigit, Z);
  /** Versión de precisión simple de operator/(Z, const Z&)*/
  Z operator/(const SignedDigit, const Z&);
  /** Versión de precisión simple de operator%(Z, const Z&)*/
  Z operator%(const SignedDigit, const Z&);
  /** Versión de precisión simple de operator&(Z, const Z&)*/
  Z operator&(const SignedDigit, Z);
  /** Versión de precisión simple de operator|(Z, const Z&)*/
  Z operator|(const SignedDigit, Z);
  /** Versión de precisión simple de XOR(Z, const Z&)*/
  Z XOR(const SignedDigit, Z);


  /** Versión de precisión simple de operator+(Z, const Z&)*/
  Z operator+(Z, const SignedDigit);
  /** Versión de precisión simple de operator-(Z, const Z&)*/
  Z operator-(Z, const SignedDigit);
  /** Versión de precisión simple de operator*(Z, const Z&)*/
  Z operator*(Z, const SignedDigit);
  /** Versión de precisión simple de operator/(Z, const Z&)*/
  Z operator/(Z, const SignedDigit);
  /** Versión de precisión simple de operator%(Z, const Z&)*/
  Z operator%(Z, const SignedDigit);
  /** Versión de precisión simple de operator&(Z, const Z&)*/
  Z operator&(Z, const SignedDigit);
  /** Versión de precisión simple de operator|(Z, const Z&)*/
  Z operator|(Z, const SignedDigit);
  /** Versión de precisión simple de XOR(Z, const Z&)*/
  Z XOR(Z, const SignedDigit);

  /** Versión de precisión simple de operator+(Z, const Z&)*/
  Z operator+(const Digit, Z);
  /** Versión de precisión simple de operator-(Z, const Z&)*/
  Z operator-(const Digit, Z);
  /** Versión de precisión simple de operator*(Z, const Z&)*/
  Z operator*(const Digit, Z);
  /** Versión de precisión simple de operator/(Z, const Z&)*/
  Z operator/(const Digit, const Z&);
  /** Versión de precisión simple de operator%(Z, const Z&)*/
  Z operator%(const Digit, const Z&);
  /** Versión de precisión simple de operator&(Z, const Z&)*/
  Z operator&(const Digit, Z);
  /** Versión de precisión simple de operator|(Z, const Z&)*/
  Z operator|(const Digit, Z);
  /** Versión de precisión simple de XOR(Z, const Z&)*/
  Z XOR(const Digit, Z);

 
  /** Versión de precisión simple de operator+(Z, const Z&)*/
  Z operator+(Z, const Digit);
  /** Versión de precisión simple de operator-(Z, const Z&)*/
  Z operator-(Z, const Digit);
  /** Versión de precisión simple de operator*(Z, const Z&)*/
  Z operator*(Z, const Digit);
  /** Versión de precisión simple de operator/(Z, const Z&)*/
  Z operator/(Z, const Digit);
  /** Versión de precisión simple de operator%(Z, const Z&)*/
  Z operator%(Z, const Digit);
  /** Versión de precisión simple de operator&(Z, const Z&)*/
  Z operator&(Z, const Digit);
  /** Versión de precisión simple de operator|(Z, const Z&)*/
  Z operator|(Z, const Digit);
  /** Versión de precisión simple de XOR(Z, const Z&)*/
  Z XOR(Z, const Digit);

  Z operator-(Z); /**< Operator - unario: cambio de signo */

  /** Operador de potenciación.
   *
   * @param base Entero base de la potenciación.
   * @param exp Entero exponente.
   *
   * @return Entero igual a \f$base^{exp}\f$
   * @sa class Potencia.
   *
   * @note El exponente ha de ser \f$\leq 2^{BASE}\f$ o se lanzará un
   * error de tipo Errors::TooBig
   *
   */
  Z operator^(Z base, const Z& exp); 
   /** Operador de potenciación.
   *
   * @param base Entero base de la potenciación.
   * @param exp Digit exponente.
   *
   * @return Entero igual a \f$base^{exp}\f$
   * @sa class Potencia.
   *
   */
 Z operator^(Z base, const Digit exp); 
   /** Operador de potenciación.
   *
   * @param base Entero base de la potenciación.
   * @param exp SignedDigit exponente.
   *
   * @return Entero igual a \f$base^{exp}\f$
   * 
   * @sa class Potencia.
   *
   * @note El exponente ha de ser positivo o se lanzará un
   * error de tipo Errors::ExponenteNegativo
   *
   */
 Z operator^(Z base, const SignedDigit exp); 

 /** Cuadrado (versión "función").
  *
  * @param x Entero del que hacer el cuadrado.
  *
  * @return Entero igual a \f$ x^2 \f$.
  *
  * @sa Z::cuadrado()
  */
  Z cuadrado(Z x);
 
 /** Cuadrado modular (versión "función").
  *
  * @param x Entero del que hacer el cuadrado modular.
  * @param mod Módulo reductor.
  *
  * @return Entero igual a \f$ x^2 \bmod mod\f$.
  *
  * @sa Z::cuadrado()
  */
  Z cuadradoModular(Z x, const Z& mod);
  
  /** Factorial (versión "función").
   *
   * @sa Z::factorial()
   * 
   */
  Z factorial(Z x);
   /** Raíz cuadrada entera (versión "función").
   *
   * @sa Z::raizCuadrada()
   * 
   */
  Z raizCuadrada(Z x);
  /** Raíz cuadrada entera precisión simple (versión "función").
   *
   * @sa Z::raizCuadrada()
   * 
   */
  Digit raizCuadrada(Digit x);
  
  
  /** Determinar si es cuadrado perfecto (versión "función")
   *
   * @sa Z::esCuadrado()
   */
  bool esCuadrado(Z x);

  /** Valor absoluto (versión "función")
   * @sa Z::abs()
   */
  Z abs(Z x);


  /** Número de bits (versión "función").
   *
   * @sa Z::numBits() 
   */
  size_t numBits(const Z& x);
  /** Número de bits precisión simple sin signo (versión "función").
   *
   * @sa Z::numBits() 
   */
  size_t numBits(const Digit x);
  /** Número de bits precisión simple con signo(versión "función").
   *
   * @sa Z::numBits() 
   */
  size_t numBits(const SignedDigit x);


  //OPERADORES DE DESPLAZAMIENTO 
  
  /** Operador de desplazamiento a la derecha no acumulativo.
   *
   * @param entero El entero a desplazar.
   * @param n El número de posiciones a desplazar
   *
   * @return El entero desplazado @a n posiciones de bits a la
   * derecha.
   *
   * @sa Z::operator>>=(const size_t n) */
  Z operator>>(Z entero, const size_t n);
  /** Operador de desplazamiento a la izquierda no acumulativo.
   *
   * @param entero El entero a desplazar.
   * @param n El número de posiciones a desplazar
   *
   * @return El entero desplazado @a n posiciones de bits a la
   * izquierda.
   *
   * @sa Z::operator<<=(const size_t n) */
  Z operator<<(Z entero, const size_t n);



  template< class iterator >
  void Z::leerBytes(iterator inicio, iterator fin )
  {
    // se supone que los iteradores son sobre un tipo de 8 bits.
    
    this->hacerCero();
    
    if( (inicio >= fin) )
      return;

      for( ; inicio != fin; inicio++){
        this->operator<<=(8);
        coefPoliB_[0] |= ((*inicio) & 0xff);
      }
        
    return;
  }
  
  
  template< class iterator >
  void Z::escribirBytes(iterator inicio, iterator fin ) const
  {
    // se supone que los iteradores son sobre un tipo de 8 bits.
    // el usuario es responsable de pasar una distancia entre
    // iteradores adecuada. 
    // Si la distancia entre iteradores es menor que el nº de bytes
    // que pudiera contener el Z, se devolveran sólo los |inicio-fin|
    // bytes menores de Z

    if( (inicio >= fin) )
      return;

    Z temp(*this);
    fin--;
    while( (!(this->esCero())) && (inicio != (fin+1)) ){
      (*fin) = temp.coefPoliB_[0] & 0xff;
      temp.operator>>=(8);
      fin--;
    }
    return;

  }

  
}
#endif
