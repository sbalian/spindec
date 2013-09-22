// df/dB
// Created  21/02/2013
// Modified 25/02/2013, 11/04/2013
// Seto Balian V1 

#include "stdincludes.hpp" // Standard includes
#include "cceincludes.hpp" // CCE includes

using namespace Eigen; // Linear algebra package
using namespace std;

int main() {

//int main(int argc, char **argv) {
//if (argc != 2) { // argument count = 2, including the executable name
//  cout << "USAGE: dfdB [magnetic field in Tesla]" << endl;
//  return 0;
//}

// get B range // NOTE: Understand this better
//char * pEnd;
//double B = strtod (argv[1],&pEnd);


// electron gyromagnetic ratio in M rad s-1 T-1
double gamma_e = 1.7591e+5;

// nucleus gyromagnetic ratio in M rad s-1 T-1
double gamma_n = -43.766;

// nucleus total spin quantum number
frac I;
I.num = 9;
I.den = 2;

// donor hyperfine strength in M rad s-1
double A = 9.2702e3;

// Donor level 0 (lower)
int level_0 = 7;

// Donor level 1 (higher)
int level_1 = 14;

// Type of the diagonalizer
string diagtype = "zheev";

frac S;
S.num = 1;
S.den = 2;

spin electron("e" , 0, S, gamma_e);
spin nucleus("Bi" , 1, I, gamma_n);

spins donor("Donor spins");
donor.add(electron);
donor.add(nucleus);

// Build basis
donor.build_high_field_basis();
// Save basis
MatrixXd basisDonor = donor.get_high_field_basis();

// Set up donor Hamiltonian
qoperator donorH(donor.dimension());
donorH.set_zeros();

// Set up analytical donor object
elecNucSpin donor_analytical("Analytical donor",electron,nucleus,A,0.0);

double P_1, P_0, delta, m, n, N_1, N_0, f1, f2, B1, B2, delta_B,sigma,rho;
// for numerical df/dB
delta_B = 0.000001;

// Magnetic field
double initial_B = 0.1;
double final_B = 0.6;
int nsteps_B = 1000;
double B = initial_B;

double B_step = (final_B - initial_B)/(static_cast<double>(nsteps_B));


// Calculate and print to file

ofstream outfile("dfdB.dat");
outfile << left << scientific << setprecision(7);
int i;
for (i = 0;i< nsteps_B; i++) {

  outfile << setw(23) << B;

  // Numerical
  // ----------------------------
  B1 = B - delta_B;
  B2 = B + delta_B;
  donorH.set_zeros();
  // Zeeman
  spinHamiltonian::Zeeman(donorH, donor, basisDonor, B1);
  // Donor hyperfine
  spinHamiltonian::IsoHyperfine(donorH, donor, basisDonor,0,1,A);
  donorH.diagonalise(diagtype);
  // eigenvalues
  f1 = donorH.get_eigenvalues()(level_1 - 1) - donorH.get_eigenvalues()(level_0 - 1);
  donorH.set_zeros();
  // Zeeman
  spinHamiltonian::Zeeman(donorH, donor, basisDonor, B2);
  // Donor hyperfine
  spinHamiltonian::IsoHyperfine(donorH, donor, basisDonor,0,1,A);
  donorH.diagonalise(diagtype);
  // eigenvalues
  f2 = donorH.get_eigenvalues()(level_1 - 1) - donorH.get_eigenvalues()(level_0 - 1);
  // df/dB (local gradient)
  outfile << setw(23) << (f1 - f2)/(B1 - B2);

  // Analytical
  // ----------------------------
  donor_analytical.set_B(B);
  m = donor_analytical.nLabel_to_adiabLabel(level_1).second;
  n = donor_analytical.nLabel_to_adiabLabel(level_0).second;
  sigma = donor_analytical.pm_to_double(donor_analytical.nLabel_to_adiabLabel(level_1).first);
  rho   = donor_analytical.pm_to_double(donor_analytical.nLabel_to_adiabLabel(level_0).first);
  P_1 = 0.5*sigma*donor_analytical.get_polarization(m);
  P_0 = 0.5*rho*donor_analytical.get_polarization(n);
  delta = donor_analytical.get_d();
  outfile << setw(23) << gamma_e*( delta*(n - m) + (1.0 + delta)*(P_1 - P_0) );

  // Mathematica
  // ----------------------------
  outfile << setw(23) << donor_analytical.effGyromagneticRatio(level_1,level_0);

  // gE [<Sz>u - <Sz>l] + gN [<Iz>u - <Iz>l]
  // ---------------------------------------------
  N_1 = (m - 0.5*sigma)*pow(donor_analytical.get_a(m),2.0)
      +(m + 0.5*sigma)*pow(donor_analytical.get_b(m),2.0);
  N_0 = (n - 0.5*rho)*pow(donor_analytical.get_a(n),2.0)
      +(n + 0.5*rho)*pow(donor_analytical.get_b(n),2.0);

  outfile << setw(23) << gamma_e*( P_1 - P_0 ) + gamma_n*(N_1 - N_0);

  B += B_step;
  outfile << endl;
}
outfile.close();
cout << "Wrote output to dfdB.dat" << endl;
cout << "COL0: Magnetic field B in [T]" << endl;
cout << "COL1-4 units: [M rad s-1 T-1]" << endl;
cout << "COL1: Numerical df/dB" << endl;
cout << "COL2: Analytical df/dB [M rad s-1 T-1]" << endl;
cout << "COL3: Mathematica df/dB [M rad s-1 T-1]" << endl;
cout << "COL4: gE [<Sz>u - <Sz>l] + gN [<Iz>u - <Iz>l]" << endl;

return 0;

}

