#ifndef DIPOLAR_H
#define DIPOLAR_H

// Calculates the strength of the dipolar interaction between two spins.
// Sources: arXiv:1204.2834v1 and arXiv:cond-mat/0211567v3
// The units of the constant are M rad s-1.
// See source code for how the calculation is performed.
//
// Created  26/10/2011
// Modified 19/09/2012, 20/09/2012, 08/03/2013
// Seto Balian
// V1

// NOTE: Needs more commenting

#include "stdincludes.hpp"
#include "spincoupling.hpp"
#include "threevector.hpp"

using namespace std;

class dipolar : public spincoupling
{
  
public:
  
  dipolar();
  dipolar(const string & name_in, const threevector & lattice_vector_in, const double gyromagneticRatio_in);
  void set_prefactor();
  double calculate(const threevector & magnetic_field_direction) const;
  double calculateMaxAbs() const;
  
};

#endif // DIPOLAR_H

