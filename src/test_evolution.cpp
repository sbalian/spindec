// For testing SpinDecoherence
// Seto Balian, Feb 6, 2014

#include <iostream>
#include "SpinDecoherence.h"

using namespace SpinDecoherence;

int main ()
{
  Eigen::Vector3d field_direction(1.0,1.0,0.0);
  
  // Set up magnetic field
  UniformMagneticField field(0.480,field_direction);
  
  // Set up spins
  ElectronSpin electron(1.75e5);
  NuclearSpin bismuth(4.5,-44.0);
  NuclearSpin si29(0.5,53.0);
  
  // Set up spin interaction graph

  // positions of bath spins
  Eigen::Vector3d bath_position1(3.0,-2.0,1.0);
  Eigen::Vector3d bath_position2(1.0,1.5,0.0);

  
  SpinInteractionGraph twocluster_graph;
  twocluster_graph.add_vertex(electron,SpinState(),Eigen::Vector3d::Zero());
  twocluster_graph.add_vertex(bismuth,SpinState(),Eigen::Vector3d::Zero());
  twocluster_graph.add_vertex(si29,SpinState(),bath_position1);
  twocluster_graph.add_vertex(si29,SpinState(),bath_position2);
  
  HyperfineParameters hyperfine_parameters
  
  twocluster_graph.add_edge(0,1,
      Hyperfine(electron,nucleus,));
  
  
  
  return 0;
}
