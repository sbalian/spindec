#ifndef PULSE_H_
#define PULSE_H_

// SpinDec::Pulse
//
// Pulses in a pulse sequence.
// Includes the no-pulse free evolution.
//
// Seto Balian, Sep 2, 2014

#include "SpinDec/typedefs.h"
#include "SpinDec/SpinState.h"
#include "SpinDec/SpinOperator.h"

namespace SpinDec
{

class Pulse
{
protected:
  
  double duration_;
  SpinOperator pulse_operator_;
  
public:
  
  Pulse();
  Pulse(const double duration, const SpinOperator& pulse_operator);
  
  const SpinOperator& get_pulse_operator() const;
  double get_duration() const;
  
};

} // namespace SpinDec

#endif // PULSE_H_
