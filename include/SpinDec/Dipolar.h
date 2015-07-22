#ifndef DIPOLAR_H_
#define	DIPOLAR_H_

// Seto Balian, Jun 24, 2015

#include "SpinDec/SpinInteraction.h"

namespace SpinDec
{

/**
 * \brief Secular dipolar interaction strength between a pair of spins.
 * 
 * For two spins, \f$ \hat{\bf S}_1, \hat{\bf S}_2 \f$,
 * \f[
 * \hat{H}_D = D \hat{S}_1^z \hat{S}_2^z - \frac{D}{4}
 *  [ \hat{S}_1^+ \hat{S}_2^- + \hat{S}_1^- \hat{S}_2^+ ]
 * \f]
 * 
 * This class calculates
 * \f[
 * D = \frac{D_0  \gamma_1 \gamma_2 ( 1 - 3\cos^2[\theta] )}{(10^{-10} r)^3}
 * \f]
 * and fills the Hamiltonian matrix elements for the Hamiltonian
 * \f$ \hat{H}_D \f$ above. The energy units are M rad s\f$^{-1}\f$.
 * 
 * The parameters are:
 * - \f$ \gamma_1,\gamma_2 \f$ [M rad s\f$^{-1}\f$T\f$^{-1}\f$]: gyromagnetic
 * ratios of the two interacting spins.
 * - \f$\theta\f$ [rad]: angle between the magnetic field direction and the 
 * vector parallel to the line connecting the two spins.
 * - \f$r\f$ [\f$\mbox{\AA}\f$]: distance between the two spins.
 * - \f$ D_0 = 10^6  (\mu_0 / (4\pi))\hbar\f$ [M rad s\f$^{-1}\f$ m\f$^{3}\f$].
 * - \f$ \hbar \f$ [J s]: reduced Plank constant.
 * - \f$ \mu_0 / (4\pi) = 10^{-7}\f$ NA\f$^{-2}\f$
 * (\f$\mu_0\f$ is the vacuum permeability).
 * 
 * From: arXiv:cond-mat/0211567 (Phys. Rev. B 68, 115322 (2003)).
 * 
 */
class Dipolar : public SpinInteraction
{

public:
  
  /// If you wish to calculate.
  Dipolar();
  /// If you don't wish to calculate.
  Dipolar(const double strength);
  
  virtual void calculate(const SpinParameters & spin_parameters1,
      const SpinParameters & spin_parameters2,
      const ThreeVector & position1, const ThreeVector & position2,
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

#endif	 // DIPOLAR_H_
