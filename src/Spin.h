#ifndef SPIN_H_
#define SPIN_H_

// Spin
//
// Contains spin quantum number S and gyromagnetic ratio [M rad s-1 T-1].
// Also gives the spin multiplicity = 2 S + 1.
//
// gyromagnetic ratio = Larmor frequency / magnetic field
//
// Seto Balian, Feb 6, 2014

#include <iostream>

namespace SpinDecoherence
{

class Spin
{

protected:

  double quantum_number_; 
  double gyromagnetic_ratio_;
  unsigned int multiplicity_;

  unsigned int calculate_multiplicity() const;

  Spin(const double quantum_number,
       const double gyromagnetic_ratio,
       const unsigned int multiplicity);

public:

  Spin();
  Spin(const double quantum_number, const double gyromagnetic_ratio);

  double get_gyromagnetic_ratio() const;
  double get_quantum_number() const;
  unsigned int get_multiplicity() const;

  // Print with cout
  friend std::ostream& operator<<(std::ostream& os, Spin const & spin);

};

} // namespace SpinDecoherence

#endif // SPIN_H_
