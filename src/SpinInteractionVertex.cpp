// See SpinInteractionVertex.h for description.
// Seto Balian, November 27, 2013

#include "SpinInteractionVertex.h"
#include <utility>

void SpinInteractionVertex::set_interaction(const SpinInteraction & 
                                                          interaction)
{
  //interaction.calculate();
  interaction_ = interaction;
  return;
}

SpinInteractionVertex::SpinInteractionVertex()
{
  set_labels(0,0);
}

SpinInteractionVertex::SpinInteractionVertex(const unsigned int label1,
                                 const unsigned int label2,
                                const SpinInteraction & interaction)
{
  set_labels(label1,label2);
  set_interaction(interaction);
}

unsigned int SpinInteractionVertex::get_label1() const
{
  return labels_.first;
}

unsigned int SpinInteractionVertex::get_label2() const
{
  return labels_.second;
}

std::string SpinInteractionVertex::get_interaction_type() const
{
  std::string null = "";
 return null; 
}

void SpinInteractionVertex::set_labels(const unsigned int label1,
                                const unsigned int label2)
{
  set_label1(label1);
  set_label2(label2);
  return;
}

void SpinInteractionVertex::set_label1(const unsigned int label)
{
  labels_.first = label;
  return;
}

void SpinInteractionVertex::set_label2(const unsigned int label)
{
  labels_.second = label;
  return;
}
