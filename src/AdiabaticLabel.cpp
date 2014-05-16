// See AdiabaticLabel.h for description.
// Seto Balian, May 15, 2014

#include "SpinDec/AdiabaticLabel.h"

namespace SpinDec
{

AdiabaticLabel::AdiabaticLabel(const Sign& sign,
    const int quantum_number)
: sign_(sign), quantum_number_(quantum_number)
{
}

const Sign& AdiabaticLabel::get_sign() const
{
  return sign_;
}

int AdiabaticLabel::get_quantum_number() const
{
  return quantum_number_;
}


} // namespace SpinDec

