// See CPMGDephasing.h for description.
// Seto Balian, Sep 10, 2014

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
  initial_system_state_ =
      csd_problem_.get_central_spin_system()->superposition(
          c0,level_label0,c1,level_label1);
  initial_system_state_.normalize();

  csd_problem_.set_central_spin_state(initial_system_state_);

  // system pi pulse
  system_pi_pulse_ =
      csd_problem_.get_central_spin_system()->pi_pulse(
                                            level_label0,level_label1);


}

// TODO May be very slow!!!
TimeEvolution CPMGDephasing::time_evolution(
    const UIntArray bath_indices)
{
  const UInt order = bath_indices.size();
  

  if (order == 0) {
    Errors::quit("Order can't be zero.");
  }

  SpinState state0 = initial_system_state_.get_state0();
  SpinState state1 = initial_system_state_.get_state1();
  
  // TODO repeat here ...  
  SpinBasis bath_basis =
      csd_problem_.get_spin_bath().reduced_problem_graph(order).get_basis();
  
  // pulse sequence
  Pulse pi_pulse = system_pi_pulse_^IdentityPulse(bath_basis);

  // CPMG coherence
  CDoubleArray L;

  CDouble norm = CDouble(1.0,0.0);
  

  for (UInt i=0;i<time_array_.get_dimension();i++) {
    
    CPMG cpmg = CPMG(cpmg_order_,pi_pulse,
        csd_problem_.get_reduced_problem(bath_indices)
        .evolution_operator(time_array_.get_time(i)));

    SpinState final_state = cpmg.final_state(
        csd_problem_.get_reduced_problem(bath_indices).get_state());

    DensityOperator density_operator(final_state,
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

auto_ptr<PulseExperiment> CPMGDephasing::clone() const
{
  return auto_ptr<PulseExperiment> (new CPMGDephasing(*this));
}

} // namespace SpinDec

