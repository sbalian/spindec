#ifndef IDENTITYPULSE_H_
#define IDENTITYPULSE_H_

// Seto Balian, Jun 24, 2015

#include "SpinDec/typedefs.h"
#include "SpinDec/Pulse.h"

namespace SpinDec
{

/// Identity pulse (no duration).
class IdentityPulse : public Pulse
{
public:
  IdentityPulse();
  IdentityPulse(const SpinBasis& basis);
};

} // namespace SpinDec

#endif // IDENTITYPULSE_H_
