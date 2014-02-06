// See ElectronSpin.h for description.
// Seto Balian, Feb 6, 2014

#include "ElectronSpin.h"
#include "MathPhysConstants.h"

namespace SpinDecoherence
{

ElectronSpin::ElectronSpin() :
  Spin(0.5,MathPhysConstants::electron_gyromagnetic_ratio(),2)
{/**/}

ElectronSpin::ElectronSpin(const double gyromagnetic_ratio) :
  Spin(0.5,gyromagnetic_ratio,2)
{/**/}

} // namespace SpinDecoherence
