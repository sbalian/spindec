// See SpinInteractionEdge.h for description.
// Seto Balian, Feb 20, 2014

#include "SpinInteractionEdge.h"

namespace SpinDecoherence
{

SpinInteractionEdge::SpinInteractionEdge() :
    vertices_(std::pair<SpinInteractionVertex,SpinInteractionVertex>(
        SpinInteractionVertex(),SpinInteractionVertex())),
        interaction_(NULL)
{
}

SpinInteractionEdge::SpinInteractionEdge(
    const SpinInteractionVertex& vertex1, const SpinInteractionVertex& vertex2,
    SpinInteraction* interaction) :
    vertices_(std::pair<SpinInteractionVertex,SpinInteractionVertex>(
        vertex1,vertex2)),
        interaction_(interaction)
{
}

const SpinInteractionVertex& SpinInteractionEdge::get_vertex1()
const
{
  return vertices_.first;
}

const SpinInteractionVertex& SpinInteractionEdge::get_vertex2()
const
{
  return vertices_.second;
}

SpinInteraction* SpinInteractionEdge::get_interaction() const
{
  return interaction_;
}

} // namespace SpinDecoherence

