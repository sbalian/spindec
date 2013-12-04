// See SpinState.h for description.
// Seto Balian, Dec 4, 2013

#include "SpinState.h"
#include "Errors.h"

void SpinState::quit_if_dimension_mismatch() const
{
  if (basis_.dimension() != state_.rows()) {
    Errors::quit("State and basis must have the same dimension!");
  }
  return;
}

SpinState::SpinState()
{
  state_ = Eigen::VectorXcd::Zero(1);
  basis_ = SpinBasis();
}

SpinState::SpinState(const Eigen::VectorXcd & state, const SpinBasis & basis)
{
  quit_if_dimension_mismatch();
  state_ = state;
  basis_ = basis;
}

Eigen::VectorXcd SpinState::get_state() const
{
  return state_;
}

SpinBasis SpinState::get_basis() const
{
  return basis_;
}

unsigned int SpinState::dimension() const
{
  return basis_.dimension();
}
