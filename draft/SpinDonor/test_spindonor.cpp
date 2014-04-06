// For testing SpinDec
// Seto Balian, Mar 6, 2014

#include <iostream>
#include <iomanip>

#include "SpinDec/base.h"

using namespace SpinDec;

int main ()
{
  ThreeVector field_direction(1.0,1.0,0.0);
  
  // Set up magnetic field (T)
  UniformMagneticField field(0.480,field_direction);
  
  // Set up spins (state vectors all zero)
  ElectronSpin electron(1.75e5); // position origin
  NuclearSpin bismuth(4.5,-44.0); // postition origin
  NuclearSpin si29(0.5,53.0); // position origin
  
  // Set up spin interaction graph

  // Spatial positions (A)
  ThreeVector si29_position1(3.0,-2.0,1.0);
  ThreeVector si29_position2(1.0,1.5,0.0);
  NuclearSpin si29_1 = si29;
  si29_1.set_position(si29_position1);
  NuclearSpin si29_2 = si29;
  si29_2.set_position(si29_position2);

  SpinInteractionGraph twocluster_graph;
  
  // Central electron and nucleus
  twocluster_graph.add_vertex(electron);// takes label 0
  twocluster_graph.add_vertex(bismuth); // takes label 1 and so on with add
                                        // vertex
  
  // Interacting with a preset hyperfine interaction (9e3 M rad s-1) 
  Hyperfine interaction_A(9.0e3);
  twocluster_graph.add_edge(0,1,&interaction_A);


  // A pair of bath 29Si nuclei at different positions
  twocluster_graph.add_vertex(si29_1);
  twocluster_graph.add_vertex(si29_2);
  
  // Each 29Si interacts with the central electron via a (calculated)
  // isotropic hyperfine interaction (Si:Bi and diamond cubic parameters)
  HyperfineParameters hyperfine_parameters(
      5.43,25.09,14.43,0.069,186.0,"Isotropic");
  IsingHyperfine interaction_J1(hyperfine_parameters);
  IsingHyperfine interaction_J2(hyperfine_parameters);

  twocluster_graph.add_edge(0,2,&interaction_J1);
  twocluster_graph.add_edge(0,3,&interaction_J2);
  
  // Dipolar interaction between the two 29Si
  Dipolar interaction_C12;
  twocluster_graph.add_edge(2,3,&interaction_C12);
  
  // Construct the spin Hamiltonian
  SpinHamiltonian H(twocluster_graph,field);
  
  // Diagonalize
  HermitianEigenspectrum eigenspectrum(H.get_matrix(),"Lapack");
    
  std::cout << std::setprecision(10) << std::left;
  std::cout << std::scientific << std::endl;
  std::cout << eigenspectrum.get_eigenvalues().real() << std::endl << std::endl;
                                               // Feb 24, 2014 matches with
                                               // legacyspindecoherence
  return 0;
}
