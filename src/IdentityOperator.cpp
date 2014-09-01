// See IdentityOperator.h for description.
// Seto Balian, Sep 1, 2014

#include "SpinDec/IdentityOperator.h"

namespace SpinDec
{

IdentityOperator::IdentityOperator()
{
}

IdentityOperator::IdentityOperator(const UInt dimension,
    const SpinBasis& basis)
: SpinOperator(ComplexMatrix::Identity(dimension,dimension),basis)
{
}


} // namespace SpinDec

