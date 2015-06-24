#ifndef HYPERFINEPARAMETERS_H_
#define HYPERFINEPARAMETERS_H_

// Seto Balian, Jun 24, 2015

#include "SpinDec/typedefs.h"

namespace SpinDec
{

/**
 * Parameters to cacluate the hyperfine interaction between an electron spin
 * and a nuclear spin in a lattice.
 */
class HyperfineParameters
{
private:
  
   /// Lattice constant in \f$\mbox{\AA}\f$.
   double lattice_constant_;     
   /// Lattice parameter in \f$\mbox{\AA}\f$.
   double lattice_parameter_a_;
   /// Lattice parameter in \f$\mbox{\AA}\f$.
   double lattice_parameter_b_;
   /// Donor electron ionization energy in eV.
   double electron_ionization_energy_; 
   /// Charge density (dimensionless).
   double charge_density_; 
   
   /// Ignore flip-flop part of interaction.
   bool ising_only_; 
   /// ignore dipolar part of hyperfine interaction.
   bool fermi_contact_only_; 
  
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
