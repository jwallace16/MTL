///////////////////////////////////////////////////////////////////////////////
//!
//! @file Euler.hpp
//!
//! Euler angles class. This class assumes all angles are provided in radians
//!
//! @author David Wallace <jdavidwallace1@gmail.com>
///////////////////////////////////////////////////////////////////////////////
#ifndef _EULER_HPP__
#define _EULER_HPP__

#include <cmath>

#include "Vector3.hpp"
#include "DCM.hpp"
#include "Quaternion.hpp"

namespace matrix
{

template<class T>
class DCM;

template<class T>
class Quaternion;

enum class EulerSequence
{
    // "Proper" Euler Angles
    ZXZ_313 = 0,
    XYX_121,
    YZY_232,
    ZYZ_323,
    XZX_131,
    YXY_212,
    // Tait-Bryan angles
    XYZ_123,
    YZX_231,
    ZXY_312,
    XZY_132,
    ZYX_321,
    YXZ_213
};

template<class T>
class Euler: public Vector3<T>
{
public:
    //! Default constructor
    Euler(EulerSequence seq = EulerSequence::ZYX_321);

    //! Copy constructor from Vector
    Euler(const Vector<T, 3> &other, EulerSequence seq = EulerSequence::ZYX_321);

    //! Copy constructor from Matrix
    Euler(const Matrix<T, 3, 1> &other, EulerSequence seq = EulerSequence::ZYX_321);

    //! Create from provided angles
    Euler(T _angle1, T _angle2, T _angle3, EulerSequence seq = EulerSequence::ZYX_321);

    //! Create from DCM
    Euler(const DCM<T> &dcm);

    //! Create from quaternion
    Euler(const Quaternion<T> &quaternion);

    //! Get sequence
    inline EulerSequence getSequence() const { return sequence; }

    //! Get angle-1, -2, -3
    inline T getAngle1() const { return this->data[0]; }
    inline T getAngle2() const { return this->data[1]; }
    inline T getAngle3() const { return this->data[2]; }

    //! Obtain a DCM from an Euler sequence
    DCM<T> getDCM() const; // TODO: remove when DCM class is finalized & use conversion constructor
protected:
private:
    EulerSequence sequence;
}; // class Euler

//! Default constructor
template<class T>
Euler<T>::Euler(EulerSequence seq):
    Vector3<T>(),
    sequence(seq)
{
}

//! Copy constructor from Vector
template<class T>
Euler<T>::Euler(const Vector<T, 3> &other, EulerSequence seq):
    Vector3<T>(other),
    sequence(seq)
{
}

//! Copy constructor from Matrix
template<class T>
Euler<T>::Euler(const Matrix<T, 3, 1> &other, EulerSequence seq):
    Vector3<T>(other),
    sequence(seq)
{
}

//! Create from provided angles
template<class T>
Euler<T>::Euler(T _angle1, T _angle2, T _angle3, EulerSequence seq):
    Vector3<T>(_angle1, _angle2, _angle3),
    sequence(seq)
{
}

//! Create from DCM
template<class T>
Euler<T>::Euler(const DCM<T> &dcm)
{
    //
}

//! Create from quaternion
template<class T>
Euler<T>::Euler(const Quaternion<T> &quaternion)
{
    //
}

//! Obtain a DCM from an Euler sequence
template<class T>
DCM<T> Euler<T>::getDCM() const
{
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
    return dcm;
}

} // namespace matrix

#endif // _EULER_HPP__