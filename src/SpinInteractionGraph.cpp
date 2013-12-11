// See SpinInteractionGraph.h for description.
// Seto Balian, Dec 11, 2013

#include "SpinInteractionGraph.h"
#include "Errors.h"

SpinInteractionGraph::SpinInteractionGraph() : LabeledGraph()
{
}

void SpinInteractionGraph::add_vertex(const LabeledVertex& vertex)
{
  // TODO improve this ...
  Errors::quit("SpinInteractionGraph: Can't add vertex without contents.");
  return;
}

void SpinInteractionGraph::add_edge(const Edge& edge)
{
  // TODO improve this ...
  Errors::quit("SpinInteractionGraph: Can't add edge without contents.");
  return;
}

void SpinInteractionGraph::add_vertex(const LabeledVertex& vertex,
    const Spin& spin, const SpinState& state, const Eigen::Vector3d& position)
{
  LabeledGraph::add_vertex(vertex);
  spins_.push_back(spin);
  states_.push_back(state);
  positions_.push_back(position);
  vertex_label_map_.push_back(vertex.get_label());
  return;
}

void SpinInteractionGraph::add_edge(const Edge& edge,
    const SpinInteraction* interaction)
{
  LabeledGraph::add_edge(edge);
  interactions_.push_back(interaction);
  return;
}

Spin SpinInteractionGraph::get_spin(const unsigned int vertex_label) const
{
  for (unsigned int i=0;i<)
}

SpinState SpinInteractionGraph::get_state(const unsigned int vertex_label) const
{
}

Eigen::Vector3d SpinInteractionGraph::get_position(
    const unsigned int vertex_label) const
{
}

SpinInteraction* SpinInteractionGraph::get_interaction(
    const unsigned int vertex_label1, const unsigned int vertex_label2) const
{
}

void SpinInteractionGraph::set_position(const unsigned int vertex_label,
    const Eigen::Vector3d& position)
{
}
