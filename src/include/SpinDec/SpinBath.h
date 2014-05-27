#ifndef SPINBATH_H_
#define SPINBATH_H_

// SpinDec::SpinBath
//
// Spin bath for the central spin decoherence problem in a crystal.
// This is a spin bath of just a single spin system, e.g. a donor
// or a single spin like a nucleus. Also, intrabath interaction is
// confined to a single interaction type. Also, it is assumed that the
// temperature of the bath is infinite such as for example for a spin-1/2 bath,
// there is an equal probablity of the spin-up/spin-down states in the initial
// state unentangled with the central spin system.
//
// TODO generalize
//
// Seto Balian, May 22, 2014

#include "SpinDec/typedefs.h"

#include "SpinDec/SpinInteractionGraph.h"
#include "SpinDec/CrystalStructure.h"

namespace SpinDec
{

class SpinBath
{
private:
  
  // this is the bath spin system
  SpinInteractionGraph graph_;
  // this is the interaction between bath spin systems
  SpinInteractionEdge itrabath_interaction_;
  // this is the crystal structure
  CrystalStructure crystal_structure_;

public:
  SpinBath();
  // Constructs a spin bath with spins on all the crystal sites (usually with
  // some fractional abundance - see CrystalStructure) and the interaction
  // among all bath spin systems, forming joined graphs: e.g. for two bath spin
  // systems: joined graph - intrabath_interaction - graph

  SpinBath(const SpinInteractionGraph & graph,
      const SpinInteractionEdge & intrabath_interaction,
      const CrystalStructure & crystal_structure);

};

} // namespace SpinDec

#endif // SPINBATH_H_
