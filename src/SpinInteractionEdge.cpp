// See SpinInteractionEdge.h for description.
// Seto Balian, Dec 3, 2013

#include "SpinInteractionEdge.h"

SpinInteractionEdge::SpinInteractionEdge()
{
  vertices_.first = SpinInteractionVertex();
  vertices_.second = SpinInteractionVertex();
}

SpinInteractionEdge::SpinInteractionEdge(const SpinInteractionVertex & vertex1,
                                         const SpinInteractionVertex & vertex2)
{
  vertices_.first = vertex1;
  vertices_.second = vertex2;
}

std::pair<SpinInteractionVertex,SpinInteractionVertex>
  SpinInteractionEdge::get_vertices() const
{
  return vertices_;
}

SpinInteractionVertex SpinInteractionEdge::get_vertex1() const
{
  return vertices_.first;
}

SpinInteractionVertex SpinInteractionEdge::get_vertex2() const
{
  return vertices_.second;
}

void SpinInteractionEdge::set_vertices(
    const std::pair<SpinInteractionVertex,SpinInteractionVertex> & vertices)
{
  vertices_ = vertices;
  return;
}

void SpinInteractionEdge::set_vertices(const SpinInteractionVertex & vertex1,
                                       const SpinInteractionVertex & vertex2)
{
  set_vertex1(vertex1);
  set_vertex2(vertex2);
  return;
}

void SpinInteractionEdge::set_vertex1(const SpinInteractionVertex & vertex)
{
  vertices_.first = vertex;
  return;
}

void SpinInteractionEdge::set_vertex2(const SpinInteractionVertex & vertex)
{
  vertices_.second = vertex;
  return;
}
