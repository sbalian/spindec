// See Spin.h for description.
// Seto Balian, Mar 25, 2014

#include "include/SpinDec/Spin.h"

namespace SpinDec
{

Spin::Spin() : parameters_(SpinParameters()),
    state_(SpinState(SpinBasis(SpinParameters()))),
    position_(ThreeVector::Zero())
{
}

Spin::Spin(const SpinParameters& parameters, const ComplexVector& state_vector,
    const ThreeVector& position) :
        parameters_(parameters),
        state_(state_vector,SpinBasis(parameters)),
        position_(position)
{
}

const SpinParameters& Spin::get_parameters() const
{
  return parameters_;
}

const SpinState& Spin::get_state() const
{
  return state_;
}

const ThreeVector& Spin::get_position() const
{
  return position_;
}

void Spin::set_state(const ComplexVector& state_vector)
{
  state_.set_state_vector(state_vector);
  return;
}


} // namespace SpinDec

