#ifndef KOHNLUTTINGERCONTACT_H
#define KOHNLUTTINGERCONTACT_H

// Calculates the Fermi contact interaction using the Kohn-Luttinger electronic wavefunction.
// Source: arXiv:cond-mat/0211567v3
// The units of the constant are M rad s-1.
// See source code for how the calculation is performed.
//
// Created  26/10/2011
// Modified 19/09/2012, 20/09/2012
// Seto Balian
// V1

// NOTE: Needs more commenting

#include "stdincludes.hpp"
#include "spincoupling.hpp"
#include "threevector.hpp"

using namespace std;

class KohnLuttingerContact : public spincoupling
{
private:
  double a0;  // Lattice constant in Angstroms
  double a;   // Lattice parameter in Angstroms
  double b;   // Lattice parameter in Angstroms
  double Ei;  // Donor electron ionization energy in eV
  double eta; // charge density (dimensionless)
  
public:
  
  KohnLuttingerContact();
  KohnLuttingerContact(const string & name_in, const threevector & lattice_vector_in,
                       const double gyromagneticRatio_1_in, const double gyromagneticRatio_2_in, // Electron and nucleus gyromagnetic ratios in M rad s-1
                        const double a0_in, const double a_in, const double b_in, const double Ei_in, const double eta_in);
  
  double get_a0() const;
  double get_a() const;
  double get_b() const;
  double get_Ei() const;
  double get_eta() const;
  
  void set_a0(const double a0_in);
  void set_a(const double a_in);
  void set_b(const double b_in);
  void set_Ei(const double Ei_in);
  void set_eta(const double eta_in);
  
  double get_na() const;
  double get_nb() const;
  
  void set_prefactor();
  double get_F(const int i) const;
  double get_sumSq() const;
  
  double calculate() const;

  // NOTE: can be optimized (second prefactor)
  double calculate(const threevector & magnetic_field_direction) const; // anisotropy
  
};

#endif // KOHNLUTTINGERCONTACT_H

