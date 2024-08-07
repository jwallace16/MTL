///////////////////////////////////////////////////////////////////////////////
//!
//! @file Quaternion.hpp
//!
//! Quaternion notes: initially I was going to use a scalar-last formulation to
//! be consistent with Orbital Mechanics for Engineering Students (Curtis) and
//! Robot and Multibody Dynamics (Jain), but most other references show a 
//! scalar-first representation like, Aircraft Control and Simulation (Stevens,
//! Lewis, Johnson), Modeling and Simulation of Aerospace Vehicle Dynamics 
//! (Zipfel), and others.
//!
//! @author David Wallace <jdavidwallace1@gmail.com>
///////////////////////////////////////////////////////////////////////////////
#ifndef _QUATERNION_HPP__
#define _QUATERNION_HPP__

#include "Matrix.hpp"
#include "Vector.hpp"
#include "Vector3.hpp"
#include "DCM.hpp"
#include "Euler.hpp"
// #include "AxisAngle.hpp"
#include "RotationSequence.hpp"

namespace matrix
{

template<class T>
class DCM;

template<class T>
class Euler;

template<class T>
class Quaternion: public Vector<T, 4>
{
public:
    //-------------------------------------------------------------------------
    // Constructors
    //-------------------------------------------------------------------------
    //! Default constructor
    Quaternion();

    //! Constructor from array of values
    explicit Quaternion(const T values[4]);

    //! Constructor from individual values
    Quaternion(T q0, T q1, T q2, T q3);

    //! Construct from axis and angle
    Quaternion(const Vector3<T> &axis, T angle);

    //! Construct from Euler angles
    Quaternion(const Euler<T> &eulerAngles);

    //! Construct from Direction Cosine Matrix
    Quaternion(const DCM<T> &dcm);

    //! Construct quaternion from Vector<T, 4>
    Quaternion(const Vector<T, 4> &vec);

    //! Construct a quaternion generating the shortest rotation from a to b
    Quaternion(const Vector3<T> &a, const Vector3<T> &b, const T eps = 1.0e-6);

    //-------------------------------------------------------------------------
    // Operators
    //-------------------------------------------------------------------------
    //! Quaternion addition
    Quaternion operator+(const Quaternion<T> &q) const;

    //! Quaternion subtraction
    Quaternion operator-(const Quaternion<T> &q) const;

    //! Quaternion multiplication
    Quaternion operator*(const Quaternion<T> &q) const;

    //! Compound quaternion addition operator
    void operator+=(const Quaternion<T> &other);

    //! Compound quaternion subtraction operator
    void operator-=(const Quaternion<T> &other);

    //! Quaternion compound multiplication operator
    void operator*=(const Quaternion<T> &other);

    //! Add scalar component
    Quaternion operator+(T value) const;

    //! Subtract scalar component
    Quaternion operator-(T value) const;

    //! Quaternion-scalar multiplication
    Quaternion operator*(T value) const;

    //! Compound quaternion-scalar addition
    void operator+=(T value);

    //! Compound quaternion-scalar subtraction
    void operator-=(T value);

    //! Quaternion-scalar compound multiplication operator
    void operator*=(T value);

    //-------------------------------------------------------------------------
    // Class methods
    //-------------------------------------------------------------------------
    //! Compute the norm
    T norm() const;

    //! Compute quaternion conjugate
    Quaternion conjugate() const;

    //! Compute the derivative of a quaternion rotation from system a to system b
    Vector<T, 4> derivA2B(const Vector3<T> &w) const;

    //! Return the inverse of this quaternion
    Quaternion inverse() const;

    //! Invert this quaternion
    void invert();

    //! Get individual elements
    inline const T x() const { return this->data[1]; }
    inline const T y() const { return this->data[2]; }
    inline const T z() const { return this->data[3]; }
    inline const T w() const { return this->data[0]; }

    //! Get the scalar part
    inline const T scalar() const { return this->data[0]; }

    //! Get the vector part
    inline const Vector3<T> vector() const { return Vector3<T>(this->data[1], this->data[2], this->data[3]); }

    //! Return as a matrix
    SquareMatrix<T, 4> asMatrix() const;
};

//! Default constructor
template<class T>
Quaternion<T>::Quaternion()
{
    this->data[0] = static_cast<T>(1);
    this->data[1] = static_cast<T>(0);
    this->data[2] = static_cast<T>(0);
    this->data[3] = static_cast<T>(0);
}

//! Constructor from array of values
template<class T>
Quaternion<T>::Quaternion(const T values[4]):
    Vector<T, 4>(values)
{
}

//! Constructor from individual values
template<class T>
Quaternion<T>::Quaternion(T q0, T q1, T q2, T q3)
{
    this->data[0] = q0;
    this->data[1] = q1;
    this->data[2] = q2;
    this->data[3] = q3;
}

//! Construct from scalar and vector
template<class T>
Quaternion<T>::Quaternion(const Vector3<T> &axis, T angle)
{
    T halfAngle = angle / static_cast<T>(2);
    T sinHalf = std::sin(halfAngle);
    this->data[0] = std::cos(halfAngle);
    this->data[1] = axis(0) * sinHalf;
    this->data[2] = axis(1) * sinHalf;
    this->data[3] = axis(2) * sinHalf;
}

//! Construct from Euler angles
template<class T>
Quaternion<T>::Quaternion(const Euler<T> &euler)
{
    T a1 = 0.5*euler.getAngle1();
    T a2 = 0.5*euler.getAngle2();
    T a3 = 0.5*euler.getAngle3();
    switch(euler.getRotatationSequence())
    {
        case RotationSequence::ZXZ_313:
        {
            T plus = 0.5*(euler.getAngle1() + euler.getAngle3());
            T minus = 0.5*(euler.getAngle1() - euler.getAngle3());
            this->data[0] = std::cos(a2)*std::cos(plus);
            this->data[1] = std::sin(a2)*std::cos(minus);
            this->data[2] = std::sin(a2)*std::sin(minus);
            this->data[3] = std::cos(a2)*std::sin(plus);
        } break;

        case RotationSequence::XYX_121:
        {
            T plus = 0.5*(euler.getAngle1() + euler.getAngle3());
            T minus = 0.5*(euler.getAngle1() - euler.getAngle3());
            this->data[0] = std::cos(a2)*std::cos(plus);
            this->data[1] = std::cos(a2)*std::sin(plus);
            this->data[2] = std::sin(a2)*std::cos(minus);
            this->data[3] = std::sin(a2)*std::sin(minus);
        } break;

        case RotationSequence::YZY_232:
        {
            T plus = 0.5*(euler.getAngle1() + euler.getAngle3());
            T minus = 0.5*(euler.getAngle1() - euler.getAngle3());
            this->data[0] = std::cos(a2)*std::cos(plus);
            this->data[1] = std::sin(a2)*std::sin(minus);
            this->data[2] = std::cos(a2)*std::sin(plus);
            this->data[3] = std::sin(a2)*std::cos(minus);
        } break;

        case RotationSequence::ZYZ_323:
        {
            T plus = 0.5*(euler.getAngle1() + euler.getAngle3());
            T minus = 0.5*(euler.getAngle1() - euler.getAngle3());
            this->data[0] =  std::cos(a2)*std::cos(plus);
            this->data[1] = -std::sin(a2)*std::sin(minus);
            this->data[2] =  std::sin(a2)*std::cos(minus);
            this->data[3] =  std::cos(a2)*std::sin(plus);
        } break;

        case RotationSequence::XZX_131:
        {
            T plus = 0.5*(euler.getAngle1() + euler.getAngle3());
            T minus = 0.5*(euler.getAngle1() - euler.getAngle3());
            this->data[0] =  std::cos(a2)*std::cos(plus);
            this->data[1] =  std::cos(a2)*std::sin(plus);
            this->data[2] = -std::sin(a2)*std::sin(minus);
            this->data[3] =  std::sin(a2)*std::cos(minus);
        } break;

        case RotationSequence::YXY_212:
        {
            T plus = 0.5*(euler.getAngle1() + euler.getAngle3());
            T minus = 0.5*(euler.getAngle1() - euler.getAngle3());
            this->data[0] =  std::cos(a2)*std::cos(plus);
            this->data[1] =  std::sin(a2)*std::cos(minus);
            this->data[2] =  std::cos(a2)*std::sin(plus);
            this->data[3] = -std::sin(a2)*std::sin(minus);
        } break;

        case RotationSequence::XYZ_123:
        {
            this->data[0] = -std::sin(a1)*std::sin(a2)*std::sin(a3) + std::cos(a1)*std::cos(a2)*std::cos(a3);
            this->data[1] =  std::sin(a1)*std::cos(a2)*std::cos(a3) + std::sin(a2)*std::sin(a3)*std::cos(a1);
            this->data[2] = -std::sin(a1)*std::sin(a3)*std::cos(a2) + std::sin(a2)*std::cos(a1)*std::cos(a3);
            this->data[3] =  std::sin(a1)*std::sin(a2)*std::cos(a3) + std::sin(a3)*std::cos(a1)*std::cos(a2);
        } break;

        case RotationSequence::YZX_231:
        {
            this->data[0] = -std::sin(a1)*std::sin(a2)*std::sin(a3) + std::cos(a1)*std::cos(a2)*std::cos(a3);
            this->data[1] =  std::sin(a1)*std::sin(a2)*std::cos(a3) + std::sin(a3)*std::cos(a1)*std::cos(a2);
            this->data[2] =  std::sin(a1)*std::cos(a2)*std::cos(a3) + std::sin(a2)*std::sin(a3)*std::cos(a1);
            this->data[3] = -std::sin(a1)*std::sin(a3)*std::cos(a2) + std::sin(a2)*std::cos(a1)*std::cos(a3);
        } break;

        case RotationSequence::ZXY_312:
        {
            this->data[0] = -std::sin(a1)*std::sin(a2)*std::sin(a3) + std::cos(a1)*std::cos(a2)*std::cos(a3);
            this->data[1] = -std::sin(a1)*std::sin(a3)*std::cos(a2) + std::sin(a2)*std::cos(a1)*std::cos(a3);
            this->data[2] =  std::sin(a1)*std::sin(a2)*std::cos(a3) + std::sin(a3)*std::cos(a1)*std::cos(a2);
            this->data[3] =  std::sin(a1)*std::cos(a2)*std::cos(a3) + std::sin(a2)*std::sin(a3)*std::cos(a1);
        } break;

        case RotationSequence::XZY_132:
        {
            this->data[0] =  std::sin(a1)*std::sin(a2)*std::sin(a3) + std::cos(a1)*std::cos(a2)*std::cos(a3);
            this->data[1] =  std::sin(a1)*std::cos(a2)*std::cos(a3) - std::sin(a2)*std::sin(a3)*std::cos(a1);
            this->data[2] = -std::sin(a1)*std::sin(a2)*std::cos(a3) + std::sin(a3)*std::cos(a1)*std::cos(a2);
            this->data[3] =  std::sin(a1)*std::sin(a3)*std::cos(a2) + std::sin(a2)*std::cos(a1)*std::cos(a3);
        } break;

        case RotationSequence::ZYX_321:
        {
            this->data[0] =  std::sin(a1)*std::sin(a2)*std::sin(a3) + std::cos(a1)*std::cos(a2)*std::cos(a3);
            this->data[1] = -std::sin(a1)*std::sin(a2)*std::cos(a3) + std::sin(a3)*std::cos(a1)*std::cos(a2);
            this->data[2] =  std::sin(a1)*std::sin(a3)*std::cos(a2) + std::sin(a2)*std::cos(a1)*std::cos(a3);
            this->data[3] =  std::sin(a1)*std::cos(a2)*std::cos(a3) - std::sin(a2)*std::sin(a3)*std::cos(a1);
        } break;

        case RotationSequence::YXZ_213:
        {
            this->data[0] =  std::sin(a1)*std::sin(a2)*std::sin(a3) + std::cos(a1)*std::cos(a2)*std::cos(a3);
            this->data[1] =  std::sin(a1)*std::sin(a3)*std::cos(a2) + std::sin(a2)*std::cos(a1)*std::cos(a3);
            this->data[2] =  std::sin(a1)*std::cos(a2)*std::cos(a3) - std::sin(a2)*std::sin(a3)*std::cos(a1);
            this->data[3] = -std::sin(a1)*std::sin(a2)*std::cos(a3) + std::sin(a3)*std::cos(a1)*std::cos(a2);
        } break;

        default:
        {
            // Undefined rotation sequence
            char message[100];
            snprintf(message, 100, "ERROR: Undefined rotation sequence!\n");
            throw std::runtime_error(message);
        } break;
    }
}

//! Construct from Direction Cosine Matrix
template<class T>
Quaternion<T>::Quaternion(const DCM<T> &dcm)
{
    // Stevens and Lewis, 1.8-19a, 1.8-19b
    T t = dcm.trace();
    if( t > 0.0)
    {
        this->data[0] = 0.5*std::sqrt(1.0 + t);
        this->data[1] = (dcm(2,1) - dcm(1,2)) / (4.0*this->data[0]);
        this->data[2] = (dcm(0,2) - dcm(2,0)) / (4.0*this->data[0]);
        this->data[3] = (dcm(1,0) - dcm(0,1)) / (4.0*this->data[0]);
    }
    else if(dcm(0,0) > dcm(1,1) && dcm(0,0) > dcm(2,2))
    {
        this->data[1] = 0.5*std::sqrt(1.0 + dcm(0,0) - dcm(1,1) - dcm(2,2));
        T div = 1.0 / (4.0*this->data[1]);
        this->data[0] = (dcm(2,1) - dcm(1,2)) * div;
        this->data[2] = (dcm(1,0) + dcm(0,1)) * div;
        this->data[3] = (dcm(0,2) + dcm(2,0)) * div;
    }
    else if(dcm(1,1) > dcm(2,2))
    {
        this->data[2] = 0.5*std::sqrt(1.0 - dcm(0,0) + dcm(1,1) - dcm(2,2));
        T div = 1.0 / (4.0*this->data[2]);
        this->data[0] = (dcm(0,2) - dcm(2,0)) * div;
        this->data[1] = (dcm(1,0) + dcm(0,1)) * div;
        this->data[3] = (dcm(2,1) + dcm(1,2)) * div;
    }
    else
    {
        this->data[3] = 0.5*std::sqrt(1.0 - dcm(0,0) - dcm(1,1) + dcm(2,2));
        T div = 1.0 / (4.0*this->data[3]);
        this->data[0] = (dcm(1,0) - dcm(0,1)) * div;
        this->data[1] = (dcm(0,2) + dcm(2,0)) * div;
        this->data[2] = (dcm(2,1) + dcm(1,2)) * div;
    }
    T norm = this->norm();
    if(norm != T(0))
    {
        *this /= norm;
    }
}

//! Construct quaternion from Vector<T, 4>
template<class T>
Quaternion<T>::Quaternion(const Vector<T, 4> &vec):
    Vector<T, 4>(vec)
{
}

//! Construct a quaternion that rotates vector a to b
template<class T>
Quaternion<T>::Quaternion(const Vector3<T> &a, const Vector3<T> &b, const T eps)
{
    // https://math.stackexchange.com/questions/2356649/how-to-find-the-quaternion-representing-the-rotation-between-two-3-d-vectors
    Quaternion<T> &self = *this;
    Vector3<T> cross = a.cross(b);
    const T dot = a.dot(b);

    // If the vectors are parallel, the cross product is 0
    // and if the vectors point in opposite directions, the dot
    // product is negative
    if(cross.norm() <= eps && dot < 0)
    {
        cross = a.abs();
        if(cross(0) < cross(1))
        {
            if(cross(0) < cross(2))
            {
                cross = Vector3<T>(1, 0, 0);
            }
            else
            {
                cross = Vector3<T>(0, 0, 1);
            }
        }
        else
        {
            if(cross(1) < cross(2))
            {
                cross = Vector3<T>(0, 1, 0);
            }
            else
            {
                cross = Vector3<T>(0, 0, 1);
            }
        }
        self(3) = (T)0;
        cross = a.cross(cross);
    }
    // Non-edge-case, half-quat solution
    else
    {
        T anorm = a.norm();
        T bnorm = b.norm();
        self(0) = dot + std::sqrt(anorm*anorm * bnorm*bnorm);
    }

    self(1) = cross(0);
    self(2) = cross(1);
    self(3) = cross(2);
    self.normalize();
}

//! Quaternion addition
template<class T>
Quaternion<T> Quaternion<T>::operator+(const Quaternion<T> &q) const
{
    return Quaternion<T>(this->data[0]+q.data[0], this->data[1]+q.data[1], this->data[2]+q.data[2], this->data[3]+q.data[3]);
}

//! Quaternion subtraction
template<class T>
Quaternion<T> Quaternion<T>::operator-(const Quaternion<T> &q) const
{
    return Quaternion<T>(this->data[0]-q.data[0], this->data[1]-q.data[1], this->data[2]-q.data[2], this->data[3]-q.data[3]);
}

//! Quaternion multiplication
template<class T>
Quaternion<T> Quaternion<T>::operator*(const Quaternion<T> &q) const
{
    // r = p * q
    const Quaternion &p = *this;
    Quaternion r = {p(0)*q(0) - p(1)*q(1) - p(2)*q(2) - p(3)*q(3),
                    p(0)*q(1) + p(1)*q(0) + p(2)*q(3) - p(3)*q(2),
                    p(0)*q(2) - p(1)*q(3) + p(2)*q(0) + p(3)*q(1),
                    p(0)*q(3) + p(1)*q(2) - p(2)*q(1) + p(3)*q(0)};
    return r;
}

//! Compound quaternion addition operator
template<class T>
void Quaternion<T>::operator+=(const Quaternion<T> &other)
{
    this->data[0] += other.data[0];
    this->data[1] += other.data[1];
    this->data[2] += other.data[2];
    this->data[3] += other.data[3];
}

//! Compound quaternion subtraction operator
template<class T>
void Quaternion<T>::operator-=(const Quaternion<T> &other)
{
    this->data[0] -= other.data[0];
    this->data[1] -= other.data[1];
    this->data[2] -= other.data[2];
    this->data[3] -= other.data[3];
}

//! Quaternion compound multiplication operator
template<class T>
void Quaternion<T>::operator*=(const Quaternion<T> &other)
{
    Quaternion &self = *this;
    self = self * other;
}

//! Add scalar component
template<class T>
Quaternion<T> Quaternion<T>::operator+(T value) const
{
    return Quaternion<T>(this->data[0]+value, this->data[1], this->data[2], this->data[3]);
}

//! Subtract scalar component
template<class T>
Quaternion<T> Quaternion<T>::operator-(T value) const
{
    return Quaternion<T>(this->data[0]-value, this->data[1], this->data[2], this->data[3]);
}

//! Quaternion-scalar multiplication
template<class T>
Quaternion<T> Quaternion<T>::operator*(T value) const
{
    return Quaternion<T>(this->data[0]*value, this->data[1]*value, this->data[2]*value, this->data[3]*value);
}

//! Compound quaternion-scalar addition
template<class T>
void Quaternion<T>::operator+=(T value)
{
    this->data[0] += value;
}

//! Compound quaternion-scalar subtraction
template<class T>
void Quaternion<T>::operator-=(T value)
{
    this->data[0] -= value;
}

//! Quaternion-scalar compound multiplication operator
template<class T>
void Quaternion<T>::operator*=(T value)
{
    Quaternion &self = *this;
    self = self * value;
}

//! Compute the norm
template<class T>
T Quaternion<T>::norm() const
{
    return this->data[0]*this->data[0] + this->data[1]*this->data[1] + this->data[2]*this->data[2] + this->data[3]*this->data[3];
}

//! Compute quaternion conjugate
template<class T>
Quaternion<T> Quaternion<T>::conjugate() const
{
    return Quaternion(this->data[0], -this->data[1], -this->data[2], -this->data[3]);
}

//! Compute the derivative of a quaternion rotation from system a to system b
template<class T>
Vector<T, 4> Quaternion<T>::derivA2B(const Vector3<T> &w) const
{
    // Equation 1.8-14 in Stevens and Lewis
    const Quaternion &q = *this;
    return 0.5 * q * Quaternion<T>(0, w);
}

//! Return the inverse of this quaternion
template<class T>
Quaternion<T> Quaternion<T>::inverse() const
{
    // Equation 1.8-5 in Stevens and Lewis
    const Quaternion &q = *this;
    T norm = q.norm();
    return conjugate() / norm;
}

//! Invert this quaternion
template<class T>
void Quaternion<T>::invert()
{
    Quaternion<T> &self = *this;
    self = self.inverse();
}

//! Return as a matrix
template<class T>
SquareMatrix<T, 4> Quaternion<T>::asMatrix() const
{
    SquareMatrix<T, 4> m = {{ this->data[0],  this->data[1],  this->data[2],  this->data[3]},
                            {-this->data[1],  this->data[0], -this->data[3],  this->data[2]},
                            {-this->data[2],  this->data[3],  this->data[0], -this->data[1]},
                            {-this->data[3], -this->data[2],  this->data[1],  this->data[0]}};
    return m;
}

//! Scalar-Quaternion multiplication
template<class T>
Quaternion<T> operator*(T value, const Quaternion<T> &q)
{
    return q * value;
}

} // namespace matrix

#endif // _QUATERNION_HPP__