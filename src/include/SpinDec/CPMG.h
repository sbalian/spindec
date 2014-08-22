#ifndef CPMG_H_
#define CPMG_H_

// SpinDec::CPMG
//
// Carr-Purcell-Meiboom-Gill (CPMG) pulse sequence.
// - order 0 (FID)
//   evolve, t (duration t)
// - order 1 (Hahn)
//   evolve, t/2 > pi-pulse > evolve, t/2 > measure
// - order n >= 1
//   evolve, t/2n > pi-pulse > evolve, t/2n, ... ,
//   > evolve, t/2n >pi-pulse, evolve, t/2n> measure
//
// Seto Balian, Aug 4, 2014

#include "SpinDec/typedefs.h"
#include "SpinDec/PulseSequence.h"
#include "SpinDec/PiPulse.h"
#include "SpinDec/SpinHamiltonian.h"
#include "SpinDec/SpinSystemBase.h"
#include "SpinDec/TimeArray.h"
#include "SpinDec/SpinDonor.h"
#include "SpinDec/SpinSystem.h"

namespace SpinDec
{

class CPMG : public PulseSequence
{
private:
  PiPulse pi_pulse_;
  UInt order_;
  double time_gap_;
  
  SpinState state0_;
  SpinState state1_;
  vector<SpinState> other_states_;
  vector<SpinState> states_to_trace_out_;
  
  SpinHamiltonian hamiltonian_;
  ComplexMatrix eigenvectors_;
  RealVector eigenvalues_;
  
  bool is_pi_pulse_constructed_;
  
public:
  
  CPMG();
  CPMG(const UInt order,
       const SpinState & state0,
       const SpinState & state1,
       const std::auto_ptr<SpinSystemBase> & spin_system_base);
  
  CPMG(const UInt order,
       const UInt lower_donor_level,
       const UInt upper_donor_level,
       const SpinDonor & spin_donor,
       const SpinSystem & combined_spin_system);
  
  void add_state_to_trace_out(const SpinState& state_to_trace_out);
  void add_other_state(const SpinState& other_state);
  
  virtual void calculate(const SpinState& initial_state,
       const double duration);
  
  // TODO Comment this
  CDouble decay_experiment(const SpinState& initial_state,
       const double duration);
  CDoubleArray decay_experiment(
      const SpinState& initial_state, const TimeArray& time_array);
  
};

} // namespace SpinDec

#endif // CPMG_H_
