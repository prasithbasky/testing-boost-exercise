#define BOOST_TEST_DYN_LINK
#include <Eigen/Dense>
#include <boost/test/unit_test.hpp>
#include <cstdio>
#include <stdexcept>
#include "matrixIO.hpp"

BOOST_AUTO_TEST_SUITE(IOTests)

BOOST_AUTO_TEST_CASE(OpenDataReadsMatrix)
{
  const int matrixSize = 3;

  Eigen::MatrixXd expected(matrixSize, matrixSize);
  expected << 0.680375, 0.59688, -0.329554,
      -0.211234, 0.823295, 0.536459,
      0.566198, -0.604897, -0.444451;

  Eigen::MatrixXd result = IOTests::openData("../data/m3.csv", matrixSize);

  BOOST_TEST(result.rows() == expected.rows());
  BOOST_TEST(result.cols() == expected.cols());
  BOOST_TEST(result.isApprox(expected, 1e-6));
}

BOOST_AUTO_TEST_CASE(OpenDataThrowsOnWrongSize)
{
  BOOST_CHECK_THROW(IOTests::openData("../data/m3.csv", 4), std::runtime_error);
}

BOOST_AUTO_TEST_CASE(SaveDataAndOpenDataRoundtrip)
{
  const char *fileName = "test_matrix_io.csv";

  Eigen::MatrixXd expected(2, 2);
  expected << 1.25, -2.5,
      3.75, 4.0;

  IOTests::saveData(fileName, expected);
  Eigen::MatrixXd result = IOTests::openData(fileName, 2);

  BOOST_TEST(result.isApprox(expected, 1e-12));

  std::remove(fileName);
}

BOOST_AUTO_TEST_SUITE_END()