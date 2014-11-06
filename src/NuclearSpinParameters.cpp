// See NuclearSpinParameters.h for description.
// Seto Balian, Nov 6, 2014

#include "SpinDec/NuclearSpinParameters.h"

namespace SpinDec
{

NuclearSpinParameters::NuclearSpinParameters() : SpinParameters()
{
}

NuclearSpinParameters::NuclearSpinParameters(const double quantum_number,
               const double gyromagnetic_ratio) :
    SpinParameters(quantum_number,gyromagnetic_ratio)
{
}

} // namespace SpinDec
