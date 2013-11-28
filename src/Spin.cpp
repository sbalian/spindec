// See Spin.h for description.
// Seto Balian, November 28, 2013

#include "Spin.h"

unsigned int Spin::calculate_multiplicity() const
{
  return static_cast<unsigned int> (2.0*Spin::get_quantum_number() + 1.0);
}

Spin::Spin(const double quantum_number, const double gyromagnetic_ratio,
           const unsigned int multiplicity) :
  quantum_number_(quantum_number),
  gyromagnetic_ratio_(gyromagnetic_ratio),
  multiplicity_(multiplicity)
{/**/}


Spin::Spin() :
  quantum_number_(0.0),
  gyromagnetic_ratio_(0.0),
  multiplicity_(0.0)
{/**/}

Spin::Spin(const double quantum_number,
           const double gyromagnetic_ratio) :
  quantum_number_(quantum_number),
  gyromagnetic_ratio_(gyromagnetic_ratio),
  multiplicity_(calculate_multiplicity())
{/**/}

double Spin::get_gyromagnetic_ratio() const
{
  return gyromagnetic_ratio_;
}

double Spin::get_quantum_number() const
{
  return quantum_number_;
}

double Spin::get_multiplicity() const
{
  return multiplicity_;
}
