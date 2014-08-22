// See Eigenspectrum.h for description.
// Seto Balian, Aug 22, 2014

#include "SpinDec/Eigenspectrum.h"
#include "SpinDec/BoostEigen.h"
#include "SpinDec/Errors.h"

namespace SpinDec
{

Eigenspectrum::Eigenspectrum()
{
}

Eigenspectrum::Eigenspectrum(const ComplexMatrix & matrix)
{
  diagonalize(matrix);
  return;
}

const ComplexVector& Eigenspectrum::get_eigenvalues() const
{
  return eigenvalues_;
}

const ComplexMatrix& Eigenspectrum::get_eigenvectors() const
{
  return eigenvectors_;
}

CDouble Eigenspectrum::get_eigenvalue(
    const UInt index) const
{
  return eigenvalues_(index);
}

ComplexVector Eigenspectrum::get_eigenvector(const UInt index) const
{
  return eigenvectors_.col(index);
}


Eigenspectrum::~Eigenspectrum()
{/**/
}

ComplexMatrix Eigenspectrum::spectralDecomposition() const
{
  return BoostEigen::spectralDecomposition(eigenvectors_,eigenvalues_);
}

void Eigenspectrum::diagonalize(const ComplexMatrix& matrix)
{
  
  Eigen::ComplexEigenSolver<ComplexMatrix> eigensolver(matrix.rows());
  eigensolver.compute(matrix);

  eigenvectors_ = eigensolver.eigenvectors();
  eigenvalues_  = eigensolver.eigenvalues();
  
  return;

}

void Eigenspectrum::set_spectrum(const ComplexMatrix & eigenvectors,
    const ComplexVector& eigenvalues)
{
  eigenvectors_ = eigenvectors;
  eigenvalues_ = eigenvalues;
  return;
}


} // namespace SpinDec
