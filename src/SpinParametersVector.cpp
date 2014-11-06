// See SpinParametersVector.h for description.
// Seto Balian, Nov 6, 2014

#include "SpinDec/SpinParametersVector.h"

namespace SpinDec
{

SpinParametersVector::SpinParametersVector() {/**/}

SpinParametersVector::SpinParametersVector(
    const SpinParameters & spin_parameters)
{
  push_back(spin_parameters);
}


void SpinParametersVector::push_back(const SpinParameters & spin_parameters)
{
  spin_parameters_vector_.push_back(spin_parameters);
  return;
}

SpinParameters& SpinParametersVector::operator[](const UInt index)
{
    return spin_parameters_vector_[index];
}

const SpinParameters& SpinParametersVector::operator[](const UInt index) const
{
  return spin_parameters_vector_[index];
}

UInt SpinParametersVector::size() const
{
  return spin_parameters_vector_.size();
}

UInt SpinParametersVector::multiplicity() const
{
  UInt M = 1;
  for (UInt i =0; i<size(); i++ ) {
    M*= (*this)[i].get_multiplicity();
  }
  return M;
}

void SpinParametersVector::clear()
{
  spin_parameters_vector_.clear();
}

} // namespace SpinDec
