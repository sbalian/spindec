#ifndef PIPULSE_H_
#define PIPULSE_H_

// SpinDec::PiPulse
//
// Pi (refocusing) pulse.
// [ |0X1| + |1X0| ]
//
// Seto Balian, Sep 1, 2014

#include "SpinDec/typedefs.h"
#include "SpinDec/Pulse.h"

namespace SpinDec
{

class PiPulse : public Pulse
{
private:
  
  SpinState state0_;
  SpinState state1_;
  
  virtual void construct_pulse_operator();
  
public:
  PiPulse();
  // instantaneous
  PiPulse(const SpinState & state0, const SpinState & state1);
  
  virtual std::auto_ptr<Pulse> clone() const;
  
};

} // namespace SpinDec

#endif // PIPULSE_H_
