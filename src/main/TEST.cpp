// To test SpinDecoherence
//
// Seto Balian 23/10/2013

#include <iostream>
#include <Eigen/Dense>
#include <complex>
#include <cmath>

#include "MathPhysConstants.h"
#include "BoostEigen.h"

std::complex<double> testexp(const std::complex<double> & z) {

  return std::complex<double>( exp(z.real())*cos(z.imag()) ,
                               exp(z.real())*sin(z.imag()) );

}

int main () {

std::cout << "pi " << MathPhysConstants::pi() << std::endl;
std::cout << "h " << MathPhysConstants::plank() << std::endl;
std::cout << "hbar " << MathPhysConstants::reduced_plank() << std::endl;

Eigen::Vector3d aVec, bVec;

aVec << 0.0, 3.3, -1.2;
bVec << 1.2, -0.2, 0.8;

std::cout << "Angle between vectors ";
std::cout << BoostEigen::cosAngleBetween(aVec,bVec) << std::endl;
std::cout << std::endl;

std::cout << aVec.array().exp() << std::endl;

Eigen::Vector3d testv = (aVec.array().exp()).matrix();

std::cout << testv << std::endl;

Eigen::Array3cd complexvector(std::complex<double>(1.0,-1.0),
                             std::complex<double>(-1.0,-1.0),
                             std::complex<double>(0.0,-3.0));
std::cout << complexvector.exp() <<  std::endl;

std::cout << std::endl;

std::cout << testexp(std::complex<double>(1.0,-1.0)) << std::endl;
std::cout << testexp(std::complex<double>(-1.0,-1.0)) << std::endl;
std::cout << testexp(std::complex<double>(0.0,-3.0)) << std::endl;

std::cout << std::endl;

std::cout << std::polar( exp(1.0) , -1.0 ) << std::endl;

return 0;

}

