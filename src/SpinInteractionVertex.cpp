// See SpinInteractionVertex.h for description.
// Seto Balian, Dec 5, 2013

#include "SpinInteractionVertex.h"

SpinInteractionVertex::SpinInteractionVertex()
{
  label_ = 0;
  spin_ = Spin();
  state_ = SpinState();
}

SpinInteractionVertex::SpinInteractionVertex(const unsigned int label,
    const Spin & spin, const SpinState & state,
    const Eigen::Vector3d & position)
{
  label_ = label;
  spin_ = spin;
  state_ = state;
  position_ = position;
}

unsigned int SpinInteractionVertex::get_label() const
{
  return label_;
}

Spin SpinInteractionVertex::get_spin() const
{
  return spin_;
}

SpinState SpinInteractionVertex::get_state() const
{
  return state_;
}

Eigen::Vector3d SpinInteractionVertex::get_position() const
{
  return position_;
}

void SpinInteractionVertex::set_label(const unsigned int label)
{
  label_= label;
  return;
}

void SpinInteractionVertex::set_spin(const Spin& spin)
{
  spin_ = spin;
  return;
}

void SpinInteractionVertex::set_state(const SpinState& state)
{
  state_ = state;
  return;
}

void SpinInteractionVertex::set_position(const Eigen::Vector3d& position)
{
  position_ = position;
  return;
}
