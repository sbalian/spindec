// See SpinInteractionNode.h for description.
// Seto Balian 04/10/2013

#include "SpinInteractionNode.h"
#include "Spin.h"

#include "Errors.h"

SpinInteractionNode::SpinInteractionNode()
{
  set_spin(Spin());
  isEmpty_ = 1;
}

SpinInteractionNode::SpinInteractionNode(const Spin & spin)
{
  set_spin(spin);
  isEmpty_ = 0;
}

Spin SpinInteractionNode::get_spin() const
{
  if (isEmpty()) {
    Errors::quit("You're not allowed to return an empty Spin.");
  }
  return spin_;
}

void SpinInteractionNode::set_spin(const Spin & spin)
{
  spin_ = spin;
  isEmpty_ = 0;
  return;
}

bool SpinInteractionNode::isEmpty() const
{
  return isEmpty_;
}

