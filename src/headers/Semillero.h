/* 
 * $Id$
 */

#ifndef __SEEDBANK_H
#define __SEEDBANK_H

#include "Z.h"
#include <fstream>

namespace mpplas{

 
  /** Fuente de semillas aleatorias (<em>realmente aleatorias</em>).
   *
   * Clase "almacén" de entropía real donde se empaqueta ésta en forma
   * de semillas para los métodos que las requieran.
   */
  class Seedbank
  {
    public: 
      Seedbank(void);
   
      ~Seedbank(void);
      
      /** Leer semilla de entropía REAL 
       *
       * @param numBytes Número de bytes a obtener.
       * @return Un entero conteniendo los @e numBytes bytes de datos aleatorios
       * reales.
       *
       * Lee un número determinados de bytes aleatorios obtenidos de
       * una fuente REAL de entropía. 
       *
       * @warning En principio, las llamadas a los métodos de esta 
       * clase podrían bloquearse si no hay suficiente entropía disponible.
       *
       * @note <b> No abusar </b> de esta función: la entropía real es
       * un bien escaso. Si se requiere de datos aleatorios sin 
       * particular fortaleza, utilizar los métodos ofrecidos por el
       * método leerSemilla(size_t numBytes) 
       */
      Z leerSemillaSegura(size_t numBytes);
      
      /** Leer semilla pseudo-aleatoria.
       *
       * @param numBytes Número de bytes a obtener.
       * @return Un entero conteniendo los @e numBytes bytes de datos pseudo-aleatorios
       *
       * Lee un número determinados de bytes aleatorios obtenidos tras
       * aplicar funciones de mezcla fuerte (ver RFC1750 pto. 6.1.2) (en concreto, una función
       * resumen) a datos aleatorios inicialmente reales.
       * En la llamada siguiente a la generacion de un número mayor o
       * igual que UMBRAL_SEMILLA bytes, se vuelve a alimentar a la
       * funcion mezcla con datos aleatorios reales. 
       *
       * @warning En principio, las llamadas a los métodos de esta 
       * clase podrían bloquearse si no hay suficiente entropía disponible tras la 
       * generacion de UMBRAL_SEMILLA bytes. Esto debería suceder rara
       * vez.
       */
      Z leerSemilla(size_t numBytes);


    private:
      MiVec<uint8_t> _source(size_t numBytes);
      MiVec<uint8_t> _randomData;
  };

}

#endif
