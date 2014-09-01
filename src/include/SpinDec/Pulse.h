#ifndef PULSE_H_
#define PULSE_H_

// SpinDec::Pulse
//
// Abstract base class for pulses in a pulse sequence.
// Includes the no-pulse free evolution.
//
// Seto Balian, Sep 1, 2014

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
  
  // sets
  virtual void construct_pulse_operator() = 0;
  
public:
  Pulse();
  explicit Pulse(const double duration);
  
  const SpinOperator& get_pulse_operator() const;
  
  virtual std::auto_ptr<Pulse> clone() const = 0;
  
  virtual ~Pulse();
  
};

} // namespace SpinDec

#endif // PULSE_H_
