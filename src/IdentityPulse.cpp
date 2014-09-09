// See IdentityPulse.h for description.
// Seto Balian, Sep 8, 2014

#include "SpinDec/IdentityPulse.h"
#include "SpinDec/IdentityOperator.h"

namespace SpinDec
{

IdentityPulse::IdentityPulse() : Pulse()
{

}

IdentityPulse::IdentityPulse(const SpinBasis& basis) :
    Pulse(0.0,IdentityOperator(basis))
{
}


} // namespace SpinDec

