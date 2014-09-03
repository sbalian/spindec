// See PulseExperiment.h for description.
// Seto Balian, Sep 3, 2014

#include "SpinDec/PulseExperiment.h"

namespace SpinDec
{

PulseExperiment::PulseExperiment()
{
}

PulseExperiment::PulseExperiment(
    const auto_ptr<PulseSequence>& pulse_sequence, const TimeArray& time_array)
{
  pulse_sequence_ = pulse_sequence->clone();
}

PulseExperiment::~PulseExperiment()
{
}

PulseExperiment::PulseExperiment(const PulseExperiment& other)
{
  *this = other;
}

PulseExperiment& PulseExperiment::operator =(
  const PulseExperiment& other)
{
  pulse_sequence_ = other.pulse_sequence_->clone();
  time_array_ = other.time_array_;
  return *this;
}

const TimeArray& SpinDec::PulseExperiment::get_time_array() const
{
  return time_array_;
}


} // namespace SpinDec

