// To test SpinDecoherence
//
// Seto Balian, Dec 3, 2013

#include <iostream>
#include "Spin.h"
#include "ElectronSpin.h"
#include "NuclearSpin.h"
#include "SpinVector.h"

int main () {

SpinVector spin_vector;
ElectronSpin electron;
NuclearSpin nucleus;

spin_vector.push_back(electron);
spin_vector.push_back(nucleus);

Spin some_spin = spin_vector.get_spin(0);

std::cout << some_spin.get_gyromagnetic_ratio() << std::endl;

return 0;

}
