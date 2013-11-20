// See SpinInteractionNode.h for description.
// Seto Balian 20/11/2013

#include "SpinInteractionNode.h"
#include "Spin.h"

#include "Errors.h"

#include <Eigen/Dense>

void quit_if_empty(const SpinInteractionNode & node) {
  if (node.is_empty()) {
    Errors::quit("Node is empty.");
  }
}

SpinInteractionNode::SpinInteractionNode()
{
  set_spin(Spin());
  set_label(0);
  set_state(Eigen::VectorXcd::Zero(0));
  is_empty_ = true;
}

SpinInteractionNode::SpinInteractionNode(const Spin & spin,
                                const Eigen::VectorXcd & state,
                                const unsigned int label)
{
  set_spin(spin);
  set_state(state);
  set_label(label);
}

Spin SpinInteractionNode::get_spin() const
{
  quit_if_empty(*this);
  return spin_;
}

Eigen::VectorXcd SpinInteractionNode::get_state() const
{
  quit_if_empty(*this);
  return state_;
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


void SpinInteractionNode::set_state(const Eigen::VectorXcd & state)
{
  state_ = state;
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
