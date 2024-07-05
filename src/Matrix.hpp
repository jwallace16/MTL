///////////////////////////////////////////////////////////////////////////////
//!
//! @file Matrix.hpp
//!
//! Template matrix header
//!
//! @author David Wallace <jdavidwallace1@gmail.com>
///////////////////////////////////////////////////////////////////////////////
#ifndef _MATRIX_HPP__
#define _MATRIX_HPP__

#include <cmath>
#include <cstdio>
#include <cstring>
#include <stdexcept>


namespace matrix
{

template<typename T, size_t M, size_t N>
class Matrix
{
public:
    //! Default constructor
    Matrix();

    //! Destructor
    virtual ~Matrix() = default;

    //! Constructor initializing with 2-d array of data
    explicit Matrix(const T values[M][N]);

    //! Constructor initializing with flat array of data
    explicit Matrix(const T values[M*N]);

    //! Construct using initializer list
    Matrix(std::initializer_list<std::initializer_list<T>> list);

    //! Copy constructor
    Matrix(const Matrix &other) = default;

    //! Move constructor
    Matrix(Matrix&& other) = default;

    //! Copy assignment
    Matrix& operator=(const Matrix &other) = default;

    //! Move assignment
    Matrix& operator=(Matrix&& other) = default;

    //! Element access operator
    const T &operator()(size_t i, size_t j) const;

    //! Element assignment operator
    T &operator()(size_t i, size_t j);

    //! Resize method (create new matrix)
    // template<size_t P, size_t Q>
    // Matrix<T, P, Q> resize();

    //! Add two matrices
    Matrix<T, M, N> operator+(const Matrix<T, M, N> &other) const;

    //! Element-wise matrix subtraction
    Matrix<T, M, N> operator-(const Matrix<T, M, N> &other) const;

    //! Matrix multiply
    template<size_t P>
    Matrix<T, M, P> operator*(const Matrix<T, N, P> &other) const;

    //! Compound addition operator
    void operator+=(const Matrix<T, M, N> &other);

    //! Compound subtraction operator
    void operator-=(const Matrix<T, M, N> &other);

    //! Compound matrix multiplication
    template<size_t P>
    void operator*=(const Matrix<T, N, P> &other);

    //! Unary minus operator
    Matrix<T, M, N> operator-() const;

    //! Element-wise scalar addition
    Matrix<T, M, N> operator+(T value) const;

    //! Matrix-scalar subtraction
    Matrix<T, M, N> operator-(T value) const;

    //! Scalar multiplication
    Matrix<T, M, N> operator*(T value) const;

    //! Matrix element-wise scalar division
    Matrix<T, M, N> operator/(T value) const;

    //! Compound scalar addition
    void operator+=(T value);

    //! Compound matrix-scalar subtraction
    void operator-=(T value);

    //! Compound rhs scalar multiplication
    void operator*=(T value);

    //! Compound matrix element-wise scalar division
    void operator/=(T value);

    //! Test equality
    bool operator==(const Matrix<T, M, N> &other) const;

    //! Test non-equality
    bool operator!=(const Matrix<T, M, N> &other) const;

    //! Matrix transpose
    Matrix<T, N, M> transpose() const;

    //! Swap rows
    void swapRows(size_t rowA, size_t rowB);

    //! Swap columns
    void swapCols(size_t colA, size_t colB);

    //! Set all elements to value
    void setValue(T value);

    //! Return absolute value of matrix elements
    Matrix<T, M, N> abs() const;

    //! Return submatrix of parent
    template<size_t P, size_t Q>
    Matrix<T, P, Q> submatrix(size_t rowA, size_t colA, size_t rowB, size_t colB) const;

protected:
    T data[M*N];

private:
}; // class Matrix

//! Default constructor
template<class T, size_t M, size_t N>
Matrix<T,M,N>::Matrix()
{
    for(size_t i = 0; i < M*N; ++i)
    {
        data[i] = (T)0;
    }
}

//! Constructor initializing with 2-d array of data
template<class T, size_t M, size_t N>
Matrix<T,M,N>::Matrix(const T values[M][N])
{
    for(size_t i = 0; i < M; ++i)
    {
        for(size_t j = 0; j < N; ++j)
        {
            data[i*N+j] = values[i][j];
        }
    }
}

//! Constructor initializing with flat array of data
template<class T, size_t M, size_t N>
Matrix<T,M,N>::Matrix(const T values[M*N])
{
    for(size_t i = 0; i < M*N; ++i)
    {
        data[i] = values[i];
    }
}

//! Construct using initializer list
template<class T, size_t M, size_t N>
Matrix<T,M,N>::Matrix(std::initializer_list<std::initializer_list<T>> list)
{
    size_t listcols = static_cast<size_t>(list.begin()->size());
    size_t listrows = static_cast<size_t>(list.size());
    if(listrows != M || listcols != N)
    {
        char message[120];
        snprintf(message, 120, "ERROR: Invalid number of arguments supplied. Expected [%lu, %lu], Received [%lu, %lu]\n", M, N, listrows, listcols);
        throw std::invalid_argument(message);
    }

    auto outeriter = list.begin();
    for(size_t i = 0; i < listrows; ++i)
    {
        auto inneriter = (outeriter+i)->begin();
        for(size_t j = 0; j < listcols; ++j)
        {
            // Keep for posterity
            // data[i*N+j] = ((list.begin()+i)->begin())[j];
            // data[i*N+j] = ((iter+i)->begin())[j];
            data[i*N+j] = inneriter[j];
        }
    }
}

//! Element access operator
template<class T, size_t M, size_t N>
const T &Matrix<T,M,N>::operator()(size_t i, size_t j) const
{
    if(i >= M || j >= N)
    {
        char message[110];
        snprintf(message, 110, 
            "ERROR: Matrix index access out of range. Size [%ld, %ld], Received [%ld, %ld]\n", M, N, i, j);
        throw std::domain_error(message);
    }
    return data[i*N+j];
}

//! Element assignment operator
template<class T, size_t M, size_t N>
T &Matrix<T,M,N>::operator()(size_t i, size_t j)
{
    if(i >= M || j >= N)
    {
        char message[110];
        snprintf(message, 110, 
            "ERROR: Matrix index access out of range. Size [%ld, %ld], Received [%ld, %ld]\n", M, N, i, j);
        throw std::domain_error(message);
    }
    return data[i*N+j];
}

//! Add two matrices
template<class T, size_t M, size_t N>
Matrix<T,M,N> Matrix<T,M,N>::operator+(const Matrix<T, M, N> &other) const
{
    Matrix<T, M, N> result;
    for(size_t i = 0; i < M*N; ++i)
    {
        result.data[i] = data[i] + other.data[i];
    }
    return result;
}

//! Subtract other from this
template<class T, size_t M, size_t N>
Matrix<T,M,N> Matrix<T,M,N>::operator-(const Matrix<T, M, N> &other) const
{
    Matrix<T, M, N> result;
    for(size_t i = 0; i < M*N; ++i)
    {
        result.data[i] = data[i] - other.data[i];
    }
    return result;
}

//! Matrix multiplication
template<class T, size_t M, size_t N>
template<size_t P>
Matrix<T,M,P> Matrix<T,M,N>::operator*(const Matrix<T, N, P> &other) const
{
    const Matrix<T, M, N> &self = *this;
    Matrix<T, M, P> result;
    for(size_t i = 0; i < M; ++i)
    {
        for(size_t j = 0; j < P; ++j)
        {
            for(size_t k = 0; k < N; ++k)
            {
                result(i,j) += self(i,k) * other(k,j);
            }
        }
    }
    return result;
}

//! Compound addition operator
template<class T, size_t M, size_t  N>
void Matrix<T,M,N>::operator+=(const Matrix<T, M, N> &other)
{
    for(size_t i = 0; i < M*N; ++i)
    {
        data[i] += other.data[i];
    }
}

//! Compound subtraction operator
template<class T, size_t M, size_t N>
void Matrix<T,M,N>::operator-=(const Matrix<T, M, N> &other)
{
    for(size_t i = 0; i < M*N; ++i)
    {
        data[i] -= other.data[i];
    }
}

//! Compound matrix multiplication
template<class T, size_t M, size_t N>
template<size_t P>
void Matrix<T,M,N>::operator*=(const Matrix<T, N, P> &other)
{
    (*this) = (*this) * other;
}

//! Unary minus operator
template<class T, size_t M, size_t N>
Matrix<T,M,N> Matrix<T,M,N>::operator-() const
{
    Matrix<T, M, N> result;
    for(size_t i = 0; i < M*N; ++i)
    {
        result.data[i] = -data[i];
    }
    return result;
}

//! Element-wise scalar addition
template<class T, size_t M, size_t N>
Matrix<T, M, N> Matrix<T,M,N>::operator+(T value) const
{
    Matrix<T, M, N> result;
    for(size_t i = 0; i < M*N; ++i)
    {
        result.data[i] = data[i] + value;
    }
    return result;
}

//! Matrix-scalar subtraction
template<class T, size_t M, size_t N>
Matrix<T, M, N> Matrix<T,M,N>::operator-(T value) const
{
    Matrix<T, M, N> result;
    for(size_t i = 0; i < M*N; ++i)
    {
        result.data[i] = data[i] - value;
    }
    return result;
}

//! Scalar multiplication
template<class T, size_t M, size_t N>
Matrix<T, M, N> Matrix<T,M,N>::operator*(T value) const
{
    // const Matrix<T, M, N> &self = *this;
    Matrix<T, M, N> result;
    for(size_t i = 0; i < M*N; ++i)
    {
        result.data[i] = data[i] * value;
    }
    return result;
}

//! Matrix element-wise scalar division
template<class T, size_t M, size_t N>
Matrix<T, M, N> Matrix<T,M,N>::operator/(T value) const
{
    Matrix<T, M, N> result;
    for(size_t i = 0; i < M*N; ++i)
    {
        result.data[i] = (T)(data[i] / value);
    }
    return result;
}

//! Compound scalar addition
template<class T, size_t M, size_t N>
void Matrix<T,M,N>::operator+=(T value)
{
    for(size_t i = 0; i < M*N; ++i)
    {
        data[i] += value;
    }
}

//! Compound matrix-scalar subtraction
template<class T, size_t M, size_t N>
void Matrix<T,M,N>::operator-=(T value)
{
    for(size_t i = 0; i < M*N; ++i)
    {
        data[i] -= value;
    }
}

//! Compound rhs scalar multiplication
template<class T, size_t M, size_t N>
void Matrix<T,M,N>::operator*=(T value)
{
    for(size_t i = 0; i < M*N; ++i)
    {
        data[i] *= value;
    }
}

//! Compound matrix element-wise scalar division
template<class T, size_t M, size_t N>
void Matrix<T,M,N>::operator/=(T value)
{
    for(size_t i = 0; i < M*N; ++i)
    {
        data[i] = (T)(data[i] / value);
    }
}

//! Test equality
template<class T, size_t M, size_t N>
bool Matrix<T,M,N>::operator==(const Matrix<T, M, N> &other) const
{
    for(size_t i = 0; i < M*N; ++i)
    {
        if(data[i] != other.data[i])
        {
            return false;
        }
    }
    return true;
}

//! Test non-equality
template<class T, size_t M, size_t N>
bool Matrix<T,M,N>::operator!=(const Matrix<T, M, N> &other) const
{
    return !(*this == other);
}

//! Matrix transpose
template<class T, size_t M, size_t N>
Matrix<T, N, M> Matrix<T,M,N>::transpose() const
{
    Matrix<T, N, M> result;
    const Matrix<T, M, N> &self = *this;
    for(size_t i = 0; i < M; ++i)
    {
        for(size_t j = 0; j < N; ++j)
        {
            result(j,i) = self(i,j);
        }
    }
    return result;
}

//! Swap rows
template<class T, size_t M, size_t N>
void Matrix<T,M,N>::swapRows(size_t rowA, size_t rowB)
{
    if(rowA >= M || rowB >= M)
    {
        char message[110];
        snprintf(message, 110,
            "ERROR: Matrix row index access out of range. Max row index [%ld], Received [%ld, %ld]\n", M, rowA, rowB);
        throw std::domain_error(message);
    }

    Matrix<T, M, N> &self = *this;
    for(size_t i = 0; i < N; ++i)
    {
        T temp = self(rowA, i);
        self(rowA, i) = self(rowB, i);
        self(rowB, i) = temp;
    }
}

//! Swap columns
template<class T, size_t M, size_t N>
void Matrix<T,M,N>::swapCols(size_t colA, size_t colB)
{
    if(colA >= N || colB >= N)
    {
        char message[110];
        snprintf(message, 110,
            "ERROR: Matrix column index access out of range. Max column index [%ld], Received [%ld, %ld]\n", N, colA, colB);
            throw std::domain_error(message);
    }

    Matrix<T, M, N> &self = *this;
    for(size_t i = 0; i < M; ++i)
    {
        T temp = self(i, colA);
        self(i, colA) = self(i, colB);
        self(i, colB) = temp;
    }
}

//! Set all elements to value
template<class T, size_t M, size_t N>
void Matrix<T,M,N>::setValue(T value)
{
    Matrix<T, M, N> &self = *this;
    for(size_t i = 0; i < M; ++i)
    {
        for(size_t j = 0; j < N; ++j)
        {
            self(i,j) = value;
        }
    }
}

//! Return absolute value of matrix elements
template<class T, size_t M, size_t N>
Matrix<T, M, N> Matrix<T,M,N>::abs() const
{
    const Matrix<T, M, N> &self = *this;
    Matrix<T, M, N> result;
    for(size_t i = 0; i < M*N; ++i)
    {
        result.data[i] = (T)std::fabs(data[i]);
    }
    return result;
}

//! Return submatrix of parent
template<class T, size_t M, size_t N>
template<size_t P, size_t Q>
Matrix<T, P, Q> Matrix<T,M,N>::submatrix(size_t rowA, size_t colA, size_t rowB, size_t colB) const
{
    if(P >= M || Q >= N)
    {
        char message[130];
        snprintf(message, 130, 
            "ERROR: Submatrix must be smaller than original matrix. Original [%ld, %ld], Requested [%ld, %ld]\n", M, N, P, Q);
        throw std::domain_error(message);
    }
    if(rowA >= M || rowB >= M || colA >= N, colB >= N)
    {
        char message[130];
        snprintf(message, 130,
            "ERROR: Submatrix indices exceed size of original matrix. Original [%ld, %ld], Requested [%ld, %ld, %ld, %ld]\n", M, N, rowA, rowB, colA, colB);
        throw std::domain_error(message);
    }

    Matrix<T, P, Q> res;
    const Matrix<T, M, N> &self = *this;
    for(size_t i = rowA; i < rowB; ++i)
    {
        for(size_t j = colA; j < colB; ++j)
        {
            res(i-rowA, j-colA) = self(i,j);
        }
    }
    return res;
}

template<class T, size_t M, size_t N>
Matrix<T, M, N> operator*(T value, const Matrix<T, M, N> &other)
{
    return other * value;
}

//! TODO: move this method into non-flight utilities module?
template<class T, size_t M, size_t N>
std::ostream& operator<<(std::ostream &os, const matrix::Matrix<T, M, N> &mat)
{
    for(size_t i = 0; i < M; ++i)
    {
        for(size_t j = 0; j < N; ++j)
        {
            os << mat(i,j) << "\t";
        }
        os << "\n";
    }
    return os;
}

} // namespace matrix

#endif // _MATRIX_HPP__