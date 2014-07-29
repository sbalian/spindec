#ifndef PULSESEQUENCE_H_
#define PULSESEQUENCE_H_

// SpinDec::PulseSequence
//
// Abstract base class for pulse sequences.
//
// Seto Balian, Jul 29, 2014

#include "SpinDec/typedefs.h"
#include "SpinDec/SpinState.h"

namespace SpinDec
{

class PulseSequence
{
protected:
  SpinState initial_state_;
  SpinState final_state_;
  
public:
  
  PulseSequence();
  PulseSequence(const SpinState& initial_state);
  
  const SpinState& get_initial_state() const;
  const SpinState& get_final_state() const;
  
  virtual void calculate() = 0;
  
  virtual ~PulseSequence();
  
};

} // namespace SpinDec

#endif // PULSESEQUENCE_H_
