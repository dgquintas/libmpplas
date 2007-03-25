/* 
 * $Id$
 */
#ifndef __TRANSCENDENTES_H
#define __TRANSCENDENTES_H

#include "R.h"
#include "AbstractMethod.h"

namespace mpplas{

  class ExpTaylor;
  class LnTaylor;
  class CosTaylor;
  class SenFase;
  class ATanTaylor;
  class PiMachin;


  /** Interfaz para la exponencial ( e^x ) en los reales.
   *
   * Clase base para métodos de exponencial de reales (esto es,
   * \f$ e^x \f$, con \f$ e \f$ la base de los logaritmos naturales) */
  class Exponencial : public AbstractMethod
  {
    public:
      /** Exponenciación (\f$ e^x \f$) en los reales 
       *
       * Este método devuelve el real resultado de la exponencial
       * real al exponente @a x de la base \f$ e \f$ de los logaritmos
       * naturales.
       *
       * @param x El exponente de \f$ e^x \f$.
       *
       * @return El entero resultado de la exponencial.
       * */
      virtual R exponencial(const R& x) = 0;

      virtual ~Exponencial(){}
  
      typedef ExpTaylor DFL;
  };

  class Ln: public AbstractMethod
  {
    public:
      virtual R ln(const R& x) = 0;

      virtual ~Ln(){}
  
      typedef LnTaylor DFL;
  };

  class Seno: public AbstractMethod
  {
    public:
      virtual R seno(const R& x) = 0;

      virtual ~Seno(){}
  
      typedef SenFase DFL;
  };

  class Coseno: public AbstractMethod
  {
    public:
      virtual R coseno(const R& x) = 0;

      virtual ~Coseno(){}
  
      typedef CosTaylor DFL;
  };
 
  class Tangente: public AbstractMethod
  {
    public:
      virtual R tangente(const R& x) = 0;

      virtual ~Tangente(){}
  
  };

  class ArcoTangente: public AbstractMethod
  {
    public:
      virtual R arcotangente(const R& x) = 0;

      virtual ~ArcoTangente(){}
      typedef ATanTaylor DFL;
  };
 
  class Pi: public AbstractMethod
  {
    public:
      virtual R pi(size_t prec = 0) = 0;

      virtual ~Pi(){}
  
      typedef PiMachin DFL;
  };


  /* implementacion */
  /** Implementation of the exponential function by means of the 
   * Taylor/McLaurin series expansion.
   *
   *  This implementation uses the McLaurin series of \f$ e^x \f$,
   *  i.e, \f$ e^x = \sum_{k=0}^{\infty} \frac{x^k}{k!} \f$.
   */
  class ExpTaylor : public Exponencial
  {
    public:
      virtual R exponencial(const R& x);
        
    private:
      /** Particular case when @a x equals 1. It's used by the
       * implementation. */
      R e(void);
      
  };
 
  /** Implementation of the natural logarithm function by means of the 
   * Taylor/McLaurin series expansion (and some other "tricks").
   *
   *  This implementation uses the McLaurin series of \f$ \ln x \f$,
   *  i.e, \f$ \ln x = 2 \times \left( \frac{x-1}{x+1} + 
   *  (1/3) \times {\left(\frac{x-1}{x+1}\right)}^3 + 
   *  (1/5) \times {\left(\frac{x-1}{x+1}\right)}^5 + \ldots \right) \f$.
   *
   *  It also takes advantage of the fact that we know the bit size of
   *  @a x, so working with only \f$ \ln 2 \f$ and the calculus of
   *  another logarithm which argument will always be less than 2, we
   *  are able to work out the \f$ \ln \f$ of any argument @a x (see
   *  documentation for more in-depth details).
   *  
   *  
   */

  class LnTaylor : public Ln
  {
    public: 
      virtual R ln(const R& x);

    private:
      R ln2(void);

  };
  

  /** Cálculo del seno utilizando el desplazamiento de fase respecto
   * al coseno.
   *
   * Aprovechando que el seno está desfasado medio ciclo respecto al
   * coseno (\f$ \sin(x) = \cos\left(\frac{\pi}{2} - x \right) \f$),
   * se calcula el seno en base al coseno.
   *
   * */
  class SenFase : public Seno
  {
    public: 
      virtual R seno(const R& x);

  };

  

  /**            */
  class CosTaylor : public Coseno
  {
    public: 
      virtual R coseno(const R& x);

  };

  
   /**            */
  class ATanTaylor : public ArcoTangente
  {
    public: 
      virtual R arcotangente(const R& x);

  };
 
  /** Calculation of \f$ \pi \f$ by means of the Machin's formula:
   * \f$ \pi/4 = 4 \arctan(1/5) - \arctan(1/239) \f$ */
  class PiMachin : public Pi
  {
    public:
      /** Calculation of \f$ \pi \f$ to @a prec decimal places. 
       * @param prec Number of decimal places to calculate. If @a prec
       * equals 0, the default precision for real numbers will be
       * used. */
      virtual R pi(const size_t prec = 0);
  };


}

#endif
