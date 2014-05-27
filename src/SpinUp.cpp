// See SpinUp.h for description.
// Seto Balian, May 22, 2014

#include "SpinDec/SpinUp.h"

namespace SpinDec
{

SpinUp::SpinUp()
{
  init(0.0);
}

SpinUp::SpinUp(const SpinHalfParameters& spin_half_parameters) :
    SpinHalfStates()
{
  init(spin_half_parameters.get_gyromagnetic_ratio());
}

void SpinUp::init(const double gyromagnetic_ratio)
{
  state_vector_ = ComplexVector(2);
  if (gyromagnetic_ratio >= 0) {
    state_vector_(0) = CDouble(1.0,0.0);
    state_vector_(1) = CDouble(0.0,0.0);
  } else {
    state_vector_(0) = CDouble(0.0,0.0);
    state_vector_(1) = CDouble(1.0,0.0);
  }
  return;
}


} // namespace SpinDec
