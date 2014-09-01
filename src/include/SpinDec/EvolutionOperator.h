#ifndef EVOLUTIONOPERATOR_H_
#define EVOLUTIONOPERATOR_H_

// SpinDec::EvolutionOperator
//
// Free evolution operator.
//
// Seto Balian, Sep 1, 2014

#include "SpinDec/typedefs.h"
#include "SpinDec/SpinOperator.h"


namespace SpinDec
{

class EvolutionOperator : public SpinOperator
{
private:
  
  double time_;
  
public:
  EvolutionOperator();
  // Unitary matrix
  // U = \sum{n} ( |E_n> exp(- i E_n t) <E_n| )
  // E_n: eigenvalues (real)
  // |E_n>: eigenvectors
  // t: time (real double) units: microseconds (energies in M rad s-1)
  // (for time independent spin Hamiltonians ...)
  
  EvolutionOperator(const SpinBasis& basis,
      const ComplexMatrix & eigenvectors,
      const RealVector & eigenvalues,
      const double time);
  
  double get_time() const;
  
};

} // namespace SpinDec

#endif // EVOLUTIONOPERATOR_H_
