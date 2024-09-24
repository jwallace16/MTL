///////////////////////////////////////////////////////////////////////////////
//!
//! @file TestEuler.cpp
//!
//! Unit test for Euler.hpp
//!
//! @author David Wallace <jdavidwallace1@gmail.com>
///////////////////////////////////////////////////////////////////////////////

#include <iostream>
#include <gtest/gtest.h>
#include "../src/Euler.hpp"
#include "../src/RotationSequence.hpp"

TEST(EulerTestSuite, TestEulerDefaultConstructor)
{
    matrix::Euler<double> euler;
    EXPECT_DOUBLE_EQ(0.0, euler.getAngle1());
    EXPECT_DOUBLE_EQ(0.0, euler.getAngle2());
    EXPECT_DOUBLE_EQ(0.0, euler.getAngle3());
    EXPECT_EQ(RotationSequence::ZYX_321, euler.getRotatationSequence());
}

TEST(EulerTestSuite, TestEulerConstructorWithSequence)
{
    matrix::Euler<double> euler(RotationSequence::XYZ_123);
    EXPECT_DOUBLE_EQ(0.0, euler.getAngle1());
    EXPECT_DOUBLE_EQ(0.0, euler.getAngle2());
    EXPECT_DOUBLE_EQ(0.0, euler.getAngle3());
    EXPECT_EQ(RotationSequence::XYZ_123, euler.getRotatationSequence());
}

TEST(EulerTestSuite, TestEulerExplicitConstructor)
{
    matrix::Euler<double> euler(1.1, 2.2, 3.3, RotationSequence::XYX_121);
    EXPECT_DOUBLE_EQ(1.1, euler.getAngle1());
    EXPECT_DOUBLE_EQ(2.2, euler.getAngle2());
    EXPECT_DOUBLE_EQ(3.3, euler.getAngle3());
    EXPECT_EQ(RotationSequence::XYX_121, euler.getRotatationSequence());
}

TEST(EulerTestSuite, TestAssigningAngles)
{
    matrix::Euler<double> euler;
    EXPECT_DOUBLE_EQ(0.0, euler.getAngle1());
    EXPECT_DOUBLE_EQ(0.0, euler.getAngle2());
    EXPECT_DOUBLE_EQ(0.0, euler.getAngle3());

    euler.setAngle1() = 1.1;
    euler.setAngle2() = 2.2;
    euler.setAngle3() = 3.3;

    EXPECT_DOUBLE_EQ(1.1, euler.getAngle1());
    EXPECT_DOUBLE_EQ(2.2, euler.getAngle2());
    EXPECT_DOUBLE_EQ(3.3, euler.getAngle3());
}