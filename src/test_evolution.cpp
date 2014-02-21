// For testing SpinDecoherence
// Seto Balian, Feb 21, 2014

#include <iostream>

#include "base.h"

using namespace SpinDecoherence;

int main ()
{
  d3vector field_direction(1.0,1.0,0.0);
  
  // Set up magnetic field (T)
  UniformMagneticField field(0.480,field_direction);
  
  // Set up spins (state vectors all zero)
  ElectronSpin electron(1.75e5); // position origin
  NuclearSpin bismuth(4.5,-44.0); // postition origin
  NuclearSpin si29(0.5,53.0); // position origin
  
  // Set up spin interaction graph

  // Spatial positions (A)
  d3vector si29_position1(3.0,-2.0,1.0);
  d3vector si29_position2(1.0,1.5,0.0);

  SpinInteractionGraph twocluster_graph;
  
  // Central electron and nucleus
  twocluster_graph.add_vertex(electron);// takes label 0
  twocluster_graph.add_vertex(bismuth); // takes label 1 and so on with add
                                        // vertex
  
  // Interacting with a preset hyperfine interaction (9e3 M rad s-1) 
  Hyperfine interaction_A(9.0e3);
  twocluster_graph.add_edge(0,1,&interaction_A);

  // A pair of bath 29Si nuclei at different positions
  si29.set_position(si29_position1);
  twocluster_graph.add_vertex(si29);
  si29.set_position(si29_position2);
  twocluster_graph.add_vertex(si29);

  // Each 29Si interacts with the central electron via a (calculated)
  // isotropic hyperfine interaction (Si:Bi and diamond cubic parameters)
  HyperfineParameters hyperfine_parameters(
      5.43,25.09,14.43,0.069,186.0,"Isotropic");
  IsingHyperfine interaction_J(electron,si29,field,hyperfine_parameters);

  twocluster_graph.add_edge(0,2,&interaction_J);
  twocluster_graph.add_edge(0,3,&interaction_J);

  // Construct the spin Hamiltonian
  SpinHamiltonian H(twocluster_graph,field);

  std::cout << H.get_basis() << std::endl;
  
  return 0;
}
