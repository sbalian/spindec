// For testing SpinDecoherence
// Seto Balian, Feb 7, 2014

#include <iostream>
#include "SpinDecoherence.h"

using namespace SpinDecoherence;

int main ()
{
  Eigen::Vector3d field_direction(1.0,1.0,0.0);
  
  // Set up magnetic field (T)
  UniformMagneticField field(0.480,field_direction);
  
  // Set up spins
  ElectronSpin electron(1.75e5);
  NuclearSpin bismuth(4.5,-44.0);
  NuclearSpin si29(0.5,53.0);
  
  // Set up spin interaction graph

  // Spatial positions (A)
  Eigen::Vector3d origin = Eigen::Vector3d::Zero();
  Eigen::Vector3d si29_position1(3.0,-2.0,1.0);
  Eigen::Vector3d si29_position2(1.0,1.5,0.0);

  SpinInteractionGraph twocluster_graph;
  
  // Central electron and nucleus
  twocluster_graph.add_vertex(electron,origin); // takes label 0
  twocluster_graph.add_vertex(bismuth,origin); // takes label 1
  
  // interacting with a preset hyperfine interaction
  // first set up the hyperfine interaction (9e3 M rad s-1) 
  Hyperfine interaction_A(9.0e3);
  
  
  twocluster_graph.add_vertex(si29,null_state,bath_position1);
  twocluster_graph.add_vertex(si29,null_state,bath_position2);
  
  HyperfineParameters hyperfine_parameters
  
  twocluster_graph.add_edge(0,1,
      Hyperfine(electron,nucleus,));
  
  
  
  return 0;
}
