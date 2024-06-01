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
//! Y axis: theta (pitch)
//! X axis: phi (roll)
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

#if 0
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
#endif

template<class T>
class Euler
{
public:
    //! Default constructor
    Euler();

    //! Copy constructor from Vector
    // Euler(const Vector<T, 3> &other, EulerSequence seq = EulerSequence::ZYX_321);

    //! Copy constructor from Matrix
    // Euler(const Matrix<T, 3, 1> &other, EulerSequence seq = EulerSequence::ZYX_321);

    //! Create from provided angles
    Euler(T _psi, T _theta, T _phi);

    //! Create from DCM
    Euler(const DCM<T> &dcm);

    //! Create from quaternion
    Euler(const Quaternion<T> &quaternion);

    //! Get yaw/heading/psi
    inline const T getPsi() const { return psi; }

    //! Get pitch/theta
    inline const T getTheta() const { return theta; }

    //! Get roll/phi
    inline const T getPhi() const { return phi; }

    //! Assign yaw/psi
    inline T& Psi() { return psi; }

    //! Assign pitch/theta
    inline T& Theta() { return theta; }

    //! Assign roll/phi
    inline T& Phi() { return phi; }
protected:
private:
    T psi;
    T theta;
    T phi;
}; // class Euler

//! Default constructor
template<class T>
Euler<T>::Euler():
    psi(0),
    theta(0),
    phi(0)
{
}

//! Create from provided angles
template<class T>
Euler<T>::Euler(T _psi, T _theta, T _phi):
    psi(_psi),
    theta(_theta),
    phi(_phi)
{
}

//! Create from DCM
template<class T>
Euler<T>::Euler(const DCM<T> &dcm)
{
    // TODO: need to account for (see Stevens and Lewis page 12):
    // -pi < phi <= +pi
    // -pi/2 <= theta <= pi/2
    // -pi < psi <= pi
    phi = atan2(dcm(1,2), dcm(2,2));
    theta = -asin(dcm(0,2));
    psi = atan2(dcm(0,1), dcm(0,0));
}

//! Create from quaternion
template<class T>
Euler<T>::Euler(const Quaternion<T> &quaternion)
{
    //
}

} // namespace matrix

#endif // _EULER_HPP__