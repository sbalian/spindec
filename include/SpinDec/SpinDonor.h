#ifndef SPINDONOR_H_
#define SPINDONOR_H_

// Seto Balian, Jun 25, 2015

// TODO confusing names ...

#include "SpinDec/SpinSystem.h"

#include "SpinDec/Hyperfine.h"
#include "SpinDec/ElectronSpinParameters.h"
#include "SpinDec/SpinParameters.h"
#include "SpinDec/AdiabaticLabel.h"

#include <vector>

#include "SpinDec/typedefs.h"

namespace SpinDec
{


/**
 * \brief Special spin system: mixed electron-nuclear spin donors.
 * 
 * Electron coupled to a nucleus via a preset hyperfine interaction.
 * Analytical methods include energy levels, eigenstates and polarization
 * obtained from Phys. Rev. Lett. 105, 067602 (2010).
 * 
 * Energy levels are (adiabatic states) labeled as follows,
 * with adiabatic level labels:
 * \f[ \left | \pm, m \right\rangle, \f]
 * with integer quantum number \f$ m = - |I + S|, \dots , I + S \f$, 
 * separated by 1. \f$S\f$ and \f$I\f$ are the electron and nuclear
 * spin quantum numbers respectively.
 * 
 * Alternatively, energy levels are labeled according to increasing energy:
 * \f$0, 1, \dots, (2S + 1)(2I + 1) - 1\f$.
 * 
 */
class SpinDonor : public SpinSystem
{
private:
  
  /**
   * \brief Use full Zeeman basis.
   * 
   * Computationally intensive for CCE - 20D for Si:Bi.). Otherwise,
   * the truncated basis is used, which consists of the subspaces
   * for the two levels involved in the transition.
   * 
   */
  bool complete_basis_;
  
  /// For the spin interaction graph.
  ElectronSpinParameters electron_parameters_;
  /// For the spin interaction graph.
  SpinParameters nuclear_parameters_;
  /// For the spin interaction graph.
  Hyperfine hyperfine_;
  
  /**
   * \brief Upper and lower transition energy levels.
   * 
   * Labeled \f$0,1,2,\dots,(2S+1)(2I+1) - 1\f$. Elements are:
   * - Lower energy level label for a transition.
   * - Upper energy level label for a transition.
   * 
   */ 
  UInt transition_level_labels_[2];

  /**
   * If the donor interacts via the electron \f$z\f$-component spin operator
   * (with the field along \f$z\f$), Hamiltonian matrix elements involving the
   * orthogonal levels must be included in the Hilbert space for completeness.
   * Orthogonal levels are \f$\left|\pm,m\right\rangle \leftrightarrow
   * \left|\mp,m\right\rangle\f$ (if they exist).
   * These orthogonal levels are included so that all the relevant Zeeman
   * basis states are included. Elements are:
   * - Orthogonal lower energy level.
   * - Orthogonal upper energy level.
   * 
   * At most of size 2.
   * 
   */
  UIntArray orthogonal_level_labels_;
  
  /**
   * These are the upper, lower and orthogonal levels for a non-complete
   * basis and all the energy levels for the complete basis, sorted
   * in order of increasing energy.
   */
  UIntArray sorted_level_labels_;
  
  /// Sets and sorts sorted_level_labels_ in increasing energy.
  void sort_level_labels();
  
  /**
   * \brief Given level label, returns the index in sorted_level_labels_.
   */
  UInt level_label_index(const UInt level_label) const;
  
  virtual void check_level_label(const UInt level_label) const;
  
  /**
   * In order of increasing energy, these are:
   * \f[
   * \left| -,M-1 \right\rangle, \left| -,M-2 \right\rangle, \dots , 
   * \left| -,-M \right\rangle, \left| -,-M+1 \right\rangle, \dots
   * \left| +,+M \right\rangle,
   * \f]
   * 
   * where \f$ M = I + S\f$.
   * 
   */
  std::vector<AdiabaticLabel> adiabatic_level_labels_;
  
  /**
   * Calculates and sets all the adiabatic level labels
   * and adiabatic_level_labels_.
   */ 
  void calc_adiabatic_level_labels(); 
  
  // Private methods to calculate energies, polarization, etc. analytically
  
  /// Ratio of gyromagnetic ratios \f$\delta = - \gamma_n / \gamma_e\f$.
  double delta() const;
  
  /**
   * \brief \f$\omega=\gamma_e B\f$ [M rad s\f$^{-1}\f$], where 
   *        \f$B\f$ is the Zeeman field strength.
   */
  double omega() const;
  
  /**
   * \brief \f$\omega'=\omega/A\f$, where \f$A\f$ is the
   * electron-nuclear hyperfine strength in M rad s\f$^{-1}\f$.
   */
  double scaled_omega() const;
  
  /// \f$D=m+ \omega'(1 + \delta) \f$.
  double D(const int quantum_number) const;
  
  /// \f$ O = \sqrt{ I(I + 1) + 1/4 - m^2 }\f$.
  double O(const int quantum_number) const;
  
  /// \f$R = \sqrt{ D^2 + O^2} \f$.
  double R(const int quantum_number) const;
  
  /**
   * \f[
   * E = \frac{A}{2} \left( -\frac{1}{2}
   * \left[ 1 + 4\omega' m \delta \right] \pm R(m) \right)
   * \f]
   * for level \f$ \left| \pm, m \right\rangle \f$ and \f$ A \f$ is the
   * hyperfine strength. Units are M rad s\f$^{-1}\f$.
   * 
   */
  double energy(const AdiabaticLabel & adiabatic_level_label) const;
  
//  virtual void set_eigenstates();
//  virtual void set_energies();
  
  /**
   * \brief Convert \f$\left|\pm,m\right\rangle\f$ levels to
   * \f$0,1,2,\dots,\mbox{dim(donor)}-1\f$.
   */
  UInt adiabatic_label_to_int_label(const AdiabaticLabel&
      adiabatic_level_label) const;
  
  /// Other way to adiabatic_label_to_int_label.
  AdiabaticLabel int_label_to_adiabatic_label(const UInt level_label) const;
  
  /**
   * \brief Given \f$\left|\pm,m\right\rangle\f$,
   * returns \f$\left|\mp,m\right\rangle\f$.
   * 
   * If \f$ \left| \mp , m\right\rangle\f$ does not exist (\f$ m = |M| \f$),
   * returns the input.
   * 
   */ 
  AdiabaticLabel orthogonal_adiabatic_level_label(
      AdiabaticLabel adiabatic_level_label) const;
  
  /// \f$ \cos{\theta} =  D / R \f$.
  double cos_theta(const int quantum_number) const;
  /// \f$ \sin{\theta} = O / R \f$.
  double sin_theta(const int quantum_number) const;

  /// \f$[1/\sqrt{2}]\sqrt{1 + \cos{\theta}}\f$.
  double a(const int quantum_number) const;
  /// \f$[1/\sqrt{2}]\sqrt{1 - \cos{\theta}}\f$.
  double b(const int quantum_number) const;
  
  
  /**
   * \brief Expectation value of the electron \f$z\f$-component of spin.
   * 
   * For field along \f$z\f$, for level \f$ \pm , m \f$.
   * 
   * This is
   * \f[ \left\langle \pm, m \right| \hat{S}^z \left| \pm, m\right\rangle =
   * \pm\frac{1}{2} \left[ a^2(m) - b^2(m) \right].
   * \f] 
   * 
   */
  double polarization(const AdiabaticLabel& adiabatic_level_label) const;
  
  /**
   * Gives the (at most two) Zeeman basis states:
   * \f$ \left|m_S = \pm 1/2, m_I = m \mp 1/2\right\rangle\f$ and
   * \f$ \left|m_S = \mp 1/2, m_I = m \pm 1/2\right\rangle\f$
   * where \f$ m_S = \pm 1/2\f$ and \f$ m_I = - I, \dots, +I\f$ in integer
   * steps, for the energy state:
   * \f[
   * \left| \pm,m \right\rangle =
   * a_m \left| m_S = \pm 1/2, m_I = m \mp 1/2 \right\rangle
   * \pm
   * b_m \left| m_S = \mp 1/2, m_I = m \pm 1/2 \right\rangle.
   * \f]
   * 
   * - For \f$ m = -M \f$,
   * \f$ \left|-,-M\right\rangle = \left|-1/2,-I\right\rangle \f$
   * (only one Zeeman state) (\f$ M = \mbox{max}(m)\f$).
   * - For \f$ m = +M \f$, 
   * \f$ \left|+,+M\right\rangle = \left|+1/2,+I\right\rangle \f$
   * (only one Zeeman state).
   * 
   * States \f$ \left| +, -M \right\rangle \f$ and
   *        \f$ \left| -, M \right\rangle \f$ don't exist.
   * For all the other \f$ \left| \pm,m \right\rangle \f$,
   * there are two basis states.
   * 
   */
  SpinBasis build_basis(const AdiabaticLabel& adiabatic_level_label) const;
  
  /**
   * Like build_basis(const AdiabaticLabel&), but for multiple levels
   * (non-zero coefficient basis states).
   */
  SpinBasis build_basis(const std::vector<AdiabaticLabel>&
      adiabatic_level_labels) const;
  
  /**
   * Same as build_basis(const std::vector<AdiabaticLabel>&)
   * but with integer labels for energy levels as the arguments.
   */ 
  SpinBasis build_basis(const UIntArray & level_labels) const;
  
  /** 
   * This calls build_basis(const UIntArray&) const
   * for UIntArray containing the upper and lower levels only.
   * Output basis has the Zeeman basis states in which the upper and lower
   * levels as well as the levels orthogonal to these (if they exist) can
   * be completely represented.
   * This is a complete basis for interactions of the donor via the
   * \f$z\f$-component of the electron spin only.
   */
  SpinBasis build_truncated_basis() const;
  
  /**
   * Also sets orthogonal levels if they exist.
   */
  void set_transition(const UInt lower_level_label,
      const UInt upper_level_label);
  
  void set_orthogonal_level_labels(const UInt lower_level_label,
      const UInt upper_level_label);
  UIntArray get_orthogonal_level_labels(const UInt lower_level_label,
      const UInt upper_level_label) const;
  
  
  /**
   * \brief Given \f$\left|\pm,m\right\rangle\f$,
   * returns \f$\left|\mp,m\right\rangle\f$.
   * 
   * If \f$ \left| \mp , m\right\rangle\f$ does not exist (\f$ m = |M| \f$),
   * returns the input.
   * 
   * This method takes and outputs integer energy level inputs
   * \f$0,1,\dots,\mbox{donor(dim)}-1\f$.
   * 
   */
  UInt orthogonal_level_label(const UInt level_label) const;
  
  /// See constructors.
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
  
  /**
   * Field strength in Tesla (T), gyromagnetic ratios in
   * M rad s\f$^{-1}\f$T\f$^{-1}\f$, hyperfine strength in M rad s\f$^{-1}\f$,
   * and positions in \f$\mbox{\AA}\f$.
   */
  SpinDonor(const double field_strength,
            const double nuclear_quantum_number,
            const double electron_gyromagnetic_ratio,
            const double nuclear_gyromagnetic_ratio,
            const double hyperfine_strength,      
            const unsigned int lower_level_label,
            const unsigned int upper_level_label,
            const ThreeVector& electron_position,
            const ThreeVector& nuclear_position,
            const bool complete_basis);
  
  const ElectronSpinParameters& get_electron_parameters() const;
  const SpinParameters& get_nuclear_parameters() const;
  const Hyperfine& get_hyperfine() const;
  
  /// \f$ I + S\f$, \f$I\f$ is nuclear spin quantum number.
  int max_quantum_number() const;
                                 
  /// This is the Hamiltonian dimension.
  virtual UInt dimension() const; 
  
  /// The complete spin basis dimension. This is \f$ (2S + 1)(2I + 1) \f$.
  UInt total_multiplicity() const; 
  
  virtual SpinState eigenstate(const UInt level_label);
  virtual double energy(const UInt level_label);
  
  /**
   * See polarization(const AdiabaticLabel& label) const.
   * This takes an integer energy level label.
   * Gives expectation value of the electron \f$z\f$-component of spin
   * (for field along \f$z\f$) for input level.
   * 
   */
  double polarization(const UInt level_label) const;
  
  const SpinInteractionVertex& electron_vertex() const;
  const SpinInteractionVertex& nuclear_vertex() const;
  
  const UIntArray get_orthogonal_level_labels() const;
  
  SpinState get_lower_level();
  SpinState get_upper_level();
  vector<SpinState> get_orthogonal_levels();
  
  virtual PiPulse pi_pulse(const UInt level_label1,
      const UInt level_label2);
  
  virtual auto_ptr<SpinSystemBase> clone() const;
  
};


} // namespace SpinDec

#endif // SPINDONOR_H_
