// See ElectronSpinParameters.h for description.
// Seto Balian, Sep 25, 2014

#include "SpinDec/ElectronSpinParameters.h"
#include "SpinDec/constants.h"

namespace SpinDec
{

ElectronSpinParameters::ElectronSpinParameters() :
    SpinHalfParameters(kElectronGyromagneticRatio)
{
}

ElectronSpinParameters::ElectronSpinParameters(
    const double gyromagnetic_ratio) :
    SpinHalfParameters(gyromagnetic_ratio)
{
}

} // namespace SpinDec
