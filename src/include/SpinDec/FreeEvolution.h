#ifndef FREEEVOLUTION_H_
#define FREEEVOLUTION_H_

// SpinDec::FreeEvolution
//
// (Pulse)-free evolution.
//
// Seto Balian, Sep 1, 2014

#include "SpinDec/typedefs.h"
#include "SpinDec/Pulse.h"
#include "SpinDec/EvolutionOperator.h"

namespace SpinDec
{

class FreeEvolution : public Pulse
{
private:
  
  EvolutionOperator evolution_operator_;
  
  virtual void construct_pulse_operator();
  
public:
  FreeEvolution();
  // "pulse" duration taken from evolution operator
  FreeEvolution(const EvolutionOperator& evolution_operator);
  
  virtual std::auto_ptr<Pulse> clone() const;
  
};

} // namespace SpinDec

#endif // FREEEVOLUTION_H_
