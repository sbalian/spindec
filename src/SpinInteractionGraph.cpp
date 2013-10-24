// See SpinInteractionGraph.h for description.
// Seto Balian 22/10/2013

#include "SpinInteractionGraph.h"
#include "SpinInteractionNode.h"
#include "SpinInteractionVertex.h"

#include <vector>

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

