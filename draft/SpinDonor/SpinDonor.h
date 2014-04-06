#ifndef SPINDONOR_H_
#define SPINDONOR_H_

// SpinDec::SpinDonor
//
// Electron coupled to a nucleus via a preset hyperfine interaction.
// Analytical methods include energy levels and polarization
// obtained from Phys. Rev. Lett. 105, 067602 (2010).
//
// Seto Balian, Mar 31, 2014

#include "SpinDec/SpinInteractionGraph.h"
#include "SpinDec/UniformMagneticField.h"
#include "SpinDec/Hyperfine.h"
#include "SpinDec/ElectronSpinParameters.h"

#include <vector>

#include "SpinDec/typedefs.h"

namespace SpinDec
{

// Energy levels are (adiabatic states) labeled as follows:
// |slot1,slot2>
struct AdiabaticLabel;
// slot1 - sign (plus or minus)
// slot2 - quantum number m
//
// |pm,m> (pm=+/-, mp = -/+)
//
// integer quantum number m = - |I + S|,..., I + S (separated by 1)
// S = 1/2 (electron quantum number), I = nuclear quantum number

class SpinDonor : public SpinInteractionGraph
{
private:
  
  UniformMagneticField field_;
  ElectronSpinParameters electron_parameters_;
  SpinParameters nucleus_parameters_;
  Hyperfine hyperfine_;
  
  // Energy levels labeled 0,1,2 ... (2S+1)*(2I+1) 
  unsigned int upper_level_label_; // upper energy level label for a transition
  unsigned int lower_level_label_; // lower energy level label for a transition
  // If the donor interacts via the electron z-component spin operator (with
  // the field along z), Hamiltonian matrix elements involving the orthogonal
  // levels must be included in the Hilbert space for completeness.
  // Orthogonal levels are |pm,m> <-> |mp,m>.
  // (these orthogonal levels are included so that all the relevant Zeeman
  // basis states are included)
  unsigned int orthogonal_upper_level_label_;
  unsigned int orthogonal_lower_level_label_;
  
  // In order of increasing energy, these are
  // |-,M-1> , |-,M-2> , ... , |-,-M>, |-,-M+1>, ... |+,+M>
  // where M = I + S
  std::vector<AdiabaticLabel> energy_level_labels_;
  void calc_energy_level_labels(); // calculates and sets energy_level_labels_
  
  // Builds graph consisting of electron and nucleus interacting via the
  // hyperfine interaction
  void build_graph();
  
  // Private methods to calculate energies, polarization, etc. analytically
  
  // - nucleus_gyromagnetic_ratio / electron_gyromagnetic_ratio
  double delta() const;
  // electron_gyromagnetic_ratio * field_strength [M rad s-1]
  double omega() const;
  // omega / hyperfine_strength
  double scaled_omega() const;
  
  // D = m + scaled_omega*(1 + delta)
  double D(const double quantum_number) const;
  
  // O = sqrt( I*(I + 1) + 0.25 - m^2 )
  double O(const double quantum_number) const;
  
  // R = sqrt( D^2 + O^2)
  double R(const double quantum_number) const;
  
  // (A/2)*(-0.5*(1 + 4*scaled_omega*m*delta) + pm*R(m))
  // for level |pm,m>, A = hyperfine strength. Units M rad s-1
  double eigenvalue(const AdiabaticLabel & label) const;
  
  // convert |pm,m> levels to -> 0,1,2,...,dim(donor)
  unsigned int adiabatic_label_to_int_label(const AdiabaticLabel & label) const;
  
  // Given |pm,m>, returns |mp,m>.
  // If |mp,m> does not exist (m = |M|), returns the input
  AdiabaticLabel orthogonal_level_label(AdiabaticLabel label) const;
  
  // D / R
  double cos_theta(const double quantum_number) const;
  // O / R
  double sin_theta(const double quantum_number) const;

  // (1/sqrt(2))*sqrt(1 + cos_theta);
  double a(const double quantum_number) const;
  // (1/sqrt(2))*sqrt(1 - cos_theta);
  double b(const double quantum_number) const;
  
  // expectation value of the electron z-component of spin
  // (for field along z) for level |pm,m>
  // <pm,m|S_z|pm,m> = 0.5*pm*(a(m)^2 - b(m)^2)
  double polarization(const AdiabaticLabel& label) const;
  
  // Gives the (at most two) Zeeman basis states
  // |mS = pm 1/2, mI = m mp 1/2> and |mS = mp 1/2,mI = m pm 1/2>
  // (pm = +/-, mp = -/+)
  // where mS = pm 1/2 and mI = -I ... +I in integer steps for the energy
  // state |pm,m> =
  //         a_m |mS = pm 1/2, mI = m mp 1/2> pm b_m |mS = mp 1/2,mI = m pm 1/2>
  // For m = -M, |-,-M> = |-1/2,-I> (only one Zeeman state) (M = max(m))
  // For m = +M, |+,+M> = |+1/2,+I> (only one Zeeman state)
  // |+,-M> and |-,M> don't exist.
  // For all other |pm,m>, there are two basis states.
  SpinBasis build_basis(const AdiabaticLabel& label) const;
  
  // Like above but includes (non-zero coefficient) basis states
  // required for the given set of labels
  SpinBasis build_basis(const std::vector<AdiabaticLabel>& labels) const;
  // Same as above but with integer labels for energy levels as the arguments
  SpinBasis build_basis(const uivector& labels) const;

  // also sets orthogonal levels
  void set_transition(const unsigned int upper_level,
                      const unsigned int lower_level);
    
public:
  
  SpinDonor();
  SpinDonor(const double field_strength, // Tesla
            const double nucleus_quantum_number,
            const double electron_gyromagnetic_ratio, // M rad s-1 T-1
            const double nucleus_gyromagnetic_ratio, // M rad s-1 T-1
            const double hyperfine_strength, // M rad s-1
            const unsigned int upper_level,
            const unsigned int lower_level);
  
  SpinDonor(const double field_strength, // Tesla
            const double nucleus_quantum_number,
            const double electron_gyromagnetic_ratio, // M rad s-1 T-1
            const double nucleus_gyromagnetic_ratio, // M rad s-1 T-1
            const double hyperfine_strength,        // M rad s-1
            const unsigned int upper_level,
            const unsigned int lower_level,
            const ThreeVector & electron_position, // Angstroms
            const ThreeVector & nucleus_position, // Angstroms
            const ComplexVector & electron_state,
            const ComplexVector & nucleus_state);
  
  const UniformMagneticField& get_field() const;
  const ElectronSpin& get_electron() const;
  const NuclearSpin& get_nucleus() const;
  const Hyperfine& get_hyperfine() const;
  
  double max_quantum_number() const; // I + S, S = 1/2,
                                     // I = nucleus quantum number

  // energy eigenvalue in M rad s-1
  cdouble eigenvalue(const unsigned int label) const;
  // always real but return complex type
  // energy levels labeled
  // 0,1,2 ... (2S+1)*(2I+1)
  
  unsigned int dimension() const; // The complete spin basis dimension.
                                  // This is donor(dim) = (2S+1)*(2I+1)
  
  // See double polarization(const AdiabaticLabel& label) const
  // This takes an integer energy level label.
  // Gives expectation value of the electron z-component of spin
  // (for field along z) for input level
  double polarization(const unsigned int label) const;

  // This calls
  // SpinBasis build_basis(const uivector& labels) const
  // for uivector containing the upper and lower levels
  // as well as the two levels orthogonal to these.
  // Output basis has the Zeeman basis states in which the upper and lower
  // transition levels can be completely represented
  // (this is a truncated basis for speed). It includes also basis states
  // for the orthogonal levels as interactions of the donor via the z-component
  // of the electron spin involve these levels.
  virtual SpinBasis build_basis() const;

  // This calls SpinBasis SpinInteractionGraph::build_basis() const
  // and builds the full Zeeman basis
  SpinBasis build_complete_basis() const;
  
  // Given |pm,m>, returns |mp,m>. (pm = +/-, mp = -/+)
  // If |mp,m> does not exist (m = |M|), returns the input.
  // This method takes and outputs integer energy level inputs
  // 0,1,2,...,donor(dim)
  unsigned int orthogonal_label(const unsigned int label) const;
  
};

} // namespace SpinDec

#endif // SPINDONOR_H_
