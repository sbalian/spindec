// See NuclearSpin.h for description.
// Seto Balian, Mar 24, 2014

#include "SpinDec/NuclearSpin.h"

namespace SpinDec
{

NuclearSpin::NuclearSpin() :
  Spin()
{/**/}

NuclearSpin::NuclearSpin(const double quantum_number,
    const double gyromagnetic_ratio) : Spin(quantum_number,gyromagnetic_ratio)
{/**/}

} // namespace SpinDec
