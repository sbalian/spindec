// See UniformMagneticField.h for description.
// Seto Balian, Nov 6, 2014

#include "SpinDec/UniformMagneticField.h"

namespace SpinDec
{

UniformMagneticField::UniformMagneticField()
{
  set_magnitude(0.0);
  set_direction(ThreeVector::Zero());
}

UniformMagneticField::UniformMagneticField(const double magnitude)
{
  set_magnitude(magnitude);
  set_direction(ThreeVector::Zero());
}

UniformMagneticField::UniformMagneticField(const double magnitude,
    const ThreeVector& direction)
{
  set_magnitude(magnitude);
  set_direction(direction);
}

double UniformMagneticField::get_magnitude() const
{
  return magnitude_;
}

ThreeVector UniformMagneticField::get_direction() const
{
  return direction_;
}

void UniformMagneticField::set_magnitude(const double magnitude)
{
  magnitude_ = magnitude;
  return;
}

void UniformMagneticField::set_direction(const ThreeVector& direction)
{
  if (direction.norm() == 1.0) {
    direction_ = direction;
    return;
  } // else
  
  direction_ = direction.normalized();
  return;
  
}

} // namespace SpinDec
