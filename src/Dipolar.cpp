// See Dipolar.h for description.
// Seto Balian, Nov 6, 2014

#include "SpinDec/Dipolar.h"
#include "SpinDec/constants.h"
#include "SpinDec/BoostEigen.h"

#include <cmath>

namespace SpinDec
{

void Dipolar::calculate(const SpinParameters & spin_parameters1,
    const SpinParameters & spin_parameters2,
    const ThreeVector & position1, const ThreeVector & position2,
    const UniformMagneticField & field)
{
  
  if (strength_preset_ == true) {
    warn_if_preset_then_calculated();
  }
  
  // TODO Comment more, add units
  const double prefactor = 1.0e29*kReducedPlanck;
  const double gamma_product = spin_parameters1.get_gyromagnetic_ratio()
                              *spin_parameters2.get_gyromagnetic_ratio();
  const double non_spatial_dependence =prefactor*gamma_product;
  const ThreeVector spin_separation = position2-position1;
  
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

void Dipolar::fill(ComplexMatrix * hamiltonian,
    const SpinParametersVector& spin_parameters_vector,
    const SpinBasis& basis, const UInt spin_label1,
    const UInt spin_label2) const
{
  SpinInteraction::fill_ising_flipflop(hamiltonian,spin_parameters_vector,basis,
      spin_label1,spin_label2,false,CDouble(-0.25,0.0));
  return;
}

auto_ptr<SpinInteraction> Dipolar::clone() const
{
  return auto_ptr<SpinInteraction>( new Dipolar(*this) );
}

} // namespace SpinDec
