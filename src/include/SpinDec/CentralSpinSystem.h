#ifndef CENTRALSPINSYSTEM_H_
#define CENTRALSPINSYSTEM_H_

// SpinDec::CentralSpinSystem
//
// Central spin system for the central spin decoherence problem.
//
// Seto Balian, May 21, 2014

#include "SpinDec/typedefs.h"
#include "SpinDec/SpinInteractionGraph.h"

namespace SpinDec
{

class CentralSpinSystem
{
private:
  SpinInteractionGraph graph_;
  
public:
  
  CentralSpinSystem();
  CentralSpinSystem(const SpinInteractionGraph & graph);
  
};

} // namespace SpinDec

#endif // CENTRALSPINSYSTEM_H_
