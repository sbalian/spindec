// Approximates the Hahn spin echo decay of a donor in silicon due to the 
// interaction with a spin-bath of (flip-flopping) spin-1/2 nuclei.
// Uses (up to) the 3-cluster cluster correlation expansion (CCE).
//
// CCE references:
// - Phys. Rev. B 74, 035322 (2006)
// - Phys. Rev. B 78, 085315 (2008)
// - Phys. Rev. B 78, 129901(E) (2008)
// - Phys. Rev. B 79, 115320 (2009)
// - Phys. Rev. B 86, 035452 (2012)
//
// Some of the source code in is based on existing FORTRAN90 code by
// Tania Monteiro: STATIC.f90: solves for a bismuth donor in
// silicon - energy levels and transition probabilities.
//
// Created  16/11/2011 threecluster.cpp -> donornucbath.cpp
// Modified 21/09/2012, 22/09/2012, 26/09/2012, 27/09/2012, 28/09/2012,
// 30/09/2012, 01/10/2012, 02/10/2012, 03/10/2012, 04/10/2012, 05/10/2012
// 07/10/2012, 08/10/2012, 09/10/2012, 11/10/2012, 26/10/2012, 29/10/2012
// 31/10/2012, 12/11/2012, 14/11/2012, 15/11/2012, 16/11/2012 (fixed log_time
// bug), 19/11/2012, 29/11/2012
// Modified 02/12/2012 - complex echo
// Modified 03/12/2012
// Modified 11/12/2012
// Modified 10/01/2013 - cleanup, echo normalise
// Modified 11/01/2013, 15/01/2013
// Modified 17/01/2013 - cleanup, general improvements
// Modified 18/01/2013 - added abs_echo
// Modified 29/01/2013 - df/dB (temp)
// Modified 19/02/2013 - added central nucleus - 29Si interaction
//                       (2cluster only, wo 1clusters)
// Modified 21/02/2013
// Modified 22/02/2013, 25/02/2013, 26/02/2013
// Modified 18/03/2013 added include_shf_to_bath and include_dipolar_to_bath
//                     and output couplings
// Modified 20/03/2013, 24/03/2013, 08/05/2013, 14/05/2013, 16/05/2013
// Modified 17/05/2013
// Seto Balian
// V1

#include "stdincludes.hpp" // Standard includes
#include "cceincludes.hpp" // CCE includes
#include "argvparser.h" // Argument Parser: http://mih.voxindeserto.de/argvparser.html

using namespace Eigen; // Linear algebra package
using namespace std;
using namespace CommandLineProcessing;

int main(int argc, char **argv) {

// Read command line parameters
// ____________________________________________________________________________
ArgvParser cmd;

string version = "Seto Balian - 17/05/2013 - V1\n";

string introduction = "---------------------------------------------------------\n";
introduction       += "SpinDecoherence: donornucbath                            \n";
introduction       += "---------------------------------------------------------\n";
introduction       += "Calculates spin echo decay of a donor in silicon due to  \n";
introduction       += "the interaction with a spin-bath of (flip-flopping)      \n";
introduction       += "spin-1/2 nuclei. Uses (up to) the 3-cluster cluster      \n";
introduction       += "correlation expansion.                                   \n";
introduction       += "---------------------------------------------------------\n";
introduction       += "USAGE: donornucbath -i INPUTFILENAME -o OUTPUTFILENAME   \n";
introduction       += "---------------------------------------------------------\n";
//introduction       += "Option --sampleconfig to create a sample input file      \n";
introduction       += version;
introduction       += "---------------------------------------------------------\n";

cmd.setIntroductoryDescription(introduction);

cmd.addErrorCode(0, "Success");
cmd.addErrorCode(1, "Error");

cmd.setHelpOption("h", "help", "Print this help page");

cmd.defineOption("version", "Display current version and exit", ArgvParser::NoOptionAttribute);
cmd.defineOptionAlternative("version","v");

cmd.defineOption("silent", "Don't print to screen (excludes errors and warnings)", ArgvParser::NoOptionAttribute);
cmd.defineOptionAlternative("silent","s");

cmd.defineOption("input","Input file name",ArgvParser::OptionRequiresValue);
cmd.defineOptionAlternative("input","i");

cmd.defineOption("output","Output file name",ArgvParser::OptionRequiresValue);
cmd.defineOptionAlternative("output","o");

cmd.defineOption("couplings","Output file name for 2-cluster couplings",ArgvParser::OptionRequiresValue);
cmd.defineOptionAlternative("couplings","c");

cmd.defineOption("field","Magnetic field in Tesla\n(overrides value in input file)",ArgvParser::OptionRequiresValue);

cmd.defineOption("finaltime","Final time in microseconds\n(overrides value in input file)",ArgvParser::OptionRequiresValue);

//cmd.defineOption("fullbasis","Do not truncate the full central system basis\n(intensive!)",ArgvParser::NoOptionAttribute);

cmd.defineOption("plot", "Plot echo vs time\n(requires grace)", ArgvParser::NoOptionAttribute);
cmd.defineOptionAlternative("plot","p");

cmd.defineOption("orientation","Orientation angle in PRL 105, 067601 (2010) in degrees",ArgvParser::OptionRequiresValue);

cmd.defineOption("findtimescale","Automatically find decay time scale", ArgvParser::NoOptionAttribute);

int parse_result = cmd.parse(argc, argv);
if (argc == 1) {
  cout << cmd.usageDescription() << endl;
  exit(1);
}

if (parse_result != ArgvParser::NoParserError)
{
  cout << cmd.parseErrorDescription(parse_result);
  exit(1);
}

if (cmd.foundOption("version")) {
  cout << "SpinDecoherence - " << version;
  exit(1);
}

bool silent = 0;
if (cmd.foundOption("silent")) {
  silent = 1;
}


string input_file_name;
if (cmd.foundOption("input")) {
  input_file_name = cmd.optionValue("input");
} else {
    cout << "ERROR: input file required." << endl;
    exit(1);
  }

string output_file_name;
if (cmd.foundOption("output")) {
  output_file_name = cmd.optionValue("output");
} else {
    cout << "ERROR: output file name required." << endl;
    exit(1);
  }

string couplings_file_name;
if (cmd.foundOption("couplings")) {
  couplings_file_name = cmd.optionValue("couplings");
} else {
    couplings_file_name = "null";
  }

bool findtimescale = 0;
if (cmd.foundOption("findtimescale")) {
  findtimescale = 1;
} 

// ____________________________________________________________________________

int tint = 0;

if (!silent) {
cout << "donornucbath started:" << endl;
tint = system("date");
cout << "Initialising ... " << endl;
}

// ____________________________________________________________________________

// BEGIN INPUT
// ____________________________________________________________________________

if (!silent) {
cout << "  Reading input parameters ... " << endl;
}

cceread infile ( input_file_name , "donornucbath" );

// CCE order
int CCE_order = infile.get_int("CCE_order");

// Include/exclude 1-clusters
bool include_1c = infile.get_bool("include_1c");

if ((CCE_order == 1) && (include_1c == 0)) {
  cout << "ERROR: Cannot calculate the CCE to 1st order without 1-clusters!";
  cout << endl;
  return 1;
}

// Magnetic field in Tesla
double B;
if (cmd.foundOption("field")) {
  B = infile.string_to_double(cmd.optionValue("field"));
} else {
    B = infile.get_double("B");
}


// Magnetic field direction
doubleTriplet B_dir_dt = infile.get_doubleTriplet("B_dir");
threevector B_dir;
B_dir.set_x ( B_dir_dt.d_1 );
B_dir.set_y ( B_dir_dt.d_2 );
B_dir.set_z ( B_dir_dt.d_3 );

if (cmd.foundOption("orientation")) {
  B_dir.set_x ( cos( infile.string_to_double(cmd.optionValue("orientation")) *(PI/180.0)) );
  B_dir.set_y ( sin( infile.string_to_double(cmd.optionValue("orientation")) *(PI/180.0)) );
  B_dir.set_z ( sin( infile.string_to_double(cmd.optionValue("orientation")) *(PI/180.0)) );
}

// Central electron gyromagnetic ratio in M rad s-1 T-1
double gamma_e = infile.get_double("gamma_e");

// Donor electron ionization energy (IE) in eV
double eIE = infile.get_double("eIE");

// Central nucleus gyromagnetic ratio in M rad s-1 T-1
double gamma_n = infile.get_double("gamma_n");

// Central nucleus total spin quantum number
frac I = infile.get_frac ("I");

// Central donor hyperfine strength in M rad s-1
double A = infile.get_double("A");

// Donor level 0 (lower)
int level_0 = infile.get_int("level_0");

// Donor level 1 (higher)
int level_1 = infile.get_int("level_1");

// Use the full Zeeman basis without truncations?
bool full_basis = infile.get_bool("full_basis");

// Bath nuclear gyromagnetic ratio in M rad s-1 T-1
double gamma_b = infile.get_double("gamma_b");

// Abundance of spin-1/2's in the bath (ppm)
int bath_abundance_ppm = infile.get_int("bath_abundance_ppm");

// Bath spin separation cutoff in Angstroms (for including clusters)
double sep_cutoff = infile.get_double("sep_cutoff");

// Lattice size parameter (int)
int lattice_size = infile.get_int("lattice_size");

// Logarithmic time switch (base 10)
bool log_time = infile.get_bool("log_time");

// Initial evolution time
double i_time = infile.get_double("i_time");

// Final time in microseconds (up to pi-pulse)
double f_time;
if (cmd.foundOption("finaltime")) {
  f_time = infile.string_to_double(cmd.optionValue("finaltime"));
} else {
    f_time = infile.get_double("f_time");
}

// Number of time steps
int n_time = infile.get_int("n_time");

// Number of random bath spatial configurations
int nplacements = infile.get_int("nplacements");

// Seed random number generator? (using current time)
bool seed_rand = infile.get_bool("seed_rand");

// Seed value (negative uses current time)
int seed_value = infile.get_int("seed_value");

// Type of the diagonalizer
string diagtype = infile.get_string("diagtype");

// Silicon lattice constant in Angstroms
double a0 = infile.get_double("a0");

// FCC lattice parameter a in Angstroms
double fcc_a = infile.get_double("fcc_a");

// FCC lattice parameter b in Angstroms
double fcc_b = infile.get_double("fcc_b");

// Charge density for Fermi contact calculation
double eta = infile.get_double("eta");

// Output mode
string output_mode = infile.get_string("output_mode");
// stdevmean or raw (see "finalise" block below)

// report echo: real, imag, abs, cmplx
string report_echo = infile.get_string("report_echo");
if ((report_echo == "real") || (report_echo == "imag") ||
    (report_echo == "cmplx") || (report_echo == "abs") )
{} else {
  cout << "ERROR: report_echo must be \"real\",\"imag\",\"abs\" or \"cmplx\".";
  cout << " Quitting ..." << endl;
  return 1;
}

// abs_echo (bool): use the absolute echo everywhere
bool abs_echo = infile.get_bool("abs_echo");

// No pipulse
bool no_pipulse = infile.get_bool("no_pipulse");

// Ising only (don't include flip-flop parts of the donor-bath hyperfine 
// interaction)
bool Ising_only = infile.get_bool("Ising_only");

// Include superhyperfine interaction to the bath (central electron - bath
// nucleus) (bool)
bool include_shf_to_bath     = infile.get_bool("include_shf_to_bath");
// Include dipolar interaction to the bath (central nucleus - bath
// nucleus) (bool)
bool include_dipolar_to_bath     = infile.get_bool("include_dipolar_to_bath");

// Effective gyromagnetic ratio?
bool eff_gyro_ratio = infile.get_bool("eff_gyro_ratio");

// Effective gyromagnetic value
double gamma_eff = infile.get_double("gamma_eff");

// Use old lattice generator
bool old_lattice_generator = infile.get_bool("old_lattice_generator");

// Fractional bath abundance (only used if old_lattice_generator = 1)
double bath_abundance_frac = infile.get_double("bath_abundance_frac");

// Flush random number generator
bool flush_random_number_generator = infile.get_bool("flush_random_number_generator");

// ____________________________________________________________________________

// END INPUT
// ____________________________________________________________________________

// Continue initialisation ...

// ____________________________________________________________________________

// Compute the square of the maximum bath separation
double sep_cutoff_sq = pow(sep_cutoff,2.0);

// Normalise magnetic field direction
B_dir = B_dir.normalised();

// Seed random number generator rand() - uniform distribution
if (seed_rand) {
  if (seed_value < 0 ) {
    srand ( time(NULL) );
  } else {
      srand(seed_value);
    }
}
int i;
if (flush_random_number_generator) {
  for (i=0;i<100;i++) {
    tint = rand();
  }
}


// Set up spins
// ____________________________________________________________________________

if (!silent) {
cout << "  Setting up spins ..." << endl;
}

// electron spin quantum number
frac S;
S.num = 1;
S.den = 2;

// bath spin quantum number
frac I_b = S;

// Central electron and nucleus
//                          spin ID
spin celec("CentralElectron", 0, S, gamma_e);
spin cnuc ("CentralNucleus" , 1, I, gamma_n);

// Set up donor object to form subspace or get effective gyromagnetic ratio
elecNucSpin donor_analytical("AnalyticalDonor",celec,cnuc,A,B);

// TODO improve this ...
//// TEMP: df/dB out
//int q;
//double iB = 0.275;
//double fB = 0.450;
//int nB = 100000;
//double dB = (fB - iB)/double(nB);
//cout << scientific << left;
//for (q=0;q<nB;q++) {
//  donor_analytical.set_B(iB);
//  cout << setprecision(7)  << setw(25) << iB;
//  cout << setprecision(10) << setw(25) << donor_analytical.effGyromagneticRatio( level_1 , level_0) << endl;
////  cout << setprecision(10) << setw(25) << 2.0*PI/(1.0e3*iB*abs(donor_analytical.effGyromagneticRatio( level_1 , level_0))) << endl;
//  iB = iB + dB;
//}
//exit(1);


// Calculate electron effective gyromagnetic ratio
if ((eff_gyro_ratio==1) && (gamma_eff == 0.0)) {
  gamma_e = donor_analytical.effGyromagneticRatio( level_1 , level_0);
  celec.set_gyromagneticRatio( gamma_e );
}
// Use input electron effective gyromagnetic ratio
if ((eff_gyro_ratio==1) && (gamma_eff != 0.0)) {
  gamma_e = gamma_eff;
  celec.set_gyromagneticRatio( gamma_e );
}

// Bath nuclei
spin bnuc1 ("BathSpin1"  , 2, I_b, gamma_b);
spin bnuc2 ("BathSpin2"  , 3, I_b, gamma_b);
spin bnuc3 ("BathSpin3"  , 4, I_b, gamma_b);

// Collect spins into a 1-cluster, 2-cluster and 3-cluster
spins spins1c("1-clusterSpins");
spins spins2c("2-clusterSpins");
spins spins3c("3-clusterSpins");

spins1c.add(celec);
if (eff_gyro_ratio==0) { // no central nucleus if using effective gamma_e
  spins1c.add(cnuc);
}
spins1c.add(bnuc1);

spins2c.add(celec);
if (eff_gyro_ratio==0) {
  spins2c.add(cnuc);
}
spins2c.add(bnuc1);
spins2c.add(bnuc2);

spins3c.add(celec);
if (eff_gyro_ratio==0) {
  spins3c.add(cnuc);
}
spins3c.add(bnuc1);
spins3c.add(bnuc2);
spins3c.add(bnuc3);

// Print spins
if (!silent) {
switch (CCE_order)
{
  case 1:
    spins1c.print();
    break;
  case 2:
    spins2c.print();
    break;
  case 3:
    spins3c.print();
    break;
  default:
    cout << "ERROR: Can only do up to 3-rd order at the moment. Quitting ... ";
    cout << endl;
    return 1;
}
}

// ____________________________________________________________________________

// Bases
// ____________________________________________________________________________

if (!silent) {
cout << "  Setting up bases ..." << endl;
}

// Get subspace magnetic quantum numbers
MatrixXd donor_mQNs;
if (eff_gyro_ratio==0) {
 donor_mQNs = donor_analytical.get_high_field_basis(level_0,level_1);
// donor_mQNs = donor_analytical.get_high_field_basis(level_0,level_1,Ising_only);
}

// Set up basis for the combined system (bath + donor (qubit) system)
// (basis of eigenstates of the z-component spin operators
// or high-field energy eigenstates)
spins1c.build_high_field_basis();
spins2c.build_high_field_basis();
spins3c.build_high_field_basis();
// Truncate bases
if (eff_gyro_ratio==0) {
  if (full_basis == 0) { // don't truncate if full basis requested
    spins1c.truncate_high_field_basis_by_2_spins(0,1,donor_mQNs);
    spins2c.truncate_high_field_basis_by_2_spins(0,1,donor_mQNs);
    spins3c.truncate_high_field_basis_by_2_spins(0,1,donor_mQNs);
  }
}
// Save bases
MatrixXd basis1c = spins1c.get_high_field_basis();
MatrixXd basis2c = spins2c.get_high_field_basis();
MatrixXd basis3c = spins3c.get_high_field_basis();

// Print
if (!silent) {
cout << "  High-field basis (";
switch (CCE_order)
{
  case 1:
    cout << "1-cluster):" << endl;
    cout << basis1c << endl;
    cout << endl;
    break;
  case 2:
    cout << "2-cluster):" << endl;
    cout << basis2c << endl;
    cout << endl;
    break;
  case 3:
    cout << "3-cluster):" << endl;
    cout << basis3c << endl;
    cout << endl;
    break;
  default:
    cout << "ERROR: Can only do up to 3-rd order at the moment. Quitting ... ";
    cout << endl;
    return 1;
}
}

// ____________________________________________________________________________

// Solve for the donor
// ____________________________________________________________________________

if (!silent) {
cout << "  Solving for the donor ... " << endl;
}

// Collect donor electron and nuclear spins
spins donor("DonorSpins");
donor.add(celec);
if (eff_gyro_ratio==0) {
  donor.add(cnuc);
}
// Build basis
donor.build_high_field_basis();
if (eff_gyro_ratio==0) {
  if (full_basis == 0) {
    donor.truncate_high_field_basis_by_2_spins(0,1,donor_mQNs);
  }
}
// Save basis
MatrixXd basisDonor = donor.get_high_field_basis();

// Get the donor dimension
int donor_dim = donor.dimension();

if (full_basis == 1) {
  donor_dim = donor.dimension();
}

if (eff_gyro_ratio!=0) {
  donor_dim = celec.get_multiplicity();
}

// Set up donor Hamiltonian
qoperator donorH(donor_dim);

// Zeeman
spinHamiltonian::Zeeman(donorH, donor, basisDonor, B);
// Donor hyperfine
if (eff_gyro_ratio==0) {
  spinHamiltonian::IsoHyperfine(donorH, donor, basisDonor,0,1,A);
}
donorH.diagonalise(diagtype);

// Get donor levels for subspace
ArrayXi donor_levels, nLabels;
nLabels = donor_analytical.nLabels();
int nLabels_size = nLabels.rows();

if (eff_gyro_ratio==0) {
  if (full_basis == 0) {
    donor_levels = donor_analytical.subspace_nLabels(level_0, level_1);
  } else {
      donor_levels = nLabels;
  }
} else {
    donor_levels = ArrayXi(2);
    donor_levels(0) = level_0;
    donor_levels(1) = level_1;
}

// Check if donor levels within bounds
bool level_bounds_ok = 0;
for (i=0;i<nLabels_size;i++) {
  if (level_0 == nLabels(i)) {
    level_bounds_ok = 1;
  }
}
if (level_bounds_ok == 0) {
  cout << "ERROR: level_0 must be between " << nLabels(0) << " and ";
  cout << nLabels(nLabels_size-1) << ". Quitting ..." << endl;
  return 1;
}

level_bounds_ok = 0;
for (i=0;i<nLabels_size;i++) {
  if (level_1 == nLabels(i)) {
    level_bounds_ok = 1;
  }
}
if (level_bounds_ok == 0) {
  cout << "ERROR: level_1 must be between " << nLabels(0) << " and ";
  cout << nLabels(nLabels_size-1) << ". Quitting ..." << endl;
  return 1;
}

// Set up initial donor state ...
statevector sysvec0, sysvec1;

sysvec0 = statevector(
                      donorH.get_eigenvector(donor_levels, level_0));
sysvec1 = statevector(
                      donorH.get_eigenvector(donor_levels, level_1));
statevector isysvec ( sysvec0.get_col_vec() + 
                                   sysvec1.get_col_vec() ) ;
isysvec = isysvec.normalised();


// The other statevectors in the two subspaces
vector<statevector> other_sysvecs;
for (i=0;i<donor_levels.rows();i++) {
  if ( donor_levels(i) == level_0 ) {continue;}
  if ( donor_levels(i) == level_1 ) {continue;}
  other_sysvecs.push_back(
        statevector(donorH.get_eigenvector(donor_levels, donor_levels(i))));
}

// ____________________________________________________________________________

// pi-pulse
// ____________________________________________________________________________

if (no_pipulse == 0) {
if (!silent) {
  cout << "  Setting up the pi-pulse ... " << endl;
}
}

// bath identities
qoperator bathI1c = qoperator::Identity(2);
qoperator bathI2c = qoperator::Identity(4);
qoperator bathI3c = qoperator::Identity(8);

// projection operators (system only)
qoperator sysvec0sysvec1(sysvec0,sysvec1);
qoperator sysvec1sysvec0(sysvec1,sysvec0);

qoperator sysPIpulse = sysvec0sysvec1 + sysvec1sysvec0;
for (i=0;i<static_cast<int>(other_sysvecs.size());i++) {
  sysPIpulse = sysPIpulse + qoperator(other_sysvecs[i],other_sysvecs[i]);
                            // add |m><m| for the other statevectors in the
                            // subspaces
}

// No pi-pulse
if (no_pipulse == 1) {
  sysPIpulse = qoperator::Identity(donor_dim); // set sysPIpulse to identity
}

// construct pi-pulse system X bath identity
qoperator PIpulse1c = sysPIpulse^bathI1c;
qoperator PIpulse2c = sysPIpulse^bathI2c;
qoperator PIpulse3c = sysPIpulse^bathI3c;

// ____________________________________________________________________________

// Prepare Hamiltonians
// ____________________________________________________________________________

if (!silent) {
cout << "  Preparing Hamiltonians ... " << endl;
}

// "fixed" Hamiltonians
qoperator f1cH(spins1c.dimension());
qoperator f2cH(spins2c.dimension());
qoperator f3cH(spins3c.dimension());

// Zeeman
spinHamiltonian::Zeeman(f1cH, spins1c,basis1c,B);
spinHamiltonian::Zeeman(f2cH, spins2c,basis2c,B);
spinHamiltonian::Zeeman(f3cH, spins3c,basis3c,B);
// Donor hyperfine
if (eff_gyro_ratio==0) {
  spinHamiltonian::IsoHyperfine(f1cH,spins1c,basis1c,0,1,A);
  spinHamiltonian::IsoHyperfine(f2cH,spins2c,basis2c,0,1,A);
  spinHamiltonian::IsoHyperfine(f3cH,spins3c,basis3c,0,1,A);
}

// Superhyperfine Hamiltonians
qoperator shf1cH(spins1c.dimension());
qoperator shf2cH(spins2c.dimension());
qoperator shf3cH(spins3c.dimension());

// Dipolar Hamiltonians
qoperator dipolar2cH(spins2c.dimension());
qoperator dipolar3cH(spins3c.dimension());

// Total Hamiltonians
qoperator total1cH(spins1c.dimension());
qoperator total2cH(spins2c.dimension());
qoperator total3cH(spins3c.dimension());

qoperator total1cH_j(spins1c.dimension());
qoperator total1cH_k(spins1c.dimension());
qoperator total1cH_l(spins1c.dimension());

qoperator total2cH_jk(spins2c.dimension());
qoperator total2cH_kl(spins2c.dimension());
qoperator total2cH_lj(spins2c.dimension());

// ____________________________________________________________________________

// Prepare bath states
// ____________________________________________________________________________
if (!silent) {
cout << "  Preparing initial bath states ... " << endl;
}

// spin up, spin down
statevector bath_u(2);
statevector bath_d(2);
bath_u.set_comp(0,cmplxd(0.0,0.0));
bath_u.set_comp(1,cmplxd(1.0,0.0));
bath_d.set_comp(0,cmplxd(1.0,0.0));
bath_d.set_comp(1,cmplxd(0.0,0.0));

statevector sysbath_u = isysvec^bath_u;
statevector sysbath_d = isysvec^bath_d;

// 2 spin 1/2s
statevector bath_uu = bath_u^bath_u;
statevector bath_dd = bath_d^bath_d;
statevector bath_ud = bath_u^bath_d;
statevector bath_du = bath_d^bath_u;

statevector sysbath_uu = isysvec^bath_uu;
statevector sysbath_dd = isysvec^bath_dd;
statevector sysbath_ud = isysvec^bath_ud;
statevector sysbath_du = isysvec^bath_du;

// 3 spin 1/2s
statevector bath_uuu = bath_uu^bath_u;
statevector bath_ddd = bath_dd^bath_d;

statevector bath_ddu = bath_dd^bath_u;
statevector bath_dud = bath_du^bath_d;
statevector bath_udd = bath_ud^bath_d;

statevector bath_uud = bath_uu^bath_d;
statevector bath_udu = bath_ud^bath_u;
statevector bath_duu = bath_du^bath_u;

statevector sysbath_uuu = isysvec^bath_uuu;
statevector sysbath_ddd = isysvec^bath_ddd;

statevector sysbath_ddu = isysvec^bath_ddu;
statevector sysbath_dud = isysvec^bath_dud;
statevector sysbath_udd = isysvec^bath_udd;

statevector sysbath_uud = isysvec^bath_uud;
statevector sysbath_udu = isysvec^bath_udu;
statevector sysbath_duu = isysvec^bath_duu;

// ____________________________________________________________________________

// Prepare lattice
// ____________________________________________________________________________

if (!silent) {
cout << "  Preparing lattice ..." << endl;
}

// Lattice vectors
lattice silat("SiliconLattice", a0);

if (old_lattice_generator) {
  silat.old_generate_diamond_cubic(lattice_size);
}

// ____________________________________________________________________________

// Prepare couplings
// ____________________________________________________________________________

if (!silent) {
cout << "  Preparing Fermi contact and dipolar couplings ..." << endl;
}

KohnLuttingerContact fermic1("FermiContact1", 
  threevector(0.0,0.0,0.0),
  gamma_e, gamma_b, a0,
  fcc_a, fcc_b, eIE, eta);

KohnLuttingerContact fermic2("FermiContact2", 
  threevector(0.0,0.0,0.0),
  gamma_e, gamma_b, a0,
  fcc_a, fcc_b, eIE, eta);

KohnLuttingerContact fermic3("FermiContact3", 
  threevector(0.0,0.0,0.0),
  gamma_e, gamma_b, a0,
  fcc_a, fcc_b, eIE, eta);


dipolar dipolar1("Dipolar1",
                              threevector(0.0,0.0,0.0) ,
                              gamma_n);
dipolar1.set_gyromagneticRatio_1(gamma_n);
dipolar1.set_gyromagneticRatio_2(gamma_b);

dipolar dipolar2("Dipolar2", 
                              threevector(0.0,0.0,0.0) ,
                              gamma_n);
dipolar2.set_gyromagneticRatio_1(gamma_n);
dipolar2.set_gyromagneticRatio_2(gamma_b);

dipolar dipolar3("Dipolar3", 
                              threevector(0.0,0.0,0.0) ,
                              gamma_n);
dipolar3.set_gyromagneticRatio_1(gamma_n);
dipolar3.set_gyromagneticRatio_2(gamma_b);


dipolar bathdipolar("BathDipolar",
                              threevector(0.0,0.0,0.0) ,
                              gamma_b);


// calculate prefactors
fermic1.set_prefactor();
fermic2.set_prefactor();
fermic3.set_prefactor();

dipolar1.set_prefactor();
dipolar2.set_prefactor();
dipolar3.set_prefactor();

bathdipolar.set_prefactor();


// ____________________________________________________________________________

// Final preloop declarations
// ____________________________________________________________________________

if (!silent) {
cout << "  Final preparations ..." << endl;
}

// Preloop declarations

// Unitary evolution operators
qoperator U1c, U2c, U3c;
qoperator U1c_j, U1c_k, U1c_l;
qoperator U2c_jk, U2c_kl, U2c_lj;

// threevectors
threevector j_3vec, k_3vec, l_3vec;

// echos
cmplxd echo1c, echo1c_j, echo1c_k, echo1c_l;
cmplxd echo2c, echo2c_jk, echo2c_kl, echo2c_lj;
cmplxd echo3c;

// normalisations
cmplxd norm1c, norm1c_j, norm1c_k, norm1c_l;
cmplxd norm2c, norm2c_jk, norm2c_kl, norm2c_lj;
cmplxd norm3c;

// Loop variables
int j, k, l, m;

// Shift spin ID's for eff_gyro_ratio==1 mode
int IDshift = 0;
if (eff_gyro_ratio==1) {
  IDshift = -1;
}

// number of bath spins / placement
int nsites = 0;

bool no_clusters_found = 1;

// Output file stream
// start output file stream
ofstream outfile;

ofstream couplingsfile;

// Find time scale

double initial_finaltime = 0.5e2;
double increase_timescale = 10;

double echo_threshold = 0.01;

double timescale = initial_finaltime;

int iterations = 0;

cmplxd echo2c_timescale = cmplxd(1.0,0.0);

if (findtimescale == 1) {

if (log_time == 1) {
  cout << "ERROR: Cannot look for time scale if log_time = 1. Quitting ..." << endl;;
  return 1;
}

if (!silent) {
cout << "Finding time scale of decoherence ... " << endl;
}

while (1) {
  iterations += 1;

  echo2c_timescale = cmplxd(1.0,0.0);
  if (old_lattice_generator) {
    silat.set_lattice_vectors( silat.get_random_lattice_vectors(bath_abundance_frac) );
    nsites = silat.get_lattice_vectors_size();
  } else {
      nsites = silat.generate_random_diamond_cubic(lattice_size,
                                             bath_abundance_ppm);
  }

  // Loop over sites
  for (j=0;j<nsites;j++) {

    j_3vec = silat.get_lattice_vector(j);

    k = 0;
    while (k<j) { // Loop over sites to pair spins, pairing the same pair once
      
      k_3vec = silat.get_lattice_vector(k);
      
      // 2-CLUSTER HEURISTICS
      if ( cluster_heuristics::heuristics_2cluster(j_3vec,k_3vec,sep_cutoff_sq) == 0 ) {
        k = k+1;
        continue;
      }

      no_clusters_found = 0;

      fermic1.set_lattice_vector( j_3vec );
      dipolar1.set_lattice_vector( j_3vec );

      fermic2.set_lattice_vector( k_3vec );
      dipolar2.set_lattice_vector( k_3vec );

      shf2cH.set_zeros();

      
      spinHamiltonian::IsoHyperfine(shf2cH,spins2c, basis2c, 0, 2, fermic1.calculate(),Ising_only);
      spinHamiltonian::IsoHyperfine(shf2cH,spins2c, basis2c, 0, 3, fermic2.calculate(),Ising_only);

      bathdipolar.set_lattice_vector(k_3vec - j_3vec);

      dipolar2cH.set_zeros();
      spinHamiltonian::Dipolar(dipolar2cH, spins2c,basis2c,2,3, bathdipolar.calculate(B_dir));

      total2cH = f2cH + dipolar2cH + shf2cH;
      total2cH.diagonalise(diagtype);

      U2c = total2cH.exponentiate(0.0);
      U1c_j = total1cH_j.exponentiate(0.0);
      U1c_k = total1cH_k.exponentiate(0.0);
      norm2c   = HahnSpinEcho::calculate(cmplxd(1.0,0.0),U2c,   PIpulse2c, sysbath_uu, 4, sysvec0, sysvec1);
      norm1c_j = HahnSpinEcho::calculate(cmplxd(1.0,0.0),U1c_j, PIpulse1c, sysbath_u, 2, sysvec0, sysvec1);
      norm1c_k = HahnSpinEcho::calculate(cmplxd(1.0,0.0),U1c_k, PIpulse1c, sysbath_u, 2, sysvec0, sysvec1);
        
      U2c = total2cH.exponentiate( timescale );

      // UP UP
      echo2c = HahnSpinEcho::calculate(norm2c,U2c, PIpulse2c, sysbath_uu, 4, sysvec0, sysvec1, abs_echo);

      // DOWN DOWN
      echo2c += HahnSpinEcho::calculate(norm2c,U2c, PIpulse2c, sysbath_dd, 4, sysvec0, sysvec1, abs_echo);

      // UP DOWN
      echo2c += HahnSpinEcho::calculate(norm2c,U2c, PIpulse2c, sysbath_ud, 4, sysvec0, sysvec1, abs_echo);

      // DOWN UP
      echo2c += HahnSpinEcho::calculate(norm2c,U2c, PIpulse2c, sysbath_du, 4, sysvec0, sysvec1, abs_echo);
      
      echo2c /= cmplxd(4.0,0.0);

      echo2c_timescale *= echo2c;

      k = k + 1;

    }


  } 

  srand(seed_value);

  if (abs(echo2c_timescale) <= echo_threshold) {
    break;
  }

  timescale *= increase_timescale;

  if (timescale >= 1.0e8){
    cout << "ERROR: Timescale not found. Quitting ..." << endl;
    return 0; // NOTE TODO Handle these error codes properly. Are bash scripts affected?
  }

}
}

if (findtimescale == 1) {
  f_time = timescale;
if (!silent) {
  cout << "Final time set to " << f_time << " microseconds after " << fixed << iterations << " iteration(s)." << endl;
}
}


// ____________________________________________________________________________

// L(t) holders - L: spin echo intensity. t: time.
// ____________________________________________________________________________

ft L_t_1c(i_time,f_time,n_time,log_time,1);
ft L_t_2c(i_time,f_time,n_time,log_time,1);
ft L_t_3c(i_time,f_time,n_time,log_time,1);

ft L_t_combined(i_time,f_time,n_time,log_time,3);

ft L_t_1c2c3c_product(i_time,f_time,n_time,log_time,1);

// Output spin echo
ft L_t_out(i_time,f_time,n_time,log_time,0);

// Mean and standard deviation on the mean over placements
ft L_t_mean_f;
ft L_t_stdev_mean_f;

// ____________________________________________________________________________

// ____________________________________________________________________________

// CALCULATE THE CCE (UP TO K=3)
// ____________________________________________________________________________

if (!silent) {
tint = system("clear"); // clear the screen
cout << "---------------^^^^^ Scroll up for more ^^^^^-----------------------";
cout << endl;
cout << "Input : " << input_file_name << endl;
cout << "Output: " << output_file_name << endl;
}

// print calculation details
if (!silent) {
switch (CCE_order)
{
  case 1:
    cout << "Calculating CCE(k=1) ... " << endl;
    break;
  case 2:
    if (include_1c == 1) {
      cout << "Calculating CCE(k=2) ... " << endl;
    } else {
        cout << "Calculating CCE(k=2) (excluding 1-clusters) ... " << endl;
      }
    break;
  case 3:
    if (include_1c == 1) {
      cout << "Calculating CCE(k=3) ... " << endl;
    } else {
        cout << "Calculating CCE(k=3) (excluding 1-clusters) ... " << endl;
      }
    break;
  default:
    cout << "ERROR: Can only do up to 3-rd order at the moment. Quitting ...";
    cout << endl;
    return 1;
}
}

if (couplings_file_name != "null") {
  couplingsfile.open(couplings_file_name.c_str());
}



 // LOOP OVER PLACEMENTS
for (i=0;i<nplacements;i++) {

  no_clusters_found = 1;

  // Get random lattice vectors
if (!silent) {
  tint = system("tput cup 4 0");
  cout << "Bath " << i+1 << " / " << nplacements << "...         " << endl;
  tint = system("tput cup 5 0");
  cout << "Generating lattice ... " << endl;
}

  if (old_lattice_generator) {
    silat.set_lattice_vectors( silat.get_random_lattice_vectors(bath_abundance_frac) );
    nsites = silat.get_lattice_vectors_size();
  } else {
      nsites = silat.generate_random_diamond_cubic(lattice_size,
                                             bath_abundance_ppm);
  }

if (!silent) {
  tint = system("tput cup 5 0");
  cout << "Iterating over " << nsites << " sites ...                 " << endl;
}

  // 1-CLUSTER
  L_t_1c.set_f_ones();

  if (include_1c == 1) {
    // Loop over sites
    for (j=0;j<nsites;j++) {

      no_clusters_found = 0;

      j_3vec = silat.get_lattice_vector(j);

      fermic1.set_lattice_vector(j_3vec);
      dipolar1.set_lattice_vector(j_3vec);

      shf1cH.set_zeros();

      if (include_shf_to_bath == 1) {
        spinHamiltonian::IsoHyperfine(shf1cH, spins1c, basis1c, 0, 2 + IDshift, fermic1.calculate(B_dir),Ising_only);
      }

      if ((include_dipolar_to_bath == 1) && (eff_gyro_ratio == 0)) {
        spinHamiltonian::Dipolar(shf1cH, spins1c, basis1c, 1, 2 + IDshift, dipolar1.calculate(B_dir),Ising_only);
      }

      total1cH = f1cH + shf1cH;
      total1cH.diagonalise(diagtype);
      
      // Loop over time
      U1c  = total1cH.exponentiate(0.0);
      norm1c = HahnSpinEcho::calculate(cmplxd(1.0,0.0),U1c, PIpulse1c, sysbath_u, 2, sysvec0, sysvec1);
      for (k=0;k<L_t_1c.t_size();k++) {
        U1c = total1cH.exponentiate(L_t_1c.get_t(k));
        
        echo1c  = HahnSpinEcho::calculate(norm1c,U1c, PIpulse1c, sysbath_u, 2, sysvec0, sysvec1, abs_echo);
        echo1c += HahnSpinEcho::calculate(norm1c,U1c, PIpulse1c, sysbath_d, 2, sysvec0, sysvec1, abs_echo);

        echo1c /= cmplxd(2.0,0.0);

        L_t_1c.set_f ( k , 0 , L_t_1c.get_f ( k,0 )*echo1c  );
        
      }
      

    }

  }
  

  // 2-CLUSTER
  L_t_2c.set_f_ones();

  if ((CCE_order == 2) || (CCE_order == 3)) {
    
    // Loop over sites
    for (j=0;j<nsites;j++) {

      j_3vec = silat.get_lattice_vector(j);

      k = 0;
      while (k<j) { // Loop over sites to pair spins, pairing the same pair once
        
        k_3vec = silat.get_lattice_vector(k);
        
        // 2-CLUSTER HEURISTICS
        if ( cluster_heuristics::heuristics_2cluster(j_3vec,k_3vec,sep_cutoff_sq) == 0 ) {
         k = k+1;
         continue;
        }

        no_clusters_found = 0;

        fermic1.set_lattice_vector( j_3vec );
        dipolar1.set_lattice_vector( j_3vec );

        fermic2.set_lattice_vector( k_3vec );
        dipolar2.set_lattice_vector( k_3vec );

        shf2cH.set_zeros();
        
        if (include_shf_to_bath == 1) {
          if (include_1c == 1) {
            spinHamiltonian::IsoHyperfine(shf2cH,spins2c, basis2c, 0, 2 + IDshift, fermic1.calculate(B_dir),Ising_only);
            spinHamiltonian::IsoHyperfine(shf2cH,spins2c, basis2c, 0, 3 + IDshift, fermic2.calculate(B_dir),Ising_only);
          } else {
              spinHamiltonian::IsoHyperfine(shf2cH,spins2c, basis2c, 0, 2 + IDshift, fermic1.calculate(),Ising_only);
              spinHamiltonian::IsoHyperfine(shf2cH,spins2c, basis2c, 0, 3 + IDshift, fermic2.calculate(),Ising_only);
            }
        }

        if ((include_dipolar_to_bath == 1) && (eff_gyro_ratio == 0)) {
          spinHamiltonian::Dipolar(shf2cH,spins2c, basis2c, 1, 2 + IDshift, dipolar1.calculate(B_dir),Ising_only);
          spinHamiltonian::Dipolar(shf2cH,spins2c, basis2c, 1, 3 + IDshift, dipolar2.calculate(B_dir),Ising_only);
        }

        bathdipolar.set_lattice_vector(k_3vec - j_3vec);

        dipolar2cH.set_zeros();
        spinHamiltonian::Dipolar(dipolar2cH, spins2c,basis2c,2 + IDshift,3 + IDshift,bathdipolar.calculate(B_dir));

        if ((CCE_order == 2) && (couplings_file_name != "null")) {
          couplingsfile << scientific << setprecision(8) << left;
          if (include_shf_to_bath == 1) {
            if (include_1c == 1) {
              couplingsfile << setw(23) << fermic1.calculate(B_dir);
              couplingsfile << setw(23) << fermic2.calculate(B_dir);
            } else {
                couplingsfile << setw(23) << fermic1.calculate();
                couplingsfile << setw(23) << fermic2.calculate();
              }
          }
          if (include_dipolar_to_bath == 1) {
            couplingsfile << setw(23) << dipolar1.calculate(B_dir);
            couplingsfile << setw(23) << dipolar2.calculate(B_dir);
          }
          couplingsfile << setw(23) << bathdipolar.calculate(B_dir);
          couplingsfile << endl;
        }

        total2cH = f2cH + dipolar2cH + shf2cH;
        total2cH.diagonalise(diagtype);

        if (include_1c == 1) {
          // 1-cluster for 2-clusters
          shf1cH.set_zeros();
          if (include_shf_to_bath == 1) {
            spinHamiltonian::IsoHyperfine(shf1cH,spins1c, basis1c, 0, 2 + IDshift, fermic1.calculate(B_dir),Ising_only);
          }
          if ((include_dipolar_to_bath == 1) && (eff_gyro_ratio == 0)) {
            spinHamiltonian::Dipolar(shf1cH,spins1c, basis1c, 1, 2 + IDshift, dipolar1.calculate(B_dir),Ising_only);
          }
          
          total1cH_j = f1cH + shf1cH;
          total1cH_j.diagonalise(diagtype);

          shf1cH.set_zeros();
          if (include_shf_to_bath == 1) {
            spinHamiltonian::IsoHyperfine(shf1cH,spins1c, basis1c, 0, 2 + IDshift, fermic2.calculate(B_dir),Ising_only);
          }
          if ( (include_dipolar_to_bath == 1) && (eff_gyro_ratio == 0) ) {
            spinHamiltonian::Dipolar(shf1cH,spins1c, basis1c, 1, 2 + IDshift, dipolar2.calculate(B_dir),Ising_only);
          }
          total1cH_k = f1cH + shf1cH;
          total1cH_k.diagonalise(diagtype);
        }

// !#####################################################################################################
// TODO WHY IS THIS NOT WORKING????
//        if (norm2c != test_complex) {
//          cout << setprecision(12) << scientific << test_complex << "\t" << norm2c << " HHHHHH" << endl;
//          exit(1);
//        }
// !#####################################################################################################

        // Loop over time
        U2c = total2cH.exponentiate(0.0);
        U1c_j = total1cH_j.exponentiate(0.0);
        U1c_k = total1cH_k.exponentiate(0.0);
        norm2c   = HahnSpinEcho::calculate(cmplxd(1.0,0.0),U2c,   PIpulse2c, sysbath_uu, 4, sysvec0, sysvec1);
        norm1c_j = HahnSpinEcho::calculate(cmplxd(1.0,0.0),U1c_j, PIpulse1c, sysbath_u, 2, sysvec0, sysvec1);
        norm1c_k = HahnSpinEcho::calculate(cmplxd(1.0,0.0),U1c_k, PIpulse1c, sysbath_u, 2, sysvec0, sysvec1);

        for (l=0;l<L_t_2c.t_size();l++) {
          
          U2c = total2cH.exponentiate(L_t_2c.get_t(l) );
          if (include_1c == 1) {
            U1c_j = total1cH_j.exponentiate(L_t_2c.get_t(l) );
            U1c_k = total1cH_k.exponentiate(L_t_2c.get_t(l) );
          }

          // UP UP
          if (include_1c == 1) {
            echo1c_j = HahnSpinEcho::calculate(norm1c_j,U1c_j, PIpulse1c, sysbath_u, 2, sysvec0, sysvec1, abs_echo);
            echo1c_k = HahnSpinEcho::calculate(norm1c_k,U1c_k, PIpulse1c, sysbath_u, 2, sysvec0, sysvec1, abs_echo);
          } else {
              echo1c_j = cmplxd(1.0,0.0);
              echo1c_k = cmplxd(1.0,0.0);
            }
          echo2c = HahnSpinEcho::calculate(norm2c,U2c, PIpulse2c, sysbath_uu, 4, sysvec0, sysvec1, abs_echo)/(echo1c_j*echo1c_k);


          // DOWN DOWN
          if (include_1c == 1) {
            echo1c_j = HahnSpinEcho::calculate(norm1c_j,U1c_j, PIpulse1c, sysbath_d, 2, sysvec0, sysvec1, abs_echo);
            echo1c_k = HahnSpinEcho::calculate(norm1c_k,U1c_k, PIpulse1c, sysbath_d, 2, sysvec0, sysvec1, abs_echo);
          } else {
              echo1c_j = cmplxd(1.0,0.0);
              echo1c_k = cmplxd(1.0,0.0);
            }
          echo2c += HahnSpinEcho::calculate(norm2c,U2c, PIpulse2c, sysbath_dd, 4, sysvec0, sysvec1, abs_echo)/(echo1c_j*echo1c_k);

          // UP DOWN
          if (include_1c == 1) {
            echo1c_j = HahnSpinEcho::calculate(norm1c_j,U1c_j, PIpulse1c, sysbath_u, 2, sysvec0, sysvec1, abs_echo);
            echo1c_k = HahnSpinEcho::calculate(norm1c_k,U1c_k, PIpulse1c, sysbath_d, 2, sysvec0, sysvec1, abs_echo);
          } else {
              echo1c_j = cmplxd(1.0,0.0);
              echo1c_k = cmplxd(1.0,0.0);
            }
          echo2c += HahnSpinEcho::calculate(norm2c,U2c, PIpulse2c, sysbath_ud, 4, sysvec0, sysvec1, abs_echo)/(echo1c_j*echo1c_k);

          // DOWN UP
          if (include_1c == 1) {
            echo1c_j = HahnSpinEcho::calculate(norm1c_j,U1c_j, PIpulse1c, sysbath_d, 2, sysvec0, sysvec1, abs_echo);
            echo1c_k = HahnSpinEcho::calculate(norm1c_k,U1c_k, PIpulse1c, sysbath_u, 2, sysvec0, sysvec1, abs_echo);
          } else {
              echo1c_j = cmplxd(1.0,0.0);
              echo1c_k = cmplxd(1.0,0.0);
            }
          echo2c += HahnSpinEcho::calculate(norm2c,U2c, PIpulse2c, sysbath_du, 4, sysvec0, sysvec1, abs_echo)/(echo1c_j*echo1c_k);
         
          echo2c /= cmplxd(4.0,0.0);

          L_t_2c.set_f(l,0,L_t_2c.get_f(l,0)*echo2c);

        }

        k = k + 1;

      }


    }



  }

  // 3-CLUSTER

  L_t_3c.set_f_ones();

  
  if (CCE_order == 3) {

    // Loop over sites
    for (j=0;j<nsites;j++) {
      
      j_3vec = silat.get_lattice_vector(j);

      k = 0;
      while (k<j) {
        
        k_3vec = silat.get_lattice_vector(k);

        // 3-CLUSTER HEURISTICS
        if ( cluster_heuristics::heuristics_2cluster(j_3vec,k_3vec,sep_cutoff_sq) == 0) {
          k = k + 1;
          continue;
        }
        
        l = 0;
        while (l<k) {
          
          l_3vec = silat.get_lattice_vector( l );
          
          // 3-CLUSTER HEURISTICS
          if ( cluster_heuristics::heuristics_3cluster(j_3vec,k_3vec,l_3vec,sep_cutoff_sq) == 0) {
            l = l + 1;
            continue;
          }

          no_clusters_found = 0;
          
          // Calculate L_jk, L_kl, L_lj (2-cluster)
          // j -> bath spin ID 2
          // k -> bath spin ID 3
          // l -> bath spin ID 4
          // together with 1-clusters

          if (include_1c == 1) {
            // j
            fermic1.set_lattice_vector(j_3vec);
            dipolar1.set_lattice_vector(j_3vec);
            shf1cH.set_zeros();
            if (include_shf_to_bath == 1) {
              spinHamiltonian::IsoHyperfine(shf1cH, spins1c, basis1c, 0, 2 + IDshift, fermic1.calculate(B_dir),Ising_only);
            }
            if ( (include_dipolar_to_bath == 1) && (eff_gyro_ratio == 0) ) {
              spinHamiltonian::Dipolar(shf1cH, spins1c, basis1c, 1, 2 + IDshift, dipolar1.calculate(B_dir),Ising_only);
            }
            total1cH_j = f1cH + shf1cH;
            total1cH_j.diagonalise(diagtype);

            // k
            fermic1.set_lattice_vector(k_3vec);
            dipolar1.set_lattice_vector(k_3vec);
            shf1cH.set_zeros();
            if (include_shf_to_bath == 1) {
              spinHamiltonian::IsoHyperfine(shf1cH, spins1c, basis1c, 0, 2 + IDshift, fermic1.calculate(B_dir),Ising_only);
            }
            if ( (include_dipolar_to_bath == 1) && (eff_gyro_ratio == 0) ) {
              spinHamiltonian::Dipolar(shf1cH, spins1c, basis1c, 1, 2 + IDshift, dipolar1.calculate(B_dir),Ising_only);
            }
            total1cH_k = f1cH + shf1cH;
            total1cH_k.diagonalise(diagtype);

            // l
            fermic1.set_lattice_vector(l_3vec);
            dipolar1.set_lattice_vector(l_3vec);
            shf1cH.set_zeros();
            if (include_shf_to_bath == 1) {
              spinHamiltonian::IsoHyperfine(shf1cH, spins1c, basis1c, 0, 2 + IDshift, fermic1.calculate(B_dir),Ising_only);
            }
            if ( (include_dipolar_to_bath == 1) && (eff_gyro_ratio == 0) ) {
              spinHamiltonian::Dipolar(shf1cH, spins1c, basis1c, 1, 2 + IDshift, dipolar1.calculate(B_dir),Ising_only);
            }
            total1cH_l = f1cH + shf1cH;
            total1cH_l.diagonalise(diagtype);
          }


          // jk
          fermic1.set_lattice_vector( j_3vec );
          fermic2.set_lattice_vector( k_3vec );

          dipolar1.set_lattice_vector( j_3vec );
          dipolar2.set_lattice_vector( k_3vec );

          shf2cH.set_zeros();
          if (include_shf_to_bath == 1) {
            if (include_1c == 1) {
              spinHamiltonian::IsoHyperfine(shf2cH, spins2c, basis2c, 0, 2 + IDshift, fermic1.calculate(B_dir),Ising_only);
              spinHamiltonian::IsoHyperfine(shf2cH, spins2c, basis2c, 0, 3 + IDshift, fermic2.calculate(B_dir),Ising_only);
            } else {
                spinHamiltonian::IsoHyperfine(shf2cH, spins2c, basis2c, 0, 2 + IDshift, fermic1.calculate(),Ising_only);
                spinHamiltonian::IsoHyperfine(shf2cH, spins2c, basis2c, 0, 3 + IDshift, fermic2.calculate(),Ising_only);
              }
          }

          if ((include_dipolar_to_bath == 1) && (eff_gyro_ratio == 0)) {
            spinHamiltonian::Dipolar(shf2cH, spins2c, basis2c, 1, 2 + IDshift, dipolar1.calculate(B_dir),Ising_only);
            spinHamiltonian::Dipolar(shf2cH, spins2c, basis2c, 1, 3 + IDshift, dipolar2.calculate(B_dir),Ising_only);
          }

          bathdipolar.set_lattice_vector(k_3vec - j_3vec);

          dipolar2cH.set_zeros();
          spinHamiltonian::Dipolar(dipolar2cH,spins2c,basis2c,3 + IDshift,2 + IDshift,bathdipolar.calculate(B_dir));

          total2cH_jk = f2cH + shf2cH + dipolar2cH;
          total2cH_jk.diagonalise(diagtype);


          // kl
          fermic1.set_lattice_vector( k_3vec );
          fermic2.set_lattice_vector( l_3vec );

          dipolar1.set_lattice_vector( k_3vec );
          dipolar2.set_lattice_vector( l_3vec );

          shf2cH.set_zeros();
          if (include_shf_to_bath == 1) {
            if (include_1c == 1) {
              spinHamiltonian::IsoHyperfine(shf2cH, spins2c, basis2c, 0, 2 + IDshift, fermic1.calculate(B_dir),Ising_only);
              spinHamiltonian::IsoHyperfine(shf2cH, spins2c, basis2c, 0, 3 + IDshift, fermic2.calculate(B_dir),Ising_only);
            } else {
                spinHamiltonian::IsoHyperfine(shf2cH, spins2c, basis2c, 0, 2 + IDshift, fermic1.calculate(),Ising_only);
                spinHamiltonian::IsoHyperfine(shf2cH, spins2c, basis2c, 0, 3 + IDshift, fermic2.calculate(),Ising_only);
              }
          }

          if ((include_dipolar_to_bath == 1) && (eff_gyro_ratio == 0)) {
            spinHamiltonian::Dipolar(shf2cH, spins2c, basis2c, 1, 2 + IDshift, dipolar1.calculate(B_dir),Ising_only);
            spinHamiltonian::Dipolar(shf2cH, spins2c, basis2c, 1, 3 + IDshift, dipolar2.calculate(B_dir),Ising_only);
          }

          bathdipolar.set_lattice_vector(l_3vec - k_3vec);

          dipolar2cH.set_zeros();
          spinHamiltonian::Dipolar(dipolar2cH,spins2c,basis2c,3 + IDshift,2 + IDshift,bathdipolar.calculate(B_dir));

          total2cH_kl = f2cH + shf2cH + dipolar2cH;
          total2cH_kl.diagonalise(diagtype);


          // lj
          fermic1.set_lattice_vector( l_3vec );
          fermic2.set_lattice_vector( j_3vec );

          dipolar1.set_lattice_vector( l_3vec );
          dipolar2.set_lattice_vector( j_3vec );

          shf2cH.set_zeros();
          if (include_shf_to_bath == 1) {
            if (include_1c == 1) {
              spinHamiltonian::IsoHyperfine(shf2cH, spins2c, basis2c, 0, 2 + IDshift, fermic1.calculate(B_dir),Ising_only);
              spinHamiltonian::IsoHyperfine(shf2cH, spins2c, basis2c, 0, 3 + IDshift, fermic2.calculate(B_dir),Ising_only);
            } else {
                spinHamiltonian::IsoHyperfine(shf2cH, spins2c, basis2c, 0, 2 + IDshift, fermic1.calculate(),Ising_only);
                spinHamiltonian::IsoHyperfine(shf2cH, spins2c, basis2c, 0, 3 + IDshift, fermic2.calculate(),Ising_only);
              }
          }

          if ((include_dipolar_to_bath == 1) && (eff_gyro_ratio == 0)) {
            spinHamiltonian::Dipolar(shf2cH, spins2c, basis2c, 1, 2 + IDshift, dipolar1.calculate(B_dir),Ising_only);
            spinHamiltonian::Dipolar(shf2cH, spins2c, basis2c, 1, 3 + IDshift, dipolar2.calculate(B_dir),Ising_only);
          }
          bathdipolar.set_lattice_vector(j_3vec - l_3vec);

          dipolar2cH.set_zeros();
          spinHamiltonian::Dipolar(dipolar2cH,spins2c,basis2c,3 + IDshift,2 + IDshift,bathdipolar.calculate(B_dir));

          total2cH_lj = f2cH + shf2cH + dipolar2cH;
          total2cH_lj.diagonalise(diagtype);
          
          // 3-cluster
          fermic1.set_lattice_vector( j_3vec );
          fermic2.set_lattice_vector( k_3vec );
          fermic3.set_lattice_vector( l_3vec );

          dipolar1.set_lattice_vector( j_3vec );
          dipolar2.set_lattice_vector( k_3vec );
          dipolar3.set_lattice_vector( l_3vec );

          shf3cH.set_zeros();
          if (include_shf_to_bath == 1) {
            if (include_1c == 1) {
              spinHamiltonian::IsoHyperfine(shf3cH, spins3c, basis3c, 0, 2 + IDshift, fermic1.calculate(B_dir),Ising_only);
              spinHamiltonian::IsoHyperfine(shf3cH, spins3c, basis3c, 0, 3 + IDshift, fermic2.calculate(B_dir),Ising_only);
              spinHamiltonian::IsoHyperfine(shf3cH, spins3c, basis3c, 0, 4 + IDshift, fermic3.calculate(B_dir),Ising_only);
            } else {
                spinHamiltonian::IsoHyperfine(shf3cH, spins3c, basis3c, 0, 2 + IDshift, fermic1.calculate(),Ising_only);
                spinHamiltonian::IsoHyperfine(shf3cH, spins3c, basis3c, 0, 3 + IDshift, fermic2.calculate(),Ising_only);
                spinHamiltonian::IsoHyperfine(shf3cH, spins3c, basis3c, 0, 4 + IDshift, fermic3.calculate(),Ising_only);
              }
          }


          if ( (include_dipolar_to_bath == 1) && (eff_gyro_ratio == 0) ) {
            spinHamiltonian::Dipolar(shf3cH, spins3c, basis3c, 1, 2 + IDshift, dipolar1.calculate(B_dir),Ising_only);
            spinHamiltonian::Dipolar(shf3cH, spins3c, basis3c, 1, 3 + IDshift, dipolar2.calculate(B_dir),Ising_only);
            spinHamiltonian::Dipolar(shf3cH, spins3c, basis3c, 1, 4 + IDshift, dipolar3.calculate(B_dir),Ising_only);
          }

          dipolar3cH.set_zeros();
                    
          bathdipolar.set_lattice_vector(k_3vec - j_3vec);
          spinHamiltonian::Dipolar(dipolar3cH,spins3c,basis3c,3 + IDshift,2 + IDshift,bathdipolar.calculate(B_dir));

          bathdipolar.set_lattice_vector(l_3vec - k_3vec);
          spinHamiltonian::Dipolar(dipolar3cH,spins3c,basis3c,4 + IDshift,3 + IDshift,bathdipolar.calculate(B_dir));

          bathdipolar.set_lattice_vector(j_3vec - l_3vec);
          spinHamiltonian::Dipolar(dipolar3cH,spins3c,basis3c,2 + IDshift,4 + IDshift,bathdipolar.calculate(B_dir));

          total3cH = f3cH + dipolar3cH + shf3cH;

          total3cH.diagonalise(diagtype);

          // Loop over time
          U1c_j = total1cH_j.exponentiate(0.0);
          U1c_k = total1cH_k.exponentiate(0.0);
          U1c_l = total1cH_l.exponentiate(0.0);
          U2c_jk = total2cH_jk.exponentiate(0.0);
          U2c_kl = total2cH_kl.exponentiate(0.0);
          U2c_lj = total2cH_lj.exponentiate(0.0);
          U3c = total3cH.exponentiate(0.0);

          norm2c_jk = HahnSpinEcho::calculate(cmplxd(1.0,0.0),U2c_jk, PIpulse2c, sysbath_uu, 4, sysvec0, sysvec1);
          norm2c_kl = HahnSpinEcho::calculate(cmplxd(1.0,0.0),U2c_kl, PIpulse2c, sysbath_uu, 4, sysvec0, sysvec1);
          norm2c_lj = HahnSpinEcho::calculate(cmplxd(1.0,0.0),U2c_lj, PIpulse2c, sysbath_uu, 4, sysvec0, sysvec1);

          norm1c_j = HahnSpinEcho::calculate(cmplxd(1.0,0.0),U1c_j, PIpulse1c, sysbath_u, 2, sysvec0, sysvec1);
          norm1c_k = HahnSpinEcho::calculate(cmplxd(1.0,0.0),U1c_k, PIpulse1c, sysbath_u, 2, sysvec0, sysvec1);
          norm1c_l = HahnSpinEcho::calculate(cmplxd(1.0,0.0),U1c_l, PIpulse1c, sysbath_u, 2, sysvec0, sysvec1);

          norm3c   = HahnSpinEcho::calculate(cmplxd(1.0,0.0),U3c, PIpulse3c, sysbath_uuu, 8, sysvec0, sysvec1);

          for (m=0;m<L_t_3c.t_size();m++) {

            if (include_1c == 1) {
              U1c_j = total1cH_j.exponentiate(L_t_3c.get_t(m));
              U1c_k = total1cH_k.exponentiate(L_t_3c.get_t(m));
              U1c_l = total1cH_l.exponentiate(L_t_3c.get_t(m));
            }

            U2c_jk = total2cH_jk.exponentiate(L_t_3c.get_t(m));
            U2c_kl = total2cH_kl.exponentiate(L_t_3c.get_t(m));
            U2c_lj = total2cH_lj.exponentiate(L_t_3c.get_t(m));

            U3c = total3cH.exponentiate(L_t_3c.get_t(m));
	    
	          // UP UP UP
           
            echo2c_jk = HahnSpinEcho::calculate(norm2c_jk,U2c_jk, PIpulse2c, sysbath_uu, 4, sysvec0, sysvec1, abs_echo);
            echo2c_kl = HahnSpinEcho::calculate(norm2c_kl,U2c_kl, PIpulse2c, sysbath_uu, 4, sysvec0, sysvec1, abs_echo);
            echo2c_lj = HahnSpinEcho::calculate(norm2c_lj,U2c_lj, PIpulse2c, sysbath_uu, 4, sysvec0, sysvec1, abs_echo);

            if (include_1c == 1) {
              echo1c_j = HahnSpinEcho::calculate(norm1c_j,U1c_j, PIpulse1c, sysbath_u, 2, sysvec0, sysvec1, abs_echo);
              echo1c_k = HahnSpinEcho::calculate(norm1c_k,U1c_k, PIpulse1c, sysbath_u, 2, sysvec0, sysvec1, abs_echo);
              echo1c_l = HahnSpinEcho::calculate(norm1c_l,U1c_l, PIpulse1c, sysbath_u, 2, sysvec0, sysvec1, abs_echo);
            } else {
                echo1c_j = cmplxd(1.0,0.0);
                echo1c_k = cmplxd(1.0,0.0);
                echo1c_l = cmplxd(1.0,0.0);
              }

            echo3c = HahnSpinEcho::calculate(norm3c,U3c, PIpulse3c, sysbath_uuu, 8, sysvec0, sysvec1, abs_echo)/(   (echo2c_jk/(echo1c_j*echo1c_k)) *
                                          (echo2c_kl/(echo1c_k*echo1c_l)) *
                                          (echo2c_lj/(echo1c_l*echo1c_j))   );

	          // DOWN DOWN DOWN
           

            echo2c_jk = HahnSpinEcho::calculate(norm2c_jk,U2c_jk, PIpulse2c, sysbath_dd, 4, sysvec0, sysvec1, abs_echo);
            echo2c_kl = HahnSpinEcho::calculate(norm2c_kl,U2c_kl, PIpulse2c, sysbath_dd, 4, sysvec0, sysvec1, abs_echo);
            echo2c_lj = HahnSpinEcho::calculate(norm2c_lj,U2c_lj, PIpulse2c, sysbath_dd, 4, sysvec0, sysvec1, abs_echo);

            if (include_1c == 1) {
              echo1c_j = HahnSpinEcho::calculate(norm1c_j,U1c_j, PIpulse1c, sysbath_d, 2, sysvec0, sysvec1, abs_echo);
              echo1c_k = HahnSpinEcho::calculate(norm1c_k,U1c_k, PIpulse1c, sysbath_d, 2, sysvec0, sysvec1, abs_echo);
              echo1c_l = HahnSpinEcho::calculate(norm1c_l,U1c_l, PIpulse1c, sysbath_d, 2, sysvec0, sysvec1, abs_echo);
            } else {
                echo1c_j = cmplxd(1.0,0.0);
                echo1c_k = cmplxd(1.0,0.0);
                echo1c_l = cmplxd(1.0,0.0);
              }
            echo3c += HahnSpinEcho::calculate(norm3c,U3c, PIpulse3c, sysbath_ddd, 8, sysvec0, sysvec1, abs_echo)/(   (echo2c_jk/(echo1c_j*echo1c_k)) *
                                          (echo2c_kl/(echo1c_k*echo1c_l)) *
                                          (echo2c_lj/(echo1c_l*echo1c_j))   );


	          // DOWN DOWN UP
           

            echo2c_jk = HahnSpinEcho::calculate(norm2c_jk,U2c_jk, PIpulse2c, sysbath_dd, 4, sysvec0, sysvec1, abs_echo);
            echo2c_kl = HahnSpinEcho::calculate(norm2c_kl,U2c_kl, PIpulse2c, sysbath_du, 4, sysvec0, sysvec1, abs_echo);
            echo2c_lj = HahnSpinEcho::calculate(norm2c_lj,U2c_lj, PIpulse2c, sysbath_ud, 4, sysvec0, sysvec1, abs_echo);
            

            if (include_1c == 1) {
              echo1c_j = HahnSpinEcho::calculate(norm1c_j,U1c_j, PIpulse1c, sysbath_d, 2, sysvec0, sysvec1, abs_echo);
              echo1c_k = HahnSpinEcho::calculate(norm1c_k,U1c_k, PIpulse1c, sysbath_d, 2, sysvec0, sysvec1, abs_echo);
              echo1c_l = HahnSpinEcho::calculate(norm1c_l,U1c_l, PIpulse1c, sysbath_u, 2, sysvec0, sysvec1, abs_echo);
            } else {
                echo1c_j = cmplxd(1.0,0.0);
                echo1c_k = cmplxd(1.0,0.0);
                echo1c_l = cmplxd(1.0,0.0);
              }

            echo3c += HahnSpinEcho::calculate(norm3c,U3c, PIpulse3c, sysbath_ddu, 8, sysvec0, sysvec1, abs_echo)/(   (echo2c_jk/(echo1c_j*echo1c_k)) *
                                          (echo2c_kl/(echo1c_k*echo1c_l)) *
                                          (echo2c_lj/(echo1c_l*echo1c_j))   );


	          // DOWN UP DOWN
            

            echo2c_jk = HahnSpinEcho::calculate(norm2c_jk,U2c_jk, PIpulse2c, sysbath_du, 4, sysvec0, sysvec1, abs_echo);
            echo2c_kl = HahnSpinEcho::calculate(norm2c_kl,U2c_kl, PIpulse2c, sysbath_ud, 4, sysvec0, sysvec1, abs_echo);
            echo2c_lj = HahnSpinEcho::calculate(norm2c_lj,U2c_lj, PIpulse2c, sysbath_dd, 4, sysvec0, sysvec1, abs_echo);

            if (include_1c == 1) {
              echo1c_j = HahnSpinEcho::calculate(norm1c_j,U1c_j, PIpulse1c, sysbath_d, 2, sysvec0, sysvec1, abs_echo);
              echo1c_k = HahnSpinEcho::calculate(norm1c_k,U1c_k, PIpulse1c, sysbath_u, 2, sysvec0, sysvec1, abs_echo);
              echo1c_l = HahnSpinEcho::calculate(norm1c_l,U1c_l, PIpulse1c, sysbath_d, 2, sysvec0, sysvec1, abs_echo);
            } else {
                echo1c_j = cmplxd(1.0,0.0);
                echo1c_k = cmplxd(1.0,0.0);
                echo1c_l = cmplxd(1.0,0.0);
              }
            echo3c += HahnSpinEcho::calculate(norm3c,U3c, PIpulse3c, sysbath_dud, 8, sysvec0, sysvec1, abs_echo)/(   (echo2c_jk/(echo1c_j*echo1c_k)) *
                                          (echo2c_kl/(echo1c_k*echo1c_l)) *
                                          (echo2c_lj/(echo1c_l*echo1c_j))   );



	          // UP DOWN DOWN
            

            echo2c_jk = HahnSpinEcho::calculate(norm2c_jk,U2c_jk, PIpulse2c, sysbath_ud, 4, sysvec0, sysvec1, abs_echo);
            echo2c_kl = HahnSpinEcho::calculate(norm2c_kl,U2c_kl, PIpulse2c, sysbath_dd, 4, sysvec0, sysvec1, abs_echo);
            echo2c_lj = HahnSpinEcho::calculate(norm2c_lj,U2c_lj, PIpulse2c, sysbath_du, 4, sysvec0, sysvec1, abs_echo);

            if (include_1c == 1) {
              echo1c_j = HahnSpinEcho::calculate(norm1c_j,U1c_j, PIpulse1c, sysbath_u, 2, sysvec0, sysvec1, abs_echo);
              echo1c_k = HahnSpinEcho::calculate(norm1c_k,U1c_k, PIpulse1c, sysbath_d, 2, sysvec0, sysvec1, abs_echo);
              echo1c_l = HahnSpinEcho::calculate(norm1c_l,U1c_l, PIpulse1c, sysbath_d, 2, sysvec0, sysvec1, abs_echo);
            } else {
                echo1c_j = cmplxd(1.0,0.0);
                echo1c_k = cmplxd(1.0,0.0);
                echo1c_l = cmplxd(1.0,0.0);
              }

            echo3c += HahnSpinEcho::calculate(norm3c,U3c, PIpulse3c, sysbath_udd, 8, sysvec0, sysvec1, abs_echo)/(   (echo2c_jk/(echo1c_j*echo1c_k)) *
                                          (echo2c_kl/(echo1c_k*echo1c_l)) *
                                          (echo2c_lj/(echo1c_l*echo1c_j))   );



	          // UP UP DOWN
            


            echo2c_jk = HahnSpinEcho::calculate(norm2c_jk,U2c_jk, PIpulse2c, sysbath_uu, 4, sysvec0, sysvec1, abs_echo);
            echo2c_kl = HahnSpinEcho::calculate(norm2c_kl,U2c_kl, PIpulse2c, sysbath_ud, 4, sysvec0, sysvec1, abs_echo);
            echo2c_lj = HahnSpinEcho::calculate(norm2c_lj,U2c_lj, PIpulse2c, sysbath_du, 4, sysvec0, sysvec1, abs_echo);

            if (include_1c == 1) {
              echo1c_j = HahnSpinEcho::calculate(norm1c_j,U1c_j, PIpulse1c, sysbath_u, 2, sysvec0, sysvec1, abs_echo);
              echo1c_k = HahnSpinEcho::calculate(norm1c_k,U1c_k, PIpulse1c, sysbath_u, 2, sysvec0, sysvec1, abs_echo);
              echo1c_l = HahnSpinEcho::calculate(norm1c_l,U1c_l, PIpulse1c, sysbath_d, 2, sysvec0, sysvec1, abs_echo);
            } else {
                echo1c_j = cmplxd(1.0,0.0);
                echo1c_k = cmplxd(1.0,0.0);
                echo1c_l = cmplxd(1.0,0.0);
              }
            echo3c += HahnSpinEcho::calculate(norm3c,U3c, PIpulse3c, sysbath_uud, 8, sysvec0, sysvec1, abs_echo)/(   (echo2c_jk/(echo1c_j*echo1c_k)) *
                                          (echo2c_kl/(echo1c_k*echo1c_l)) *
                                          (echo2c_lj/(echo1c_l*echo1c_j))   );


	          // UP DOWN UP
            

            echo2c_jk = HahnSpinEcho::calculate(norm2c_jk,U2c_jk, PIpulse2c, sysbath_ud, 4, sysvec0, sysvec1, abs_echo);
            echo2c_kl = HahnSpinEcho::calculate(norm2c_kl,U2c_kl, PIpulse2c, sysbath_du, 4, sysvec0, sysvec1, abs_echo);
            echo2c_lj = HahnSpinEcho::calculate(norm2c_lj,U2c_lj, PIpulse2c, sysbath_uu, 4, sysvec0, sysvec1, abs_echo);

            if (include_1c == 1) {
              echo1c_j = HahnSpinEcho::calculate(norm1c_j,U1c_j, PIpulse1c, sysbath_u, 2, sysvec0, sysvec1, abs_echo);
              echo1c_k = HahnSpinEcho::calculate(norm1c_k,U1c_k, PIpulse1c, sysbath_d, 2, sysvec0, sysvec1, abs_echo);
              echo1c_l = HahnSpinEcho::calculate(norm1c_l,U1c_l, PIpulse1c, sysbath_u, 2, sysvec0, sysvec1, abs_echo);
            } else {
                echo1c_j = cmplxd(1.0,0.0);
                echo1c_k = cmplxd(1.0,0.0);
                echo1c_l = cmplxd(1.0,0.0);
              }

            echo3c += HahnSpinEcho::calculate(norm3c,U3c, PIpulse3c, sysbath_udu, 8, sysvec0, sysvec1, abs_echo)/(   (echo2c_jk/(echo1c_j*echo1c_k)) *
                                          (echo2c_kl/(echo1c_k*echo1c_l)) *
                                          (echo2c_lj/(echo1c_l*echo1c_j))   );


	          // DOWN UP UP
           

            echo2c_jk = HahnSpinEcho::calculate(norm2c_jk,U2c_jk, PIpulse2c, sysbath_du, 4, sysvec0, sysvec1, abs_echo);
            echo2c_kl = HahnSpinEcho::calculate(norm2c_kl,U2c_kl, PIpulse2c, sysbath_uu, 4, sysvec0, sysvec1, abs_echo);
            echo2c_lj = HahnSpinEcho::calculate(norm2c_lj,U2c_lj, PIpulse2c, sysbath_ud, 4, sysvec0, sysvec1, abs_echo);

            if (include_1c == 1) {
              echo1c_j = HahnSpinEcho::calculate(norm1c_j,U1c_j, PIpulse1c, sysbath_d, 2, sysvec0, sysvec1, abs_echo);
              echo1c_k = HahnSpinEcho::calculate(norm1c_k,U1c_k, PIpulse1c, sysbath_u, 2, sysvec0, sysvec1, abs_echo);
              echo1c_l = HahnSpinEcho::calculate(norm1c_l,U1c_l, PIpulse1c, sysbath_u, 2, sysvec0, sysvec1, abs_echo);
            } else {
                echo1c_j = cmplxd(1.0,0.0);
                echo1c_k = cmplxd(1.0,0.0);
                echo1c_l = cmplxd(1.0,0.0);
              }

            echo3c += HahnSpinEcho::calculate(norm3c,U3c, PIpulse3c, sysbath_duu, 8, sysvec0, sysvec1, abs_echo)/(   (echo2c_jk/(echo1c_j*echo1c_k)) *
                                          (echo2c_kl/(echo1c_k*echo1c_l)) *
                                          (echo2c_lj/(echo1c_l*echo1c_j))   );


            echo3c /= cmplxd(8.0,0.0);

            L_t_3c.set_f(m,0,L_t_3c.get_f(m,0)*echo3c);



          } // end loop over time

          l = l + 1;

          
        }

        k = k + 1;

      }


    }

  }


  // TODO: Find a better way to do this ...
  if (no_clusters_found == 1) {
    cout << "ERROR: No clusters found. Quitting ..." << endl;
    return 1;
  }

  // Multiply 1-cluster, 2-cluster and 3-cluster results
  
  L_t_combined.set_f(0,L_t_1c.get_f(0));
  L_t_combined.set_f(1,L_t_2c.get_f(0));
  L_t_combined.set_f(2,L_t_3c.get_f(0));
  L_t_1c2c3c_product = L_t_combined.product_f();

  // Store result for placement i
  L_t_out.add_f(L_t_1c2c3c_product.get_f(0)); // TODO: Improve

  outfile.open(output_file_name.c_str());

  if (output_mode != "raw") {
    L_t_mean_f           = L_t_out.mean_f();
    L_t_stdev_mean_f     = L_t_out.stdev_mean_f();
  }

  if (output_mode == "raw")  {
    for (l=0;l<L_t_out.t_size();l++) {
      outfile << setw(32) << left << scientific << setprecision(8);
      // Multiply by 2 and convert microseconds -> milliseconds
      outfile << 2.0*L_t_out.get_t(l)/1.0e3;
      for (m=0;m<L_t_out.f_size();m++) {
        if (report_echo == "real") {
          outfile << setw(32) << left << scientific << setprecision(8) << real(L_t_out.get_f(l,m));
        }
        if (report_echo == "imag") {
          outfile << setw(32) << left << scientific << setprecision(8) << imag(L_t_out.get_f(l,m));
        }
        if (report_echo == "abs") {
          outfile << setw(32) << left << scientific << setprecision(8) << abs(L_t_out.get_f(l,m));
        }
        if (report_echo == "cmplx") {
          outfile << setw(32) << left << scientific << setprecision(8) << L_t_out.get_f(l,m);
        }
      }
      outfile << endl;
    }
  } else {
      for (l=0;l<L_t_out.t_size();l++) {
        outfile << setw(32) << left << scientific << setprecision(8);
        // Multiply by 2 and convert microseconds -> milliseconds
        outfile << 2.0*L_t_out.get_t(l)/1.0e3;
        if (report_echo == "real") {
          outfile << setw(32) << left << scientific << setprecision(8) << real(L_t_mean_f.get_f(l,0));       // TODO: Improve
          outfile << setw(32) << left << scientific << setprecision(8) << real(L_t_stdev_mean_f.get_f(l,0)); // TODO: Improve
        }
        if (report_echo == "imag") {
          outfile << setw(32) << left << scientific << setprecision(8) << imag(L_t_mean_f.get_f(l,0));       // TODO: Improve
          outfile << setw(32) << left << scientific << setprecision(8) << imag(L_t_stdev_mean_f.get_f(l,0)); // TODO: Improve
        }
        if (report_echo == "abs") {
          outfile << setw(32) << left << scientific << setprecision(8) << abs(L_t_mean_f.get_f(l,0));       // TODO: Improve
          outfile << setw(32) << left << scientific << setprecision(8) << abs(L_t_stdev_mean_f.get_f(l,0)); // TODO: Improve
        }
        if (report_echo == "cmplx") {
          outfile << setw(32) << left << scientific << setprecision(8) << L_t_mean_f.get_f(l,0);       // TODO: Improve
          outfile << setw(32) << left << scientific << setprecision(8) << L_t_stdev_mean_f.get_f(l,0); // TODO: Improve
        }
        outfile << endl;
      }
  }

  outfile.close();

  if (couplings_file_name != "null") {
    couplingsfile << endl;
  }

}
// end loop over placements

if (couplings_file_name != "null") {
  couplingsfile.close();
}

if (!silent) {
cout << "... done." << endl;
cout << endl;
}

// ____________________________________________________________________________

// Finalise
// ____________________________________________________________________________

if (!silent) {
cout << "Wrote results to '" << output_file_name << "':" << endl;
cout << " Column 1: time = 2T in milliseconds, where T is the time" << endl;
cout << "           before/after the echo." << endl;
cout << " Subsequent columns: " << report_echo << " echos for each" << endl;
cout << "                     spatial configuration of bath spins." << endl;
if (couplings_file_name != "null") {
  cout << "Wrote 2-cluster coupling strengths to '" << couplings_file_name << "':" << endl;
  cout << " Units: M rad s-1." << endl;
  cout << " Columns 1 and 2: superhyperfine couplings between the" << endl;
  cout << "                  central electron and each bath nucleus" << endl;
  cout << "                  (if included)." << endl;
  cout << " Columns 3 and 4: dipolar couplings between the central" << endl;
  cout << "                  nucleus and each bath nucleus" << endl;
  cout << "                  (if included)." << endl;
  cout << " Last column: dipolar coupling between the two bath nuclei." << endl;
}
cout << endl;
cout << "donornucbath finished: " << endl;
tint = system("date");
}

string plot_command = "xmgrace ";
plot_command += output_file_name;
plot_command += " &";

if (cmd.foundOption("plot")) {
  tint = system(plot_command.c_str());
}

tint += 1;
return 0;

}

