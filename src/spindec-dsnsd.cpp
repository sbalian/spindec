// SpinDec dsnsd
//
// Donors in silicon - CMPMG-N T2 for nuclear spin diffusion (29Si impurities).
// See help_page string below for details of arguments.
//
// Calculates the CPMG decay for a central donor spin in
// silicon in a nuclear spin bath (spin-1/2 29Si nuclear impurities)
// using the cluster correlation expansion.
//
// Seto Balian, Nov 13, 2014

#include <ctime>
#include <fstream>
#include <sstream>

#include "SpinDec/base.h"
using namespace SpinDec;

#include <boost/program_options.hpp>
namespace po = boost::program_options;

string sample_config();

int main (int argc, char **argv)
{
  
  // start timer
  std::time_t time_start = std::time(0);
  
  // Arguments
  
  UInt max_cce_order, cpmg_order;
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
  string input_file;
  string prefix;
  
  // Help
  string help_page =
      "==============\n"
      "SpinDec: dsnsd\n"
      "==============\n\n"
      "Calculates T2 (CPMG-N) for a donor in silicon interacting with a\n"
      "spin bath of 29Si nuclear impurities. Initially, the donor is\n"
      "prepared in a coherent superposition of the specified upper\n"
      "and lower eigenstates. The outputs are the absolute of the\n"
      "off-diagonal of the reduced donor density matrix after evolution\n"
      "under the CPMG sequence. They are named prefix_XC.dat where X\n"
      "is the CCE truncation order (up to a specified maximum order),\n"
      "and prefix must be specified by the user. The time columns are\n"
      "2t/N, where t is the specified evolution time in ms (until the\n"
      "first pulse). N=0 corresponds to the FID case (without pulses)\n"
      "with total evolution time t. The donor interacts with the nuclear\n"
      "bath via its electron-29Si hyperfine interaction.\n\n"
      "Usage: spindec-dsnsd ... PREFIX ... [INPUT] ... [ARGUMENTS] ...\n"
      "- PREFIX for output files (positional) is required\n"
      "- ARGUMENTS override those in INPUT\n"
      "- INPUT file name (positional) may be omitted\n"
      "- INPUT format is key=value, without - or -- prefixes\n"
      "- for flags, add a line with the flag's name followed by == to enable.\n"
      "=================\n"
      "\nARGUMENTS";
  
  string version = "v0.9, Copyright (C) Seto Balian, Nov 12 2014.\n"
      "Free software, no warranty.";
  
  // Declare a group of options that will be 
  // allowed only on command line
  po::options_description cmd_only_options;
  cmd_only_options.add_options()
      ("help,h", "print this help page")
      ("version,v", "display version")
      ("sample_config", "print sample config file")
      ("prefix,w", po::value< string >(&prefix),
          "prefix for output files")
      ;
  
  // Declare a group of options that will be 
  // allowed both on command line and in
  // config file
  po::options_description options;
  options.add_options()
      ("max_cce_order,O",po::value<UInt>(&max_cce_order)->default_value(2,"2"),
       "maximum CCE truncation order\n"
       "(minimum is 1)")

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

      ("perc_29Si,p", po::value<double>(&perc_29si)->default_value(4.67,
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
            
      ("verbose,V", "verbose mode")
      
    ;
  
  // Hidden positional options on command line
  po::options_description positional_options;
  positional_options.add_options()
      ("input_file", po::value< string >(&input_file), "input file")
      ;
  
  po::options_description cmd;
  cmd.add(cmd_only_options).add(options).add(positional_options);
  
  po::options_description visible( help_page );
  visible.add(cmd_only_options).add(options);
  
  po::positional_options_description pod;
  pod.add("prefix",1);
  pod.add("input_file",1);
  
  po::variables_map vm;
  
  store(po::command_line_parser(argc, argv).
        options(cmd).positional(pod).run(), vm);
  notify(vm);
  
  if ((vm.count("help")) || (argc == 1)) {
      cout << visible << endl;
      cout << version << endl;
      return 0;
  }
  
  if (vm.count("version")) {
    cout << "spindec-dsnsd " << version << endl;
    return 0;
  }
  
  if (vm.count("sample_config")) {
    cout << sample_config() << endl;
    return 0;
  }
  
  if (vm.count("prefix") == 0) {
    cout << "run spindec-dsnsd --help" << endl;
    Errors::quit("prefix argument required.");
    return 0;
  }
  
  
  if (vm.count("input_file")) {
        
    std::ifstream ifs(input_file.c_str());
    
    if (!ifs.is_open()) {
      Errors::quit("Cannot find input configuration file.");
    }
    
    store(parse_config_file(ifs, options), vm);
    notify(vm);

    
  }
  
  store(po::command_line_parser(argc, argv).
        options(cmd).positional(pod).run(), vm);
  notify(vm);
  
  if (vm.count("one_clusters")) {
    include_one_cluster = true;
  }
  
  if ((max_cce_order == 1) && (include_one_cluster == false)) {
    Errors::quit("Can't do CCE1 without including one clusters!");
  }
  
  if (vm.count("log_time")) {
    log_time = true;
  }
  
  if (vm.count("kill_nonising")) {
    kill_nonising = true;
  }

  
  // Initialise
  
  if (vm.count("verbose")) {
  
  cout << "max CCE order: " << max_cce_order << endl;
  cout << "CPMG order: " << cpmg_order << endl;
  cout << "Include 1-clusters: " << include_one_cluster << endl;
  cout << "B = " << field_strength << " T." << endl;
  cout << "B || [" << field_x << "," << field_y << "," << field_z << "]" <<endl;
  cout << "gamma_e = " << gamma_e << " M rad s-1 T-1" << endl;
  cout << "electron_IE = " << electron_ie << " eV" << endl;
  cout << "gamma_n = " << gamma_n << " M rad s-1 T-1" << endl;
  cout << "I = " << nuclear_spin << endl;
  cout << "A = " << hyperfine << " M rad s-1" << endl;
  cout << "Transition |" << upper_level << "> --> |" << lower_level << ">\n";
  cout << perc_29si << "% 29Si abundance" << endl;
  cout << "separation cutoff: " << sep_cutoff << " Angstroms" << endl;
  cout << "superlattice size: " << lattice_size << " Angstroms" << endl;
  cout << "log time: " << log_time << endl;
  cout << "initial time = " << initial_time << " ms" << endl;
  cout << "final time = " << final_time << " ms" << endl;
  cout << "num time steps: " << num_steps << endl;
  cout << "seed value: " << seed_value << endl;
  cout << "kill non-Ising: " << kill_nonising << endl;
  
  if (vm.count("input_file")) {
    cout << "input file: " << input_file << endl;
  } else {
      cout << "input file: none, defaults or input from command line" << endl;
  }

  cout << "output file prefix: " << prefix << endl;
  
  cout << "CALCULATING ..." << endl;
  
  }

  
  RandomNumberGenerator::seed_uniform_c_rand(seed_value);
  
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
    initial_time/=(static_cast<double>(cpmg_order));
    final_time/=(static_cast<double>(cpmg_order));
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
  CCE cce(max_cce_order,cpmg_dephasing.clone(),sep_cutoff,include_one_cluster);
  
  // Calculate
  
  cce.calculate();
  
  
  // Print to files scaling times appropriately
  
  for (UInt i=1;i<=max_cce_order;i++) {
    
    if (include_one_cluster == false) {
      if (i==1) {continue;}
    }
    
    // file name
    string str;
    std::ostringstream oss;
    oss<<"_";
    oss<<i;
    oss<<"C.dat";
    str=oss.str();
    string output_file_name = prefix + str;
    
    // convert to show ms like input
    TimeEvolution scaled_time_evolution = cce.evolution(i);
    
    if (cpmg_order == 0) {
      scaled_time_evolution.scale_time(1.0/1000.0);
    } else {
        scaled_time_evolution.scale_time(
            2.0*static_cast<double>(cpmg_order)/1000.0);
    }

    scaled_time_evolution.print_abs( output_file_name );
    
  }
  
  if (vm.count("verbose")) {

  cout << "... DONE!" << endl;
  cout << "time taken: " <<
      static_cast<UInt>(std::difftime(std::time(0), time_start));
  cout << " seconds." << endl;
  
  }

  return 0;
  
}


string sample_config() {
  
  string config =
      "# SpinDec input file\n"
      "# Seto Balian, Nov 13 2014\n"
      "\n"
      "# Maximum CCE truncation order (minimum is 1)\n"
      "max_cce_order = 2\n"
      "# CPMG order, 1 is Hahn spin echo, 0 is FID\n"
      "cpmg_order = 1\n"
      "# include 1 clusters (comment out to turn off)\n"
      "#one_clusters==\n"
      "\n"
      "# magnetic field in Tesla\n"
      "field = 0.480\n"
      "# x-component of vector parallel to magnetic field\n"
      "field_x = 0\n"
      "# y-component of vector parallel to magnetic field\n"
      "field_y = 1\n"
      "# z-component of vector parallel to magnetic field\n"
      "field_z = 1\n"
      "\n"
      "# donor electron gyromagnetic ratio in M rad s-1 T-1\n"
      "gamma_e = 1.7591e5\n"
      "# donor electron ionization energy in eV\n"
      "electron_ie = 0.069\n"
      "\n"
      "# donor nucleus gyromagnetic ratio in M rad s-1 T-1\n"
      "gamma_n = -43.775\n"
      "# donor nucleus quantum number\n"
      "nuclear_spin = 4.5\n"
      "\n"
      "# donor hyperfine in M rad s-1\n"
      "hyperfine = 9.2702e3\n"
      "# donor lower transition level (counting from 1 in increasing energy)\n"
      "lower_level = 9\n"
      "# upper lower transition level (counting from 1 in increasing energy)\n"
      "upper_level = 12\n"
      "\n"
      "# 29Si percentage abundance\n"
      "perc_29Si = 4.67\n"
      "# pair separation cutoff in Angstroms\n"
      "sep_cutoff = 4.51\n"
      "# side length of cubic superlattice in Angstroms\n"
      "lattice_size = 162.9\n"
      "\n"
      "# initial evolution time in ms\n"
      "initial_time = 0\n"
      "# final evolution time in ms\n"
      "final_time = 0.5\n"
      "# number of time steps\n"
      "num_steps = 100\n"
      "# logarithmic time divisions (comment out to turn off)\n"
      "#log_time==\n"
      "\n"
      "# kill the non-Ising part of the donor-bath interaction\n"
      "# (comment out to turn off)\n"
      "#kill_nonising==\n"
      "\n"
      "# random number generator seed\n"
      "seed_value = 15\n"
      "\n"
      "# verbose mode\n"
      "# (comment out to turn off)\n"
      "#verbose==\n"
      ;

  return config;
  
}
