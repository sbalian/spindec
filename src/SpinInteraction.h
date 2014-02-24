#ifndef SPININTERACTION_H_
#define SPININTERACTION_H_

// SpinInteraction
//
// Abstract base class for interaction between a pair of spins.
// TODO calculate non spatial dependence once?
//
// Seto Balian, Feb 24, 2014

#include <Eigen/Dense>

#include "Spin.h"
#include "SpinVector.h"
#include "SpinBasis.h"
#include "UniformMagneticField.h"

#include "types.h"

namespace SpinDecoherence
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
  void fill_ising_flipflop(cdmatrix* hamiltonian,
                   const SpinVector & spins,
                   const SpinBasis & basis,
                   const unsigned int spin_label1,
                   const unsigned int spin_label2,
                   const bool ising_only,
                   const cdouble & flipflop_form) const;
  
  void warn_if_preset_then_calculated() const;

public:
  
  virtual void calculate(const Spin & spin1, const Spin & spin2,
      const UniformMagneticField & field) = 0;

  double get_strength() const;
  bool strength_preset() const;
  
  virtual void fill(cdmatrix * hamiltonian,
                   const SpinVector & spins,
                   const SpinBasis & basis,
                   const unsigned int spin_label1,
                   const unsigned int spin_label2) const = 0;
  
  virtual ~SpinInteraction();

};

} // namespace SpinDecoherence

#endif // SPININTERACTION_H_
