#ifndef DIPOLAR_H_
#define	DIPOLAR_H_

// Dipolar
//
// Dipolar interaction strength between a pair of spins
//
// D S_1^z S_2^z - (D / 4) [ S_1^+ S_2^- + S_1^- S_2^+ ]
//
// Strength
// D = D0 * gamma_1 gamma_2 ( 1.0 - 3.0*cos^2[theta] ) / (1e-10 r)^3
// 
// Units: M rad s-1
//
// gamma_1, gamma_2 [M rad s-1]: gyromagnetic ratios of the two interacting
//                               spins
// theta [rad]: angle between the magnetic field direction and the vector
//              parallel to the line connecting the two spins
// r [Angstroms]: distance between the two spins
//
// D0 = 1e6 * (\mu_0 / 4 pi)  hbar
//
// Units: M rad s-1 m^3
//
// hbar [J s]: reduced Plank constant
// (mu_0 / 4pi) = 1e-7 NA^-2 (mu_0 is the vacuum permeability)
//
// From: arXiv:cond-mat/0211567 (Phys. Rev. B 68, 115322 (2003))
//
// Seto Balian, Jan 28, 2014

#include "SpinInteraction.h"
#include "UniformMagneticField.h"

class Dipolar : public SpinInteraction
{
private:
  
  UniformMagneticField field_;
  virtual double calculate_non_spatial_dependence() const;

public:
  
  Dipolar();
  Dipolar(const Spin & spin1,
                  const Spin & spin2,
                  const UniformMagneticField & field);

  Dipolar(const Spin & spin1,
                  const Spin & spin2, const double strength,
                  const UniformMagneticField & field);
  
  virtual double calculate(const Eigen::Vector3d & position1,
                           const Eigen::Vector3d & position2);
  
  virtual void fill(Eigen::MatrixXcd & hamiltonian,
                   const SpinVector & spins,
                   const Eigen::ArrayXXd & basis,
                   const unsigned int spin_label1,
                   const unsigned int spin_label2) const;

};

#endif	 // DIPOLAR_H_
