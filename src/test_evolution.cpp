// For testing SpinDecoherence
// Seto Balian, Feb 10, 2014

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
  twocluster_graph.add_vertex(electron,origin);           // takes label 0
  twocluster_graph.add_vertex(bismuth,origin); // takes label 1
  
  // interacting with a preset hyperfine interaction
  // first set up the hyperfine interaction (9e3 M rad s-1) 
  Hyperfine interaction_A(9.0e3);
  twocluster_graph.add_edge(0,1,&interaction_A);
  
  // A pair of bath 29Si nuclei
  twocluster_graph.add_vertex(si29,si29_position1);
  twocluster_graph.add_vertex(si29,si29_position2);
  
  // each 29Si interacting with the central electron via a (caluclated)
  // isotropic hyperfine interaction
  // Si:Bi and diamond cubic parameters
  HyperfineParameters hyperfine_parameters(5.43,25.09,14.43,0.069,186.0,
      
      "Isotropic");
  IsingHyperfine interaction_J(electron,si29,field,hyperfine_parameters);
  
  twocluster_graph.add_edge(0,2,&interaction_J);
  twocluster_graph.add_edge(0,3,&interaction_J);
  
  // Construct the spin Hamiltonian
  SpinHamiltonian H(twocluster_graph,field);
  
  std::cout << H.get_basis() << std::endl;
  
  return 0;
}
