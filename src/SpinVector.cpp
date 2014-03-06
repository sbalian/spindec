// See SpinVector.h for description.
// Seto Balian, Mar 6, 2014

#include "SpinDec/SpinVector.h"

namespace SpinDec
{

SpinVector::SpinVector() {/**/}

SpinVector::SpinVector(const Spin & spin)
{
  push_back(spin);
}


void SpinVector::push_back(const Spin & spin)
{
  spin_vector_.push_back(spin);
  return;
}

Spin& SpinVector::operator[](const unsigned int index)
{
    return spin_vector_[index];
}

const Spin& SpinVector::operator[](const unsigned int index) const
{
  return spin_vector_[index];
}

unsigned int SpinVector::size() const
{
  return spin_vector_.size();
}

unsigned int SpinVector::get_multiplicity() const
{
  unsigned int M = 1;
  for (unsigned int i =0; i<size(); i++ ) {
    M*= (*this)[i].get_multiplicity();
  }
  return M;
}

void SpinVector::clear()
{
  spin_vector_.clear();
}

} // namespace SpinDec
