// See Pulse.h for description.
// Seto Balian, Sep 2, 2014

#include "SpinDec/Pulse.h"
#include "SpinDec/Errors.h"

namespace SpinDec
{

Pulse::Pulse() : duration_(0.0)
{
}

SpinDec::Pulse::Pulse(const double duration, const SpinOperator& pulse_operator)
{
  duration_ = duration;
  pulse_operator_ = pulse_operator;
}

const SpinOperator& Pulse::get_pulse_operator() const
{
  return pulse_operator_;
}

double Pulse::get_duration() const
{
  return duration_;
}

} // namespace SpinDec

