// For testing SpinDec
// Seto Balian, Sep 9, 2014

#include <iostream>
#include <iomanip>
#include <memory>

#include "SpinDec/base.h"

using namespace SpinDec;

int main ()
{
  ThreeVector field_direction(1.0,1.0,0.0);
  
  // Set up magnetic field (T)
  UniformMagneticField field(0.480,field_direction);
  
  // Set up spins (state vectors all zero)
  ElectronSpinParameters electron(1.75e5); // position origin
  SpinParameters bismuth(4.5,-44.0); // postition origin
  SpinParameters si29(0.5,53.0); // position origin
  
  ThreeVector origin; // 0 0 0 cartesian x y z
  
  // Set up spin interaction graph

  // Spatial positions (A)
  ThreeVector si29_position1(3.0,-2.0,1.0);
  ThreeVector si29_position2(1.0,1.5,0.0);
  
  SpinInteractionGraph twocluster_graph;
  
  // Central electron and nucleus
  twocluster_graph.add_vertex(electron,origin);// takes label 0
  twocluster_graph.add_vertex(bismuth,origin);
                                        // takes label 1 and so on with add
                                        // vertex

  // Interacting with a preset hyperfine interaction (9e3 M rad s-1) 
  Hyperfine interaction_A(9.0e3);
  twocluster_graph.add_edge(0,1,interaction_A.clone());
  
  // A pair of bath 29Si nuclei at different positions
  twocluster_graph.add_vertex(si29,si29_position1);
  twocluster_graph.add_vertex(si29,si29_position2);
  
  // Each 29Si interacts with the central electron via a (calculated)
  // isotropic hyperfine interaction (Si:Bi and diamond cubic parameters)
  HyperfineParameters hyperfine_parameters(
      5.43,25.09,14.43,0.069,186.0,"Isotropic");
  IsingHyperfine interaction_J1(hyperfine_parameters);
  IsingHyperfine interaction_J2(hyperfine_parameters);

  twocluster_graph.add_edge(0,2,interaction_J1.clone());
  twocluster_graph.add_edge(0,3,interaction_J2.clone());
  
  // Dipolar interaction between the two 29Si
  Dipolar interaction_C12;
  twocluster_graph.add_edge(2,3,interaction_C12.clone());
  
  SpinSystem spin_system(twocluster_graph,field);
  // Print eigenvalues
  spin_system.print('e');
  
  return 0;
}
