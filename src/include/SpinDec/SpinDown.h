#ifndef SPINDOWN_H_
#define SPINDOWN_H_

// SpinDec::SpinUp
//
// Spin down state. For a positive (or zero) gyromagnetic ratio
// (and positive spin quantum number) this is (0,1) in the (0.5,-0.5) basis.
// See also SpinUp.
//
// Seto Balian, Apr 2, 2014

#include "SpinDec/typedefs.h"
#include "SpinDec/SpinHalf.h"

namespace SpinDec
{

class SpinDown : public SpinHalf
{
public:
  SpinDown(); // default for positive gyromagnetic ratio
  SpinDown(const SpinHalfParameters& spin_half_parameters);
  
private:
  virtual void init(const double gyromagnetic_ratio);
  
};

} // namespace SpinDec

#endif // SPINDOWN_H_
