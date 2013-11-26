#ifndef DIPOLAR_H
#define	DIPOLAR_H

// Dipolar
//
// Dipolar interaction between a pair of spins,
// @todo(keeping only energy conserving and spin conserving terms.)
//
// D = D0 * gamma_1 gamma_2 ( 1.0 - 3.0*cos^2[theta]^2 ) / (1e-10 r)^3
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
// From: arXiv:cond-mat/0211567 or Phys. Rev. B 68, 115322 (2003)
//
// Seto Balian, November 26, 2013

#include "SpinInteraction.h"
#include "Spin.h"
#include "UniformMagneticField.h"

class Dipolar : public SpinInteraction
{
public:
  
  Dipolar();
  // sets SpinInteraction::strength_ 
  void calculate(const Spin & spin_1,
                 const Spin & spin_2,
                 const UniformMagneticField & field);
};

#endif	 // DIPOLAR_H
