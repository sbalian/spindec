// See SpinInteractionVertex.h for description.
// Seto Balian 22/10/2013

#include "SpinInteractionVertex.h"
#include "SpinInteractionNode.h"

#include <utility>

SpinInteractionVertex::SpinInteractionVertex()
{
  set_nodes(SpinInteractionNode(),SpinInteractionNode());
  set_strength(0.0);
}

SpinInteractionVertex::SpinInteractionVertex(const SpinInteractionNode & node1,
                                 const SpinInteractionNode & node2,
                                 const double strength)
{
  set_nodes(node1,node2);
  set_strength(strength);
}

SpinInteractionNode SpinInteractionVertex::get_node1() const
{
  return nodes_.first;
}

SpinInteractionNode SpinInteractionVertex::get_node2() const
{
  return nodes_.second;
}

double SpinInteractionVertex::get_strength() const
{
  return strength_;
}

void SpinInteractionVertex::set_nodes(const SpinInteractionNode & node1,
                                const SpinInteractionNode & node2)
{
  set_node1(node1);
  set_node2(node2);
  return;
}

void SpinInteractionVertex::set_node1(const SpinInteractionNode & node)
{
  set_node1(node);
  return;
}

void SpinInteractionVertex::set_node2(const SpinInteractionNode & node)
{
  set_node2(node);
  return;
}

void SpinInteractionVertex::set_strength(const double strength)
{
  strength_ = strength;
  return;
}

