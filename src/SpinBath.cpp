// See SpinBath.h for description.
// Seto Balian, Aug 22, 2014

#include "SpinDec/SpinBath.h"
#include "SpinDec/RandomNumberGenerator.h"

namespace SpinDec
{

SpinBath::SpinBath()
{
}

SpinBath::SpinBath(const CrystalStructure& crystal_structure,
    const auto_ptr<SpinSystemBase>& spin_system_base,
    const UInt interaction_label1,
    const UInt interaction_label2,
    const  auto_ptr<SpinInteraction> & interaction)
{
  
  // Prepare bath states
  UInt dimension = spin_system_base->get_hamiltonian().get_dimension();
  
  for (UInt i=0;i<crystal_structure.num_site_vectors();i++) {
    UInt random_number = 
        RandomNumberGenerator::uniform_c_rand(0,dimension-1);
    
    SpinState to_add(
        spin_system_base->get_eigenvector_matrix().col(random_number),
        spin_system_base->get_hamiltonian().get_basis());
    
    states_.push_back(to_add);
    
  }
  
  // graph
  graph_ = spin_system_base->get_graph();
  
  // add interaction
  add_intrabath_interaction(interaction_label1,interaction_label2,
      interaction->clone());
  
  return;
  
}

void SpinBath::add_intrabath_interaction(const UInt interaction_label1,
    const UInt interaction_label2,
    const auto_ptr<SpinInteraction> & interaction)
{
  
  graph_.join_in_place(graph_);
  graph_.add_edge(interaction_label1,interaction_label2,interaction->clone());
  
  return;
}

const SpinState& SpinBath::get_state(const UInt index) const
{
  return states_[index];
}

UInt SpinBath::num_spins() const
{
  return states_.size();
}

const SpinInteractionGraph& SpinBath::get_graph() const
{
  return graph_;
}

} // namespace SpinDec

