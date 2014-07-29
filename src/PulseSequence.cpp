// See PulseSequence.h for description.
// Seto Balian, Jul 29, 2014

#include "SpinDec/PulseSequence.h"

namespace SpinDec
{

PulseSequence::PulseSequence()
{
}

PulseSequence::PulseSequence(const SpinState& initial_state)
{
  initial_state_ = initial_state;
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

