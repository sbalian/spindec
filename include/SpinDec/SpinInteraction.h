#ifndef SPININTERACTION_H_
#define SPININTERACTION_H_

// Seto Balian, Jun 25, 2015

// TODO calculate non spatial dependence once?

#include "SpinDec/SpinParametersVector.h"
#include "SpinDec/SpinBasis.h"
#include "SpinDec/UniformMagneticField.h"

#include "SpinDec/typedefs.h"

#include <memory>

namespace SpinDec
{

/**
 * \brief Abstract base class for interaction between a pair of spins.
 */
class SpinInteraction
{
protected:
  
  /// M rad s\f$^{-1}\f$ (calculated or set).
  double strength_; 
  
  /// Set to true, this indicates that the strength was set in the constructor.
  bool strength_preset_;  
  
  /// If you wish to calculate.
  SpinInteraction();
  
  /// If you don't wish to calculate.
  SpinInteraction(const double strength);
  
  /**
   * Fill
   * \f[
   * J \hat{S}_1^z \hat{S}_2^z +
   * F J (\hat{S}_1^+ \hat{S}_2^- + \hat{S}_1^- \hat{S}_2^+),
   * \f]
   * where \f$ S \f$ is the strength, \f$ F \f$ is a factor depending on
   * the type of interaction, the first term is known as "Ising" and the second
   * term as "Flip-Flop".
   * 
   */
  void fill_ising_flipflop(ComplexMatrix* hamiltonian,
                   const SpinParametersVector & spin_parameters_vector,
                   const SpinBasis & basis,
                   const UInt spin_label1,
                   const UInt spin_label2,
                   const bool ising_only,
                   const CDouble & flipflop_form) const;
  
  void warn_if_preset_then_calculated() const;

public:
  
  virtual void calculate(const SpinParameters & spin_parameters1,
      const SpinParameters & spin_parameters2,
      const ThreeVector & position1, const ThreeVector & position2,
      const UniformMagneticField & field) = 0;

  double get_strength() const;
  bool strength_preset() const;
  
  virtual void fill(ComplexMatrix * hamiltonian,
                   const SpinParametersVector & spins,
                   const SpinBasis & basis,
                   const UInt spin_label1,
                   const UInt spin_label2) const = 0;
  
  virtual shared_ptr<SpinInteraction> clone() const = 0;
  
  virtual string get_type() const = 0;
  
  virtual ~SpinInteraction();

};

} // namespace SpinDec

#endif // SPININTERACTION_H_
