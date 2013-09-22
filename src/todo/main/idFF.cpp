// Created  15/01/2013 - from dFF.cpp
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
threevector B_dir(1.0,0.0,1.0);
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
int l0d = 9;
// Donor level 1
int l1d = 12;
// bath levels
int l0b1 =  7;
int l1b1 = 14;

int l0b2 = 7;
int l1b2 = 14;
// Log time switch
bool log_time = 0;
// Initial time in microseconds
double i_time = 0;
// Final time in microseconds
double f_time = 2.0e8;
// Number of time steps
int n_time = 200;

// c0_bath
double c0_b1 = 1.0/sqrt(2.0);
double c1_b1 = sqrt(1.0 - c0_b1*c0_b1);
// c1_bath
double c0_b2 = 1.0/sqrt(2.0);
double c1_b2 = sqrt(1.0 - c0_b2*c0_b2);

// No pipulse
bool no_pipulse = 0;

// Bath spin position
threevector bathpos1(0,0,380.0*5.43);
threevector bathpos2(0,0,280.0*5.43);

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
spins donor("'donor'");
donor.add(celec);
donor.add(cnuc);

spins bath1("'bath1'");
bath1.add(celec);
bath1.add(cnuc);

spins bath2("'bath2'");
bath2.add(celec);
bath2.add(cnuc);


// Get subspace magnetic quantum numbers
MatrixXd donor_mQNs;
donor_mQNs = donor_analytical.get_high_field_basis(l0d,l1d);

MatrixXd bath1_mQNs;
bath1_mQNs = donor_analytical.get_high_field_basis(l0b1,l1b1);

MatrixXd bath2_mQNs;
bath2_mQNs = donor_analytical.get_high_field_basis(l0b2,l1b2);

// Build high field basis
spins allspins("allSpins");

allspins.add(celec);
allspins.add(cnuc);
allspins.add(celec);
allspins.add(cnuc);
allspins.add(celec);
allspins.add(cnuc);

allspins.build_high_field_basis();
allspins.truncate_high_field_basis_by_2_spins(0,1,donor_mQNs);
allspins.truncate_high_field_basis_by_2_spins(2,3,bath1_mQNs);
allspins.truncate_high_field_basis_by_2_spins(4,5,bath2_mQNs);

MatrixXd basis = allspins.get_high_field_basis();

// Solve for 1 donor
donor.build_high_field_basis();
donor.truncate_high_field_basis_by_2_spins(0,1,donor_mQNs);
qoperator donorH(donor.dimension()); // Hamiltonian
spinHamiltonian::Zeeman(donorH, donor, donor.get_high_field_basis(), B);
spinHamiltonian::IsoHyperfine(donorH, donor, donor.get_high_field_basis(),0,1,A);
donorH.diagonalise("zheev");


bath1.build_high_field_basis();
bath1.truncate_high_field_basis_by_2_spins(0,1,bath1_mQNs);
qoperator bath1H(bath1.dimension()); // Hamiltonian
spinHamiltonian::Zeeman(bath1H, bath1, bath1.get_high_field_basis(), B);
spinHamiltonian::IsoHyperfine(bath1H, bath1, bath1.get_high_field_basis(),0,1,A);
bath1H.diagonalise("zheev");


bath2.build_high_field_basis();
bath2.truncate_high_field_basis_by_2_spins(0,1,bath2_mQNs);
qoperator bath2H(bath2.dimension()); // Hamiltonian
spinHamiltonian::Zeeman(bath2H, bath2, bath2.get_high_field_basis(), B);
spinHamiltonian::IsoHyperfine(bath2H, bath2, bath2.get_high_field_basis(),0,1,A);
bath2H.diagonalise("zheev");

// Donor eigenvectors

// Get donor levels for subspace
ArrayXi donor_levels;
donor_levels = donor_analytical.subspace_nLabels(l0d, l1d);
int donor_dim = donor_analytical.subspace_dimension(l0d, l1d);
statevector sysvec0, sysvec1;
sysvec0 = statevector(
                      donorH.get_eigenvector(donor_levels, l0d));
sysvec1 = statevector(
                      donorH.get_eigenvector(donor_levels, l1d));

vector<statevector> other_sysvecs;
for (i=0;i<donor_dim;i++) {
  if ( donor_levels(i) == l0d ) {continue;}
  if ( donor_levels(i) == l1d ) {continue;}
  other_sysvecs.push_back(
        statevector(donorH.get_eigenvector(donor_levels, donor_levels(i))));
}


ArrayXi bath1_levels;
bath1_levels = donor_analytical.subspace_nLabels(l0b1, l1b1);
int bath1_dim = donor_analytical.subspace_dimension(l0b1, l1b1);
statevector bath1vec0, bath1vec1;
bath1vec0 = statevector(
                      bath1H.get_eigenvector(bath1_levels, l0b1));
bath1vec1 = statevector(
                      bath1H.get_eigenvector(bath1_levels, l1b1));

vector<statevector> other_bath1vecs;
for (i=0;i<bath1_dim;i++) {
  if ( bath1_levels(i) == l0b1 ) {continue;}
  if ( bath1_levels(i) == l1b1 ) {continue;}
  other_bath1vecs.push_back(
        statevector(bath1H.get_eigenvector(bath1_levels, bath1_levels(i))));
}

ArrayXi bath2_levels;
bath2_levels = donor_analytical.subspace_nLabels(l0b2, l1b2);
int bath2_dim = donor_analytical.subspace_dimension(l0b2, l1b2);
statevector bath2vec0, bath2vec1;
bath2vec0 = statevector(
                      bath2H.get_eigenvector(bath2_levels, l0b2));
bath2vec1 = statevector(
                      bath2H.get_eigenvector(bath2_levels, l1b2));

vector<statevector> other_bath2vecs;
for (i=0;i<bath1_dim;i++) {
  if ( bath2_levels(i) == l0b2 ) {continue;}
  if ( bath2_levels(i) == l1b2 ) {continue;}
  other_bath2vecs.push_back(
        statevector(bath2H.get_eigenvector(bath2_levels, bath2_levels(i))));
}




// Hamiltonian matrix elements

qoperator TotalH(allspins.dimension());

spinHamiltonian::Zeeman(TotalH, allspins,basis,B);

spinHamiltonian::IsoHyperfine(TotalH,allspins,basis,0,1,A);
spinHamiltonian::IsoHyperfine(TotalH,allspins,basis,2,3,A);
spinHamiltonian::IsoHyperfine(TotalH,allspins,basis,4,5,A);


dipolar donorbath1dipolar("",
                              bathpos1 ,
                              gamma_e);

dipolar donorbath2dipolar("",
                              bathpos2 ,
                              gamma_e);

dipolar bathdipolar("",
                              bathpos2 - bathpos1 ,
                              gamma_e);


donorbath1dipolar.set_prefactor();
donorbath2dipolar.set_prefactor();
bathdipolar.set_prefactor();


double D1 = donorbath1dipolar.calculate(B_dir);
double D2 = donorbath2dipolar.calculate(B_dir);
double D = bathdipolar.calculate(B_dir);

 D1 = 1.1e-6;
 D2 = 1.3e-6;
 D  = 1.2e-6;


// Dipolar Hamiltonian
spinHamiltonian::Ising(TotalH,allspins,basis,0,2,D1);
spinHamiltonian::Ising(TotalH,allspins,basis,0,4,D2);
spinHamiltonian::Dipolar(TotalH,allspins,basis,2,4,D);

TotalH.diagonalise("zheev");


// Initial states
statevector isysvec ( sysvec0.get_col_vec() + 
                                   sysvec1.get_col_vec() ) ;

statevector ibath1vec ( c0_b1*bath1vec0.get_col_vec() + 
                                   c1_b1*bath1vec1.get_col_vec() ) ;

statevector ibath2vec ( c0_b2*bath2vec0.get_col_vec() + 
                                   c1_b2*bath2vec1.get_col_vec() ) ;

isysvec = isysvec.normalised();
ibath1vec = ibath1vec.normalised();
ibath2vec = ibath2vec.normalised();
statevector isysbathvec = isysvec^(ibath1vec^ibath2vec);

// Unitary time evolver
qoperator Uevolve;

// pipulse
qoperator sysvec0sysvec1(sysvec0,sysvec1);
qoperator sysvec1sysvec0(sysvec1,sysvec0);

qoperator sysPIpulse;
sysPIpulse = sysvec0sysvec1 + sysvec1sysvec0;
for (i=0;i<donor_dim-2;i++) {
  sysPIpulse = sysPIpulse + qoperator(other_sysvecs[i],other_sysvecs[i]);
}
qoperator bathIdentity = qoperator::Identity(bath1_dim*bath2_dim);
qoperator PIpulse = sysPIpulse^bathIdentity;


//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
// CALCULATE ECHO
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@


cmplxd norm, echo;
double t;

Uevolve = TotalH.exponentiate(0.0);

if (no_pipulse == 0) {

  norm = HahnSpinEcho::calculate(cmplxd(1.0,0.0), Uevolve, PIpulse , isysbathvec, bath1_dim*bath2_dim, 
                                                        sysvec0, sysvec1);

} else {
    norm = HahnSpinEcho::calculate(cmplxd(1.0,0.0), Uevolve, isysbathvec, bath1_dim*bath2_dim, 
                                                        sysvec0, sysvec1);
  }


for (j=0;j<L_t.t_size();j++) {

  t = L_t.get_t(j);

  Uevolve = TotalH.exponentiate(t);


  if (no_pipulse == 0) {
    echo = HahnSpinEcho::calculate(norm, Uevolve, PIpulse , isysbathvec, bath1_dim*bath2_dim, 
                                                          sysvec0, sysvec1);

  } else {
      echo = HahnSpinEcho::calculate(norm, Uevolve, isysbathvec, bath1_dim*bath2_dim, 
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

