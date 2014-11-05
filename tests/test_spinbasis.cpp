// For testing SpinDec
// Seto Balian, Mar 31, 2014

#include <iostream>

#include "SpinDec/base.h"

using namespace SpinDec;

int main() {
  
Eigen::ArrayXXd basis1;
Eigen::ArrayXd basis2;

std::cout << basis1.rows() << "\t" << basis1.cols() << std::endl;
std::cout << basis2.rows() << "\t" << basis2.cols() << std::endl;

basis1 = basis2;

std::cout << basis1.rows() << "\t" << basis1.cols() << std::endl;

ElectronSpinParameters electron;
SpinParameters nucleus(4.5,0.0);

SpinBasis electron_basis (electron);
SpinBasis nucleus_basis (nucleus);

std::cout << "Electron basis\n" << electron_basis << std::endl;
std::cout << "Nucleus basis\n" << nucleus_basis << std::endl;

SpinBasis combined;
combined = nucleus_basis^((electron_basis)^(electron_basis));

std::cout << "Combined basis\n" << combined << std::endl;

SpinBasis combined2 = electron_basis^electron_basis;
SpinBasis combined3 = combined2^combined2;

std::cout << "test\n" << combined2 << std::endl;
std::cout << "test\n" << combined3 << std::endl;

Eigen::ArrayXd custom_basis_elements(2);

custom_basis_elements(0) = -0.5;
custom_basis_elements(1) = 1.5;

SpinBasis custom_electron_basis(custom_basis_elements);

SpinBasis joined_basis = electron_basis+custom_electron_basis;
std::cout << "joined\n" << joined_basis << std::endl;
SpinBasis combined4 = joined_basis^electron_basis;
std::cout << "test\n" << combined4 << std::endl;

SpinBasis fail_join = electron_basis+combined4;

return 0;

}


