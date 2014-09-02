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
    const double time) : SpinOperator(basis)
{
  
  time_ = time;
  eigenvectors_ = eigenvectors;
  eigenvalues_ = eigenvalues;
  
  set_matrix();
  
}

double EvolutionOperator::get_time() const
{
  return time_;
}

void EvolutionOperator::set_matrix()
{
  SpinOperator::set_matrix(
      BoostEigen::unitarySpectralDecomposition(eigenvectors_,
      BoostEigen::exp( eigenvalues_.cast< CDouble >() * 
                       std::complex<double>(0.0,-time_) ) ));
  return;
}

void EvolutionOperator::set_time(const double time)
{
  time_ = time;
  set_matrix();
  return;
}


} // namespace SpinDec

