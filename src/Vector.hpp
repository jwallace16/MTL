///////////////////////////////////////////////////////////////////////////////
//!
//! @file Vector.hpp
//!
//! Template vector header
//!
//! @author David Wallace <jdavidwallace1@gmail.com>
///////////////////////////////////////////////////////////////////////////////
#ifndef _VECTOR_HPP__
#define _VECTOR_HPP__

#include "Matrix.hpp"

#include <initializer_list>

namespace matrix
{

template<class T, size_t M>
class Vector : public Matrix<T, M, 1>
{
public:
    //! Default constructor
    Vector();

    //! Constructor with array of initial values
    explicit Vector(const T values[M]);

    //! Constructor with initializer list
    Vector(std::initializer_list<T> list);

    //! Construct with other vector/matrix
    Vector(const Vector<T, M> &other);

    //! Construct with matrix
    Vector(const Matrix<T, M, 1> &other);

    //! Access vector elements
    const T &operator()(size_t i) const;

    //! Assign vector elements
    T &operator()(size_t i);

    //! Get size of vector
    inline const size_t size(){ return M; }

    //! Dot product of this vector with b
    T dot(const Vector<T, M> &b) const;

    //! Dot product with operator*
    T operator*(const Vector<T, M> &b);

    //! Multiply with scalar
    Vector<T, M> operator*(T value) const;

    //! Compute the norm of a vector
    T norm() const;

    //! Normalize this vector
    void normalize();

    //! Get the length of the vector (same as norm)
    T length() const;

    //! Return unit vector
    Vector<T, M> unit() const;
};

//! Default constructor
template<class T, size_t M>
Vector<T,M>::Vector():
    Matrix<T, M, 1>()
{
}

//! Constructor with array of initial values
template<class T, size_t M>
Vector<T,M>::Vector(const T values[M]):
    Matrix<T, M, 1>(values)
{
}

//! Constructor with initializer list
template<class T, size_t M>
Vector<T,M>::Vector(std::initializer_list<T> list)
{
    size_t listsize = static_cast<size_t>(list.size());
    if(listsize != M)
    {
        char message[120];
        snprintf(message, 120, "ERROR: Invalid number of arguments supplied. Expected [%lu], Received [%lu]\n", M, listsize);
        throw std::invalid_argument(message);
    }

    auto iter = list.begin();
    for(size_t i = 0; i < listsize; ++i)
    {
        this->data[i] = iter[i];
    }
}

//! Construct with other vector/matrix
template<class T, size_t M>
Vector<T,M>::Vector(const Vector<T, M> &other):
    Matrix<T, M, 1>(other)
{
}

//! Construct with matrix
template<class T, size_t M>
Vector<T,M>::Vector(const Matrix<T, M, 1> &other):
    Matrix<T, M, 1>(other)
{
}

//! Access vector elements
template<class T, size_t M>
const T &Vector<T,M>::operator()(size_t i) const
{
    const Matrix<T, M, 1> &self = *this;
    return self(i, 0);
}

//! Assign vector elements
template<class T, size_t M>
T &Vector<T,M>::operator()(size_t i)
{
    Matrix<T, M, 1> &self = *this;
    return self(i, 0);
}

//! Dot product of this vector with b
template<class T, size_t M>
T Vector<T,M>::dot(const Vector<T, M> &b) const
{
    const Vector<T, M> &a = *this;
    T value = 0;
    for(size_t i = 0; i < M; ++i)
    {
        value += a(i) * b(i);
    }
    return value;
}

//! Dot product with operator*
template<class T, size_t M>
T Vector<T,M>::operator*(const Vector<T, M> &b)
{
    const Vector<T, M> &self = *this;
    return self.dot(b);
}

//! Multiply with scalar
template<class T, size_t M>
Vector<T, M> Vector<T,M>::operator*(T value) const
{
    return Vector(Matrix<T, M, 1>::operator*(value));
}

//! Compute the norm of a vector
template<class T, size_t M>
T Vector<T,M>::norm() const
{
    const Vector<T, M> &self = *this;
    return T(std::sqrt(self.dot(self)));
}

//! Normalize this vector
template<class T, size_t M>
void Vector<T,M>::normalize()
{
    Vector<T,M> &self = *this;
    self /= norm();
}

//! Get the length of the vector (same as norm)
template<class T, size_t M>
T Vector<T,M>::length() const
{
    return norm();
}

//! Return unit vector
template<class T, size_t M>
Vector<T, M> Vector<T,M>::unit() const
{
    const Vector<T, M> &self = *this;
    return self / norm();
}

//! TODO: move this to a non-flight module?
//! Operator for printing to ostream
template<class OStream, class T, size_t M>
OStream &operator<<(OStream &os, const matrix::Vector<T,M> &vec)
{
    for(size_t i = 0; i < M; ++i)
    {
        os << vec(i) << ",\t";
    }
    os << "\n";
    return os;
}

} // namespace matrix

#endif // _VECTOR_HPP__