/* 
 * $Id$
 */


#ifndef __VECTOR_H
#define __VECTOR_H

#include <algorithm>
#include <sstream>


#include "Errors.h"
#include "AlgebraUtils.h"
#include "Matrix.h"
#include "Constants.h"
#include "R.h"

namespace mpplas 
{
  template<typename T>
    class Vector : public Matrix<T>
  {
    public:
      Vector();
      Vector(const int size);
      Vector(const int size, const T& ini);
      Vector(const Vector<T>& rhs); /**< Copy constructor */
      Vector(const std::vector<T>& rhs); /**< Constructor from a std::vector */
      Vector(const std::string &); /**< Parsing contructor from a textual representation */

      Vector<T>& operator=(const Vector<T>& rhs);



      /** Vector specific transposition.
       *
       * Converts a row-vector into a column-vector and viceversa.
       *
       * It is advantageous over the general matrix transposition 
       * because only a swap of the dimension values is needed.
       *
       *   @par Complexity
       *   \f$O(1)\f$
       *
       *   @return The tranposed vector.
       */
      Vector<T>& transpose();
      Vector<T>& cross(const Vector<T>&);
      T dot(const Vector<T>& rhs);
//      Vector<T>& normalize();
      R norm(const int p = 2);


      /** Input operator for Vector 
       *
       * The reason not to use Matrix<T> input operator is because 
       * the textual representation of a vector is a subset of the former.
       * For instance, ';' characters should not be allowed, whereas for 
       * matrices it is.
       * 
       * @param in An input stream
       * @param v The target Vector
       *
       * @return A reference to the input stream @a in
       *
       */
      template<typename U> friend std::istream& operator>>(std::istream& in, 
          Vector<U>& v) ;


  };


  /** Non-modifying tranposition.
   *
   * @sa Vector<T>::transpose()
   * @param src The vector to transpose.
   *
   * @return The transposed version of @a src.
   */
  template<typename T> Vector<T> transpose( Vector<T> src ); 
//  template<typename T> Vector<T> normalize( Vector<T> src );
  template<typename T> R norm( Vector<T> src, const int p = 2 );
  template<typename T> T dot( Vector<T> lhs, const Vector<T>& rhs);
  template<typename T> Vector<T> cross( Vector<T> lhs, const Vector<T>& rhs);

#include "VectorImpl.h"
}

#endif
