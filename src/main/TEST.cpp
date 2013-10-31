// To test SpinDecoherence
//
// Seto Balian 31/10/2013

#include <iostream>
#include <Eigen/Dense>
#include <complex>
#include <cmath>

#include "MathPhysConstants.h"
#include "BoostEigen.h"
#include "ZeemanBasis.h"
#include "NuclearSpin.h"
#include "ElectronSpin.h"

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

std::cout << "TESTING BoostEigen\n" << std::endl;

Eigen::Vector3d aVec, bVec;

aVec << 0.0, 3.3, -1.2;
bVec << 1.2, -0.2, 0.8;

std::cout << "a" << aVec << std::endl;
std::cout << "b" << bVec << std::endl;

std::cout << "Angle between a and b ";
std::cout << BoostEigen::cosAngleBetween(aVec,bVec) << std::endl;
std::cout << std::endl;

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

std::cout << "TESTING ZeemanBasis + dependencies\n" << std::endl;

Spins donor;

NuclearSpin nucleus(4.5,10,Eigen::Vector3d::Zero());
ElectronSpin electron;

donor.add_spin(electron);
donor.add_spin(nucleus);
donor.add_spin(electron);


ZeemanBasis test_basis;
test_basis.set_spins(donor);

test_basis.build();

std::cout << "basis" << std::endl;
std::cout << test_basis.get_basis() << std::endl;

Eigen::ArrayXXd to_keep(3,2);

to_keep << 0.5 , 4.5,
          -0.5, 2.5,
           0.5, -1.5;

std::vector<unsigned int> indices;

indices.push_back(0);
indices.push_back(1);

test_basis.truncate(indices,to_keep);

std::cout << "truncated" << std::endl;
std::cout << test_basis.get_basis() << std::endl;


return 0;

}
