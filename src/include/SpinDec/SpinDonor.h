#ifndef SPINDONOR_H_
#define SPINDONOR_H_

// SpinDec::SpinDonor
//
// Special spin system - electron-nuclear donors:
// Electron coupled to a nucleus via a preset hyperfine interaction.
//
// Analytical methods include energy levels, eigenstates and polarization
// obtained from Phys. Rev. Lett. 105, 067602 (2010).
//
// Seto Balian, Sep 2, 2014

#include "SpinDec/SpinSystem.h"

#include "SpinDec/Hyperfine.h"
#include "SpinDec/ElectronSpinParameters.h"
#include "SpinDec/NuclearSpinParameters.h"
#include "SpinDec/AdiabaticLabel.h"

#include <vector>

#include "SpinDec/typedefs.h"

namespace SpinDec
{

// Energy levels are (adiabatic states) labeled as follows,
// with adiabatic level labels:
//
// |+/-,m> with
// integer quantum number m = - |I + S|,..., I + S (separated by 1)
// S = 1/2 (electron quantum number), I = nuclear quantum number
//
// Or labeled according to increasing energy: 0,1,..., (2*S+1)*(2*I+1) - 1

class SpinDonor : public SpinSystem
{
private:
  
  // if set to true, the full Zeeman basis
  // is used (computationally intensive
  // for CCE - 20D for Si:Bi.). Otherwise,
  // the truncated basis is used, which consists of the subspaces
  // for the two levels involved in the transition (see below).
  bool complete_basis_;
  
  // For the spin interaction graph
  ElectronSpinParameters electron_parameters_;
  NuclearSpinParameters nuclear_parameters_;
  Hyperfine hyperfine_;
  
  // Energy levels labeled 0,1,2,... (2S+1)*(2I+1) - 1
  // - lower energy level label for a transition
  // - upper energy level label for a transition
  UInt transition_level_labels_[2];

  // If the donor interacts via the electron z-component spin operator (with
  // the field along z), Hamiltonian matrix elements involving the orthogonal
  // levels must be included in the Hilbert space for completeness.
  // Orthogonal levels are |pm,m> <-> |mp,m> (if they exist).
  // (these orthogonal levels are included so that all the relevant Zeeman
  // basis states are included)
  // - orthogonal lower energy level
  // - orthogonal upper energy level
  UIntArray orthogonal_level_labels_; // at most of size 2
  
  // These are the upper, lower and orthogonal levels for a non-complete
  // basis and all the energy levels for the complete basis, sorted
  // in order of increasing energy
  UIntArray sorted_level_labels_;
  // sets and sorts sorted_level_labels_ in increasing energy
  void sort_level_labels();
  UInt level_label_index(const UInt level_label) const;
                            // given level label, returns the index in
                            // sorted_level_labels_
  
  virtual void check_level_label(const UInt level_label) const;
  
  // In order of increasing energy, these are
  // |-,M-1> , |-,M-2> , ... , |-,-M>, |-,-M+1>, ... |+,+M>
  // where M = I + S
  std::vector<AdiabaticLabel> adiabatic_level_labels_;
  // calculates and sets all the adiabatic level labels
  // and adiabatic_level_labels_
  void calc_adiabatic_level_labels(); 
  
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
  double energy(const AdiabaticLabel & adiabatic_level_label) const;
  
//  virtual void set_eigenstates();
//  virtual void set_energies();
  
  // convert |+/-,m> levels to -> 0,1,2,...,dim(donor)-1
  UInt adiabatic_label_to_int_label(const AdiabaticLabel&
      adiabatic_level_label) const;
  // other way
  AdiabaticLabel int_label_to_adiabatic_label(const UInt level_label) const;
  
  // Given |+/-,m>, returns |-/+,m>.
  // If |-/+,m> does not exist (m = |M|), returns the input
  AdiabaticLabel orthogonal_adiabatic_level_label(
      AdiabaticLabel adiabatic_level_label) const;
  
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
  double polarization(const AdiabaticLabel& adiabatic_level_label) const;
  
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
  SpinBasis build_basis(const AdiabaticLabel& adiabatic_level_label) const;
  
  // Like above but for multiple levels (non-zero coefficient basis states)
  SpinBasis build_basis(const std::vector<AdiabaticLabel>&
      adiabatic_level_labels) const;
  
  // Same as above but with integer labels for energy levels as the arguments
  SpinBasis build_basis(const UIntArray & level_labels) const;
  
  // This calls
  // SpinBasis build_basis(const UIntArray & level_label) const
  // for UIntArray containing the upper and lower levels only.
  // Output basis has the Zeeman basis states in which the upper and lower
  // levels as well as the levels orthogonal to these (if they exist) can
  // be completely represented.
  // This is a complete basis for interactions of the donor via the z-component
  // of the electron spin.
  SpinBasis build_truncated_basis() const;
  
  void set_transition(const UInt lower_level_label,
      const UInt upper_level_label);
  // Also sets orthogonal levels if they exist
  
  // Given |+/-,m>, returns |-/+,m>.
  // If |-/+,m> does not exist (m = |M|), returns the input.
  // This method takes and outputs integer energy level inputs
  // 0,1,...,donor(dim)-1
  UInt orthogonal_level_label(const UInt level_label) const;
  
  // see constructors below
  void init(const double field_strength,
      const double nuclear_quantum_number,
      const double electron_gyromagnetic_ratio,
      const double nuclear_gyromagnetic_ratio,
      const double hyperfine_strength,
      const unsigned int lower_level_label,
      const unsigned int upper_level_label,
      const ThreeVector & electron_position,
      const ThreeVector & nuclear_position,
      const bool complete_basis);
    
public:
  
  SpinDonor();
  SpinDonor(const double field_strength, // Tesla
            const double nuclear_quantum_number,
            const double electron_gyromagnetic_ratio, // M rad s-1 T-1
            const double nuclear_gyromagnetic_ratio, // M rad s-1 T-1
            const double hyperfine_strength,        // M rad s-1
            const unsigned int lower_level_label,
            const unsigned int upper_level_label,
            const ThreeVector& electron_position, // Angstroms
            const ThreeVector& nuclear_position,  // Angstroms
            const bool complete_basis);
  
  const ElectronSpinParameters& get_electron_parameters() const;
  const NuclearSpinParameters& get_nuclear_parameters() const;
  const Hyperfine& get_hyperfine() const;
  
  int max_quantum_number() const;    // I + S, S = 1/2,
                                     // I = nucleus quantum number
  
  virtual UInt dimension() const; // This is the Hamiltonian dimension
  
  UInt total_multiplicity() const; // The complete spin basis dimension.
                                   // This is (2S+1)*(2I+1)
  
  virtual SpinState eigenstate(const UInt level_label) const;
  virtual double energy(const UInt level_label) const;
  
  // See double polarization(const AdiabaticLabel& label) const
  // This takes an integer energy level label.
  // Gives expectation value of the electron z-component of spin
  // (for field along z) for input level
  double polarization(const UInt level_label) const;
  
  const SpinInteractionVertex& electron_vertex() const;
  const SpinInteractionVertex& nuclear_vertex() const;
  
  const UIntArray get_orthogonal_level_labels() const;
  
};


} // namespace SpinDec

#endif // SPINDONOR_H_
