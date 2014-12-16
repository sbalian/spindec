// For testing SpinDec
// Seto Balian, Dec 16, 2014

#include <ctime>

#include "SpinDec/base.h"

using namespace SpinDec;

int main ()
{
  
  // This example calculates Hahn spin echo decay for a central donor spin in
  // silicon in a nuclear spin bath (spin-1/2 29Si with a natural abundance of
  // 4.7%). It uses the cluster correlation expansion (CCE) up to 3rd order.
  
  std::time_t time_start = std::time(0); 
  
  // Set up magnetic field (T)
  UniformMagneticField field(0.480,ThreeVector(0.0,1.0,1.0));
  
  // Central spin system - donor spin  
  const UInt lower_donor_level = 9 - 1;
  const UInt upper_donor_level = 12 - 1;
  
  SpinDonor donor(field.get_magnitude(),
      // Nuclear spin quantum number
      4.5,
      // Electron gyromagnetic ration in M rad s-1 T-1
      1.7591e5,
      // Nuclear gyromagnetic ration in M rad s-1 T-1
      -43.775,
      // Electron-nuclear hyperfine coupling in M rad s-1
      9.2702e3,
      lower_donor_level,upper_donor_level,
      ThreeVector::Zero(), // at origin
      ThreeVector::Zero(),
      false); // truncate the full Zeeman basis for speed
              // make sure the states thrown away are not involved in evolution
              // under the total spin Hamiltonian (bath + interaction + central
              // spin)

  // 29Si spin bath
  
  SpinHalf si29(53.1903, field.get_magnitude(),ThreeVector::Zero());
  
  // Dipolar interaction between two 29Si
  Dipolar interaction_C12;
  
  // Central system - bath interaction
  HyperfineParameters hyperfine_parameters(
      5.43,25.09,14.43,0.069,186.0,false,"Isotropic");
  Hyperfine interaction_J(hyperfine_parameters);

  // Crystal structure
  DiamondCubic diamond_cubic(5.43,162.9,0.0467);
  
  // spin bath
  SpinBath spin_bath(diamond_cubic,si29.clone(),
      SpinInteractionEdge(0,1,interaction_C12.clone()));
  
  // Initial donor state: coherent superposition of upper and lower states

  CDouble invsqrt2(1.0/std::sqrt(2.0));
  donor.set_state(invsqrt2,lower_donor_level,invsqrt2,
      upper_donor_level);

  // Central spin decoherence problem
  CSDProblem csd_problem(donor.clone(),spin_bath,
      SpinInteractionEdge(0,2,interaction_J.clone()),field);

  // Hahn spin echo decay experiment
  TimeArray time_array(0.0,0.5e3,50);
  CPMGDephasing cpmg_dephasing( // CPMG order 1 = Hahn spin echo
      csd_problem,time_array,1,invsqrt2,lower_donor_level,invsqrt2,
      upper_donor_level);
  
  // CCE to 3rd order
  CCE cce(3,cpmg_dephasing.clone(),4.51,false);
  
  cce.calculate();
  
  TimeEvolution time_evolution = cce.evolution(3);
  
  // print results
  
  cout << "# Time taken: " <<
      static_cast<UInt>(std::difftime(std::time(0), time_start));
  cout << " seconds." << endl;
  
  // print to screen
  time_evolution.scale_time(2.0);
  time_evolution.print_abs("test.dat");
  
  return 0;
  
}
