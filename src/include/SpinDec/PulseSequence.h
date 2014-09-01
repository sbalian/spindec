#ifndef PULSESEQUENCE_H_
#define PULSESEQUENCE_H_

// SpinDec::PulseSequence
//
// Abstract base class for pulse sequences.
//
// Seto Balian, Sep 1, 2014

#include "SpinDec/typedefs.h"
#include "SpinDec/SpinState.h"

namespace SpinDec
{

class PulseSequence
{
protected:
  
  SpinState initial_state_;
  SpinState final_state_; 
  double duration_;
  
public:
  
  PulseSequence();
  PulseSequence(const SpinState& initial_state);
    
  const SpinState& get_initial_state() const;
  
  void add_pulse(const std::auto_ptr<Pulse> )
  
  void set_initial_state(const SpinState& initial_state) const;
  void set_initial_state(const SpinState& initial_state) const;
  
  virtual const SpinState& get_final_state() const = 0;
  
  virtual std::auto_ptr<PulseSequence> clone() const = 0;
  
  virtual ~PulseSequence();

};

} // namespace SpinDec

#endif // PULSESEQUENCE_H_
