// See DensityOperator.h for description.
// Seto Balian, Nov 6, 2014

#include "SpinDec/DensityOperator.h"
#include "SpinDec/BoostEigen.h"
#include "SpinDec/Errors.h"

namespace SpinDec
{

DensityOperator::DensityOperator() : SpinOperator()
{
}

DensityOperator::DensityOperator(const SpinState& state,
    const SpinState& state0, const SpinState& state1) :
SpinOperator( state%state) // TODO is this working correctly?
{
  
  if (!(state0.get_basis().is_equal(state1.get_basis()))) {
    Errors::quit("|0> and |1> states must have the same basis.");
  }

  state0_ = state0;
  state1_ = state1;
  
}

DensityOperator::DensityOperator(const ComplexMatrix& matrix,
    const SpinBasis& basis,
    const SpinState& state0,
    const SpinState& state1) :
        SpinOperator(matrix,basis)
{
  state0_ = state0;
  state1_ = state1;
}


// TODO Is this working correctly?
DensityOperator DensityOperator::reduced() const
{
  const unsigned int trace_dimension =
      get_dimension()/state0_.get_dimension();
  if (trace_dimension == 1) {
    return *this;
  }
  // else
  return DensityOperator(
      BoostEigen::partialTrace(get_matrix(),trace_dimension),
      state0_.get_basis(),state0_,state1_);
  
}

CDouble DensityOperator::off_diagonal_reduced() const
{
  return state0_*(reduced()*state1_);
}

} // namespace SpinDec
