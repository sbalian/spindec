// See TwoStateSuperposition.h for description.
// Seto Balian, Sep 8, 2014

#include "SpinDec/TwoStateSuperposition.h"

namespace SpinDec
{

TwoStateSuperposition::TwoStateSuperposition() : SpinState()
{
}

TwoStateSuperposition::TwoStateSuperposition(const CDouble& c0,
    const SpinState& state0, const CDouble& c1, const SpinState& state1)
  : SpinState( state0*c0 + state1*c1 ), state0_(state0), state1_(state1),
    c0_(c0),c1_(c1)
{
}

const SpinState& TwoStateSuperposition::get_state0() const
{
  return state0_;
}

const SpinState& TwoStateSuperposition::get_state1() const
{
  return state1_;
}

const CDouble& TwoStateSuperposition::get_c0() const
{
  return c0_;
}

const CDouble& TwoStateSuperposition::get_c1() const
{
  return c1_;
}

} // namespace SpinDec

