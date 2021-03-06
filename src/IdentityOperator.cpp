// See IdentityOperator.h for description.
// Seto Balian, Nov 6, 2014

#include "SpinDec/IdentityOperator.h"

namespace SpinDec
{

IdentityOperator::IdentityOperator()
{
}

IdentityOperator::IdentityOperator(const SpinBasis& basis)
: SpinOperator(ComplexMatrix::Identity(
    basis.num_basis_states(),basis.num_basis_states()),basis)
{
}


} // namespace SpinDec

