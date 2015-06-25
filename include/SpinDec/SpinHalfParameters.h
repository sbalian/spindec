#ifndef SPINHALFPARAMETERS_H_
#define SPINHALFPARAMETERS_H_

// Seto Balian, Jun 25, 2015

#include "SpinDec/typedefs.h"
#include "SpinDec/SpinParameters.h"

namespace SpinDec
{

/// Spin-1/2 spin parameters.
class SpinHalfParameters : public SpinParameters
{
public:
  SpinHalfParameters();
  explicit SpinHalfParameters(const double gyromagnetic_ratio);
  
};

} // namespace SpinDec

#endif // SPINHALFPARAMETERS_H_
