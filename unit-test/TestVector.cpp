///////////////////////////////////////////////////////////////////////////////
//!
//! @file TestVector.cpp
//!
//! Unit test for Vector.hpp
//!
//! @author David Wallace <jdavidwallace1@gmail.com>
///////////////////////////////////////////////////////////////////////////////

#include <iostream>
#include <gtest/gtest.h>
#include "../src/Vector.hpp"

TEST(VectorTestSuite, TestDefaultConstructor)
{
    matrix::Vector<int, 4> v;
    EXPECT_EQ(0, v(0));
    EXPECT_EQ(0, v(1));
    EXPECT_EQ(0, v(2));
    EXPECT_EQ(0, v(3));
}

TEST(VectorTestSuite, TestFlatArrayConstructor)
{
    int vals1[3] = {4, 5, 6};
    matrix::Vector<int, 3> v1(vals1);
    EXPECT_EQ(4, v1(0));
    EXPECT_EQ(5, v1(1));
    EXPECT_EQ(6, v1(2));

    double vals2[4] = {1.1, 2.2, 3.3, 4.4};
    matrix::Vector<double, 4> v2(vals2);
    EXPECT_DOUBLE_EQ(1.1, v2(0));
    EXPECT_DOUBLE_EQ(2.2, v2(1));
    EXPECT_DOUBLE_EQ(3.3, v2(2));
    EXPECT_DOUBLE_EQ(4.4, v2(3));

    matrix::Vector<double, 4> v3;
    EXPECT_DOUBLE_EQ(0.0, v3(0));
    EXPECT_DOUBLE_EQ(0.0, v3(1));
    EXPECT_DOUBLE_EQ(0.0, v3(2));
    EXPECT_DOUBLE_EQ(0.0, v3(3));
    v3 = v2;
    EXPECT_DOUBLE_EQ(1.1, v3(0));
    EXPECT_DOUBLE_EQ(2.2, v3(1));
    EXPECT_DOUBLE_EQ(3.3, v3(2));
    EXPECT_DOUBLE_EQ(4.4, v3(3));

    matrix::Vector<double, 4> v4(v2);
    EXPECT_DOUBLE_EQ(1.1, v4(0));
    EXPECT_DOUBLE_EQ(2.2, v4(1));
    EXPECT_DOUBLE_EQ(3.3, v4(2));
    EXPECT_DOUBLE_EQ(4.4, v4(3));
}

TEST(VectorTestSuite, TestInitializerListConstructor)
{
    matrix::Vector<int, 4> v = {1, 2, 3, 4};
    EXPECT_EQ(1, v(0));
    EXPECT_EQ(2, v(1));
    EXPECT_EQ(3, v(2));
    EXPECT_EQ(4, v(3));
}

TEST(VectorTestSuite, TestVectorAddition)
{
    int vals1[3] = {3, 4, 5};
    matrix::Vector<int, 3> v1(vals1);

    int vals2[3] = {6, -9, 2};
    matrix::Vector<int, 3> v2(vals2);

    matrix::Vector<int, 3> res = v1 + v2;
    EXPECT_EQ(9, res(0));
    EXPECT_EQ(-5, res(1));
    EXPECT_EQ(7, res(2));
}

TEST(VectorTestSuite, TestVectorSubtraction)
{
    int vals1[3] = {3, 4, 5};
    matrix::Vector<int, 3> v1(vals1);

    int vals2[3] = {6, -9, 2};
    matrix::Vector<int, 3> v2(vals2);

    matrix::Vector<int, 3> res = v1 - v2;
    EXPECT_EQ(-3, res(0));
    EXPECT_EQ(13, res(1));
    EXPECT_EQ(3, res(2));
}

TEST(VectorTestSuite, TestVectorCompoundAddition)
{
    int vals1[3] = {3, 4, 5};
    matrix::Vector<int, 3> v1(vals1);

    int vals2[3] = {6, -9, 2};
    matrix::Vector<int, 3> v2(vals2);

    v1 += v2;
    EXPECT_EQ(9, v1(0));
    EXPECT_EQ(-5, v1(1));
    EXPECT_EQ(7, v1(2));
}

TEST(VectorTestSuite, TestVectorCompoundSubtraction)
{
    int vals1[3] = {3, 4, 5};
    matrix::Vector<int, 3> v1(vals1);

    int vals2[3] = {6, -9, 2};
    matrix::Vector<int, 3> v2(vals2);

    v1 -= v2;
    EXPECT_EQ(-3, v1(0));
    EXPECT_EQ(13, v1(1));
    EXPECT_EQ(3, v1(2));
}

TEST(VectorTestSuite, TestVectorScalarAddition)
{
    int vals[4] = {5, 6, 2, 1};
    matrix::Vector<int, 4> v(vals);

    matrix::Vector<int, 4> res = v + 5;
    EXPECT_EQ(10, res(0));
    EXPECT_EQ(11, res(1));
    EXPECT_EQ(7, res(2));
    EXPECT_EQ(6, res(3));
}

TEST(VectorTestSuite, TestVectorScalarSubtraction)
{
    int vals[4] = {5, 6, 2, 1};
    matrix::Vector<int, 4> v(vals);

    matrix::Vector<int, 4> res = v - 5;
    EXPECT_EQ(0, res(0));
    EXPECT_EQ(1, res(1));
    EXPECT_EQ(-3, res(2));
    EXPECT_EQ(-4, res(3));
}

TEST(VectorTestSuite, TestVectorScalarMultiplication)
{
    double vals1[4] = {4.4, 3.3, 2.2, 1.1};
    matrix::Vector<double, 4> v1(vals1);
    matrix::Vector<double, 4> result;
    result = v1 * 5.0;
    EXPECT_DOUBLE_EQ(22.0, result(0));
    EXPECT_DOUBLE_EQ(16.5, result(1));
    EXPECT_DOUBLE_EQ(11.0, result(2));
    EXPECT_DOUBLE_EQ(5.5, result(3));

    result.setValue(0.0);
    EXPECT_DOUBLE_EQ(0.0, result(0));
    EXPECT_DOUBLE_EQ(0.0, result(1));
    EXPECT_DOUBLE_EQ(0.0, result(2));
    EXPECT_DOUBLE_EQ(0.0, result(3));

    result = 4.3 * v1;
    EXPECT_DOUBLE_EQ(18.92, result(0));
    EXPECT_DOUBLE_EQ(14.19, result(1));
    EXPECT_DOUBLE_EQ(9.46, result(2));
    EXPECT_DOUBLE_EQ(4.73, result(3));
}

TEST(VectorTestSuite, TestVectorScalarDivision)
{
    double vals[4] = {5.0, 3.3, 2.7, 8.4};
    matrix::Vector<double, 4> v(vals);

    matrix::Vector<double, 4> res = v / 2.0;
    EXPECT_DOUBLE_EQ(2.5, res(0));
    EXPECT_DOUBLE_EQ(1.65, res(1));
    EXPECT_DOUBLE_EQ(1.35, res(2));
    EXPECT_DOUBLE_EQ(4.2, res(3));
}

TEST(VectorTestSuite, TestVectorScalarCompoundAddition)
{
    int vals[4] = {5, 6, 2, 1};
    matrix::Vector<int, 4> v(vals);

    v += 5;
    EXPECT_EQ(10, v(0));
    EXPECT_EQ(11, v(1));
    EXPECT_EQ(7, v(2));
    EXPECT_EQ(6, v(3));
}

TEST(VectorTestSuite, TestVectorScalarCompoundSubtraction)
{
    int vals[4] = {5, 6, 2, 1};
    matrix::Vector<int, 4> v(vals);

    v -= 5;
    EXPECT_EQ(0, v(0));
    EXPECT_EQ(1, v(1));
    EXPECT_EQ(-3, v(2));
    EXPECT_EQ(-4, v(3));
}

TEST(VectorTestSuite, TestVectorScalarCompoundMultiplication)
{
    double vals[4] = {4.4, 3.3, 2.2, 1.1};
    matrix::Vector<double, 4> v(vals);
    
    v *= 5.0;
    EXPECT_DOUBLE_EQ(22.0, v(0));
    EXPECT_DOUBLE_EQ(16.5, v(1));
    EXPECT_DOUBLE_EQ(11.0, v(2));
    EXPECT_DOUBLE_EQ(5.5, v(3));
}

TEST(VectorTestSuite, TestVectorScalarCompoundDivision)
{
    double vals[4] = {5.0, 3.3, 2.7, 8.4};
    matrix::Vector<double, 4> v(vals);

    v /= 2.0;
    EXPECT_DOUBLE_EQ(2.5, v(0));
    EXPECT_DOUBLE_EQ(1.65, v(1));
    EXPECT_DOUBLE_EQ(1.35, v(2));
    EXPECT_DOUBLE_EQ(4.2, v(3));
}

TEST(VectorTestSuite, TestVectorSize)
{
    matrix::Vector<int, 7> v7;
    matrix::Vector<float, 32> v32;
    matrix::Vector<double, 6> v6;
    EXPECT_EQ(7, v7.size());
    EXPECT_EQ(32, v32.size());
    EXPECT_EQ(6, v6.size());
}

TEST(VectorTestSuite, TestVectorDotProduct)
{
    double vals1[4] = {1.1, 2.2, 3.3, 4.4};
    double vals2[4] = {0.5, 7.2, 1.4, 3.3};
    matrix::Vector<double, 4> v1{vals1};
    matrix::Vector<double, 4> v2(vals2);

    double res1 = v1.dot(v2);
    double res2 = v2.dot(v1);
    EXPECT_DOUBLE_EQ(35.53, res1);
    EXPECT_DOUBLE_EQ(35.53, res2);

    int vals3[3] = {4, 5, 8};
    int vals4[3] = {3, 8, -7};
    matrix::Vector<int, 3> v3(vals3);
    matrix::Vector<int, 3> v4(vals4);

    int res3 = v3.dot(v4);
    int res4 = v4.dot(v3);
    EXPECT_EQ(-4, res3);
    EXPECT_EQ(-4, res4);
}

TEST(MatrixTestSuite, TestVectorNorm)
{
    double vals1[3] = {7.3, 1.2, 3.3};
    matrix::Vector<double, 3> v1(vals1);
    EXPECT_DOUBLE_EQ(8.100617260431454, v1.norm());

    int vals2[3] = {2, 3, 4};
    matrix::Vector<int, 3> v2(vals2);
    EXPECT_EQ(5, v2.norm()); // truncates decimal places in cast to int
}

TEST(MatrixTestSuite, TestVectorNormalize)
{
    double vals[4] = {1.4, 3.5, 2.2, 5.7};
    matrix::Vector<double, 4> v(vals);
    v.normalize();
    EXPECT_NEAR(0.19500953, v(0), 1.0e-7);
    EXPECT_NEAR(0.48752382, v(1), 1.0e-7);
    EXPECT_NEAR(0.30644354, v(2), 1.0e-7);
    EXPECT_NEAR(0.79396736, v(3), 1.0e-7);
}

TEST(MatrixTestSuite, TestUnitVector)
{
    double vals[3] = {5.5, 3.3, -1.5};
    matrix::Vector<double, 3> v(vals);
    matrix::Vector<double, 3> result = v.unit();
    EXPECT_NEAR(0.83496422, result(0), 1.0e-7);
    EXPECT_NEAR(0.50097853, result(1), 1.0e-7);
    EXPECT_NEAR(-0.22771751, result(2), 1.0e-7);
    EXPECT_NEAR(1.0, result.length(), 1.0e-7);
}