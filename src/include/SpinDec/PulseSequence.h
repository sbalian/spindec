#ifndef PULSESEQUENCE_H_
#define PULSESEQUENCE_H_

// SpinDec::PulseSequence
//
// Abstract base class for general pulse sequence.
//
// Seto Balian, Sep 3, 2014

#include "SpinDec/typedefs.h"
#include "SpinDec/SpinState.h"
#include "SpinDec/Pulse.h"

namespace SpinDec
{

class PulseSequence
{
protected:
  
  SpinState initial_state_;

  vector<Pulse> pulses_;
  double duration_;

public:
  
  PulseSequence();
  
  explicit PulseSequence(const SpinState& initial_state);
  
  void add_pulse(const Pulse& pulse);
  void set_initial_state(const SpinState& initial_state);
  
  const SpinState& get_initial_state() const;
  SpinState final_state() const;
  SpinState final_state(const SpinState& initial_state);
  
  double get_duration() const;
  
  virtual void update(const double time) = 0;
  
  virtual std::auto_ptr<PulseSequence> clone() const = 0;
  
  virtual ~PulseSequence();
  
};

} // namespace SpinDec

#endif // PULSESEQUENCE_H_
