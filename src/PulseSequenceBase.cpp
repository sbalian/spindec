// See PulseSequenceBase.h for description.
// Seto Balian, Sep 8, 2014

#include "SpinDec/PulseSequenceBase.h"
#include "SpinDec/Errors.h"

namespace SpinDec
{

PulseSequenceBase::PulseSequenceBase() : duration_(0.0)
{
}

SpinState PulseSequenceBase::final_state(const SpinState& initial_state) const
{
  
  if (num_pulses() == 0) {
    Errors::quit("No pulses in pulse sequence.");
  }
  
  if (!pulses_[0].get_pulse_operator().is_basis_equal(
      initial_state.clone())) {
    Errors::quit("Invalid initial state basis.");
  }
  
  SpinState final_state = initial_state;
  for (int i=pulses_.size()-1;i>=0;i--) {
    final_state = pulses_[i].get_pulse_operator()*final_state;
  }
  return final_state;
  
}

double PulseSequenceBase::get_duration() const
{
  return duration_;
}

UInt PulseSequenceBase::num_pulses() const
{
  return pulses_.size();
}

PulseSequenceBase::~PulseSequenceBase()
{
}

} // namespace SpinDec
