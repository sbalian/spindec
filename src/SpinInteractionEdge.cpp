// See SpinInteractionEdge.h for description.
// Seto Balian, Mar 31, 2014

#include "SpinDec/SpinInteractionEdge.h"

namespace SpinDec
{

SpinInteractionEdge::SpinInteractionEdge() :
    vertices_(pair<SpinInteractionVertex,SpinInteractionVertex>(
        SpinInteractionVertex(),SpinInteractionVertex()))
{
}

SpinInteractionEdge::SpinInteractionEdge(
    const SpinInteractionVertex& vertex1, const SpinInteractionVertex& vertex2,
    const auto_ptr<SpinInteraction>&  interaction) :
    vertices_(pair<SpinInteractionVertex,SpinInteractionVertex>(
        vertex1,vertex2))
{
  interaction_ = interaction->clone();
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

auto_ptr<SpinInteraction> SpinInteractionEdge::get_interaction() const
{
  return interaction_->clone();
}

SpinInteractionEdge::SpinInteractionEdge(const SpinInteractionEdge& other)
{
  // TODO repeat code, use = here?
  vertices_ = other.vertices_;
  interaction_ = other.interaction_->clone();
}

SpinInteractionEdge& SpinInteractionEdge::operator =(
  const SpinInteractionEdge& other)
{
  vertices_ = other.vertices_;
  interaction_ = other.interaction_->clone();
  return *this;
}

} // namespace SpinDec

