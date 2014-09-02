// See PulseSequence.h for description.
// Seto Balian, Sep 2, 2014

#include "SpinDec/PulseSequence.h"
#include "SpinDec/Errors.h"

namespace SpinDec
{

PulseSequence::PulseSequence() : duration_(0.0)
{
}

PulseSequence::PulseSequence(const SpinState& initial_state) : duration_(0.0)
{
  initial_state_ = initial_state;
}

void PulseSequence::add_pulse(const Pulse& pulse)
{
  
  if (!pulse.get_pulse_operator().get_basis().is_equal(
      initial_state_.get_basis())) {
    Errors::quit("Invalid pulse operator basis.");
  }
  
  pulses_.push_back(pulse);
  
  duration_+=pulse.get_duration();
  
  return;
}


void PulseSequence::set_initial_state(const SpinState& initial_state)
{
  if (!initial_state.is_basis_equal(initial_state_.clone())) {
    Errors::quit("Invalid initial state basis.");
  }
  initial_state_ = initial_state;
  return;
}

const SpinState& PulseSequence::get_initial_state() const
{
  return initial_state_;
}

SpinState PulseSequence::final_state() const
{
  SpinState final_state = initial_state_;
  for (UInt i=pulses_.size()-1;i>=0;i--) {
    final_state = pulses_[i].get_pulse_operator()*final_state;
  }
  return final_state;
}

double PulseSequence::get_duration() const
{
  return duration_;
}

SpinState PulseSequence::final_state(
    const SpinState& initial_state)
{
  set_initial_state(initial_state);
  return final_state();
}

SpinDec::PulseSequence::~PulseSequence()
{
}

} // namespace SpinDec

