#ifndef IDENTITYOPERATOR_H_
#define IDENTITYOPERATOR_H_

// SpinDec::IdentityOperator
//
// Identity.
//
// Seto Balian, Sep 1, 2014

#include "SpinDec/typedefs.h"
#include "SpinDec/SpinOperator.h"

namespace SpinDec
{

class IdentityOperator : SpinOperator
{
public:
  IdentityOperator();
  IdentityOperator(const UInt dimension,const SpinBasis& basis);
  
};

} // namespace SpinDec

#endif // IDENTITYOPERATOR_H_
