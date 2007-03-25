/*
 * $Id$ 
 */

#ifndef __ERR_H
#define __ERR_H

#include <iostream>
#include <string>
#include <stdexcept>
#include <exception>

#include "AlgebraUtils.h"

//FIXME
#define _(STRING) STRING

namespace mpplas{
  /** Espacio de nombres contenedor del mecanismo de errores. */
  namespace Errores{
    // Tipos báicos
    /** Clase base de todas las excepciones (errores) que comprende
     * la librería. */
    class Exception: public std::exception 
    {
      public:
        virtual ~Exception() throw()
        {}
    };
      
    /** Clase base para errores de tipo aritméico.
     *
     * Ejemplo clásico: la división por cero.
     * 
     * */
    class Aritmetico : public Exception
    {
      public:
      virtual const char* what(void) const throw()
      {
        return _("Undefined arithmetic error");
      }

      virtual ~Aritmetico() throw() {}

    };

    /** Clase base para errores de tipo sintáctico.
     *
     * Se utiliza por ejemplo en la lectura de números con el operador
     * de entrada ">>".
     * 
     */
    class Sintactic : public Exception
    {
      public:
        Sintactic( std::string msg = "<empty>" )
        {
          _msg = "Sintactic error: ";
          _msg += msg;
        }
        virtual const char* what(void) const throw() 
        {
          return _msg.c_str();
        }

        virtual ~Sintactic() throw() {}

      private:
        std::string _msg;

    };

    /** Clase base para errores internos.
     *
     * Por ejemplo al detectar un puntero inválido, intento de acceso
     * a una posición de memoria no reservada, etc.
     * */
    class Interno : public Exception
    {
      public:
        virtual const char* what(void) const throw()
        {
          return _("Undefined internal error");
        }
    };


    ////////////////////////////////////////////////////////////////////////////////////

    // Tipos derivados
    /** Error de división por cero */
    class DivisionPorCero : public Aritmetico
    {
      public:
      virtual const char* what(void) const throw() 
      { 
        return _("Division by zero");
      }
    };

    /** Resultado negativo en resta sin signo */
    class RestaNegativa : public Aritmetico
    {
      public:
      virtual const char* what(void) const throw()
      {
        return _("Subtrahend is greater than the minuend at unsigned subtraction");
      }
    };

    /** Elemento no invertible en un grupo finito */
    class ElementoNoInvertible : public Aritmetico
    {
      public:
      virtual const char* what(void) const throw()
      {
         return _("Invalid inversion");
      }
    };

    /** Intento de potenciación de un elemento no inverbiel en un no-cuerpo */
    class ExponenteNegativo : public Aritmetico
    {
      public:
      virtual const char* what(void) const throw()
      {
         return _("Negative exponent on a non-invertible element");
      }
    };

    /** Segundo argumento de un símbolo de Jacobi es par */
    class ParEnSimboloJacobi : public Aritmetico
    {
      public:
      virtual const char* what(void) const throw()
      {
         return _("Even element as second argument of a Jacoby Symbol");
      }
    };

    /** Modulo par en la exponenciación por Montgomery */
    class ModuloParEnMontgomery : public Aritmetico
    {
      public:
      virtual const char* what(void) const throw()
      {
         return _("Even modulus on Montgomery exponentiation"); 
      }
    };

    /** Logaritmo de cero */
    class LogaritmoDeCero : public Aritmetico
    {
      public:
      virtual const char* what(void) const throw()
      {
         return _("Calculation of the logarithm of zero");
      }
    };

    class NonConformantDimensions: public Aritmetico
    {
      public:
        NonConformantDimensions(const Dimensions& dimsLeft, const Dimensions& dimsRight, std::string str = ""){
          _str = "Non conformant dimensions: " + dimsLeft.toString() + " and " + dimsRight.toString() + " " + str;
        }

        virtual const char* what(void) const throw() {
          return _str.c_str();
        }

        virtual ~NonConformantDimensions() throw() {}
      private:
        std::string _str;
    };






    /** Detectado símbolo inválido en la lectura de un nmero */
    class InvalidSymbol: public Sintactic
    {
      public:
        InvalidSymbol(std::string str = "<empty>"){
          _str = "Invalid symbol: ";
          _str += str;
        }
        virtual const char* what(void) const throw()  { 
          return _str.c_str();
        }

        virtual ~InvalidSymbol() throw() {}

      private:
        std::string _str;

    };

    /** Signo inválido */
    class SignoInvalido : public Interno
    {
      virtual const char* what(void) const throw()
      {
         return _("Incorrect sign");
      }

    };

    /** Uso de un nmero demasiado grande para el contexto */
    class DemasiadoGrande : public Interno
    {
      virtual const char* what(void) const throw()
      {
         return _("Number too big");
      }
    };

    /** Intento de uso de perfilado en arquitectura que no lo soporta
     * */
    class ArchNoProfiling : public Interno
    {
      virtual const char* what(void) const throw()
      {
         return _("The current architecture does not support profiling");
      }
    };


    /** Error en el proceso de perfilado */
    class ErrorPerfilado : public Interno
    {
      virtual const char* what(void) const throw()
      {
         return _("Profiling error");
      }
    };


    /** Error al acceder a la fuente de entropía */
    class FuenteEntropiaInvalida : public Interno
    {
      virtual const char* what(void) const throw()
      {
         return _("Error while accessing the entropy source");
      }
    };

    
    /** Intento de desreferenciar un puntero nulo */
    class PunteroNulo : public Interno
    {
      virtual const char* what(void) const throw()
      {
         return _("Null pointer error");
      }
    };

    /** Exponente de reales desbordado */
    class OverflowExpReales : public Interno
    {
      virtual const char* what(void) const throw()
      {
         return _("The exponent for floating-point exp. overflowed");
      }
    };
 
    /** Función no implementada */
    class NoImplementado : public Interno
    {
      virtual const char* what(void) const throw()
      {
         return _("Feature not implemented");
      }
    };

  
  }//namespace Errores
}//namespace 

   
#endif
