// See DensityOperator.h for description.
// Seto Balian, Jun 2, 2014

#include "SpinDec/DensityOperator.h"
#include "SpinDec/BoostEigen.h"

namespace SpinDec
{

DensityOperator::DensityOperator() : SpinOperator()
{
}

DensityOperator::DensityOperator(const SpinState& state)
: SpinOperator( state.get_state_vector()*(state.get_state_vector().adjoint())
    , state.get_basis())
{
}

} // namespace SpinDec
