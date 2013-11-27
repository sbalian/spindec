// See NuclearSpin.h for description.
// Seto Balian, November 27, 2013

#include "NuclearSpin.h"

NuclearSpin::NuclearSpin ()
{
  set_quantum_number(0.0);
  Spin::set_gyromagnetic_ratio(0.0);
}

NuclearSpin::NuclearSpin(const double quantum_number,
                         const double gyromagnetic_ratio)
{
  set_quantum_number(quantum_number);
  Spin::set_gyromagnetic_ratio(gyromagnetic_ratio);
}

double NuclearSpin::get_quantum_number() const
{
  return quantum_number_;
}

void NuclearSpin::set_quantum_number(const double quantum_number)
{
  quantum_number_ = quantum_number;
  return;
}

unsigned int NuclearSpin::multiplicity() const
{
  return static_cast<unsigned int>( 2.0*get_quantum_number() + 1.0 );
}
