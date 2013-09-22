// Created 09/05/2013
// Modified 13/05/2013
// Seto Balian
// V1

#include "stdincludes.hpp" // Standard includes
#include "cceincludes.hpp" // CCE includes

using namespace Eigen; // Linear algebra package
using namespace std;

int main() {


double gamma_e = 1.760859708e5;
double gamma_n   = -43.775;
frac I;
I.num = 9;
I.den = 2;
double A =  9.2702e3;
int level_0 =  2;
int level_1  = 19;

frac S;
S.num = 1;
S.den = 2;

spin celec("CentralElectron", 0, S, gamma_e);
spin cnuc ("CentralNucleus" , 1, I, gamma_n);

double B = 0.0;

// Set up donor object to form subspace or get effective gyromagnetic ratio
elecNucSpin donor_analytical("AnalyticalDonor",celec,cnuc,A,B);

double sigma0 = donor_analytical.pm_to_double(donor_analytical.nLabel_to_adiabLabel(level_0).first);
double sigma1 = donor_analytical.pm_to_double(donor_analytical.nLabel_to_adiabLabel(level_1).first);


double m0 = donor_analytical.nLabel_to_adiabLabel(level_0).second;
double m1 = donor_analytical.nLabel_to_adiabLabel(level_1).second;


double iB = 0.000;
double fB = 0.950;
int nB = 10000;
double dB = (fB - iB)/(static_cast<double>(nB));

int i;

B = iB;

cout  << scientific << left;

double T2 = 0.0;
double prefactor = 16.0e-3/(0.024);

double P1 = 0.0;
double P0 = 0.0;

for (i=0;i<nB;i++) {

  donor_analytical.set_B(B);

  P0 = sigma0*donor_analytical.get_polarization(m0);
  P1 = sigma1*donor_analytical.get_polarization(m1);


  T2 = prefactor*sqrt(abs(P1*P0))/abs(P1 - P0);

  cout << setw(20) << setprecision(6) << B;
  //cout << setw(20) << setprecision(8) << T2;
  cout << setw(20) << setprecision(8) << T2/sqrt(abs(P1*P0));
  cout << endl;

  B += dB;
}


return 0;

}

