// See ElectronSpinParameters.h for description.
// Seto Balian, Mar 31, 2014

#include "SpinDec/ElectronSpinParameters.h"
#include "SpinDec/constants.h"

namespace SpinDec
{

ElectronSpinParameters::ElectronSpinParameters() :
    SpinParameters(0.5,kElectronGyromagneticRatio)
{
}

ElectronSpinParameters::ElectronSpinParameters(
    const double gyromagnetic_ratio) :
        SpinParameters(0.5,gyromagnetic_ratio)
{
}

} // namespace SpinDec

