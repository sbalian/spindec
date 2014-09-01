// See Pulse.h for description.
// Seto Balian, Sep 1, 2014

#include "SpinDec/Pulse.h"
#include "SpinDec/Errors.h"

namespace SpinDec
{

Pulse::Pulse() : duration_(0.0)
{
}

Pulse::Pulse(const double duration) : duration_(duration)
{
}

const SpinOperator& Pulse::get_pulse_operator() const
{
  return pulse_operator_;
}

Pulse::~Pulse()
{
}

} // namespace SpinDec

