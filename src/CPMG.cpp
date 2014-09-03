// See CPMG.h for description.
// Seto Balian, Sep 3, 2014

#include "SpinDec/CPMG.h"
#include "SpinDec/Errors.h"
#include "SpinDec/PiPulse.h"
#include "SpinDec/FreeEvolution.h"

#include <algorithm>

namespace SpinDec
{

CPMG::CPMG() : order_(0)
{
}

void CPMG::init(const PiPulse& pi_pulse)
{
  
  // construct the free evolution pulse
  FreeEvolution unitary_evolution(evolution_operator_);
  
  //FID
  if (order_ == 0) {
    add_pulse(unitary_evolution);
  } else {
    // Hahn (CPMG-1), CPMG-2, CPMG-3, ...
    
    for (UInt i=0;i<order_;i++) {

      add_pulse(unitary_evolution);
      add_pulse(pi_pulse);
      add_pulse(unitary_evolution);
      
    }
  }


}

CPMG::CPMG(const UInt order,const SpinState& state0, const SpinState& state1,
    const SpinState& initial_state,
    const EvolutionOperator& evolution_operator) :
    PulseSequence(initial_state), order_(order)
{
  
  state0_ = state0;
  state1_ = state1;
  evolution_operator_ = evolution_operator;
  
  // construct the pi pulse (also checks |0> and |1> bases)
  PiPulse  pi_pulse(state0,state1);  
  init(pi_pulse);

}

CPMG::CPMG(const UInt order, const SpinState& state0, const SpinState& state1,
    const SpinState& initial_state, const SpinState& unaffected_state,
    const EvolutionOperator& evolution_operator)
: PulseSequence(initial_state), order_(order)
{

  state0_ = state0;
  state1_ = state1;
  unaffected_state_ = unaffected_state;
  evolution_operator_ = evolution_operator;
  
  // construct the pi pulse (also checks |0> and |1> bases)
  PiPulse  pi_pulse(state0,state1,unaffected_state);
  init(pi_pulse);
  
}

CPMG::CPMG(const UInt order, const SpinState& state0, const SpinState& state1,
    const vector<SpinState>& states2_plus, const SpinState& initial_state,
    const SpinState& unaffected_state,
    const EvolutionOperator& evolution_operator)
: PulseSequence(initial_state), order_(order)
{
  
  state0_ = state0;
  state1_ = state1;
  states2_plus_ = states2_plus;
  unaffected_state_ = unaffected_state;
  evolution_operator_ = evolution_operator;
  
  // construct the pi pulse (also checks |0> and |1> bases)
  PiPulse  pi_pulse(state0,state1,states2_plus,unaffected_state);
  init(pi_pulse);
  
}

void CPMG::update(const double time)
{
  
  // update the free evolution pulse
  evolution_operator_.set_time(time);
  FreeEvolution unitary_evolution(evolution_operator_);
  
  //FID
  if (order_ == 0) {
    pulses_[0] = unitary_evolution;
  } else {
    // Hahn (CPMG-1), CPMG-2, CPMG-3, ...
    UIntArray indices;
    
    for (UInt i=0;i<order_;i++) {
      indices.push_back(1+3*i);
    }
    
    // TODO make sure this is working and is efficient
    for (UInt i=0;i<pulses_.size();i++) {
      if (std::find(indices.begin(), indices.end(),i)!=indices.end()) {
        continue;
      } // else
      pulses_[i] = unitary_evolution;
    }
    
  }
  return;
}

std::auto_ptr<PulseSequence> CPMG::clone() const
{
  return std::auto_ptr<PulseSequence>(new CPMG(*this));
}

const SpinState& CPMG::get_state0() const
{
  return state0_;
}

const SpinState& CPMG::get_state1() const
{
  return state1_;
}


} // namespace SpinDec

