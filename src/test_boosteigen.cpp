// For testing SpinDecoherence
// Seto Balian, Feb 6, 2014

#include <iostream>

#include "BoostEigen.h"
#include <Eigen/Dense>

using namespace SpinDecoherence;

int main() {

Eigen::Vector3d a_3vec, b_3vec;
a_3vec << 0.0, 3.3, -1.2;
b_3vec << 1.2, -0.2, 0.8;

std::cout << "Vector a_3vec\n" << a_3vec << std::endl;
std::cout << "Vector b_3vec\n" << b_3vec << std::endl;

std::cout << "Cosine of angle between a_3vec and b_3vec is ";
std::cout << BoostEigen::cosAngleBetween(a_3vec,b_3vec) << std::endl;
std::cout << std::endl;

std::cout << "Maximum of absolute coefficients of a_3vec is ";
std::cout << BoostEigen::maxAbsCoeff(a_3vec) << std::endl;

Eigen::ArrayXXd A_array(2,3);
A_array << 0.5, 3.3, 6.0,
           1.1, 4.4, 8.9;
std::cout << "Array A_array\n" << A_array << std::endl;

Eigen::VectorXcd c_3cvec(3);
c_3cvec << std::complex<double>(2.0,4.4),
           std::complex<double>(1.0,3.4),
           std::complex<double>(2.0,-4.4);
std::cout << "Complex vector c_3cvec\n" << c_3cvec << std::endl;
std::cout << "Exponential of c_3cvec is\n";
std::cout << BoostEigen::exp(c_3cvec) << std::endl;
//std::cout << "Exponential of a_3vec is\n";
//std::cout << BoostEigen::exp(a_3vec) << std::endl;

Eigen::ArrayXXd rand1;
rand1.setRandom(4,3);

Eigen::ArrayXd rand2;
rand2.setRandom(4);

std::cout << "rand1\n";
std::cout << rand1 << std::endl;
std::cout << "rand2\n";
std::cout << rand2 << std::endl;

Eigen::ArrayXXd joined(4,4);
joined << rand1, rand2;

std::cout << "joined\n";
std::cout << joined << std::endl;

Eigen::MatrixXcd matrix1 = Eigen::MatrixXcd::Random(2,2);
Eigen::MatrixXcd matrix2 = Eigen::MatrixXcd::Random(2,2);

std::cout << "matrix1\n";
std::cout << matrix1 << std::endl;

std::cout << "matrix2\n";
std::cout << matrix2 << std::endl;

std::cout << "matrix1 X(tensor) matrix2\n";
std::cout << BoostEigen::tensorProduct(matrix1,matrix2) << std::endl;

Eigen::VectorXcd vector1 = Eigen::VectorXcd::Random(2);
Eigen::VectorXcd vector2 = Eigen::VectorXcd::Random(2);

std::cout << "vector1\n";
std::cout << vector1 << std::endl;

std::cout << "vector2\n";
std::cout << vector2 << std::endl;

std::cout << "vector1 X(tensor) vector2\n";
std::cout << BoostEigen::tensorProduct(vector1,vector2) << std::endl;

return 0;

}
