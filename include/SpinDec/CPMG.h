#ifndef CPMG_H_
#define CPMG_H_

// Seto Balian, Jun 24, 2015

#include "SpinDec/typedefs.h"
#include "SpinDec/PulseSequenceBase.h"
#include "SpinDec/EvolutionOperator.h"
#include "SpinDec/Pulse.h"

namespace SpinDec
{

/**
 * \brief Carr-Purcell-Meiboom-Gill (CPMG) pulse sequence.
 * 
 * - Order \f$ N=0 \f$ (FID): evolve for duration \f$ t \f$.
 * - \f$ N=1 \f$ (Hahn): evolve for \f$ t/2 \f$, \f$\pi\f$-pulse, evolve
 * for \f$ t/2 \f$.
 * - \f$ N > 1 \f$: [evolve for \f$t/(2N)\f$, \f$\pi\f$-pulse,
 * evolve for \f$t/(2N)\f$]\f$ ^{N} \f$.
 * 
 */
class CPMG : public PulseSequenceBase
{
private:
  
  UInt order_;
  EvolutionOperator evolution_operator_;
  vector<bool> is_unitary_;
  
public:
  
  CPMG();

  // TODO make this into a PiPulse, and put basis for identity?
  CPMG(const UInt order,
      const EvolutionOperator& evolution_operator,
      const Pulse& pi_pulse);
  
  void set_time(const double time_value);
  
  virtual shared_ptr<PulseSequenceBase> clone() const;
  
};

} // namespace SpinDec

#endif // CPMG_H_
