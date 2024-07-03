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

TEST(Vector3TestSuite, TestDefaultConstructor)
{
    matrix::Vector3<int> v;
    EXPECT_EQ(0, v(0));
    EXPECT_EQ(0, v(1));
    EXPECT_EQ(0, v(2));
}

TEST(Vector3TestSuite, TestFlatArrayConstructor)
{
    int vals1[3] = {4, 5, 6};
    matrix::Vector3<int> v1(vals1);
    EXPECT_EQ(vals1[0], v1(0));
    EXPECT_EQ(vals1[1], v1(1));
    EXPECT_EQ(vals1[2], v1(2));
}

TEST(Vector3TestSuite, TestIndividualElementParametersConstructor)
{
    matrix::Vector3<double> v(2.3, 1.5, 4.2);
    EXPECT_DOUBLE_EQ(2.3, v(0));
    EXPECT_DOUBLE_EQ(1.5, v(1));
    EXPECT_DOUBLE_EQ(4.2, v(2));
}

TEST(Vector3TestSuite, TestInitializerListConstructor)
{
    matrix::Vector3<int> v = {3, 4, 5};
    EXPECT_EQ(3, v(0));
    EXPECT_EQ(4, v(1));
    EXPECT_EQ(5, v(2));
}

TEST(Vector3TestSuite, TestVectorCopyConstructor)
{
    int vals[3] = {7, 6, 5};
    matrix::Vector3<int> v3_type(vals);
    matrix::Vector3<int> v(v3_type);
    EXPECT_EQ(vals[0], v(0));
    EXPECT_EQ(vals[1], v(1));
    EXPECT_EQ(vals[2], v(2));
}

TEST(Vector3TestSuite, TestVectorToVector3ConversionConstructor)
{
    double vals[3] = {2.1, 2.2, 2.3};
    matrix::Vector<double, 3> v_type(vals);
    matrix::Vector3<double> v(v_type);
    EXPECT_DOUBLE_EQ(vals[0], v(0));
    EXPECT_DOUBLE_EQ(vals[1], v(1));
    EXPECT_DOUBLE_EQ(vals[2], v(2));
}

TEST(Vector3TestSuite, TestMatrixToVector3ConversionConstruction)
{
    int vals[3] = {1, 2, 3};
    matrix::Matrix<int, 3, 1> m_type(vals);
    matrix::Vector3<int> v(m_type);
    EXPECT_EQ(vals[0], v(0));
    EXPECT_EQ(vals[1], v(1));
    EXPECT_EQ(vals[2], v(2));
}

TEST(Vector3TestSuite, TestAddition)
{
    matrix::Vector3<int> v1(1, 2, 3);
    matrix::Vector3<int> v2(4, 5, 6);
    matrix::Vector3<int> result = v1 + v2;
    EXPECT_EQ(5, result(0));
    EXPECT_EQ(7, result(1));
    EXPECT_EQ(9, result(2));
}

TEST(Vector3TestSuite, TestSubtraction)
{
    matrix::Vector3<int> v1(7, -2, 4);
    matrix::Vector3<int> v2(2, 3, 1);
    matrix::Vector3<int> result = v1 - v2;
    EXPECT_EQ(5, result(0));
    EXPECT_EQ(-5, result(1));
    EXPECT_EQ(3, result(2));
}

TEST(Vector3TestSuite, TestMultiplication)
{
    matrix::Vector3<int> v1(3, 6, -2);
    matrix::Vector3<int> v2(7, 1, 0);
    int result = v1 * v2;
    EXPECT_EQ(27, result);
}

TEST(Vector3TestSuite, TestCompoundAddition)
{
    matrix::Vector3<int> v1(1, 2, 3);
    matrix::Vector3<int> v2(4, 5, 6);
    
    v1 += v2;
    EXPECT_EQ(5, v1(0));
    EXPECT_EQ(7, v1(1));
    EXPECT_EQ(9, v1(2));
}

TEST(Vector3TestSuite, TestCompoundSubtraction)
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