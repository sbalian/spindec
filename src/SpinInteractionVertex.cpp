// See SpinInteractionVertex.h for description.
// Seto Balian, Mar 28, 2014

#include "SpinDec/SpinInteractionVertex.h"

namespace SpinDec
{

SpinInteractionVertex::SpinInteractionVertex() :
    label_(0),
    spin_parameters_(SpinParameters()),
    state_(SpinState(SpinBasis(SpinParameters()))),
    position_(ThreeVector::Zero())
{/**/}

SpinInteractionVertex::SpinInteractionVertex(
    UInt label, const SpinParameters& spin_parameters,
    const SpinState& state,
    const ThreeVector& position) :
        label_(label),
        spin_parameters_(spin_parameters),
        state_(SpinState(SpinBasis(spin_parameters))),
        position_(position)
{
}

unsigned int SpinInteractionVertex::get_label() const
{
  return label_;
}

const SpinParameters& SpinInteractionVertex::get_spin_parameters() const
{
  return spin_parameters_;
}

const SpinState& SpinInteractionVertex::get_state() const
{
  return state_;
}


const ThreeVector& SpinInteractionVertex::get_position() const
{
  return position_;
}

} // namespace SpinDec

