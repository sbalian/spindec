#ifndef PIPULSE_H_
#define PIPULSE_H_

// SpinDec::PiPulse
//
// Pi (refocusing) pulse.
// [ |0X1| + |1X0| + SUM_i ( |iXi| ) ] ^(tensor) identity
//
// Seto Balian, Jul 30, 2014

#include "SpinDec/typedefs.h"
#include "SpinDec/Pulse.h"

namespace SpinDec
{

class PiPulse : public Pulse
{
private:
  vector<SpinState> other_states_;
  virtual void construct_pulse_operator();
  
public:
  PiPulse();
  PiPulse(const SpinState & state0, const SpinState & state1,
      const vector<SpinState> & other_states,
      const vector<SpinState>& unaffected_states);
  
};

} // namespace SpinDec

#endif // PIPULSE_H_
