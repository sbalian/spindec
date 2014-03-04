// See UniformMagneticField.h for description.
// Seto Balian, Mar 3, 2014

#include "UniformMagneticField.h"

namespace SpinDecoherence
{

UniformMagneticField::UniformMagneticField()
{
  set_magnitude(0.0);
  set_direction(d3vector::Zero());
}

UniformMagneticField::UniformMagneticField(const double magnitude)
{
  set_magnitude(magnitude);
  set_direction(d3vector::Zero());
}

UniformMagneticField::UniformMagneticField(const double magnitude,
    const d3vector& direction)
{
  set_magnitude(magnitude);
  set_direction(direction);
}

double UniformMagneticField::get_magnitude() const
{
  return magnitude_;
}

d3vector UniformMagneticField::get_direction() const
{
  return direction_;
}

void UniformMagneticField::set_magnitude(const double magnitude)
{
  magnitude_ = magnitude;
  return;
}

void UniformMagneticField::set_direction(const d3vector& direction)
{
  if (direction.norm() == 1.0) {
    direction_ = direction;
    return;
  } // else
  
  direction_ = direction.normalized();
  return;
  
}

} // namespace SpinDecoherence
