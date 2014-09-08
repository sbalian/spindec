#ifndef TWOSTATESUPERPOSITION_H_
#define TWOSTATESUPERPOSITION_H_

// SpinDec::TwoStateSuperposition
//
// 2-level superposition state.
//
// Seto Balian, Sep 8, 2014

#include "SpinDec/typedefs.h"
#include "SpinDec/SpinState.h"

namespace SpinDec
{

class TwoStateSuperposition : public SpinState
{
private:
  SpinState state0_;
  SpinState state1_;
  
  CDouble c0_;
  CDouble c1_;
  
public:
  TwoStateSuperposition();
  TwoStateSuperposition(const CDouble& c0, const SpinState& state0,
      const CDouble& c1, const SpinState& state1);
  
  const SpinState& get_state0() const;
  const SpinState& get_state1() const;
  
  const CDouble& get_c0() const;
  const CDouble& get_c1() const;
    
  
};

} // namespace SpinDec

#endif // TWOSTATESUPERPOSITION_H_
