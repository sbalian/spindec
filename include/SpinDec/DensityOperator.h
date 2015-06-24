#ifndef DENSITYOPERATOR_H_
#define DENSITYOPERATOR_H_

// Seto Balian, Jun 24, 2015

#include "SpinDec/typedefs.h"
#include "SpinDec/SpinOperator.h"

namespace SpinDec
{

/**
 * In general, composite density operator for spins in the Zeeman basis.
 * \f$\rho_{\rm qubit} \otimes \rho_{\rm other}\f$, qubit states
 * \f$ \left| 0 \right \rangle \f$ and \f$ \left| 1 \right \rangle \f$.
 */
class DensityOperator : public SpinOperator
{
private:
  SpinState state0_;
  SpinState state1_;
  
  DensityOperator(const ComplexMatrix & matrix, const SpinBasis & basis,
      const SpinState& state0, const SpinState& state1);
  
public:
  DensityOperator();
  /// State is the combined (tensor product) qubit-other system state.
  DensityOperator(const SpinState& state,
                  const SpinState& state0,
                  const SpinState& state1);
  
  /// Return the qubit reduced density matrix.
  DensityOperator reduced() const;
  
  /// Off-diagonal of reduced density matrix.
  CDouble off_diagonal_reduced() const;
  
};

} // namespace SpinDec

#endif // DENSITYOPERATOR_H_
