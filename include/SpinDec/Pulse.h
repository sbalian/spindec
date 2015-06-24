#ifndef PULSE_H_
#define PULSE_H_

// Seto Balian, Jun 24, 2015

#include "SpinDec/typedefs.h"
#include "SpinDec/SpinState.h"
#include "SpinDec/SpinOperator.h"

namespace SpinDec
{

/**
 * \brief Pulses in a pulse sequence.
 * 
 * Includes the no-pulse free evolution.
 */
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
  
  Pulse operator*(const Pulse& pulse) const;
  Pulse operator^(const Pulse& pulse) const;
  
};

} // namespace SpinDec

#endif // PULSE_H_
