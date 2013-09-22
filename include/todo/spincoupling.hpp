#ifndef SPINCOUPLING_H
#define SPINCOUPLING_H

// This is a low-level class used for calculating spin couplings between
// two spins.
//
// Created 19/09/2012 hyperfineTensor -> spincoupling
// Modified 20/09/2012
// Seto Balian
// V1

// NOTE: Needs commenting

#include "stdincludes.hpp"
#include "named.hpp"
#include "threevector.hpp"

using namespace std;

class spincoupling : public named
{
private:
  threevector lattice_vector;       // lattice vector in Angstroms
  double gyromagneticRatio_1;       // gyromagnetic ratio in M rad s-1 / T
  double gyromagneticRatio_2;       // gyromagnetic ratio in M rad s-1 / T
  double prefactor;

public:

  spincoupling();
  spincoupling(const string & name_in, const threevector & lattice_vector_in, const double gyromagneticRatio_1_in, const double gyromagneticRatio_2_in);
  
  threevector get_lattice_vector() const;
  double get_gyromagneticRatio_1() const;
  double get_gyromagneticRatio_2() const;
  double get_prefactor() const;
  
  void set_lattice_vector(const threevector & lattice_vector_in);
  void set_gyromagneticRatio_1(const double gyromagneticRatio_1_in);
  void set_gyromagneticRatio_2(const double gyromagneticRatio_2_in);
  void set_prefactor(const double prefactor_in);

};

#endif // SPINCOUPLING_H

