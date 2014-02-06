// For testing SpinDecoherence
// Seto Balian, Feb 6, 2014

#include <iostream>
#include <complex>
#include <cmath>

#include <Eigen/Dense>

#include "MathPhysConstants.h"

using namespace SpinDecoherence;

std::complex<double> test_exp(const std::complex<double> & z)
{
  return std::complex<double>( exp(z.real())*std::cos(z.imag()) ,
                               exp(z.real())*std::sin(z.imag()) );
}

int main() {
  
std::cout << "pi " << MathPhysConstants::pi() << std::endl;
std::cout << "h " << MathPhysConstants::planck() << std::endl;
std::cout << "hbar " << MathPhysConstants::reduced_planck() << std::endl;
std::cout << std::endl;


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


