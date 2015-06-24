#ifndef IDENTITYOPERATOR_H_
#define IDENTITYOPERATOR_H_

// Seto Balian, Jun 24, 2015

#include "SpinDec/typedefs.h"
#include "SpinDec/SpinOperator.h"

namespace SpinDec
{

/// Identity.
class IdentityOperator : public SpinOperator
{
public:
  IdentityOperator();
  explicit IdentityOperator(const SpinBasis& basis);
  
};

} // namespace SpinDec

#endif // IDENTITYOPERATOR_H_
