#ifndef TWOSTATESUPERPOSITION_H_
#define TWOSTATESUPERPOSITION_H_

// Seto Balian, Jun 24, 2015

// TODO related to spin 1/2 ...

#include "SpinDec/typedefs.h"
#include "SpinDec/SpinState.h"

namespace SpinDec
{

/// 2-level superposition state.
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
