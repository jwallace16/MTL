///////////////////////////////////////////////////////////////////////////////
//!
//! @file TestQuaternion.cpp
//!
//! Unit test for Quaternion.hpp
//!
//! @author David Wallace <jdavidwallace1@gmail.com>
///////////////////////////////////////////////////////////////////////////////

#include <iostream>
#include <gtest/gtest.h>
#include "../src/Quaternion.hpp"
#include "../src/DCM.hpp"

TEST(QuaternionTestSuite, TestDefaultConstructor)
{
    matrix::Quaternion<double> q;
    EXPECT_DOUBLE_EQ(1.0, q(0));
    EXPECT_DOUBLE_EQ(0.0, q(1));
    EXPECT_DOUBLE_EQ(0.0, q(2));
    EXPECT_DOUBLE_EQ(0.0, q(3));
}

TEST(QuaternionTestSuite, TestFlatArrayConstructor)
{
    double vals[4] = {0.0, 1.0, 0.0, 0.0};
    matrix::Quaternion<double> q(vals);
    EXPECT_DOUBLE_EQ(0.0, q(0));
    EXPECT_DOUBLE_EQ(1.0, q(1));
    EXPECT_DOUBLE_EQ(0.0, q(2));
    EXPECT_DOUBLE_EQ(0.0, q(3));
}

TEST(QuaternionTestSuite, TestIndividualValuesConstructor)
{
    matrix::Quaternion<double> q(0.5, 0.5, 0.5, 0.5);
    EXPECT_DOUBLE_EQ(0.5, q(0));
    EXPECT_DOUBLE_EQ(0.5, q(1));
    EXPECT_DOUBLE_EQ(0.5, q(2));
    EXPECT_DOUBLE_EQ(0.5, q(3));
}

TEST(QuaternionTestSuite, TestInitializerListConstructor)
{
    matrix::Quaternion<double> q = {0.0, 0.0, -1.0, 0.0};
    EXPECT_DOUBLE_EQ(0.0, q(0));
    EXPECT_DOUBLE_EQ(0.0, q(1));
    EXPECT_DOUBLE_EQ(-1.0, q(2));
    EXPECT_DOUBLE_EQ(0.0, q(3));
}

TEST(QuaternionTestSuite, TestVector3AndAngleConstructor)
{
    matrix::Vector3<double> v1(0.5, 0.5, 0.5);
    matrix::Quaternion<double> q4(v1, 30.0);
    // EXPECT_DOUBLE_EQ(0.5, q4(0));
    // EXPECT_DOUBLE_EQ(0.5, q4(1));
    // EXPECT_DOUBLE_EQ(0.5, q4(2));
    // EXPECT_DOUBLE_EQ(0.5, q4(3));
}

TEST(QuaternionTestSuite, TestQuaternionConstructorEulerAngles)
{
    //
}

TEST(QuaternionTestSuite, TestQuaternionConstructorDCMx)
{
    // ----------
    // 0 degree rotation about x
    double xangle = 0.0;
    double yangle = 0.0;
    double zangle = 0.0;
    double rxvals0[3][3] = {{1.0, 0.0, 0.0}, {0.0, std::cos(xangle), -std::sin(xangle)}, {0.0, std::sin(xangle), std::cos(xangle)}};
    matrix::SquareMatrix<double, 3> Rx0(rxvals0);

    double ryvals0[3][3] = {{std::cos(yangle), 0.0, std::sin(yangle)}, {0.0, 1.0, 0.0}, {-std::sin(yangle), 0.0, std::cos(yangle)}};
    matrix::SquareMatrix<double, 3> Ry0(ryvals0);

    double rzvals0[3][3] = {{std::cos(zangle), -std::sin(zangle), 0.0}, {std::sin(zangle), std::cos(zangle), 0.0}, {0.0, 0.0, 1.0}};
    matrix::SquareMatrix<double, 3> Rz0(rzvals0);
    matrix::DCM<double> dcm0 = Rz0 * Ry0 * Rx0;
    matrix::Quaternion<double> q0(dcm0);
    EXPECT_NEAR(1.0, q0(0), 1.0e-15);
    EXPECT_NEAR(0.0, q0(1), 1.0e-15);
    EXPECT_NEAR(0.0, q0(2), 1.0e-15);
    EXPECT_NEAR(0.0, q0(3), 1.0e-15);

    // ----------
    // 90 degree rotation about x
    xangle = 0.5*M_PI;
    double rxvals1[3][3] = {{1.0, 0.0, 0.0}, {0.0, std::cos(xangle), -std::sin(xangle)}, {0.0, std::sin(xangle), std::cos(xangle)}};
    matrix::SquareMatrix<double, 3> Rx1(rxvals1);

    double ryvals1[3][3] = {{std::cos(yangle), 0.0, std::sin(yangle)}, {0.0, 1.0, 0.0}, {-std::sin(yangle), 0.0, std::cos(yangle)}};
    matrix::SquareMatrix<double, 3> Ry1(ryvals1);

    double rzvals1[3][3] = {{std::cos(zangle), -std::sin(zangle), 0.0}, {std::sin(zangle), std::cos(zangle), 0.0}, {0.0, 0.0, 1.0}};
    matrix::SquareMatrix<double, 3> Rz1(rzvals1);
    matrix::DCM<double> dcm1 = Rz1 * Ry1 * Rx1;
    matrix::Quaternion<double> q1(dcm1);
    EXPECT_NEAR(1.0/std::sqrt(2.0), q1(0), 1.0e-15);
    EXPECT_NEAR(1.0/std::sqrt(2.0), q1(1), 1.0e-15);
    EXPECT_NEAR(0.0, q1(2), 1.0e-15);
    EXPECT_NEAR(0.0, q1(3), 1.0e-15);

    // ----------
    // 180 degree rotation about x
    xangle = 1.0*M_PI;
    double rxvals2[3][3] = {{1.0, 0.0, 0.0}, {0.0, std::cos(xangle), -std::sin(xangle)}, {0.0, std::sin(xangle), std::cos(xangle)}};
    matrix::SquareMatrix<double, 3> Rx2(rxvals2);

    double ryvals2[3][3] = {{std::cos(yangle), 0.0, std::sin(yangle)}, {0.0, 1.0, 0.0}, {-std::sin(yangle), 0.0, std::cos(yangle)}};
    matrix::SquareMatrix<double, 3> Ry2(ryvals2);

    double rzvals2[3][3] = {{std::cos(zangle), -std::sin(zangle), 0.0}, {std::sin(zangle), std::cos(zangle), 0.0}, {0.0, 0.0, 1.0}};
    matrix::SquareMatrix<double, 3> Rz2(rzvals2);
    matrix::DCM<double> dcm2 = Rz2 * Ry2 * Rx2;
    matrix::Quaternion<double> q2(dcm2);
    EXPECT_NEAR(0.0, q2(0), 1.0e-15);
    EXPECT_NEAR(1.0, q2(1), 1.0e-15);
    EXPECT_NEAR(0.0, q2(2), 1.0e-15);
    EXPECT_NEAR(0.0, q2(3), 1.0e-15);

    // ----------
    // 270 degree rotation about x
    xangle = 1.5*M_PI;
    double rxvals3[3][3] = {{1.0, 0.0, 0.0}, {0.0, std::cos(xangle), -std::sin(xangle)}, {0.0, std::sin(xangle), std::cos(xangle)}};
    matrix::SquareMatrix<double, 3> Rx3(rxvals3);

    double ryvals3[3][3] = {{std::cos(yangle), 0.0, std::sin(yangle)}, {0.0, 1.0, 0.0}, {-std::sin(yangle), 0.0, std::cos(yangle)}};
    matrix::SquareMatrix<double, 3> Ry3(ryvals3);

    double rzvals3[3][3] = {{std::cos(zangle), -std::sin(zangle), 0.0}, {std::sin(zangle), std::cos(zangle), 0.0}, {0.0, 0.0, 1.0}};
    matrix::SquareMatrix<double, 3> Rz3(rzvals3);
    matrix::DCM<double> dcm3 = Rz3 * Ry3 * Rx3;
    matrix::Quaternion<double> q3(dcm3);
    EXPECT_NEAR(1.0/std::sqrt(2.0), q3(0), 1.0e-15);
    EXPECT_NEAR(-1.0/std::sqrt(2.0), q3(1), 1.0e-15);
    EXPECT_NEAR(0.0, q3(2), 1.0e-15);
    EXPECT_NEAR(0.0, q3(3), 1.0e-15);

    // ----------
    // 360 degree rotation about x
    xangle = 2.0*M_PI;
    double rxvals4[3][3] = {{1.0, 0.0, 0.0}, {0.0, std::cos(xangle), -std::sin(xangle)}, {0.0, std::sin(xangle), std::cos(xangle)}};
    matrix::SquareMatrix<double, 3> Rx4(rxvals4);

    double ryvals4[3][3] = {{std::cos(yangle), 0.0, std::sin(yangle)}, {0.0, 1.0, 0.0}, {-std::sin(yangle), 0.0, std::cos(yangle)}};
    matrix::SquareMatrix<double, 3> Ry4(ryvals4);

    double rzvals4[3][3] = {{std::cos(zangle), -std::sin(zangle), 0.0}, {std::sin(zangle), std::cos(zangle), 0.0}, {0.0, 0.0, 1.0}};
    matrix::SquareMatrix<double, 3> Rz4(rzvals4);
    matrix::DCM<double> dcm4 = Rz4 * Ry4 * Rx4;
    matrix::Quaternion<double> q4(dcm4);
    EXPECT_NEAR(1.0, q4(0), 1.0e-15);
    EXPECT_NEAR(0.0, q4(1), 1.0e-15);
    EXPECT_NEAR(0.0, q4(2), 1.0e-15);
    EXPECT_NEAR(0.0, q4(3), 1.0e-15);

    // ----------
    // -90 degree rotation about x
    xangle = -0.5*M_PI;
    double rxvals5[3][3] = {{1.0, 0.0, 0.0}, {0.0, std::cos(xangle), -std::sin(xangle)}, {0.0, std::sin(xangle), std::cos(xangle)}};
    matrix::SquareMatrix<double, 3> Rx5(rxvals5);

    double ryvals5[3][3] = {{std::cos(yangle), 0.0, std::sin(yangle)}, {0.0, 1.0, 0.0}, {-std::sin(yangle), 0.0, std::cos(yangle)}};
    matrix::SquareMatrix<double, 3> Ry5(ryvals5);

    double rzvals5[3][3] = {{std::cos(zangle), -std::sin(zangle), 0.0}, {std::sin(zangle), std::cos(zangle), 0.0}, {0.0, 0.0, 1.0}};
    matrix::SquareMatrix<double, 3> Rz5(rzvals5);
    matrix::DCM<double> dcm5 = Rz5 * Ry5 * Rx5;
    matrix::Quaternion<double> q5(dcm5);
    EXPECT_NEAR(1.0/std::sqrt(2.0), q5(0), 1.0e-15);
    EXPECT_NEAR(-1.0/std::sqrt(2.0), q5(1), 1.0e-15);
    EXPECT_NEAR(0.0, q5(2), 1.0e-15);
    EXPECT_NEAR(0.0, q5(3), 1.0e-15);

    // ----------
    // -180 degree rotation about x
    xangle = -1.0*M_PI;
    double rxvals6[3][3] = {{1.0, 0.0, 0.0}, {0.0, std::cos(xangle), -std::sin(xangle)}, {0.0, std::sin(xangle), std::cos(xangle)}};
    matrix::SquareMatrix<double, 3> Rx6(rxvals6);

    double ryvals6[3][3] = {{std::cos(yangle), 0.0, std::sin(yangle)}, {0.0, 1.0, 0.0}, {-std::sin(yangle), 0.0, std::cos(yangle)}};
    matrix::SquareMatrix<double, 3> Ry6(ryvals6);

    double rzvals6[3][3] = {{std::cos(zangle), -std::sin(zangle), 0.0}, {std::sin(zangle), std::cos(zangle), 0.0}, {0.0, 0.0, 1.0}};
    matrix::SquareMatrix<double, 3> Rz6(rzvals6);
    matrix::DCM<double> dcm6 = Rz6 * Ry6 * Rx6;
    matrix::Quaternion<double> q6(dcm6);
    EXPECT_NEAR(0.0, q6(0), 1.0e-15);
    EXPECT_NEAR(1.0, q6(1), 1.0e-15);
    EXPECT_NEAR(0.0, q6(2), 1.0e-15);
    EXPECT_NEAR(0.0, q6(3), 1.0e-15);

    // ----------
    // -270 degree rotation about x
    xangle = -1.5*M_PI;
    double rxvals7[3][3] = {{1.0, 0.0, 0.0}, {0.0, std::cos(xangle), -std::sin(xangle)}, {0.0, std::sin(xangle), std::cos(xangle)}};
    matrix::SquareMatrix<double, 3> Rx7(rxvals7);

    double ryvals7[3][3] = {{std::cos(yangle), 0.0, std::sin(yangle)}, {0.0, 1.0, 0.0}, {-std::sin(yangle), 0.0, std::cos(yangle)}};
    matrix::SquareMatrix<double, 3> Ry7(ryvals7);

    double rzvals7[3][3] = {{std::cos(zangle), -std::sin(zangle), 0.0}, {std::sin(zangle), std::cos(zangle), 0.0}, {0.0, 0.0, 1.0}};
    matrix::SquareMatrix<double, 3> Rz7(rzvals7);
    matrix::DCM<double> dcm7 = Rz7 * Ry7 * Rx7;
    matrix::Quaternion<double> q7(dcm7);
    EXPECT_NEAR(1.0/std::sqrt(2.0), q7(0), 1.0e-15);
    EXPECT_NEAR(1.0/std::sqrt(2.0), q7(1), 1.0e-15);
    EXPECT_NEAR(0.0, q7(2), 1.0e-15);
    EXPECT_NEAR(0.0, q7(3), 1.0e-15);
}

TEST(QuaternionTestSuite, TestQuaternionConstructorDCMy)
{
    // ----------
    // 0 degree rotation about y
    double xangle = 0.0;
    double yangle = 0.0;
    double zangle = 0.0;
    double rxvals0[3][3] = {{1.0, 0.0, 0.0}, {0.0, std::cos(xangle), -std::sin(xangle)}, {0.0, std::sin(xangle), std::cos(xangle)}};
    matrix::SquareMatrix<double, 3> Rx0(rxvals0);

    double ryvals0[3][3] = {{std::cos(yangle), 0.0, std::sin(yangle)}, {0.0, 1.0, 0.0}, {-std::sin(yangle), 0.0, std::cos(yangle)}};
    matrix::SquareMatrix<double, 3> Ry0(ryvals0);

    double rzvals0[3][3] = {{std::cos(zangle), -std::sin(zangle), 0.0}, {std::sin(zangle), std::cos(zangle), 0.0}, {0.0, 0.0, 1.0}};
    matrix::SquareMatrix<double, 3> Rz0(rzvals0);
    matrix::DCM<double> dcm0 = Rz0 * Ry0 * Rx0;
    matrix::Quaternion<double> q0(dcm0);
    EXPECT_NEAR(1.0, q0(0), 1.0e-15);
    EXPECT_NEAR(0.0, q0(1), 1.0e-15);
    EXPECT_NEAR(0.0, q0(2), 1.0e-15);
    EXPECT_NEAR(0.0, q0(3), 1.0e-15);

    // ----------
    // 90 degree rotation about y
    yangle = 0.5*M_PI;
    double rxvals1[3][3] = {{1.0, 0.0, 0.0}, {0.0, std::cos(xangle), -std::sin(xangle)}, {0.0, std::sin(xangle), std::cos(xangle)}};
    matrix::SquareMatrix<double, 3> Rx1(rxvals1);

    double ryvals1[3][3] = {{std::cos(yangle), 0.0, std::sin(yangle)}, {0.0, 1.0, 0.0}, {-std::sin(yangle), 0.0, std::cos(yangle)}};
    matrix::SquareMatrix<double, 3> Ry1(ryvals1);

    double rzvals1[3][3] = {{std::cos(zangle), -std::sin(zangle), 0.0}, {std::sin(zangle), std::cos(zangle), 0.0}, {0.0, 0.0, 1.0}};
    matrix::SquareMatrix<double, 3> Rz1(rzvals1);
    matrix::DCM<double> dcm1 = Rz1 * Ry1 * Rx1;
    matrix::Quaternion<double> q1(dcm1);
    EXPECT_NEAR(1.0/std::sqrt(2.0), q1(0), 1.0e-15);
    EXPECT_NEAR(0.0, q1(1), 1.0e-15);
    EXPECT_NEAR(1.0/std::sqrt(2.0), q1(2), 1.0e-15);
    EXPECT_NEAR(0.0, q1(3), 1.0e-15);

    // ----------
    // 180 degree rotation about y
    yangle = 1.0*M_PI;
    double rxvals2[3][3] = {{1.0, 0.0, 0.0}, {0.0, std::cos(xangle), -std::sin(xangle)}, {0.0, std::sin(xangle), std::cos(xangle)}};
    matrix::SquareMatrix<double, 3> Rx2(rxvals2);

    double ryvals2[3][3] = {{std::cos(yangle), 0.0, std::sin(yangle)}, {0.0, 1.0, 0.0}, {-std::sin(yangle), 0.0, std::cos(yangle)}};
    matrix::SquareMatrix<double, 3> Ry2(ryvals2);

    double rzvals2[3][3] = {{std::cos(zangle), -std::sin(zangle), 0.0}, {std::sin(zangle), std::cos(zangle), 0.0}, {0.0, 0.0, 1.0}};
    matrix::SquareMatrix<double, 3> Rz2(rzvals2);
    matrix::DCM<double> dcm2 = Rz2 * Ry2 * Rx2;
    matrix::Quaternion<double> q2(dcm2);
    EXPECT_NEAR(0.0, q2(0), 1.0e-15);
    EXPECT_NEAR(0.0, q2(1), 1.0e-15);
    EXPECT_NEAR(1.0, q2(2), 1.0e-15);
    EXPECT_NEAR(0.0, q2(3), 1.0e-15);

    // ----------
    // 270 degree rotation about y
    yangle = 1.5*M_PI;
    double rxvals3[3][3] = {{1.0, 0.0, 0.0}, {0.0, std::cos(xangle), -std::sin(xangle)}, {0.0, std::sin(xangle), std::cos(xangle)}};
    matrix::SquareMatrix<double, 3> Rx3(rxvals3);

    double ryvals3[3][3] = {{std::cos(yangle), 0.0, std::sin(yangle)}, {0.0, 1.0, 0.0}, {-std::sin(yangle), 0.0, std::cos(yangle)}};
    matrix::SquareMatrix<double, 3> Ry3(ryvals3);

    double rzvals3[3][3] = {{std::cos(zangle), -std::sin(zangle), 0.0}, {std::sin(zangle), std::cos(zangle), 0.0}, {0.0, 0.0, 1.0}};
    matrix::SquareMatrix<double, 3> Rz3(rzvals3);
    matrix::DCM<double> dcm3 = Rz3 * Ry3 * Rx3;
    matrix::Quaternion<double> q3(dcm3);
    EXPECT_NEAR(1.0/std::sqrt(2.0), q3(0), 1.0e-15);
    EXPECT_NEAR(0.0, q3(1), 1.0e-15);
    EXPECT_NEAR(-1.0/std::sqrt(2.0), q3(2), 1.0e-15);
    EXPECT_NEAR(0.0, q3(3), 1.0e-15);

    // ----------
    // 360 degree rotation about y
    yangle = 2.0*M_PI;
    double rxvals4[3][3] = {{1.0, 0.0, 0.0}, {0.0, std::cos(xangle), -std::sin(xangle)}, {0.0, std::sin(xangle), std::cos(xangle)}};
    matrix::SquareMatrix<double, 3> Rx4(rxvals4);

    double ryvals4[3][3] = {{std::cos(yangle), 0.0, std::sin(yangle)}, {0.0, 1.0, 0.0}, {-std::sin(yangle), 0.0, std::cos(yangle)}};
    matrix::SquareMatrix<double, 3> Ry4(ryvals4);

    double rzvals4[3][3] = {{std::cos(zangle), -std::sin(zangle), 0.0}, {std::sin(zangle), std::cos(zangle), 0.0}, {0.0, 0.0, 1.0}};
    matrix::SquareMatrix<double, 3> Rz4(rzvals4);
    matrix::DCM<double> dcm4 = Rz4 * Ry4 * Rx4;
    matrix::Quaternion<double> q4(dcm4);
    EXPECT_NEAR(1.0, q4(0), 1.0e-15);
    EXPECT_NEAR(0.0, q4(1), 1.0e-15);
    EXPECT_NEAR(0.0, q4(2), 1.0e-15);
    EXPECT_NEAR(0.0, q4(3), 1.0e-15);

    // ----------
    // -90 degree rotation about y
    yangle = -0.5*M_PI;
    double rxvals5[3][3] = {{1.0, 0.0, 0.0}, {0.0, std::cos(xangle), -std::sin(xangle)}, {0.0, std::sin(xangle), std::cos(xangle)}};
    matrix::SquareMatrix<double, 3> Rx5(rxvals5);

    double ryvals5[3][3] = {{std::cos(yangle), 0.0, std::sin(yangle)}, {0.0, 1.0, 0.0}, {-std::sin(yangle), 0.0, std::cos(yangle)}};
    matrix::SquareMatrix<double, 3> Ry5(ryvals5);

    double rzvals5[3][3] = {{std::cos(zangle), -std::sin(zangle), 0.0}, {std::sin(zangle), std::cos(zangle), 0.0}, {0.0, 0.0, 1.0}};
    matrix::SquareMatrix<double, 3> Rz5(rzvals5);
    matrix::DCM<double> dcm5 = Rz5 * Ry5 * Rx5;
    matrix::Quaternion<double> q5(dcm5);
    EXPECT_NEAR(1.0/std::sqrt(2.0), q5(0), 1.0e-15);
    EXPECT_NEAR(0.0, q5(1), 1.0e-15);
    EXPECT_NEAR(-1.0/std::sqrt(2.0), q5(2), 1.0e-15);
    EXPECT_NEAR(0.0, q5(3), 1.0e-15);

    // ----------
    // -180 degree rotation about y
    yangle = -1.0*M_PI;
    double rxvals6[3][3] = {{1.0, 0.0, 0.0}, {0.0, std::cos(xangle), -std::sin(xangle)}, {0.0, std::sin(xangle), std::cos(xangle)}};
    matrix::SquareMatrix<double, 3> Rx6(rxvals6);

    double ryvals6[3][3] = {{std::cos(yangle), 0.0, std::sin(yangle)}, {0.0, 1.0, 0.0}, {-std::sin(yangle), 0.0, std::cos(yangle)}};
    matrix::SquareMatrix<double, 3> Ry6(ryvals6);

    double rzvals6[3][3] = {{std::cos(zangle), -std::sin(zangle), 0.0}, {std::sin(zangle), std::cos(zangle), 0.0}, {0.0, 0.0, 1.0}};
    matrix::SquareMatrix<double, 3> Rz6(rzvals6);
    matrix::DCM<double> dcm6 = Rz6 * Ry6 * Rx6;
    matrix::Quaternion<double> q6(dcm6);
    EXPECT_NEAR(0.0, q6(0), 1.0e-15);
    EXPECT_NEAR(0.0, q6(1), 1.0e-15);
    EXPECT_NEAR(1.0, q6(2), 1.0e-15);
    EXPECT_NEAR(0.0, q6(3), 1.0e-15);

    // ----------
    // -270 degree rotation about y
    yangle = -1.5*M_PI;
    double rxvals7[3][3] = {{1.0, 0.0, 0.0}, {0.0, std::cos(xangle), -std::sin(xangle)}, {0.0, std::sin(xangle), std::cos(xangle)}};
    matrix::SquareMatrix<double, 3> Rx7(rxvals7);

    double ryvals7[3][3] = {{std::cos(yangle), 0.0, std::sin(yangle)}, {0.0, 1.0, 0.0}, {-std::sin(yangle), 0.0, std::cos(yangle)}};
    matrix::SquareMatrix<double, 3> Ry7(ryvals7);

    double rzvals7[3][3] = {{std::cos(zangle), -std::sin(zangle), 0.0}, {std::sin(zangle), std::cos(zangle), 0.0}, {0.0, 0.0, 1.0}};
    matrix::SquareMatrix<double, 3> Rz7(rzvals7);
    matrix::DCM<double> dcm7 = Rz7 * Ry7 * Rx7;
    matrix::Quaternion<double> q7(dcm7);
    EXPECT_NEAR(1.0/std::sqrt(2.0), q7(0), 1.0e-15);
    EXPECT_NEAR(0.0, q7(1), 1.0e-15);
    EXPECT_NEAR(1.0/std::sqrt(2.0), q7(2), 1.0e-15);
    EXPECT_NEAR(0.0, q7(3), 1.0e-15);
}

TEST(QuaternionTestSuite, TestQuaternionConstructorDCMz)
{
    // ----------
    // 0 degree rotation about z
    double xangle = 0.0;
    double yangle = 0.0;
    double zangle = 0.0;
    double rxvals0[3][3] = {{1.0, 0.0, 0.0}, {0.0, std::cos(xangle), -std::sin(xangle)}, {0.0, std::sin(xangle), std::cos(xangle)}};
    matrix::SquareMatrix<double, 3> Rx0(rxvals0);

    double ryvals0[3][3] = {{std::cos(yangle), 0.0, std::sin(yangle)}, {0.0, 1.0, 0.0}, {-std::sin(yangle), 0.0, std::cos(yangle)}};
    matrix::SquareMatrix<double, 3> Ry0(ryvals0);

    double rzvals0[3][3] = {{std::cos(zangle), -std::sin(zangle), 0.0}, {std::sin(zangle), std::cos(zangle), 0.0}, {0.0, 0.0, 1.0}};
    matrix::SquareMatrix<double, 3> Rz0(rzvals0);
    matrix::DCM<double> dcm0 = Rz0 * Ry0 * Rx0;
    matrix::Quaternion<double> q0(dcm0);
    EXPECT_NEAR(1.0, q0(0), 1.0e-15);
    EXPECT_NEAR(0.0, q0(1), 1.0e-15);
    EXPECT_NEAR(0.0, q0(2), 1.0e-15);
    EXPECT_NEAR(0.0, q0(3), 1.0e-15);

    // ----------
    // 90 degree rotation about z
    zangle = 0.5*M_PI;
    double rxvals1[3][3] = {{1.0, 0.0, 0.0}, {0.0, std::cos(xangle), -std::sin(xangle)}, {0.0, std::sin(xangle), std::cos(xangle)}};
    matrix::SquareMatrix<double, 3> Rx1(rxvals1);

    double ryvals1[3][3] = {{std::cos(yangle), 0.0, std::sin(yangle)}, {0.0, 1.0, 0.0}, {-std::sin(yangle), 0.0, std::cos(yangle)}};
    matrix::SquareMatrix<double, 3> Ry1(ryvals1);

    double rzvals1[3][3] = {{std::cos(zangle), -std::sin(zangle), 0.0}, {std::sin(zangle), std::cos(zangle), 0.0}, {0.0, 0.0, 1.0}};
    matrix::SquareMatrix<double, 3> Rz1(rzvals1);
    matrix::DCM<double> dcm1 = Rz1 * Ry1 * Rx1;
    matrix::Quaternion<double> q1(dcm1);
    EXPECT_NEAR(1.0/std::sqrt(2.0), q1(0), 1.0e-15);
    EXPECT_NEAR(0.0, q1(1), 1.0e-15);
    EXPECT_NEAR(0.0, q1(2), 1.0e-15);
    EXPECT_NEAR(1.0/std::sqrt(2.0), q1(3), 1.0e-15);

    // ----------
    // 180 degree rotation about z
    zangle = 1.0*M_PI;
    double rxvals2[3][3] = {{1.0, 0.0, 0.0}, {0.0, std::cos(xangle), -std::sin(xangle)}, {0.0, std::sin(xangle), std::cos(xangle)}};
    matrix::SquareMatrix<double, 3> Rx2(rxvals2);

    double ryvals2[3][3] = {{std::cos(yangle), 0.0, std::sin(yangle)}, {0.0, 1.0, 0.0}, {-std::sin(yangle), 0.0, std::cos(yangle)}};
    matrix::SquareMatrix<double, 3> Ry2(ryvals2);

    double rzvals2[3][3] = {{std::cos(zangle), -std::sin(zangle), 0.0}, {std::sin(zangle), std::cos(zangle), 0.0}, {0.0, 0.0, 1.0}};
    matrix::SquareMatrix<double, 3> Rz2(rzvals2);
    matrix::DCM<double> dcm2 = Rz2 * Ry2 * Rx2;
    matrix::Quaternion<double> q2(dcm2);
    EXPECT_NEAR(0.0, q2(0), 1.0e-15);
    EXPECT_NEAR(0.0, q2(1), 1.0e-15);
    EXPECT_NEAR(0.0, q2(2), 1.0e-15);
    EXPECT_NEAR(1.0, q2(3), 1.0e-15);

    // ----------
    // 270 degree rotation about z
    zangle = 1.5*M_PI;
    double rxvals3[3][3] = {{1.0, 0.0, 0.0}, {0.0, std::cos(xangle), -std::sin(xangle)}, {0.0, std::sin(xangle), std::cos(xangle)}};
    matrix::SquareMatrix<double, 3> Rx3(rxvals3);

    double ryvals3[3][3] = {{std::cos(yangle), 0.0, std::sin(yangle)}, {0.0, 1.0, 0.0}, {-std::sin(yangle), 0.0, std::cos(yangle)}};
    matrix::SquareMatrix<double, 3> Ry3(ryvals3);

    double rzvals3[3][3] = {{std::cos(zangle), -std::sin(zangle), 0.0}, {std::sin(zangle), std::cos(zangle), 0.0}, {0.0, 0.0, 1.0}};
    matrix::SquareMatrix<double, 3> Rz3(rzvals3);
    matrix::DCM<double> dcm3 = Rz3 * Ry3 * Rx3;
    matrix::Quaternion<double> q3(dcm3);
    EXPECT_NEAR(1.0/std::sqrt(2.0), q3(0), 1.0e-15);
    EXPECT_NEAR(0.0, q3(1), 1.0e-15);
    EXPECT_NEAR(0.0, q3(2), 1.0e-15);
    EXPECT_NEAR(-1.0/std::sqrt(2.0), q3(3), 1.0e-15);

    // ----------
    // 360 degree rotation about z
    zangle = 2.0*M_PI;
    double rxvals4[3][3] = {{1.0, 0.0, 0.0}, {0.0, std::cos(xangle), -std::sin(xangle)}, {0.0, std::sin(xangle), std::cos(xangle)}};
    matrix::SquareMatrix<double, 3> Rx4(rxvals4);

    double ryvals4[3][3] = {{std::cos(yangle), 0.0, std::sin(yangle)}, {0.0, 1.0, 0.0}, {-std::sin(yangle), 0.0, std::cos(yangle)}};
    matrix::SquareMatrix<double, 3> Ry4(ryvals4);

    double rzvals4[3][3] = {{std::cos(zangle), -std::sin(zangle), 0.0}, {std::sin(zangle), std::cos(zangle), 0.0}, {0.0, 0.0, 1.0}};
    matrix::SquareMatrix<double, 3> Rz4(rzvals4);
    matrix::DCM<double> dcm4 = Rz4 * Ry4 * Rx4;
    matrix::Quaternion<double> q4(dcm4);
    EXPECT_NEAR(1.0, q4(0), 1.0e-15);
    EXPECT_NEAR(0.0, q4(1), 1.0e-15);
    EXPECT_NEAR(0.0, q4(2), 1.0e-15);
    EXPECT_NEAR(0.0, q4(3), 1.0e-15);

    // ----------
    // -90 degree rotation about z
    zangle = -0.5*M_PI;
    double rxvals5[3][3] = {{1.0, 0.0, 0.0}, {0.0, std::cos(xangle), -std::sin(xangle)}, {0.0, std::sin(xangle), std::cos(xangle)}};
    matrix::SquareMatrix<double, 3> Rx5(rxvals5);

    double ryvals5[3][3] = {{std::cos(yangle), 0.0, std::sin(yangle)}, {0.0, 1.0, 0.0}, {-std::sin(yangle), 0.0, std::cos(yangle)}};
    matrix::SquareMatrix<double, 3> Ry5(ryvals5);

    double rzvals5[3][3] = {{std::cos(zangle), -std::sin(zangle), 0.0}, {std::sin(zangle), std::cos(zangle), 0.0}, {0.0, 0.0, 1.0}};
    matrix::SquareMatrix<double, 3> Rz5(rzvals5);
    matrix::DCM<double> dcm5 = Rz5 * Ry5 * Rx5;
    matrix::Quaternion<double> q5(dcm5);
    EXPECT_NEAR(1.0/std::sqrt(2.0), q5(0), 1.0e-15);
    EXPECT_NEAR(0.0, q5(1), 1.0e-15);
    EXPECT_NEAR(0.0, q5(2), 1.0e-15);
    EXPECT_NEAR(-1.0/std::sqrt(2.0), q5(3), 1.0e-15);

    // ----------
    // -180 degree rotation about z
    zangle = -1.0*M_PI;
    double rxvals6[3][3] = {{1.0, 0.0, 0.0}, {0.0, std::cos(xangle), -std::sin(xangle)}, {0.0, std::sin(xangle), std::cos(xangle)}};
    matrix::SquareMatrix<double, 3> Rx6(rxvals6);

    double ryvals6[3][3] = {{std::cos(yangle), 0.0, std::sin(yangle)}, {0.0, 1.0, 0.0}, {-std::sin(yangle), 0.0, std::cos(yangle)}};
    matrix::SquareMatrix<double, 3> Ry6(ryvals6);

    double rzvals6[3][3] = {{std::cos(zangle), -std::sin(zangle), 0.0}, {std::sin(zangle), std::cos(zangle), 0.0}, {0.0, 0.0, 1.0}};
    matrix::SquareMatrix<double, 3> Rz6(rzvals6);
    matrix::DCM<double> dcm6 = Rz6 * Ry6 * Rx6;
    matrix::Quaternion<double> q6(dcm6);
    EXPECT_NEAR(0.0, q6(0), 1.0e-15);
    EXPECT_NEAR(0.0, q6(1), 1.0e-15);
    EXPECT_NEAR(0.0, q6(2), 1.0e-15);
    EXPECT_NEAR(1.0, q6(3), 1.0e-15);

    // ----------
    // -270 degree rotation about z
    zangle = -1.5*M_PI;
    double rxvals7[3][3] = {{1.0, 0.0, 0.0}, {0.0, std::cos(xangle), -std::sin(xangle)}, {0.0, std::sin(xangle), std::cos(xangle)}};
    matrix::SquareMatrix<double, 3> Rx7(rxvals7);

    double ryvals7[3][3] = {{std::cos(yangle), 0.0, std::sin(yangle)}, {0.0, 1.0, 0.0}, {-std::sin(yangle), 0.0, std::cos(yangle)}};
    matrix::SquareMatrix<double, 3> Ry7(ryvals7);

    double rzvals7[3][3] = {{std::cos(zangle), -std::sin(zangle), 0.0}, {std::sin(zangle), std::cos(zangle), 0.0}, {0.0, 0.0, 1.0}};
    matrix::SquareMatrix<double, 3> Rz7(rzvals7);
    matrix::DCM<double> dcm7 = Rz7 * Ry7 * Rx7;
    matrix::Quaternion<double> q7(dcm7);
    EXPECT_NEAR(1.0/std::sqrt(2.0), q7(0), 1.0e-15);
    EXPECT_NEAR(0.0, q7(1), 1.0e-15);
    EXPECT_NEAR(0.0, q7(2), 1.0e-15);
    EXPECT_NEAR(1.0/std::sqrt(2.0), q7(3), 1.0e-15);
}

TEST(QuaternionTestSuite, TestQuaternionConstructorDCMzyx)
{
    #if 0
    // ----------
    // Rotation about z-y-x
    double xangle = 120.0;
    double yangle = -15.0;
    double zangle = 30.0;
    double rxvals0[3][3] = {{1.0, 0.0, 0.0}, {0.0, std::cos(xangle), -std::sin(xangle)}, {0.0, std::sin(xangle), std::cos(xangle)}};
    matrix::SquareMatrix<double, 3> Rx0(rxvals0);
    std::cout << Rx0 << std::endl;

    double ryvals0[3][3] = {{std::cos(yangle), 0.0, std::sin(yangle)}, {0.0, 1.0, 0.0}, {-std::sin(yangle), 0.0, std::cos(yangle)}};
    matrix::SquareMatrix<double, 3> Ry0(ryvals0);
    std::cout << Ry0 << std::endl;

    double rzvals0[3][3] = {{std::cos(zangle), -std::sin(zangle), 0.0}, {std::sin(zangle), std::cos(zangle), 0.0}, {0.0, 0.0, 1.0}};
    matrix::SquareMatrix<double, 3> Rz0(rzvals0);
    std::cout << Rz0 << std::endl;
    matrix::DCM<double> dcm0 = Rz0 * Ry0 * Rx0;
    std::cout << dcm0 << std::endl;
    matrix::Quaternion<double> q0(dcm0);
    EXPECT_NEAR(0.449574452866277, q0(0), 1.0e-6);
    EXPECT_NEAR(0.237489694003173, q0(1), 1.0e-6);
    EXPECT_NEAR(0.159186976142444, q0(2), 1.0e-6);
    EXPECT_NEAR(0.846251123011894, q0(3), 1.0e-6);
    #endif
}

TEST(QuaternionTestSuite, TestQuaternionConstructorVector4)
{
    double vals2[4] = {1.0, 0.0, 0.0, 0.0};
    matrix::Vector<double, 4> v2(vals2);
    matrix::Quaternion<double> q5(v2);
    EXPECT_DOUBLE_EQ(1.0, q5(0));
    EXPECT_DOUBLE_EQ(0.0, q5(1));
    EXPECT_DOUBLE_EQ(0.0, q5(2));
    EXPECT_DOUBLE_EQ(0.0, q5(3));
}

TEST(QuaternionTestSuite, TestQuaternionConstructorTwoVectors)
{
    // Test ctor with to very not the same vectors
    matrix::Vector3<double> v3(0.375, 0.2, 2.4);
    matrix::Vector3<double> v4(1.2, 3.4, 2.223);
    matrix::Quaternion<double> q6(v3, v4);

    // Test ctor with the same two vectors
    double vals3[3] = {1.0, 2.0, 3.0};
    matrix::Vector3<double> v5(vals3), v6(vals3);
    matrix::Quaternion<double> q7(v5, v6);

    //! Test ctor with vectors pointing opposite directions
    matrix::Vector3<double> v7(1.0, 0.0, 0.0);
    matrix::Vector3<double> v8(-1.0, 0.0, 0.0);
    matrix::Quaternion<double> q8(v7, v8);

    //! Test ctor with parallel vectors
    matrix::Vector3<double> v9(1.0, 0.0, 0.0);
    matrix::Vector3<double> v10(1.0, 1.0, 0.0);
    matrix::Quaternion<double> q9(v9, v10);

    //! Test ctor with perpendicular vectors
    matrix::Vector3<double> v11(1.0, 0.0, 0.0);
    matrix::Vector3<double> v12(0.0, 1.0, 0.0);
    matrix::Quaternion<double> q10(v11, v12);
}

TEST(QuaternionTestSuite, TestQuaternionAddition)
{
    matrix::Quaternion<double> q1(0.5, -0.5, 1.0, 2.0);
    matrix::Quaternion<double> q2(0.5, 0.5, -4.0, 3.0);
    matrix::Quaternion<double> res = q1 + q2;
    EXPECT_DOUBLE_EQ(1.0, res(0));
    EXPECT_DOUBLE_EQ(0.0, res(1));
    EXPECT_DOUBLE_EQ(-3.0, res(2));
    EXPECT_DOUBLE_EQ(5.0, res(3));
}

TEST(QuaternionTestSuite, TestQuaternionSubtraction)
{
    matrix::Quaternion<double> q1(0.5, -0.5, 1.0, 2.0);
    matrix::Quaternion<double> q2(0.5, 0.5, -4.0, 3.0);
    matrix::Quaternion<double> res = q1 - q2;
    EXPECT_DOUBLE_EQ(0.0, res(0));
    EXPECT_DOUBLE_EQ(-1.0, res(1));
    EXPECT_DOUBLE_EQ(5.0, res(2));
    EXPECT_DOUBLE_EQ(-1.0, res(3));
}

TEST(QuaternionTestSuite, TestQuaternionMultiplication)
{
    double vals1[4] = {1.3, 5.1, 3.2, 1.1};
    matrix::Quaternion<double> q1(vals1);
    
    double vals2[4] = {0.2, 4.4, 6.1, -2.0};
    matrix::Quaternion<double> q2(vals2);

    matrix::Quaternion<double> result = q1 * q2;
    EXPECT_DOUBLE_EQ(-39.5, result(0));
    EXPECT_DOUBLE_EQ(-6.37, result(1));
    EXPECT_DOUBLE_EQ(23.61, result(2));
    EXPECT_DOUBLE_EQ(14.65, result(3));
}

TEST(QuaternionTestSuite, TestQuaternionCompoundAddition)
{
    matrix::Quaternion<double> q1(0.5, -0.5, 1.0, 2.0);
    matrix::Quaternion<double> q2(0.5, 0.5, -4.0, 3.0);
    q1 += q2;
    EXPECT_DOUBLE_EQ(1.0, q1(0));
    EXPECT_DOUBLE_EQ(0.0, q1(1));
    EXPECT_DOUBLE_EQ(-3.0, q1(2));
    EXPECT_DOUBLE_EQ(5.0, q1(3));
}

TEST(QuaternionTestSuite, TestQuaternionCompoundSubtraction)
{
    matrix::Quaternion<double> q1(0.5, -0.5, 1.0, 2.0);
    matrix::Quaternion<double> q2(0.5, 0.5, -4.0, 3.0);
    q1 -= q2;
    EXPECT_DOUBLE_EQ(0.0, q1(0));
    EXPECT_DOUBLE_EQ(-1.0, q1(1));
    EXPECT_DOUBLE_EQ(5.0, q1(2));
    EXPECT_DOUBLE_EQ(-1.0, q1(3));
}

TEST(QuaternionTestSuite, TestQuaternionCompoundMultiplication)
{
    double vals1[4] = {1.3, 5.1, 3.2, 1.1};
    matrix::Quaternion<double> q1(vals1);
    
    double vals2[4] = {0.2, 4.4, 6.1, -2.0};
    matrix::Quaternion<double> q2(vals2);

    q1 *= q2;
    EXPECT_DOUBLE_EQ(-39.5, q1(0));
    EXPECT_DOUBLE_EQ(-6.37, q1(1));
    EXPECT_DOUBLE_EQ(23.61, q1(2));
    EXPECT_DOUBLE_EQ(14.65, q1(3));
}

TEST(QuaternionTestSuite, TestScalarAddition)
{
    matrix::Quaternion<double> q(-4.3, 0.5, 5.5, 1.2);
    matrix::Quaternion<double> res = q + 3.0;

    EXPECT_DOUBLE_EQ(-1.3, res(0));
    EXPECT_DOUBLE_EQ(0.5, res(1));
    EXPECT_DOUBLE_EQ(5.5, res(2));
    EXPECT_DOUBLE_EQ(1.2, res(3));
}

TEST(QuaternionTestSuite, TestScalarSubtraction)
{
    matrix::Quaternion<double> q(-4.3, 0.5, 5.5, 1.2);
    matrix::Quaternion<double> res = q - 3.0;

    EXPECT_DOUBLE_EQ(-7.3, res(0));
    EXPECT_DOUBLE_EQ(0.5, res(1));
    EXPECT_DOUBLE_EQ(5.5, res(2));
    EXPECT_DOUBLE_EQ(1.2, res(3));
}

TEST(QuaternionTestSuite, TestQuaternionScalarMultiplication)
{
    double vals1[4] = {3.4, -2.3, 1.1, 0.5};
    matrix::Quaternion<double> q1(vals1);
    matrix::Quaternion<double> result1 = q1 * 4.3;
    EXPECT_DOUBLE_EQ(14.62, result1(0));
    EXPECT_DOUBLE_EQ(-9.89, result1(1));
    EXPECT_DOUBLE_EQ(4.73, result1(2));
    EXPECT_DOUBLE_EQ(2.15, result1(3));

    matrix::Quaternion<double> result2 = 4.3 * q1;
    EXPECT_DOUBLE_EQ(14.62, result2(0));
    EXPECT_DOUBLE_EQ(-9.89, result2(1));
    EXPECT_DOUBLE_EQ(4.73, result2(2));
    EXPECT_DOUBLE_EQ(2.15, result2(3));
}
