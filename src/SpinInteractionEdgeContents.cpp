// See SpinInteractionEdgeContents.h for description.
// Seto Balian, Dec 13, 2013

#include "SpinInteractionEdgeContents.h"

SpinInteractionEdgeContents::SpinInteractionEdgeContents() : EdgeContents(),
  interaction_(NULL)
{
}

SpinInteractionEdgeContents::SpinInteractionEdgeContents(
    SpinInteraction* interaction) : EdgeContents(),
  interaction_(NULL)
{
}

SpinInteraction* SpinInteractionEdgeContents::get_interaction() const
{
  return interaction_;
}
