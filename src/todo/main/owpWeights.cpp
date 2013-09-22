// Created 13/05/2013
// Seto Balian
// V1

#include "stdincludes.hpp" // Standard includes
#include "cceincludes.hpp" // CCE includes

using namespace Eigen; // Linear algebra package
using namespace std;

int main() {

cout  << scientific << setprecision(8) << left;

double gamma_e = 1.760859708e5;
double gamma_n   = -43.775;
frac I;
I.num = 9;
I.den = 2;
double A =  9.2702e3;
int level_0 =  7;
int level_1  = 14;

frac S;
S.num = 1;
S.den = 2;

spin celec("CentralElectron", 0, S, gamma_e);
spin cnuc ("CentralNucleus" , 1, I, gamma_n);

double B = 0.07978;

// Set up donor object to form subspace or get effective gyromagnetic ratio
elecNucSpin donor_analytical("AnalyticalDonor",celec,cnuc,A,B);
donor_analytical.set_B(B);

double sigma0 = donor_analytical.pm_to_double(donor_analytical.nLabel_to_adiabLabel(level_0).first);
double sigma1 = donor_analytical.pm_to_double(donor_analytical.nLabel_to_adiabLabel(level_1).first);

double m0 = donor_analytical.nLabel_to_adiabLabel(level_0).second;
double m1 = donor_analytical.nLabel_to_adiabLabel(level_1).second;

double P0 = sigma0*donor_analytical.get_polarization(m0);
double P1 = sigma1*donor_analytical.get_polarization(m1);

// Read couplings
lattice toReadCouplings("couplings",0.0);
toReadCouplings.read_lattice_vectors("couplings.dat");

vector<double> J1;
vector<double> J2;
vector<double> C12;

int i;
int n = toReadCouplings.get_lattice_vectors_size();
for (i=0;i<n;i++) {
  J1.push_back(toReadCouplings.get_lattice_vector(i).get_x());
  J2.push_back(toReadCouplings.get_lattice_vector(i).get_y());
  C12.push_back(toReadCouplings.get_lattice_vector(i).get_z());
}

//cout << n << endl;
//exit(1);
//for (i=0;i<static_cast<int>(J1.size());i++) {
//  cout << setw(23) << J1[i] << setw(23) << J2[i] << setw(23) << C12[i] << endl;
//}


double K0 = 0.0;
double K1 = 0.0;

double epsilon0 = 0.0;
double epsilon1 = 0.0;

double xi_p_0 = 0.0;
double xi_p_1 = 0.0;

double xi_m_0 = 0.0;
double xi_m_1 = 0.0;

double R_p = 0.0;
double R_m = 0.0;

double C12sq = 0.0;

//double weightThreshold = 1.0e-15;

double weight = 0.0;
double J1minusJ2 = 0.0;

for (i=0;i<n;i++) {

  J1minusJ2 = (J1[i] - J2[i]);

  if ( J1minusJ2  == 0.0) {
    continue;
  }

  C12sq = pow( C12[i] ,2.0);

  K0 = (J1minusJ2)*P0;
  K1 = (J1minusJ2)*P1;

  epsilon0 = sqrt(C12sq + pow( K0 ,2.0));
  epsilon1 = sqrt(C12sq + pow( K1 ,2.0));

  xi_p_0 = K0 + epsilon0;
  xi_p_1 = K1 + epsilon1;

  xi_m_0 = K0 - epsilon0;
  xi_m_1 = K1 - epsilon1;

  R_p = C12sq*(C12sq + xi_p_1*xi_m_0)/
        ((C12sq + pow(xi_p_1,2.0) )*(C12sq + pow(xi_m_0,2.0) ));

  R_m = C12sq*(C12sq + xi_m_1*xi_p_0)/
        ((C12sq + pow(xi_m_1,2.0) )*(C12sq + pow(xi_p_0,2.0) ));

  weight = (1.0e6/4.0)*(R_p + R_m)*pow(epsilon0 + epsilon1,2.0)/16.0/sqrt(2.0);

  if (weight < 0) {
    continue;
  }

  if (C12[i] == 0) {
    continue;
  }

//  if (weight < 0 ) {

//  cout << setw(23) << J1[i] << setw(23) << J2[i];
  cout << setw(23) << abs(J1minusJ2);
  cout << setw(23) << weight;
  cout << setw(23) << C12[i];
  cout << endl;

//  }



}



return 0;

}

