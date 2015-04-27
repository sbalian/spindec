// SpinDec dsnsd
//
// Donors in silicon - CMPMG-N T2 for nuclear spin diffusion (29Si impurities).
// See help_page string below for details of arguments.
//
// Calculates the CPMG decay for a central donor spin in
// silicon in a nuclear spin bath (spin-1/2 29Si nuclear impurities)
// using the cluster correlation expansion.
//
// Seto Balian, Apr 17, 2015

#include <ctime>
#include <fstream>
#include <sstream>

#include "SpinDec/base.h"
using namespace SpinDec;

#include <boost/program_options.hpp>
namespace po = boost::program_options;

string sample_config(const string & version);

int main (int argc, char **argv)
{
  
  // start timer
  std::time_t time_start = std::time(0);
  
  // Arguments
  
  UInt cpmg_order, cce_order;
  UInt build_order;
  string build_method;
  bool include_one_cluster = false;
  double field_strength, field_x, field_y, field_z, gamma_e, electron_ie;
  double gamma_n, nuclear_spin, hyperfine;
  UInt lower_level, upper_level;
  double perc_29si, cluster_cutoff, lattice_size;
  bool log_time = false;
  double initial_time, final_time;
  UInt num_steps;
  int position_seed, state_seed;
  bool kill_nonising = false;
  bool dipolar_hyperfine = false;
  string input_file;
  string prefix;
  
  // Help
  string title =       
      "==============\n"
      "SpinDec: dsnsd\n"
      "==============\n\n"
      "Nuclear spin diffusion for donors in silicon\n\n";

  string help_page = title +
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
      "\nARGUMENTS";
  
  string version = "v0.9, Copyright (C) Seto Balian, Feb 24 2015. "
      "Free software, no warranty.";
  
  // Declare a group of options that will be 
  // allowed only on command line
  po::options_description cmd_only_options("Allowed only on command line");
  cmd_only_options.add_options()
      ("help,h", "print this help page")
      ("version,v", "display version")
      ("sample-config,C", "print sample config file")
      ("prefix,o", po::value< string >(&prefix),
          "prefix for output files")
          ("print-hyperfine,H", "print the hyperfine couplings to\n"
                              "the bath in M rad s-1 and exit")
      ("verbose,V", "verbose mode")
      ;
  
  // Declare a group of options that will be 
  // allowed both on command line and in
  // config file
  po::options_description options("Allowed on command line and config file");
  options.add_options()
       
     ("cce-order,c",po::value<UInt>(&cce_order)->default_value(2,"2"),
        "maximum CCE truncation order to calculate\n"
        "(minimum is 1)")
     
     ("build-method,m",po::value<string>(&build_method)->
         default_value("local","local"),
           "cluster build method: \"local\" or \"global\"")
        
      ("build-order,b",po::value<UInt>(&build_order)->
          default_value(0,"cce-order"),
           "cluster build order\n"
           "(minimum is 1)")

      ("cpmg-order,N",po::value<UInt>(&cpmg_order)->default_value(1,"1"),
       "CPMG order, 1 is Hahn spin echo,\n0 is FID")
       
      ("one-clusters,1", "include 1 clusters")
      
      ("complex,Z", "print complex output (not abs of echo)")
            
      ("field,B", po::value<double>(&field_strength)->default_value(0.480,
       "0.480"),
       "magnetic field in Tesla")
       
      ("field-x,x", po::value<double>(&field_x)->default_value(0.0,"0"),
      "x-component of vector parallel\nto magnetic field")
        
      ("field-y,y", po::value<double>(&field_y)->default_value(1.0,"1"),
       "y-component of vector parallel\nto magnetic field")

      ("field-z,z", po::value<double>(&field_z)->default_value(1.0,"1"),
       "z-component of vector parallel\nto magnetic field")
       
      ("gamma-e,G", po::value<double>(&gamma_e)->default_value(1.7591e5,
       "1.7591e5"),
       "donor electron gyromagnetic ratio\nin M rad s-1 T-1")
       
      ("electron-ie,e", po::value<double>(&electron_ie)->default_value(0.069,
       "0.069"),
       "donor electron ionization energy in eV")

      ("gamma-n,g", po::value<double>(&gamma_n)->default_value(-43.775,
       "-43.775"),
       "donor nucleus gyromagnetic ratio\nin M rad s-1 T-1")

      ("nuclear-spin,I", po::value<double>(&nuclear_spin)->default_value(4.5,
       "4.5"),
       "donor nucleus quantum number")

      ("hyperfine,A", po::value<double>(&hyperfine)->default_value(9.2702e3,
       "9.2702e3"),
       "donor hyperfine in M rad s-1")

      ("lower-level,l", po::value<UInt>(&lower_level)->default_value(9,
       "9"),
       "donor lower transition level\n(counting from 1 in increasing energy)")

      ("upper-level,u", po::value<UInt>(&upper_level)->default_value(12,
       "12"),
       "donor upper transition level\n(counting from 1 in increasing energy)")

      ("perc-29Si,p", po::value<double>(&perc_29si)->default_value(4.67,
       "4.67"),
       "29Si percentage abundance")

      ("cluster-cutoff,s", po::value<double>
        (&cluster_cutoff)->default_value(4.51,
       "4.51"),
       "cluster size cutoff in Angstroms")

      ("lattice-size,S", po::value<double>(&lattice_size)->default_value(162.9,
       "162.9"),
       "side length of cubic superlattice\nin Angstroms")
       
      ("initial-time,t", po::value<double>(&initial_time)->default_value(0.0,
       "0"),
       "initial evolution time in ms")

      ("final-time,T", po::value<double>(&final_time)->default_value(0.5,
       "0.5"),
       "final evolution time in ms")

      ("num-steps,n", po::value<UInt>(&num_steps)->default_value(100,
       "100"),
       "number of time steps")

      ("log-time,L", "logarithmic time divisions")
      
      ("kill-nonising,k", "kill the non-Ising part of\n"
                           "the donor-bath interaction")
                           
      ("dipolar-hyperfine,D", "include the dipolar part of\n"
       "the donor-bath interaction")

      ("position-seed,P", po::value<int>(&position_seed)->default_value(15,
       "15"),
       "random number generator seed\n"
       "for bath spin positions")
       
       ("state-seed,J", po::value<int>(&state_seed)->default_value(25,
        "25"),
        "random number generator seed\n"
        "for bath spin states\n(won't seed if 0)")
        
        ("sphere,Q", "spherical superlattice")
        
        ("no-divisions,x","no CCE divisions")
      
    ;
  
  // Hidden positional options on command line
  po::options_description positional_options;
  positional_options.add_options()
      ("input-file,i", po::value< string >(&input_file), "input file")
      ;
  
  po::options_description cmd;
  cmd.add(cmd_only_options).add(options).add(positional_options);
  
  po::options_description visible( help_page );
  visible.add(cmd_only_options).add(options);
  
  po::positional_options_description pod;
  pod.add("prefix",1);
  pod.add("input-file",1);
  
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
  
  if (vm.count("sample-config")) {
    cout << sample_config(version) << endl;
    return 0;
  }
  
  if (vm.count("prefix") == 0) {
    cout << "run spindec-dsnsd --help" << endl;
    Errors::quit("prefix argument required.");
    return 0;
  }
  
  if (vm.count("input-file")) {
        
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
  
  if (vm.count("one-clusters")) {
    include_one_cluster = true;
  }
    
  if ( (cce_order == 1) && (include_one_cluster == false)) {
    Errors::quit("Can't do CCE1 without one clusters!");
  }
    
  if (vm.count("log-time")) {
    log_time = true;
  }
  
  if (vm.count("kill-nonising")) {
    kill_nonising = true;
  }
  
  if (vm.count("dipolar-hyperfine")) {
    dipolar_hyperfine = true;
  }
  
  if (build_order == 0) {
    build_order = cce_order;
  }
  
  if (build_order < cce_order) {
    Errors::quit("Can't have build order < CCE order ...");
  }
  
  // Initialise
  
  if (vm.count("verbose")) {
    
  cout << title;
  struct tm * now = localtime( & time_start );
  cout << "Start date: ";
  cout << now->tm_mday << "/" << (now->tm_mon + 1)<<"/"<< (now->tm_year + 1900);
  cout << endl;
  cout << "Start time: ";
  cout << now->tm_hour << ":" << now->tm_min << ":" << now->tm_sec << endl;
  cout << endl;
  if (vm.count("input-file")) {
    cout << "Input file: " << input_file << endl;
  } else {
      cout << "Input file: none, defaults or input from command line" << endl;
  }
  cout << "Output file prefix: " << prefix << endl;
  cout << endl;
  cout << "Parameters" << endl;
  cout << "----------" << endl;
  cout << "Will calculate the CCE up to order " << cce_order << endl;
  cout << "Built clusters up to order " << build_order << endl;
  cout << "CPMG order: " << cpmg_order << endl;
  cout << "Include 1-clusters? ";
  if (include_one_cluster) {
    cout << "Yes";
  } else {
      cout << "No";
  }
  cout << endl;
  cout << "Magnetic field = " << field_strength << " Tesla" << endl;
  cout << "Magnetic field parallel to [";
  cout << field_x << "," << field_y << "," << field_z << "]" <<endl;
  cout << "Donor electron gyromagnetic ratio = ";
  cout << gamma_e << " M rad s-1 T-1" << endl;
  cout << "Donor ionization energy = " << electron_ie << " eV" << endl;
  cout << "Host nucleus gyromagnetic ratio  = ";
  cout << gamma_n << " M rad s-1 T-1" << endl;
  cout << "Host nuclear spin = " << nuclear_spin << endl;
  cout << "Donor hyperfine = " << hyperfine << " M rad s-1" << endl;
  cout << "Transition: |" << upper_level << "> --> |" << lower_level << ">\n";
  cout << perc_29si << "% 29Si abundance" << endl;
  cout << "Cluster size cutoff: " << cluster_cutoff << " Angstroms";
  cout << endl;
  cout << "Build method" << build_method << endl;
  cout << "Superlattice size: " << lattice_size << " Angstroms" << endl;
  cout << "Logarithmic time scale? ";
  if (log_time) {
    cout << "Yes";
  } else {
      cout << "No";
  }
  cout << endl;
  cout << "Initial time = " << initial_time << " ms" << endl;
  cout << "Final time = " << final_time << " ms" << endl;
  cout << "Number of time steps: " << num_steps << endl;
  cout << "Position seed: " << position_seed << endl;
  cout << "State seed: " << state_seed << endl;
  cout << "Kill non-Ising part of donor-bath interaction? ";
  if (kill_nonising) {
    cout << "Yes";
  } else {
      cout << "No";
  }
  cout << endl;
  cout << "Include dipolar part of donor-bath interaction? ";
  if (dipolar_hyperfine) {
    cout << "Yes";
  } else {
      cout << "No";
  }
  cout << endl;
  cout << endl;
  cout << "Calculating (this may take a long time!) ..." << endl;
  
  }
  
  
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
  HyperfineParameters hyperfine_parameters
  (5.43,25.09,14.43,electron_ie,186.0,kill_nonising,!dipolar_hyperfine);
    
  Hyperfine interaction_J(hyperfine_parameters);
  
  // Crystal structure
  RandomNumberGenerator::seed_uniform_c_rand(position_seed);
  
  DiamondCubic diamond_cubic(5.43,lattice_size, perc_29si/100.0);
  
  if (vm.count("sphere")) {
   diamond_cubic.make_sphere(lattice_size/2.0);
  }
  
  //diamond_cubic.make_shell(70.0,80.0);
  
  if (vm.count("print-hyperfine")) {
    for (UInt i=0;i<diamond_cubic.num_site_vectors();i++) {
      
      interaction_J.calculate(
          donor.get_electron_parameters(),
          SpinHalfParameters(53.1903),
          ThreeVector::Zero(),
          diamond_cubic.get_site_vector(i),field);
      
      cout << interaction_J.get_strength() << endl;
      
    }
    return 0;
  }
  
  // spin bath
  if (state_seed!=0) {
    RandomNumberGenerator::seed_uniform_c_rand(state_seed);
  }
  
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
  
  // TODO make sure the same spin bath goes into cpmg_dephasing and
  // CCE database ...
  
  // Cluster database
  ClusterDatabase database(spin_bath,build_order,cluster_cutoff,build_method);
  
  // CCE
  CCE cce(cce_order,cpmg_dephasing.clone(),database,include_one_cluster);
  
  // Calculate
  if (vm.count("no-divisions")) {
    cce.calculate(cce_order,true);
  } else {
      cce.calculate(cce_order);
  }
  
  // Print to files scaling times appropriately
  
  for (UInt i=1;i<=(cce_order);i++) {
    
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

    if (vm.count("complex")) {
      scaled_time_evolution.print( output_file_name );
    } else {
        scaled_time_evolution.print_abs( output_file_name );
    }
  }
  
  if (vm.count("verbose")) {

  cout << "Done! (";
  cout << "time taken: " <<
      static_cast<UInt>(std::difftime(std::time(0), time_start));
  cout << " seconds)" << endl;
  
  }
  return 0;
  
}

string add_to_config(const string description,const string value)
{
  string desc_line  = "# " + description + "\n";
  string value_line = "  " + value + "\n";
  return desc_line + value_line;
}

string sample_config(const string& version) {
  
  string config =
      "# SpinDec input file\n"
      "# for flags (==), comment out to turn off\n# "
      + version + "\n\n";

  config += add_to_config
      ("Maximum CCE truncation order to calculate (minimum is 1)",
       "cce-order = 2");
  
  config += add_to_config
      ("Cluster build method: \"local\" or \"global\"",
       "build-method = local");
  
  config += add_to_config
      ("Cluster build order (minimum is 1)",
       "build-order = 2");

  config += add_to_config
      ("CPMG order, 1 is Hahn spin echo, 0 is FID",
       "cpmg-order = 1");

  config += add_to_config
      ("include 1 clusters",
       "#one-clusters==");
  
  config += add_to_config
      ("print complex output",
       "#complex==");
  
  config += "\n";
  
  config += add_to_config
      ("magnetic field in Tesla",
       "field = 0.480");

  config += add_to_config
      ("x-component of vector parallel to magnetic field",
       "field-x = 0");

  config += add_to_config
      ("y-component of vector parallel to magnetic field",
       "field-y = 1");

  config += add_to_config
      ("z-component of vector parallel to magnetic field",
       "field-z = 1");

  config += "\n";

  config += add_to_config
      ("donor electron gyromagnetic ratio in M rad s-1 T-1",
       "gamma-e = 1.7591e5");

  config += add_to_config
      ("donor electron ionization energy in eV",
       "electron-ie = 0.069");

  config += "\n";

  config += add_to_config
      ("donor nucleus gyromagnetic ratio in M rad s-1 T-1",
       "gamma-n = -43.775");

  config += add_to_config
      ("donor nucleus quantum number",
       "nuclear-spin = 4.5");
  
  config += add_to_config
      ("donor hyperfine in M rad s-1",
       "hyperfine = 9.2702e3");

  config += add_to_config
      ("donor lower transition level (counting from 1 in increasing energy)",
       "lower-level = 9");

  config += add_to_config
      ("donor upper transition level (counting from 1 in increasing energy)",
       "upper-level = 12");

  config += "\n";

  config += add_to_config
      ("29Si percentage abundance",
       "perc-29Si = 4.67");
  
  config += add_to_config
      ("cluster cutoff in Angstroms",
       "cluster-cutoff = 4.51");

  config += add_to_config
      ("side length of cubic superlattice in Angstroms",
       "lattice-size = 162.9");

  config += "\n";
  
  config += add_to_config
      ("kill the non-Ising part of the donor-bath interaction",
       "#kill-nonising==");

  config += add_to_config
      ("include the dipolar part of the donor-bath interaction",
       "#dipolar-hyperfine==");

  config += "\n";
  
  config += add_to_config
      ("initial evolution time in ms",
       "initial-time = 0");

  config += add_to_config
      ("final evolution time in ms",
       "final-time = 0.5");
  
  config += add_to_config
      ("number of time steps",
       "num-steps = 100");

  config += add_to_config
      ("logarithmic time divisions",
       "#log-time==");
  
  config += "\n";
  
  config += add_to_config
      ("random number generator seed for bath positions",
       "position-seed = 15");
  
  config += add_to_config
      ("random number generator seed for bath spin states (won't seed if 0)",
       "state-seed = 25");
  
  config += add_to_config
  ("spherical superlattice","#sphere==");
  
  config += add_to_config
  ("no CCE divisions","#no-divisions==");

  return config;
  
}
