// See SpinInteractionGraph.h for description.
// Seto Balian, Dec 3, 2013

#include "SpinInteractionGraph.h"

SpinInteractionGraph::SpinInteractionGraph() {/**/}

void SpinInteractionGraph::add_isolated_vertex(
    const SpinInteractionVertex & isolated_vertex)
{
  isolated_vertices_.push_back(isolated_vertex);
  return;
}

void SpinInteractionGraph::add_edge(const SpinInteractionEdge & edge)
{
  edges_.push_back(edge);
  return;
}

SpinInteractionVertex SpinInteractionGraph::get_isolated_vertex(
    const unsigned int index) const
{
  return isolated_vertices_[index];
}

SpinInteractionEdge SpinInteractionGraph::get_edge(
    const unsigned int index) const
{
  return edges_[index];
}

unsigned int SpinInteractionGraph::num_isolated_vertices() const
{
  return isolated_vertices_.size();
}

unsigned int SpinInteractionGraph::num_edges() const
{
  return edges_.size();
}

void SpinInteractionGraph::clear()
{
  isolated_vertices_.clear();
  edges_.clear();
  return;
}
