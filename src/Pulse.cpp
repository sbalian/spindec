// See Pulse.h for description.
// Seto Balian, Jul 29, 2014

#include "SpinDec/Pulse.h"
#include "SpinDec/Errors.h"

namespace SpinDec
{

Pulse::Pulse() : duration_(0.0)
{
}

Pulse::Pulse(const SpinState& state0, const SpinState& state1,
    const double duration)
{
  state0_ = state0;
  state1_ = state1;
  
  if (!state0_.get_basis().is_equal(state1_.get_basis())) {
    Errors::quit("Bases for states |0> and |1> in pulse are not the same.");
  }
  
  duration_ = duration;
  
}

const SpinOperator& Pulse::get_pulse_operator() const
{
  return pulse_operator_;
}

Pulse::~Pulse()
{
}

} // namespace SpinDec

