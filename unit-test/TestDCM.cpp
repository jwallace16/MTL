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