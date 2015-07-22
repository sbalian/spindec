#ifndef PULSESEQUENCE_H_
#define PULSESEQUENCE_H_

// Seto Balian, Jun 24, 2015

#include "SpinDec/typedefs.h"
#include "SpinDec/PulseSequenceBase.h"

namespace SpinDec
{

/// Concrete general pulse sequence.
class PulseSequence : public PulseSequenceBase
{

public:
  
  PulseSequence();
  
  void clear();
  void add_pulse(const Pulse& pulse);
  
  virtual shared_ptr<PulseSequenceBase> clone() const;
  
};

} // namespace SpinDec

#endif // PULSESEQUENCE_H_
