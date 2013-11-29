// See SpinVector.h for description.
// Seto Balian, November 29, 2013

#include "SpinVector.h"

SpinVector::SpinVector() {/**/}

void SpinVector::push_back(const Spin & spin)
{
  spin_vector_.push_back(spin);
  return;
}

Spin SpinVector::get_spin(const unsigned int index) const
{
  return spin_vector_[index];
}

void SpinVector::set_spin(const unsigned int index, const Spin & spin)
{
  spin_vector_[index] = spin;
  return;
}

unsigned int SpinVector::size() const
{
  return spin_vector_.size();
}
  
unsigned int SpinVector::get_multiplicity() const
{
  unsigned int M = 1;
  for (unsigned int i =0; i<size(); i++ ) {
    M*= get_spin(i).Spin::get_multiplicity();
  }
  return M;
}
