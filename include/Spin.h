#ifndef SPIN_H
#define SPIN_H

// Spin
//
// Contains spin quantum number S and gyromagnetic ratio [M rad s-1 T-1].
// Also gives the spin multiplicity = 2 S + 1.
//
// gyromagnetic ratio = Larmor frequency / magnetic field
//
// Seto Balian, November 28, 2013

class Spin
{

protected:

  const double quantum_number_;
  const double gyromagnetic_ratio_;
  const unsigned int multiplicity_;

  unsigned int calculate_multiplicity() const;

  Spin(const double quantum_number,
       const double gyromagnetic_ratio,
       const unsigned int multiplicity);

public:
  
  Spin(); // all data members set to zero
  Spin(const double quantum_number, const double gyromagnetic_ratio);

  double get_gyromagnetic_ratio() const;
  double get_quantum_number() const;
  double get_multiplicity() const;

};

#endif // SPIN_H
