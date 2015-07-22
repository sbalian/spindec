#ifndef HYPERFINE_H_
#define HYPERFINE_H_

// Seto Balian, Jun 24, 2015

// TODO Force between electron and nucleus.
// TODO check and see if residual dipolar is implemented correctly.
// TODO check if all parts of the interaction are implemented and documented
// TODO correctly

#include "SpinDec/SpinInteraction.h"

//#include "SpinDec/ElectronSpin.h"
//#include "SpinDec/NuclearSpin.h"

#include "SpinDec/HyperfineParameters.h"

namespace SpinDec
{

/**
 * \brief Calculates the electron-nuclear hyperfine interaction in a lattice.
 * 
 * The Hamiltonian is
 * \f[
 * \hat{H}_A = A \hat{S}^z \hat{I}^z +
 * \frac{A}{2}\left[\hat{S}^+\hat{I}^- + \hat{S}^-\hat{I}^+\right]
 * \f]
 * 
 * This class calculates \f$A\f$ for the above Hamiltonian, \f$\hat{H}_A\f$,
 * where \f$\hat{\bf S}\f$ and \f$\hat{\bf I}\f$ are the
 * electronic and nuclear spin operators. Also fills the Hamiltonian matrix
 * elements for \f$\hat{H}_A\f$. Uses the Kohn-Luttinger electronic
 * wavefunction. Energy units are M rad s\f$^{-1}\f$.
 * 
 * \f[ A = pq - D(R)\theta(|R| - na) \f]
 * 
 * The first term \f$ pq \f$ is the isotropic Fermi contact part.
 * \f[ p = \frac{16}{9} \pi \hbar \gamma_e\gamma_n\eta \f]
 * where
 * - \f$ \hbar \f$: reduced Planck constant [J s].
 * - \f$ \gamma_e\f$: electron gyromagnetic ratio
 * [M rad s\f$^{-1}\f$T\f$^{-1}\f$].
 * - \f$ \gamma_n\f$: nuclear gyromagnetic ratio
 * [M rad s\f$^{-1}\f$T\f$^{-1}\f$].
 * - \f$\eta\f$: charge density.
 * 
 * \f[
 * q = (10^{30}) |F_1(R)\cos(k_0x) + F_3(R)\cos(k_0y) + F_5(R)\cos(k_0z)|^2
 * \f]
 * where
 * - \f$R\f$: vector between nucleus and electron (\f$(x,y,z)\f$) components)
 * [\f$\mbox{\AA}\f$].
 * - \f$k_0 = 0.85\times2\pi a_0\f$ [\f$\mbox{\AA}\f$\f$^{-1}\f$]
 * - \f$ F_{1,2}(R)=\exp[-\sqrt{x^2/(nb)^2 + (y^2 + z^2)/(na)^2 }]/
 * \sqrt{\pi (na)^2 nb}\f$
 * - \f$ F_{3,4}(R):\f$ \f$xyz \rightarrow yzx\f$.
 * - \f$ F_{5,6}(R):\f$ \f$xyz \rightarrow zxy\f$.
 * - \f$ n = \sqrt{0.029/E_i}\f$, \f$E_i\f$: electron ionization energy [eV].
 * - \f$ a \f$ and \f$ b \f$ are lattice parameters [\f$\mbox{\AA}\f$].
 * 
 * The second term \f$[- D(R)\theta(|R| - na ) ]\f$ is the dipolar part which
 * requires the direction of the magnetic field and where \f$ \theta \f$ here
 * is the Heaviside step function. See Dipolar.h for \f$D(R)\f$, the dipolar
 * interaction (units M rad s\f$^{-1}\f$).
 * 
 * From: arXiv:cond-mat/0211567 (Phys. Rev. B 68, 115322 (2003)).
 * 
 */
class Hyperfine : public SpinInteraction
{
private:

  HyperfineParameters parameters_;
  
  double envelope_function(const UInt index,
      const ThreeVector & separation) const;
  double n_parameter() const;
  double n_times_a() const;
  double n_times_b() const;
  double scaled_probability_density(const ThreeVector & separation) const;
  
public:
  
  Hyperfine();
  /// If you wish to calculate.
  explicit Hyperfine(const HyperfineParameters & parameters);
  /// If you don't wish to calculate.
  Hyperfine(const double strength);
  
  virtual void calculate(const SpinParameters & electron_parameters,
      const SpinParameters & nuclear_parameters,
      const ThreeVector& electron_position,
      const ThreeVector& nuclear_position,
      const UniformMagneticField & field);

  virtual void fill(ComplexMatrix * hamiltonian,
                   const SpinParametersVector & spin_parameters_vector,
                   const SpinBasis & basis,
                   const UInt spin_label1,
                   const UInt spin_label2) const;
  
  virtual shared_ptr<SpinInteraction> clone() const;
  
  virtual string get_type() const;

};

} // namespace SpinDec

#endif // HYPERFINE_H_
