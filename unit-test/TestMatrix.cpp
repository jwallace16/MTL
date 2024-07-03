///////////////////////////////////////////////////////////////////////////////
//!
//! @file TestMatrix.cpp
//!
//! Unit test for Matrix.hpp
//!
//! @author David Wallace <jdavidwallace1@gmail.com>
///////////////////////////////////////////////////////////////////////////////

#include <iostream>
#include <gtest/gtest.h>
#include "../src/Matrix.hpp"

TEST(MatrixTestSuite, TestDefaultCreation)
{
    matrix::Matrix<double, 3,3> m1;
    for(size_t i = 0; i < 3; ++i)
    {
        for(size_t j = 0; j < 3; ++j)
        {
            EXPECT_DOUBLE_EQ(0.0, m1(i,j));
        }
    }

    matrix::Matrix<float, 1, 3> m2;
    for(size_t i = 0; i < 1; ++i)
    {
        for(size_t j = 0; j < 3; ++j)
        {
            EXPECT_FLOAT_EQ(0.0, m2(i,j));
        }
    }

    matrix::Matrix<int, 3, 1> m3;
    for(size_t i = 0; i < 3; ++i)
    {
        for(size_t j = 0; j < 1; ++j)
        {
            EXPECT_EQ(0, m3(i,j));
        }
    }

    matrix::Matrix<char, 2, 2> m4;
    for(size_t i = 0; i < 2; ++i)
    {
        for(size_t j = 0; j < 2; ++j)
        {
            EXPECT_EQ(0, m4(i,j));
        }
    }
}

TEST(MatrixTestSuite, Test2DArrayCreation)
{
    double vals1[2][3] = {{1.1, 1.2, 1.3}, {2.1, 2.2, 2.3}};
    matrix::Matrix<double, 2, 3> m1(vals1);
    EXPECT_DOUBLE_EQ(1.1, m1(0,0));
    EXPECT_DOUBLE_EQ(1.2, m1(0,1));
    EXPECT_DOUBLE_EQ(1.3, m1(0,2));
    EXPECT_DOUBLE_EQ(2.1, m1(1,0));
    EXPECT_DOUBLE_EQ(2.2, m1(1,1));
    EXPECT_DOUBLE_EQ(2.3, m1(1,2));
    EXPECT_NE(vals1[0][1], m1(1,0));
    
    double vals2[3][2] = {{1.1, 1.2}, {2.1, 2.2}, {3.1, 3.2}};
    matrix::Matrix<double, 3, 2> m2(vals2);
    EXPECT_DOUBLE_EQ(1.1, m2(0,0));
    EXPECT_DOUBLE_EQ(1.2, m2(0,1));
    EXPECT_DOUBLE_EQ(2.1, m2(1,0));
    EXPECT_DOUBLE_EQ(2.2, m2(1,1));
    EXPECT_DOUBLE_EQ(3.1, m2(2,0));
    EXPECT_DOUBLE_EQ(3.2, m2(2,1));
}

TEST(MatrixTestSuite, TestFlatArrayCreation)
{
    double values[6] = {0.0, 1.0, 2.0, 3.0, 4.0, 5.0};
    matrix::Matrix<double, 2, 3> m(values);
    EXPECT_DOUBLE_EQ(0.0, m(0,0));
    EXPECT_DOUBLE_EQ(1.0, m(0,1));
    EXPECT_DOUBLE_EQ(2.0, m(0,2));
    EXPECT_DOUBLE_EQ(3.0, m(1,0));
    EXPECT_DOUBLE_EQ(4.0, m(1,1));
    EXPECT_DOUBLE_EQ(5.0, m(1,2));
}

TEST(MatrixTestSuite, TestInitializerListConstructor)
{
    matrix::Matrix<double, 2, 2> m1 = {{1.1, 1.2}, {2.1, 2.2}};
    EXPECT_DOUBLE_EQ(1.1, m1(0,0));
    EXPECT_DOUBLE_EQ(1.2, m1(0,1));
    EXPECT_DOUBLE_EQ(2.1, m1(1,0));
    EXPECT_DOUBLE_EQ(2.2, m1(1,1));

    matrix::Matrix<double, 3, 2> m2 = {{1.1, 1.2}, {2.1, 2.2}, {3.1, 3.2}};
    EXPECT_DOUBLE_EQ(1.1, m2(0,0));
    EXPECT_DOUBLE_EQ(1.2, m2(0,1));
    EXPECT_DOUBLE_EQ(2.1, m2(1,0));
    EXPECT_DOUBLE_EQ(2.2, m2(1,1));
    EXPECT_DOUBLE_EQ(3.1, m2(2,0));
    EXPECT_DOUBLE_EQ(3.2, m2(2,1));

    matrix::Matrix<int, 2, 2> m3;
    m3 = {{1, 2}, {3, 4}};
    EXPECT_EQ(1, m3(0,0));
    EXPECT_EQ(2, m3(0,1));
    EXPECT_EQ(3, m3(1,0));
    EXPECT_EQ(4, m3(1,1));
}

TEST(MatrixTestSuite, TestCopyConstructor)
{
    matrix::Matrix<int, 2, 2> m1;
    m1(0,0) = 1;
    m1(0,1) = 2;
    m1(1,0) = 3;
    m1(1,1) = 4;
    matrix::Matrix<int, 2, 2> m2 = m1;
    EXPECT_EQ(m1(0,0), m2(0,0));
    EXPECT_EQ(m1(0,1), m2(0,1));
    EXPECT_EQ(m1(1,0), m2(1,0));
    EXPECT_EQ(m1(1,1), m2(1,1));
}

// TEST(MatrixTestSuite, TestTypeString)
// {
//     matrix::Matrix<double, 1, 1> m;
//     EXPECT_STRCASEEQ("Matrix", m.typeString());
// }

// TEST(MatrixTestSuite, TestPutStr)
// {
//     double vals[9] = {1.1, 1.2, 1.3, 2.1, 2.2, 2.3, 3.1, 3.2, 3.3};
//     matrix::Matrix<double, 3, 3> m(vals);
//     char result[100];
//     m.put_string(result, 100);
//     char expected[100] = "1.1   1.2   1.3   \n2.1   2.2   2.3   \n3.1   3.2   3.3   \n";
//     EXPECT_STRCASEEQ(expected, result);
// }

TEST(MatrixTestSuite, TestElementAccessOperator)
{
    matrix::Matrix<int, 1, 2> m;
    m(0,0) = 4;
    m(0,1) = -3;
    EXPECT_EQ(4, m(0,0));
    EXPECT_EQ(-3, m(0,1));
}

TEST(MatrixTestSuite, TestMatrixAddition)
{
    int vals1[4] = {1,2,3,4};
    int vals2[4] = {4,3,2,1};
    matrix::Matrix<int, 2, 2> m1(vals1);
    matrix::Matrix<int, 2, 2> m2 (vals2);
    matrix::Matrix<int, 2, 2> result = m1 + m2;
    EXPECT_EQ(5, result(0,0));
    EXPECT_EQ(5, result(0,1));
    EXPECT_EQ(5, result(1,0));
    EXPECT_EQ(5, result(1,1));
}

TEST(MatrixTestSuite, TestMatrixScalarAddition)
{
    double vals[4] = {0.0, 1.0, 2.0, 3.0};
    matrix::Matrix<double, 2, 2> m(vals);
    matrix::Matrix<double, 2, 2> result = m + 3.0;
    EXPECT_DOUBLE_EQ(3.0, result(0,0));
    EXPECT_DOUBLE_EQ(4.0, result(0,1));
    EXPECT_DOUBLE_EQ(5.0, result(1,0));
    EXPECT_DOUBLE_EQ(6.0, result(1,1));
}

TEST(MatrixTestSuite, TestMatrixCompoundAddition)
{
    int vals1[4] = {7,7,7,7};
    int vals2[4] = {-4, 3, 8, 1};
    matrix::Matrix<int, 2, 2> m1(vals1);
    matrix::Matrix<int, 2, 2> m2(vals2);
    m2 += m1;
    EXPECT_EQ(3, m2(0,0));
    EXPECT_EQ(10, m2(0,1));
    EXPECT_EQ(15, m2(1,0));
    EXPECT_EQ(8, m2(1,1));
}

TEST(MatrixTestSuite, TestMatrixScalarCompoundAddition)
{
    double vals[4] = {0.0, 1.0, 2.0, 3.0};
    matrix::Matrix<double, 2, 2> m(vals);
    m += 3.0;
    EXPECT_DOUBLE_EQ(3.0, m(0,0));
    EXPECT_DOUBLE_EQ(4.0, m(0,1));
    EXPECT_DOUBLE_EQ(5.0, m(1,0));
    EXPECT_DOUBLE_EQ(6.0, m(1,1));
}

TEST(MatrixTestSuite, TestMatrixSubtraction)
{
    int vals1[4] = {7,2,9,1};
    int vals2[4] = {1,2,8,9};
    matrix::Matrix<int, 2, 2> m1(vals1);
    matrix::Matrix<int, 2, 2> m2 (vals2);
    matrix::Matrix<int, 2, 2> result = m1 - m2;
    EXPECT_EQ(6, result(0,0));
    EXPECT_EQ(0, result(0,1));
    EXPECT_EQ(1, result(1,0));
    EXPECT_EQ(-8, result(1,1));
}

TEST(MatrixTestSuite, TestMatrixScalarSubtraction)
{
    double vals[4] = {4.0, 3.0, 2.0, 1.0};
    matrix::Matrix<double, 2, 2> m1(vals);
    matrix::Matrix<double, 2, 2> m2 = m1 - 7.0;
    EXPECT_DOUBLE_EQ(-3.0, m2(0,0));
    EXPECT_DOUBLE_EQ(-4.0, m2(0,1));
    EXPECT_DOUBLE_EQ(-5.0, m2(1,0));
    EXPECT_DOUBLE_EQ(-6.0, m2(1,1));
}

TEST(MatrixTestSuite, TestMatrixCompoundSubtraction)
{
    int vals1[4] = {7,7,7,7};
    int vals2[4] = {-4, 3, 8, 7};
    matrix::Matrix<int, 2, 2> m1(vals1);
    matrix::Matrix<int, 2, 2> m2(vals2);
    m2 -= m1;
    EXPECT_EQ(-11, m2(0,0));
    EXPECT_EQ(-4, m2(0,1));
    EXPECT_EQ(1, m2(1,0));
    EXPECT_EQ(0, m2(1,1));
}

TEST(MatrixTestSuite, TestMatrixScalarCompoundSubtraction)
{
    double vals[4] = {7.0, -1.0, 3.3, 2.1};
    matrix::Matrix<double, 2, 2> m(vals);
    m -= 5.0;
    EXPECT_DOUBLE_EQ(2.0, m(0,0));
    EXPECT_DOUBLE_EQ(-6.0, m(0,1));
    EXPECT_DOUBLE_EQ(-1.7, m(1,0));
    EXPECT_DOUBLE_EQ(-2.9, m(1,1));
}

TEST(MatrixTestSuite, TestMatrixUnaryMinus)
{
    int vals[4] = {7, 3, -8, 0};
    matrix::Matrix<int, 2, 2> m(vals);
    matrix::Matrix<int, 2, 2> result = -m;
    EXPECT_EQ(-7, result(0,0));
    EXPECT_EQ(-3, result(0,1));
    EXPECT_EQ(8, result(1,0));
    EXPECT_EQ(0, result(1,1));
}

TEST(MatrixTestSuite, TestSquareMatrixMatrixMultiply)
{
    double vals[9] = {1.1, 1.2, 1.3, 2.1, 2.2, 2.3, 3.1, 3.2, 3.3};
    matrix::Matrix<double, 3, 3> m1(vals);
    matrix::Matrix<double, 3, 3> m2(vals);
    matrix::Matrix<double, 3, 3> result = m1 * m2;
    EXPECT_DOUBLE_EQ(7.76, result(0,0));
    EXPECT_DOUBLE_EQ(8.12, result(0,1));
    EXPECT_DOUBLE_EQ(8.48, result(0,2));
    EXPECT_DOUBLE_EQ(14.06, result(1,0));
    EXPECT_DOUBLE_EQ(14.72, result(1,1));
    EXPECT_DOUBLE_EQ(15.38, result(1,2));
    EXPECT_DOUBLE_EQ(20.36, result(2,0));
    EXPECT_DOUBLE_EQ(21.32, result(2,1));
    EXPECT_DOUBLE_EQ(22.28, result(2,2));
}

TEST(MatrixTestSuite, TestNonSquareMatrixMatrixMultiply)
{
    double vals1[4][2] = {{1.1, 1.2}, {2.1, 2.2}, {3.1, 3.2}, {4.1, 4.2}};
    double vals2[2][4] = {{1.1, 1.2, 1.3, 1.4}, {2.1, 2.2, 2.3, 2.4}};
    matrix::Matrix<double, 4, 2> m1(vals1);
    matrix::Matrix<double, 2, 4> m2(vals2);
    matrix::Matrix<double, 4, 4> result = m1 * m2;

    EXPECT_DOUBLE_EQ(3.73, result(0,0));
    EXPECT_DOUBLE_EQ(3.96, result(0,1));
    EXPECT_DOUBLE_EQ(4.19, result(0,2));
    EXPECT_DOUBLE_EQ(4.42, result(0,3));
    EXPECT_DOUBLE_EQ(6.93, result(1,0));
    EXPECT_DOUBLE_EQ(7.36, result(1,1));
    EXPECT_DOUBLE_EQ(7.79, result(1,2));
    EXPECT_DOUBLE_EQ(8.22, result(1,3));
    EXPECT_DOUBLE_EQ(10.13, result(2,0));
    EXPECT_DOUBLE_EQ(10.76, result(2,1));
    EXPECT_DOUBLE_EQ(11.39, result(2,2));
    EXPECT_DOUBLE_EQ(12.02, result(2,3));
    EXPECT_DOUBLE_EQ(13.33, result(3,0));
    EXPECT_DOUBLE_EQ(14.16, result(3,1));
    EXPECT_DOUBLE_EQ(14.99, result(3,2));
    EXPECT_DOUBLE_EQ(15.82, result(3,3));
}

TEST(MatrixTestSuite, TestMatrixScalarMultiply)
{
    double vals[4] = {1.1, 2.2, 3.3, 4.4};
    matrix::Matrix<double, 2, 2> m(vals);
    matrix::Matrix<double, 2, 2> result1 = m * 4.2;
    EXPECT_DOUBLE_EQ(4.62, result1(0,0));
    EXPECT_DOUBLE_EQ(9.24, result1(0,1));
    EXPECT_DOUBLE_EQ(13.86, result1(1,0));
    EXPECT_DOUBLE_EQ(18.48, result1(1,1));

    matrix::Matrix<double, 2, 2> result2 = 4.2 * m;
    EXPECT_DOUBLE_EQ(4.62, result2(0,0));
    EXPECT_DOUBLE_EQ(9.24, result2(0,1));
    EXPECT_DOUBLE_EQ(13.86, result2(1,0));
    EXPECT_DOUBLE_EQ(18.48, result2(1,1));
}

TEST(MatrixTestSuite, TestCompoundSquareMatrixMatrixMultiply)
{
    double vals1[9] = {1.1, 1.2, 1.3, 2.1, 2.2, 2.3, 3.1, 3.2, 3.3};
    double vals2[9] = {3.3, 3.2, 3.1, 2.3, 2.2, 2.1, 1.3, 1.2, 1.1};
    matrix::Matrix<double, 3, 3> m1(vals1);
    matrix::Matrix<double, 3, 3> m2(vals2);
    m2 *= m1;
    EXPECT_DOUBLE_EQ(19.96, m2(0,0));
    EXPECT_DOUBLE_EQ(20.92, m2(0,1));
    EXPECT_DOUBLE_EQ(21.88, m2(0,2));
    EXPECT_DOUBLE_EQ(13.66, m2(1,0));
    EXPECT_DOUBLE_EQ(14.32, m2(1,1));
    EXPECT_DOUBLE_EQ(14.98, m2(1,2));
    EXPECT_DOUBLE_EQ(7.36, m2(2,0));
    EXPECT_DOUBLE_EQ(7.72, m2(2,1));
    EXPECT_DOUBLE_EQ(8.08, m2(2,2));
}

TEST(MatrixTestSuite, TestCompoundMatrixScalarMultiply)
{
    double vals[4] = {1.0, 2.0, 3.0, 4.0};
    matrix::Matrix<double, 2, 2> m(vals);
    m*=3.0;
    EXPECT_DOUBLE_EQ(3.0, m(0,0));
    EXPECT_DOUBLE_EQ(6.0, m(0,1));
    EXPECT_DOUBLE_EQ(9.0, m(1,0));
    EXPECT_DOUBLE_EQ(12.0, m(1,1));
}

TEST(MatrixTestSuite, TestMatrixScalarDivision)
{
    double vals[4] = {5.0, -10.0, 1.0, 200.0};
    matrix::Matrix<double, 2, 2> m(vals);
    matrix::Matrix<double, 2, 2> result = m / 5.0;
    EXPECT_DOUBLE_EQ(1.0, result(0,0));
    EXPECT_DOUBLE_EQ(-2.0, result(0,1));
    EXPECT_DOUBLE_EQ(0.2, result(1,0));
    EXPECT_DOUBLE_EQ(40.0, result(1,1));
}

TEST(MatrixTestSuite, TestMatrixScalarCompoundDivision)
{
    double vals[4] = {5.0, -10.0, 1.0, 200.0};
    matrix::Matrix<double, 2, 2> m(vals);
    m /= 5.0;
    EXPECT_DOUBLE_EQ(1.0, m(0,0));
    EXPECT_DOUBLE_EQ(-2.0, m(0,1));
    EXPECT_DOUBLE_EQ(0.2, m(1,0));
    EXPECT_DOUBLE_EQ(40.0, m(1,1));
}

TEST(MatrixTestSuite, TestSquareMatrixTranspose)
{
    double vals[9] = {1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0};
    matrix::Matrix<double, 3, 3> m(vals);
    matrix::Matrix<double, 3, 3> result = m.transpose();
    EXPECT_DOUBLE_EQ(m(0,0), result(0,0));
    EXPECT_DOUBLE_EQ(m(0,1), result(1,0));
    EXPECT_DOUBLE_EQ(m(0,2), result(2,0));
    EXPECT_DOUBLE_EQ(m(1,0), result(0,1));
    EXPECT_DOUBLE_EQ(m(1,1), result(1,1));
    EXPECT_DOUBLE_EQ(m(1,2), result(2,1));
    EXPECT_DOUBLE_EQ(m(2,0), result(0,2));
    EXPECT_DOUBLE_EQ(m(2,1), result(1,2));
    EXPECT_DOUBLE_EQ(m(2,2), result(2,2));
}

TEST(MatrixTestSuite, TestNonSquareMatrixTranspose)
{
    double vals[4][2] = {{1.1, 1.2}, {2.1, 2.2}, {3.1, 3.2}, {4.1, 4.2}};
    matrix::Matrix<double, 4, 2> m(vals);
    matrix::Matrix<double, 2, 4> result = m.transpose();
    EXPECT_DOUBLE_EQ(m(0,0), result(0,0));
    EXPECT_DOUBLE_EQ(m(1,0), result(0,1));
    EXPECT_DOUBLE_EQ(m(2,0), result(0,2));
    EXPECT_DOUBLE_EQ(m(3,0), result(0,3));
    EXPECT_DOUBLE_EQ(m(0,1), result(1,0));
    EXPECT_DOUBLE_EQ(m(1,1), result(1,1));
    EXPECT_DOUBLE_EQ(m(2,1), result(1,2));
    EXPECT_DOUBLE_EQ(m(3,1), result(1,3));
}

TEST(MatrixTestSuite, TestRowSwap)
{
    int vals[3][3] = {{1, 1, 1}, {2, 2, 2}, {3, 3, 3}};
    matrix::Matrix<int, 3, 3> m(vals);
    EXPECT_EQ(1, m(0,0));
    EXPECT_EQ(1, m(0,1));
    EXPECT_EQ(1, m(0,2));
    EXPECT_EQ(2, m(1,0));
    EXPECT_EQ(2, m(1,1));
    EXPECT_EQ(2, m(1,2));
    EXPECT_EQ(3, m(2,0));
    EXPECT_EQ(3, m(2,1));
    EXPECT_EQ(3, m(2,2));

    m.swapRows(0, 1);
    EXPECT_EQ(2, m(0,0));
    EXPECT_EQ(2, m(0,1));
    EXPECT_EQ(2, m(0,2));
    EXPECT_EQ(1, m(1,0));
    EXPECT_EQ(1, m(1,1));
    EXPECT_EQ(1, m(1,2));
    EXPECT_EQ(3, m(2,0));
    EXPECT_EQ(3, m(2,1));
    EXPECT_EQ(3, m(2,2));
}

TEST(MatrixTestSuite, TestColSwap)
{
    int vals[3][3] = {{1, 2, 3}, {1, 2, 3}, {1, 2, 3}};
    matrix::Matrix<int, 3, 3> m(vals);
    EXPECT_EQ(1, m(0,0));
    EXPECT_EQ(2, m(0,1));
    EXPECT_EQ(3, m(0,2));
    EXPECT_EQ(1, m(1,0));
    EXPECT_EQ(2, m(1,1));
    EXPECT_EQ(3, m(1,2));
    EXPECT_EQ(1, m(2,0));
    EXPECT_EQ(2, m(2,1));
    EXPECT_EQ(3, m(2,2));

    m.swapCols(0, 1);
    EXPECT_EQ(2, m(0,0));
    EXPECT_EQ(1, m(0,1));
    EXPECT_EQ(3, m(0,2));
    EXPECT_EQ(2, m(1,0));
    EXPECT_EQ(1, m(1,1));
    EXPECT_EQ(3, m(1,2));
    EXPECT_EQ(2, m(2,0));
    EXPECT_EQ(1, m(2,1));
    EXPECT_EQ(3, m(2,2));
}

TEST(MatrixTestSuite, TestSetAllValues)
{
    int vals[4] = {0, 0, 0, 0};
    matrix::Matrix<int, 2, 2> m(vals);
    EXPECT_EQ(0, m(0,0));
    EXPECT_EQ(0, m(0,1));
    EXPECT_EQ(0, m(1,0));
    EXPECT_EQ(0, m(1,1));

    m.setValue(7);
    EXPECT_EQ(7, m(0,0));
    EXPECT_EQ(7, m(0,1));
    EXPECT_EQ(7, m(1,0));
    EXPECT_EQ(7, m(1,1));
}

TEST(MatrixTestSuite, TestAbsVal)
{
    double vals1[3][3] = {{-1.0, 2.0, -3.0}, {4.0, -5.0, 6.0}, {-7.0, 8.0, -9.0}};
    matrix::Matrix<double, 3, 3> m1(vals1);
    matrix::Matrix<double, 3, 3> r1 = m1.abs();
    EXPECT_DOUBLE_EQ(1.0, r1(0,0));
    EXPECT_DOUBLE_EQ(2.0, r1(0,1));
    EXPECT_DOUBLE_EQ(3.0, r1(0,2));
    EXPECT_DOUBLE_EQ(4.0, r1(1,0));
    EXPECT_DOUBLE_EQ(5.0, r1(1,1));
    EXPECT_DOUBLE_EQ(6.0, r1(1,2));
    EXPECT_DOUBLE_EQ(7.0, r1(2,0));
    EXPECT_DOUBLE_EQ(8.0, r1(2,1));
    EXPECT_DOUBLE_EQ(9.0, r1(2,2));

    int vals2[2][2] = {{-6, 5}, {-4, 3}};
    matrix::Matrix<int, 2, 2> m2(vals2);
    matrix::Matrix<int, 2, 2> r2 = m2.abs();
    EXPECT_EQ(6, r2(0,0));
    EXPECT_EQ(5, r2(0,1));
    EXPECT_EQ(4, r2(1,0));
    EXPECT_EQ(3, r2(1,1));
}

TEST(MatrixTestSuite, TestSubmatrixSuccess)
{
    int vals1[9] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    matrix::Matrix<int, 3, 3> m1(vals1);

    matrix::Matrix<int, 2, 2> res1 = m1.submatrix<2, 2>(1, 0, 2, 1);
    std::cout << res1 << std::endl;
}

// TEST(MatrixTestSuite, TestZerosIntFunction)
// {
//     matrix::Matrix<int, 2, 2> m = matrix::zeros<int, 2, 2>();
//     EXPECT_EQ(0, m(0,0));
//     EXPECT_EQ(0, m(0,1));
//     EXPECT_EQ(0, m(1,0));
//     EXPECT_EQ(0, m(1,1));
// }

// TEST(MatrixTestSuite, TestZerosDoubleFunction)
// {
//     matrix::Matrix<double, 2, 2> m = matrix::zeros<double, 2, 2>();
//     EXPECT_EQ(0.0, m(0,0));
//     EXPECT_EQ(0.0, m(0,1));
//     EXPECT_EQ(0.0, m(1,0));
//     EXPECT_EQ(0.0, m(1,1));
// }

// TEST(MatrixTestSuite, TestOnesIntFunction)
// {
//     matrix::Matrix<int, 2, 2> m = matrix::ones<int, 2, 2>();
//     EXPECT_EQ(1, m(0,0));
//     EXPECT_EQ(1, m(0,1));
//     EXPECT_EQ(1, m(1,0));
//     EXPECT_EQ(1, m(1,1));
// }

// TEST(MatrixTestSuite, TestOnesDoubleFunction)
// {
//     matrix::Matrix<double, 2, 2> m = matrix::ones<double, 2, 2>();
//     EXPECT_EQ(1.0, m(0,0));
//     EXPECT_EQ(1.0, m(0,1));
//     EXPECT_EQ(1.0, m(1,0));
//     EXPECT_EQ(1.0, m(1,1));
// }

TEST(MatrixTestSuite, TestScalarMatrixMultiplication)
{
    int vals[4] = {1, 2, 3, 4};
    matrix::Matrix<int, 2, 2> m(vals);
    matrix::Matrix<int, 2, 2> result = 4 * m;
    EXPECT_EQ(4, result(0,0));
    EXPECT_EQ(8, result(0,1));
    EXPECT_EQ(12, result(1,0));
    EXPECT_EQ(16, result(1,1));
}

TEST(MatrixTestSuite, TestOStreamOutputSquareInts)
{
    int vals[9] = {1,2,3,4,5,6,7,8,9};
    matrix::Matrix<int, 3, 3> m(vals);
    std::cout << m << std::endl;
}

TEST(MatrixTestSuite, TestOStreamOutputNonsquareInts)
{
    int vals[4][2] = {{1,2}, {3,4}, {5,6}, {7,8}};
    matrix::Matrix<int, 4, 2> m(vals);
    std::cout << m << std::endl;
}

TEST(MatrixTestSuite, TestOStreamOutputDoubles)
{
    double vals[3][3] = {{1.1, 1.2, 1.3}, {2.1, 2.2, 2.3}, {3.1, 3.2, 3.3}};
    matrix::Matrix<double, 3, 3> m(vals);
    std::cout << m << std::endl;
}