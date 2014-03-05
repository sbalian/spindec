// See Dipolar.h for description.
// Seto Balian, Mar 5, 2014

#include "Dipolar.h"
#include "MathPhysConstants.h"
#include "BoostEigen.h"

#include <cmath>

namespace SpinDecoherence
{

void Dipolar::calculate(const Spin & spin1, const Spin & spin2,
    const UniformMagneticField & field)
{
  
  if (strength_preset_ == true) {
    warn_if_preset_then_calculated();
  }
  
  // TODO Comment more, add units
  const double prefactor = 1.0e29*MathPhysConstants::reduced_planck();
  const double gamma_product = spin1.get_gyromagnetic_ratio()
                              *spin2.get_gyromagnetic_ratio();
  const double non_spatial_dependence =prefactor*gamma_product;
  const ThreeVector spin_separation = spin2.get_position()-spin1.get_position();
  
  const double radial_dependence =
      1.0/std::pow(spin_separation.norm(),3.0);
  const ThreeVector field_direction = field.get_direction();
  const double angular_dependence =
     (1.0  - 3.0*std::pow(BoostEigen::cosAngleBetween(spin_separation,
                                                  field_direction),2.0) );
  
  strength_ = non_spatial_dependence*radial_dependence*angular_dependence;
  return;
}

Dipolar::Dipolar() : SpinInteraction()
{
}

Dipolar::Dipolar(const double strength) :
        SpinInteraction(strength)
{
}

void Dipolar::fill(ComplexMatrix * hamiltonian, const SpinVector& spins,
    const SpinBasis& basis, const unsigned int spin_label1,
    const unsigned int spin_label2) const
{
  SpinInteraction::fill_ising_flipflop(hamiltonian,spins,basis,
      spin_label1,spin_label2,false,cdouble(-0.25,0.0));
  return;
}

} // namespace SpinDecoherence
