// See UniformMagneticField.h for description.
// Seto Balian, November 26, 2013

#include "UniformMagneticField.h"
#include "Named.h"

UniformMagneticField::UniformMagneticField()
{
  Named::set_class_name("UniformMagneticField");
}

UniformMagneticField::UniformMagneticField(const double magnitude,
                       const Eigen::Vector3d & direction)
{
  set_magnitude(magnitude);
  set_direction(direction);
  Named::set_class_name("UniformMagneticField");
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

void UniformMagneticField::set_direction(const Eigen::Vector3d & direction)
{
  direction_ = direction;
  return;
}
