// See Dipolar.h for description.
// Seto Balian, November 26, 2013

#include "Dipolar.h"
#include "MathPhysConstants.h"

#include "BoostEigen.h"
#include "SpinInteraction.h"

#include <cmath>

Dipolar::Dipolar()
{
  Named::set_class_name("Dipolar");
}

// See header for description
void Dipolar::calculate(const Spin & spin_1,
                        const Spin & spin_2,
                        const UniformMagneticField & field)
{
  
  const double prefactor = 1.0e-31*MathPhysConstants::reduced_plank();
  const double gamma_product = spin_1.get_gyromagnetic_ratio()
                              *spin_2.get_gyromagnetic_ratio();
  const double radial_dependence = 1.0/std::pow(field.get_magnitude(),3.0);

  
  const Eigen::Vector3d spin_separation = spin_2.get_position()
                                          - spin_1.get_position();
  const Eigen::Vector3d field_direction = field.get_direction();
  const double angular_dependence =
       (1.0  - std::pow(BoostEigen::cosAngleBetween(spin_separation,
                                                    field_direction),2.0) );

  
  SpinInteraction::set_strength(prefactor*gamma_product*
                                radial_dependence*angular_dependence);
  return;
  
}
