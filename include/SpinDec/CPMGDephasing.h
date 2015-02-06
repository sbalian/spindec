#ifndef CPMGDEPHASING_H_
#define CPMGDEPHASING_H_

// SpinDec::CPMGDephasing
//
// CPMG pulse sequence.
//
// Seto Balian, Feb 4, 2015

#include "SpinDec/typedefs.h"
#include "SpinDec/PulseExperiment.h"
#include "SpinDec/TwoStateSuperposition.h"

namespace SpinDec
{

class CPMGDephasing : public PulseExperiment
{

private:
  UInt cpmg_order_;
  TwoStateSuperposition initial_system_state_;
  PiPulse system_pi_pulse_;
  
  vector< pair< UInt, Pulse > > pulses_;

public:

  CPMGDephasing();
  CPMGDephasing(const CSDProblem& csd_problem,
      const TimeArray& time_array, const UInt cpmg_order,
      const CDouble& c0, const UInt level_label0,
      const CDouble& c1, const UInt level_label1);

  virtual TimeEvolution time_evolution(const UIntArray bath_indices);

  virtual auto_ptr<PulseExperiment> clone() const;

};

} // namespace SpinDec

#endif // CPMGDEPHASING_H_
