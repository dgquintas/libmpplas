/* 
 * $Id$
 */

#ifndef __SEMILLERO_H
#define __SEMILLERO_H

#include "Z.h"
#include <fstream>

namespace numth{

 
  /** Fuente de semillas aleatorias (<em>realmente aleatorias</em>).
   *
   * Clase "almac�n" de entrop�a real donde se empaqueta �sta en forma
   * de semillas para los m�todos que las requieran.
   */
  class Semillero
  {
    public: 
      Semillero(void);
   
      ~Semillero(void);
      
      /** Leer semilla de entrop�a REAL 
       *
       * @param numBytes N�mero de bytes a obtener.
       * @return Un entero conteniendo los @e numBytes bytes de datos aleatorios
       * reales.
       *
       * Lee un n�mero determinados de bytes aleatorios obtenidos de
       * una fuente REAL de entrop�a. 
       *
       * @warning En principio, las llamadas a los m�todos de esta 
       * clase podr�an bloquearse si no hay suficiente entrop�a disponible.
       *
       * @note <b> No abusar </b> de esta funci�n: la entrop�a real es
       * un bien escaso. Si se requiere de datos aleatorios sin 
       * particular fortaleza, utilizar los m�todos ofrecidos por el
       * m�todo leerSemilla(size_t numBytes) 
       */
      Z leerSemillaSegura(size_t numBytes);
      
      /** Leer semilla pseudo-aleatoria.
       *
       * @param numBytes N�mero de bytes a obtener.
       * @return Un entero conteniendo los @e numBytes bytes de datos pseudo-aleatorios
       *
       * Lee un n�mero determinados de bytes aleatorios obtenidos tras
       * aplicar funciones de mezcla fuerte (ver RFC1750 pto. 6.1.2) (en concreto, una funci�n
       * resumen) a datos aleatorios inicialmente reales.
       * En la llamada siguiente a la generacion de un n�mero mayor o
       * igual que UMBRAL_SEMILLA bytes, se vuelve a alimentar a la
       * funcion mezcla con datos aleatorios reales. 
       *
       * @warning En principio, las llamadas a los m�todos de esta 
       * clase podr�an bloquearse si no hay suficiente entrop�a disponible tras la 
       * generacion de UMBRAL_SEMILLA bytes. Esto deber�a suceder rara
       * vez.
       */
      Z leerSemilla(size_t numBytes);

#if 0
      /** Establecer fuente de entrop�a.
       *
       * @param fuente Puntero a flujo de entrada de entrop�a.
       *
       * @exception Errores::FuenteEntropiaInvalida Si el flujo
       * suministrado no es v�lido.
       *
       * Establece de donde conseguir la entrop�a para el Semillero.
       */
      void ponerFuente(std::ifstream* fuente);
#endif
    private:
      MiVec<uint8_t> fuente_(size_t numBytes);
      MiVec<uint8_t> datosRnd_;
  };

}

#endif
