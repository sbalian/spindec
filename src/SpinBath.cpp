// See SpinBath.h for description.
// Seto Balian, Sep 26, 2014

#include "SpinDec/SpinBath.h"
#include "SpinDec/RandomNumberGenerator.h"
#include "SpinDec/Errors.h"

#include <algorithm>

namespace SpinDec
{

void SpinDec::SpinBath::init(const CrystalStructure& crystal_structure,
    const auto_ptr<SpinSystemBase>& spin_system_base,
    const vector<SpinInteractionEdge>& intrabath_edges)
{

  // Save spin system base as a spin system
  spin_system_base_ = spin_system_base->clone();
  
  // Prepare bath states
  UInt dimension = spin_system_base_->dimension();
  
  for (UInt i=0;i<crystal_structure.num_site_vectors();i++) {
    UInt random_number = 
        RandomNumberGenerator::uniform_c_rand(0,dimension-1);
    
    SpinState to_add(
        spin_system_base_->get_eigenvector_matrix().col(random_number),
        spin_system_base_->get_hamiltonian().get_basis());
    
    bath_states_.push_back(to_add);
    
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

const SpinState& SpinBath::get_bath_state(const UInt index) const
{
  return bath_states_[index];
}

UInt SpinBath::num_bath_states() const
{
  return bath_states_.size();
}

SpinState SpinBath::get_bath_product_state(const UIntArray& indices) const
{
  SpinState out = get_bath_state(indices[0]);
  for (UInt i=1;i<indices.size();i++) {
    out = out^get_bath_state(indices[i]);
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

auto_ptr<SpinSystemBase> SpinBath::get_spin_system() const
{
  return spin_system_base_->clone();
}

ThreeVector SpinDec::SpinBath::get_position(const UInt vertex_label,
    const UInt bath_index) const
{
  // TODO make sure this does not involve bad inits/values for positions ...
  return crystal_structure_.get_site_vector(bath_index) +
      spin_system_base_->
      get_hamiltonian().get_graph().get_position(vertex_label);
}

vector<SpinInteractionEdge> SpinBath::make_intrabath_edges(
    const UInt order,
    const SpinInteractionEdge& intrabath_edge) const
{
  
  if (order == 0) {
    Errors::quit("Order must be +ve non-zero integer.");
  }
  
  
  const UInt a = intrabath_edge.get_label1();
  const UInt b = intrabath_edge.get_label2();
    
  vector<SpinInteractionEdge> edges;
  
  // order = 1, return an empty edge vector
  if (order == 1) {
    return edges;
  }
  
  // otherwise
  UIntArray labels;
  
  // order 2
  labels.push_back(a);
  labels.push_back(b);
  
  // order above 2
  const UInt num_vertices = spin_system_base_->get_hamiltonian()
      .get_graph().num_vertices();

  for (UInt i=3;i<=order;i++) {
    labels.push_back(a+(i-2)*num_vertices);
    if (i!=order) {
      labels.push_back(b+(i-2)*num_vertices);
    }
  }
  
  for (UInt i=0;i<labels.size();i++) {
    UInt j = 0;
    while (j<i) {
      UIntArray pair;
      pair.push_back(labels[i]);
      pair.push_back(labels[j]);
      std::sort (pair.begin(), pair.end());
            
      edges.push_back( SpinInteractionEdge(
          pair[0],pair[1],intrabath_edge.get_interaction()) );
      j+=1;
    }
  }
  
  
  return edges;
  
}

vector<SpinInteractionEdge> SpinBath::make_intrabath_edges(
    const UInt order)
const
{
  
  vector<SpinInteractionEdge> edges;
  
  for (UInt i=0;i<intrabath_edges_.size();i++) {
    vector<SpinInteractionEdge> edges_i = make_intrabath_edges(order,
        intrabath_edges_[i]);
    
    for (UInt j=0;j<edges_i.size();j++) {
      edges.push_back(edges_i[j]);
    }
    
  }
    
  return edges;
  
}

SpinInteractionGraph SpinBath::reduced_problem_graph(
    const UInt order) const
{
  if (order == 0) {
    Errors::quit("Order must be +ve non-zero integer.");
  }
  
  
  SpinInteractionGraph single_system_graph =
      spin_system_base_->get_hamiltonian().get_graph();
  SpinInteractionGraph graph;
  
  graph = single_system_graph;
  
  if (order == 1) {
    return graph;
  }
  
  for (UInt i=2; i<=order;i++) {
    graph.join_in_place(single_system_graph);
  }
  
  
  graph.add_edges(make_intrabath_edges(order));

  
  return graph;
  
}

SpinBath::SpinBath(const SpinBath& spin_bath)
{
  *this = spin_bath;
}

SpinBath& SpinBath::operator =(const SpinBath& spin_bath)
{

  bath_states_ = spin_bath.bath_states_;
  spin_system_base_ = spin_bath.spin_system_base_->clone();
  intrabath_edges_ = spin_bath.intrabath_edges_;
  crystal_structure_ = spin_bath.crystal_structure_;
  
  return *this;

}


} // namespace SpinDec

