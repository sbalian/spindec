// For testing SpinDecoherence
// Seto Balian, Jan 29, 2014

#include <iostream>

#include "Spin.h"
#include "ElectronSpin.h"
#include "NuclearSpin.h"
#include "SpinVector.h"

int main() {
  
ElectronSpin electron;
std::cout << electron;// << std::endl;

NuclearSpin nucleus(4.5,0.0);
std::cout << nucleus;
  
SpinVector spin_vector;

spin_vector.push_back(electron);
spin_vector.push_back(nucleus);

Spin some_spin = spin_vector[0];

std::cout << some_spin.get_gyromagnetic_ratio() << std::endl;
  
return 0;

}
