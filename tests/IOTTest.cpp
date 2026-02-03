#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>
#include <fstream>
#include <cstdio>
#include "matrixIO.hpp"
#include <Eigen/Dense>

using namespace Eigen;

struct IOFixture {
    std::string filename;

    IOFixture() {
        filename = "test_matrix.csv";
        std::ofstream outfile(filename);
        outfile << "1.0, 2.0\n";
        outfile << "3.0, 4.0\n";
        outfile.close();
    }

    ~IOFixture() {
        std::remove(filename.c_str());
    }
};

BOOST_FIXTURE_TEST_SUITE(IOTests, IOFixture)

BOOST_AUTO_TEST_CASE(OpenDataTest) {
    int rows = 2;
    int cols = 2;
    
    MatrixXd expected(rows, cols);
    expected << 1.0, 2.0,
                3.0, 4.0;

    MatrixXd result = matrixIO::openData(filename, rows, cols);

    BOOST_TEST(result.rows() == rows);
    BOOST_TEST(result.cols() == cols);
    
    BOOST_TEST((result - expected).norm() == 0.0, boost::test_tools::tolerance(1e-9));
}

BOOST_AUTO_TEST_SUITE_END()
