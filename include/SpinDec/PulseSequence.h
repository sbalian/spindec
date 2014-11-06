#ifndef PULSESEQUENCE_H_
#define PULSESEQUENCE_H_

// SpinDec::PulseSequence
//
// Concrete general pulse sequence.
//
// Seto Balian, Nov 6, 2014

#include "SpinDec/typedefs.h"
#include "SpinDec/PulseSequenceBase.h"

namespace SpinDec
{

class PulseSequence : public PulseSequenceBase
{

public:
  
  PulseSequence();
  
  void clear();
  void add_pulse(const Pulse& pulse);
  
  virtual auto_ptr<PulseSequenceBase> clone() const;
  
};

} // namespace SpinDec

#endif // PULSESEQUENCE_H_
