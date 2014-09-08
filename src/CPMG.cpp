// See CPMG.h for description.
// Seto Balian, Sep 8, 2014

#include "SpinDec/CPMG.h"
#include "SpinDec/Errors.h"
#include "SpinDec/FreeEvolution.h"

namespace SpinDec
{

CPMG::CPMG() : order_(0)
{
}

CPMG::CPMG(const UInt order,
    const PiPulse& pi_pulse,
    const EvolutionOperator& evolution_operator):
    PulseSequenceBase(),
    order_(order)
{
  
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

std::auto_ptr<PulseSequenceBase> CPMG::clone() const
{
  return std::auto_ptr<PulseSequenceBase>(new CPMG(*this));
}

} // namespace SpinDec

