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

TEST(DCMTestSuite, TestDCMConstructors)
{
    matrix::DCM<double> d1;
    EXPECT_DOUBLE_EQ(1.0, d1(0,0));
    EXPECT_DOUBLE_EQ(0.0, d1(0,1));
    EXPECT_DOUBLE_EQ(0.0, d1(0,2));
    EXPECT_DOUBLE_EQ(0.0, d1(1,0));
    EXPECT_DOUBLE_EQ(1.0, d1(1,1));
    EXPECT_DOUBLE_EQ(0.0, d1(1,2));
    EXPECT_DOUBLE_EQ(0.0, d1(2,0));
    EXPECT_DOUBLE_EQ(0.0, d1(2,1));
    EXPECT_DOUBLE_EQ(1.0, d1(2,2));

    double vals2[3][3] = {{1.1, 2.2, 3.3}, {4.4, 5.5, 6.6}, {7.7, 8.8, 9.9}};
    matrix::DCM<double> d2(vals2);
    EXPECT_DOUBLE_EQ(1.1, d2(0,0));
    EXPECT_DOUBLE_EQ(2.2, d2(0,1));
    EXPECT_DOUBLE_EQ(3.3, d2(0,2));
    EXPECT_DOUBLE_EQ(4.4, d2(1,0));
    EXPECT_DOUBLE_EQ(5.5, d2(1,1));
    EXPECT_DOUBLE_EQ(6.6, d2(1,2));
    EXPECT_DOUBLE_EQ(7.7, d2(2,0));
    EXPECT_DOUBLE_EQ(8.8, d2(2,1));
    EXPECT_DOUBLE_EQ(9.9, d2(2,2));

    double vals3[9] = {1.1, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7, 8.8, 9.9};
    matrix::DCM<double> d3(vals3);
    EXPECT_DOUBLE_EQ(1.1, d3(0,0));
    EXPECT_DOUBLE_EQ(2.2, d3(0,1));
    EXPECT_DOUBLE_EQ(3.3, d3(0,2));
    EXPECT_DOUBLE_EQ(4.4, d3(1,0));
    EXPECT_DOUBLE_EQ(5.5, d3(1,1));
    EXPECT_DOUBLE_EQ(6.6, d3(1,2));
    EXPECT_DOUBLE_EQ(7.7, d3(2,0));
    EXPECT_DOUBLE_EQ(8.8, d3(2,1));
    EXPECT_DOUBLE_EQ(9.9, d3(2,2));

    double vals4[9] = {1.1, 1.2, 1.3, 2.1, 2.2, 2.3, 3.1, 3.2, 3.3};
    matrix::Matrix<double, 3, 3> m4(vals4);
    matrix::DCM<double> d4(m4);
    EXPECT_DOUBLE_EQ(1.1, d4(0,0));
    EXPECT_DOUBLE_EQ(1.2, d4(0,1));
    EXPECT_DOUBLE_EQ(1.3, d4(0,2));
    EXPECT_DOUBLE_EQ(2.1, d4(1,0));
    EXPECT_DOUBLE_EQ(2.2, d4(1,1));
    EXPECT_DOUBLE_EQ(2.3, d4(1,2));
    EXPECT_DOUBLE_EQ(3.1, d4(2,0));
    EXPECT_DOUBLE_EQ(3.2, d4(2,1));
    EXPECT_DOUBLE_EQ(3.3, d4(2,2));

    matrix::Quaternion<double> q5(1.0, 0.0, 0.0, 0.0);
    matrix::DCM<double> d5(q5);
    EXPECT_DOUBLE_EQ(1.0, d5(0,0));
    EXPECT_DOUBLE_EQ(0.0, d5(0,1));
    EXPECT_DOUBLE_EQ(0.0, d5(0,2));
    EXPECT_DOUBLE_EQ(0.0, d5(1,0));
    EXPECT_DOUBLE_EQ(1.0, d5(1,1));
    EXPECT_DOUBLE_EQ(0.0, d5(1,2));
    EXPECT_DOUBLE_EQ(0.0, d5(2,0));
    EXPECT_DOUBLE_EQ(0.0, d5(2,1));
    EXPECT_DOUBLE_EQ(1.0, d5(2,2));
    
    matrix::Quaternion<double> q6(0.0, 1.0, 0.0, 0.0);
    matrix::DCM<double> d6(q6);
    std::cout << d6 << std::endl;
}