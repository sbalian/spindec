#ifndef TWOSTATESUPERPOSITION_H_
#define TWOSTATESUPERPOSITION_H_

// SpinDec::TwoStateSuperposition
//
// Two-spin-state superposition.
// alpha|state_0> + beta|state_1>
// complex alpha and beta.
//
// Seto Balian, Jun 5, 2014

#include "SpinDec/typedefs.h"
#include "SpinDec/SpinState.h"

namespace SpinDec
{

class TwoStateSuperposition : public SpinState
{
private:
  CDouble alpha_;
  CDouble beta_;
  
  ComplexVector state0_;
  ComplexVector state1_;
  
public:
  TwoStateSuperposition();
  TwoStateSuperposition(const CDouble & alpha,
                        const ComplexVector & state0,
                        const CDouble & beta,
                        const ComplexVector & state1,
                        const SpinBasis& basis);
  
};

} // namespace SpinDec

#endif // TWOSTATESUPERPOSITION_H_
