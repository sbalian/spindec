// See PiPulse.h for description.
// Seto Balian, Jul 30, 2014

#include "SpinDec/PiPulse.h"
#include "SpinDec/Errors.h"
#include "SpinDec/BoostEigen.h"

namespace SpinDec
{

PiPulse::PiPulse()
{
}

void PiPulse::construct_pulse_operator()
{
  
  // construct basis and get identity dimension
  UInt identity_dimension = 1;
  SpinBasis operator_basis = state0_.get_basis();
  for (UInt i=0;i<unaffected_states_.size();i++) {
    identity_dimension *= unaffected_states_[i].get_dimension();
    operator_basis = operator_basis^unaffected_states_[i].get_basis();
  }
  
  pulse_operator_ = SpinOperator(operator_basis);
  
  ComplexMatrix pulse_matrix(pulse_operator_.get_dimension(),
      pulse_operator_.get_dimension());
  
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
  
  // Now do the identities
  ComplexMatrix identity(identity_dimension,identity_dimension);
  identity=Eigen::MatrixXcd::Identity(identity_dimension,identity_dimension);
  
  if (identity_dimension <= 1) { // TODO Improve this ...
    pulse_operator_.set_matrix(pulse_matrix);
  } else {
      pulse_operator_.set_matrix(
          BoostEigen::tensorProduct(pulse_matrix,identity));
  }
  
  return;
  
}

PiPulse::PiPulse(const SpinState& state0, const SpinState& state1,
    const vector<SpinState>& other_states,
    const vector<SpinState>& unaffected_states) :
      Pulse(state0,state1,0.0,unaffected_states)
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
