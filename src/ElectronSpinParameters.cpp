// See ElectronSpinParameters.h for description.
// Seto Balian, Jun 23, 2015

#include "SpinDec/ElectronSpinParameters.h"
#include "SpinDec/Constants.h"

namespace SpinDec
{

ElectronSpinParameters::ElectronSpinParameters() :
    SpinHalfParameters(Constants::kElectronGyromagneticRatio)
{
}

ElectronSpinParameters::ElectronSpinParameters(
    const double gyromagnetic_ratio) :
    SpinHalfParameters(gyromagnetic_ratio)
{
}

} // namespace SpinDec
