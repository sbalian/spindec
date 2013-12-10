// See SpinInteractionVertex.h for description.
// Seto Balian, Dec 10, 2013

#include "SpinInteractionVertex.h"

SpinInteractionVertex::SpinInteractionVertex() :
  LabeledVertex(),
  spin_(Spin()),
  state_(SpinState())
{
}

SpinInteractionVertex::SpinInteractionVertex(const unsigned int label,
    const Spin & spin, const SpinState & state,
    const Eigen::Vector3d & position) :
        LabeledVertex(label),
        spin_(spin),
        state_(state),
        position_(position)
{
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

void SpinInteractionVertex::set_position(const Eigen::Vector3d& position)
{
  position_ = position;
  return;
}
