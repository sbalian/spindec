#ifndef SPIN_H
#define SPIN_H

// Spin
//
// Quantum spin object containing gyromagnetic ratio, spin quantum number S and
// position in real space. Also give the spin multiplicity = 2 S + 1.
//
// Seto Balian 04/10/2013

#include <Eigen/Dense>

class Spin
{

private:
  double quantum_number_;      // Spin quantum number
  double gyromagnetic_ratio_;  // Gyromagnetic ratio in M rad s-1 T-1 
                               // = Larmor frequency / magnetic field
  Eigen::Vector3d position_;   // Vector position in Angstroms

public:

  Spin();
  Spin(const double quantum_number,
       const double gyromagnetic_ratio,
       const Eigen::Vector3d & position);
  
  double get_quantum_number() const;
  double get_gyromagnetic_ratio() const;
  Eigen::Vector3d get_position() const;

  void set_quantum_number(const double quantum_number);
  void set_gyromagnetic_ratio(const double gyromagnetic_ratio);
  void set_position(const Eigen::Vector3d & position);
  
  unsigned int multiplicity() const;

};

#endif // SPIN_H

