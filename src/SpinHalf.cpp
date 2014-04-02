// See SpinHalf.h for description.
// Seto Balian, Apr 2, 2014

#include "SpinDec/SpinHalf.h"
#include "SpinDec/Errors.h"

namespace SpinDec
{

SpinHalf::SpinHalf() : SpinState(SpinBasis(SpinHalfParameters()))
{
/**/
}

void SpinHalf::set_state_vector(const ComplexVector& state_vector)
{
  Errors::quit("Can't change spin half state vector.");
  return;
}

void SpinHalf::set_element(const UInt index, const CDouble& element)
{
  Errors::quit("Can't change spin half state vector.");
  return;
}

void SpinHalf::set_element(const UInt index, const double element)
{
  Errors::quit("Can't change spin half state vector.");
  return;
}

SpinHalf::~SpinHalf()
{
/**/
}

} // namespace SpinDec
