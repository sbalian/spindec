#ifndef HYPERFINEPARAMETERS_H_
#define HYPERFINEPARAMETERS_H_

// SpinDec::HyperfineParameters
//
// Parameters to cacluate the hyperfine interaction between and electron
// and a nucleus in a lattice.
//
// Seto Balian, Jan 14, 2015

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
   
   bool ising_only_; // Ignore flip-flop part of interaction
   bool fermi_contact_only_; // ignore dipolar part of hyperfine interaction
  
public:
  HyperfineParameters();
  HyperfineParameters(const double lattice_constant,
      const double lattice_parameter_a,
      const double lattice_parameter_b,
      const double electron_ionization_energy,
      const double charge_density,
      const bool ising_only,
      bool fermi_contact_only_);
  
  double get_lattice_constant() const;
  double get_lattice_parameter_a() const;
  double get_lattice_parameter_b() const;
  double get_electron_ionization_energy() const;
  double get_charge_density() const;
  bool is_ising_only() const;
  bool is_fermi_contact_only() const;
  
};

} // namespace SpinDec

#endif // HYPERFINEPARAMETERS_H_
