// See AdiabaticLabel.h for description.
// Seto Balian, Nov 6, 2014

#include "SpinDec/AdiabaticLabel.h"

#include <iomanip>

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

std::ostream& operator<<(std::ostream& os, AdiabaticLabel const & label)
{

  os << "|" << label.get_sign() << "," << label.get_quantum_number() << ">";
  
  return os;
  
}



} // namespace SpinDec

