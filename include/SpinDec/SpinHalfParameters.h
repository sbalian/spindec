#ifndef SPINHALFPARAMETERS_H_
#define SPINHALFPARAMETERS_H_

// SpinDec::SpinHalfParameters
//
// Spin-1/2 spin parameters.
//
// Seto Balian, Sep 25, 2014

#include "SpinDec/typedefs.h"
#include "SpinDec/SpinParameters.h"

namespace SpinDec
{

class SpinHalfParameters : public SpinParameters
{
public:
  SpinHalfParameters();
  explicit SpinHalfParameters(const double gyromagnetic_ratio);
  
};

} // namespace SpinDec

#endif // SPINHALFPARAMETERS_H_
