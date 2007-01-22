/* 
 * $Id$
 */

/************************ Z.h ***************************************
 * Cabecera que define el tipo de dato para un n�mero entero.       *
 * El 'token' b�sico ser� el tipo 'Cifra' definido en el n�cleo.    *
 * *****************************************************************/

#ifndef __Z_H
#define __Z_H


#include <string>
#include "MiVec.h"
#include "err.h"
#include "constantes.h"

namespace numth
{
  /** Clase para la representaci�n de enteros. */
  class Z 
  {

    public:
      /////////////////////
      //   CONSTRUCTORES //
      /////////////////////
      Z() /**< constructor por defecto */;
      Z( const Z& otro); /**< Constructor de copia.
                           @param otro Entero a copiar. */

      ////////////////////////////////
      //   OPERADORES DE CONVERSION //
      ////////////////////////////////
      //se devuelve un objeto (y no una referencia) debido a lo
      //expuesto en stroustrup p�g. 297 ultimo parrafo.
      //
      //Estas funciones no son amigas de class Z por lo expuesto
      //en stroustrup 11.3.1 (pag 282)

      /** Funci�n de conversi�n de tipo Cifra a Z (entero).
       *
       *  @par Complejidad:
       *       \f$O(1)\f$
       * 
       *  @param numSimple N�mero de precisi�n simple a convertir a entero.
       *
       *  @return El entero correspondiente a la conversi�n.
       */
      static Z convertir(const Cifra numSimple);


      /** Funci�n de conversi�n de tipo long a Z (entero).
       *
       *  @par Complejidad:
       *       \f$O(1)\f$
       * 
       *  @param numSimple N�mero de precisi�n simple a convertir a entero.
       *
       *  @return El entero correspondiente a la conversi�n.
       */
      static Z convertir(const CifraSigno numSimple);


      /** Funci�n de conversi�n de tipo cadena de caracteres a Z (entero).
       * 
       *  @par Complejidad:
       *       \f$O(n)\f$
       * 
       *  @param cadena Vector de caracteres que representa el n�mero a
       *  convertir a entero.
       *
       *  @exception numth::Errores::Sintactico Error sint�ctico en la
       *  cadena.
       *
       *  @return El entero correspondiente a la conversi�n.
       */
      static Z convertir(const char* cadena) throw(Errores::Sintactico);


      /** Funci�n de conversi�n de tipo double a Z (entero).
       *
       *  @note La conversi�n trunca el n�mero double.
       *  @par Complejidad:
       *       \f$O(1)\f$
       * 
       *  @param numFlotante N�mero de precisi�n simple a convertir a entero.
       *
       *  @return El entero correspondiente a la conversi�n.
       */
      static Z convertir(const double numFlotante);

      /** Funci�n de conversi�n de tipo MiVec<Cifra> a Z (entero).
       *
       *  @par Complejidad:
       *       \f$O(1)\f$
       * 
       *  @param vec Vector de Cifra 's representando un entero
       *  positivo en base sizeof(Cifra)*8 
       *
       *  @return El entero correspondiente a la conversi�n.
       */
      static Z convertir(const MiVec<Cifra>& vec);


      /** Operador de asignaci�n desde Z.
       *
       *  @par Complejidad:
       *       \f$O(n)\f$
       * 
       * @param origen Entero a asignar a la instancia invocadora. 
       *
       * @return Referencia a *this 
       */
      Z& operator=(const Z& origen);


      /** Operador de asignaci�n desde Cifra.
       *
       *  @par Complejidad:
       *       \f$O(1)\f$
       * 
       * @param origenSimple N�mero simple a asignar a la instancia invocadora. 
       *
       * @return Referencia a *this 
       */
      Z& operator=(const Cifra origenSimple);

      
      //////////////////////////////
      //   OPERADORES ARITMETICOS //
      //////////////////////////////
      /** Operador de suma acumulada.
       *
       * @pre *this y sumandoDerecha Enteros v�lidos.
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
       * @pre *this y sustraendo Enteros v�lidos.
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
       * @pre *this y factorDer Enteros v�lidos.
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
       * @pre *this y divisor Enteros v�lidos.
       * @post *this cociente de la divisi�n de si mismo por el valor del Entero divisor.
       * 
       *  @par Complejidad:
       *       \f$O(n \cdot m)\f$
       *       con \f$n\f$ y \f$m\f$ tama�os de dividendo y divisor.
       *
       * @param divisor Entero a actuar de divisor de *this. 
       *
       * @return Referencia a *this.
       */
      Z& operator/=(const Z& divisor);
 
      /** Operador de resto acumulado.
       *
       * @pre *this y divisor Enteros v�lidos.
       * @post *this resto de la divisi�n de si mismo por el valor del Entero divisor.
       * 
       *  @par Complejidad:
       *       \f$O(n \cdot m)\f$
       *       con \f$n\f$ y \f$m\f$ tama�os de dividendo y divisor.
       *       
       * @param divisor Entero a actuar de divisor de *this. 
       *
       * @return Referencia a *this.
       */
      Z& operator%=(const Z& divisor);


      /** Operador de AND l�gico a nivel de bits acumulado.
       *
       * @par Complejidad:
       *      \f$O(n)\f$
       *      con \f$n\f$ las cifras en base BASE.
       *
       *  Realiza una operacion AND l�gica a nivel de bits entre el
       *  entero sobre el que se invoca el m�todo y el par�metro dado.
       * 
       *  @param der Operando de la derecha en la operaci�n AND.
       *
       *  @return Referencia a *this.
       */
      Z& operator&=(const Z& der);
  
      /** Operador de OR l�gico a nivel de bits acumulado.
       *
       * @par Complejidad:
       *      \f$O(n)\f$
       *      con \f$n\f$ las cifras en base BASE.
       *
       *  Realiza una operacion OR l�gica a nivel de bits entre el
       *  entero sobre el que se invoca el m�todo y el par�metro dado.
       * 
       *  @param der Operando de la derecha en la operaci�n OR.
       *
       *  @return Referencia a *this.
       */
       Z& operator|=(const Z& der);

       /** Operaci�n de XOR l�gico a nivel de bits acumulado.
       *
       * @par Complejidad:
       *      \f$O(n)\f$
       *      con \f$n\f$ las cifras en base BASE.
       *
       *  Realiza una operacion XOR l�gica a nivel de bits entre el
       *  entero sobre el que se invoca el m�todo y el par�metro dado.
       * 
       *  @param der Operando de la derecha en la operaci�n XOR.
       *
       *  @return Referencia a *this.
       */
       Z& XOR(const Z& der);

      /** Hacer el cuadrado.
       *  
       *  Versi�n especializada de la multiplicaci�n con una mayor
       *  eficiencia en el calculo del cuadrado de un n�mero.
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
       *  Versi�n especializada de la multiplicaci�n y posterior
       *  reducci�n modular con una mayor eficiencia en el calculo 
       *  del cuadrado de un n�mero.
       *
       *  @post *this es el cuadrado de su valor original reducido
       *  m�dulo @e mod. \f$ x^{2} \bmod mod \f$
       *  
       *  @param x Entero a elevar al cuadrado.
       *  @param mod M�dulo reductor.
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
       *  C�lculo del factorial con algunas optimizaciones.
       *
       *  @return Referencia a *this.
       */
      Z& factorial(void);
      
      /** Raiz cuadrada.
       *
       *  @par Complejidad:
       *        \f$ O(\log^{2}{n}) \f$
       * 
       *  Hace la raiz cuadrada entera del n�mero entero sobre el que
       *  se aplique el m�todo. 
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
       * Se determina si el entero sobre el que se invoca el m�todo es
       * un cuadrado perfecto (esto es, si su ra�z cuadrada es un
       * entero)
       *
       * @param raiz Argumento opcional que se rellenar� con la raiz
       * cuadrada en caso de ser el entero sobre el que se invoca el
       * m�todo un cuadrado perfecto. \n
       * En caso de no serlo, tomar� el valor -1
       * 
       * @return @e true si es cuadrado perfecto.\n
       *         @e false si no es cuadrado perfecto.
       *
       * @note La ra�z devuelta ser� la positiva. De ah� que se
       * utilice a -1 como indicador de no existencia de raiz para el
       * parametro opcional @e ra�z
       */
      bool esCuadrado(Z* raiz = NULL);
      
      /** Versi�n de precisi�n simple de suma. @sa operator+=(const Z&)*/
      Z& operator+=(const CifraSigno); 
      /** Versi�n de precisi�n simple de resta. @sa operator-=(const Z&)*/
      Z& operator-=(const CifraSigno); 
      /** Versi�n de precisi�n simple de multiplicacion. @sa operator*=(const Z&)*/
      Z& operator*=(const CifraSigno); 
      /** Versi�n de precisi�n simple de divisi�n. @sa operator/=(const Z&)*/
      Z& operator/=(const CifraSigno); 
      /** Versi�n de precisi�n simple de resto. @sa operator%=(const Z&)*/
      Z& operator%=(const CifraSigno); 
      /** Versi�n de precisi�n simple de AND. @sa operator&=(const Z&)*/
      Z& operator&=(const CifraSigno);
      /** Versi�n de precisi�n simple de OR. @sa operator|=(const Z&)*/
      Z& operator|=(const CifraSigno);
      /** Versi�n de precisi�n simple de XOR. @sa XOR(const Z&)*/
      Z& XOR(const CifraSigno);
      
      
      /** Versi�n de precisi�n simple de suma. @sa operator+=(const Z&)*/
      Z& operator+=(const Cifra); 
      /** Versi�n de precisi�n simple de resta. @sa operator-=(const Z&)*/
      Z& operator-=(const Cifra); 
      /** Versi�n de precisi�n simple de multiplicacion. @sa operator*=(const Z&)*/
      Z& operator*=(const Cifra); 
      /** Versi�n de precisi�n simple de divisi�n. @sa operator/=(const Z&)*/
      Z& operator/=(const Cifra); 
      /** Versi�n de precisi�n simple de resto. @sa operator%=(const Z&)*/
      Z& operator%=(const Cifra); 
      /** Versi�n de precisi�n simple de AND. @sa operator&=(const Z&)*/
      Z& operator&=(const Cifra);
      /** Versi�n de precisi�n simple de OR. @sa operator|=(const Z&)*/
      Z& operator|=(const Cifra);
      /** Versi�n de precisi�n simple de XOR. @sa XOR(const Z&)*/
      Z& XOR(const Cifra);


      //////////////////////////////////
      //   OPERADORES DE POTENCIACION //
      //////////////////////////////////
      /** Operador de potenciaci�n acumulada.
       *
       * @param exp Entero reprensentado el exponente al que elevar.
       *
       * @return *this, instancia de la clase actual tras elevarla a
       * exp.
       * 
       * Se realiza la operaci�n \f$(*this) = (*this)^{exp}\f$
       *
       * \exception 
       * Errores::DemasiadoGrande Si el entero que
       * representa el exponente exp es demasiado grande ( mayor que
       * CIFRA_MAX )
       *
       * \note
       * Esta funci�n invoca a la versi�n con argumento Cifra. En
       * cualquier caso, depende de la implementaci�n particular de la
       * clase Potencia accesible mediante la clase Funciones.
       * 
       */
      Z& operator^=(const Z& exp); 
       /** Operador de potenciaci�n acumulada.
       *
       * @param exp Dato Cifra reprensentado el exponente al que elevar.
       *
       * @return *this, instancia de la clase actual tras elevarla a
       * exp.
       * 
       * Se realiza la operaci�n \f$(*this) = (*this)^{exp}\f$
       *
       * \note
       * Esta funci�n depende de la implementaci�n particular de la
       * clase Potencia accesible mediante la clase Funciones.
       */
      Z& operator^=(Cifra exp); 

      /** Operador de potenciaci�n acumulada.
       *
       * @param exp Dato CifraSigno reprensentado el exponente al que elevar.
       *
       * @return *this, instancia de la clase actual tras elevarla a
       * exp.
       * 
       * Se realiza la operaci�n \f$(*this) = (*this)^{exp}\f$
       *
       * \exception 
       * Errores::ExponenteNegativo Si el entero que
       * representa el exponente exp es negativo.
       *
       * \note
       * Esta funci�n invoca a la versi�n con argumento Cifra. En
       * cualquier caso, depende de la implementaci�n particular de la
       * clase Potencia accesible mediante la clase Funciones.
       * 
       */
      Z& operator^=(CifraSigno exp); 

      /////////////////////////////////
      //   OPERADORES DE COMPARACION //
      /////////////////////////////////
      /** Operador "Mayor que".
       *
       * @param der Entero a comparar con *this. 
       * @return "true" o "false"
       *
       * La comparaci�n se corresponder�a con el predicado \f$(*this) > der\f$
       *
       * \note
       * Esta funci�n delega la comparaci�n en la familia de rutinas
       * de comparacion de la clase vCPUVectorial. Por tanto, La cota
       * de complejidad de esta funci�n sera una constante de �stas.
       * Ver grafo de dependencias para determinar qu� funciones de
       * vCPUVectorial se utilizan en concreto.
       */ 
      bool operator>(const Z& der) const;

      
      /** Operador "Menor que".
       *
       * @param der Entero a comparar con *this. 
       * @return "true" o "false"
       *
       * La comparaci�n se corresponder�a con el predicado \f$(*this) < der\f$
       *
       * \note
       * Esta funci�n delega la comparaci�n en la familia de rutinas
       * de comparacion de la clase vCPUVectorial. Por tanto, La cota
       * de complejidad de esta funci�n sera una constante de �stas.
       * Ver grafo de dependencias para determinar qu� funciones de
       * vCPUVectorial se utilizan en concreto.
       */ 
      bool operator<(const Z& der) const;
  
      
      /** Operador "Igual".
       *
       * @param der Entero a comparar con *this. 
       * @return "true" o "false"
       *
       * La comparaci�n se corresponder�a con el predicado \f$(*this) = der\f$
       *
       * \note
       * Esta funci�n delega la comparaci�n en la familia de rutinas
       * de comparacion de la clase vCPUVectorial. Por tanto, La cota
       * de complejidad de esta funci�n sera una constante de �stas.
       * Ver grafo de dependencias para determinar qu� funciones de
       * vCPUVectorial se utilizan en concreto.
       */ 
      bool operator==(const Z& der) const;
      
      /** Operador "Distinto".
       *
       * @param der Entero a comparar con *this. 
       * @return "true" o "false"
       *
       * La comparaci�n se corresponder�a con el predicado \f$(*this) \neq der\f$
       *
       * \note
       * Esta funci�n delega la comparaci�n en la familia de rutinas
       * de comparacion de la clase vCPUVectorial. Por tanto, La cota
       * de complejidad de esta funci�n sera una constante de �stas.
       * Ver grafo de dependencias para determinar qu� funciones de
       * vCPUVectorial se utilizan en concreto.
       */ 
      bool operator!=(const Z& der) const;
      
      /** Operador "Mayor o igual que".
       *
       * @param der Entero a comparar con *this. 
       * @return "true" o "false"
       *
       * La comparaci�n se corresponder�a con el predicado \f$(*this) \geq der\f$
       *
       * \note
       * Esta funci�n delega la comparaci�n en la familia de rutinas
       * de comparacion de la clase vCPUVectorial. Por tanto, La cota
       * de complejidad de esta funci�n sera una constante de �stas.
       * Ver grafo de dependencias para determinar qu� funciones de
       * vCPUVectorial se utilizan en concreto.
       */ 
      bool operator>=(const Z& der) const;
      
      
      /** Operador "Menor o igual que".
       *
       * @param der Entero a comparar con *this. 
       * @return "true" o "false"
       *
       * La comparaci�n se corresponder�a con el predicado \f$(*this) \leq der\f$
       *
       * \note
       * Esta funci�n delega la comparaci�n en la familia de rutinas
       * de comparacion de la clase vCPUVectorial. Por tanto, La cota
       * de complejidad de esta funci�n sera una constante de �stas.
       * Ver grafo de dependencias para determinar qu� funciones de
       * vCPUVectorial se utilizan en concreto.
       */ 
      bool operator<=(const Z& der) const;

      /** Versi�n de precisi�n simple de "Mayor que"
       *
       * @par Complejidad:
       *      \f$O(1)\f$
       * 
       * @sa operator>(const Z&) const*/
      bool operator>(const CifraSigno der) const;  
      
     
      /** Versi�n de precisi�n simple de "Menor que"
       *
       * @par Complejidad:
       *      \f$O(1)\f$
       * 
       * @sa operator<(const Z&) const*/
     bool operator<(const CifraSigno der) const;

     
     /** Versi�n de precisi�n simple de "Igual"
       *
       * @par Complejidad:
       *      \f$O(1)\f$
       * 
       * @sa operator==(const Z&) const*/
     bool operator==(const CifraSigno der) const;
      
     
     /** Versi�n de precisi�n simple de "Distinto"
       *
       * @par Complejidad:
       *      \f$O(1)\f$
       * 
       * @sa operator!=(const Z&) const*/
     bool operator!=(const CifraSigno der) const;
     
     
     /** Versi�n de precisi�n simple de "Mayor o igual que"
       *
       * @par Complejidad:
       *      \f$O(1)\f$
       * 
       * @sa operator>=(const Z&) const*/
     bool operator>=(const CifraSigno der) const;
     
     
     /** Versi�n de precisi�n simple de "Menor o igual que"
       *
       * @par Complejidad:
       *      \f$O(1)\f$
       * 
       * @sa operator<=(const Z&) const*/
     bool operator<=(const CifraSigno der) const;

     
     /** Versi�n de precisi�n simple de "Mayor que"
       *
       * @par Complejidad:
       *      \f$O(1)\f$
       * 
       * @sa operator>(const Z&) const*/
     bool operator>(const Cifra der) const;
     
     
     /** Versi�n de precisi�n simple de "Menor que"
       *
       * @par Complejidad:
       *      \f$O(1)\f$
       * 
       * @sa operator<(const Z&) const*/
     bool operator<(const Cifra der) const;
     
     
     /** Versi�n de precisi�n simple de "Igual"
       *
       * @par Complejidad:
       *      \f$O(1)\f$
       * 
       * @sa operator==(const Z&) const*/
     bool operator==(const Cifra der) const;
     
     
     /** Versi�n de precisi�n simple de "Distinto"
       *
       * @par Complejidad:
       *      \f$O(1)\f$
       * 
       * @sa operator!=(const Z&) const*/
     bool operator!=(const Cifra der) const;
     
     
     /** Versi�n de precisi�n simple de "Mayor o igual que"
       *
       * @par Complejidad:
       *      \f$O(1)\f$
       * 
       * @sa operator>=(const Z&) const*/
     bool operator>=(const Cifra der) const;
     
     
     /** Versi�n de precisi�n simple de "Menor o igual que"
       *
       * @par Complejidad:
       *      \f$O(1)\f$
       * 
       * @sa operator<=(const Z&) const*/
     bool operator<=(const Cifra der) const;


     
      ////////////////////////////////////
      //   OPERADORES DE DESPLAZAMIENTO //
      ////////////////////////////////////
      /** Operador de desplazamiento a la derecha acumulado.
      *
      * @param n N�mero de bits a desplazar hacia la derecha.
      * @return *this, instancia de la clase actual tras el
      * desplazamiento
      *
      * Se desplaza (*this) un numero n de bits hacia la derecha.
      * Esto es equivalente a \f$(*this) = \lfloor(*this) / 2^{n}\rfloor\f$
      * 
      * \note
      * Esta funci�n delega el desplazamiento en la familia de rutinas
      * de desplazamiento de la clase vCPUVectorial. Por tanto, la cota
      * de complejidad de esta funci�n sera una constante de �stas.
      * Ver grafo de dependencias para determinar qu� funciones de
      * vCPUVectorial se utilizan en concreto.
      */
      Z& operator>>=(const size_t n);
      
      /** Operador de desplazamiento a la izquierda acumulado.
      *
      * @param n N�mero de bits a desplazar hacia la izquierda.
      * @return *this, instancia de la clase actual tras el
      * desplazamiento
      *
      * Se desplaza (*this) un numero n de bits hacia la izquieda.
      * Esto es equivalente a \f$(*this) = (*this) \cdot 2^{n}\f$
      * 
      * \note
      * Esta funci�n delega el desplazamiento en la familia de rutinas
      * de desplazamiento de la clase vCPUVectorial. Por tanto, la cota
      * de complejidad de esta funci�n sera una constante de �stas.
      * Ver grafo de dependencias para determinar qu� funciones de
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
      /** N�mero de bits.
       *
       * @par Complejidad:
       *      \f$O(1)\f$
       * 
       * @return El n�mero de bits de (*this).
       *
       * Se devuelve un dato de tipo size_t con valor el n�mero de
       * bits que ocupa la instancia del entero sobre la que se aplica 
       * el m�todo.
       * Por definici�n el n�mero de bits de un entero N ser�
       * \f$\lceil \log_{2} N \rceil \f$
       * 
       */ 
      size_t numBits(void) const;
 
      //redondeo
      CifraSigno redondear(size_t exceso) ;

      /** Hacer cero.
       * 
       * \par Complejidad:
       *      \f$ O(1) \f$
       *
       * @return Referencia a *this.
       *  
       * Hace que el entero sobre el que se invoca el m�todo pase a ser
       * igual a 0.\n
       *  El objetivo de este m�todo es ser un atajo para la frecuente 
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
       * Hace que el entero sobre el que se invoca el m�todo pase a ser
       * igual a 1.
       *  El objetivo de este m�todo es ser un atajo para la frecuente 
       *  operacion \f$ x = 1 \f$ para el entero \f$x\f$
       *
       */
      Z& hacerUno(void);
  
      /** Hacer el n�mero positivo.
       * 
       * \par Complejidad:
       *      \f$ O(1) \f$
       *
       * @return Referencia a *this.
       *  
       * Hace que el entero sobre el que se invoca el m�todo pase a ser
       * positivo.
       */
      inline Z& hacerPositivo(void) { signo_ = 1; return *this; } 
      
      /** Hacer el n�mero negativo.
       * 
       * \par Complejidad:
       *      \f$ O(1) \f$
       *
       * @return Referencia a *this.
       *  
       * Hace que el entero sobre el que se invoca el m�todo pase a ser
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
       * Hace que el entero sobre el que se invoca el m�todo cambie de signo.
       *  El objetivo de este m�todo es ser un atajo para la frecuente 
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
       *  El objetivo de este m�todo es ser un atajo para la frecuente 
       *  operacion de comprobar si un n�mero es cero.
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
       *  El objetivo de este m�todo es ser un atajo para la frecuente 
       *  operacion de comprobar si un n�mero es uno.
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
       *  El objetivo de este m�todo es ser un atajo para la frecuente 
       *  operacion de comprobar si un n�mero es positivo.
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
       *  El objetivo de este m�todo es ser un atajo para la frecuente 
       *  operacion de comprobar si un n�mero es negativo.
       */
     inline bool esNegativo(void) const { return signo_ < 0; }
 
      /** Eliminar ceros no significativos.
       * 
       * \par Complejidad:
       *      \f$ O(n) \f$
       *
       *  Este m�todo elimina los ceros a la izquierda (no
       *  significativos) del entero sobre el que es invocado.
       *  Pese a que no hacerlo teoricamente no plantea problemas, en
       *  la pr�ctica es mejor, desde el punto de vista del rendimiento y 
       *  gesti�n de la memoria, hacerlo.
       *
       *  @note El usuario no deber�a tener la necesidad de utilizar
       *  este m�todo, ya que es utilizado internamente por la
       *  librer�a de forma autom�tica. Se proporciona para
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
       *  El objetivo de este m�todo es ser un atajo para la frecuente 
       *  operacion de comprobar si un n�mero es par.
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
       *  El objetivo de este m�todo es ser un atajo para la frecuente 
       *  operacion de comprobar si un n�mero es impar.
       */
     inline bool esImpar(void) const { return ((coefPoliB_[0] & 0x1)); }
  
     /** Mayor potencia de 2.
       *
       * Este m�todo devuelve el exponente de la mayor potencia de 2
       * contenida en el entero sobre el que se aplica. Esto es,
       * devuelve \f$r\f$ para \f$ n = 2^{r} \times d \quad / \quad \textrm{d impar}\f$.
       * 
       * \par Complejidad:
       *      \f$ O(n) \f$
       *
       * @return Exponente de la mayor potencia de 2 contenida en el
       * n�mero.
       */
     size_t numDoses(void) const;
      /** Valor absoluto.
       *
       * Este m�todo devuelve el valor absoluto del entero sobre el
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
       * Determina si el entero sobre el que se aplica el m�todo es
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
       * Este m�todo define el entero sobre el que se aplica como
       * concatenaci�n de 
       * la ristra de bytes definida por los dos iteradores @a ini y
       * @a fin, que se suponen iteran sobre un tipo de dato de
       * longitud 1 byte (8 bits). De no ser as�, en tan s�lo se
       * considerar�an los 8 bits de menos peso de cada elemento.
       *
       * \note De apuntar @a ini a una posici�n posterior a @a fin, no
       * se realizar� ninguna acci�n.
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
       * Este m�todo vuelca la representaci�n del entero sobre el que
       * se aplica en la ristra de bytes definida por 
       * los dos iteradores @a ini y
       * @a fin, que se suponen iteran sobre un tipo de dato de
       * longitud 1 byte (8 bits). De no ser as�, en tan s�lo ser�n 
       * escritos los 8 bits de menos peso de cada elemento.
       *
       * \note De apuntar @a ini a una posici�n posterior a @a fin, no
       * se realizar� ninguna acci�n. Asimismo, si 
       * la distancia entre iteradores es menor que el n�mero de bytes
       * que pudiera contener el entero, se devolveran s�lo los \f$|ini - fin|\f$
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
       * entero sobre el que se invoca el m�todo.
       *
       * @return Una referencia a *this.
       * 
       * Se divide el entero actual (*this) entre la potencia n-esima
       * de la base; \f$(*this) = (*this) / BITS\_EN\_CIFRA^{n}\f$.\n
       * Es decir, se dejan los d�gitos siguientes al n-esimo en base BITS_EN_CIFRA.
       *
       * */
      Z& divisionBase(const size_t n);

      /** Modulo entre \f$BASE^{n}\f$ 
       *
       * @param n La potencia de la base entre la que se realiza la
       * reduccion del entero sobre el que se invoca el m�todo.
       * 
       * @return Una referencia a *this.
       *
       * Se reduce el entero actual (*this) por la potencia n-esima
       * de la base; \f$(*this) = (*this) \bmod (BITS\_EN\_CIFRA^{n})\f$.\n
       * 
       * Es decir, se dejan los n d�gitos de menor peso en base
       * BITS_EN_CIFRA.
       * */
      Z& moduloBase(const size_t n);
      
      /** Iguala a \f$BASE^{n}\f$.
       * 
       * @param n La potencia de la base a la que se
       * iguala el entero sobre el que se invoca el m�todo.
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
      std::string toString(void);


      /** Get the Z as a single precision signed type.
       *
       * If the conversion cannot be performed (the actual Z being
       * larger than numth::Constantes::CIFRASIGNO_MAX), only the first
       * numth::Constructor::BITS_EN_CIFRASIGNO are considered.
       *
       * @return A CifraSigno representing (a possibly truncated) *this.
       */
      inline CifraSigno toCifraSigno(void) throw(){
        Cifra c = coefPoliB_[0] & (Constantes::CIFRASIGNO_MAX-1);
        CifraSigno ret = (CifraSigno)c;
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
       * larger than numth::Constantes::CIFRA_MAX), only the first
       * numth::Constructor::BITS_EN_CIFRA are considered.
       *
       * @return A Cifra representing (a possibly truncated) *this.
       */
      inline Cifra toCifra(void) throw(){
        return coefPoliB_[0];
      };

      
      //destructor
      ~Z();

      /////////////////////////////////
      //   FUNCIONES DE INFORMACI�N  //
      /////////////////////////////////
      /** Cifras en base BITS_EN_CIFRA 
       *
       * @par Complejidad:
       *      \f$O(1)\f$
       *
       * @return El n�mero de cifras del entero sobre el que se invoca
       *         el m�todo en base BITS_EN_CIFRA.
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
       * @param i Cifra a considerar (desde 0 hasta
       * \f$longitud()-1\f$).
       *
       * @return Referencia a la i-�sima cifra del entero en base 
       * \f$2^{BITS\_EN\_CIFRA}\f$.
       *
       */
      inline
        Cifra& operator[](size_t i) { return coefPoliB_[i]; }
 
      /** Acceso constante a cifra.
       *  
       *  Acceso a una cifra del  entero 
       *  (recordando que el entero se representa en base
       *  \f$2^{BITS\_EN\_CIFRA}\f$
       * 
       * @par Complejidad:
       *      \f$O(1)\f$
       *
       * @param i Cifra a considerar (desde 0 hasta
       * \f$longitud()-1\f$).
       * 
       * @return Copia de la i-�sima cifra del entero en base 
       * \f$2^{BITS\_EN\_CIFRA}\f$.
       *
       */
      inline
        Cifra operator[](size_t i) const { return coefPoliB_[i]; }

      /** Signo del entero. 
       * 
       * @par Complejidad:
       *      \f$O(1)\f$
       *
       *  @return Un valor mayor que 0 (t�picamente "1")
       *          si el entero es mayor o igual que 0.\n
       *          Un valor menor que 0 (t�picamente "-1") si no.
       */
      inline 
        long signo(void) const { return signo_; }


      //relativas a precision de salida
      /** Ver precisi�n actual de salida.
       *
       *  Este m�todo est�tico muestra el valor actual de la precisi�n de
       *  salida para enteros.
       *
       * \note Un valor de \f$0\f$ representa precisi�n ilimitada.
       *
       * @par Complejidad:
       *      \f$O(1)\f$
       *  
       * @return El valor actual de la precisi�n de salida para
       * enteros.
       *
       */
      inline 
        static size_t precisionSalida(void) { return precisionSalida_; }

      /** Establecer precisi�n de salida.
       *
       *  Este m�todo est�tico establece el valor actual de la precisi�n de
       *  salida para enteros.
       *
       * \note Un valor de \f$0\f$ representa precisi�n ilimitada.
       * 
       * @par Complejidad:
       *      \f$O(1)\f$
       *  
       *  @param nueva La nueva precisi�n a utilizar.
       *
       */
      inline 
        static void precisionSalida(size_t nueva) 
        { precisionSalida_ = nueva; return;}


      /** TODO */
      static Z Zero;

    protected:
      Z( const CifraSigno ); /**< construccion desde simple precision */
      Z( const Cifra ); /**< construccion desde 'token' b�sico */
      Z( const double ); /**< construccion desde double  */
      Z( const char* ); /**< construccion desde cadena de caracteres */

      /** Vector de coeficientes del polinomio que representa el n�mero en base B */
      numth::MiVec<Cifra> coefPoliB_; 
      int8_t signo_; /**< Indica el signo del numero largo representado. \n
                     Valor positivo \f$\Rightarrow\f$ entero positivo. \n
                     valor negativo \f$\Rightarrow\f$ entero negativo.
                     */
      static size_t precisionSalida_; /**< Indica la precisi�n de salida a utilizar. 

      Esto es, no se presentar�n mas que \f$precisionSalida\_\f$ digitos decimales, 
      representandose en resto del n�mero con notaci�n "eN" siendo "N" el exponente
      de la potencia de 10 adecuada.
      
      \note Un valor de \f$0\f$ representa precisi�n ilimitada.

      */

      /** Operador de salida del n�mero */
      friend std::ostream& operator<<(std::ostream&, Z);
      /** Operador obtencion del n�mero */
      friend std::istream& operator>>(std::istream&, Z&) throw (Errores::Sintactico);

      /** Funciones (procedimientos) para el calculo simultaneao de cociente y m�dulo.
       *
       *  @par Complejidad:
       *       \f$O(n \cdot m) \quad / \quad n=tam(dividendo) y m=tam(divisor)\f$
       * 
       * @param dividendo Entero a dividir.
       * @param divisor Entero que divide.
       * @param cociente Direcci�n del Entero para el cociente.
       * @param resto Direccion del Entero para el resto.
       *
       * @return Los valores devueltos son los parametris "cociente" y
       * "resto".
       */
      friend void divMod(const Z& dividendo, const Z& divisor, Z* cociente, Z* resto) 
        throw (Errores::DivisionPorCero);
      friend void divMod(const Z& dividendo, const CifraSigno divisor, Z* cociente, Z* resto) 
        throw (Errores::DivisionPorCero);
      friend void divMod(const Z& dividendo, const Cifra divisor, Z* cociente, Z* resto) 
        throw (Errores::DivisionPorCero);


  };

  /** Versi�n de precisi�n simple con signo del operador "<" */
  bool operator<(const CifraSigno, const Z&);
  /** Versi�n de precisi�n simple con signo del operador ">" */
  bool operator>(const CifraSigno, const Z&);
  /** Versi�n de precisi�n simple con signo del operador "<=" */
  bool operator<=(const CifraSigno, const Z&);
  /** Versi�n de precisi�n simple con signo del operador ">=" */
  bool operator>=(const CifraSigno, const Z&);
  /** Versi�n de precisi�n simple con signo del operador "==" */
  bool operator==(const CifraSigno, const Z&);
  /** Versi�n de precisi�n simple con signo del operador "!=" */
  bool operator!=(const CifraSigno, const Z&);


  /** Versi�n de precisi�n simple sin signo del operador "<" */
  bool operator<(const Cifra, const Z&);
  /** Versi�n de precisi�n simple sin signo del operador ">" */
  bool operator>(const Cifra, const Z&);
  /** Versi�n de precisi�n simple sin signo del operador "<=" */
  bool operator<=(const Cifra, const Z&);
  /** Versi�n de precisi�n simple sin signo del operador ">=" */
  bool operator>=(const Cifra, const Z&);
  /** Versi�n de precisi�n simple sin signo del operador "==" */
  bool operator==(const Cifra, const Z&);
  /** Versi�n de precisi�n simple sin signo del operador "!=" */
  bool operator!=(const Cifra, const Z&);

  //se devuelve un objeto (y no una referencia) debido a lo
  //expuesto en stroustrup p�g. 297 ultimo parrafo.
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
  /** Divisi�n no acumulativa de enteros.
   *
   * @param a Dividendo.
   * @param b Divisor.
   * 
   * @return El entero cociente \f$\lfloor(a/b)\rfloor\f$. 
   */
  Z operator/(Z a, const Z& b);
  /** Resto no acumulativo de la divisi�n entera.
   *
   * @param a Dividendo.
   * @param b Divisor.
   * 
   * @return El entero resto de la divisi�n \f$\lfloor(a/b)\rfloor\f$. 
   */
  Z operator%(Z a, const Z& b);
  /** Operaci�n AND a nivel de bits no acumulativa.
   *
   * @param a Operando izquierdo.
   * @param b Operando derecho.
   * 
   * @return El entero resultado de la operaci�n AND a nivel de bits
   * de @a a y @a b. 
   */
  Z operator&(Z a, const Z& b);
  /** Operaci�n OR a nivel de bits no acumulativa.
   *
   * @param a Operando izquierdo.
   * @param b Operando derecho.
   * 
   * @return El entero resultado de la operaci�n OR a nivel de bits
   * de @a a y @a b. 
   */
  Z operator|(Z a, const Z& b);

  /** Operaci�n XOR a nivel de bits no acumulativa.
   *
   * @param a Operando izquierdo.
   * @param b Operando derecho.
   * 
   * @return El entero resultado de la operaci�n XOR a nivel de bits
   * de @a a y @a b. 
   */
  Z XOR(Z a, const Z &b);

  /** Versi�n de precisi�n simple de operator+(Z, const Z&)*/
  Z operator+(const CifraSigno, Z); 
  /** Versi�n de precisi�n simple de operator-(Z, const Z&)*/
  Z operator-(const CifraSigno, Z);
  /** Versi�n de precisi�n simple de operator*(Z, const Z&)*/
  Z operator*(const CifraSigno, Z);
  /** Versi�n de precisi�n simple de operator/(Z, const Z&)*/
  Z operator/(const CifraSigno, const Z&);
  /** Versi�n de precisi�n simple de operator%(Z, const Z&)*/
  Z operator%(const CifraSigno, const Z&);
  /** Versi�n de precisi�n simple de operator&(Z, const Z&)*/
  Z operator&(const CifraSigno, Z);
  /** Versi�n de precisi�n simple de operator|(Z, const Z&)*/
  Z operator|(const CifraSigno, Z);
  /** Versi�n de precisi�n simple de XOR(Z, const Z&)*/
  Z XOR(const CifraSigno, Z);


  /** Versi�n de precisi�n simple de operator+(Z, const Z&)*/
  Z operator+(Z, const CifraSigno);
  /** Versi�n de precisi�n simple de operator-(Z, const Z&)*/
  Z operator-(Z, const CifraSigno);
  /** Versi�n de precisi�n simple de operator*(Z, const Z&)*/
  Z operator*(Z, const CifraSigno);
  /** Versi�n de precisi�n simple de operator/(Z, const Z&)*/
  Z operator/(Z, const CifraSigno);
  /** Versi�n de precisi�n simple de operator%(Z, const Z&)*/
  Z operator%(Z, const CifraSigno);
  /** Versi�n de precisi�n simple de operator&(Z, const Z&)*/
  Z operator&(Z, const CifraSigno);
  /** Versi�n de precisi�n simple de operator|(Z, const Z&)*/
  Z operator|(Z, const CifraSigno);
  /** Versi�n de precisi�n simple de XOR(Z, const Z&)*/
  Z XOR(Z, const CifraSigno);

  /** Versi�n de precisi�n simple de operator+(Z, const Z&)*/
  Z operator+(const Cifra, Z);
  /** Versi�n de precisi�n simple de operator-(Z, const Z&)*/
  Z operator-(const Cifra, Z);
  /** Versi�n de precisi�n simple de operator*(Z, const Z&)*/
  Z operator*(const Cifra, Z);
  /** Versi�n de precisi�n simple de operator/(Z, const Z&)*/
  Z operator/(const Cifra, const Z&);
  /** Versi�n de precisi�n simple de operator%(Z, const Z&)*/
  Z operator%(const Cifra, const Z&);
  /** Versi�n de precisi�n simple de operator&(Z, const Z&)*/
  Z operator&(const Cifra, Z);
  /** Versi�n de precisi�n simple de operator|(Z, const Z&)*/
  Z operator|(const Cifra, Z);
  /** Versi�n de precisi�n simple de XOR(Z, const Z&)*/
  Z XOR(const Cifra, Z);

 
  /** Versi�n de precisi�n simple de operator+(Z, const Z&)*/
  Z operator+(Z, const Cifra);
  /** Versi�n de precisi�n simple de operator-(Z, const Z&)*/
  Z operator-(Z, const Cifra);
  /** Versi�n de precisi�n simple de operator*(Z, const Z&)*/
  Z operator*(Z, const Cifra);
  /** Versi�n de precisi�n simple de operator/(Z, const Z&)*/
  Z operator/(Z, const Cifra);
  /** Versi�n de precisi�n simple de operator%(Z, const Z&)*/
  Z operator%(Z, const Cifra);
  /** Versi�n de precisi�n simple de operator&(Z, const Z&)*/
  Z operator&(Z, const Cifra);
  /** Versi�n de precisi�n simple de operator|(Z, const Z&)*/
  Z operator|(Z, const Cifra);
  /** Versi�n de precisi�n simple de XOR(Z, const Z&)*/
  Z XOR(Z, const Cifra);

  Z operator-(Z); /**< Operator - unario: cambio de signo */

  /** Operador de potenciaci�n.
   *
   * @param base Entero base de la potenciaci�n.
   * @param exp Entero exponente.
   *
   * @return Entero igual a \f$base^{exp}\f$
   * @sa class Potencia.
   *
   * @note El exponente ha de ser \f$\leq 2^{BASE}\f$ o se lanzar� un
   * error de tipo Errores::DemasiadoGrande
   *
   */
  Z operator^(Z base, const Z& exp); 
   /** Operador de potenciaci�n.
   *
   * @param base Entero base de la potenciaci�n.
   * @param exp Cifra exponente.
   *
   * @return Entero igual a \f$base^{exp}\f$
   * @sa class Potencia.
   *
   */
 Z operator^(Z base, const Cifra exp); 
   /** Operador de potenciaci�n.
   *
   * @param base Entero base de la potenciaci�n.
   * @param exp CifraSigno exponente.
   *
   * @return Entero igual a \f$base^{exp}\f$
   * 
   * @sa class Potencia.
   *
   * @note El exponente ha de ser positivo o se lanzar� un
   * error de tipo Errores::ExponenteNegativo
   *
   */
 Z operator^(Z base, const CifraSigno exp); 

 /** Cuadrado (versi�n "funci�n").
  *
  * @param x Entero del que hacer el cuadrado.
  *
  * @return Entero igual a \f$ x^2 \f$.
  *
  * @sa Z::cuadrado()
  */
  Z cuadrado(Z x);
 
 /** Cuadrado modular (versi�n "funci�n").
  *
  * @param x Entero del que hacer el cuadrado modular.
  * @param mod M�dulo reductor.
  *
  * @return Entero igual a \f$ x^2 \bmod mod\f$.
  *
  * @sa Z::cuadrado()
  */
  Z cuadradoModular(Z x, const Z& mod);
  
  /** Factorial (versi�n "funci�n").
   *
   * @sa Z::factorial()
   * 
   */
  Z factorial(Z x);
   /** Ra�z cuadrada entera (versi�n "funci�n").
   *
   * @sa Z::raizCuadrada()
   * 
   */
  Z raizCuadrada(Z x);
  /** Ra�z cuadrada entera precisi�n simple (versi�n "funci�n").
   *
   * @sa Z::raizCuadrada()
   * 
   */
  Cifra raizCuadrada(Cifra x);
  
  
  /** Determinar si es cuadrado perfecto (versi�n "funci�n")
   *
   * @sa Z::esCuadrado()
   */
  bool esCuadrado(Z x);

  /** Valor absoluto (versi�n "funci�n")
   * @sa Z::abs()
   */
  Z abs(Z x);


  /** N�mero de bits (versi�n "funci�n").
   *
   * @sa Z::numBits() 
   */
  size_t numBits(const Z& x);
  /** N�mero de bits precisi�n simple sin signo (versi�n "funci�n").
   *
   * @sa Z::numBits() 
   */
  size_t numBits(const Cifra x);
  /** N�mero de bits precisi�n simple con signo(versi�n "funci�n").
   *
   * @sa Z::numBits() 
   */
  size_t numBits(const CifraSigno x);


  //OPERADORES DE DESPLAZAMIENTO 
  
  /** Operador de desplazamiento a la derecha no acumulativo.
   *
   * @param entero El entero a desplazar.
   * @param n El n�mero de posiciones a desplazar
   *
   * @return El entero desplazado @a n posiciones de bits a la
   * derecha.
   *
   * @sa Z::operator>>=(const size_t n) */
  Z operator>>(Z entero, const size_t n);
  /** Operador de desplazamiento a la izquierda no acumulativo.
   *
   * @param entero El entero a desplazar.
   * @param n El n�mero de posiciones a desplazar
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
    // Si la distancia entre iteradores es menor que el n� de bytes
    // que pudiera contener el Z, se devolveran s�lo los |inicio-fin|
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
