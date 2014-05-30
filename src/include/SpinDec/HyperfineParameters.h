#ifndef HYPERFINEPARAMETERS_H_
#define HYPERFINEPARAMETERS_H_

// SpinDec::HyperfineParameters
//
// Parameters to cacluate the hyperfine interaction between and electron
// and a nucleus in a lattice.
//
// Seto Balian, May 30, 2014

#include "SpinDec/typedefs.h"

namespace SpinDec
{

class HyperfineParameters
{
private:
  
   double lattice_constant_;     // Lattice constant in Angstroms
   double lattice_parameter_a_;  // Lattice parameter in Angstroms
   double lattice_parameter_b_;  // Lattice parameter in Angstroms
   double electron_ionization_energy_; 
                        // Donor electron ionization energy in eV
   double charge_density_; // charge density (dimensionless)
   string form_; // "Isotropic" (only), "Anisotropic" (only)
                           // "Full" (both of the above) (default)
  void check_form();
  
public:
  HyperfineParameters();
  HyperfineParameters(const double lattice_constant,
      const double lattice_parameter_a,
      const double lattice_parameter_b,
      const double electron_ionization_energy,
      const double charge_density);
  
  HyperfineParameters(const double lattice_constant,
      const double lattice_parameter_a,
      const double lattice_parameter_b,
      const double electron_ionization_energy,
      const double charge_density,
      const string & form);
  
  double get_lattice_constant() const;
  double get_lattice_parameter_a() const;
  double get_lattice_parameter_b() const;
  double get_electron_ionization_energy() const;
  double get_charge_density() const;
  const string& get_form() const;
  
};

} // namespace SpinDec

#endif // HYPERFINEPARAMETERS_H_
