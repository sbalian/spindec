#ifndef DENSITYOPERATOR_H_
#define DENSITYOPERATOR_H_

// SpinDec::DensityOperator
//
// In general, composite density operator for spins in the Zeeman basis.
// P_qubit X(tensor) P_other
// Qubit states |0> and |1>.
//
// Seto Balian, Jul 30, 2014

#include "SpinDec/typedefs.h"
#include "SpinDec/SpinOperator.h"

namespace SpinDec
{

class DensityOperator : public SpinOperator
{
private:
  SpinState state0_;
  SpinState state1_;
  
  DensityOperator(const ComplexMatrix & matrix, const SpinBasis & basis,
      const SpinState& state0, const SpinState& state1);
  
public:
  DensityOperator();
  // state is the combined (tensor product) qubit-other system state
  DensityOperator(const SpinState& state,
                  const SpinState& state0,
                  const SpinState& state1);
  
  // return the qubit reduced density matrix
  DensityOperator reduced() const;
  
  // off-diagonal of reduced density matrix
  CDouble off_diagonal_reduced() const;
  
};

} // namespace SpinDec

#endif // DENSITYOPERATOR_H_
