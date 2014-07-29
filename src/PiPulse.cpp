// See PiPulse.h for description.
// Seto Balian, Jul 29, 2014

#include "SpinDec/PiPulse.h"
#include "SpinDec/Errors.h"

namespace SpinDec
{

PiPulse::PiPulse()
{
}

void PiPulse::construct_pulse_operator()
{
  
  pulse_operator_ = SpinOperator(state0_.get_basis());
  
  ComplexMatrix pulse_matrix(state0_.get_dimension(),state0_.get_dimension());
  
  // |0X1|
  pulse_matrix = state0_.get_state_vector()*
      (state1_.get_state_vector().adjoint());
  
  // |1X0|
  pulse_matrix += state1_.get_state_vector()*
      (state0_.get_state_vector().adjoint());
  
  // SUM_i ( |iXi| )
  for (unsigned int i=0;i<other_states_.size();i++) {
    pulse_matrix += other_states_[i].get_state_vector()*
        (other_states_[i].get_state_vector().adjoint());
  }
  
  pulse_operator_.set_matrix(pulse_matrix);
  
  return;
}

PiPulse::PiPulse(const SpinState& state0, const SpinState& state1,
    const vector<SpinState>& other_states) :
      Pulse(state0,state1,0.0)
{
  other_states_ = other_states;
  
  for (unsigned int i=0;i<other_states_.size();i++) {
    if (!other_states_[i].get_basis().is_equal(state1_.get_basis())) {
      Errors::quit("Bases for states in pulse are not the same.");
    }
  }
  
  construct_pulse_operator();
  
}


} // namespace SpinDec
