// To test SpinDecoherence
//
// Seto Balian 04/10/2013

#include <iostream>
#include <Eigen/Dense>

#include "MathPhysConstants.h"
#include "ExtendEigen.h"

int main () {

std::cout << "pi " << MathPhysConstants::pi() << std::endl;
std::cout << "h " << MathPhysConstants::plank() << std::endl;
std::cout << "hbar " << MathPhysConstants::reduced_plank() << std::endl;

Eigen::Vector3d aVec, bVec;

aVec << 0.0, 3.3, -1.2;
bVec << 1.2, -0.2, 0.8;

std::cout << "Angle between vectors ";
std::cout << ExtendEigen::cosineAngleBetween(aVec,bVec) << std::endl;
std::cout << std::endl;

return 0;

}

