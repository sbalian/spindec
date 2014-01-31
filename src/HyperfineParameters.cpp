// See HyperfineParameters.h for description.
// Seto Balian, Jan 31, 2014

#include "HyperfineParameters.h"
#include "Errors.h"

void HyperfineParameters::check_form()
{
  if (form_ == "Full") {
    return;
  }
  if (form_ == "Isotropic") {
    return;
  }
  if (form_ == "Anisotropic") {
    return;
  }
  Errors::quit("Invalid form for Hyperfine interaction.");
  return;
}


HyperfineParameters::HyperfineParameters() :
lattice_constant_(0.0),
lattice_parameter_a_(0.0),
lattice_parameter_b_(0.0),
electron_ionization_energy_(0.0),
charge_density_(0.0),
form_("Full")
{
  //
}

HyperfineParameters::HyperfineParameters(const double lattice_constant,
    const double lattice_parameter_a, const double lattice_parameter_b,
    const double electron_ionization_energy, const double charge_density) :
        lattice_constant_(lattice_constant),
        lattice_parameter_a_(lattice_parameter_a),
        lattice_parameter_b_(lattice_parameter_b),
        electron_ionization_energy_(electron_ionization_energy),
        charge_density_(charge_density),
        form_("Full")
{
  //
}

HyperfineParameters::HyperfineParameters(const double lattice_constant,
    const double lattice_parameter_a, const double lattice_parameter_b,
    const double electron_ionization_energy, const double charge_density,
    const std::string& form) :
        lattice_constant_(lattice_constant),
        lattice_parameter_a_(lattice_parameter_a),
        lattice_parameter_b_(lattice_parameter_b),
        electron_ionization_energy_(electron_ionization_energy),
        charge_density_(charge_density),
        form_(form)
{
  check_form();
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

std::string HyperfineParameters::get_form() const
{
  return form_;
}

