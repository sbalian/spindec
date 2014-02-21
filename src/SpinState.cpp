// See SpinState.h for description.
// Seto Balian, Feb 21, 2014

#include "SpinState.h"
#include "BoostEigen.h"
#include "Errors.h"

namespace SpinDecoherence
{

SpinState::SpinState() : MatrixRepresentation()
{
  set_state_vector(cdvector::Zero(0)); // TODO Is this OK?
}

SpinState::SpinState(const cdvector & state_vector,
    const SpinBasis & basis) :
    MatrixRepresentation(basis)
{
  set_state_vector(state_vector);
}

SpinState::SpinState(const SpinBasis & basis) : MatrixRepresentation(basis)
{
  set_state_vector(cdvector::Zero(get_dimension()));
}

const cdvector& SpinState::get_state_vector() const
{
  return state_vector_;
}

void SpinState::set_state_vector(const cdvector & state_vector)
{
  state_vector_ = state_vector;
  quit_if_dimension_mismatch();
  return;
}

SpinState SpinState::operator^(const SpinState & rhs)
{
  return SpinState( BoostEigen::tensorProduct(get_state_vector(),
                                              rhs.get_state_vector()) ,
      get_basis()^(rhs.get_basis()) );
}

void SpinState::quit_if_dimension_mismatch() const
{
  if (MatrixRepresentation::get_dimension() != state_vector_.rows()) {
    Errors::quit(
        "SpinState: State-vector and basis must have the same dimension!");
  }
  return;
}

void SpinState::set_zero()
{
  state_vector_.setZero();
  return;
}

} // namespace SpinDecoherence
