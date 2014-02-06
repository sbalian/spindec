// See NuclearSpin.h for description.
// Seto Balian, Feb 6, 2014

#include "NuclearSpin.h"

namespace SpinDecoherence
{

NuclearSpin::NuclearSpin() :
  Spin()
{/**/}

NuclearSpin::NuclearSpin(const double quantum_number, 
        const double gyromagnetic_ratio) :
  Spin(quantum_number, gyromagnetic_ratio)
{/**/}

} // namespace SpinDecoherence
