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

TEST(EulerTestSuite, TestEulerDefaultConstructor)
{
    matrix::Euler<double> euler;
    EXPECT_DOUBLE_EQ(0.0, euler.getPsi());
    EXPECT_DOUBLE_EQ(0.0, euler.getTheta());
    EXPECT_DOUBLE_EQ(0.0, euler.getPhi());
}

TEST(EulerTestSuite, TestEulerExplicitConstructor)
{
    matrix::Euler<double> euler(1.1, 2.2, 3.3);
    EXPECT_DOUBLE_EQ(1.1, euler.getPsi());
    EXPECT_DOUBLE_EQ(2.2, euler.getTheta());
    EXPECT_DOUBLE_EQ(3.3, euler.getPhi());
}

TEST(EulerTestSuite, TestAssigningAngles)
{
    matrix::Euler<double> euler;
    EXPECT_DOUBLE_EQ(0.0, euler.getPsi());
    EXPECT_DOUBLE_EQ(0.0, euler.getTheta());
    EXPECT_DOUBLE_EQ(0.0, euler.getPhi());

    euler.Psi() = 1.1;
    euler.Theta() = 2.2;
    euler.Phi() = 3.3;

    EXPECT_DOUBLE_EQ(1.1, euler.getPsi());
    EXPECT_DOUBLE_EQ(2.2, euler.getTheta());
    EXPECT_DOUBLE_EQ(3.3, euler.getPhi());
}