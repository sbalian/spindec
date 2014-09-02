// See PiPulse.h for description.
// Seto Balian, Sep 2, 2014

#include "SpinDec/PiPulse.h"
#include "SpinDec/Errors.h"
#include "SpinDec/IdentityOperator.h"

namespace SpinDec
{

PiPulse::PiPulse()
{
}

PiPulse::PiPulse(const SpinState& state0, const SpinState& state1) :
      Pulse(0.0,SpinOperator(state0.get_state_vector()*
      (state1.get_state_vector().adjoint()) +
      state1.get_state_vector()*
            (state0.get_state_vector().adjoint()),state0.get_basis()))
{
  
  if (!state0.is_basis_equal(state1.clone())) {
    Errors::quit("Bases for |0> and |1> must be the same.");
  }
  
}

PiPulse::PiPulse(const SpinState& state0, const SpinState& state1,
    const SpinState& unaffected_state) :
          Pulse(0.0,
   SpinOperator(
   state0.get_state_vector()*(state1.get_state_vector().adjoint()) +
   state1.get_state_vector()*(state0.get_state_vector().adjoint()),
   state0.get_basis())^
   IdentityOperator(unaffected_state.get_basis())
   )
{
  
  if (!state0.is_basis_equal(state1.clone())) {
    Errors::quit("Bases for |0> and |1> must be the same.");
  }

}

PiPulse::PiPulse(const SpinState& state0, const SpinState& state1,
    const vector<SpinState> states2_plus, const SpinState& unaffected_state)
{
  
  if (!state0.is_basis_equal(state1.clone())) {
    Errors::quit("Bases for |0> and |1> must be the same.");
  }
  
  SpinOperator pulse(state0.get_basis());
  
  pulse.set_matrix(
          state0.get_state_vector()*(state1.get_state_vector().adjoint()) +
          state1.get_state_vector()*(state0.get_state_vector().adjoint()) );

  for (UInt i =0;i<states2_plus.size();i++) {
    if (!state0.is_basis_equal(states2_plus[i].clone())) {
      Errors::quit("Bases for |0>,|1>,|n,n>=2> must be the same.");
    }
    SpinOperator to_add(state0.get_basis());
    to_add.set_matrix(
        states2_plus[i].get_state_vector()*
        (states2_plus[i].get_state_vector().adjoint()) );
    pulse = pulse + to_add;
  }
  
  duration_ = 0.0;
  pulse_operator_ = pulse^IdentityOperator(unaffected_state.get_basis());
  
}



} // namespace SpinDec
