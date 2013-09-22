// Seto Balian 08/03/2013 
// V1

#include "stdincludes.hpp" // Standard includes
#include "cceincludes.hpp" // CCE includes

using namespace Eigen; // Linear algebra package
using namespace std;

int main(int argc, char **argv) {


double gamma_e = 1.760859708e5; // electron gyromagnetic ratio [M rad s-1 T-1]
double eIE = 0.069;           // electron ionization energy [eV]
double gamma_n   =   -43.775; // central nucleus gyromagnetic ratio [M rad s-1 T-1]
double gamma_b  =       -53.1903; // bath nucleus gyromagnetic ratio [M rad s-1 T-1]
double a0       =      5.43; // lattice constant [Angstroms]
double fcc_a    = 25.09         ; // FCC lattice parameter a [Angstroms]
double fcc_b     =     14.43;     // FCC lattice parameter b [Angstroms]
double eta    =   186.0;          // charge density

double initialDistance = -140;//(sqrt(3)/4)*a0;
double finalDistance = 140; // Angstroms
int nDistance = 60;

double dDistance = (finalDistance - initialDistance)/static_cast<double>(nDistance);

// Magnetic field direction
threevector B_dir;
B_dir.set_x ( 0.0 );
B_dir.set_y ( 0.0 );
B_dir.set_z ( 1.0 );
// Normalise magnetic field direction
 B_dir = B_dir.normalised();

threevector vec(0.0,0.0,0.0);


KohnLuttingerContact shf("shf",vec,gamma_e, gamma_b, a0, fcc_a, fcc_b, eIE, eta);

dipolar siliconSiliconDipolar("SiSiDipolar",vec,gamma_b);

dipolar bismuthSiliconDipolar("BiSiDipolar",vec,gamma_b);
bismuthSiliconDipolar.set_gyromagneticRatio_1(gamma_b);
bismuthSiliconDipolar.set_gyromagneticRatio_2(gamma_n);

shf.set_prefactor();
siliconSiliconDipolar.set_prefactor();
bismuthSiliconDipolar.set_prefactor();

cout << left << setprecision(8) << scientific;

int i,j;//,k;

double shfValue = 0.0;
double dipolarValue = 0.0;

double x = initialDistance;
double y = initialDistance;
//double z = initialDistance;

vec.set_z(0.0);

for (i =0 ;i <= nDistance; i++) {

  vec.set_x(x);
  y = initialDistance;

  for (j =0 ;j <= nDistance; j++) {

    vec.set_y(y);
//    z = initialDistance;

//    for (k =0 ;k <= nDistance; k++) {

//      vec.set_z(z);

      shf.set_lattice_vector(vec);
      siliconSiliconDipolar.set_lattice_vector(vec);
      //    bismuthSiliconDipolar.set_lattice_vector(vec);

      shfValue = shf.calculate();
      dipolarValue = siliconSiliconDipolar.calculateMaxAbs();
      //    dipolarValue = abs(siliconSiliconDipolar.calculate(B_dir));

//      if (vec.mod() < (sqrt(3.0)/4.0*a0) ) {
//        cout << setprecision(3) << setw(20) << vec.get_x();
//        cout << setprecision(3) << setw(20) << vec.get_y();
//        cout << setprecision(4) << setw(20) << 0.0 << endl;
//        continue;
//      }

      cout << setprecision(3) << setw(20) << vec.get_x();
      cout << setprecision(3) << setw(20) << vec.get_y();
//      cout << setprecision(3) << setw(20) << vec.get_z();
    //  cout << setw(20) << shf.calculate();
//      cout << setprecision(4) << setw(20) << log10(dipolarValue/shfValue) << endl;
      cout << setprecision(4) << setw(20) << log10(shfValue) << endl;
    //  cout << setw(20) << abs(siliconSiliconDipolar.calculate(B_dir)) << endl;
    //  cout << setw(20) << bismuthSiliconDipolar.calculate(B_dir) << endl;


//      z += dDistance;

//    }

    y += dDistance;

  }

  x += dDistance;

}


return 0;

}

