///////////////////////////////////////////////////////////////////////////////
//!
//! @file TestDCM.cpp
//!
//! Unit test for DCM.hpp
//!
//! @author David Wallace <jdavidwallace1@gmail.com>
///////////////////////////////////////////////////////////////////////////////

#include <iostream>
#include <gtest/gtest.h>
#include "../src/DCM.hpp"

TEST(DCMTestSuite, TestDefaultConstructor)
{
    matrix::DCM<double> d;
    EXPECT_DOUBLE_EQ(1.0, d(0,0));
    EXPECT_DOUBLE_EQ(0.0, d(0,1));
    EXPECT_DOUBLE_EQ(0.0, d(0,2));
    EXPECT_DOUBLE_EQ(0.0, d(1,0));
    EXPECT_DOUBLE_EQ(1.0, d(1,1));
    EXPECT_DOUBLE_EQ(0.0, d(1,2));
    EXPECT_DOUBLE_EQ(0.0, d(2,0));
    EXPECT_DOUBLE_EQ(0.0, d(2,1));
    EXPECT_DOUBLE_EQ(1.0, d(2,2));
}

TEST(DCMTestSuite, TestConstructor2dArray)
{
    double vals[3][3] = {{1.1, 2.2, 3.3}, {4.4, 5.5, 6.6}, {7.7, 8.8, 9.9}};
    matrix::DCM<double> d(vals);
    EXPECT_DOUBLE_EQ(1.1, d(0,0));
    EXPECT_DOUBLE_EQ(2.2, d(0,1));
    EXPECT_DOUBLE_EQ(3.3, d(0,2));
    EXPECT_DOUBLE_EQ(4.4, d(1,0));
    EXPECT_DOUBLE_EQ(5.5, d(1,1));
    EXPECT_DOUBLE_EQ(6.6, d(1,2));
    EXPECT_DOUBLE_EQ(7.7, d(2,0));
    EXPECT_DOUBLE_EQ(8.8, d(2,1));
    EXPECT_DOUBLE_EQ(9.9, d(2,2));
}

TEST(DCMTestSuite, TestConstructorFlatArray)
{
    double vals[9] = {1.1, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7, 8.8, 9.9};
    matrix::DCM<double> d(vals);
    EXPECT_DOUBLE_EQ(1.1, d(0,0));
    EXPECT_DOUBLE_EQ(2.2, d(0,1));
    EXPECT_DOUBLE_EQ(3.3, d(0,2));
    EXPECT_DOUBLE_EQ(4.4, d(1,0));
    EXPECT_DOUBLE_EQ(5.5, d(1,1));
    EXPECT_DOUBLE_EQ(6.6, d(1,2));
    EXPECT_DOUBLE_EQ(7.7, d(2,0));
    EXPECT_DOUBLE_EQ(8.8, d(2,1));
    EXPECT_DOUBLE_EQ(9.9, d(2,2));
}

TEST(DCMTestSuite, TestMatrixConversionConstructor)
{
    double vals[9] = {1.1, 1.2, 1.3, 2.1, 2.2, 2.3, 3.1, 3.2, 3.3};
    matrix::Matrix<double, 3, 3> m(vals);
    matrix::DCM<double> d(m);
    EXPECT_DOUBLE_EQ(1.1, d(0,0));
    EXPECT_DOUBLE_EQ(1.2, d(0,1));
    EXPECT_DOUBLE_EQ(1.3, d(0,2));
    EXPECT_DOUBLE_EQ(2.1, d(1,0));
    EXPECT_DOUBLE_EQ(2.2, d(1,1));
    EXPECT_DOUBLE_EQ(2.3, d(1,2));
    EXPECT_DOUBLE_EQ(3.1, d(2,0));
    EXPECT_DOUBLE_EQ(3.2, d(2,1));
    EXPECT_DOUBLE_EQ(3.3, d(2,2));
}

TEST(DCMTestSuite, TestQuaternionConversionConstructor)
{
    matrix::Quaternion<double> q1(1.0, 0.0, 0.0, 0.0);
    matrix::DCM<double> d1(q1);
    EXPECT_DOUBLE_EQ(1.0, d1(0,0));
    EXPECT_DOUBLE_EQ(0.0, d1(0,1));
    EXPECT_DOUBLE_EQ(0.0, d1(0,2));
    EXPECT_DOUBLE_EQ(0.0, d1(1,0));
    EXPECT_DOUBLE_EQ(1.0, d1(1,1));
    EXPECT_DOUBLE_EQ(0.0, d1(1,2));
    EXPECT_DOUBLE_EQ(0.0, d1(2,0));
    EXPECT_DOUBLE_EQ(0.0, d1(2,1));
    EXPECT_DOUBLE_EQ(1.0, d1(2,2));
    
    matrix::Quaternion<double> q2(0.0, 1.0, 0.0, 0.0);
    matrix::DCM<double> d2(q2);
    EXPECT_DOUBLE_EQ(1.0, d2(0,0));
    EXPECT_DOUBLE_EQ(0.0, d2(0,1));
    EXPECT_DOUBLE_EQ(0.0, d2(0,2));
    EXPECT_DOUBLE_EQ(0.0, d2(1,0));
    EXPECT_DOUBLE_EQ(-1.0, d2(1,1));
    EXPECT_DOUBLE_EQ(0.0, d2(1,2));
    EXPECT_DOUBLE_EQ(0.0, d2(2,0));
    EXPECT_DOUBLE_EQ(0.0, d2(2,1));
    EXPECT_DOUBLE_EQ(-1.0, d2(2,2));

    matrix::Quaternion<double> q3(0.0, 0.0, 1.0, 0.0);
    matrix::DCM<double> d3(q3);
    EXPECT_DOUBLE_EQ(-1.0, d3(0,0));
    EXPECT_DOUBLE_EQ(0.0, d3(0,1));
    EXPECT_DOUBLE_EQ(0.0, d3(0,2));
    EXPECT_DOUBLE_EQ(0.0, d3(1,0));
    EXPECT_DOUBLE_EQ(1.0, d3(1,1));
    EXPECT_DOUBLE_EQ(0.0, d3(1,2));
    EXPECT_DOUBLE_EQ(0.0, d3(2,0));
    EXPECT_DOUBLE_EQ(0.0, d3(2,1));
    EXPECT_DOUBLE_EQ(-1.0, d3(2,2));

    matrix::Quaternion<double> q4(0.0, 0.0, 0.0, 1.0);
    matrix::DCM<double> d4(q4);
    EXPECT_DOUBLE_EQ(-1.0, d4(0,0));
    EXPECT_DOUBLE_EQ(0.0, d4(0,1));
    EXPECT_DOUBLE_EQ(0.0, d4(0,2));
    EXPECT_DOUBLE_EQ(0.0, d4(1,0));
    EXPECT_DOUBLE_EQ(-1.0, d4(1,1));
    EXPECT_DOUBLE_EQ(0.0, d4(1,2));
    EXPECT_DOUBLE_EQ(0.0, d4(2,0));
    EXPECT_DOUBLE_EQ(0.0, d4(2,1));
    EXPECT_DOUBLE_EQ(1.0, d4(2,2));

    matrix::Quaternion<double> q5(std::sqrt(2.0)/2.0, std::sqrt(2.0)/2.0, 0.0, 0.0);
    matrix::DCM<double> d5(q5);
    EXPECT_DOUBLE_EQ(1.0, d5(0,0));
    EXPECT_DOUBLE_EQ(0.0, d5(0,1));
    EXPECT_DOUBLE_EQ(0.0, d5(0,2));
    EXPECT_DOUBLE_EQ(0.0, d5(1,0));
    EXPECT_DOUBLE_EQ(0.0, d5(1,1));
    EXPECT_DOUBLE_EQ(-1.0, d5(1,2));
    EXPECT_DOUBLE_EQ(0.0, d5(2,0));
    EXPECT_DOUBLE_EQ(1.0, d5(2,1));
    EXPECT_DOUBLE_EQ(0.0, d5(2,2));

    matrix::Quaternion<double> q6(std::sqrt(2.0)/2.0, 0.0, std::sqrt(2.0)/2.0, 0.0);
    matrix::DCM<double> d6(q6);
    EXPECT_DOUBLE_EQ(0.0, d6(0,0));
    EXPECT_DOUBLE_EQ(0.0, d6(0,1));
    EXPECT_DOUBLE_EQ(1.0, d6(0,2));
    EXPECT_DOUBLE_EQ(0.0, d6(1,0));
    EXPECT_DOUBLE_EQ(1.0, d6(1,1));
    EXPECT_DOUBLE_EQ(0.0, d6(1,2));
    EXPECT_DOUBLE_EQ(-1.0, d6(2,0));
    EXPECT_DOUBLE_EQ(0.0, d6(2,1));
    EXPECT_DOUBLE_EQ(0.0, d6(2,2));

    matrix::Quaternion<double> q7(std::sqrt(2.0)/2.0, 0.0, 0.0, std::sqrt(2.0)/2.0);
    matrix::DCM<double> d7(q7);
    EXPECT_DOUBLE_EQ(0.0, d7(0,0));
    EXPECT_DOUBLE_EQ(-1.0, d7(0,1));
    EXPECT_DOUBLE_EQ(0.0, d7(0,2));
    EXPECT_DOUBLE_EQ(1.0, d7(1,0));
    EXPECT_DOUBLE_EQ(0.0, d7(1,1));
    EXPECT_DOUBLE_EQ(0.0, d7(1,2));
    EXPECT_DOUBLE_EQ(0.0, d7(2,0));
    EXPECT_DOUBLE_EQ(0.0, d7(2,1));
    EXPECT_DOUBLE_EQ(1.0, d7(2,2));

    matrix::Quaternion<double> q8(0.0, std::sqrt(2.0)/2.0, std::sqrt(2.0)/2.0, 0.0);
    matrix::DCM<double> d8(q8);
    EXPECT_DOUBLE_EQ(0.0, d8(0,0));
    EXPECT_DOUBLE_EQ(1.0, d8(0,1));
    EXPECT_DOUBLE_EQ(0.0, d8(0,2));
    EXPECT_DOUBLE_EQ(1.0, d8(1,0));
    EXPECT_DOUBLE_EQ(0.0, d8(1,1));
    EXPECT_DOUBLE_EQ(0.0, d8(1,2));
    EXPECT_DOUBLE_EQ(0.0, d8(2,0));
    EXPECT_DOUBLE_EQ(0.0, d8(2,1));
    EXPECT_DOUBLE_EQ(-1.0, d8(2,2));

    matrix::Quaternion<double> q9(0.0, std::sqrt(2.0)/2.0, 0.0, std::sqrt(2.0)/2.0);
    matrix::DCM<double> d9(q9);
    EXPECT_DOUBLE_EQ(0.0, d9(0,0));
    EXPECT_DOUBLE_EQ(0.0, d9(0,1));
    EXPECT_DOUBLE_EQ(1.0, d9(0,2));
    EXPECT_DOUBLE_EQ(0.0, d9(1,0));
    EXPECT_DOUBLE_EQ(-1.0, d9(1,1));
    EXPECT_DOUBLE_EQ(0.0, d9(1,2));
    EXPECT_DOUBLE_EQ(1.0, d9(2,0));
    EXPECT_DOUBLE_EQ(0.0, d9(2,1));
    EXPECT_DOUBLE_EQ(0.0, d9(2,2));

    matrix::Quaternion<double> q10(0.0, 0.0, std::sqrt(2.0)/2.0, std::sqrt(2.0)/2.0);
    matrix::DCM<double> d10(q10);
    EXPECT_DOUBLE_EQ(-1.0, d10(0,0));
    EXPECT_DOUBLE_EQ(0.0, d10(0,1));
    EXPECT_DOUBLE_EQ(0.0, d10(0,2));
    EXPECT_DOUBLE_EQ(0.0, d10(1,0));
    EXPECT_DOUBLE_EQ(0.0, d10(1,1));
    EXPECT_DOUBLE_EQ(1.0, d10(1,2));
    EXPECT_DOUBLE_EQ(0.0, d10(2,0));
    EXPECT_DOUBLE_EQ(1.0, d10(2,1));
    EXPECT_DOUBLE_EQ(0.0, d10(2,2));

    matrix::Quaternion<double> q11(-std::sqrt(2.0)/2.0, std::sqrt(2.0)/2.0, 0.0, 0.0);
    matrix::DCM<double> d11(q11);
    EXPECT_DOUBLE_EQ(1.0, d11(0,0));
    EXPECT_DOUBLE_EQ(0.0, d11(0,1));
    EXPECT_DOUBLE_EQ(0.0, d11(0,2));
    EXPECT_DOUBLE_EQ(0.0, d11(1,0));
    EXPECT_DOUBLE_EQ(0.0, d11(1,1));
    EXPECT_DOUBLE_EQ(1.0, d11(1,2));
    EXPECT_DOUBLE_EQ(0.0, d11(2,0));
    EXPECT_DOUBLE_EQ(-1.0, d11(2,1));
    EXPECT_DOUBLE_EQ(0.0, d11(2,2));

    matrix::Quaternion<double> q12 = {-39.5, -6.37, 23.61, 14.65};
    matrix::DCM<double> d12(q12);
    EXPECT_DOUBLE_EQ(0.34926830522299585, d12(0,0));
    EXPECT_DOUBLE_EQ(0.36097824522632083, d12(0,1));
    EXPECT_DOUBLE_EQ(-0.86470015464320493, d12(0,2));
    EXPECT_DOUBLE_EQ(-0.61450240983378235, d12(1,0));
    EXPECT_DOUBLE_EQ(0.78490337591658088, d12(1,1));
    EXPECT_DOUBLE_EQ(0.079457402318657666, d12(1,2));
    EXPECT_DOUBLE_EQ(0.70738846419427182, d12(2,0));
    EXPECT_DOUBLE_EQ(0.50360837656663437, d12(2,1));
    EXPECT_DOUBLE_EQ(0.4959638734593364, d12(2,2));
}

TEST(DCMTestSuite, TestEulerAngleConversionConstructor)
{
    double deg2rad = M_PI / 180.0;
    double angle1 = 32.0 * deg2rad;
    double angle2 = 44.0 * deg2rad;
    double angle3 = -100.0 * deg2rad;

    matrix::Euler<double> e1(angle1, angle2, angle3, RotationSequence::ZXZ_313);
    matrix::DCM<double> d1(e1);
    // EXPECT_DOUBLE_EQ(0.0, d1(0,0));
    // EXPECT_DOUBLE_EQ(0.0, d1(0,1));
    // EXPECT_DOUBLE_EQ(0.0, d1(0,2));
    // EXPECT_DOUBLE_EQ(0.0, d1(1,0));
    // EXPECT_DOUBLE_EQ(0.0, d1(1,1));
    // EXPECT_DOUBLE_EQ(0.0, d1(1,2));
    // EXPECT_DOUBLE_EQ(0.0, d1(2,0));
    // EXPECT_DOUBLE_EQ(0.0, d1(2,1));
    // EXPECT_DOUBLE_EQ(0.0, d1(2,2));

    matrix::Euler<double> e2(angle1, angle2, angle3, RotationSequence::XYX_121);
    matrix::DCM<double> d2(e2);
    // EXPECT_DOUBLE_EQ(0.0, d2(0,0));
    // EXPECT_DOUBLE_EQ(0.0, d2(0,1));
    // EXPECT_DOUBLE_EQ(0.0, d2(0,2));
    // EXPECT_DOUBLE_EQ(0.0, d2(1,0));
    // EXPECT_DOUBLE_EQ(0.0, d2(1,1));
    // EXPECT_DOUBLE_EQ(0.0, d2(1,2));
    // EXPECT_DOUBLE_EQ(0.0, d2(2,0));
    // EXPECT_DOUBLE_EQ(0.0, d2(2,1));
    // EXPECT_DOUBLE_EQ(0.0, d2(2,2));

    matrix::Euler<double> e3(angle1, angle2, angle3, RotationSequence::YZY_232);
    matrix::DCM<double> d3(e3);
    // EXPECT_DOUBLE_EQ(0.0, d3(0,0));
    // EXPECT_DOUBLE_EQ(0.0, d3(0,1));
    // EXPECT_DOUBLE_EQ(0.0, d3(0,2));
    // EXPECT_DOUBLE_EQ(0.0, d3(1,0));
    // EXPECT_DOUBLE_EQ(0.0, d3(1,1));
    // EXPECT_DOUBLE_EQ(0.0, d3(1,2));
    // EXPECT_DOUBLE_EQ(0.0, d3(2,0));
    // EXPECT_DOUBLE_EQ(0.0, d3(2,1));
    // EXPECT_DOUBLE_EQ(0.0, d3(2,2));

    matrix::Euler<double> e4(angle1, angle2, angle3, RotationSequence::ZYZ_323);
    matrix::DCM<double> d4(e4);
    EXPECT_DOUBLE_EQ(0.41593717755472648, d4(0,0));
    EXPECT_DOUBLE_EQ(0.69278646414614875, d4(0,1));
    EXPECT_DOUBLE_EQ(0.58910370854687788, d4(0,2));
    EXPECT_DOUBLE_EQ(-0.90135763924193235, d4(1,0));
    EXPECT_DOUBLE_EQ(0.22813884797452991, d4(1,1));
    EXPECT_DOUBLE_EQ(0.36811285256706888, d4(1,2));
    EXPECT_DOUBLE_EQ(0.12062616013128424, d4(2,0));
    EXPECT_DOUBLE_EQ(-0.68410494892284712, d4(2,1));
    EXPECT_DOUBLE_EQ(0.71933980033865119, d4(2,2));

    matrix::Euler<double> e5(angle1, angle2, angle3, RotationSequence::XZX_131);
    matrix::DCM<double> d5(e5);
    // EXPECT_DOUBLE_EQ(0.0, d5(0,0));
    // EXPECT_DOUBLE_EQ(0.0, d5(0,1));
    // EXPECT_DOUBLE_EQ(0.0, d5(0,2));
    // EXPECT_DOUBLE_EQ(0.0, d5(1,0));
    // EXPECT_DOUBLE_EQ(0.0, d5(1,1));
    // EXPECT_DOUBLE_EQ(0.0, d5(1,2));
    // EXPECT_DOUBLE_EQ(0.0, d5(2,0));
    // EXPECT_DOUBLE_EQ(0.0, d5(2,1));
    // EXPECT_DOUBLE_EQ(0.0, d5(2,2));

    matrix::Euler<double> e6(angle1, angle2, angle3, RotationSequence::YXY_212);
    matrix::DCM<double> d6(e6);
    // EXPECT_DOUBLE_EQ(0.0, d6(0,0));
    // EXPECT_DOUBLE_EQ(0.0, d6(0,1));
    // EXPECT_DOUBLE_EQ(0.0, d6(0,2));
    // EXPECT_DOUBLE_EQ(0.0, d6(1,0));
    // EXPECT_DOUBLE_EQ(0.0, d6(1,1));
    // EXPECT_DOUBLE_EQ(0.0, d6(1,2));
    // EXPECT_DOUBLE_EQ(0.0, d6(2,0));
    // EXPECT_DOUBLE_EQ(0.0, d6(2,1));
    // EXPECT_DOUBLE_EQ(0.0, d6(2,2));

    matrix::Euler<double> e7(angle1, angle2, angle3, RotationSequence::XYZ_123);
    matrix::DCM<double> d7(e7);
    // EXPECT_DOUBLE_EQ(0.0, d7(0,0));
    // EXPECT_DOUBLE_EQ(0.0, d7(0,1));
    // EXPECT_DOUBLE_EQ(0.0, d7(0,2));
    // EXPECT_DOUBLE_EQ(0.0, d7(1,0));
    // EXPECT_DOUBLE_EQ(0.0, d7(1,1));
    // EXPECT_DOUBLE_EQ(0.0, d7(1,2));
    // EXPECT_DOUBLE_EQ(0.0, d7(2,0));
    // EXPECT_DOUBLE_EQ(0.0, d7(2,1));
    // EXPECT_DOUBLE_EQ(0.0, d7(2,2));

    matrix::Euler<double> e8(angle1, angle2, angle3, RotationSequence::YZX_231);
    matrix::DCM<double> d8(e8);
    // EXPECT_DOUBLE_EQ(0.0, d8(0,0));
    // EXPECT_DOUBLE_EQ(0.0, d8(0,1));
    // EXPECT_DOUBLE_EQ(0.0, d8(0,2));
    // EXPECT_DOUBLE_EQ(0.0, d8(1,0));
    // EXPECT_DOUBLE_EQ(0.0, d8(1,1));
    // EXPECT_DOUBLE_EQ(0.0, d8(1,2));
    // EXPECT_DOUBLE_EQ(0.0, d8(2,0));
    // EXPECT_DOUBLE_EQ(0.0, d8(2,1));
    // EXPECT_DOUBLE_EQ(0.0, d8(2,2));

    matrix::Euler<double> e9(angle1, angle2, angle3, RotationSequence::ZXY_312);
    matrix::DCM<double> d9(e9);
    // EXPECT_DOUBLE_EQ(0.0, d9(0,0));
    // EXPECT_DOUBLE_EQ(0.0, d9(0,1));
    // EXPECT_DOUBLE_EQ(0.0, d9(0,2));
    // EXPECT_DOUBLE_EQ(0.0, d9(1,0));
    // EXPECT_DOUBLE_EQ(0.0, d9(1,1));
    // EXPECT_DOUBLE_EQ(0.0, d9(1,2));
    // EXPECT_DOUBLE_EQ(0.0, d9(2,0));
    // EXPECT_DOUBLE_EQ(0.0, d9(2,1));
    // EXPECT_DOUBLE_EQ(0.0, d9(2,2));

    matrix::Euler<double> e10(angle1, angle2, angle3, RotationSequence::XZY_132);
    matrix::DCM<double> d10(e10);
    // EXPECT_DOUBLE_EQ(0.0, d10(0,0));
    // EXPECT_DOUBLE_EQ(0.0, d10(0,1));
    // EXPECT_DOUBLE_EQ(0.0, d10(0,2));
    // EXPECT_DOUBLE_EQ(0.0, d10(1,0));
    // EXPECT_DOUBLE_EQ(0.0, d10(1,1));
    // EXPECT_DOUBLE_EQ(0.0, d10(1,2));
    // EXPECT_DOUBLE_EQ(0.0, d10(2,0));
    // EXPECT_DOUBLE_EQ(0.0, d10(2,1));
    // EXPECT_DOUBLE_EQ(0.0, d10(2,2));
    
    matrix::Euler<double> e11(angle1, angle2, angle3, RotationSequence::ZYX_321);
    matrix::DCM<double> d11(e11);
    EXPECT_DOUBLE_EQ(0.61003474816673675, d11(0,0));
    EXPECT_DOUBLE_EQ(-0.48813438496051292, d11(0,1));
    EXPECT_DOUBLE_EQ(-0.62416538533338084, d11(0,2));
    EXPECT_DOUBLE_EQ(0.38119201772911854, d11(1,0));
    EXPECT_DOUBLE_EQ(-0.50978239766296241, d11(1,1));
    EXPECT_DOUBLE_EQ(0.77124221399804382, d11(1,2));
    EXPECT_DOUBLE_EQ(-0.69465837045899725, d11(2,0));
    EXPECT_DOUBLE_EQ(-0.70841141242375738, d11(2,1));
    EXPECT_DOUBLE_EQ(-0.12491204545210027, d11(2,2));

    matrix::Euler<double> e12(angle1, angle2, angle3, RotationSequence::YXZ_213);
    matrix::DCM<double> d12(e12);
    // EXPECT_DOUBLE_EQ(0.0, d12(0,0));
    // EXPECT_DOUBLE_EQ(0.0, d12(0,1));
    // EXPECT_DOUBLE_EQ(0.0, d12(0,2));
    // EXPECT_DOUBLE_EQ(0.0, d12(1,0));
    // EXPECT_DOUBLE_EQ(0.0, d12(1,1));
    // EXPECT_DOUBLE_EQ(0.0, d12(1,2));
    // EXPECT_DOUBLE_EQ(0.0, d12(2,0));
    // EXPECT_DOUBLE_EQ(0.0, d12(2,1));
    // EXPECT_DOUBLE_EQ(0.0, d12(2,2));
}