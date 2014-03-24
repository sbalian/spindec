// See ElectronSpin.h for description.
// Seto Balian, Mar 24, 2014

#include "SpinDec/ElectronSpin.h"
#include "SpinDec/constants.h"

namespace SpinDec
{

ElectronSpin::ElectronSpin() :
    Spin(0.5,kElectronGyromagneticRatio)
{/**/}

ElectronSpin::ElectronSpin(const double gyromagnetic_ratio) :
        Spin(0.5,gyromagnetic_ratio)
{/**/}

} // namespace SpinDec
