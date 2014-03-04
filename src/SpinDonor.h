#ifndef SPINDONOR_H_
#define SPINDONOR_H_

// SpinDonor
//
// Electron coupled to a nucleus via a preset hyperfine interaction.
// Analytical methods include energy levels and polarization.
// See Phys. Rev. Lett. 105, 067602 (2010).
// TODO Comment more
//
// Seto Balian, Mar 4, 2014

#include "SpinInteractionGraph.h"
#include "UniformMagneticField.h"
#include "ElectronSpin.h"
#include "NuclearSpin.h"
#include "Hyperfine.h"
#include "SpinBasis.h"
#include "SpinState.h"

#include <vector>

#include "types.h"

namespace SpinDecoherence
{

// |slot1,slot2>
struct AdiabaticLabel; // TODO Is this OK here?
// slot1 - sign (plus or minus)
// slot2 - quantum number m
//
// quantum number m = - |I + S|,...,I + S (separated by 1)
// S = 1/2 (electron quantum number), I = nucleus quantum number

class SpinDonor : public SpinInteractionGraph
{
private:
    
  UniformMagneticField field_; // magnetic field (strength in T)
  ElectronSpin electron_;
  NuclearSpin nucleus_;
  Hyperfine hyperfine_;
  
  // energy levels 0,1,2 ... (2S+1)*(2I+1) 
  unsigned int upper_level_; // upper energy level for a transition
  unsigned int lower_level_; // lower energy level for a transition
    
  // In order of increasing energy, these are
  // |-,M-1> , |-,M-2> , ... , |-,-M>, |-,-M+1>, ... |+,+M>
  // where M = I + S
  std::vector<AdiabaticLabel> energy_level_labels_;
  void calc_energy_level_labels(); // calculates and sets
  
  void build_graph();
  
  // - nucleus_gyromagnetic_ratio / electron_gyromagnetic_ratio
  double delta() const;
  // electron_gyromagnetic_ratio * field_strength [M rad s-1]
  double omega() const;
  // omega / hyperfine_strength
  double scaled_omega() const;
  
  double D(const double quantum_number) const;
  double O(const double quantum_number) const;
  double R(const double quantum_number) const;
  
  double eigenvalue(const AdiabaticLabel & label) const;
  
  unsigned int adiabatic_label_to_int_label(const AdiabaticLabel & label) const;
  
  double cos_theta(const double quantum_number) const;
  double sin_theta(const double quantum_number) const;

  double a(const double quantum_number) const;
  double b(const double quantum_number) const;
  
  double polarization(const AdiabaticLabel& label) const;
  
  SpinBasis build_basis(const AdiabaticLabel& label) const;
  SpinBasis build_basis(const AdiabaticLabel& label1,
                        const AdiabaticLabel& label2) const;
  SpinBasis build_basis(const unsigned int label1,
                        const unsigned int label2) const;

  void set_transition(const unsigned int upper_level,
                      const unsigned int lower_level);
    
public:
  
  SpinDonor();
  SpinDonor(const double field_strength, 
            const double nucleus_quantum_number,
            const double electron_gyromagnetic_ratio, // M rad s-1 T-1
            const double nucleus_gyromagnetic_ratio, // M rad s-1 T-1
            const double hyperfine_strength, // M rad s-1
            const unsigned int upper_level,
            const unsigned int lower_level);
  
  SpinDonor(const double field_strength,
            const double nucleus_quantum_number,
            const double electron_gyromagnetic_ratio, // M rad s-1 T-1
            const double nucleus_gyromagnetic_ratio, // M rad s-1 T-1
            const double hyperfine_strength,        // M rad s-1
            const unsigned int upper_level,
            const unsigned int lower_level,
            const d3vector & electron_position, // Angstroms
            const d3vector & nucleus_position, // Angstroms
            const cdvector & electron_state,
            const cdvector & nucleus_state);
  
  const UniformMagneticField& get_field() const;
  const ElectronSpin& get_electron() const;
  const NuclearSpin& get_nucleus() const;
  const Hyperfine& get_hyperfine() const;
  
  double max_quantum_number() const; // I + S, S = 1/2,
                                     // I = nucleus quantum number

  // energy eigenvalue in M rad s-1
  cdouble eigenvalue(const unsigned int label) const; // always real
                                                    // energy levels labeled
                                                    // 0,1,2 ... (2S+1)*(2I+1)
  
  unsigned int dimension() const; // The complete spin basis dimension.
                                  // This is (2S+1)*(2I+1)
  
  double polarization(const unsigned int label) const;

  virtual SpinBasis build_basis() const;

  SpinBasis build_complete_basis() const;
  
};

} // namespace SpinDecoherence

#endif // SPINDONOR_H_
