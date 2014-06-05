// See TwoStateSuperposition.h for description.
// Seto Balian, Jun 5, 2014

#include "SpinDec/TwoStateSuperposition.h"

namespace SpinDec
{

TwoStateSuperposition::TwoStateSuperposition() : SpinState(),
    alpha_(CDouble(0.0,0.0)),beta_(CDouble(0.0,0.0))
{
}

TwoStateSuperposition::TwoStateSuperposition(const CDouble& alpha,
    const ComplexVector& state0, const CDouble& beta,
    const ComplexVector& state1, const SpinBasis& basis) :
        SpinState(basis),alpha_(alpha),beta_(beta),state0_(state0),
        state1_(state1)
{
  set_state_vector(state0*alpha + state1*beta);
}


} // namespace SpinDec

