// See EvolutionOperator.h for description.
// Seto Balian, Sep 1, 2014

#include "SpinDec/EvolutionOperator.h"
#include "SpinDec/BoostEigen.h"

namespace SpinDec
{

EvolutionOperator::EvolutionOperator() : time_(0.0)
{
  
}

EvolutionOperator::EvolutionOperator(const SpinBasis& basis,
    const ComplexMatrix& eigenvectors, const RealVector& eigenvalues,
    const double time) : SpinOperator(
        BoostEigen::unitarySpectralDecomposition(eigenvectors,
        BoostEigen::exp( eigenvalues.cast< CDouble >() * 
                         std::complex<double>(0.0,-time) ) ),basis),
                         time_(time)
{
  
}

double EvolutionOperator::get_time() const
{
  return time_;
}

} // namespace SpinDec

