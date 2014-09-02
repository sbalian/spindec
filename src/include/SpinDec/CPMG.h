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
// Seto Balian, Sep 2, 2014

#include "SpinDec/typedefs.h"
#include "SpinDec/PulseSequence.h"
#include "SpinDec/EvolutionOperator.h"
#include "SpinDec/SpinState.h"
#include "SpinDec/PiPulse.h"
#include "SpinDec/FreeEvolution.h"

namespace SpinDec
{

class CPMG : public PulseSequence
{
private:
  void init(const PiPulse& pi_pulse);
  
  UInt order_;
  SpinState state0_;
  SpinState state1_;
  vector<SpinState> states2_plus_;
  SpinState unaffected_state_;
  EvolutionOperator evolution_operator_;
  
public:
  
  CPMG();
  CPMG(const UInt order,const SpinState& state0, const SpinState& state1,
      const SpinState& initial_state,
      const EvolutionOperator& evolution_operator);
  CPMG(const UInt order,const SpinState& state0, const SpinState& state1,
      const SpinState& initial_state,
      const SpinState& unaffected_state,
      const EvolutionOperator& evolution_operator);
  CPMG(const UInt order,const SpinState& state0, const SpinState& state1,
      const vector<SpinState>& states2_plus,
      const SpinState& initial_state,
      const SpinState& unaffected_state,
      const EvolutionOperator& evolution_operator);
  
  const SpinState& get_state0() const;
  const SpinState& get_state1() const;

  virtual void update(const double time);
  virtual std::auto_ptr<PulseSequence> clone() const;
  
};

} // namespace SpinDec

#endif // CPMG_H_
