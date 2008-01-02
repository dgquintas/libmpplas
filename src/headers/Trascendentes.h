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
  class SqrtNewton;


  /** Exponential function.
   *
   * Base class for the methods implementing the exponential function, 
   * \f$ e^x \f$, being \f$ e \f$ the base of the natural logarithms. */
  class Exponencial : public AbstractMethod {
    public:
      /** Exponential funcion, \f$ e^x \f$.
       *
       * Exponentiation of the constant \f$ e \f$ to the @a x power.
       *
       * @param x the exponent in \f$ e^x \f$.
       *
       * @return the exponential for @a x.
       * */
      virtual R exponencial(const R& x) = 0;

      virtual ~Exponencial(){}
  
      typedef ExpTaylor DFL;
  };

  class Ln: public AbstractMethod {
    public:
      virtual R ln(const R& x) = 0;

      virtual ~Ln(){}
  
      typedef LnTaylor DFL;
  };

  class Sin: public AbstractMethod {
    public:
      virtual R seno(const R& x) = 0;

      virtual ~Sin(){}
  
      typedef SenFase DFL;
  };

  class Cos: public AbstractMethod {
    public:
      virtual R coseno(const R& x) = 0;

      virtual ~Cos(){}
  
      typedef CosTaylor DFL;
  };
 
  class Tan: public AbstractMethod {
    public:
      virtual R tangente(const R& x) = 0;

      virtual ~Tan(){}
  
  };

  class ArcTan: public AbstractMethod {
    public:
      virtual R arcotangente(const R& x) = 0;

      virtual ~ArcTan(){}
      typedef ATanTaylor DFL;
  };
 
  class Pi: public AbstractMethod {
    public:
      virtual R pi(int prec = 0) = 0;

      virtual ~Pi(){}
  
      typedef PiMachin DFL;
  };

  class Sqrt: public AbstractMethod {
    public:
      virtual R sqrt(const R& x) = 0;
      virtual ~Sqrt(){}

      typedef SqrtNewton DFL;
  };


  /* implementacion */
  /** Implementation of the exponential function by means of the 
   * Taylor/McLaurin series expansion.
   *
   *  This implementation uses the McLaurin series of \f$ e^x \f$,
   *  i.e, \f$ e^x = \sum_{k=0}^{\infty} \frac{x^k}{k!} \f$.
   */
  class ExpTaylor : public Exponencial {
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
  class LnTaylor : public Ln {
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
  class SenFase : public Sin {
    public: 
      virtual R seno(const R& x);

  };

  

  /**            */
  class CosTaylor : public Cos {
    public: 
      virtual R coseno(const R& x);

  };

    
   /**            */
  class ATanTaylor : public ArcTan {
    public: 
      virtual R arcotangente(const R& x);

  };
 
  /** Calculation of \f$ \pi \f$ by means of the Machin's formula:
   * \f$ \pi/4 = 4 \arctan(1/5) - \arctan(1/239) \f$ */
  class PiMachin : public Pi  {
    public:
      /** Calculation of \f$ \pi \f$ to @a prec decimal places. 
       * @param prec Number of decimal places to calculate. If @a prec
       * equals 0, the default precision for real numbers will be
       * used. */
      virtual R pi(const int prec = 0);
  };


  class SqrtNewton : public Sqrt {
    public:
      virtual R sqrt(const R& x);
  };

}

#endif
