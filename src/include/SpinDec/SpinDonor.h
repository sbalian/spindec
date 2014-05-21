#ifndef SPINDONOR_H_
#define SPINDONOR_H_

// SpinDec::SpinDonor
//
// Special spin interaction graph for electron-nuclear donors:
// Electron coupled to a nucleus via a preset hyperfine interaction.
//
// Analytical methods include energy levels and polarization
// obtained from Phys. Rev. Lett. 105, 067602 (2010).
//
// Seto Balian, May 21, 2014

#include "SpinDec/SpinInteractionGraph.h"
#include "SpinDec/UniformMagneticField.h"
#include "SpinDec/Hyperfine.h"
#include "SpinDec/ElectronSpinParameters.h"
#include "SpinDec/NuclearSpinParameters.h"
#include "SpinDec/AdiabaticLabel.h"

#include <vector>

#include "SpinDec/typedefs.h"

namespace SpinDec
{

// Energy levels are (adiabatic states) labeled as follows:
//
// |+/-,m> with
// integer quantum number m = - |I + S|,..., I + S (separated by 1)
// S = 1/2 (electron quantum number), I = nuclear quantum number
//
// Or labeled according to increasing energy: 1,.., (2*S+1)*(2*I+1)
// TODO Starts from 1. Make sure implementation is safe!

class SpinDonor : public SpinInteractionGraph
{
private:
  
  UniformMagneticField field_;
  ElectronSpinParameters electron_parameters_;
  NuclearSpinParameters nuclear_parameters_;
  Hyperfine hyperfine_;
  
  // Energy levels labeled 0,1,2 ... (2S+1)*(2I+1) 
  UInt upper_energy_level_; // upper energy level label for a transition
  UInt lower_energy_level_; // lower energy level label for a transition
  
  // If the donor interacts via the electron z-component spin operator (with
  // the field along z), Hamiltonian matrix elements involving the orthogonal
  // levels must be included in the Hilbert space for completeness.
  // Orthogonal levels are |pm,m> <-> |mp,m>.
  // (these orthogonal levels are included so that all the relevant Zeeman
  // basis states are included)
  
  UInt orthogonal_upper_energy_level_;
  UInt orthogonal_lower_energy_level_;
  
  void check_level(const UInt level) const;
  
  // In order of increasing energy, these are
  // |-,M-1> , |-,M-2> , ... , |-,-M>, |-,-M+1>, ... |+,+M>
  // where M = I + S
  std::vector<AdiabaticLabel> energy_levels_;
  void calc_energy_levels(); // calculates and sets energy_levels_
    
  // Private methods to calculate energies, polarization, etc. analytically
  
  // - nucleus_gyromagnetic_ratio / electron_gyromagnetic_ratio
  double delta() const;
  // electron_gyromagnetic_ratio * field_strength [M rad s-1]
  double omega() const;
  // omega / hyperfine_strength
  double scaled_omega() const;
  
  // D = m + scaled_omega*(1 + delta)
  double D(const int quantum_number) const;
  
  // O = sqrt( I*(I + 1) + 0.25 - m^2 )
  double O(const int quantum_number) const;
  
  // R = sqrt( D^2 + O^2)
  double R(const int quantum_number) const;
  
  // (A/2)*(-0.5*(1 + 4*scaled_omega*m*delta) + pm*R(m))
  // for level |+/-,m>, A = hyperfine strength. Units M rad s-1
  double eigenvalue(const AdiabaticLabel & level) const;
  
  // convert |+/-,m> levels to -> 1,2,3,...,dim(donor)
  UInt adiabatic_label_to_int_label(const AdiabaticLabel & level) const;
  // other way
  AdiabaticLabel int_label_to_adiabatic_label(const UInt level) const;
  
  // Given |+/-,m>, returns |-/+,m>.
  // If |-/+,m> does not exist (m = |M|), returns the input
  AdiabaticLabel orthogonal_level(AdiabaticLabel level) const;
  
  // D / R
  double cos_theta(const int quantum_number) const;
  // O / R
  double sin_theta(const int quantum_number) const;

  // (1/sqrt(2))*sqrt(1 + cos_theta);
  double a(const int quantum_number) const;
  // (1/sqrt(2))*sqrt(1 - cos_theta);
  double b(const int quantum_number) const;
  
  // expectation value of the electron z-component of spin
  // (for field along z) for level |+/-,m>
  // <+/-,m|S_z|+/-,m> = 0.5*+/-*(a(m)^2 - b(m)^2)
  double polarization(const AdiabaticLabel& level) const;
  
  // Gives the (at most two) Zeeman basis states
  // |mS = +/- 1/2, mI = m -/+ 1/2> and |mS = -/+ 1/2,mI = m +/- 1/2>
  // where mS = +/- 1/2 and mI = -I ... +I in integer steps for the energy
  // state |+/-,m> =
  //         a_m |mS = +/- 1/2, mI = m -/+ 1/2> 
  //     +/- b_m |mS = -/+ 1/2,mI = m +/- 1/2>
  // For m = -M, |-,-M> = |-1/2,-I> (only one Zeeman state) (M = max(m))
  // For m = +M, |+,+M> = |+1/2,+I> (only one Zeeman state)
  // |+,-M> and |-,M> don't exist.
  // For all other |+/-,m>, there are two basis states.
  SpinBasis build_basis(const AdiabaticLabel& level) const;
  
  // Like above but for multiple levels (non-zero coefficient basis states)
  SpinBasis build_basis(const std::vector<AdiabaticLabel>& levels) const;
  
  // Same as above but with integer labels for energy levels as the arguments
  SpinBasis build_basis(const UIntArray & levels) const;
  
  // This calls
  // SpinBasis build_basis(const uivector& labels) const
  // for uivector containing the upper and lower levels
  // as well as the two levels orthogonal to these.
  // Output basis has the Zeeman basis states in which the upper and lower
  // transition levels can be completely represented
  // (this is a truncated basis for speed). It includes also basis states
  // for the orthogonal levels as interactions of the donor via the z-component
  // of the electron spin involve these levels.
  SpinBasis build_truncated_basis() const;
  
  void set_transition(const UInt upper_energy_level,
      const UInt lower_energy_level);
  // Also sets orthogonal levels
    
public:
  
  SpinDonor();
  SpinDonor(const double field_strength, // Tesla
            const double nuclear_quantum_number,
            const double electron_gyromagnetic_ratio, // M rad s-1 T-1
            const double nuclear_gyromagnetic_ratio, // M rad s-1 T-1
            const double hyperfine_strength,        // M rad s-1
            const unsigned int upper_energy_level,
            const unsigned int lower_energy_level,
            const ThreeVector& electron_position, // Angstroms
            const ThreeVector& nuclear_position,  // Angstroms
            const bool complete_basis); // if set to true, the full Zeeman basis
                                        // is built (computationally intensive
                                        // for CCE - 20D for Si:Bi.). Otherwise,
                                        // the truncated basis is built -
                                 //   SpinBasis build_truncated_basis() const
                                 //   is called
  
  const UniformMagneticField& get_field() const;
  const ElectronSpinParameters& get_electron_parameters() const;
  const NuclearSpinParameters& get_nuclear_parameters() const;
  const Hyperfine& get_hyperfine() const;
  
  int max_quantum_number() const;    // I + S, S = 1/2,
                                     // I = nucleus quantum number

  // energy eigenvalue in M rad s-1
  CDouble eigenvalue(const UInt level) const;
  // always real but return complex type
  // energy levels labeled
  // 1,2 ... (2S+1)*(2I+1)
  
  UInt dimension() const; // The complete spin basis dimension.
                          // This is donor(dim) = (2S+1)*(2I+1)
  
  // See double polarization(const AdiabaticLabel& label) const
  // This takes an integer energy level label.
  // Gives expectation value of the electron z-component of spin
  // (for field along z) for input level
  double polarization(const UInt level) const;

  // Given |+/-,m>, returns |-/+,m>.
  // If |-/+,m> does not exist (m = |M|), returns the input.
  // This method takes and outputs integer energy level inputs
  // 1,2,...,donor(dim)
  unsigned int orthogonal_level(const UInt level) const;
  
};


} // namespace SpinDec

#endif // SPINDONOR_H_
