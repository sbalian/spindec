// See SpinInteractionGraph.h for description.
// Seto Balian, Feb 10, 2014

#include "SpinInteractionGraph.h"
#include "Errors.h"

#include <algorithm>

namespace SpinDecoherence
{

// Check if vertex label exists
void SpinInteractionGraph::check_vertex_label(const unsigned int label) const
{
  if (label >= num_vertices()) {
    Errors::quit("Vertex does not exist.");
    return;
  }
  return;
}

void SpinInteractionGraph::check_edge_index(const unsigned int index) const
{
  if (index >= num_edges()) {
    Errors::quit("Edge does not exist.");
    return;
  }
  return;
}


SpinInteractionGraph::SpinInteractionGraph()
{
  num_vertices_ = 0;
  num_edges_ = 0;
}

void SpinInteractionGraph::add_vertex(const Spin& spin, const SpinState& state,
    const Eigen::Vector3d& position)
{
  spins_.push_back(spin);
  states_.push_back(state);
  positions_.push_back(position);
  join_basis_.push_back(false);
  num_vertices_++;
  return;
}

void SpinInteractionGraph::add_edge(unsigned int label1,
    unsigned int label2, SpinInteraction* interaction)
{
  
  // First check if labels exist
  check_vertex_label(label1);
  check_vertex_label(label2);
  
  // Swap such that label1 < label2
  if (label1 > label2)
  {
    std::swap(label1,label2);
  }
  
  vertex_labels1_.push_back(label1);
  vertex_labels2_.push_back(label2);
  interactions_.push_back(interaction);
  
  num_edges_++;
  
  return;
}

void SpinInteractionGraph::set_spin(const unsigned int label,
    const Spin & spin)
{
  check_vertex_label(label);
  spins_[label] = spin;
  return;
} 

void SpinInteractionGraph::set_position(const unsigned int label,
    const Eigen::Vector3d position)
{
  check_vertex_label(label);
  positions_[label] = position;
  return;
}

void SpinInteractionGraph::set_state(const unsigned int label,
    const SpinState & state)
{
  check_vertex_label(label);
  states_[label] = state;
  return;
}

unsigned int SpinInteractionGraph::num_vertices() const
{
  return num_vertices_;
}

unsigned int SpinInteractionGraph::num_edges() const
{
  return num_edges_;
}

void SpinInteractionGraph::clear()
{
  spins_.clear();
  states_.clear();
  positions_.clear();
  num_vertices_ = 0;
  num_edges_ = 0;
  vertex_labels1_.clear();
  vertex_labels2_.clear();
  interactions_.clear();
  return;
}

Spin SpinInteractionGraph::get_spin(const unsigned int label) const
{
  check_vertex_label(label);
  return spins_[label];
}

SpinState SpinInteractionGraph::get_state(const unsigned int label) const
{
  check_vertex_label(label);
  return states_[label];
}

Eigen::Vector3d SpinInteractionGraph::get_position(
    const unsigned int label) const
{
  check_vertex_label(label);
  return positions_[label];
}

bool SpinInteractionGraph::get_join_basis(
    const unsigned int label) const
{
  check_vertex_label(label);
  return join_basis_[label];
}

SpinInteraction* SpinInteractionGraph::get_interaction(
    const unsigned int index) const
{
  check_edge_index(index);
  return interactions_[index];
}

std::pair<unsigned int,unsigned int> SpinInteractionGraph::
                  get_interaction_labels(const unsigned int index) const
{
  return std::pair< unsigned int, unsigned int > (vertex_labels1_[index],
      vertex_labels2_[index]);
}

SpinVector SpinInteractionGraph::get_spins() const
{
  return spins_;
}

void SpinDecoherence::SpinInteractionGraph::add_vertex(const Spin& spin,
    const Eigen::Vector3d& position)
{
  spins_.push_back(spin);
  states_.push_back( SpinState(SpinBasis(spin)) );
  positions_.push_back(position);
  join_basis_.push_back(false);
  num_vertices_++;
  return;
}

void SpinInteractionGraph::add_vertex_join_basis(const Spin& spin,
  const SpinState& state, const Eigen::Vector3d& position)
{
  spins_.push_back(spin);
  states_.push_back(state);
  positions_.push_back(position);
  join_basis_.push_back(true);
  num_vertices_++;
  return;
}

void SpinInteractionGraph::add_vertex_join_basis(const Spin& spin,
  const Eigen::Vector3d& position)
{
  spins_.push_back(spin);
  states_.push_back( SpinState(SpinBasis(spin)) );
  positions_.push_back(position);
  join_basis_.push_back(true);
  num_vertices_++;
  return;
}

SpinBasis SpinInteractionGraph::build_basis() const
{
  SpinBasis basis = get_state(0).get_basis();
  for (unsigned int i = 1; i<num_vertices();i++) {
    if (get_join_basis(i) == true) {
      basis = basis + (get_state(i).get_basis());
    } else {
        basis = basis^get_state(i).get_basis();
    }
  }
  return basis;
}

} // namespace SpinDecoherence
