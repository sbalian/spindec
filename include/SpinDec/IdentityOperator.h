#ifndef IDENTITYOPERATOR_H_
#define IDENTITYOPERATOR_H_

// SpinDec::IdentityOperator
//
// Identity.
//
// Seto Balian, Nov 6, 2014

#include "SpinDec/typedefs.h"
#include "SpinDec/SpinOperator.h"

namespace SpinDec
{

class IdentityOperator : public SpinOperator
{
public:
  IdentityOperator();
  explicit IdentityOperator(const SpinBasis& basis);
  
};

} // namespace SpinDec

#endif // IDENTITYOPERATOR_H_
