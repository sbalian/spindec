// See SpinInteractionNode.h for description.
// Seto Balian, November 26, 2013

#include "SpinInteractionNode.h"
#include "Spin.h"

#include "Errors.h"

#include <Eigen/Dense>

void SpinInteractionNode::quit_if_empty(const SpinInteractionNode & node) const{
  if (node.is_empty()) {
    Errors::quit(*this,"Node is empty.");
  }
}

SpinInteractionNode::SpinInteractionNode()
{
  set_spin(Spin());
  set_label(0);
  is_empty_ = true;
  Named::set_class_name("SpinInteractionNode");
}

SpinInteractionNode::SpinInteractionNode(const Spin & spin,
                                const unsigned int label)
{
  set_spin(spin);
  set_label(label);
  Named::set_class_name("SpinInteractionNode");
}

Spin SpinInteractionNode::get_spin() const
{
  quit_if_empty(*this);
  return spin_;
}


unsigned int SpinInteractionNode::get_label() const
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


void SpinInteractionNode::set_label(const unsigned int label)
{
  label_ = label;
  return;
}


bool SpinInteractionNode::is_empty() const
{
  return is_empty_;
}
