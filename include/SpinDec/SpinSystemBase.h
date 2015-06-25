#ifndef SPINSYSTEMBASE_H_
#define SPINSYSTEMBASE_H_

// Seto Balian, Jun 25, 2015

#include "SpinDec/typedefs.h"

#include "SpinDec/SpinHamiltonian.h"
#include "SpinDec/SpinState.h"
#include "SpinDec/EvolutionOperator.h"
#include "SpinDec/PiPulse.h"

namespace SpinDec
{

/// Abstract base class for spin systems.
class SpinSystemBase
{
protected:

  SpinHamiltonian hamiltonian_;
  
  RealVector energies_;
  ComplexMatrix eigenstates_;
  
  SpinState state_;
  
  /// Calculate and set energies and eigenstates.
  virtual void solve_once() = 0;
  
  virtual void check_level_label(const UInt level_label) const = 0;
  
  /// So as not to solve for eigenvectors and eigenvalues more than once.
  bool is_solved_;
  
  bool is_state_set_;
  
public:
  SpinSystemBase();
  explicit SpinSystemBase(const SpinHamiltonian& hamiltonian);
  
  const SpinHamiltonian& get_hamiltonian() const;

  /// Levels 0,1,2, ... dimension(Hamiltonian)-1 (some levels may be excluded!).
  virtual SpinState eigenstate(const UInt level_label);
  /// Energy eigenvalue in M rad s\f$^{-1}\f$.
  virtual double energy(const UInt level_label);
  
  void set_state(const SpinState& state);
  
  /// Sets state to the level_label'th eigenstate.
  void set_state(const UInt level_label);
  
  /**
   * Sets the state to a superposition state of the eigenstates labelled
   * \f$ \left| 0 \right\rangle \f$ and \f$ \left| 1 \right\rangle \f$.
   * Also normalizes the state.
   */
  void set_state(const CDouble& c0, const UInt level_label0,
                 const CDouble& c1, const UInt level_label1);
  
  const SpinState& get_state() const;
  
  EvolutionOperator evolution_operator(const double time);
  
  /// Hamiltonian dimension.
  virtual UInt dimension() const = 0;
  
  const ComplexMatrix& get_eigenvector_matrix();
  const RealVector& get_eigenvalue_vector();
  
  /// \f$\pi\f$-pulse (refocusing pulse).
  virtual PiPulse pi_pulse(const UInt level_label1,
      const UInt level_label2);
  
  /**
   * Print options:
   * - e: energies.
   * - E: eigenstates.
   * - H: Hamiltonian.
   */
  void print(const char option);
  
  virtual auto_ptr<SpinSystemBase> clone() const = 0;
  
    void update_positions(const UIntArray& vertex_labels,
        const vector<ThreeVector>& positions);

  virtual ~SpinSystemBase();
  
};

} // namespace SpinDec

#endif // SPINSYSTEMBASE_H_
