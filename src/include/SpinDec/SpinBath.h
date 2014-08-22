#ifndef SPINBATH_H_
#define SPINBATH_H_

// SpinDec::SpinBath
//
// Spin bath (of a single spin species) for the central spin decoherence
// problem in a crystal. Infinite temperature, so that all states are equally
// likely.
// TODO Generalize to finite temperature; Generalize for multiple spin species?
//      or use combinations of single-spin-species baths?
//
// Seto Balian, Aug 22, 2014

#include "SpinDec/typedefs.h"
#include "SpinDec/CrystalStructure.h"
#include "SpinDec/SpinSystemBase.h"
#include "SpinDec/SpinState.h"
#include "SpinDec/SpinInteraction.h"

namespace SpinDec
{

class SpinBath
{
private:
  vector<SpinState> states_;
  SpinInteractionGraph graph_;
  
public:
  SpinBath();
  SpinBath(const CrystalStructure& crystal_structure,
      const auto_ptr<SpinSystemBase>& spin_system_base,
      const UInt interaction_label1,
      const UInt interaction_label2,
      const  auto_ptr<SpinInteraction> & interaction);
  
  void add_intrabath_interaction(const UInt interaction_label1,
      const UInt interaction_label2,
      const auto_ptr<SpinInteraction> & interaction);
  
  const SpinState& get_state(const UInt index) const;
  UInt num_spins() const;
  
  const SpinInteractionGraph& get_graph() const;
  
};

} // namespace SpinDec

#endif // SPINBATH_H_
