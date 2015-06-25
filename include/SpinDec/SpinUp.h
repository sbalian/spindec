#ifndef SPINUP_H_
#define SPINUP_H_

// Seto Balian, Jun 25, 2015

#include "SpinDec/typedefs.h"
#include "SpinDec/SpinHalfStates.h"

namespace SpinDec
{

/**
 * \brief Spin up state.
 * 
 * For a positive (or zero) gyromagnetic ratio (and positive spin
 * quantum number) this is (1,0) in the (0.5,-0.5) basis. See also SpinDown.
 * 
 */
class SpinUp : public SpinHalfStates
{
public:
  /// Default for positive gyromagnetic ratio.
  SpinUp();
  SpinUp(const SpinHalfParameters& spin_half_parameters);
  
private:
  virtual void init(const double gyromagnetic_ratio);
  
};

} // namespace SpinDec

#endif // SPINUP_H_
