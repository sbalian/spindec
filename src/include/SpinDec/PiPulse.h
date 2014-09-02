#ifndef PIPULSE_H_
#define PIPULSE_H_

// SpinDec::PiPulse
//
// Pi (refocusing) pulse.
// [ |0X1| + |1X0| ]
//
// Seto Balian, Sep 2, 2014

#include "SpinDec/typedefs.h"
#include "SpinDec/Pulse.h"

namespace SpinDec
{

class PiPulse : public Pulse
{
public:
  PiPulse();
  // instantaneous
  PiPulse(const SpinState & state0, const SpinState & state1);
  PiPulse(const SpinState & state0, const SpinState & state1,
      const SpinState& unaffected_state);
  PiPulse(const SpinState & state0, const SpinState & state1,
      const vector<SpinState> states2_plus,
      // these just add |nXn| for n=2,3,...
      const SpinState& unaffected_state);
  
};

} // namespace SpinDec

#endif // PIPULSE_H_
