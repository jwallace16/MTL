///////////////////////////////////////////////////////////////////////////////
//!
//! @file DCM.hpp
//!
//! Direction cosine matrix class. 
//!
//! @author David Wallace <jdavidwallace1@gmail.com>
///////////////////////////////////////////////////////////////////////////////
#ifndef _DCM_HPP__
#define _DCM_HPP__

#include "Matrix.hpp"
#include "SquareMatrix.hpp"
#include "Quaternion.hpp"
#include "Euler.hpp"
#include "RotationSequence.hpp"

namespace matrix
{

// template<class T>
// class Quaternion;

// template<class T>
// class Euler;

template<class T>
class DCM: public SquareMatrix<T, 3>
{
public:
    //! Default constructor
    DCM();

    //! Construct from a 2d array of data
    explicit DCM(const T values[3][3]);

    //! Construct from a flat array of data
    explicit DCM(const T values[9]);

    //! Copy constructor from Matrix<T, 3, 3> type
    DCM(const Matrix<T, 3, 3> &other);

    //! Copy constructor from SquareMatrix<T, 3> type
    DCM(const SquareMatrix<T, 3> &other);

    //! Constructor from Quaternion (Equation 1.8-18, Stevens and Lewis)
    DCM(const Quaternion<T> &q);

    //! Constructor from Euler Angles
    DCM(const Euler<T> &e);
}; // class DCM

//! Default constructor
template<class T>
DCM<T>::DCM():
    SquareMatrix<T, 3>(identity<T, 3>())
{
}

//! Construct from a 2d array of data
template<class T>
DCM<T>::DCM(const T values[3][3]):
    SquareMatrix<T, 3>(values)
{
}

//! Construct from a flat array of data
template<class T>
DCM<T>::DCM(const T values[9]):
    SquareMatrix<T, 3>(values)
{
}

//! Copy constructor from Matrix<T, 3, 3>
template<class T>
DCM<T>::DCM(const Matrix<T, 3, 3> &other):
    SquareMatrix<T, 3>(other)
{
}

//! Copy constructor from SquareMatrix<T, 3> type
template<class T>
DCM<T>::DCM(const SquareMatrix<T, 3> &other):
    SquareMatrix<T, 3>(other)
{
}

//! Constructor from Quaternion
template<class T>
DCM<T>::DCM(const Quaternion<T> &q)
{
    Quaternion<T> p = q.unit();
    this->data[0] = p(0)*p(0) + p(1)*p(1) - p(2)*p(2) - p(3)*p(3);
    this->data[1] = static_cast<T>(2)*(p(1)*p(2) - p(0)*p(3));
    this->data[2] = static_cast<T>(2)*(p(1)*p(3) + p(0)*p(2));
    this->data[3] = static_cast<T>(2)*(p(1)*p(2) + p(0)*p(3));
    this->data[4] = p(0)*p(0) - p(1)*p(1) + p(2)*p(2) - p(3)*p(3);
    this->data[5] = static_cast<T>(2)*(p(2)*p(3) - p(0)*p(1));
    this->data[6] = static_cast<T>(2)*(p(1)*p(3) - p(0)*p(2));
    this->data[7] = static_cast<T>(2)*(p(2)*p(3) + p(0)*p(1));
    this->data[8] = p(0)*p(0) - p(1)*p(1) - p(2)*p(2) + p(3)*p(3);
}

//! Constructor from Euler Angles
template<class T>
DCM<T>::DCM(const Euler<T> &e)
{
    T a1 = e.getAngle1();
    T a2 = e.getAngle2();
    T a3 = e.getAngle3();
    switch(e.getSequence())
    {
        case RotationSequence::ZXZ_313:
        {
            this->data[0] = std::cos(a1)*std::cos(a3) - std::cos(a2)*std::sin(a1)*std::sin(a3);
            this->data[1] = -std::cos(a1)*std::sin(a3) - std::cos(a2)*std::cos(a3)*std::sin(a1);
            this->data[2] = std::sin(a1)*std::sin(a2);
            this->data[3] = std::cos(a3)*std::sin(a1) + std::cos(a1)*std::cos(a2)*std::sin(a3);
            this->data[4] = std::cos(a1)*std::cos(a2)*std::cos(a3) - std::sin(a1)*std::sin(a3);
            this->data[5] = -std::cos(a1)*std::sin(a2);
            this->data[6] = std::sin(a2)*std::sin(a3);
            this->data[7] = std::cos(a3)*std::sin(a2);
            this->data[8] = std::cos(a2);
        } break;

        case RotationSequence::XYX_121:
        {
            this->data[0] = std::cos(a2);
            this->data[1] = std::sin(a2)*std::sin(a3);
            this->data[2] = std::cos(a3)*std::sin(a2);
            this->data[3] = std::sin(a1)*std::sin(a2);
            this->data[4] = std::cos(a1)*std::cos(a3) - std::cos(a2)*std::sin(a1)*std::sin(a3);
            this->data[5] = -std::cos(a1)*std::sin(a3) - std::cos(a2)*std::cos(a3)*std::sin(a1);
            this->data[6] = -std::cos(a1)*std::sin(a2);
            this->data[7] = std::cos(a3)*std::sin(a1) + std::cos(a1)*std::cos(a2)*std::sin(a3);
            this->data[8] = std::cos(a1)*std::cos(a2)*std::cos(a3) - std::sin(a1)*std::sin(a3);
        } break;

        case RotationSequence::YZY_232:
        {
            this->data[0] = std::cos(a1)*std::cos(a2)*std::cos(a3) - std::sin(a1)*std::sin(a3);
            this->data[1] = -std::cos(a1)*std::sin(a1);
            this->data[2] = std::cos(a3)*std::sin(a1) + std::cos(a1)*std::cos(a2)*std::sin(a3);
            this->data[3] = std::cos(a3)*std::sin(a2);
            this->data[4] = std::cos(a2);
            this->data[5] = std::sin(a2)*std::sin(a3);
            this->data[6] = -std::cos(a1)*std::sin(a3) - std::cos(a2)*std::cos(a3)*std::sin(a1);
            this->data[7] = std::sin(a1)*std::sin(a2);
            this->data[8] = std::cos(a1)*std::cos(a3) - std::cos(a2)*std::sin(a1)*std::sin(a3);
        } break;

        case RotationSequence::ZYZ_323:
        {
            this->data[0] = std::cos(a1)*std::cos(a2)*std::cos(a3) - std::sin(a1)*std::sin(a3);
            this->data[1] = -std::cos(a3)*std::sin(a1) - std::cos(a1)*std::cos(a2)*std::sin(a3);
            this->data[2] = std::cos(a1)*std::sin(a2);
            this->data[3] = std::cos(a1)*std::sin(a3) + std::cos(a2)*std::cos(a3)*std::sin(a1);
            this->data[4] = std::cos(a1)*std::cos(a3) - std::cos(a2)*std::sin(a1)*std::sin(a3);
            this->data[5] = std::sin(a1)*std::sin(a2);
            this->data[6] = -std::cos(a3)*std::sin(a2);
            this->data[7] = std::sin(a2)*std::sin(a3);
            this->data[8] = std::cos(a2);
        } break;

        case RotationSequence::XZX_131:
        {
            this->data[0] = std::cos(a2);
            this->data[1] = -std::cos(a3)*std::sin(a2);
            this->data[2] = std::sin(a2)*std::sin(a3);
            this->data[3] = std::cos(a1)*std::sin(a2);
            this->data[4] = std::cos(a1)*std::cos(a2)*std::cos(a3) - std::sin(a1)*std::sin(a3);
            this->data[5] = -std::cos(a3)*std::sin(a1) - std::cos(a1)*std::cos(a2)*std::sin(a3);
            this->data[6] = std::sin(a1)*std::sin(a2);
            this->data[7] = std::cos(a1)*std::sin(a3) + std::cos(a2)*std::cos(a3)*std::sin(a1);
            this->data[8] = std::cos(a1)*std::cos(a3) - std::cos(a2)*std::sin(a1)*std::sin(a3);
        } break;

        case RotationSequence::YXY_212:
        {
            this->data[0] = std::cos(a1)*std::cos(a3) - std::cos(a2)*std::sin(a1)*std::sin(a3);
            this->data[1] = std::sin(a1)*std::sin(a2);
            this->data[2] = std::cos(a1)*std::sin(a3) + std::cos(a2)*std::cos(a3)*std::sin(a1);
            this->data[3] = std::sin(a2)*std::sin(a3);
            this->data[4] = std::cos(a2);
            this->data[5] = -std::cos(a3)*std::sin(a2);
            this->data[6] = -std::cos(a3)*std::sin(a1) - std::cos(a1)*std::cos(a2)*std::sin(a3);
            this->data[7] = std::cos(a1)*std::sin(a2);
            this->data[8] = std::cos(a1)*std::cos(a2)*std::cos(a3) - std::sin(a1)*std::sin(a3);
        } break;

        case RotationSequence::XYZ_123:
        {
            this->data[0] = std::cos(a2)*std::cos(a3);
            this->data[1] = -std::cos(a2)*std::sin(a3);
            this->data[2] = std::sin(a2);
            this->data[3] = std::cos(a1)*std::sin(a3) + std::cos(a3)*std::sin(a1)*std::sin(a2);
            this->data[4] = std::cos(a1)*std::cos(a3) - std::sin(a1)*std::sin(a2)*std::sin(a3);
            this->data[5] = -std::cos(a2)*std::sin(a1);
            this->data[6] = std::sin(a1)*std::sin(a3) - std::cos(a1)*std::cos(a3)*std::sin(a2);
            this->data[7] = std::cos(a3)*std::sin(a1) + std::cos(a1)*std::sin(a2)*std::sin(a3);
            this->data[8] = std::cos(a1)*std::cos(a2);
        } break;

        case RotationSequence::YZX_231:
        {
            this->data[0] = std::cos(a1)*std::cos(a2);
            this->data[1] = std::sin(a1)*std::sin(a3) - std::cos(a1)*std::cos(a3)*std::sin(a2);
            this->data[2] = std::cos(a3)*std::sin(a1) + std::cos(a1)*std::sin(a2)*std::sin(a3);
            this->data[3] = std::sin(a2);
            this->data[4] = std::cos(a2)*std::cos(a3);
            this->data[5] = -std::cos(a2)*std::sin(a3);
            this->data[6] = -std::cos(a2)*std::sin(a1);
            this->data[7] = std::cos(a1)*std::sin(a3) + std::cos(a3)*std::sin(a1)*std::sin(a2);
            this->data[8] = std::cos(a1)*std::cos(a3) - std::sin(a1)*std::sin(a2)*std::sin(a3);
        } break;

        case RotationSequence::ZXY_312:
        {
            this->data[0] = std::cos(a1)*std::cos(a3) - std::sin(a1)*std::sin(a2)*std::sin(a3);
            this->data[1] = -std::cos(a2)*std::sin(a2);
            this->data[2] = std::cos(a1)*std::sin(a3) + std::cos(a3)*std::sin(a1)*std::sin(a2);
            this->data[3] = std::cos(a3)*std::sin(a1) + std::cos(a1)*std::sin(a2)*std::sin(a3);
            this->data[4] = std::cos(a1)*std::cos(a2);
            this->data[5] = std::sin(a1)*std::sin(a3) - std::cos(a1)*std::cos(a3)*std::sin(a2);
            this->data[6] = -std::cos(a2)*std::sin(a3);
            this->data[7] = std::sin(a2);
            this->data[8] = std::cos(a2)*std::cos(a3);
        } break;

        case RotationSequence::XZY_132:
        {
            this->data[0] = std::cos(a2)*std::cos(a3);
            this->data[1] = -std::sin(a2);
            this->data[2] = std::cos(a2)*std::sin(a3);
            this->data[3] = std::sin(a1)*std::sin(a3) + std::cos(a1)*std::cos(a3)*std::sin(a2);
            this->data[4] = std::cos(a1)*std::cos(a2);
            this->data[5] = std::cos(a1)*std::sin(a2)*std::sin(a3) - std::cos(a3)*std::sin(a1);
            this->data[6] = std::cos(a3)*std::sin(a1)*std::sin(a2) - std::cos(a1)*std::sin(a3);
            this->data[7] = std::cos(a2)*std::sin(a1);
            this->data[8] = std::cos(a1)*std::cos(a3) + std::sin(a1)*std::sin(a2)*std::sin(a3);
        } break;

        case RotationSequence::ZYX_321:
        {
            this->data[0] = std::cos(a1)*std::cos(a2);
            this->data[1] = std::cos(a1)*std::sin(a2)*std::sin(a3) - std::cos(a3)*std::sin(a1);
            this->data[2] = std::sin(a1)*std::sin(a3) + std::cos(a1)*std::cos(a3)*std::sin(a2);
            this->data[3] = std::cos(a2)*std::sin(a1);
            this->data[4] = std::cos(a1)*std::cos(a3) + std::sin(a1)*std::sin(a2)*std::sin(a3);
            this->data[5] = std::cos(a3)*std::sin(a1)*std::sin(a2) - std::cos(a1)*std::sin(a3);
            this->data[6] = -std::sin(a2);
            this->data[7] = std::cos(a2)*std::sin(a3);
            this->data[8] = std::cos(a2)*std::cos(a3);
        } break;

        case RotationSequence::YXZ_213:
        {
            this->data[0] = std::cos(a1)*std::cos(a3) + std::sin(a1)*std::sin(a2)*std::sin(a3);
            this->data[1] = std::cos(a3)*std::sin(a1)*std::sin(a2) - std::cos(a1)*std::sin(a3);
            this->data[2] = std::cos(a2)*std::sin(a1);
            this->data[3] = std::cos(a2)*std::sin(a3);
            this->data[4] = std::cos(a2)*std::cos(a3);
            this->data[5] = -std::sin(a2);
            this->data[6] = std::cos(a1)*std::sin(a2)*std::sin(a3) - std::cos(a3)*std::sin(a1);
            this->data[7] = std::cos(a1)*std::cos(a3)*std::sin(a2) + std::sin(a1)*std::sin(a3);
            this->data[8] = std::cos(a1)*std::cos(a2);
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

} // namespace matrix

#endif // _DCM_HPP__