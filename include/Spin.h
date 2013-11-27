#ifndef SPIN_H
#define SPIN_H

// Spin
//
// For holding the spin quantum number S and gyromagnetic ratio [M rad s-1 T-1].
// Also gives the spin multiplicity = 2 S + 1.
//
// Seto Balian, November 27, 2013

class Spin
{

protected:

  double gyromagnetic_ratio_;  // Gyromagnetic ratio [M rad s-1 T-1] 
                               // = Larmor frequency / magnetic field

public:

  double get_gyromagnetic_ratio() const;
  void set_gyromagnetic_ratio(const double gyromagnetic_ratio);
  
  virtual double get_quantum_number() const = 0;

  virtual unsigned int multiplicity() const = 0; // 2 S + 1

  virtual ~Spin() {};

};

#endif // SPIN_H
