/* 
 * $Id$
 */

#ifndef __HASH_H
#define __HASH_H

#include "Z.h"
#include "MiVec.h"

namespace numth{

  /** Interfaz para funciones hash.
   *
   * Clase base para algoritmos que implementen funciones hash.
   * 
   */
  class Hash
  {
    public:
      /** Inicializar la función hash. 
       * 
       * Se inicializa la función hash. Es necesario invocar este
       * método previamente a cualquiera de los demás de la clase.
       */
      virtual void inicializar(void) = 0;
      
      /** Introducir datos a la función hash.
       *
       * Se actualiza el contenido del resumen generado por la función
       * hash con los datos suministrados.
       *
       * @param datos Vector de bytes con los datos a introducir en la
       * función hash.
       */
      virtual void actualizar(const MiVec<uint8_t>& datos) = 0;
      
      /** Finalizar la función hash.
       *
       * Finaliza el cálculo del resumen de la función hash. Es
       * necesario invocar este método antes de tratar de obtener el
       * valor del resumen. No hacerlo provocará que el contenido del
       * resumen que se obtenga tenga un valor indeterminado. 
       */
      virtual void finalizar(void) = 0;
      
      /** Aplicar el cuerpo de la función hash.
       *
       * Este método realiza las iteraciones de la función hash
       * propiamente dicha.
       * @note El usuario no debería tener necesidad de invocar este
       * método directamente, ya que se invoca de forma automática al
       * añadir datos a la función hash y al finalizar la misma.
       */
      virtual void procesar(void) = 0;
      
      /** Obtener el resumen como un entero.
       *
       * Devuelve un entero conteniendo el valor del resumen generado
       * por la función hash.
       *
       * @return Entero conteniendo en valor del resumen generado por
       * la función hash.
       */
      virtual Z obtenerEnteroResumen(void) = 0;
 
      /** Obtener el resumen como un vector.
       *
       * Devuelve un vector de elementos de 32 bits conteniendo el valor del resumen generado
       * por la función hash.
       *
       * @return Vector de elementos de 32 bits conteniendo en valor del resumen generado por
       * la función hash.
       */
      virtual MiVec<uint32_t> obtenerVectorResumen(void) = 0;
      
      /** Obtener tamaño del resumen que genera la función hash.
       *
       * Método de información para saber que tamaño de resumen genera
       * la función hash implementada.
       *
       * @return El número de bits del resumen que genera la función hash.
       */
      virtual size_t numBitsResumen(void) const = 0;

      virtual ~Hash(){}
  };

  /** Implementación de la función hash MD5. 
   *
   * Descrito en el RFC 1321.
   * http://www.faqs.org/rfcs/rfc1321.html
   */
  class MD5 : public Hash
  {
    public:
      MD5(void);
      virtual void inicializar(void);
      virtual void actualizar(const MiVec<uint8_t>& datos);
      virtual void finalizar(void);
      virtual void procesar(void);
      virtual Z obtenerEnteroResumen(void);
      virtual MiVec<uint32_t> obtenerVectorResumen(void);
      virtual size_t numBitsResumen(void) const { return (size_t)128; }
    
      virtual ~MD5(){}  
      
    private:
      uint32_t resumen_[4];
      uint32_t tam_[2];
      uint8_t buffer8_[64];
      uint32_t buffer32_[16];

      bool finalizado_;
      
      inline uint32_t rotarIzq(uint32_t x, size_t n)
      {
        return (((x) << (n)) | ((x) >> (32-(n))));
      }
        
      
      inline uint32_t F(uint32_t x, uint32_t y, uint32_t z)
      {
        return (((x) & (y)) | ((~x) & (z)));
      }
      inline uint32_t G(uint32_t x, uint32_t y, uint32_t z)
      {
        return (((x) & (z)) | ((y) & (~z)));
      }
      inline uint32_t H(uint32_t x, uint32_t y, uint32_t z)
      {
        return ((x) ^ (y) ^ (z));
      }
      inline uint32_t I(uint32_t x, uint32_t y, uint32_t z)
      {
        return  ((y) ^ ((x) | (~z)));
      }
  
      inline void FF(uint32_t& a, const uint32_t b, const uint32_t c, const uint32_t d, 
                     const uint32_t Mj, const uint32_t s, const uint32_t ti)
      {
        a = b + rotarIzq( (a + F(b,c,d) + Mj + ti), s);
      }
      inline void GG(uint32_t& a, const uint32_t b, const uint32_t c, const uint32_t d, 
                     const uint32_t Mj, const uint32_t s, const uint32_t ti)
      {
        a = b + rotarIzq( (a + G(b,c,d) + Mj + ti), s);
      }
      inline void HH(uint32_t& a, const uint32_t b, const uint32_t c, const uint32_t d, 
                     const uint32_t Mj, const uint32_t s, const uint32_t ti)
      {
        a = b + rotarIzq( (a + H(b,c,d) + Mj + ti), s);
      }
      inline void II(uint32_t& a, const uint32_t b, const uint32_t c, const uint32_t d, 
                     const uint32_t Mj, const uint32_t s, const uint32_t ti)
      {
        a = b + rotarIzq( (a + I(b,c,d) + Mj + ti), s);
      }


  };
  typedef MD5 HashDFL;

      
}

#endif
