// See PulseSequence.h for description.
// Seto Balian, Aug 1, 2014

#include "SpinDec/PulseSequence.h"

namespace SpinDec
{

PulseSequence::PulseSequence() : duration_(0.0)
{
}

PulseSequence::PulseSequence(const SpinState& initial_state,
    const double duration)
{
  initial_state_ = initial_state;
  final_state_ = SpinState(initial_state_.get_basis());
  duration_ = duration;
}

const SpinState& PulseSequence::get_initial_state() const
{
  return initial_state_;
}

const SpinState& PulseSequence::get_final_state() const
{
  return final_state_;
}

PulseSequence::~PulseSequence()
{
}

} // namespace SpinDec

