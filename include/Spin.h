#ifndef SPIN_H
#define SPIN_H

// Spin
//
// Quantum spin object containing gyromagnetic ratio and spin quantum number.
// Also calculates the dipolar interaction between two spins.
//
// Seto Balian 02/09/2013

#include "Named.h"
#include <string>

#include <Eigen/Dense>

class Spin
{

private:
  double        spinQuantumNumber_; // Total spin quantum number
  double        gyromagneticRatio_; // Gyromagnetic ratio in M rad s-1 T-1 
                                    // = Larmor frequency / Magnetic field
  Eigen::Vector3d        position_;          // Vector position in Angstroms
  
public:

  Spin();
  Spin(const std::string & name, const double spinQuantumNumber,
       const double gyromagneticRatio, const Eigen::Vector3d & position);
  
  double getSpinQuantumNumber() const;
  double getGyromagneticRatio() const;
  Eigen::Vector3d getPosition() const;

  void setSpinQuantumNumber(const double spinQuantumNumber);
  void setGyromagneticRatio(const double gyromagneticRatio);
  void setPosition(const Eigen::Vector3d & position);
  
  unsigned int multiplicity() const;

  double dipolar(const Spin & interactingSpin,
                 const Eigen::Vector3d & magneticFieldDirection) const;

  void print() const;

};

#endif // SPIN_H

