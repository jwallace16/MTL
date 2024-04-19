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

namespace matrix
{

template<class T>
class Quaternion;

template<class T>
class Euler;

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

//! Constructor from Quaternion (Equation 1.8-18, Stevens and Lewis)
template<class T>
DCM<T>::DCM(const Quaternion<T> &q)
{
    DCM &self = *this;
    // const T q0, q1, q2, q3 = q(0), q(1), q(2), q(3);
    self(0,0) = q(0)*q(0) + q(1)*q(1) - q(2)*q(2) - q(3)*q(3);
    self(0,1) = T(2)*(q(1)*q(2) + q(0)*q(3));
    self(0,2) = T(2)*(q(1)*q(3) - q(0)*q(2));
    self(1,0) = T(2)*(q(1)*q(2) - q(0)*q(3));
    self(1,1) = q(0)*q(0) - q(1)*q(1) + q(2)*q(2) - q(3)*q(3);
    self(1,2) = T(2)*(q(2)*q(3) + q(0)*q(1));
    self(2,0) = T(2)*(q(1)*q(3) + q(0)*q(2));
    self(2,1) = T(2)*(q(2)*q(3) - q(0)*q(1));
    self(2,2) = q(0)*q(0) - q(1)*q(1) - q(2)*q(2) + q(3)*q(3);
}

//! Constructor from Euler Angles
template<class T>
DCM<T>::DCM(const Euler<T> &e)
{
    #if 0
    matrix::DCM<T> dcm;
    switch(sequence)
    {
        case EulerSequence::ZXZ_313:
        {
            //
        } break;

        case EulerSequence::XYX_121:
        {
            //
        } break;

        case EulerSequence::YZY_232:
        {
            //
        } break;

        case EulerSequence::ZYZ_323:
        {
            //
        } break;

        case EulerSequence::XZX_131:
        {
            ///
        } break;

        case EulerSequence::YXY_212:
        {
            //
        } break;

        case EulerSequence::XYZ_123:
        {
            //
        } break;

        case EulerSequence::YZX_231:
        {
            //
        } break;

        case EulerSequence::ZXY_312:
        {
            //
        } break;

        case EulerSequence::XZY_132:
        {
            //
        } break;

        case EulerSequence::ZYX_321:
        {
            // Z-axis
            T zvals[3][3] = {{std::cos(this->data[2]), std::sin(this->data[2]), 0},
                             {-std::sin(this->data[2]), std::cos(this->data[2]), 0},
                             {0, 0, 1}};
            DCM<T> z(zvals);

            // Y-axis
            T yvals[3][3] = {{std::cos(this->data[1]), 0, -std::sin(this->data[1])},
                             {0, 1, 0},
                             {std::sin(this->data[1]), 0, std::cos(this->data[1])}};
            DCM<T> y(yvals);

            // X-axis
            T xvals[3][3] = {{1, 0, 0},
                             {0, std::cos(this->data[0]), std::sin(this->data[0])},
                             {0, -std::sin(this->data[0]), std::cos(this->data[0])}};
            DCM<T> x(xvals);

            dcm = x*y*z;
        } break;

        case EulerSequence::YXZ_213:
        {
            //
        } break;

        default:
        {
            //
        } break;
    }
    #endif
}

} // namespace matrix

#endif // _DCM_HPP__