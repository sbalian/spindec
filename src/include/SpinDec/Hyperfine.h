#ifndef HYPERFINE_H_
#define HYPERFINE_H_

// SpinDec::Hyperfine
//
// Calculates the hyperfine interaction between an electron and a nucleus in
// a lattice. Note that this is a magnetic dipole interaction, but is not
// to be confused with the 1/r^3 dipole-dipole interaction in Dipolar.h.
//
// H_A = A Sz Iz + (1/2) A [S+I- + S-I+]
//
// This class calculates A for the above Hamiltonian, H_A, where S and I are the
// electronic and nuclear spin operators. Also fills the Hamiltonian matrix
// elements for H_A. Uses the Kohn-Luttinger electronic wavefunction.
//
// A = p * q - D(B,R)*theta(|R| - na )
//
// Units: M rad s-1
//
// The first term (p * q) is the isotropic Fermi contact part.
//
// p = (1.6 pi hbar / 9)*gamma_e*gamma_n*eta
//
// hbar: reduced Planck constant [J s]
// gamma_e: electron gyromagnetic ratio [M rad s-1 T-1]
// gamma_n: nuclear gyromagnetic ratio  [M rad s-1 T-1]
// eta: charge density
// 
// q = (10^30) |F1(R)cos(k0*x) + F3(R)cos(k0*y) + F5(R)cos(k0*z) |^2
//
// R = vector between nucleus and electron (x,y,z: components) [Angstroms]
// k0 = 0.85*2*pi*a0 [Angstroms^-1]
//
// F1,2(R)=exp[-sqrt(x^2/(nb)^2 + (y^2 + z^2)/(na)^2 )]/sqrt[pi (na)^2 nb]
// F3,4(R): x y z -> y z x
// F5,6(R): x y z -> z x y
//
// n = sqrt(0.029/Eie), Eie: electron ionization energy [eV]
// a: lattice parameter a [Angstroms]
// b: lattice parameter b [Angstroms]
//
// The second term (- D(B,R)*theta(|R| - na ) ) is the dipolar part.
// B is the magnetic field [T], theta the Heaviside step function and
// D [M rad s-1] the dipolar interaction (See Dipolar.h).
//
// From: arXiv:cond-mat/0211567 (Phys. Rev. B 68, 115322 (2003))
//
// Seto Balian, Mar 28, 2014

#include "SpinDec/SpinInteraction.h"

//#include "SpinDec/ElectronSpin.h"
//#include "SpinDec/NuclearSpin.h"

#include "SpinDec/HyperfineParameters.h"

namespace SpinDec
{

class Hyperfine : public SpinInteraction
{
private:

  HyperfineParameters parameters_;
  
  double envelope_function(const UInt index,
      const ThreeVector & separation) const;
  double n_parameter() const;
  double n_times_a() const;
  double n_times_b() const;
  double scaled_probability_density(const ThreeVector & separation) const;
  
public:
  
  Hyperfine();
  // If you wish to calculate
  explicit Hyperfine(const HyperfineParameters & parameters);
  // If you don't wish to calculate
  Hyperfine(const double strength);
  
  virtual void calculate(const SpinParameters & electron_parameters,
      const SpinParameters & nuclear_parameters,
      const ThreeVector& electron_position,
      const ThreeVector& nuclear_position,
      const UniformMagneticField & field);

  virtual void fill(ComplexMatrix * hamiltonian,
                   const SpinParametersVector & spin_parameters_vector,
                   const SpinBasis & basis,
                   const UInt spin_label1,
                   const UInt spin_label2) const;
  
  virtual std::auto_ptr<SpinInteraction> clone() const;

};

} // namespace SpinDec

#endif // HYPERFINE_H_
