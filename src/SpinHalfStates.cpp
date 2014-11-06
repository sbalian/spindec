// See SpinHalfStates.h for description.
// Seto Balian, Nov 6, 2014

#include "SpinDec/SpinHalfStates.h"
#include "SpinDec/Errors.h"

namespace SpinDec
{

SpinHalfStates::SpinHalfStates() : SpinState(SpinBasis(SpinHalfParameters()))
{
/**/
}

void SpinHalfStates::set_state_vector(const ComplexVector& state_vector)
{
  Errors::quit("Can't change spin half state vector.");
  return;
}

void SpinHalfStates::set_element(const UInt index, const CDouble& element)
{
  Errors::quit("Can't change spin half state vector.");
  return;
}

void SpinHalfStates::set_element(const UInt index, const double element)
{
  Errors::quit("Can't change spin half state vector.");
  return;
}

SpinHalfStates::~SpinHalfStates()
{
/**/
}

} // namespace SpinDec
