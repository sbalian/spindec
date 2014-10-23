// For testing SpinDec
// Seto Balian, Oct 23, 2014

#include <iostream>
#include <iomanip>

#include <ctime>

#include "SpinDec/base.h"

using namespace SpinDec;

int main ()
{
  
  std::time_t time_start = std::time(0); 
  
  // Set up magnetic field (T)
  UniformMagneticField field(0.480,ThreeVector(0.0,1.0,1.0));
  
  // Central spin (CS) system
  // Donor
  const UInt lower_donor_level = 9 - 1;
  const UInt upper_donor_level = 12 - 1;
  
  SpinDonor donor(field.get_magnitude(),
      4.5,1.7591e5,-43.775,9.2702e3,
      lower_donor_level,upper_donor_level,ThreeVector::Zero(),
      ThreeVector::Zero(),false);
  
  // Bath system
  // 29Si
  
  SpinHalf si29(53.1903, field.get_magnitude(),ThreeVector::Zero());
  // Dipolar interaction between the two 29Si
  Dipolar interaction_C12;
  
  // CS - bath interaction
  HyperfineParameters hyperfine_parameters(
      5.43,25.09,14.43,0.069,186.0,"Isotropic");
  Hyperfine interaction_J(hyperfine_parameters);

  // Crystal structure
  DiamondCubic diamond_cubic(5.43,162.9,0.0467);
  
  // Spin bath
  
  SpinBath spin_bath(diamond_cubic,si29.clone(),
      SpinInteractionEdge(0,1,interaction_C12.clone()));
  
  // CSDProblem

  // TODO HACK
  CDouble invsqrt2(1.0/std::sqrt(2.0));
  donor.set_state(invsqrt2,lower_donor_level,invsqrt2,
      upper_donor_level);
  
  CSDProblem csd_problem(donor.clone(),spin_bath,
      SpinInteractionEdge(0,2,interaction_J.clone()),field);

  // Hahn spin echo decay
  TimeArray time_array(0.0,1.0e3,100);
  
  CPMGDephasing cpmg_dephasing(
      csd_problem,time_array,1,invsqrt2,lower_donor_level,invsqrt2,
      upper_donor_level);
  
  // Pair correlations
  CCE cce(3,cpmg_dephasing.clone(),4.51,false);
  
  TimeEvolution time_evolution = cce.calculate();
  
  cout << "# Time taken: " <<
      static_cast<UInt>(std::difftime(std::time(0), time_start));
  cout << " seconds." << endl;
  
  // print to screen
  time_evolution.print_abs();
  
  return 0;
  
}
