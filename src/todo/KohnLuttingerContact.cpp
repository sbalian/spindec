// Calculates the Fermi contact interaction using the Kohn-Luttinger electronic wavefunction.
// Source: arXiv:cond-mat/0211567v3
// The units of the constant are M rad s-1.
// See source code for how the calculation is performed.
//
// Created  24/10/2011
// Modified 19/09/2012, 20/09/2012, 11/10/2012, 24/11/2012, 13/05/2013, 14/05/2013
// Seto Balian
// V1

// NOTE: Needs more commenting

#include "stdincludes.hpp"
#include "KohnLuttingerContact.hpp"
#include "spincoupling.hpp"
#include "threevector.hpp"

using namespace std;

KohnLuttingerContact::KohnLuttingerContact() : spincoupling() {
  set_a0(0.0);
  set_a(0.0);
  set_b(0.0);
  set_Ei(0.0);
  set_eta(0.0);
}

KohnLuttingerContact::KohnLuttingerContact(const string & name_in, const threevector & lattice_vector_in, const double gyromagneticRatio_1_in, const double gyromagneticRatio_2_in, const double a0_in, const double a_in,const double b_in,const double Ei_in,const double eta_in) 
       : spincoupling(name_in, lattice_vector_in, gyromagneticRatio_1_in, gyromagneticRatio_2_in) {
  set_a0(a0_in);
  set_a(a_in);
  set_b(b_in);
  set_Ei(Ei_in);
  set_eta(eta_in);
}

double KohnLuttingerContact::get_a0() const {
  return a0;
}

double KohnLuttingerContact::get_a() const {
 return a; 
}

double KohnLuttingerContact::get_b() const {
 return b; 
}

double KohnLuttingerContact::get_Ei() const {
 return Ei; 
}

double KohnLuttingerContact::get_eta() const {
 return eta; 
}

void KohnLuttingerContact::set_a0(const double a0_in) {
 a0 = a0_in;
 return;
}

void KohnLuttingerContact::set_a(const double a_in) {
 a = a_in;
 return;
}

void KohnLuttingerContact::set_b(const double b_in) {
 b = b_in;
 return;
}

void KohnLuttingerContact::set_Ei(const double Ei_in) {
 Ei = Ei_in;
 return;
}

void KohnLuttingerContact::set_eta(const double eta_in) {
 eta = eta_in;
 return;
}

double KohnLuttingerContact::get_na() const {  // units Angstroms
  return sqrt(0.029 / get_Ei())*get_a();       // 0.029 in eV
}

double KohnLuttingerContact::get_nb() const {  // units Angstroms
  return sqrt(0.029 / get_Ei())*get_b();       // 0.029 in eV
}

void KohnLuttingerContact::set_prefactor() { // units M rad s-1 m^3          // NOTE: 1.0e6 factor should be here ... because (Mega)^2
  spincoupling::set_prefactor ( (16.0*PI/9.0)*(spincoupling::get_gyromagneticRatio_1()*spincoupling::get_gyromagneticRatio_2()*1.0e6)*get_eta()*HBAR*VACPERMD4PI );
  return;
}

double KohnLuttingerContact::get_F(int i) const {    // units Angstroms^(-3/2)

  double nbfrac = pow(1.0/get_nb(),2.0), nafrac = pow(1.0/get_na(),2.0);
  
  switch (i){
  case 1:
    nbfrac = nbfrac*pow(spincoupling::get_lattice_vector().get_x(),2.0) ;
    nafrac = nafrac*(pow(spincoupling::get_lattice_vector().get_y(),2.0)+pow(spincoupling::get_lattice_vector().get_z(),2.0));
    break;
  case 2:
    nbfrac = nbfrac*pow(spincoupling::get_lattice_vector().get_x(),2.0) ;
    nafrac = nafrac*(pow(spincoupling::get_lattice_vector().get_y(),2.0)+pow(spincoupling::get_lattice_vector().get_z(),2.0));
    break;
  case 3:
    nbfrac = nbfrac*pow(spincoupling::get_lattice_vector().get_y(),2.0) ;
    nafrac = nafrac*(pow(spincoupling::get_lattice_vector().get_z(),2.0)+pow(spincoupling::get_lattice_vector().get_x(),2.0));
    break;
  case 4:
    nbfrac = nbfrac*pow(spincoupling::get_lattice_vector().get_y(),2.0) ;
    nafrac = nafrac*(pow(spincoupling::get_lattice_vector().get_z(),2.0)+pow(spincoupling::get_lattice_vector().get_x(),2.0));
    break;
  case 5:
    nbfrac = nbfrac*pow(spincoupling::get_lattice_vector().get_z(),2.0) ;
    nafrac = nafrac*(pow(spincoupling::get_lattice_vector().get_x(),2.0)+pow(spincoupling::get_lattice_vector().get_y(),2.0));
    break;
  case 6:
    nbfrac = nbfrac*pow(spincoupling::get_lattice_vector().get_z(),2.0) ;
    nafrac = nafrac*(pow(spincoupling::get_lattice_vector().get_x(),2.0)+pow(spincoupling::get_lattice_vector().get_y(),2.0));
    break;
  default:
    nbfrac = nbfrac*pow(spincoupling::get_lattice_vector().get_x(),2.0) ;
    nafrac = nafrac*(pow(spincoupling::get_lattice_vector().get_y(),2.0)+pow(spincoupling::get_lattice_vector().get_z(),2.0));
    break;
  }
  
  return exp(-sqrt(nbfrac + nafrac))/ (sqrt( PI*pow(get_na(),2.0) * get_nb()  ));
  
}

double KohnLuttingerContact::get_sumSq() const { // units m^(-3)
  
  double k0 = 0.85*2.0*PI/get_a0();
  
  return    pow(   get_F(1)*cos(k0*spincoupling::get_lattice_vector().get_x())  
		     + get_F(3)*cos(k0*spincoupling::get_lattice_vector().get_y())         // to convert from Angstroms to metres
		     + get_F(5)*cos(k0*spincoupling::get_lattice_vector().get_z()) , 2.0)/(pow(ANGSTROM,3.0));
 
}

double KohnLuttingerContact::calculate() const { // units M rad s-1
  return spincoupling::get_prefactor()*get_sumSq(); 
}

// NOTE: Can be optimized (second prefactor)
double KohnLuttingerContact::calculate(const threevector & magnetic_field_direction) const { // anisotropy
  double modR = spincoupling::get_lattice_vector().mod();
  double cutoff = modR - get_na();
  double cosThetaSq = pow ( threevector::cos_theta ( spincoupling::get_lattice_vector(), magnetic_field_direction ) , 2.0 );
  double anisotropy;

  if (cutoff >= 0.0) {
    anisotropy = -(spincoupling::get_gyromagneticRatio_1()*spincoupling::get_gyromagneticRatio_2()*1.0e6)*HBAR*VACPERMD4PI*(1.0 - 3.0*cosThetaSq)/pow(modR*ANGSTROM,3.0);
//    cout << "ANI " << anisotropy << endl;
    return calculate() + anisotropy;
  } else {
//    cout << "ISO " << calculate() << endl;
      return calculate();
    }
}


