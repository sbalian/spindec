// See SpinInteractionNode.h for description.
// Seto Balian 31/10/2013

#include "SpinInteractionNode.h"
#include "Spin.h"

#include "Errors.h"

void quit_if_empty(const SpinInteractionNode & node) {
  if (node.is_empty()) {
    Errors::quit("Node is empty.");
  }
}

SpinInteractionNode::SpinInteractionNode()
{
  set_spin(Spin());
  set_label(0);
  is_empty_ = true;
}

SpinInteractionNode::SpinInteractionNode(const Spin & spin, const int label)
{
  set_spin(spin);
  set_label(label);
}

Spin SpinInteractionNode::get_spin() const
{
  quit_if_empty(*this);
  return spin_;
}

int SpinInteractionNode::get_label() const
{
  quit_if_empty(*this);
  return label_;
}

void SpinInteractionNode::set_spin(const Spin & spin)
{
  spin_ = spin;
  is_empty_ = false;
  return;
}

bool SpinInteractionNode::is_empty() const
{
  return is_empty_;
}

