// See SpinState.h for description.
// Seto Balian, Dec 5, 2013

#include "SpinState.h"
#include "Errors.h"

void SpinState::quit_if_dimension_mismatch() const
{
  if (basis_.dimension() != state_.rows()) {
    Errors::quit("SpinState: State and basis must have the same dimension!");
  }
  return;
}

SpinState::SpinState()
{
  basis_ = SpinBasis();
}

SpinState::SpinState(const Eigen::VectorXcd & state, const SpinBasis & basis)
{
  state_ = state;
  basis_ = basis;
  quit_if_dimension_mismatch();
}

Eigen::VectorXcd SpinState::get_state() const
{
  return state_;
}

SpinBasis SpinState::get_basis() const
{
  return basis_;
}

void SpinState::set_state(const Eigen::VectorXcd & state)
{
  state_ = state;
  quit_if_dimension_mismatch();
  return;
}


unsigned int SpinState::dimension() const
{
  return basis_.dimension();
}
