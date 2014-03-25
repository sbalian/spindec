// See ElectronSpin.h for description.
// Seto Balian, Mar 25, 2014

#include "SpinDec/ElectronSpin.h"
#include "SpinDec/constants.h"

namespace SpinDec
{

ElectronSpin::ElectronSpin() : SpinHalf(kElectronGyromagneticRatio,
    ComplexVector::Zero(2),
    ThreeVector::Zero())
{
}

ElectronSpin::ElectronSpin(const ComplexVector& state_vector,
    const ThreeVector& position) : SpinHalf(kElectronGyromagneticRatio,
    state_vector,
    position)
{
}

ElectronSpin::ElectronSpin(const double gyromagnetic_ratio,
    const ComplexVector& state_vector,
    const ThreeVector& position) : SpinHalf(gyromagnetic_ratio,
    state_vector,
    position)
{
}


} // namespace SpinDec
