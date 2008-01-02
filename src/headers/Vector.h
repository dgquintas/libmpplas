/* 
 * $Id$
 */


#ifndef __VECTOR_H
#define __VECTOR_H

#include <algorithm>
#include <sstream>


#include "Errors.h"
#include "Dimensions.h"
#include "Matrix.h"
#include "Constants.h"
#include "R.h"

namespace mpplas 
{
  template<typename T, typename Alloc = std::allocator<T> >
    class Vector : public Matrix<T, Alloc>
  {
    public:
      Vector();
      Vector(const int size);
      Vector(const int size, const T& ini);
      Vector(const Vector<T, Alloc>& rhs); /**< Copy constructor */
      Vector(const std::vector<T, Alloc>& rhs); /**< Constructor from a std::vector */
      Vector(const std::string &); /**< Parsing contructor from a textual representation */

      Vector<T, Alloc>& operator=(const Vector<T, Alloc>& rhs);



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
      Vector<T, Alloc>& transpose();
      Vector<T, Alloc>& cross(const Vector<T, Alloc>&);
      T dot(const Vector<T, Alloc>& rhs);
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
      template<typename U, typename V> friend std::istream& operator>>(std::istream& in, 
          Vector<U, V>& v) ;


  };


  /** Non-modifying tranposition.
   *
   * @sa Vector<T>::transpose()
   * @param src The vector to transpose.
   *
   * @return The transposed version of @a src.
   */
  template<typename T, typename Alloc> Vector<T, Alloc> transpose( Vector<T, Alloc> src ); 
//  template<typename T> Vector<T, Alloc> normalize( Vector<T, Alloc> src );
  template<typename T, typename Alloc> R norm( Vector<T, Alloc> src, const int p = 2 );
  template<typename T, typename Alloc> T dot( Vector<T, Alloc> lhs, const Vector<T, Alloc>& rhs);
  template<typename T, typename Alloc> Vector<T, Alloc> cross( Vector<T, Alloc> lhs, const Vector<T, Alloc>& rhs);

#include "VectorImpl.h"
}

#endif
