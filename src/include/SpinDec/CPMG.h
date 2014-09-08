#ifndef CPMG_H_
#define CPMG_H_

// SpinDec::CPMG
//
// Carr-Purcell-Meiboom-Gill (CPMG) pulse sequence.
// - order 0 (FID)
//   evolve, t (duration t)
// - order 1 (Hahn)
//   evolve, t/2 > pi-pulse > evolve, t/2
// - order n >= 1
//   evolve, t/2n > pi-pulse > evolve, t/2n, ... ,
//   > evolve, t/2n >pi-pulse, evolve, t/2n
//
// Seto Balian, Sep 8, 2014

#include "SpinDec/typedefs.h"
#include "SpinDec/PulseSequenceBase.h"
#include "SpinDec/EvolutionOperator.h"
#include "SpinDec/PiPulse.h"

namespace SpinDec
{

class CPMG : public PulseSequenceBase
{
private:
  
  UInt order_;
  
public:
  
  CPMG();
  CPMG(const UInt order,
      const PiPulse& pi_pulse,
      const EvolutionOperator& evolution_operator);
  
  virtual std::auto_ptr<PulseSequenceBase> clone() const;
  
};

} // namespace SpinDec

#endif // CPMG_H_
