// Calculates the strength of the dipolar interaction between two spins.
// Sources: arXiv:1204.2834v1 and arXiv:cond-mat/0211567v3
// The units of the constant are M rad s-1.
// See source code for how the calculation is performed.
//
// Created  26/10/2011
// Modified 19/09/2012, 20/09/2012, 15/11/2012, 23/11/2012, 08/03/2013, 12/05/2013
// Seto Balian
// V1

// NOTE: Needs more commenting

#include "stdincludes.hpp"
#include "dipolar.hpp"
#include "spincoupling.hpp"
#include "threevector.hpp"

using namespace std;

dipolar::dipolar() : spincoupling() {}

dipolar::dipolar(const string & name_in, const threevector & lattice_vector_in, const double gyromagneticRatio_in) 
		    : spincoupling(name_in, lattice_vector_in, gyromagneticRatio_in, gyromagneticRatio_in) {}

void dipolar::set_prefactor() {
  spincoupling::set_prefactor(VACPERMD4PI*spincoupling::get_gyromagneticRatio_1()*spincoupling::get_gyromagneticRatio_2()*HBAR*1.0e6);
                      // units M rad s-1 m^3
  return;
}

double dipolar::calculate(const threevector & magnetic_field_direction) const {

  double cosThetaSq = pow ( threevector::cos_theta ( spincoupling::get_lattice_vector(), magnetic_field_direction ) , 2.0 );
  double modR = spincoupling::get_lattice_vector().mod(); // units Angstroms
  
  return spincoupling::get_prefactor()*(1.0 - 3.0*cosThetaSq)/pow(modR*ANGSTROM,3.0); // units M rad s-1
  
}

double dipolar::calculateMaxAbs() const {

  double modR = spincoupling::get_lattice_vector().mod(); // units Angstroms
  
  return spincoupling::get_prefactor()*(2.0)/pow(modR*ANGSTROM,3.0); // units M rad s-1

}



