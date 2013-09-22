// Created 12/05/2013
// Seto Balian
// V1

#include "stdincludes.hpp" // Standard includes
#include "cceincludes.hpp" // CCE includes
#include "argvparser.h" // Argument Parser: http://mih.voxindeserto.de/argvparser.html

using namespace Eigen; // Linear algebra package
using namespace std;

int main() {

cout << scientific << left << setprecision(8);

double orientation = 0.0;

double i_orientation = 0.0;
double f_orientation = 90.0;
int n_orientation = 1000;

double d_orientation = (f_orientation - i_orientation)/(static_cast<double>(n_orientation));


// Magnetic field direction
threevector B_dir;


double gamma  =  53.1903;



frac I;
I.num = 1;
I.den = 2;

spin silicon29 ("29Si" , 0, I, gamma);

threevector R(0.0,0.0,0.0);


dipolar C12("dipolar",R,gamma);
C12.set_prefactor();

threevector nn1 (-1.3575,	-1.3575,	-1.3575);
threevector nn2 (-1.3575,	1.3575,	1.3575);
threevector nn3 (1.3575,	-1.3575,	1.3575);
threevector nn4 (1.3575,	1.3575,	-1.3575);

//threevector nn1 (1.3575,	1.3575,	1.3575);
//threevector nn2 (1.3575,	-1.3575,	-1.3575);
//threevector nn3 (-1.3575,	1.3575,	-1.3575);
//threevector nn4 (-1.3575,	-1.3575,	1.3575);


int i;
orientation = i_orientation;
double avgC12 = 0.0;

for (i=0;i<=n_orientation;i++) {

  B_dir.set_x ( cos( orientation *(PI/180.0)) );
  B_dir.set_y ( sin( orientation *(PI/180.0)) );
  B_dir.set_z ( sin( orientation *(PI/180.0)) );

  // Normalise magnetic field direction
  B_dir = B_dir.normalised();

  avgC12 = 0.0;

  R = nn1;
  C12.set_lattice_vector(R);
  avgC12 += abs(C12.calculate(B_dir));

  R = nn2;
  C12.set_lattice_vector(R);
  avgC12 += abs(C12.calculate(B_dir));

  R = nn3;
  C12.set_lattice_vector(R);
  avgC12 += abs(C12.calculate(B_dir));

  R = nn4;
  C12.set_lattice_vector(R);
  avgC12 += abs(C12.calculate(B_dir));

  cout << setw(20) << orientation << setw(20) << avgC12 / 4.0 * 1000.0 << endl;

  orientation += d_orientation;

}



//double lattice_constant = 5.43;
//lattice siliconlattice("SiliconLattice", lattice_constant);
//int nsites = siliconlattice.generate_random_diamond_cubic(1,
//                                             100000001);
//double threshold = 1e-8;
//double nna = sqrt(3)/4*lattice_constant;
//double nnn = 0.0;
//int i;
//for (i=0;i<nsites;i++) {
//  nnn = siliconlattice.get_lattice_vector(i).mod();
//  if ( abs( nna - nnn ) <= threshold ) {
//    siliconlattice.get_lattice_vector(i).print('r');
//  }
//}


return 0;

}

