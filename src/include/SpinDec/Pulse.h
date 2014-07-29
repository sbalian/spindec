#ifndef PULSE_H_
#define PULSE_H_

// SpinDec::Pulse
//
// Abstract base class for pulses in a pulse sequence.
//
// Seto Balian, Jul 29, 2014

#include "SpinDec/typedefs.h"
#include "SpinDec/SpinState.h"
#include "SpinDec/SpinOperator.h"

namespace SpinDec
{

class Pulse
{
protected:
  SpinState state0_;
  SpinState state1_;
  
  double duration_;
  
  SpinOperator pulse_operator_;
  
  // sets
  virtual void construct_pulse_operator() = 0;
  
public:
  Pulse();
  Pulse(const SpinState & state0, const SpinState & state1,
      const double duration);
  
  const SpinOperator& get_pulse_operator() const;
  
  virtual ~Pulse();
  
};

} // namespace SpinDec

#endif // PULSE_H_
