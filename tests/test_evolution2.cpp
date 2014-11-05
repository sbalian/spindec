// For testing SpinDec
// Seto Balian, Sep 9, 2014

#include <iostream>
#include <iomanip>

#include "SpinDec/base.h"

using namespace SpinDec;

int main ()
{
  // TODO update and complete this
  std::cout << "EMPTY SOURCE" << std::endl;
//  // output format
//  cout << std::left << std::scientific << std::setprecision(10);
//  
//  // Calculates the coherence of a Si:Bi donor coupled to two 29Si nuclei
//  
//  // Set up magnetic field (T)
//  UniformMagneticField field(0.480,ThreeVector(0.0,1.0,1.0));
//  
//  // donor at origin
//  
//  const UInt lower_donor_level = 9 - 1;
//  const UInt upper_donor_level = 12 - 1;
//  
//  SpinDonor donor(field.get_magnitude(),
//      4.5,1.7591e5,-43.775,9.2702e3,
//      lower_donor_level,upper_donor_level,ThreeVector(),ThreeVector(),false);
//  
//  // Two 29Si nuclei
//  SpinHalf si29_1(53.1903, field.get_magnitude(),ThreeVector(1.0,0.5,3.0));
//  SpinHalf si29_2(53.1903, field.get_magnitude(),ThreeVector(-4.0,1.0,-2.0));
//  
//  // Each 29Si interacts with the central electron via a (calculated)
//  // isotropic hyperfine interaction (Si:Bi and diamond cubic parameters)
//  
//  // Now set up the combined system
//  
//  // Set up a graph, starting from the graph of the donor
//  SpinInteractionGraph graph = donor.get_graph();
//  
//  // Now add to this graph the two 29Si graphs
//  graph.join_in_place(si29_1.get_graph());
//  graph.join_in_place(si29_2.get_graph());
//  
//  // Now add the interaction of the two 29Si with the donor
//  HyperfineParameters hyperfine_parameters(
//      5.43,25.09,14.43,0.069,186.0,"Isotropic");
//  Hyperfine interaction_J1(hyperfine_parameters);
//  Hyperfine interaction_J2(hyperfine_parameters);
//  
//  graph.add_edge(0,2,interaction_J1.clone());
//  graph.add_edge(0,3,interaction_J2.clone());
//  
//  // And the dipolar interaction between the two 29Si
//  Dipolar interaction_C12;
//  graph.add_edge(2,3,interaction_C12.clone());
//  
//  // Now form the combined spin system
//  SpinSystem combined_spin_system(graph,field);
//  
//  // Print the eigenvalues of the combined system
////   combined_spin_system.print('e');
////   exit(1);
//  
//  // Now set the initial states
//  
//  // Put the donor in a superposition of it's upper and lower states
//  SpinState donor_state = 
//      donor.eigenstate(lower_donor_level) +
//      donor.eigenstate(upper_donor_level);
//  donor_state.normalize();
//
//  // spin up and down for the 29Si states
//  si29_1.set_state(0);
//  si29_2.set_state(1);
//  
//  SpinState combined_state =
//      donor_state^si29_1.get_state()^si29_2.get_state();
//  
//  combined_state.normalize();
//  combined_spin_system.set_state(combined_state);
//  
//  // Now set up the CPMG pulse sequence
//  
//  // Hahn spin echo decay
//  TimeArray time_array(0.0,1.0e3,10);
//
//  SpinState bath_state = si29_1.get_state()^si29_2.get_state();
//
//  CDouble invsqrt2(1.0/std::sqrt(2.0),0.0);
//  CPMGDephasing cpmg_dephasing(
//      csd_problem,time_array,1,invsqrt2,lower_donor_level,
//                               invsqrt2,upper_donor_level);
//  
//  CPMG cpmg(1,donor.get_lower_level(),donor.get_upper_level(),
//      donor.get_orthogonal_levels(),combined_state,bath_state,
//      combined_spin_system.evolution_operator(0.0));
//  
//  CPMGExperiment cpmg_experiment(cpmg,time_array);
//  
//  TimeEvolution echo_vs_t = cpmg_experiment.time_evolution(combined_state);
//  
//  // print to screen
//  echo_vs_t.print_abs();
  
  return 0;
  
}