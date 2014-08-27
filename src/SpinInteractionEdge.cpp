// See SpinInteractionEdge.h for description.
// Seto Balian, Aug 27, 2014

#include "SpinDec/SpinInteractionEdge.h"

namespace SpinDec
{

SpinInteractionEdge::SpinInteractionEdge() :
    labels_(pair<UInt,UInt>(0,0))
{
}

SpinInteractionEdge::SpinInteractionEdge(
    const UInt label1, const UInt label2,
    const auto_ptr<SpinInteraction>&  interaction) :
    labels_(pair<UInt,UInt>(
        label1,label2))
{
  interaction_ = interaction->clone();
}

UInt SpinInteractionEdge::get_label1() const
{
  return labels_.first;
}

UInt SpinInteractionEdge::get_label2() const
{
  return labels_.second;
}

auto_ptr<SpinInteraction> SpinInteractionEdge::get_interaction() const
{
  return interaction_->clone();
}

SpinInteractionEdge::SpinInteractionEdge(const SpinInteractionEdge& other)
{
  *this = other;
}

SpinInteractionEdge& SpinInteractionEdge::operator =(
  const SpinInteractionEdge& other)
{
  labels_ = other.labels_;
  interaction_ = other.interaction_->clone();
  return *this;
}

} // namespace SpinDec

