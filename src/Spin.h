#ifndef SPIN_H_
#define SPIN_H_

// Spin
//
// Contains spin quantum number S, gyromagnetic ratio [M rad s-1 T-1], spatial
// position [Angstroms] and quantum state.
// Also gives the spin multiplicity = 2 S + 1.
//
// gyromagnetic ratio = Larmor frequency / magnetic field
//
// Seto Balian, Feb 21, 2014

#include <iostream>

#include "SpinState.h"

#include "types.h"

namespace SpinDecoherence
{

class Spin
{
protected:

  double quantum_number_;
  double gyromagnetic_ratio_; // in M rad s-1
  
  d3vector position_; // Spatial position in Angstroms
  SpinState state_;
  
  unsigned int multiplicity_;
  
public:

  Spin();
  Spin(const double quantum_number,
       const double gyromagnetic_ratio,
       const d3vector & position,
       const cdvector & state_vector);
  
  Spin(const double quantum_number,
       const double gyromagnetic_ratio); // zero state vector and position at
                                         // 000

  double get_quantum_number() const;
  double get_gyromagnetic_ratio() const;
  const d3vector & get_position() const;
  const SpinState & get_state() const;
  
  void set_position(const d3vector & position);
  void set_state_vector(const cdvector & state_vector);
  
  unsigned int get_multiplicity() const;

  // Print with cout
  friend std::ostream& operator<<(std::ostream& os, Spin const & spin);

};

} // namespace SpinDecoherence

#endif // SPIN_H_
