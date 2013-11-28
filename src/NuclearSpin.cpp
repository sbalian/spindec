// See NuclearSpin.h for description.
// Seto Balian, November 28, 2013

#include "NuclearSpin.h"

NuclearSpin::NuclearSpin() :
  Spin()
{/**/}

NuclearSpin::NuclearSpin(const double quantum_number,
                         const double gyromagnetic_ratio) :
  Spin(quantum_number, gyromagnetic_ratio)
{/**/}
