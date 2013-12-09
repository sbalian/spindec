// See SpinInteractionEdge.h for description.
// Seto Balian, Dec 6, 2013

#include "SpinInteractionEdge.h"

SpinInteractionEdge::SpinInteractionEdge()
{
  set_label1(0);
  set_label2(0);
  interaction_ = NULL;
}

SpinInteractionEdge::SpinInteractionEdge(const unsigned int label1,
    const unsigned int label2, SpinInteraction* interaction)
{
  set_label1(label1);
  set_label2(label2);
  set_interaction(interaction);
}

unsigned int SpinInteractionEdge::get_label1() const
{
  return labels_.first;
}

unsigned int SpinInteractionEdge::get_label2() const
{
  return labels_.second;
}

SpinInteraction* SpinInteractionEdge::get_interaction() const
{
  return interaction_;
}

void SpinInteractionEdge::set_label1(const unsigned int label1)
{
  labels_.first = label1;
  return;
}

void SpinInteractionEdge::set_label2(const unsigned int label2)
{
  labels_.second = label2;
  return;
}

void SpinInteractionEdge::set_interaction(SpinInteraction* interaction)
{
  interaction_ = interaction;
}
