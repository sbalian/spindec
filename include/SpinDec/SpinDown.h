#ifndef SPINDOWN_H_
#define SPINDOWN_H_

// SpinDec::SpinUp
//
// Spin down state. For a positive (or zero) gyromagnetic ratio
// (and positive spin quantum number) this is (0,1) in the (0.5,-0.5) basis.
// See also SpinUp.
//
// Seto Balian, May 22, 2014

#include "SpinDec/typedefs.h"
#include "SpinDec/SpinHalfStates.h"

namespace SpinDec
{

class SpinDown : public SpinHalfStates
{
public:
  SpinDown(); // default for positive gyromagnetic ratio
  SpinDown(const SpinHalfParameters& spin_half_parameters);
  
private:
  virtual void init(const double gyromagnetic_ratio);
  
};

} // namespace SpinDec

#endif // SPINDOWN_H_
