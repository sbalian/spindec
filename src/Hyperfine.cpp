// See Hyperfine.h for description.
// Seto Balian, Jun 23, 2015

#include "SpinDec/Hyperfine.h"
#include <cmath>

#include "SpinDec/Errors.h"
#include "SpinDec/Dipolar.h"
#include "SpinDec/Constants.h"

namespace SpinDec
{

double Hyperfine::envelope_function(const UInt index,
    const ThreeVector & separation) const
{
  double nbfrac = std::pow(1.0/n_times_b(),2.0);
  double nafrac = std::pow(1.0/n_times_a(),2.0);
  
  const double sep_x = separation(0);
  const double sep_y = separation(1);
  const double sep_z = separation(2);
  
  switch (index) {
  case 1:
    nbfrac *= std::pow(sep_x,2.0);
    nafrac *= (std::pow(sep_y,2.0)+std::pow(sep_z,2.0));
    break;
  case 2:
    nbfrac *= std::pow(sep_x,2.0) ;
    nafrac *= (std::pow(sep_y,2.0)+std::pow(sep_z,2.0));
    break;
  case 3:
    nbfrac *= std::pow(sep_y,2.0) ;
    nafrac *= (std::pow(sep_z,2.0)+std::pow(sep_x,2.0));
    break;
  case 4:
    nbfrac *= std::pow(sep_y,2.0) ;
    nafrac *= (std::pow(sep_z,2.0)+std::pow(sep_x,2.0));
    break;
  case 5:
    nbfrac *= std::pow(sep_z,2.0) ;
    nafrac *= (std::pow(sep_x,2.0)+std::pow(sep_y,2.0));
    break;
  case 6:
    nbfrac *= std::pow(sep_z,2.0) ;
    nafrac *= (std::pow(sep_x,2.0)+std::pow(sep_y,2.0));
    break;
  default:
    Errors::quit("Invalid argument to envelope function.");
    break;
  }
  
  // units Angstroms^(-3/2)
  return std::exp(-std::sqrt(nbfrac + nafrac))/
    (std::sqrt(Constants::kPi*std::pow(n_times_a(),2.0)*n_times_b()));

}

double Hyperfine::n_parameter() const
{
  const double electron_ie = parameters_.get_electron_ionization_energy();// eV
  // 0.029 in eV
  return std::sqrt(0.029/electron_ie);
}

double Hyperfine::n_times_a() const
{
  // Angstroms
  return n_parameter()*parameters_.get_lattice_parameter_a();
}

double Hyperfine::n_times_b() const
{
  // Angstroms
  return n_parameter()*parameters_.get_lattice_parameter_b();
}

double Hyperfine::scaled_probability_density(
    const ThreeVector & separation) const
{
  const double k0 = 0.85*2.0*Constants::kPi/
                  parameters_.get_lattice_constant();
  
  const double sep_x = separation(0);
  const double sep_y = separation(1);
  const double sep_z = separation(2);
  
  // units m^(-3)
  return  std::pow(
         envelope_function(1,separation)*std::cos(k0*sep_x)  +
       + envelope_function(3,separation)*std::cos(k0*sep_y)
       + envelope_function(5,separation)*std::cos(k0*sep_z) ,2.0)*1.0e+30;
       // TODO Beware of such multipliers
       // 1.0e+30 to convert from Angstroms to metres
}

Hyperfine::Hyperfine() : SpinInteraction(),
    parameters_(HyperfineParameters())
{
  //
}

Hyperfine::Hyperfine(const HyperfineParameters & parameters) :
    SpinInteraction(),
    parameters_(parameters)
{
}

Hyperfine::Hyperfine(const double strength)
    : SpinInteraction(strength),
      parameters_(HyperfineParameters())
{
//
}

void Hyperfine::calculate(const SpinParameters & electron_parameters,
    const SpinParameters & nuclear_parameters,
    const ThreeVector& electron_position,
    const ThreeVector& nuclear_position,
    const UniformMagneticField & field)
{
  
  if (strength_preset_ == true) {
    warn_if_preset_then_calculated();
  }
  
  // Units M rad s-1 m^3
  const double electron_gyromagnetic_ratio =
      electron_parameters.get_gyromagnetic_ratio();
  const double nuclear_gyromagnetic_ratio =
      nuclear_parameters.get_gyromagnetic_ratio();
  const double hbar = Constants::kReducedPlanck;
  const double pi = Constants::kPi;
  
  const double non_spatial_dependence =
  (16.0*pi/9.0)*1.0e-07*1.0e+06*hbar*
      electron_gyromagnetic_ratio*
      nuclear_gyromagnetic_ratio*
      parameters_.get_charge_density();
  // NOTE the 1.0e6 factor should be here because (Mega)^2


  // Units M rad s-1
  const double isotropic_part = non_spatial_dependence*
      scaled_probability_density(nuclear_position
          - electron_position);
  
  if (parameters_.is_fermi_contact_only()) {
      strength_ = isotropic_part;
      return;
  } // otherwise

  Dipolar dipolar_interaction;
  dipolar_interaction.calculate(electron_parameters,
      nuclear_parameters,electron_position
      ,nuclear_position,field);
  const double cutoff =
      (nuclear_position - electron_position).norm() - n_times_a();
 
  double anisotropic_part = 0.0;
  if (cutoff >= 0.0) {
    anisotropic_part = dipolar_interaction.get_strength();
  }
  strength_ = isotropic_part + anisotropic_part;
  return;

}

void Hyperfine::fill(ComplexMatrix * hamiltonian,
    const SpinParametersVector& spin_parameters_vector,
    const SpinBasis& basis, const UInt spin_label1,
    const UInt spin_label2) const
{
  SpinInteraction::fill_ising_flipflop(hamiltonian,spin_parameters_vector,basis,
      spin_label1,spin_label2,parameters_.is_ising_only(),CDouble(0.5,0.0));
  return;
}

shared_ptr<SpinInteraction> Hyperfine::clone() const
{
  return shared_ptr<SpinInteraction>( new Hyperfine(*this) );
}

string Hyperfine::get_type() const
{
  return "Hyperfine";
}


} // namespace SpinDec
