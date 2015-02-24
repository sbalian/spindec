// For testing SpinDec
// Seto Balian, Feb 24, 2015

#include <ctime>

#include "SpinDec/base.h"

using namespace SpinDec;

int main ()
{
  
  // Set up magnetic field (T)
  UniformMagneticField field(0.5,ThreeVector(1.0,1.0,1.0));
  
  SpinHalf electron(1.7591e5,field.get_magnitude(),ThreeVector::Zero());
  
  SpinHalf si29(53.1903, field.get_magnitude(),ThreeVector::Zero());
  
  // Dipolar interaction between two 29Si
  Dipolar interaction_C12;
  
  // Central system - bath interaction
  HyperfineParameters hyperfine_parameters(
      5.43,25.09,14.43,0.069,186.0,false,"Isotropic");
  
  Hyperfine interaction_J( hyperfine_parameters );

  // Crystal structure
  
  vector<ThreeVector> site_vectors;
  site_vectors.push_back(ThreeVector(1.0,0.0,0.0)*1.5);
  site_vectors.push_back(ThreeVector(0.0,1.0,0.0)*1.5);
   
  CrystalStructure structure(site_vectors);
  
  SpinBath spin_bath(structure,si29.clone(),
      SpinInteractionEdge(0,1,interaction_C12.clone()));
  
  spin_bath.set_bath_state(0,1);
  spin_bath.set_bath_state(1,0);

  
  CDouble invsqrt2(1.0/std::sqrt(2.0));
  electron.set_state(invsqrt2,0,invsqrt2,1);

  // Central spin decoherence problem
  CSDProblem csd_problem(electron.clone(),spin_bath,
      SpinInteractionEdge(0,1,interaction_J.clone()),field);

  TimeArray time_array(0.0,1000.0,1000);
  CPMGDephasing cpmg_dephasing( // CPMG order 1 = Hahn spin echo
      csd_problem,time_array,0,invsqrt2,0,invsqrt2,
      1);
  
  ClusterDatabase database(spin_bath,2,50000.0,"local");
  
  CCE cce(2,cpmg_dephasing.clone(),database,false);


  cce.calculate();
  
  TimeEvolution time_evolution = cce.evolution(2);
  
  // print results
  
  // print to screen
  time_evolution.print_abs();
  
  return 0;
  
}
