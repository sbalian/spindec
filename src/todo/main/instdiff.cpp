// Created  15/01/2013 - from idFF.cpp
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
double B = 0.480;
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
// Levels
int l_n = 9;
int l_m = 12;
int l_p = 7;
int l_q = 14;
// Initial time in microseconds
double i_time = 0;
// Final time in microseconds
double f_time = 2.0e6;
// Number of time steps
int n_time = 1000;
// bath coefficients
double c_p = 1.0;
double c_q = sqrt(1.0 - c_p*c_p);
// Diolar strength (M rad s-1)
double d = 40e-2;
// Tip angles (radians)
double a = PI;
double b = PI;

//#############################################################################
// END INPUT
//#############################################################################

frac S;
S.num = 1;
S.den = 2;
// Set up spin objects
//                          spin ID
spin celec("'Donor electron'", 0, S, gamma_e);
spin cnuc ("'Donor nucleus'" , 1, I, gamma_n);
elecNucSpin donor_analytical("Analytical donor",celec,cnuc,A,B);

// Energies (M rad s-1)
double E_n = donor_analytical.get_eigenvalue(nLabel_to_adiabLabel(l_n).first,nLabel_to_adiabLabel(l_n).second);
double E_m = donor_analytical.get_eigenvalue(nLabel_to_adiabLabel(l_m).first,nLabel_to_adiabLabel(l_m).second);
double E_p = donor_analytical.get_eigenvalue(nLabel_to_adiabLabel(l_p).first,nLabel_to_adiabLabel(l_p).second);
double E_q = donor_analytical.get_eigenvalue(nLabel_to_adiabLabel(l_q).first,nLabel_to_adiabLabel(l_q).second);

// Polarisations
double P_n = donor_analytical.get_polarization(nLabel_to_adiabLabel(l_n).second);
double P_m = donor_analytical.get_polarization(nLabel_to_adiabLabel(l_m).second);
double P_p = donor_analytical.get_polarization(nLabel_to_adiabLabel(l_p).second);
double P_q = donor_analytical.get_polarization(nLabel_to_adiabLabel(l_q).second);

  double get_polarization(const double m) const;







% OWP
P_n = P_m;
% P_p = P_n;




% c_q = 0;
% c_p = 1;

%% Convert tip angles to radians and divide by 2
a = degtorad(a/2);
b = degtorad(b/2);

%% Calculate phases
phi_np = exp(-1i*t*(E_n + E_p + d*P_n*P_p));
phi_mp = exp(-1i*t*(E_m + E_p + d*P_m*P_p));
phi_nq = exp(-1i*t*(E_n + E_q + d*P_n*P_q));
phi_mq = exp(-1i*t*(E_m + E_q + d*P_m*P_q));

// Calculate complex echo terms
// R_mp, R_np , R_mq , R_nq

R_mp = phi_mp.*(c_p*phi_mp*cos(a)*cos(b) ...
               +c_p*phi_np*sin(a)*cos(b) ...
               +c_q*phi_mq*cos(a)*sin(b) ...
               +c_q*phi_nq*sin(a)*sin(b) );
           
R_np = phi_np.*(c_p*phi_np*cos(a)*cos(b) ...
               +c_p*phi_mp*sin(a)*cos(b) ...
               +c_q*phi_nq*cos(a)*sin(b) ...
               +c_q*phi_mq*sin(a)*sin(b) );
           
R_nq = phi_nq.*(c_q*phi_nq*cos(a)*cos(b) ...
               +c_q*phi_mq*sin(a)*cos(b) ...
               +c_p*phi_np*cos(a)*sin(b) ...
               +c_p*phi_mp*sin(a)*sin(b) );
           
R_mq = phi_mq.*(c_q*phi_mq*cos(a)*cos(b) ...
               +c_q*phi_nq*sin(a)*cos(b) ...
               +c_p*phi_mp*cos(a)*sin(b) ...
               +c_p*phi_np*sin(a)*sin(b) );
           


           
%% Calculate absolute of the complex echo
% 2*L(t) = | R_mp R_np* + R_mq R_nq* |

% normalisation
L = abs(R_mp.*conj(R_np) + R_mq.*conj(R_nq));
norm = L(1);

% calcluate absolute of echo
L = (1/norm)*abs(R_mp.*conj(R_np) + R_mq.*conj(R_nq));

%% Plot

plot(t,L);



// Set up analytical donor





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

