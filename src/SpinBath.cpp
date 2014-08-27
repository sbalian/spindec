// See SpinBath.h for description.
// Seto Balian, Aug 27, 2014

#include "SpinDec/SpinBath.h"
#include "SpinDec/RandomNumberGenerator.h"
#include "SpinDec/Errors.h"

namespace SpinDec
{


void SpinDec::SpinBath::init(const CrystalStructure& crystal_structure,
    const auto_ptr<SpinSystemBase>& spin_system_base,
    const vector<SpinInteractionEdge>& intrabath_edges)
{
  // Save spin system base as a spin system
  // TODO rediagonalization here ...
  spin_system_ = SpinSystem(spin_system_base->get_graph(),
      spin_system_base->get_field());
  
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
  
  // intrabath interaction
  intrabath_edges_ = intrabath_edges;
  
  // crystal structure
  crystal_structure_ = crystal_structure;
  
  return;
}


SpinBath::SpinBath()
{
}

SpinBath::SpinBath(const CrystalStructure& crystal_structure,
    const auto_ptr<SpinSystemBase>& spin_system_base,
    const vector<SpinInteractionEdge>& intrabath_edges)
{
  init(crystal_structure,spin_system_base,intrabath_edges);
}

SpinBath::SpinBath(const CrystalStructure& crystal_structure,
    const auto_ptr<SpinSystemBase>& spin_system_base,
    const SpinInteractionEdge& intrabath_edge)
{
  vector<SpinInteractionEdge> intrabath_edges;
  intrabath_edges.push_back(intrabath_edge);
  init(crystal_structure,spin_system_base,intrabath_edges);
}

const SpinState& SpinBath::get_state(const UInt index) const
{
  return states_[index];
}

UInt SpinBath::num_spins() const
{
  return states_.size();
}

SpinState SpinBath::get_state(const UIntArray& indices) const
{
  SpinState out = get_state(indices[0]);
  for (UInt i=1;i<indices.size();i++) {
    out = out^get_state(indices[i]);
  }
  return out;
}


const CrystalStructure& SpinBath::get_crystal_structure() const
{
  return crystal_structure_;
}


const vector<SpinInteractionEdge>& SpinBath::get_intrabath_edges() const
{
  return intrabath_edges_;
}

const SpinSystem& SpinBath::get_spin_system() const
{
  return spin_system_;
}

ThreeVector SpinDec::SpinBath::get_position(const UInt vertex_label,
    const UInt index) const
{
  // TODO make sure this does not involve bad inits/values for positions ...
  return crystal_structure_.get_site_vector(index) +
      spin_system_.get_graph().get_position(vertex_label);
}

vector<SpinInteractionEdge> SpinBath::intrabath_edges(
    const UInt order,
    const SpinInteractionEdge& intrabath_edge,
    const UInt num_vertices) const
{
  
  if (order == 0) {
    Errors::quit("Order must be +ve non-zero integer.");
  }
  
  if (num_vertices <= 1) {
    Errors::quit("Need at least two vertices for an edge.");
  }
  
  // TODO you are here
  vector<SpinInteractionEdge> edges;
  for (UInt i=0;i<order-1;i++) {
    
  }
  
  
  
}


} // namespace SpinDec

