// See SpinInteractionVertexContents.h for description.
// Seto Balian, Dec 13, 2013

#include "SpinInteractionVertexContents.h"

SpinInteractionVertexContents::SpinInteractionVertexContents() :
  VertexContents(), spin_(Spin()), state_(SpinState())
{
}

SpinInteractionVertexContents::SpinInteractionVertexContents(const Spin& spin,
    const SpinState& state, const Eigen::Vector3d& position) :
    VertexContents(), spin_(spin), state_(state), position_(position)
{
}

Spin SpinInteractionVertexContents::get_spin() const
{
  return spin_;
}

SpinState SpinInteractionVertexContents::get_state() const
{
  return state_;
}

Eigen::Vector3d SpinInteractionVertexContents::get_position() const
{
  return position_;
}

void SpinInteractionVertexContents::set_position(
    const Eigen::Vector3d& position)
{
  position_ = position;
  return;
}
