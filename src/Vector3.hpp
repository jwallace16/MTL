///////////////////////////////////////////////////////////////////////////////
//!
//! @file Vector3.hpp
//!
//! Template specialization of vector header for a 3-vector
//!
//! @author David Wallace <jdavidwallace1@gmail.com>
///////////////////////////////////////////////////////////////////////////////
#ifndef _VECTOR3_HPP__
#define _VECTOR3_HPP__

#include "Matrix.hpp"
#include "SquareMatrix.hpp"
#include "Vector.hpp"

namespace matrix
{

template<class T>
class Vector3 : public Vector<T, 3>
{
public:
    //! Default constructor
    Vector3();

    //! Copy constructor from Vector3 type
    Vector3(const Vector3<T> &other);

    //! Copy constructor from Vector type
    Vector3(const Vector<T, 3> &other);

    //! Copy constructor from Matrix type
    Vector3(const Matrix<T, 3, 1> &other);

    //! Create 3-vector from individual elements
    Vector3(T x, T y, T z);

    //! Create 3-vector from an array
    explicit Vector3(const T values[3]);

    // Override basic operations to return correct type and skip unnecessary casting operations
    //! Vector addition
    Vector3<T> operator+(Vector3<T> &other) const;

    //! Vector subtraction
    Vector3<T> operator-(Vector3<T> &other) const;

    //! Vector multiplication (dot product)
    T operator*(const Vector3<T> &other) const;

    //! Scalar addition
    Vector3<T> operator+(T value) const;

    //! Scalar subtraction
    Vector3<T> operator-(T value) const;

    //! Unary minus
    Vector3<T> operator-() const;

    //! Scalar multiplication
    Vector3<T> operator*(T value) const;

    //! Cross product
    Vector3 cross(const Vector3 &other) const;

    //! Tilde matrix (cross prod matrix)
    SquareMatrix<T, 3> tilde() const;
};

//! Default constructor
template<class T>
Vector3<T>::Vector3():
    Vector<T, 3>()
{
}

//! Copy construcctor from Vector3 type
template<class T>
Vector3<T>::Vector3(const Vector3<T> &other):
    Vector<T, 3>(other)
{
}

//! Copy constructor form Vector type
template<class T>
Vector3<T>::Vector3(const Vector<T, 3> &other):
    Vector<T, 3>(other)
{
}

//! Copy constructor from Matrix type
template<class T>
Vector3<T>::Vector3(const Matrix<T, 3, 1> &other):
    Vector<T, 3>(other)
{
}

//! Create a 3-vector from individual elements
template<class T>
Vector3<T>::Vector3(T x, T y, T z)
{
    Vector3<T> &self = *this;
    self(0) = x;
    self(1) = y;
    self(2) = z;
}

//! Create 3-vector from an array
template<class T>
Vector3<T>::Vector3(const T values[3]):
    Vector<T, 3>(values)
{
}

//! Vector addition
template<class T>
Vector3<T> Vector3<T>::operator+(Vector3<T> &other) const
{
    return Vector3<T>(this->data[0]+other.data[0], this->data[1]+other.data[1], this->data[2]+other.data[2]);
}

//! Vector subtraction
template<class T>
Vector3<T> Vector3<T>::operator-(Vector3<T> &other) const
{
    return Vector3<T>(this->data[0]-other.data[0], this->data[1]-other.data[1], this->data[2]-other.data[2]);
}

//! Vector multiplication (dot product)
template<class T>
T Vector3<T>::operator*(const Vector3<T> &other) const
{
    return this->data[0]*other.data[0] + this->data[1]*other.data[1] + this->data[2]*other.data[2];
}

//! Scalar addition
template<class T>
Vector3<T> Vector3<T>::operator+(T value) const
{
    return Vector3<T>(this->data[0]+value, this->data[1]+value, this->data[2]+value);
}

//! Scalar subtraction
template<class T>
Vector3<T> Vector3<T>::operator-(T value) const
{
    return Vector3<T>(this->data[0]-value, this->data[1]-value, this->data[2]-value);
}

//! Unary minus
template<class T>
Vector3<T> Vector3<T>::operator-() const
{
    return Vector3<T>(-(this->data[0]), -(this->data[1]), -(this->data[2]));
}

//! Scalar multiplication
template<class T>
Vector3<T> Vector3<T>::operator*(T value) const
{
    return Vector3<T>(this->data[0]*value, this->data[1]*value, this->data[2]*value);
}

//! Cross product
template<class T>
Vector3<T> Vector3<T>::cross(const Vector3<T> &other) const
{
    const Vector3<T> &self = *this;
    Vector3<T> result(self(1)*other(2)-self(2)*other(1), -(self(0)*other(2)-self(2)*other(0)), self(0)*other(1)-self(1)*other(0));
    return result;
}

//! Tilde matrix (cross prod matrix)
template<class T>
SquareMatrix<T, 3> Vector3<T>::tilde() const
{
    const Vector3<T> &self = *this;
    SquareMatrix<T, 3> ret;
    ret(0,1) = -1.0*this->data[2];
    ret(0,2) = this->data[1];
    ret(1,0) = this->data[2];
    ret(1,2) = -1.0*this->data[0];
    ret(2,0) = -1.0*this->data[1];
    ret(2,1) = this->data[0];
    return ret;
}

} // namespace matrix

#endif // _VECTOR3_HPP__