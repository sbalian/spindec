// See SpinHalfParameters.h for description.
// Seto Balian, Sep 25, 2014

#include "SpinDec/SpinHalfParameters.h"

namespace SpinDec
{

SpinHalfParameters::SpinHalfParameters() : SpinParameters(0.5,0.0)
{
}

SpinHalfParameters::SpinHalfParameters(const double gyromagnetic_ratio) :
    SpinParameters(0.5,gyromagnetic_ratio)
{
}

} // namespace SpinDec

