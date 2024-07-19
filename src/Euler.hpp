///////////////////////////////////////////////////////////////////////////////
//!
//! @file Euler.hpp
//!
//! Euler angles class. This class assumes all angles are provided in radians.
//! I initially wanted to provide an Euler class that could represent any 
//! rotation sequence (think: for robotics applications, etc), but for the time
//! being I'd rather cover more ground before working through a lot of cases 
//! that are unlikely to be used. TL;DR I am lazy.
//!
//! This class will utilize a ZYX (3-2-1) right-handed rotation sequence, with:
//! Z axis: psi (yaw)
//! Y' axis: theta (pitch)
//! X'' axis: phi (roll)
//!
//! @author David Wallace <jdavidwallace1@gmail.com>
///////////////////////////////////////////////////////////////////////////////
#ifndef _EULER_HPP__
#define _EULER_HPP__

#include <cmath>

#include "Vector3.hpp"
#include "DCM.hpp"
#include "Quaternion.hpp"
#include "RotationSequence.hpp"

namespace matrix
{

template<class T>
class DCM;

template<class T>
class Quaternion;

template<class T>
class Euler
{
public:
    //! Default constructor
    Euler(RotationSequence _seq = RotationSequence::ZYX_321);

    //! Copy constructor from Vector
    // Euler(const Vector<T, 3> &other, EulerSequence seq = EulerSequence::ZYX_321);

    //! Copy constructor from Matrix
    // Euler(const Matrix<T, 3, 1> &other, EulerSequence seq = EulerSequence::ZYX_321);

    //! Create from provided angles
    // Euler(T _psi, T _theta, T _phi);
    Euler(T _angle1, T _angle2, T _angle3, RotationSequence _seq = RotationSequence::ZYX_321);

    //! Create from DCM
    Euler(const DCM<T> &dcm, RotationSequence _seq = RotationSequence::ZYX_321);

    //! Create from quaternion
    Euler(const Quaternion<T> &quaternion, RotationSequence _seq = RotationSequence::ZYX_321);

    //! Get rotation sequence
    inline const RotationSequence getRotatationSequence() const { return seq; }

    //! Get angle-1, -2, -3
    inline const T getAngle1() const { return angle1; }
    inline const T getAngle2() const { return angle2; }
    inline const T getAngle3() const { return angle3; }

    //! Assign angle-1, -2, -3
    inline T& setAngle1(){ return angle1; }
    inline T& setAngle2(){ return angle2; }
    inline T& setAngle3(){ return angle3; }
protected:
private:
    RotationSequence seq;
    T angle1;
    T angle2;
    T angle3;
}; // class Euler

//! Default constructor
template<class T>
Euler<T>::Euler(RotationSequence _seq):
    seq(_seq),
    angle1(0),
    angle2(0),
    angle3(0)
{
}

template<class T>
Euler<T>::Euler(T _angle1, T _angle2, T _angle3, RotationSequence _seq):
    seq(_seq),
    angle1(_angle1),
    angle2(_angle2),
    angle3(_angle3)
{
}

//! Create from DCM
template<class T>
Euler<T>::Euler(const DCM<T> &dcm, RotationSequence _seq):
    seq(_seq)
{
    #if 0
    // need to account for (see Stevens and Lewis page 12):
    // -pi < phi <= +pi
    // -pi/2 <= theta <= pi/2
    // -pi < psi <= pi
    //
    // Note: Special case when handling theta = -pi/2
    theta = -std::asin(dcm(0,2));
    if(std::fabs(theta - M_PI/2.0) < 1.0e-6)
    {
        phi = 0.0;
        psi = std::atan2(dcm(2,1), dcm(2,0));
    }
    else if(std::fabs(theta + M_PI/2.0) < 1.0e-6)
    {
        //
    }
    else
    {
        phi = atan2(dcm(1,2), dcm(2,2));
        psi = atan2(dcm(0,1), dcm(0,0));
    }
    #endif
}

//! Create from quaternion
template<class T>
Euler<T>::Euler(const Quaternion<T> &quaternion, RotationSequence _seq):
    seq(_seq)
{
    //
}

} // namespace matrix

#endif // _EULER_HPP__