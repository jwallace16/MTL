///////////////////////////////////////////////////////////////////////////////
//!
//! @file TestVector3.cpp
//!
//! Unit test for Vector3.hpp
//!
//! @author David Wallace <jdavidwallace1@gmail.com>
///////////////////////////////////////////////////////////////////////////////

#include <iostream>
#include <gtest/gtest.h>
#include "../src/Vector3.hpp"
#include "../src/SquareMatrix.hpp"

TEST(Vector3TestSuite, TestConstruction)
{
    matrix::Vector3<int> v1;
    EXPECT_EQ(0, v1(0));
    EXPECT_EQ(0, v1(1));
    EXPECT_EQ(0, v1(2));

    int vals2[3] = {4, 5, 6};
    matrix::Vector3<int> v2(vals2);
    EXPECT_EQ(vals2[0], v2(0));
    EXPECT_EQ(vals2[1], v2(1));
    EXPECT_EQ(vals2[2], v2(2));

    matrix::Vector3<double> v3(2.3, 1.5, 4.2);
    EXPECT_DOUBLE_EQ(2.3, v3(0));
    EXPECT_DOUBLE_EQ(1.5, v3(1));
    EXPECT_DOUBLE_EQ(4.2, v3(2));

    double vals4[3] = {2.1, 2.2, 2.3};
    matrix::Vector<double, 3> v_type(vals4);
    matrix::Vector3<double> v4(v_type);
    EXPECT_DOUBLE_EQ(vals4[0], v4(0));
    EXPECT_DOUBLE_EQ(vals4[1], v4(1));
    EXPECT_DOUBLE_EQ(vals4[2], v4(2));

    int vals5[3] = {7, 6, 5};
    matrix::Vector3<int> v3_type(vals5);
    matrix::Vector3<int> v5(v3_type);
    EXPECT_EQ(vals5[0], v5(0));
    EXPECT_EQ(vals5[1], v5(1));
    EXPECT_EQ(vals5[2], v5(2));

    int vals6[3] = {1, 2, 3};
    matrix::Matrix<int, 3, 1> m_type(vals6);
    matrix::Vector3<int> v6(m_type);
    EXPECT_EQ(vals6[0], v6(0));
    EXPECT_EQ(vals6[1], v6(1));
    EXPECT_EQ(vals6[2], v6(2));
}

TEST(Vector3TestSuite, TestVectorAddition)
{
    matrix::Vector3<int> v1(1, 2, 3);
    matrix::Vector3<int> v2(4, 5, 6);
    matrix::Vector3<int> result = v1 + v2;
    EXPECT_EQ(5, result(0));
    EXPECT_EQ(7, result(1));
    EXPECT_EQ(9, result(2));
}

TEST(Vector3TestSuite, TestVectorSubtraction)
{
    matrix::Vector3<int> v1(7, -2, 4);
    matrix::Vector3<int> v2(2, 3, 1);
    matrix::Vector3<int> result = v1 - v2;
    EXPECT_EQ(5, result(0));
    EXPECT_EQ(-5, result(1));
    EXPECT_EQ(3, result(2));
}

TEST(Vector3TestSuite, TestVectorMultiplication)
{
    matrix::Vector3<int> v1(3, 6, -2);
    matrix::Vector3<int> v2(7, 1, 0);
    int result = v1 * v2;
    EXPECT_EQ(27, result);
}

TEST(Vector3TestSuite, TestVectorCompoundAddition)
{
    matrix::Vector3<int> v1(1, 2, 3);
    matrix::Vector3<int> v2(4, 5, 6);
    
    v1 += v2;
    EXPECT_EQ(5, v1(0));
    EXPECT_EQ(7, v1(1));
    EXPECT_EQ(9, v1(2));
}

TEST(Vector3TestSuite, TestVectorCompoundSubtraction)
{
    matrix::Vector3<int> v1(7, -2, 4);
    matrix::Vector3<int> v2(2, 3, 1);

    v1 -= v2;
    EXPECT_EQ(5, v1(0));
    EXPECT_EQ(-5, v1(1));
    EXPECT_EQ(3, v1(2));
}

TEST(Vector3TestSuite, TestScalarAddition)
{
    matrix::Vector3<int> v(-4, 3, 6);
    matrix::Vector3<int> result = v + 4;
    EXPECT_EQ(0, result(0));
    EXPECT_EQ(7, result(1));
    EXPECT_EQ(10, result(2));
}

TEST(Vector3TestSuite, TestScalarSubtraction)
{
    matrix::Vector3<int> v(6, 1, -2);
    matrix::Vector3<int> result = v - 5;
    EXPECT_EQ(1, result(0));
    EXPECT_EQ(-4, result(1));
    EXPECT_EQ(-7, result(2));
}

TEST(Vector3TestSuite, TestUnaryMinus)
{
    matrix::Vector3<int> v(7, 7, 7);
    matrix::Vector3<int> result = -v;
    EXPECT_EQ(-7, result(0));
    EXPECT_EQ(-7, result(1));
    EXPECT_EQ(-7, result(2));
}

TEST(Vector3TestSuite, TestScalarMultiplication)
{
    matrix::Vector3<int> v(7, 3, 4);
    matrix::Vector3<int> result = v * 3;
    EXPECT_EQ(21, result(0));
    EXPECT_EQ(9, result(1));
    EXPECT_EQ(12, result(2));
}

TEST(Vector3TestSuite, TestScalarDivision)
{
    matrix::Vector3<double> v(5.5, 2.3, -4.2);
    matrix::Vector3<double> res = v / 2.0;
    EXPECT_DOUBLE_EQ(2.75, res(0));
    EXPECT_DOUBLE_EQ(1.15, res(1));
    EXPECT_DOUBLE_EQ(-2.1, res(2));
}

TEST(Vector3TestSuite, TestScalarCompoundAddition)
{
    matrix::Vector3<int> v(-4, 3, 6);
    v += 4;
    EXPECT_EQ(0, v(0));
    EXPECT_EQ(7, v(1));
    EXPECT_EQ(10, v(2));
}

TEST(Vector3TestSuite, TestScalarCompoundSubtraction)
{
    matrix::Vector3<int> v(6, 1, -2);
    v -= 5;
    EXPECT_EQ(1, v(0));
    EXPECT_EQ(-4, v(1));
    EXPECT_EQ(-7, v(2));
}

TEST(Vector3TestSuite, TestScalarCompoundMultiplication)
{
    matrix::Vector3<int> v(7, 3, 4);
    v *= 3;
    EXPECT_EQ(21, v(0));
    EXPECT_EQ(9, v(1));
    EXPECT_EQ(12, v(2));
}

TEST(Vector3TestSuite, TestScalarCompoundDivision)
{
    matrix::Vector3<double> v(5.5, 2.3, -4.2);
    v /= 2.0;
    EXPECT_DOUBLE_EQ(2.75, v(0));
    EXPECT_DOUBLE_EQ(1.15, v(1));
    EXPECT_DOUBLE_EQ(-2.1, v(2));
}

TEST(Vector3TestSuite, TestVector3CrossProduct)
{
    matrix::Vector3<int> v1(3, 6, -2);
    matrix::Vector3<int> v2(7, 1, 0);
    matrix::Vector3<int> result1 = v1.cross(v2);
    EXPECT_EQ(2, result1(0));
    EXPECT_EQ(-14, result1(1));
    EXPECT_EQ(-39, result1(2));

    int vals[3] = {7, 1, 0};
    matrix::Vector<int, 3> v3(vals);
    matrix::Vector3<int> result2 = v1.cross(v3);
    EXPECT_EQ(2, result2(0));
    EXPECT_EQ(-14, result2(1));
    EXPECT_EQ(-39, result2(2));

    matrix::Matrix<int, 3, 1> v4(vals);
    matrix::Vector3<int> result3 = v1.cross(v4);
    EXPECT_EQ(2, result3(0));
    EXPECT_EQ(-14, result3(1));
    EXPECT_EQ(-39, result3(2));
}

TEST(Vector3TestSuite, TestVector3TildeOperation)
{
    int vals[3] = {-7, 2, 4};
    matrix::Vector3<int> v(vals);
    matrix::SquareMatrix<int, 3> m = v.tilde();
    EXPECT_EQ(0, m(0,0));
    EXPECT_EQ(-4, m(0,1));
    EXPECT_EQ(2, m(0,2));
    EXPECT_EQ(4, m(1,0));
    EXPECT_EQ(0, m(1,1));
    EXPECT_EQ(7, m(1,2));
    EXPECT_EQ(-2, m(2,0));
    EXPECT_EQ(-7, m(2,1));
    EXPECT_EQ(0, m(2,2));
}

TEST(Vector3TestSuite, TestVector3UnitVector)
{
    matrix::Vector3<double> v(2.1, 3.3, 5.3);
    matrix::Vector3<double> result = v.unit();
    EXPECT_DOUBLE_EQ(0.31880451962467254, result(0));
    EXPECT_DOUBLE_EQ(0.50097853083877109, result(1));
    EXPECT_DOUBLE_EQ(0.80460188286226875, result(2));
}