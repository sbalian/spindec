// See Dipolar.h for description.
// Seto Balian, Jan 31, 2014

#include "Dipolar.h"
#include "MathPhysConstants.h"
#include "BoostEigen.h"
#include <cmath>

double Dipolar::calculate_non_spatial_dependence() const
{
  const double prefactor = 1.0e-31*MathPhysConstants::reduced_plank();
  const double gamma_product = spin1_.get_gyromagnetic_ratio()
                              *spin2_.get_gyromagnetic_ratio();
  return prefactor*gamma_product;
}

Dipolar::Dipolar() : SpinInteraction()
{
  //
}

Dipolar::Dipolar(const Spin& spin1, const Spin& spin2,
    const UniformMagneticField& field) : SpinInteraction(spin1, spin2, field)
{
  non_spatial_dependence_ = calculate_non_spatial_dependence();
}

Dipolar::Dipolar(const Spin& spin1, const Spin& spin2, const double strength,
    const UniformMagneticField& field) :
        SpinInteraction(spin1,spin2,field,strength)
{
  non_spatial_dependence_ = calculate_non_spatial_dependence();
}

double Dipolar::calculate(const Eigen::Vector3d& position1,
    const Eigen::Vector3d& position2)
{
  double strength = 0.0;
  const double radial_dependence =
      1.0/std::pow(get_field().get_magnitude(),3.0);
  const Eigen::Vector3d spin_separation = position2 - position1;
  const Eigen::Vector3d field_direction = get_field().get_direction();
  const double angular_dependence =
     (1.0  - std::pow(BoostEigen::cosAngleBetween(spin_separation,
                                                  field_direction),2.0) );
  
  strength = non_spatial_dependence_*radial_dependence*angular_dependence;
  set_strength(strength);
  return strength;
}

void Dipolar::fill(Eigen::MatrixXcd * hamiltonian, const SpinVector& spins,
    const SpinBasis& basis, const unsigned int spin_label1,
    const unsigned int spin_label2) const
{
  SpinInteraction::fill_ising_flipflop(hamiltonian,spins,basis,
      spin_label1,spin_label2,false,std::complex<double>(-0.25,0.0));
  return;
}
