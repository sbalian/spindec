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
#include "spincoupling.hpp"
#include "threevector.hpp"

using namespace std;

spincoupling::spincoupling() : named::named("") {
  threevector zero_vector;
  set_lattice_vector( zero_vector );
  set_gyromagneticRatio_1(0.0);
  set_gyromagneticRatio_2(0.0);
  prefactor = 1.0;
}

spincoupling::spincoupling(const string & name_in, const threevector & lattice_vector_in, const double gyromagneticRatio_1_in, const double gyromagneticRatio_2_in) : named(name_in) {
  set_lattice_vector(lattice_vector_in);
  set_gyromagneticRatio_1(gyromagneticRatio_1_in);
  set_gyromagneticRatio_2(gyromagneticRatio_2_in);
  prefactor = 1.0;
}

threevector spincoupling::get_lattice_vector() const {
 return lattice_vector;
}

double spincoupling::get_gyromagneticRatio_1 () const {
 return gyromagneticRatio_1;
}

double spincoupling::get_gyromagneticRatio_2 () const {
 return gyromagneticRatio_2;
}

double spincoupling::get_prefactor() const {
 return prefactor;
}

void spincoupling::set_lattice_vector(const threevector & lattice_vector_in) {
 lattice_vector = lattice_vector_in;
 return;
}

void spincoupling::set_gyromagneticRatio_1(const double gyromagneticRatio_1_in) {
 gyromagneticRatio_1 = gyromagneticRatio_1_in;
 return;
}

void spincoupling::set_gyromagneticRatio_2(const double gyromagneticRatio_2_in) {
 gyromagneticRatio_2 = gyromagneticRatio_2_in;
 return;
}

void spincoupling::set_prefactor(const double prefactor_in) {
 prefactor = prefactor_in;
 return;
}


