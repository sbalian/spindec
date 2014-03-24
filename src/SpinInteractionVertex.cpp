// See SpinInteractionVertex.h for description.
// Seto Balian, Mar 24, 2014

#include "SpinDec/SpinInteractionVertex.h"

namespace SpinDec
{

SpinInteractionVertex::SpinInteractionVertex() :
    label_(0),spin_(Spin()),position_(ThreeVector()),state_(SpinState())
{/**/}

SpinInteractionVertex::SpinInteractionVertex(
    UInt label, const Spin& spin, const ThreeVector& position,
    const SpinState& state) :
        label_(label), spin_(spin), position_(position), state_(state)
{
}

unsigned int SpinInteractionVertex::get_label() const
{
  return label_;
}

const Spin& SpinInteractionVertex::get_spin() const
{
  return spin_;
}

const ThreeVector& SpinInteractionVertex::get_position() const
{
  return position_;
}

const SpinState& SpinInteractionVertex::get_state() const
{
  return state_;
}

} // namespace SpinDec

