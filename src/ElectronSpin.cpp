// See ElectronSpin.h for description.
// Seto Balian, Dec 3, 2013

#include "ElectronSpin.h"
#include "MathPhysConstants.h"

ElectronSpin::ElectronSpin() :
  Spin(0.5,MathPhysConstants::electron_gyromagnetic_ratio(),2)
{/**/}

ElectronSpin::ElectronSpin(const double gyromagnetic_ratio) :
  Spin(0.5,gyromagnetic_ratio,2)
{/**/}
