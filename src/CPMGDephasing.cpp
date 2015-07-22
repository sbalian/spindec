// See CPMGDephasing.h for description.
// Seto Balian, Nov 13, 2014

#include "SpinDec/CPMGDephasing.h"
#include "SpinDec/Errors.h"
#include "SpinDec/DensityOperator.h"
#include "SpinDec/CPMG.h"
#include "SpinDec/IdentityPulse.h"

namespace SpinDec
{

CPMGDephasing::CPMGDephasing() : PulseExperiment(), cpmg_order_(0)
{

}

CPMGDephasing::CPMGDephasing(const CSDProblem& csd_problem,
    const TimeArray& time_array, const UInt cpmg_order, const CDouble& c0,
    const UInt level_label0, const CDouble& c1, const UInt level_label1) :
        PulseExperiment(csd_problem,time_array), cpmg_order_(cpmg_order)
{

  // Initial state pi/2 pulse superposition
  csd_problem_.get_central_spin_system()->set_state(
      c0,level_label0,c1,level_label1);
  
  initial_system_state_ = TwoStateSuperposition(c0,
      csd_problem_.get_central_spin_system()->eigenstate(level_label0),
      c1,csd_problem_.get_central_spin_system()->eigenstate(level_label1));

  initial_system_state_.normalize();

  csd_problem_.set_central_spin_state(initial_system_state_);

  // system pi pulse
  system_pi_pulse_ =
      csd_problem_.get_central_spin_system()->pi_pulse(
                                            level_label0,level_label1);


}

// TODO May be very slow
TimeEvolution CPMGDephasing::time_evolution(
    const UIntArray bath_indices)
{
  
  const UInt order = bath_indices.size();
  
  if (order == 0) {
    Errors::quit("Order can't be zero.");
  }
  
  Pulse pi_pulse;
  
  UInt index = 0;
  bool found = false;
  
  for (UInt i =0;i<pulses_.size();i++) {
    if ( pulses_[i].first == order ) {
      found = true;
      index = i;
    }
  }
  

  if (found == true) {
    pi_pulse = pulses_[index].second;
  } else {
    
    
    SpinBasis bath_basis =
        csd_problem_.get_spin_bath().reduced_problem_graph(order).get_basis();

    pi_pulse = system_pi_pulse_^IdentityPulse(bath_basis);
    pulses_.push_back(
        pair< UInt,Pulse>(order,pi_pulse) );
    
  }
  

  SpinState state0 = initial_system_state_.get_state0();
  SpinState state1 = initial_system_state_.get_state1();
  
  // CPMG coherence
  CDoubleArray L;

  CDouble norm = CDouble(1.0,0.0);
  
  SpinSystem reduced_problem = csd_problem_.get_reduced_problem(bath_indices);
  SpinState initial_state = reduced_problem.get_state();
  
  CPMG cpmg(cpmg_order_,reduced_problem.evolution_operator(0.0),pi_pulse);
    
  for (UInt i=0;i<time_array_.get_dimension();i++) {
    
    cpmg.set_time( time_array_.get_time(i) );
    
    DensityOperator density_operator(cpmg.final_state(initial_state),
        state0,
        state1);

    // off diagonal of reduced density matrix
    if (i==0) { // norm
      norm = density_operator.off_diagonal_reduced();
      L.push_back(CDouble(1.0,0.0));
    } else {
      L.push_back( density_operator.off_diagonal_reduced()/norm );
    }

  }
  
  return TimeEvolution(time_array_,L);

}

shared_ptr<PulseExperiment> CPMGDephasing::clone() const
{
  return shared_ptr<PulseExperiment> (new CPMGDephasing(*this));
}

} // namespace SpinDec

