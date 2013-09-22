// Created  31/10/2012
// Modified 01/11/2012 analyticaldonordonor -> directflipflop
// Modified 14/11/2012, 15/11/2012, 19/11/2012, 11/12/2012, 15/01/2013
// Seto Balian
// V1

// NOTE: Needs commenting, eg doc and intro, c0_bath etc ...

#include "stdincludes.hpp"
#include "cceincludes.hpp"

using namespace Eigen; // for matrix algebra package Eigen
using namespace std;

int main(int argc, char **argv) {

//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
// INITIALISE
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
  
// Read command line parameters
if (argc != 3) { // argument count = 3, including the executable name
cout << "ERROR: Invalid number of arguments to 'directflipflop'" << endl;
  cout << "USAGE: directflipflop infilename outfilename" << endl;
  cout << "Seto Balian - 11/12/2012 - V1" << endl;
  return 0;
}

// Argument input parameter file name
string input_file_name = argv[1];

// Argument output parameter file name
string output_file_name = argv[2];

cout << "'directflipflop' started:" << endl;
system("date");

//#############################################################################
// BEGIN INPUT
//#############################################################################

cceread infile ( input_file_name , "donornucbath"  , 0 );
cout << "Reading input file ..." << endl;
// Magnetic field in Tesla
double B = infile.get_double("B");

// Magnetic field direction
doubleTriplet B_dir_dt = infile.get_doubleTriplet("B_dir");
threevector B_dir;
B_dir.set_x ( B_dir_dt.d_1 );
B_dir.set_y ( B_dir_dt.d_2 );
B_dir.set_z ( B_dir_dt.d_3 );

// Central electron gyromagnetic ratio in M rad s-1 T-1
double gamma_e = infile.get_double("gamma_e");

// Central nucleus gyromagnetic ratio in M rad s-1 T-1
double gamma_n = infile.get_double("gamma_n");

// Central nucleus spin quantum number
frac I = infile.get_frac ("I");

// Central donor hyperfine strength in M rad s-1
double A = infile.get_double("A");

// Donor level 0
int level_0 = infile.get_int("level_0");

// Donor level 1
int level_1 = infile.get_int("level_1");

// Bath abundance
int bath_abundance_ppm = infile.get_int("bath_abundance_ppm");

// Cubic lattice size
int lattice_size = infile.get_int
                                           ("lattice_size");

// Log time switch
bool log_time = infile.get_bool("log_time");

// Initial time in microseconds
double i_time = infile.get_double("i_time");

// Final time in microseconds
double f_time = infile.get_double("f_time");

// Number of time steps
int n_time = infile.get_int("n_time");


// Seed random number generator? (using current time)
bool seed_rand = infile.get_bool("seed_rand");

// c0_bath
double c0_bath = infile.get_double("c0_bath");

// random c0_bath ?
bool rand_c0_bath = infile.get_bool("rand_c0_bath");

// No pipulse
bool no_pipulse = infile.get_bool("no_pipulse");

// Diagonaliser
string diagtype = infile.get_string("diagtype");

// Silicon lattice constant in Angstroms
double a0 = infile.get_double("a0");

//#############################################################################
// END INPUT
//#############################################################################

// Continue initialisation ...

// Seed random number generator
if (seed_rand) {
  srand ( time(NULL) );
}
int i, tint;
for (i=0;i<100;i++) {
  tint = rand();
}

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
donorH.diagonalise(diagtype);

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

// Lattice vectors
lattice silat("'Silicon lattice'", a0);


dipolar donordonordipolar("'Dipolar strength'",
                              threevector(0.0,0.0,0.0) ,
                              gamma_e);
donordonordipolar.set_prefactor();

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


// bath donor position
//threevector bathpos(0.0,0.0,2000.0);
//donordonordipolar.set_lattice_vector(bathpos);
//double D = donordonordipolar.calculate(B_dir);

double D = 0.0;

//cout << "Typical coupling strength should be " << D << " M rad s-1." << endl;


//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
// CALCULATE ECHO
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

// Prepare for calculations
c0_bath = 0.0;
double c1_bath = 0.0;

cmplxd echo = cmplxd(0.0,0.0);
double t = 0.0;

int j = 0;

// Loop over sites
cout << "Generating lattice vectors ..." << endl;
int nsites = silat.generate_random_diamond_cubic(lattice_size, bath_abundance_ppm);
cout << "Generated " << nsites << " lattice vectors with average separation " << silat.get_average_lattice_vector_separation() << " A."  << endl;
cout << "Looping over " << nsites << " sites and calculating echo intensities ... " << endl;

//double scale_D = 1.0;
//double avg_D = 0.0;

//cout << "D will be scaled by " << scale_D << endl;

threevector bathpos;

for (i=0;i<nsites;i++) {

  bathpos = silat.get_lattice_vector(i);

//  bathpos = bathpos*(1.0/0.3628);
//  cout << bathpos.mod() << endl;

  donordonordipolar.set_lattice_vector(bathpos);
  D = donordonordipolar.calculate(B_dir);

//  D = D*scale_D;
//  avg_D = avg_D + D;

  if (rand_c0_bath == 1) {
    c0_bath = (double)rand()/(double)RAND_MAX;
  }
  c1_bath = sqrt(1.0 - c0_bath*c0_bath);

  dipolarH.set_zeros();
  spinHamiltonian::Dipolar(dipolarH, donors,donorsbasis,0,2,D);
  totalH = fixedH + dipolarH;
  totalH.diagonalise(diagtype);

  for (j=0;j<L_t.t_size();j++) {

    t = L_t.get_t(j);

    Uevolve = totalH.exponentiate(t);

    ibathvec = statevector ( c0_bath*sysvec0.get_col_vec() + 
                                   c1_bath*sysvec1.get_col_vec() ) ;

    isysbathvec = isysvec^ibathvec;

    if (no_pipulse == 0) {
      echo = HahnSpinEcho::calculate(Uevolve, PIpulse , isysbathvec, donor_dim, 
                                                            sysvec0, sysvec1);
    } else {
        echo = HahnSpinEcho::calculate(Uevolve, isysbathvec, donor_dim, 
                                                            sysvec0, sysvec1);
      }

    L_t.set_f(j,0, L_t.get_f(j,0)*echo);

  }

}
cout << "... done." << endl;

//cout << "Average D was " << avg_D/double(nsites) << " M rad s-1 " << endl;


//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
// FINALISE
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

cout << "Included " << nsites << " pairs." << endl;
cout << "Writing to file with first column: 2xtime in milliseconds," << endl;
cout << "second column: product Hahn echo intensity." << endl;


// start output file stream
ofstream outfile(output_file_name.c_str());

for (i=0;i<L_t.t_size();i++) {
  outfile << left << scientific << setprecision(8);
  // Convert microseconds -> seconds
  outfile << setw(32) << 2.0*L_t.get_t(i)/1.0e3;
  outfile << setw(32) << abs(L_t.get_f(i,0)) << endl;
}


cout << "Wrote results to " << output_file_name << endl;
cout << "Do $ cat " << output_file_name << endl;
cout << "'directflipflop' finished:" << endl;
system("date");

outfile.close();

return 0;

}

