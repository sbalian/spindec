// See SpinInteractionGraph.h for description.
// Seto Balian, Dec 13, 2013

#include "SpinInteractionGraph.h"

SpinInteractionGraph::SpinInteractionGraph() : LabeledGraph()
{
}

void SpinInteractionGraph::add_vertex(const LabeledVertex& vertex,
    const SpinInteractionVertexContents& contents)
{
  LabeledGraph::add_vertex(vertex, contents);
  return;
}

void SpinInteractionGraph::add_edge(const Edge& edge,
    const SpinInteractionEdgeContents& contents)
{
  LabeledGraph::add_edge(edge, contents);
  return;
}
