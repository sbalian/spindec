// See ElectronSpin.h for description.
// Seto Balian, November 27, 2013

#include "ElectronSpin.h"
#include "MathPhysConstants.h"

#include "Errors.h"

ElectronSpin::ElectronSpin()
{
  Spin::set_gyromagnetic_ratio(
                            MathPhysConstants::electron_gyromagnetic_ratio());
}

ElectronSpin::ElectronSpin(const double gyromagnetic_ratio)
{
  Spin::set_gyromagnetic_ratio(gyromagnetic_ratio);
}

double ElectronSpin::get_quantum_number() const
{
  return 0.5;
}

unsigned int ElectronSpin::multiplicity() const
{
  return 2;
}
