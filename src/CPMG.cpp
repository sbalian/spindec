// See CPMG.h for description.
// Seto Balian, Oct 23, 2014

#include "SpinDec/CPMG.h"
#include "SpinDec/Errors.h"
#include "SpinDec/FreeEvolution.h"

namespace SpinDec
{

CPMG::CPMG() : order_(0)
{
}

CPMG::CPMG(const UInt order,
    const EvolutionOperator& evolution_operator,
    const Pulse& pi_pulse):
    PulseSequenceBase(),
    order_(order)
{
  
  evolution_operator_ = evolution_operator;
  
  if (!pi_pulse.get_pulse_operator().is_basis_equal(
      evolution_operator.clone())) {
    Errors::quit("Evolution and pi-pulse operators have different bases.");
  }

  
  // construct the free evolution pulse
  FreeEvolution unitary_evolution(evolution_operator);

  //FID
  if (order_ == 0) {
    pulses_.push_back(unitary_evolution);
    duration_ += unitary_evolution.get_duration();
  } else {
    // Hahn (CPMG-1), CPMG-2, CPMG-3, ...
    
    for (UInt i=0;i<order_;i++) {

      pulses_.push_back(unitary_evolution);
      duration_ += unitary_evolution.get_duration();
      pulses_.push_back(pi_pulse);
      duration_ += pi_pulse.get_duration();
      pulses_.push_back(unitary_evolution);
      duration_ += unitary_evolution.get_duration();
      
    }
  }

}

void CPMG::set_time(const double time_value)
{
  //FID
  
  duration_ = 0.0;
  
  evolution_operator_.set_time(time_value);
  
  FreeEvolution unitary_evolution(evolution_operator_);
  
  if (order_ == 0) {
    pulses_[0] = unitary_evolution;
    duration_ += unitary_evolution.get_duration();
  } else {
    // Hahn (CPMG-1), CPMG-2, CPMG-3, ...
    
    for (UInt i=0;i<order_;i++) {
      
      pulses_[i] = unitary_evolution;
      duration_ += unitary_evolution.get_duration();
      
      duration_ += pulses_[i+1].get_duration();
      
      pulses_[i+2] = unitary_evolution;
      duration_ += unitary_evolution.get_duration();
      
    }
  }

}


auto_ptr<PulseSequenceBase> CPMG::clone() const
{
  return auto_ptr<PulseSequenceBase>(new CPMG(*this));
}

} // namespace SpinDec

