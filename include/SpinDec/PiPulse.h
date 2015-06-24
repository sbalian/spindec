#ifndef PIPULSE_H_
#define PIPULSE_H_

// Seto Balian, Jun 24, 2015

#include "SpinDec/typedefs.h"
#include "SpinDec/Pulse.h"

namespace SpinDec
{

/**
 * \brief \f$\pi\f$-pulse or refocusing pulse.
 * 
 * \f$ \left | 0 \right \rangle \left\langle 1 \right |  + 
   \left | 1 \right \rangle \left\langle 0 \right |\f$.
 * 
 */
class PiPulse : public Pulse
{
public:
  PiPulse();
  /// Instantaneous.
  PiPulse(const SpinState & state0, const SpinState & state1);
  
  /**
   * Third parameter: these just add
   * \f$ \left | n \right \rangle \left\langle n \right | \f$ for
   * \f$ n = 2,3, \dots \f$
   */
  PiPulse(const SpinState & state0, const SpinState & state1,
      const vector<SpinState>& states2_plus);
  
};

} // namespace SpinDec

#endif // PIPULSE_H_
