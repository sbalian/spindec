// See SpinInteractionGraph.h for description.
// Seto Balian, Jan 22, 2014

#include "SpinInteractionGraph.h"
#include "Errors.h"

// Check if vertex label exists
void SpinInteractionGraph::check_vertex_label(const unsigned int label) const
{
  if (label >= num_vertices()) {
    Errors::quit("Vertices for edge don't exist.");
    return;
  }
  return;
}

SpinInteractionGraph::SpinInteractionGraph()
{
  num_vertices_ = 0;
}

void SpinInteractionGraph::add_vertex(const Spin& spin, const SpinState& state,
    const Eigen::Vector3d& position)
{
  spins_.push_back(spin);
  states_.push_back(state);
  positions_.push_back(position);
  num_vertices_++;
  return;
}

void SpinInteractionGraph::add_edge(const unsigned int label1,
    const unsigned int label2, SpinInteraction* interaction)
{
  
  // First check if labels exist
  check_vertex_label(label1);
  check_vertex_label(label2);
  
  edges_.insert(
      std::make_pair(std::pair<unsigned int, unsigned int>(label1,label2),
                     interaction));
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
  return edges_.size();
}

void SpinInteractionGraph::clear()
{
  spins_.clear();
  states_.clear();
  positions_.clear();
  num_vertices_ = 0;
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
