// See Eigenspectrum.h for description.
// Seto Balian, Mar 24, 2014

#include "SpinDec/Eigenspectrum.h"
#include "SpinDec/BoostEigen.h"
#include "SpinDec/Errors.h"

namespace SpinDec
{

Eigenspectrum::Eigenspectrum() : diagonalizer_("Eigen")
{
}


Eigenspectrum::Eigenspectrum(const ComplexMatrix & matrix) :
    diagonalizer_("Eigen")
{
  diagonalize(matrix);
  return;
}

Eigenspectrum::Eigenspectrum(const ComplexMatrix & matrix,
    const string & diagonalizer) :
        diagonalizer_()
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

const string& Eigenspectrum::get_diagonalizer() const
{
  return diagonalizer_;
}

Eigenspectrum::~Eigenspectrum()
{/**/
}

void Eigenspectrum::diagonalize_eigen(const ComplexMatrix& matrix)
{
  Eigen::ComplexEigenSolver<ComplexMatrix> eigensolver(matrix.rows());
  eigensolver.compute(matrix);

  eigenvectors_ = eigensolver.eigenvectors();
  eigenvalues_  = eigensolver.eigenvalues();
  return;

}

void Eigenspectrum::diagonalize_lapack(const ComplexMatrix& matrix)
{
  quit_if_diagonalizer_not_supported();
  return;
}

void Eigenspectrum::quit_if_diagonalizer_not_supported() const
{
  string message = "Diagonalizer \"";
  message += diagonalizer_;
  message += "\" not supported.";
  Errors::quit(message);
  return;
}

Eigenspectrum::Eigenspectrum(const string& diagonalizer) :
    diagonalizer_(diagonalizer)
{
}

ComplexMatrix Eigenspectrum::spectralDecomposition() const
{
  return BoostEigen::spectralDecomposition(eigenvectors_,eigenvalues_);
}

void Eigenspectrum::diagonalize(const ComplexMatrix& matrix)
{
  
  if (diagonalizer_ == "Eigen") {
    diagonalize_eigen(matrix);
    return;
  }
  
  // else
  quit_if_diagonalizer_not_supported();
  return;

}

} // namespace SpinDec
