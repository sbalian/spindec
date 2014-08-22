// See CCE.h for description.
// Seto Balian, Aug 22, 2014

#include "SpinDec/CCE.h"

namespace SpinDec
{

CCE::CCE() : truncation_order_(0)
{
}

CCE::CCE(const UInt truncation_order,
    const auto_ptr<SpinSystemBase>& central_spin_system_base,
    const SpinBath& spin_bath, const UInt interaction_label1,
    const UInt interaction_label2, const auto_ptr<SpinInteraction>& interaction,
    const UniformMagneticField& field) : truncation_order_(truncation_order)
{
  
  central_spin_system_ = SpinSystem(central_spin_system_base->get_graph(),
      central_spin_system_base->get_field());
  spin_bath_ = spin_bath;
    
  SpinInteractionGraph combined_graph = central_spin_system_.get_graph();
  
  combined_graph.join_in_place(spin_bath.get_graph());
  add_system_bath_interaction(interaction_label1,interaction_label2,
        interaction->clone());
  
  field_ = field;
  combined_spin_system_ = SpinSystem(combined_graph,field_);
  
}

void CCE::add_system_bath_interaction(
    const UInt interaction_label1, const UInt interaction_label2,
    const auto_ptr<SpinInteraction>& interaction)
{
  SpinInteractionGraph graph = combined_spin_system_.get_graph();
  graph.add_edge(interaction_label1,interaction_label2,
      interaction->clone());
  combined_spin_system_ = SpinSystem(graph,field_);
  return;
}

void CCE::solve()
{
  return;
}

} // namespace SpinDec
