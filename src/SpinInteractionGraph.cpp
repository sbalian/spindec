// See SpinInteractionGraph.h for description.
// Seto Balian 08/10/2013

#include "SpinInteractionGraph.h"
#include "SpinInteractionNode.h"
#include "SpinInteraction.h"

#include <vector>


void SpinInteractionGraph::add_node(const SpinInteractionNode & node)
{
  nodes_.push_back(node);
  return;
}

void SpinInteractionGraph::add_interaction(const SpinInteraction &
                                                                interaction)
{
  interactions_.push_back(interaction);
  return;
}

