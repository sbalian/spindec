#ifndef DENSITYOPERATOR_H_
#define DENSITYOPERATOR_H_

// SpinDec::DensityOperator
//
// Density operator for spins in the Zeeman basis.
//
// Seto Balian, Jun 2, 2014

#include "SpinDec/typedefs.h"
#include "SpinDec/SpinOperator.h"
#include "SpinDec/SpinState.h"

namespace SpinDec
{

class DensityOperator : public SpinOperator
{
public:
  DensityOperator();
  
  explicit DensityOperator(const SpinState& state);
      
};

} // namespace SpinDec

#endif // DENSITYOPERATOR_H_
