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

#include "Errors.h"
#include "AlgebraUtils.h"
#include "Constants.h"
#include "MiVec.h"

namespace mpplas {

  template<typename T, typename Alloc = std::allocator<T> >
    class Matrix
    {
      public:
        Matrix();
        Matrix(const int nAndm) ;
        Matrix(const int n, const int m);
        Matrix(const Dimensions& dims);
        Matrix(const Matrix<T, Alloc>& rhs);
        Matrix(const std::string& str);
        Matrix(const std::vector<T, Alloc>& rhs, const Dimensions& dims);

        Matrix<T, Alloc>& operator=(const Matrix<T, Alloc>& rhs);

        inline T& operator[](int i);
        inline const T& operator[](int i) const;

        inline T& operator()(int i);
        inline const T& operator()(int i) const;
        inline T& operator()(int i, int j);
        inline const T& operator()(int i, int j) const;
  
        Matrix<T, Alloc> operator()(int n1, int n2, 
                                    int m1, int m2) const;


        
        bool operator==(const Matrix<T, Alloc>& rhs) const;

        Matrix<T, Alloc>& operator+=(const Matrix<T, Alloc>&);
        Matrix<T, Alloc>& operator+=(const T&);
        Matrix<T, Alloc>& operator+=(const Digit);
        Matrix<T, Alloc>& operator+=(const SignedDigit);


        Matrix<T, Alloc>& operator-=(const Matrix<T, Alloc>&);
        Matrix<T, Alloc>& operator-=(const T&);
        Matrix<T, Alloc>& operator-=(const Digit);
        Matrix<T, Alloc>& operator-=(const SignedDigit);


        Matrix<T, Alloc>& operator*=(const Matrix<T, Alloc>& rhs);
        Matrix<T, Alloc>& operator*=(const T& rhs); 
        Matrix<T, Alloc>& operator*=(const Digit rhs);
        Matrix<T, Alloc>& operator*=(const SignedDigit rhs);
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
        Matrix<T, Alloc>& byElementProd( const Matrix<T, Alloc>& rhs);


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
        Matrix<T, Alloc>& operator/=(const Matrix<T, Alloc>& rhs);
        Matrix<T, Alloc>& operator/=(const T&);
        Matrix<T, Alloc>& operator/=(const Digit);
        Matrix<T, Alloc>& operator/=(const SignedDigit);
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
        Matrix<T, Alloc>& byElementDiv( const Matrix<T, Alloc>& rhs);


        Matrix<T, Alloc>& operator^=(const T&);
        Matrix<T, Alloc>& operator^=(const Digit);
        Matrix<T, Alloc>& operator^=(const SignedDigit );


        Matrix<T, Alloc>& transpose();
        Matrix<T, Alloc>& diagonalize();
        Matrix<T, Alloc>& invert();
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
        inline int getSize() const;
        inline const Dimensions& getDimensions() const;
        void setDimensions(const Dimensions& dims);
        inline int getRows() const;
        inline int getColumns() const;
        inline bool isSquare() const;

        std::string toString() const;



      protected:
        Dimensions _dims;
        mpplas::MiVec<T, Alloc> _data; /**< Row-major vector representation of the matrix */


        void _reset();


        /** Matrix ouput operator */
        template<typename U, typename V> 
          friend std::ostream& operator<<(std::ostream&, 
            const Matrix<U, V>& );
        /** Matrix input operator */
        template<typename U, typename V>
          friend std::istream& operator>>(std::istream&, 
              Matrix<U, V>& ) ;
        template<typename U, typename V, typename Composed_t>
          friend void _parseMatrixInput(std::istream& in, Matrix<U, V>& m); 

    };

  template<typename T, typename Alloc>
    Matrix<T, Alloc> transpose(const Matrix<T, Alloc>& matrix);

  template<typename T, typename Alloc>
    Matrix<T, Alloc> operator-(Matrix<T, Alloc> m); /**< Unary negation, sign inversion */

  template<typename T, typename Alloc>
    Matrix<T, Alloc> operator+(Matrix<T, Alloc> lhs, const Matrix<T, Alloc>& rhs){
      lhs += rhs;
      return lhs;
    }

  template<typename T, typename Alloc>
    Matrix<T, Alloc> operator*(const Matrix<T, Alloc>& lhs, const Matrix<T, Alloc>& rhs);

  namespace MatrixHelpers{

    template<typename T>
    class Strassen{
      public:
        void run(T* C, const T* const A, const T* const B, 
            const int numRowsA, const int numColsA, const int numColsB,
            const int strideC, const int strideA, const int strideB) const;

        virtual void baseMult(T* C, const T* const A, const T* const B,
        const int numRowsA, const int numColsA, const int numColsB,
        const int strideC, const int strideA, const int strideB) const;

        
      private:
        virtual void _addBlocks(T* res, const T* const A, const T* const B, 
            const int rows, const int cols,
            const int strideRes, const int strideA, const int strideB) const;

        virtual void _subBlocks(T* res,const T* const A, const T* const B,
            const int rows, const int cols,
            const int strideRes, const int strideA, const int strideB) const;

        virtual void _multBlocks(T* res,const T* const A, const T* const B,
            const int numRowsA, const int numColsA, const int numColsB,
            const int strideRes, const int strideA, const int strideB) const;


        
        void _generateQs(T* Q, const T* const A, const T* const B, 
            const int halfRowsA, const int halfColsA, const int halfColsB,
            const int strideA, const int strideB) const;

    };
    
  } /* namespace MatrixHelpers */
    
    #include "MatrixImpl.h"

}

#endif
