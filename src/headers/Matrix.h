/* 
 * $Id$
 */

#ifndef __MATRIX_H
#define __MATRIX_H

#include <string>
#include <iterator>
#include <cassert>
#include <sstream>
#include <cstring>
#include <iomanip>
#include <vector>
#include <algorithm>

#include "err.h"
#include "AlgebraUtils.h"
#include "constants.h"

namespace mpplas 
{
#ifdef RELEASE
#define _SAFE_GET(i) operator[](i)
#else
#define _SAFE_GET(i) at(i)
#endif


  template<typename T>
    class Matrix
    {
      public:
        Matrix();
        Matrix(const size_t nAndm) ;
        Matrix(const size_t n, const size_t m);
        Matrix(const Dimensions& dims);
        Matrix(const Matrix<T>& rhs);
        Matrix(const std::string& str);
        Matrix(const std::vector<T>& rhs, const Dimensions& dims);

        Matrix<T>& operator=(const Matrix<T>& rhs);

        inline T& operator[](size_t i);
        inline const T& operator[](size_t i) const;

        inline T& operator()(size_t i);
        inline const T& operator()(size_t i) const;
        inline T& operator()(size_t i, size_t j);
        inline const T& operator()(size_t i, size_t j) const;
  
        Matrix<T>& operator()(size_t n1, size_t m1, 
                              size_t n2, size_t m2);
        const Matrix<T>& operator()(size_t n1, size_t m1, 
                                    size_t n2, size_t m2) const;


        
        bool operator==(const Matrix<T>& rhs) const;

        Matrix<T>& operator+=(const Matrix<T>&);
        Matrix<T>& operator+=(const T&);
        Matrix<T>& operator+=(const Digit);
        Matrix<T>& operator+=(const SignedDigit);


        Matrix<T>& operator-=(const Matrix<T>&);
        Matrix<T>& operator-=(const T&);
        Matrix<T>& operator-=(const Digit);
        Matrix<T>& operator-=(const SignedDigit);


        Matrix<T>& operator*=(const Matrix<T>& rhs);
        Matrix<T>& operator*=(const T& rhs); 
        Matrix<T>& operator*=(const Digit rhs);
        Matrix<T>& operator*=(const SignedDigit rhs);
        /** Element by element product.
         *
         * Multiply the current matrix by @a rhs element by element. 
         * That is, 
         * \f$ A_{i,j} = A_{i,j} \times B_{i,j}\f$
         * Both matrices should have the same dimensions.
         *
         * @param rhs The right-hand-side factor matrix.
         *
         * @return A reference to *this, the result matrix.
         *
         * @throw Errors::NonConformantDimensions If the matrices have different 
         * dimensions
         */
        Matrix<T>& byElementProd( const Matrix<T>& rhs);


        /** Matrix "division" 
         *
         * Matrix division is defined as the product of the dividend by 
         * the inverse of the divisor, if such an inverse exists.
         * 
         * @param rhs The divisor matrix. Should be non-singular.
         *
         * @return A reference to *this, the result matrix.
         * 
         * @throw Errors::NonInvertibleElement The divisor is not invertible
         */
        Matrix<T>& operator/=(const Matrix<T>& rhs);
        Matrix<T>& operator/=(const T&);
        Matrix<T>& operator/=(const Digit);
        Matrix<T>& operator/=(const SignedDigit);
        /** Element by element division.
         *
         * Divide the current matrix by @a rhs element by element. 
         * That is, 
         * \f$ A_{i,j} = A_{i,j} / B_{i,j}\f$
         * Both matrices should have the same dimensions.
         *
         * @param rhs The divisor matrix.
         *
         * @return A reference to *this, the result matrix.
         *
         * @throw Errors::NonConformantDimensions If the matrices have 
         * different dimensions
         */
        Matrix<T>& byElementDiv( const Matrix<T>& rhs);


        Matrix<T>& operator^=(const T&);
        Matrix<T>& operator^=(const Digit);
        Matrix<T>& operator^=(const SignedDigit );


        Matrix<T>& transpose();
        Matrix<T>& diagonalize();
        Matrix<T>& invert();
        T getDeterminant();
        void setDiagonal(T n);
        void setAll(T n);
        void setToZero();

        /** Number of elements in the matrix.
         *
         * That is, the product of its dimensions.
         *
         * @return The number of elements in the matrix.
         */
        inline size_t getSize() const;
        inline const Dimensions& getDimensions() const;
        void setDimensions(const Dimensions& dims);
        inline const size_t getNumRows() const;
        inline const size_t getNumColumns() const;

        std::string toString() const;

      protected:
        Dimensions _dims;
        std::vector<T> _data; /**< Row-major vector representation of the matrix */

        void _reset();
        /** Matrix ouput operator */
        template<typename U> friend std::ostream& operator<<(std::ostream&, 
            const Matrix<U>& );
        /** Matrix input operator */
        template<typename U> friend std::istream& operator>>(std::istream&, 
            Matrix<U>& ) ;

    };

  template<typename T>
    Matrix<T> operator-(Matrix<T> m); /**< Unary negation, sign inversion */

  template<typename T>
    Matrix<T> operator+(Matrix<T> lhs, const Matrix<T>& rhs){
      lhs += rhs;
      return lhs;
    }

  template<typename T>
    Matrix<T> operator*(Matrix<T> lhs, const Matrix<T>& rhs){
      lhs *= rhs;
      return lhs;
    }

     
    #include "MatrixImpl.h"

}

#endif
