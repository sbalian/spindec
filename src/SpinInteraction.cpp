// See SpinInteraction.h for description.
// Seto Balian 04/10/2013

#include "SpinInteraction.h"
#include "SpinInteractionNode.h"

#include <utility>

SpinInteraction::SpinInteraction()
{
  set_nodes(SpinInteractionNode(),SpinInteractionNode());
  set_strength(0.0);
}

SpinInteraction::SpinInteraction(const SpinInteractionNode & node1,
                                 const SpinInteractionNode & node2,
                                 const double strength)
{
  set_nodes(node1,node2);
  set_strength(strength);
}

SpinInteractionNode SpinInteraction::get_node1() const
{
  return nodes_.first;
}

SpinInteractionNode SpinInteraction::get_node2() const
{
  return nodes_.second;
}

double SpinInteraction::get_strength() const
{
  return strength_;
}

void SpinInteraction::set_nodes(const SpinInteractionNode & node1,
                                const SpinInteractionNode & node2)
{
  set_node1(node1);
  set_node2(node2);
  return;
}

void SpinInteraction::set_node1(const SpinInteractionNode & node)
{
  set_node1(node);
  return;
}

void SpinInteraction::set_node2(const SpinInteractionNode & node)
{
  set_node2(node);
  return;
}

void SpinInteraction::set_strength(const double strength)
{
  strength_ = strength;
  return;
}

// TODO something like this ...
void SpinInteraction::set_interaction(const std::string & option)
{
  return;
}
void SpinInteraction::set_interaction(const double strength)
{
  return;
}


