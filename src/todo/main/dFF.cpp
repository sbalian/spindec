// Created  15/01/2013 - from directflipflop.cpp
// Seto Balian
// V1

#include "stdincludes.hpp"
#include "cceincludes.hpp"

using namespace Eigen; // for matrix algebra package Eigen
using namespace std;

int main() {

//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
// INITIALISE
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@


//#############################################################################
// BEGIN INPUT
//#############################################################################


// Magnetic field in Tesla
double B = 0.188;

// Magnetic field direction
threevector B_dir(1.0,0.0,-1.0);

// Central electron gyromagnetic ratio in M rad s-1 T-1
double gamma_e = 1.7591e+5;

// Central nucleus gyromagnetic ratio in M rad s-1 T-1
double gamma_n = -43.744;

// Central nucleus spin quantum number
frac I;
I.num = 9;
I.den = 2;

// Central donor hyperfine strength in M rad s-1
double A = 9.2702e3;

// Donor level 0
int level_0 = 9;

// Donor level 1
int level_1 = 12;

// Log time switch
bool log_time = 0;

// Initial time in microseconds
double i_time = 0;

// Final time in microseconds
double f_time = 2.0e6;

// Number of time steps
int n_time = 1000;

// c0_bath
double c0_bath = 1.0;
double c1_bath = sqrt(1.0 - c0_bath*c0_bath);

// No pipulse
bool no_pipulse = 0;

// Bath spin position
threevector bathpos(0,0,380.0*5.43);

//#############################################################################
// END INPUT
//#############################################################################

// Continue initialisation ...

int i, j;

// L(t) holders - L: spin echo intensity. t: time.
ft L_t(i_time,f_time,n_time,log_time,1);
L_t.set_f_ones();

// Normalise magnetic field direction
B_dir = B_dir.normalised();

// Electron spin quantum number
frac S;
S.num = 1;
S.den = 2;

// Set up spin objects
//                          spin ID
spin celec("'Donor electron'", 0, S, gamma_e);
spin cnuc ("'Donor nucleus'" , 1, I, gamma_n);

// Set up analytical donor
elecNucSpin donor_analytical("Analytical donor",celec,cnuc,A,B);

// Set up spins
spins donors("'2xdonor'");
donors.add(celec);
donors.add(cnuc);
donors.add(celec);
donors.add(cnuc);

// Get subspace magnetic quantum numbers
MatrixXd donor_mQNs;
donor_mQNs = donor_analytical.get_high_field_basis(level_0,level_1);

// Build high field basis
donors.build_high_field_basis();
donors.truncate_high_field_basis_by_2_spins(0,1,donor_mQNs);
donors.truncate_high_field_basis_by_2_spins(2,3,donor_mQNs);
MatrixXd donorsbasis = donors.get_high_field_basis();

// Solve for 1 donor
spins donor("'Donor'");
donor.add(celec);
donor.add(cnuc);
donor.build_high_field_basis();
donor.truncate_high_field_basis_by_2_spins(0,1,donor_mQNs);
qoperator donorH(donor.dimension()); // Hamiltonian
spinHamiltonian::Zeeman(donorH, donor, donor.get_high_field_basis(), B);
spinHamiltonian::IsoHyperfine(donorH, donor, donor.get_high_field_basis(),0,1,A);
donorH.diagonalise("eigen");

// Donor eigenvectors

// Get donor levels for subspace
ArrayXi donor_levels;
donor_levels = donor_analytical.subspace_nLabels(level_0, level_1);
int donor_dim = donor_analytical.subspace_dimension(level_0, level_1);
statevector sysvec0, sysvec1;
sysvec0 = statevector(
                      donorH.get_eigenvector(donor_levels, level_0));
sysvec1 = statevector(
                      donorH.get_eigenvector(donor_levels, level_1));

vector<statevector> other_sysvecs;
for (i=0;i<donor_dim;i++) {
  if ( donor_levels(i) == level_0 ) {continue;}
  if ( donor_levels(i) == level_1 ) {continue;}
  other_sysvecs.push_back(
        statevector(donorH.get_eigenvector(donor_levels, donor_levels(i))));
}


// Donor Hamiltonian matrix elements
qoperator fixedH(donors.dimension());
spinHamiltonian::Zeeman(fixedH, donors,donorsbasis,B);
spinHamiltonian::IsoHyperfine(fixedH,donors,donorsbasis,0,1,A);
spinHamiltonian::IsoHyperfine(fixedH,donors,donorsbasis,2,3,A);

// Initial state
statevector isysvec ( sysvec0.get_col_vec() + 
                                   sysvec1.get_col_vec() ) ;
isysvec = isysvec.normalised();
statevector ibathvec, isysbathvec;

// Dipolar Hamiltonian
qoperator dipolarH(donors.dimension());

// Total Hamiltonian
qoperator totalH(donors.dimension());

// Unitary time evolver
qoperator Uevolve;


dipolar donordonordipolar("'Dipolar strength'",
                              threevector(0.0,0.0,0.0) ,
                              gamma_e);
donordonordipolar.set_prefactor();
donordonordipolar.set_lattice_vector(bathpos);
double D = donordonordipolar.calculate(B_dir);

// pipulse
qoperator sysvec0sysvec1(sysvec0,sysvec1);
qoperator sysvec1sysvec0(sysvec1,sysvec0);

qoperator sysPIpulse;
sysPIpulse = sysvec0sysvec1 + sysvec1sysvec0;
for (i=0;i<donor_dim-2;i++) {
  sysPIpulse = sysPIpulse + qoperator(other_sysvecs[i],other_sysvecs[i]);
}
qoperator bathIdentity = qoperator::Identity(donor_dim);
qoperator PIpulse = sysPIpulse^bathIdentity;


//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
// CALCULATE ECHO
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@


dipolarH.set_zeros();
spinHamiltonian::Dipolar(dipolarH, donors,donorsbasis,0,2,D);
totalH = fixedH + dipolarH;
totalH.diagonalise("eigen");

ibathvec = statevector ( c0_bath*sysvec0.get_col_vec() + 
                                c1_bath*sysvec1.get_col_vec() ) ;
isysbathvec = isysvec^ibathvec;

cmplxd norm, echo;
double t;

Uevolve = totalH.exponentiate(0.0);
if (no_pipulse == 0) {
  norm = HahnSpinEcho::calculate(cmplxd(1.0,0.0), Uevolve, PIpulse , isysbathvec, donor_dim, 
                                                        sysvec0, sysvec1);
} else {
    norm = HahnSpinEcho::calculate(cmplxd(1.0,0.0), Uevolve, isysbathvec, donor_dim, 
                                                        sysvec0, sysvec1);
  }

for (j=0;j<L_t.t_size();j++) {

  t = L_t.get_t(j);

  Uevolve = totalH.exponentiate(t);


  if (no_pipulse == 0) {
    echo = HahnSpinEcho::calculate(norm, Uevolve, PIpulse , isysbathvec, donor_dim, 
                                                          sysvec0, sysvec1);
  } else {
      echo = HahnSpinEcho::calculate(norm, Uevolve, isysbathvec, donor_dim, 
                                                          sysvec0, sysvec1);
    }

  L_t.set_f(j,0, L_t.get_f(j,0)*echo);

}

//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
// FINALISE
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

for (i=0;i<L_t.t_size();i++) {
  cout << left << scientific << setprecision(8);
  // Convert microseconds -> seconds
  cout << setw(32) << 2.0*L_t.get_t(i)/1.0e3;
  cout << setw(32) << abs(L_t.get_f(i,0)) << endl;
}


return 0;

}

