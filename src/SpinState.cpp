// See SpinState.h for description.
// Seto Balian, Feb 6, 2014

#include "SpinState.h"
#include "BoostEigen.h"
#include "Errors.h"

namespace SpinDecoherence
{

SpinState::SpinState() : MatrixRepresentation()
{/**/}

SpinState::SpinState(const Eigen::VectorXcd & state, const SpinBasis & basis) :
    MatrixRepresentation(basis)
{
  set_state(state);
}

SpinState::SpinState(const SpinBasis & basis) : MatrixRepresentation(basis)
{
  set_state(Eigen::VectorXcd::Zero(get_dimension()));
}

Eigen::VectorXcd SpinState::get_state() const
{
  return state_;
}

void SpinState::set_state(const Eigen::VectorXcd & state)
{
  state_ = state;
  quit_if_dimension_mismatch();
  return;
}

SpinState SpinState::operator^(const SpinState & rhs)
{
  return SpinState( BoostEigen::tensorProduct(get_state(),rhs.get_state()) ,
      get_basis()^(rhs.get_basis()) );
}

void SpinState::quit_if_dimension_mismatch() const
{
  if (MatrixRepresentation::get_dimension() != state_.rows()) {
    Errors::quit("SpinState: State and basis must have the same dimension!");
  }
  return;
}

void SpinState::set_zero()
{
  state_.setZero(get_dimension());
  return;
}

} // namespace SpinDecoherence
