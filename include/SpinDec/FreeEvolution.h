#ifndef FREEEVOLUTION_H_
#define FREEEVOLUTION_H_

// Seto Balian, Jun 24, 2015

#include "SpinDec/typedefs.h"
#include "SpinDec/Pulse.h"
#include "SpinDec/EvolutionOperator.h"

namespace SpinDec
{

/// (Pulse)-free evolution.
class FreeEvolution : public Pulse
{
  
public:
  FreeEvolution();
  /// "Pulse" duration taken from evolution operator.
  FreeEvolution(const EvolutionOperator& evolution_operator);
  
};

} // namespace SpinDec

#endif // FREEEVOLUTION_H_
