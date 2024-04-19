///////////////////////////////////////////////////////////////////////////////
//!
//! @file SquareMatrix.hpp
//!
//! Template matrix header specialization for square matrices
//!
//! @author David Wallace <jdavidwallace1@gmail.com>
///////////////////////////////////////////////////////////////////////////////
#ifndef _SQUAREMATRIX_HPP__
#define _SQUAREMATRIX_HPP__

#include "Matrix.hpp"

namespace matrix
{

// template<class T, size_t M, size_t N>
// class Matrix;

// template<class T, size_t M>
// class Vector;

template<class T, size_t M>
class SquareMatrix : public Matrix<T, M, M>
{
public:
    //! Default constructor
    SquareMatrix();

    //! Construct with 2d array
    explicit SquareMatrix(const T values[M][M]);

    //! Construct with a flat array
    explicit SquareMatrix(const T values[M*M]);

    //! Construct with Matrix type
    SquareMatrix(const Matrix<T, M, M> &other);

    //! Assignment operator of Base Type
    SquareMatrix<T, M> &operator=(const Matrix<T, M, M> &other);

    //! Make this matrix an identity matrix
    void identity();

    //! Obtain the trace of the matrix
    T trace() const;
};

//! Default constructor
template<class T, size_t M>
SquareMatrix<T,M>::SquareMatrix():
    Matrix<T, M, M>()
{
}

//! Construct with 2d array
template<class T, size_t M>
SquareMatrix<T,M>::SquareMatrix(const T values[M][M]):
    Matrix<T, M, M>(values)
{
}

//! Construct with a flat array
template<class T, size_t M>
SquareMatrix<T,M>::SquareMatrix(const T values[M*M]):
    Matrix<T, M, M>(values)
{
}

//! Construct with Matrix type
template<class T, size_t M>
SquareMatrix<T,M>::SquareMatrix(const Matrix<T, M, M> &other):
    Matrix<T, M, M>(other)
{
}

//! Assignment operator from base type
template<class T, size_t M>
SquareMatrix<T, M> &SquareMatrix<T,M>::operator=(const Matrix<T, M, M> &other)
{
    Matrix<T, M, M>::operator=(other);
    return *this;
}

//! Make this matrix an identity matrix
template<class T, size_t M>
void SquareMatrix<T,M>::identity()
{
    SquareMatrix<T, M> &self = *this;
    for(size_t i = 0; i < M*M; ++i)
    {
        this->data[i] = (T)0;
    }
    for(size_t i = 0; i < M; ++i)
    {
        this->data[i*(M+1)] = (T)1;
    }
}

//! Return an identity matrix
template<class T, size_t M>
SquareMatrix<T, M> identity()
{
    SquareMatrix<T, M> result;
    result.identity();
    return result;
}

//! Obtain the trace of the matrix
template<class T, size_t M>
T SquareMatrix<T, M>::trace() const
{
    T tr = 0;
    for(size_t i = 0; i < M; ++i)
    {
        tr += this->data[i*M+i];
    }
    return tr;
}

//! Return the determinant of a 2x2 matrix
template<class T>
T determinant(const SquareMatrix<T, 2> &A)
{
    return (A(0,0)*A(1,1) - A(0,1)*A(1,0));
}

//! Return the determinant of a 3x3 matrix
template<class T>
T determinant(const SquareMatrix<T, 3> &A)
{
    return ((A(0,0)*(A(1,1)*A(2,2) - A(1,2)*A(2,1)))
           -(A(0,1)*(A(1,0)*A(2,2) - A(1,2)*A(2,0)))
           +(A(0,2)*(A(1,0)*A(2,1) - A(1,1)*A(2,0))));
}

//! Compute the inverse of a 2x2 matrix
template<class T>
SquareMatrix<T, 2> inverse(const SquareMatrix<T, 2> &A)
{
    T det = determinant<T>(A);
    if(std::fabs(det) < 1.0e-9)
    {
        char message[100];
        snprintf(message, 100, "ERROR: Determinant is < 1.0e-9. Matrix is not invertible. Det = %f\n", (double)det);
        throw std::runtime_error(message);
    }

    SquareMatrix<T, 2> Ainv;
    Ainv(0,0) = A(1,1);
    Ainv(0,1) = -A(0,1);
    Ainv(1,0) = -A(1,0);
    Ainv(1,1) = A(0,0);
    Ainv /= det;
    return Ainv;
}

//! Compute the inverse of a 3x3 matrix
template<class T>
SquareMatrix<T, 3> inverse(const SquareMatrix<T, 3> &A)
{
    T det = determinant<T>(A);
    if(std::fabs(det) < 1.0e-9)
    {
        char message[100];
        snprintf(message, 100, "ERROR: Determinant is < 1.0e-9. Matrix is not invertible. Det = %f\n", (double)det);
        throw std::runtime_error(message);
    }
    SquareMatrix<T, 3> Ainv;
    T detinv = 1.0 / det;
    Ainv(0,0) = detinv*(A(1,1)*A(2,2) - A(1,2)*A(2,1));
    Ainv(0,1) = detinv*(A(0,2)*A(2,1) - A(0,1)*A(2,2));
    Ainv(0,2) = detinv*(A(0,1)*A(1,2) - A(0,2)*A(1,1));
    Ainv(1,0) = detinv*(A(1,2)*A(2,0) - A(1,0)*A(2,2));
    Ainv(1,1) = detinv*(A(0,0)*A(2,2) - A(0,2)*A(2,0));
    Ainv(1,2) = detinv*(A(0,2)*A(1,0) - A(0,0)*A(1,2));
    Ainv(2,0) = detinv*(A(1,0)*A(2,1) - A(1,1)*A(2,0));
    Ainv(2,1) = detinv*(A(0,1)*A(2,0) - A(0,0)*A(2,1));
    Ainv(2,2) = detinv*(A(0,0)*A(1,1) - A(0,1)*A(1,0));
    return Ainv;
}

} // namespace matrix

#endif // _SQUAREMATRIX_HPP__