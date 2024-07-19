///////////////////////////////////////////////////////////////////////////////
//!
//! @file RotationSequence.hpp
//!
//! Defining rotation sequences for Quaternion, DCM, and Euler classes
//!
//! @author David Wallace <jdavidwallace1@gmail.com>
///////////////////////////////////////////////////////////////////////////////
#ifndef _ROTATION_SEQUENCE_HPP__
#define _ROTATION_SEQUENCE_HPP__

enum class RotationSequence
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

#endif // _ROTATION_SEQUENCE_HPP__