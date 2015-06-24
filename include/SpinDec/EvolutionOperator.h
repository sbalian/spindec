#ifndef EVOLUTIONOPERATOR_H_
#define EVOLUTIONOPERATOR_H_

// Seto Balian, Jun 24, 2015

#include "SpinDec/typedefs.h"
#include "SpinDec/SpinOperator.h"

namespace SpinDec
{

/// Free evolution operator.
class EvolutionOperator : public SpinOperator
{
private:
  
  double time_;
  
  /**
   * Not for the resulting opertor! These are used to construct the operator,
   * for example from a Hamiltonian.
   */
  ComplexMatrix eigenvectors_;
  /**
   * Not for the resulting opertor! These are used to construct the operator,
   * for example from a Hamiltonian.
   */
  RealVector eigenvalues_;
    
  void set_matrix();
  
public:
  EvolutionOperator();
  
  /** Unitary operator
   * \f[
   * \hat{U} = \sum_n \left(
   * \left|E_n\right\rangle \exp[- i E_n t] \left\langle E_n \right|
   * \right)
   * \f]
   * - \f$ E_n \f$: eigenvalues (real).
   * - \f$ \left| E_n \right\rangle \f$: eigenvectors.
   * - \f$ t \f$: time (real double) in microseconds
   * (energies in M rad s\f$^{-1}\f$).
   *
   * For time independent Hamiltonians.
   * 
   */ 
  EvolutionOperator(const SpinBasis& basis,
      const ComplexMatrix & eigenvectors,
      const RealVector & eigenvalues,
      const double time);
  
  /// Updates matrix.
  void set_time(const double time);
  double get_time() const;
  
};

} // namespace SpinDec

#endif // EVOLUTIONOPERATOR_H_
