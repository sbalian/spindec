// SpinDec dsnsd
//
// Donors in silicon - CMPMG-N T2 for nuclear spin diffusion (29Si impurities).
// See help_page string below for details of arguments.
//
// Calculates the CPMG decay for a central donor spin in
// silicon in a nuclear spin bath (spin-1/2 29Si nuclear impurities)
// using the cluster correlation expansion.
//
// Seto Balian, Nov 11, 2014

#include <ctime>

#include "SpinDec/base.h"
using namespace SpinDec;

#include <boost/program_options.hpp>
namespace po = boost::program_options;

int main (int argc, char **argv)
{
  
  // Program arguments
  
  string help_page =
      "SpinDec: dsnsd\n"
      "Calculates T2 (CPMG-N) for a donor in silicon interacting with a\n"
      "spin bath of 29Si nuclear impurities. Initially, the donor is\n"
      "prepared in a coherent superposition of the specified upper\n"
      "and lower eigenstates. The output is the absolute of the\n"
      "off-diagonal of the reduced donor density matrix after evolution\n"
      "under the CPMG sequence. The time column is 2t/N, where t is the\n"
      "specified evolution time in ms (until the first pulse).N=0 corresponds\n"
      "to the FID case (without pulses) with total evolution time t.\n"
      "The donor interacts with the nuclear bath via its electron-29Si\n"
      "hyperfine interaction."
      "\nArguments";
  
  string version = "v0.9, Seto Balian, Nov 11 2014";
  
  po::options_description desc(help_page);
  
  UInt cce_order, cpmg_order;
  bool include_one_cluster = false;
  double field_strength, field_x, field_y, field_z, gamma_e, electron_ie;
  double gamma_n, nuclear_spin, hyperfine;
  UInt lower_level, upper_level;
  double perc_29si, sep_cutoff, lattice_size;
  bool log_time = false;
  double initial_time, final_time;
  UInt num_steps;
  int seed_value;
  bool kill_nonising = false;
  
  desc.add_options()
      
    ("cce_order,O",po::value<UInt>(&cce_order)->default_value(2,"2"),
     "maximum CCE order (minimum is 1)")

    ("cpmg_order,o",po::value<UInt>(&cpmg_order)->default_value(1,"1"),
     "CPMG order, 1 is Hahn spin echo,\n0 is FID")
     
    ("one_clusters,1", "include 1 clusters")
    
    ("field,B", po::value<double>(&field_strength)->default_value(0.480,
     "0.480"),
     "magnetic field in Tesla")
     
    ("field_x,x", po::value<double>(&field_x)->default_value(0.0,"0"),
    "x-component of vector parallel\nto magnetic field")
      
    ("field_y,y", po::value<double>(&field_y)->default_value(1.0,"1"),
     "y-component of vector parallel\nto magnetic field")

    ("field_z,z", po::value<double>(&field_z)->default_value(1.0,"1"),
     "z-component of vector parallel\nto magnetic field")
     
    ("gamma_e,e", po::value<double>(&gamma_e)->default_value(1.7591e5,
     "1.7591e5"),
     "donor electron gyromagnetic ratio\nin M rad s-1 T-1")
     
    ("electron_ie,i", po::value<double>(&electron_ie)->default_value(0.069,
     "0.069"),
     "donor electron ionization energy in eV")

    ("gamma_n,n", po::value<double>(&gamma_n)->default_value(-43.775,
     "-43.775"),
     "donor nucleus gyromagnetic ratio\nin M rad s-1 T-1")

    ("nuclear_spin,I", po::value<double>(&nuclear_spin)->default_value(4.5,
     "4.5"),
     "donor nucleus quantum number")

    ("hyperfine,A", po::value<double>(&hyperfine)->default_value(9.2702e3,
     "9.2702e3"),
     "donor hyperfine in M rad s-1")

    ("lower_level,l", po::value<UInt>(&lower_level)->default_value(9,
     "9"),
     "donor lower transition level\n(counting from 1 in increasing energy)")

    ("upper_level,u", po::value<UInt>(&upper_level)->default_value(12,
     "12"),
     "donor upper transition level\n(counting from 1 in increasing energy)")

    ("prec_29Si,p", po::value<double>(&perc_29si)->default_value(4.67,
     "4.67"),
     "29Si percentage abundance")

    ("sep_cutoff,s", po::value<double>(&sep_cutoff)->default_value(4.51,
     "4.51"),
     "pair separation cutoff in Angstroms")

    ("lattice_size,S", po::value<double>(&lattice_size)->default_value(162.9,
     "162.9"),
     "side length of cubic superlattice\nin Angstroms")
     
    ("initial_time,a", po::value<double>(&initial_time)->default_value(0.0,
     "0"),
     "initial evolution time in ms")

    ("final_time,b", po::value<double>(&final_time)->default_value(0.5,
     "0.5"),
     "final evolution time in ms")

    ("num_steps,N", po::value<UInt>(&num_steps)->default_value(100,
     "100"),
     "number of time steps")

    ("log_time,L", "logarithmic time divisions")
    
    ("kill_nonising,k", "kill the non-Ising part of\n"
                         "the donor-bath interaction")

    ("seed_value,r", po::value<int>(&seed_value)->default_value(15,
     "15"),
     "random number generator seed")
    
    ("help,h", "print this help page")
    
  ;
  
  po::variables_map vm;
  po::store(po::parse_command_line(argc, argv, desc), vm);
  po::notify(vm);

//  if ((vm.count("help")) || (argc == 1)) {
  if (vm.count("help")) {
    cout << desc << endl;
    cout << version << endl;
    return 0;
  }
  
  if (vm.count("one_clusters")) {
    include_one_cluster = true;
  }
  
  if ((cce_order == 1) && (include_one_cluster == false)) {
    Errors::quit("Can't do CCE1 without including one clusters!");
  }
  
  if (vm.count("log_time")) {
    log_time = true;
  }
  
  if (vm.count("kill_nonising")) {
    kill_nonising = true;
  }

  
  // Initialise
  
  // start timer
  std::time_t time_start = std::time(0); 
  
  // Set up magnetic field (T)
  UniformMagneticField field(field_strength,
      ThreeVector(field_x,field_y,field_z));
  
  // Central spin system - donor spin
  // Physicists count from 1, C++ from 0
  lower_level-=1;
  upper_level-=1;
  
  SpinDonor donor(field.get_magnitude(),
      // Nuclear spin quantum number
      nuclear_spin,
      // Electron gyromagnetic ration in M rad s-1 T-1
      gamma_e,
      // Nuclear gyromagnetic ration in M rad s-1 T-1
      gamma_n,
      // Electron-nuclear hyperfine coupling in M rad s-1
      hyperfine,
      lower_level,upper_level,
      ThreeVector::Zero(), // at origin
      ThreeVector::Zero(),
      false); // false = truncate the full Zeeman basis for speed
              // make sure the states thrown away are not involved in evolution
              // under the total spin Hamiltonian (bath + interaction + central
              // spin)

  // 29Si spin bath
  SpinHalf si29(53.1903, field.get_magnitude(),ThreeVector::Zero());
  
  // Dipolar interaction between two 29Si
  Dipolar interaction_C12;
  
  // Central system - bath interaction
  HyperfineParameters hyperfine_parameters;
  
  if (include_one_cluster == true) {
    hyperfine_parameters = HyperfineParameters(
        5.43,25.09,14.43,electron_ie,186.0,"Full");
  } else {
      hyperfine_parameters = HyperfineParameters(
          5.43,25.09,14.43,electron_ie,186.0,"Isotropic");
  }
  
  Hyperfine interaction_J;
  if (kill_nonising == false) {
    interaction_J = Hyperfine(hyperfine_parameters);
  } else {
      interaction_J = IsingHyperfine(hyperfine_parameters);
  }
  
  // Crystal structure
  DiamondCubic diamond_cubic(5.43,lattice_size, perc_29si/100.0);
  
  // spin bath
  SpinBath spin_bath(diamond_cubic,si29.clone(),
      SpinInteractionEdge(0,1,interaction_C12.clone()));
  
  // Initial donor state: coherent superposition of upper and lower states

  CDouble invsqrt2(1.0/std::sqrt(2.0));
  donor.set_state(invsqrt2,lower_level,invsqrt2,
      upper_level);

  // Central spin decoherence problem
  CSDProblem csd_problem(donor.clone(),spin_bath,
      SpinInteractionEdge(0,2,interaction_J.clone()),field);

  // CPMG order
  
  // convert time to microseconds (SpinDec working units)
  initial_time *= 1000.0;
  final_time *= 1000.0;
  
  if (cpmg_order != 0) { // cpmg_order = 0 is FID
    initial_time*=(static_cast<double>(cpmg_order));
    final_time*=(static_cast<double>(cpmg_order));
  }
  
  TimeArray time_array(initial_time,final_time,num_steps);
    
  if (log_time == true) {
    time_array.logarithmic_time();
  }
  
  // CPMG
  CPMGDephasing cpmg_dephasing(
      csd_problem,time_array,cpmg_order,invsqrt2,lower_level,invsqrt2,
      upper_level);
  
  // CCE
  CCE cce(cce_order,cpmg_dephasing.clone(),sep_cutoff,include_one_cluster);
  
  // Calculate
  
  TimeEvolution time_evolution = cce.calculate();
  
  // Print results
  
  cout << "# Time taken: " <<
      static_cast<UInt>(std::difftime(std::time(0), time_start));
  cout << " seconds." << endl;
  
  // convert to show ms like input
  if (cpmg_order == 0) {
    time_evolution.scale_time(1.0/1000.0);
  } else {
      time_evolution.scale_time(2.0/1000.0);
  }
  
  // print to screen
  //cout << "# COL1: time (ms), COL2: evolution" << std::endl;
  time_evolution.print_abs();
  
  return 0;
  
}
