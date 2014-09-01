// See PulseSequence.h for description.
// Seto Balian, Sep 1, 2014

#include "SpinDec/PulseSequence.h"

namespace SpinDec
{

PulseSequence::PulseSequence() : duration_(0.0)
{
}

PulseSequence::PulseSequence(const SpinBasis& basis,
    const double duration)
{
  basis_ = basis;
  final_state_ = SpinState(basis_);
  duration_ = duration;
}

const SpinBasis& PulseSequence::get_basis() const
{
  return basis_;
}

const SpinState& PulseSequence::get_final_state() const
{
  return final_state_;
}

PulseSequence::~PulseSequence()
{
}

} // namespace SpinDec

