// See Pulse.h for description.
// Seto Balian, Nov 6, 2014

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

Pulse Pulse::operator *(const Pulse& pulse) const
{
  return Pulse(get_duration()+pulse.get_duration(), get_pulse_operator()
      + pulse.get_pulse_operator()) ;
}

Pulse SpinDec::Pulse::operator ^(const Pulse& pulse) const
{
  if (!(get_duration() == pulse.get_duration())) {
    Errors::quit("Pulse durations must be equal.");
  }
  return Pulse(get_duration(),get_pulse_operator()^pulse.get_pulse_operator());
}


} // namespace SpinDec

