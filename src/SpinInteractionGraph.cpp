// See SpinInteractionGraph.h for description.
// Seto Balian, Dec 6, 2013

#include "SpinInteractionGraph.h"

SpinInteractionGraph::SpinInteractionGraph()
{
  SpinInteractionGraph(UniformMagneticField());
}

SpinInteractionGraph::SpinInteractionGraph(const UniformMagneticField& field) :
    field_(field)
{/**/}


void SpinInteractionGraph::add_vertex(const SpinInteractionVertex& vertex)
{
  vertices_.push_back(vertex);
  return;
}

void SpinInteractionGraph::add_edge(const SpinInteractionEdge& edge)
{
  edges_.push_back(edge);
  return;
}

SpinInteractionVertex SpinInteractionGraph::get_vertex(
    const unsigned int index) const
{
  return vertices_[index];
}

SpinInteractionEdge SpinInteractionGraph::get_edge(
    const unsigned int index) const
{
  return edges_[index];
}

UniformMagneticField SpinInteractionGraph::get_field() const
{
  return field_;
}

void SpinInteractionGraph::set_field(const UniformMagneticField & field)
{
  field_ = field;
  return;
}


unsigned int SpinInteractionGraph::num_vertices() const
{
  return vertices_.size();
}

unsigned int SpinInteractionGraph::num_edges() const
{
  return edges_.size();
}


void SpinInteractionGraph::clear()
{
  vertices_.clear();
  edges_.clear();
  return;
}
