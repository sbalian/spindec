// For testing SpinDec
// sbalian, Nov 7, 2014

#include "SpinDec/base.h"

using namespace SpinDec;

int main() {

ElectronSpinParameters electron;
std::cout << electron;// << std::endl;

SpinParameters nucleus(4.5,0.0);
std::cout << nucleus;

SpinParametersVector spin_vector;

spin_vector.push_back(electron);
spin_vector.push_back(nucleus);

SpinParameters some_spin = spin_vector[0];

std::cout << some_spin.get_gyromagnetic_ratio() << std::endl;
  
return 0;

}
