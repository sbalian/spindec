// For testing SpinDec
// Seto Balian, Jul 30, 2014

#include <iostream>
#include <iomanip>
#include <memory>

#include "SpinDec/base.h"

using namespace SpinDec;

int main ()
{
  
  // Calculates the coherence of a Si:Bi donor coupled to two 29Si nuclei
  
//  // Set up magnetic field (T)
//  UniformMagneticField field(0.480,ThreeVector(0.0,1.0,1.0));
  
  // donor at origin
  SpinDonor donor(0.480,4.5,1.7591e5,-43.775,9.2702e3,9-1,12-1,ThreeVector(),
      ThreeVector(),true);
  
  // 29Si
  SpinHalf si29(53.1903, 0.480,ThreeVector(1.0,0.5,3.0));
  SpinHalf si29(53.1903, 0.480,ThreeVector(-4.0,1.0,-2.0));
  
  
  SpinSystem
  
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
                                               // May 29, 2014 matches with
                                               // legacyspindecoherence
  
  // Now set up initial states
  SpinState electron_state();
  
  return 0;
}
