#ifndef SPINDOWN_H_
#define SPINDOWN_H_

// Seto Balian, Jun 25, 2015

#include "SpinDec/typedefs.h"
#include "SpinDec/SpinHalfStates.h"

namespace SpinDec
{

/**
 * \brief Spin down state.
 * 
 * For a positive (or zero) gyromagnetic ratio
 * (and positive spin quantum number) this is (0,1) in the (0.5,-0.5) basis.
 * See also SpinUp.
 */
class SpinDown : public SpinHalfStates
{
public:
  // Default for positive gyromagnetic ratio.
  SpinDown(); 
  SpinDown(const SpinHalfParameters& spin_half_parameters);
  
private:
  virtual void init(const double gyromagnetic_ratio);
  
};

} // namespace SpinDec

#endif // SPINDOWN_H_
