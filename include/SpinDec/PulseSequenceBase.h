#ifndef PULSESEQUENCEBASE_H_
#define PULSESEQUENCEBASE_H_

// SpinDec::PulseSequenceBase
//
// Abstract base class for pulse sequences.
//
// Seto Balian, Nov 6, 2014

#include "SpinDec/typedefs.h"
#include "SpinDec/Pulse.h"
#include "SpinDec/SpinState.h"

namespace SpinDec
{

class PulseSequenceBase
{
protected:
  
  vector<Pulse> pulses_;
  double duration_;

public:
  
  PulseSequenceBase();
  
  SpinState final_state(const SpinState& initial_state) const;
  
  double get_duration() const;
  
  UInt num_pulses() const;
  
  virtual auto_ptr<PulseSequenceBase> clone() const = 0;
  
  virtual ~PulseSequenceBase();
  
};

} // namespace SpinDec

#endif // PULSESEQUENCEBASE_H_
