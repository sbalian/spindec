#ifndef SPINUP_H_
#define SPINUP_H_

// SpinDec::SpinUp
//
// Spin up state. For a positive (or zero) gyromagnetic ratio (and positive spin
// quantum number) this is (1,0) in the (0.5,-0.5) basis. See also SpinDown.
//
// Seto Balian, May 22, 2014

#include "SpinDec/typedefs.h"
#include "SpinDec/SpinHalfStates.h"

namespace SpinDec
{

class SpinUp : public SpinHalfStates
{
public:
  SpinUp(); // default for positive gyromagnetic ratio
  SpinUp(const SpinHalfParameters& spin_half_parameters);
  
private:
  virtual void init(const double gyromagnetic_ratio);
  
};

} // namespace SpinDec

#endif // SPINUP_H_
