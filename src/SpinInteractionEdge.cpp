// See SpinInteractionEdge.h for description.
// Seto Balian, Dec 10, 2013

#include "SpinInteractionEdge.h"

SpinInteractionEdge::SpinInteractionEdge() :
  Edge(), interaction_(NULL)
{
}

SpinInteractionEdge::SpinInteractionEdge(const unsigned int label1,
    const unsigned int label2, SpinInteraction* interaction) :
        Edge(label1,label2), interaction_(interaction)
{
}

SpinInteraction* SpinInteractionEdge::get_interaction() const
{
  return interaction_;
}
