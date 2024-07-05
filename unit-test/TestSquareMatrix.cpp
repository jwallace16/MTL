///////////////////////////////////////////////////////////////////////////////
//!
//! @file TestSquareMatrix.cpp
//!
//! Unit test for SquareMatrix.hpp
//!
//! @author David Wallace <jdavidwallace1@gmail.com>
///////////////////////////////////////////////////////////////////////////////

#include <iostream>
#include <gtest/gtest.h>
#include "../src/SquareMatrix.hpp"

TEST(SquareMatrixTestSuite, TestDefaultConstructor)
{
    matrix::SquareMatrix<int, 2> m_int;
    for(size_t i = 0; i < 2; ++i)
    {
        for(size_t j = 0; j < 2; ++j)
        {
            EXPECT_EQ(0, m_int(i,j));
        }
    }

    matrix::SquareMatrix<double, 4> m_double;
    for(size_t i = 0; i < 4; ++i)
    {
        for(size_t j = 0; j < 4; ++j)
        {
            EXPECT_DOUBLE_EQ(0.0, m_double(i,j));
        }
    }

    matrix::SquareMatrix<uint16_t, 5> m_uint16;
    for(size_t i = 0; i < 5; ++i)
    {
        for(size_t j = 0; j < 5; ++j)
        {
            EXPECT_EQ(0, m_uint16(i,j));
        }
    }
}

TEST(SquareMatrixTestSuite, Test2dArrayConstructor)
{
    double vals[3][3] = {{1.1, 1.2, 1.3}, {2.1, 2.2, 2.3}, {3.1, 3.2, 3.3}};
    matrix::SquareMatrix<double, 3> m(vals);
    for(size_t i = 0; i < 3; ++i)
    {
        for(size_t j = 0; j < 3; ++j)
        {
            EXPECT_DOUBLE_EQ(vals[i][j], m(i,j));
        }
    }
}

TEST(SquareMatrixTestSuite, TestFlatArrayConstructor)
{
    double vals[9] = {1.1, 1.2, 1.3, 2.1, 2.2, 2.3, 3.1, 3.2, 3.3};
    matrix::SquareMatrix<double, 3> m(vals);
    for(size_t i = 0; i < 3; ++i)
    {
        for(size_t j = 0; j < 3; ++j)
        {
            EXPECT_DOUBLE_EQ(vals[i*3+j], m(i,j));
        }
    }
}

TEST(SquareMatrixTestSuite, TestInitializerListConstructor)
{
    matrix::SquareMatrix<double, 3> m1 = {{1.1, 1.2, 1.3}, {2.1, 2.2, 2.3}, {3.1, 3.2, 3.3}};
    EXPECT_DOUBLE_EQ(1.1, m1(0,0));
    EXPECT_DOUBLE_EQ(1.2, m1(0,1));
    EXPECT_DOUBLE_EQ(1.3, m1(0,2));
    EXPECT_DOUBLE_EQ(2.1, m1(1,0));
    EXPECT_DOUBLE_EQ(2.2, m1(1,1));
    EXPECT_DOUBLE_EQ(2.3, m1(1,2));
    EXPECT_DOUBLE_EQ(3.1, m1(2,0));
    EXPECT_DOUBLE_EQ(3.2, m1(2,1));
    EXPECT_DOUBLE_EQ(3.3, m1(2,2));

    matrix::SquareMatrix<int, 4> m2 = {{1, 2, 3, 4}, {5, 6, 7, 8}, {9, 10, 11, 12}, {13, 14, 15, 16}};
    EXPECT_EQ(1, m2(0,0));
    EXPECT_EQ(2, m2(0,1));
    EXPECT_EQ(3, m2(0,2));
    EXPECT_EQ(4, m2(0,3));
    EXPECT_EQ(5, m2(1,0));
    EXPECT_EQ(6, m2(1,1));
    EXPECT_EQ(7, m2(1,2));
    EXPECT_EQ(8, m2(1,3));
    EXPECT_EQ(9, m2(2,0));
    EXPECT_EQ(10, m2(2,1));
    EXPECT_EQ(11, m2(2,2));
    EXPECT_EQ(12, m2(2,3));
    EXPECT_EQ(13, m2(3,0));
    EXPECT_EQ(14, m2(3,1));
    EXPECT_EQ(15, m2(3,2));
    EXPECT_EQ(16, m2(3,3));
}

TEST(SquareMatrixTestSuite, TestMatrixAssignment)
{
    double vals[4] = {1.1, 1.2, 2.1, 2.2};
    matrix::Matrix<double, 2, 2> m1(vals);
    matrix::SquareMatrix<double, 2> m2;
    EXPECT_DOUBLE_EQ(0.0, m2(0,0));
    EXPECT_DOUBLE_EQ(0.0, m2(0,1));
    EXPECT_DOUBLE_EQ(0.0, m2(1,0));
    EXPECT_DOUBLE_EQ(0.0, m2(1,1));
    m2 = m1;
    EXPECT_DOUBLE_EQ(1.1, m2(0,0));
    EXPECT_DOUBLE_EQ(1.2, m2(0,1));
    EXPECT_DOUBLE_EQ(2.1, m2(1,0));
    EXPECT_DOUBLE_EQ(2.2, m2(1,1));
}

TEST(SquareMatrixTestSuite, TestMatrixAddition)
{
    int vals1[9] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    matrix::SquareMatrix<int, 3> m1(vals1);

    int vals2[9] = {2, -3, 4, 5, 6, 7, 8, 9, 10};
    matrix::SquareMatrix<int, 3> m2(vals2);

    matrix::SquareMatrix<int, 3> res = m1 + m2;
    EXPECT_EQ(3, res(0,0));
    EXPECT_EQ(-1, res(0,1));
    EXPECT_EQ(7, res(0,2));
    EXPECT_EQ(9, res(1,0));
    EXPECT_EQ(11, res(1,1));
    EXPECT_EQ(13, res(1,2));
    EXPECT_EQ(15, res(2,0));
    EXPECT_EQ(17, res(2,1));
    EXPECT_EQ(19, res(2,2));
}

TEST(SquareMatrixTestSuite, TestMatrixSubtraction)
{
    int vals1[9] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    matrix::SquareMatrix<int, 3> m1(vals1);

    int vals2[9] = {2, -3, 4, 5, 6, 7, 8, 9, 10};
    matrix::SquareMatrix<int, 3> m2(vals2);

    matrix::SquareMatrix<int, 3> res = m1 - m2;
    EXPECT_EQ(-1, res(0,0));
    EXPECT_EQ(5, res(0,1));
    EXPECT_EQ(-1, res(0,2));
    EXPECT_EQ(-1, res(1,0));
    EXPECT_EQ(-1, res(1,1));
    EXPECT_EQ(-1, res(1,2));
    EXPECT_EQ(-1, res(2,0));
    EXPECT_EQ(-1, res(2,1));
    EXPECT_EQ(-1, res(2,2));
}

TEST(SquareMatrixTestSuite, TestMatrixMultiplication)
{
    int vals1[9] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    matrix::SquareMatrix<int, 3> m1(vals1);

    int vals2[9] = {2, -3, 4, 5, 6, 7, 8, 9, 10};
    matrix::SquareMatrix<int, 3> m2(vals2);

    matrix::SquareMatrix<int, 3> res = m1 * m2;
    EXPECT_EQ(36, res(0,0));
    EXPECT_EQ(36, res(0,1));
    EXPECT_EQ(48, res(0,2));
    EXPECT_EQ(81, res(1,0));
    EXPECT_EQ(72, res(1,1));
    EXPECT_EQ(111, res(1,2));
    EXPECT_EQ(126, res(2,0));
    EXPECT_EQ(108, res(2,1));
    EXPECT_EQ(174, res(2,2));
}

TEST(SquareMatrixTestSuite, TestMatrixCompoundAddition)
{
    int vals1[9] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    matrix::SquareMatrix<int, 3> m1(vals1);

    int vals2[9] = {2, -3, 4, 5, 6, 7, 8, 9, 10};
    matrix::SquareMatrix<int, 3> m2(vals2);

    m1 += m2;
    EXPECT_EQ(3, m1(0,0));
    EXPECT_EQ(-1, m1(0,1));
    EXPECT_EQ(7, m1(0,2));
    EXPECT_EQ(9, m1(1,0));
    EXPECT_EQ(11, m1(1,1));
    EXPECT_EQ(13, m1(1,2));
    EXPECT_EQ(15, m1(2,0));
    EXPECT_EQ(17, m1(2,1));
    EXPECT_EQ(19, m1(2,2));
}

TEST(SquareMatrixTestSuite, TestMatrixCompoundSubtraction)
{
    int vals1[9] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    matrix::SquareMatrix<int, 3> m1(vals1);

    int vals2[9] = {2, -3, 4, 5, 6, 7, 8, 9, 10};
    matrix::SquareMatrix<int, 3> m2(vals2);

    m1 -= m2;
    EXPECT_EQ(-1, m1(0,0));
    EXPECT_EQ(5, m1(0,1));
    EXPECT_EQ(-1, m1(0,2));
    EXPECT_EQ(-1, m1(1,0));
    EXPECT_EQ(-1, m1(1,1));
    EXPECT_EQ(-1, m1(1,2));
    EXPECT_EQ(-1, m1(2,0));
    EXPECT_EQ(-1, m1(2,1));
    EXPECT_EQ(-1, m1(2,2));
}

TEST(SquareMatrixTestSuite, TestMatrixCompoundMultiplication)
{
    int vals1[9] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    matrix::SquareMatrix<int, 3> m1(vals1);

    int vals2[9] = {2, -3, 4, 5, 6, 7, 8, 9, 10};
    matrix::SquareMatrix<int, 3> m2(vals2);

    m1 *= m2;
    EXPECT_EQ(36, m1(0,0));
    EXPECT_EQ(36, m1(0,1));
    EXPECT_EQ(48, m1(0,2));
    EXPECT_EQ(81, m1(1,0));
    EXPECT_EQ(72, m1(1,1));
    EXPECT_EQ(111, m1(1,2));
    EXPECT_EQ(126, m1(2,0));
    EXPECT_EQ(108, m1(2,1));
    EXPECT_EQ(174, m1(2,2));
}

TEST(SquareMatrixTestSuite, TestMatrixScalarAddition)
{
    int vals[9] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    matrix::SquareMatrix<int, 3> m(vals);

    matrix::SquareMatrix<int, 3> res = m + 3;
    EXPECT_EQ(4, res(0,0));
    EXPECT_EQ(5, res(0,1));
    EXPECT_EQ(6, res(0,2));
    EXPECT_EQ(7, res(1,0));
    EXPECT_EQ(8, res(1,1));
    EXPECT_EQ(9, res(1,2));
    EXPECT_EQ(10, res(2,0));
    EXPECT_EQ(11, res(2,1));
    EXPECT_EQ(12, res(2,2));
}

TEST(SquareMatrixTestSuite, TestMatrixScalarSubtraction)
{
    int vals[9] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    matrix::SquareMatrix<int, 3> m(vals);

    matrix::SquareMatrix<int, 3> res = m - 4;
    EXPECT_EQ(-3, res(0,0));
    EXPECT_EQ(-2, res(0,1));
    EXPECT_EQ(-1, res(0,2));
    EXPECT_EQ(0, res(1,0));
    EXPECT_EQ(1, res(1,1));
    EXPECT_EQ(2, res(1,2));
    EXPECT_EQ(3, res(2,0));
    EXPECT_EQ(4, res(2,1));
    EXPECT_EQ(5, res(2,2));
}

TEST(SquareMatrixTestSuite, TestMatrixScalarMultiplication)
{
    int vals[9] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    matrix::SquareMatrix<int, 3> m(vals);

    matrix::SquareMatrix<int, 3> res = m * 2;
    EXPECT_EQ(2, res(0,0));
    EXPECT_EQ(4, res(0,1));
    EXPECT_EQ(6, res(0,2));
    EXPECT_EQ(8, res(1,0));
    EXPECT_EQ(10, res(1,1));
    EXPECT_EQ(12, res(1,2));
    EXPECT_EQ(14, res(2,0));
    EXPECT_EQ(16, res(2,1));
    EXPECT_EQ(18, res(2,2));
}

TEST(SquareMatrixTestSuite, TestMatrixScalarDivision)
{
    int vals[9] = {3, 6, 9, 12, 15, 18, 21, 24, 27};
    matrix::SquareMatrix<int, 3> m(vals);

    matrix::SquareMatrix<int, 3> res = m / 3;
    EXPECT_EQ(1, res(0,0));
    EXPECT_EQ(2, res(0,1));
    EXPECT_EQ(3, res(0,2));
    EXPECT_EQ(4, res(1,0));
    EXPECT_EQ(5, res(1,1));
    EXPECT_EQ(6, res(1,2));
    EXPECT_EQ(7, res(2,0));
    EXPECT_EQ(8, res(2,1));
    EXPECT_EQ(9, res(2,2));
}


TEST(SquareMatrixTestSuite, TestMatrixScalarCompoundAddition)
{
    int vals[9] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    matrix::SquareMatrix<int, 3> m(vals);

    m += 3;
    EXPECT_EQ(4, m(0,0));
    EXPECT_EQ(5, m(0,1));
    EXPECT_EQ(6, m(0,2));
    EXPECT_EQ(7, m(1,0));
    EXPECT_EQ(8, m(1,1));
    EXPECT_EQ(9, m(1,2));
    EXPECT_EQ(10, m(2,0));
    EXPECT_EQ(11, m(2,1));
    EXPECT_EQ(12, m(2,2));
}

TEST(SquareMatrixTestSuite, TestMatrixScalarCompoundSubtraction)
{
    int vals[9] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    matrix::SquareMatrix<int, 3> m(vals);

    m -= 4;
    EXPECT_EQ(-3, m(0,0));
    EXPECT_EQ(-2, m(0,1));
    EXPECT_EQ(-1, m(0,2));
    EXPECT_EQ(0, m(1,0));
    EXPECT_EQ(1, m(1,1));
    EXPECT_EQ(2, m(1,2));
    EXPECT_EQ(3, m(2,0));
    EXPECT_EQ(4, m(2,1));
    EXPECT_EQ(5, m(2,2));
}

TEST(SquareMatrixTestSuite, TestMatrixScalarCompoundMultiplication)
{
    int vals[9] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    matrix::SquareMatrix<int, 3> m(vals);

    m *= 2;
    EXPECT_EQ(2, m(0,0));
    EXPECT_EQ(4, m(0,1));
    EXPECT_EQ(6, m(0,2));
    EXPECT_EQ(8, m(1,0));
    EXPECT_EQ(10, m(1,1));
    EXPECT_EQ(12, m(1,2));
    EXPECT_EQ(14, m(2,0));
    EXPECT_EQ(16, m(2,1));
    EXPECT_EQ(18, m(2,2));
}

TEST(SquareMatrixTestSuite, TestMatrixScalarCompoundDivision)
{
    int vals[9] = {3, 6, 9, 12, 15, 18, 21, 24, 27};
    matrix::SquareMatrix<int, 3> m(vals);

    m /= 3;
    EXPECT_EQ(1, m(0,0));
    EXPECT_EQ(2, m(0,1));
    EXPECT_EQ(3, m(0,2));
    EXPECT_EQ(4, m(1,0));
    EXPECT_EQ(5, m(1,1));
    EXPECT_EQ(6, m(1,2));
    EXPECT_EQ(7, m(2,0));
    EXPECT_EQ(8, m(2,1));
    EXPECT_EQ(9, m(2,2));
}

TEST(SquareMatrixTestSuite, TestIdentity)
{
    int vals[9] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    matrix::SquareMatrix<int, 3> m(vals);
    EXPECT_EQ(1, m(0,0));
    EXPECT_EQ(2, m(0,1));
    EXPECT_EQ(3, m(0,2));
    EXPECT_EQ(4, m(1,0));
    EXPECT_EQ(5, m(1,1));
    EXPECT_EQ(6, m(1,2));
    EXPECT_EQ(7, m(2,0));
    EXPECT_EQ(8, m(2,1));
    EXPECT_EQ(9, m(2,2));
    m.identity();
    EXPECT_EQ(1, m(0,0));
    EXPECT_EQ(0, m(0,1));
    EXPECT_EQ(0, m(0,2));
    EXPECT_EQ(0, m(1,0));
    EXPECT_EQ(1, m(1,1));
    EXPECT_EQ(0, m(1,2));
    EXPECT_EQ(0, m(2,0));
    EXPECT_EQ(0, m(2,1));
    EXPECT_EQ(1, m(2,2));
}

TEST(SquareMatrixTestSuite, TestTrace)
{
    int vals[3][3] = {{2, -5, 3}, {3, -3, 0}, {4, 1, 6}};
    matrix::SquareMatrix<int, 3> m(vals);
    EXPECT_EQ(5, m.trace());
}

TEST(SquareMatrixTestSuite, TestMinor)
{
    matrix::SquareMatrix<int, 3> m = {{1, 2, 3}, {4, 5, 6}, {7, 8 ,9}};
    EXPECT_EQ(1, m(0,0));
    EXPECT_EQ(2, m(0,1));
    EXPECT_EQ(3, m(0,2));
    EXPECT_EQ(4, m(1,0));
    EXPECT_EQ(5, m(1,1));
    EXPECT_EQ(6, m(1,2));
    EXPECT_EQ(7, m(2,0));
    EXPECT_EQ(8, m(2,1));
    EXPECT_EQ(9, m(2,2));

    matrix::SquareMatrix<int, 2> minor1 = m.minor(0,0);
    EXPECT_EQ(5, minor1(0,0));
    EXPECT_EQ(6, minor1(0,1));
    EXPECT_EQ(8, minor1(1,0));
    EXPECT_EQ(9, minor1(1,1));

    matrix::SquareMatrix<int, 2> minor2 = m.minor(0,1);
    EXPECT_EQ(4, minor2(0,0));
    EXPECT_EQ(6, minor2(0,1));
    EXPECT_EQ(7, minor2(1,0));
    EXPECT_EQ(9, minor2(1,1));

    matrix::SquareMatrix<int, 2> minor3 = m.minor(0,2);
    EXPECT_EQ(4, minor3(0,0));
    EXPECT_EQ(5, minor3(0,1));
    EXPECT_EQ(7, minor3(1,0));
    EXPECT_EQ(8, minor3(1,1));

    matrix::SquareMatrix<int, 2> minor4 = m.minor(1,0);
    EXPECT_EQ(2, minor4(0,0));
    EXPECT_EQ(3, minor4(0,1));
    EXPECT_EQ(8, minor4(1,0));
    EXPECT_EQ(9, minor4(1,1));
    
    matrix::SquareMatrix<int, 2> minor5 = m.minor(1,1);
    EXPECT_EQ(1, minor5(0,0));
    EXPECT_EQ(3, minor5(0,1));
    EXPECT_EQ(7, minor5(1,0));
    EXPECT_EQ(9, minor5(1,1));

    matrix::SquareMatrix<int, 2> minor6 = m.minor(1,2);
    EXPECT_EQ(1, minor6(0,0));
    EXPECT_EQ(2, minor6(0,1));
    EXPECT_EQ(7, minor6(1,0));
    EXPECT_EQ(8, minor6(1,1));

    matrix::SquareMatrix<int, 2> minor7 = m.minor(2,0);
    EXPECT_EQ(2, minor7(0,0));
    EXPECT_EQ(3, minor7(0,1));
    EXPECT_EQ(5, minor7(1,0));
    EXPECT_EQ(6, minor7(1,1));

    matrix::SquareMatrix<int, 2> minor8 = m.minor(2,1);
    EXPECT_EQ(1, minor8(0,0));
    EXPECT_EQ(3, minor8(0,1));
    EXPECT_EQ(4, minor8(1,0));
    EXPECT_EQ(6, minor8(1,1));

    matrix::SquareMatrix<int, 2> minor9 = m.minor(2,2);
    EXPECT_EQ(1, minor9(0,0));
    EXPECT_EQ(2, minor9(0,1));
    EXPECT_EQ(4, minor9(1,0));
    EXPECT_EQ(5, minor9(1,1));
}

TEST(SquareMatrixTestSuite, Test1x1Determinant)
{
    matrix::SquareMatrix<int, 1> m = {{3}};
    EXPECT_EQ(3, matrix::determinant<int>(m));
}

TEST(SquareMatrixTestSuite, Test2x2Determinant)
{
    matrix::SquareMatrix<int, 2> m = {{1, 2}, {3, 4}};
    EXPECT_EQ(-2, matrix::determinant<int>(m));
}

TEST(SquareMatrixTestSuite, Test3x3Determinant)
{
    matrix::SquareMatrix<int, 3> m = {{5, -4, 2}, {0, -7, 8}, {4, -3, 5}};
    EXPECT_EQ(-127, matrix::determinant<int>(m));
}

TEST(SquareMatrixTestSuite, Test4x4Determinant)
{
    matrix::SquareMatrix<int, 4> m = {{2, 2, 6, 8}, {5, 3, -4, 5}, {3, -7, 2, 0}, {3, 5, 7, 2}};
    EXPECT_EQ(3508, matrix::determinant<int>(m));
}

TEST(SquareMatrixTestSuite, Test5x5Determinant)
{
    matrix::SquareMatrix<int, 5> m = {{3, -3, 2, 1, 4}, {4, 1, -3, 0, 4}, {2, 1, 0, 5, -2}, {3, 7, 0, 8, -1}, {4, 5, 2, 0, 2}};
    EXPECT_EQ(3523, matrix::determinant<int>(m));
}

TEST(SquareMatrixTestSuite, Test2x2InverseSuccess)
{
    double vals[2][2] = {{3, -4}, {2, 1}};
    matrix::SquareMatrix<double, 2> m(vals);
    matrix::SquareMatrix<double, 2> minv = matrix::inverse<double>(m);
    EXPECT_DOUBLE_EQ(0.0909090909090909, minv(0,0));
    EXPECT_DOUBLE_EQ(0.3636363636363636, minv(0,1));
    EXPECT_DOUBLE_EQ(-0.18181818181818182, minv(1,0));
    EXPECT_DOUBLE_EQ(0.2727272727272727, minv(1,1));
}

TEST(SquareMatrixTestSuite, Test2x2InverseNonInvertible)
{
    double vals[2][2] = {{0, 0}, {6, 5}};
    matrix::SquareMatrix<double, 2> m(vals);
    EXPECT_ANY_THROW(matrix::inverse<double>(m));
}

TEST(SquareMatrixTestSuite, Test3x3InverseSuccess)
{
    double vals[3][3] = {{3.0, 2.0, -4.0}, {0.0, -7.0, 8.0}, {11.0, 2.0, 9.0}};
    matrix::SquareMatrix<double, 3> m(vals);
    matrix::SquareMatrix<double, 3> minv = matrix::inverse<double>(m);
    EXPECT_DOUBLE_EQ(0.21409214092140921, minv(0,0));
    EXPECT_DOUBLE_EQ(0.070460704607046065, minv(0,1));
    EXPECT_DOUBLE_EQ(0.032520325203252029, minv(0,2));
    EXPECT_DOUBLE_EQ(-0.23848238482384823, minv(1,0));
    EXPECT_DOUBLE_EQ(-0.19241192411924118, minv(1,1));
    EXPECT_DOUBLE_EQ(0.065040650406504058, minv(1,2));
    EXPECT_DOUBLE_EQ(-0.20867208672086721, minv(2,0));
    EXPECT_DOUBLE_EQ(-0.043360433604336043, minv(2,1));
    EXPECT_DOUBLE_EQ(0.056910569105691054, minv(2,2));
}