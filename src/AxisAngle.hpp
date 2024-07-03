///////////////////////////////////////////////////////////////////////////////
//!
//! @file AxisAngle.hpp
//!
//! Axis/Angle class
//!
//! @author David Wallace <jdavidwallace1@gmail.com>
///////////////////////////////////////////////////////////////////////////////
#ifndef _AXIS_ANGLE_HPP__
#define _AXIS_ANGLE_HPP__

#include "Vector3.hpp"

namespace matrix
{

template<class T>
class AxisAngle: public Vector3<T>
{
public:
    //! Default constructor
    AxisAngle() = default;

protected:
private:
    

};

} // namespace matrix

#endif // _AXIS_ANGLE_HPP__