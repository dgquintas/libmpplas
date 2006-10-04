/*
 * $Id$ 
 */

#ifndef __ERR_H
#define __ERR_H

#include <iostream>
#include <string>
#include <stdexcept>

namespace numth{
  /** Espacio de nombres contenedor del mecanismo de errores. */
  namespace Errores{
    // Tipos básicos
    /** Clase base de todas las excepciones (errores) que comprende
     * la librería. */
    class Excepcion
    {
      public:
        /** Información sobre el error.
         * 
         * @return Un vector de caracteres con un mensaje explicativo
         * del error en cuestión.
         */
        virtual const char* info(void) const = 0;
        virtual ~Excepcion(){};
    };
      
    /** Clase base para errores de tipo aritmético.
     *
     * Ejemplo clásico: la división por cero.
     * 
     * */
    class Aritmetico : public Excepcion
    {
      public:
      virtual const char* info(void) const 
      {
        return "Error aritmético indeterminado";
      }
    };

    /** Clase base para errores de tipo sintáctico.
     *
     * Se utiliza por ejemplo en la lectura de números con el operador
     * de entrada ">>".
     * 
     */
    class Sintactico : public Excepcion
    {
      public:
      virtual const char* info(void) const 
      {
        return "Error sintáctico indeterminado";
      }
    };

    /** Clase base para errores internos.
     *
     * Por ejemplo al detectar un puntero inválido, intento de acceso
     * a una posición de memoria no reservada, etc.
     * */
    class Interno : public Excepcion
    {
      public:
        virtual const char* info(void) const
        {
          return "Error interno indeterminado";
        }
    };


    // Tipos derivados
    /** Error de división por cero */
    class DivisionPorCero : public Aritmetico
    {
      public:
      virtual const char* info(void) const 
      { 
        return "Se ha producido una división por cero";
      }
    };

    /** Resultado negativo en resta sin signo */
    class RestaNegativa : public Aritmetico
    {
      public:
      virtual const char* info(void) const
      {
        return "Sustraendo mayor que minuendo en resta sin signo a nivel MP";
      }
    };

    /** Elemento no invertible en un grupo finito */
    class ElementoNoInvertible : public Aritmetico
    {
      public:
      virtual const char* info(void) const
      {
         return "Intento de inversión inválido";
      }
    };

    /** Intento de potenciación de un elemento no inverbiel en un no-cuerpo */
    class ExponenteNegativo : public Aritmetico
    {
      public:
      virtual const char* info(void) const
      {
         return "Exponente negativo en elemento no invertible";
      }
    };

    /** Segundo argumento de un símbolo de Jacobi es par */
    class ParEnSimboloJacobi : public Aritmetico
    {
      public:
      virtual const char* info(void) const
      {
         return "Segundo argumento del Simbolo de Jacobi par";
      }
    };

    /** Modulo par en la exponenciación por Montgomery */
    class ModuloParEnMontgomery : public Aritmetico
    {
      public:
      virtual const char* info(void) const
      {
         return "Modulo par en exponenciación de Montgomery";
      }
    };

    /** Logaritmo de cero */
    class LogaritmoDeCero : public Aritmetico
    {
      public:
      virtual const char* info(void) const
      {
         return "Intento de cálculo del logaritmo de cero";
      }
    };




    /** Detectado símbolo inválido en la lectura de un número */
    class SimboloInvalido : public Sintactico
    {
      char simbolo_;
      
      public:
        SimboloInvalido(char c) : simbolo_(c){}
        virtual const char* info(void) const 
        { 
          std::string msg("Simbolo inválido: ");
          msg += simbolo_;
          return msg.c_str();
        }
    };

    /** Número sin longitud alguna (al menos tendria que ser 1, para
     * el cero)*/
    class NumeroVacio : public Interno
    {
      virtual const char* info(void) const
      {
         return "Polinomio representante del número de longitud 0";
      }
    };

    /** Signo inválido */
    class SignoInvalido : public Interno
    {
      virtual const char* info(void) const
      {
         return "Signo incorrecto";
      }

    };

    /** Uso de un número demasiado grande para el contexto */
    class DemasiadoGrande : public Interno
    {
      virtual const char* info(void) const
      {
         return "Número demasiado grande";
      }
    };

    /** Intento de uso de perfilado en arquitectura que no lo soporta
     * */
    class ArchNoProfiling : public Interno
    {
      virtual const char* info(void) const
      {
         return "Arquitectura actual no soporta operaciones de perfilado";
      }
    };


    /** Error en el proceso de perfilado */
    class ErrorPerfilado : public Interno
    {
      virtual const char* info(void) const
      {
         return "Error de perfilado";
      }
    };


    /** Error al acceder a la fuente de entropía */
    class FuenteEntropiaInvalida : public Interno
    {
      virtual const char* info(void) const
      {
         return "Error al acceder a la fuente de entropía";
      }
    };

    
    /** Intento de desreferenciar un puntero nulo */
    class PunteroNulo : public Interno
    {
      virtual const char* info(void) const
      {
         return "Se ha proporcionado un puntero nulo donde no se admite";
      }
    };

    /** Exponente de reales desbordado */
    class OverflowExpReales : public Interno
    {
      virtual const char* info(void) const
      {
         return "El exponente de la representación de reales se ha desbordado";
      }
    };
 
    /** Función no implementada */
    class NoImplementado : public Interno
    {
      virtual const char* info(void) const
      {
         return "Función aún no implementada";
      }
    };

  
  }//namespace Errores
}//namespace numth

   
#endif
