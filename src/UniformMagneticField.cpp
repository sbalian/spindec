// See UniformMagneticField.h for description.
// Seto Balian, Feb 6, 2014

#include "UniformMagneticField.h"

namespace SpinDecoherence
{

UniformMagneticField::UniformMagneticField()
{
  set_magnitude(0.0);
  set_direction(Eigen::Vector3d::Zero());
}

UniformMagneticField::UniformMagneticField(const double magnitude,
    const Eigen::Vector3d& direction)
{
  set_magnitude(magnitude);
  set_direction(direction);
}

double UniformMagneticField::get_magnitude() const
{
  return magnitude_;
}

Eigen::Vector3d UniformMagneticField::get_direction() const
{
  return direction_;
}

void UniformMagneticField::set_magnitude(const double magnitude)
{
  magnitude_ = magnitude;
  return;
}

void UniformMagneticField::set_direction(const Eigen::Vector3d& direction)
{
  if (direction.norm() == 1.0) {
    direction_ = direction;
    return;
  } // else
  
  direction_ = direction.normalized();
  return;
  
}

} // namespace SpinDecoherence
