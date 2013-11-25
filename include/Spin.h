#ifndef SPIN_H
#define SPIN_H

// Spin
//
// Quantum spin object containing:
// Gyromagnetic ratio [M rad s-1]
// Spin quantum number S
// Position in real space [Angstroms]
// Zeeman basis (see SingleSpinZeemanBasis.h)
// Quantum state given in Zeeman basis (complex column vector)
//
// Also gives the spin multiplicity = 2 S + 1.
//
// Seto Balian 25/11/2013

#include <Eigen/Dense>
#include "ZeemanBasis.h"
#include "Named.h"

class Spin : public Named
{

private:
  double quantum_number_;      // Spin quantum number
  double gyromagnetic_ratio_;  // Gyromagnetic ratio in M rad s-1 T-1 
                               // = Larmor frequency / magnetic field
  Eigen::Vector3d position_;   // Vector position in Angstroms
  
  ZeemanBasis zeeman_basis_;
  Eigen::VectorXcd state_;
  
  void initialize_zeeman_basis();

public:

  Spin();
  Spin(const double quantum_number,
       const double gyromagnetic_ratio,
       const Eigen::Vector3d & position);
  
  double get_quantum_number() const;
  double get_gyromagnetic_ratio() const;
  Eigen::Vector3d get_position() const;
  ZeemanBasis get_zeeman_basis() const;

  void set_quantum_number(const double quantum_number);
  void set_gyromagnetic_ratio(const double gyromagnetic_ratio);
  void set_position(const Eigen::Vector3d & position);
  
  unsigned int multiplicity() const;
  
  // add magnetic quantum number to basis
  void add_magnetic_quantum_number_to_zeeman_basis(
                                          const double magnetic_quantum_number);
  void build_zeeman_basis(); // using multiplicity

};

#endif // SPIN_H
