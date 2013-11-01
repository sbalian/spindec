// See SpinInteractionGraph.h for description.
// Seto Balian 01/11/2013

#include "SpinInteractionGraph.h"
#include "SpinInteractionNode.h"
#include "SpinInteractionVertex.h"

#include <vector>

SpinInteractionGraph::SpinInteractionGraph() {
  //
}

void SpinInteractionGraph::add_node(const SpinInteractionNode & node)
{
  nodes_.push_back(node);
  return;
}

void SpinInteractionGraph::add_vertex(const SpinInteractionVertex &
                                                                vertex)
{
  vertices_.push_back(vertex);
  return;
}
