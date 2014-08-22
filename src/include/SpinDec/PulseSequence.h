#ifndef PULSESEQUENCE_H_
#define PULSESEQUENCE_H_

// SpinDec::PulseSequence
//
// Abstract base class for pulse sequences.
//
// Seto Balian, Aug 1, 2014

#include "SpinDec/typedefs.h"
#include "SpinDec/SpinState.h"

namespace SpinDec
{

class PulseSequence
{
protected:
  SpinState initial_state_; // TODO decide if this should be a member,
                            // store just the basis perhaps ...
  SpinState final_state_;
  
  double duration_;
  
public:
  
  PulseSequence();
  PulseSequence(const SpinState& initial_state,
      const double duration);
  
  const SpinState& get_initial_state() const;
  const SpinState& get_final_state() const;
  
  virtual void calculate(const SpinState& initial_state,
               const double duration) = 0;
  
  virtual ~PulseSequence();

};

} // namespace SpinDec

#endif // PULSESEQUENCE_H_
