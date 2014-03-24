#ifndef SPINPARAMETERS_H_
#define SPINPARAMETERS_H_

// SpinParameters
//
// Contains spin quantum number S, gyromagnetic ratio [M rad s-1 T-1] and
// spin multiplicity = 2 S + 1.
//
// gyromagnetic ratio = Larmor frequency (M rad s-1) / magnetic field (T)
//
// Seto Balian, Mar 24, 2014

#include <iostream>

#include "SpinDec/typedefs.h"

namespace SpinDec
{

class SpinParameters
{
protected:

  double quantum_number_;
  double gyromagnetic_ratio_; // in M rad s-1
  UInt multiplicity_;
  
  UInt calc_multiplicity(const double quantum_number) const;
  
public:

  SpinParameters();
  SpinParameters(const double quantum_number,
       const double gyromagnetic_ratio);

  double get_quantum_number() const;
  double get_gyromagnetic_ratio() const;

  UInt get_multiplicity() const;

  // Print with cout
  friend std::ostream& operator<<(std::ostream& os,
      SpinParameters const & spin_parameters);

};

} // namespace SpinDec

#endif // SPINPARAMETERS_H_
