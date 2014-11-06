#ifndef IDENTITYPULSE_H_
#define IDENTITYPULSE_H_

// SpinDec::IdentityPulse
//
// Identity pulse (no duration).
//
// Seto Balian, Nov 6, 2014

#include "SpinDec/typedefs.h"
#include "SpinDec/Pulse.h"

namespace SpinDec
{

class IdentityPulse : public Pulse
{
public:
  IdentityPulse();
  IdentityPulse(const SpinBasis& basis);
};

} // namespace SpinDec

#endif // IDENTITYPULSE_H_
