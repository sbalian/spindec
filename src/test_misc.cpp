// To test SpinDecoherence
//
// Seto Balian, Dec 4, 2013

#include <iostream>
#include <Eigen/Dense>
#include <complex>
#include <cmath>
#include "MathPhysConstants.h"

std::complex<double> test_exp(const std::complex<double> & z) {

  return std::complex<double>( exp(z.real())*cos(z.imag()) ,
                               exp(z.real())*sin(z.imag()) );

}

int main () {

  
std::cout << "TESTING MathPhysConstants\n" << std::endl;

std::cout << "pi " << MathPhysConstants::pi() << std::endl;
std::cout << "h " << MathPhysConstants::plank() << std::endl;
std::cout << "hbar " << MathPhysConstants::reduced_plank() << std::endl;
std::cout << std::endl;

std::cout << "TESTING exp\n" << std::endl;

Eigen::Vector3d aVec, bVec;

aVec << 0.0, 3.3, -1.2;
bVec << 1.2, -0.2, 0.8;

std::cout << "a" << aVec << std::endl;
std::cout << "b" << bVec << std::endl;

std::cout << "Eigen exp(a)" << aVec.array().exp() << std::endl;

Eigen::Vector3d testv = (aVec.array().exp()).matrix();

std::cout << "test " << testv << std::endl;

Eigen::Array3cd complexvector(std::complex<double>(1.0,-1.0),
                             std::complex<double>(-1.0,-1.0),
                             std::complex<double>(0.0,-3.0));

std::cout << "complexvector" << complexvector << std::endl;
std::cout << "Eigen exp" << complexvector.exp() << std::endl;

std::cout << std::endl;

std::cout << "test_exp" << std::endl;
std::cout << test_exp(std::complex<double>(1.0,-1.0)) << std::endl;
std::cout << test_exp(std::complex<double>(-1.0,-1.0)) << std::endl;
std::cout << test_exp(std::complex<double>(0.0,-3.0)) << std::endl;

std::cout << std::endl;

std::cout << "polar(exp(1),-1)" << std::endl;
std::cout << std::polar( exp(1.0) , -1.0 ) << std::endl;

std::cout << std::endl;

return 0;

}
