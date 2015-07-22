// See PulseSequence.h for description.
// Seto Balian, Nov 6, 2014

#include "SpinDec/PulseSequence.h"
#include "SpinDec/Errors.h"

namespace SpinDec
{

PulseSequence::PulseSequence() : PulseSequenceBase()
{
}

void PulseSequence::add_pulse(const Pulse& pulse)
{
  
  if (num_pulses() == 0) {
    pulses_.push_back(pulse);
    duration_+=pulse.get_duration();
    return;
  }
  
  if (!pulse.get_pulse_operator().is_basis_equal(
      pulses_[0].get_pulse_operator().clone())) {
    Errors::quit("Invalid pulse operator basis.");
  }
  
  pulses_.push_back(pulse);
  duration_+=pulse.get_duration();
  
  return;
}

void PulseSequence::clear()
{
  pulses_.clear();
  duration_ = 0.0;
}

shared_ptr<PulseSequenceBase> PulseSequence::clone() const
{
  return shared_ptr<PulseSequenceBase>( new PulseSequence(*this));
}


} // namespace SpinDec

