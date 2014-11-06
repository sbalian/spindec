#ifndef FREEEVOLUTION_H_
#define FREEEVOLUTION_H_

// SpinDec::FreeEvolution
//
// (Pulse)-free evolution.
//
// Seto Balian, Nov 6, 2014

#include "SpinDec/typedefs.h"
#include "SpinDec/Pulse.h"
#include "SpinDec/EvolutionOperator.h"

namespace SpinDec
{

class FreeEvolution : public Pulse
{
  
public:
  FreeEvolution();
  // "pulse" duration taken from evolution operator
  FreeEvolution(const EvolutionOperator& evolution_operator);
  
  
};

} // namespace SpinDec

#endif // FREEEVOLUTION_H_
