#ifndef SPINPARAMETERS_H_
#define SPINPARAMETERS_H_

// SpinDec::SpinParameters
//
// Contains basic parameters associated with a (quantum) spin.
// - Quantum number S
// - Gyromagnetic ratio [M rad s-1 T-1]
// - Spin multiplicity = 2 S + 1.
// - SpinBasis: Zeeman basis
// - Position in real space [Angstroms]
//
// Gyromagnetic ratio = <Larmor frequency> [M rad s-1] / <magnetic field> [T]
//
// Seto Balian, Mar 28, 2014

#include <iostream>

#include "SpinDec/typedefs.h"
#include "SpinDec/SpinBasis.h"

namespace SpinDec
{

class SpinParameters
{
private:

  double quantum_number_;
  double gyromagnetic_ratio_; // in M rad s-1
  UInt multiplicity_;
  SpinBasis basis_;
  ThreeVector position_;

  UInt calc_multiplicity(const double quantum_number) const;

public:

  SpinParameters();
  SpinParameters(const double quantum_number,
                 const double gyromagnetic_ratio,
                 const SpinBasis& basis,
                 const ThreeVector& position);

  double get_quantum_number() const;
  double get_gyromagnetic_ratio() const;
  const SpinBasis& get_basis() const;
  const ThreeVector& get_position() const;

  void set_custom_basis(const Eigen::ArrayXd& custom_basis);

  UInt get_multiplicity() const;
  
  // Print with cout
  friend std::ostream& operator<<(std::ostream& os,
      SpinParameters const & spin_parameters);

};

} // namespace SpinDec

#endif // SPINPARAMETERS_H_
