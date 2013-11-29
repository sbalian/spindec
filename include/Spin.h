#ifndef SPIN_H
#define SPIN_H

// Spin
//
// Contains spin quantum number S and gyromagnetic ratio [M rad s-1 T-1].
// Also gives the spin multiplicity = 2 S + 1.
//
// gyromagnetic ratio = Larmor frequency / magnetic field
//
// Seto Balian, November 29, 2013

class Spin
{

protected:

  // @todo make these consts, but can't use with
                           //       std::vector! use dynamical alloc in
                           //       SpinVector? how about boost::ptr_vector
  double quantum_number_; 
  double gyromagnetic_ratio_;
  unsigned int multiplicity_;

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
