// See HyperfineParameters.h for description.
// Seto Balian, Jan 14, 2015

#include "SpinDec/HyperfineParameters.h"
#include "SpinDec/Errors.h"

namespace SpinDec
{


HyperfineParameters::HyperfineParameters() :
lattice_constant_(0.0),
lattice_parameter_a_(0.0),
lattice_parameter_b_(0.0),
electron_ionization_energy_(0.0),
charge_density_(0.0),
ising_only_(false),
fermi_contact_only_(true)
{
  //
}

HyperfineParameters::HyperfineParameters(const double lattice_constant,
    const double lattice_parameter_a, const double lattice_parameter_b,
    const double electron_ionization_energy, const double charge_density,
    const bool ising_only,
    const bool fermic_contact_only) :
        lattice_constant_(lattice_constant),
        lattice_parameter_a_(lattice_parameter_a),
        lattice_parameter_b_(lattice_parameter_b),
        electron_ionization_energy_(electron_ionization_energy),
        charge_density_(charge_density),
        ising_only_(ising_only),
        fermi_contact_only_(fermic_contact_only)
{
  //
}


double HyperfineParameters::get_lattice_constant() const
{
  return lattice_constant_;
}

double HyperfineParameters::get_lattice_parameter_a() const
{
  return lattice_parameter_a_;
}

double HyperfineParameters::get_lattice_parameter_b() const
{
  return lattice_parameter_b_;
}

double HyperfineParameters::get_electron_ionization_energy() const
{
  return electron_ionization_energy_;
}

double HyperfineParameters::get_charge_density() const
{
  return charge_density_;
}

bool HyperfineParameters::is_ising_only() const
{
  return ising_only_;
}

bool HyperfineParameters::is_fermi_contact_only() const
{
  return fermi_contact_only_;
}


} // namespace SpinDec

