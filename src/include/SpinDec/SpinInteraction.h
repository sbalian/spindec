#ifndef SPININTERACTION_H_
#define SPININTERACTION_H_

// SpinInteraction
//
// Abstract base class for interaction between a pair of spins.
// TODO calculate non spatial dependence once?
//
// Seto Balian, Mar 24, 2014

#include <Eigen/Dense>

#include "SpinDec/Spin.h"
#include "SpinDec/SpinVector.h"
#include "SpinDec/SpinBasis.h"
#include "SpinDec/UniformMagneticField.h"

#include "SpinDec/typedefs.h"

#include <memory>

namespace SpinDec
{

class SpinInteraction
{
protected:
  
  double strength_; // M rad s-1 (calculated or set)
  bool strength_preset_;  // Set to true, this indicates
                          // that the strength was set in the constructor
  
  // If you wish to calculate
  SpinInteraction();
  // If you don't wish to calculate
  SpinInteraction(const double strength);
  
  // ISING            + FLIPFLOP
  // strength*S1z S2z + flipflop_form*strength*(S1+ S2- + S1- S2+)
  // flipflop_form is a complex double
  void fill_ising_flipflop(ComplexMatrix* hamiltonian,
                   const SpinVector & spins,
                   const SpinBasis & basis,
                   const UInt spin_label1,
                   const UInt spin_label2,
                   const bool ising_only,
                   const CDouble & flipflop_form) const;
  
  void warn_if_preset_then_calculated() const;

public:
  
  virtual void calculate(const Spin & spin1, const Spin & spin2,
      const ThreeVector & position1, const ThreeVector & position2,
      const UniformMagneticField & field) = 0;

  double get_strength() const;
  bool strength_preset() const;
  
  virtual void fill(ComplexMatrix * hamiltonian,
                   const SpinVector & spins,
                   const SpinBasis & basis,
                   const UInt spin_label1,
                   const UInt spin_label2) const = 0;
  
  virtual std::auto_ptr<SpinInteraction> clone() const = 0;
  
  virtual ~SpinInteraction();

};

} // namespace SpinDec

#endif // SPININTERACTION_H_
