// See Dipolar.h for description.
// Seto Balian, Feb 21, 2014

#include "Dipolar.h"
#include "MathPhysConstants.h"
#include "BoostEigen.h"

#include <cmath>

namespace SpinDecoherence
{

double Dipolar::calculate() const
{
  // TODO Comment more, add units
  const double prefactor = 1.0e-31*MathPhysConstants::reduced_planck();
  const double gamma_product = spin1_.get_gyromagnetic_ratio()
                              *spin2_.get_gyromagnetic_ratio();
  const double non_spatial_dependence =prefactor*gamma_product;
  
  const double radial_dependence =
      1.0/std::pow(field_.get_magnitude(),3.0);
  const d3vector spin_separation = spin2_.get_position()-spin1_.get_position();
  const d3vector field_direction = field_.get_direction();
  const double angular_dependence =
     (1.0  - std::pow(BoostEigen::cosAngleBetween(spin_separation,
                                                  field_direction),2.0) );
  
  return non_spatial_dependence*radial_dependence*angular_dependence;
}


Dipolar::Dipolar() : SpinInteraction()
{
}

Dipolar::Dipolar(const double strength) :
        SpinInteraction(strength)
{
}

Dipolar::Dipolar(const Spin & spin1, const Spin & spin2,
    const UniformMagneticField& field) :
    SpinInteraction(spin1,spin2,field)
{
  strength_ = calculate();
}

void Dipolar::fill(cdmatrix * hamiltonian, const SpinVector& spins,
    const SpinBasis& basis, const unsigned int spin_label1,
    const unsigned int spin_label2) const
{
  SpinInteraction::fill_ising_flipflop(hamiltonian,spins,basis,
      spin_label1,spin_label2,false,cdouble(-0.25,0.0));
  return;
}

} // namespace SpinDecoherence
