// See PiPulse.h for description.
// Seto Balian, Sep 1, 2014

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
  
  pulse_operator_ = SpinOperator(state0_.get_basis());
  pulse_operator_.set_matrix(state0_.get_state_vector()*
      (state1_.get_state_vector().adjoint()) +
      state1_.get_state_vector()*
            (state0_.get_state_vector().adjoint()));
  return;
  
}

PiPulse::PiPulse(const SpinState& state0, const SpinState& state1) :
      Pulse(0.0),state0_(state0),state1_(state1)
{
  if (!state0_.get_basis().is_equal(state1_.get_basis())) {
    Errors::quit("Bases for |0> and |1> must be the same.");
  }
  
  construct_pulse_operator();
  
}

std::auto_ptr<Pulse> PiPulse::clone() const
{
  return std::auto_ptr<Pulse>( new PiPulse(*this) );
}

} // namespace SpinDec
