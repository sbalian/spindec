// See Eigenspectrum.h for description.
// Seto Balian, Mar 6, 2014

#include "SpinDec/Eigenspectrum.h"
#include "SpinDec/BoostEigen.h"
#include "SpinDec/Errors.h"

namespace SpinDec
{

Eigenspectrum::Eigenspectrum() : diagonalizer_("Eigen")
{
}


Eigenspectrum::Eigenspectrum(const Eigen::MatrixXcd & matrix) :
    diagonalizer_("Eigen")
{
  diagonalize(matrix);
  return;
}

Eigenspectrum::Eigenspectrum(const Eigen::MatrixXcd & matrix,
    const std::string & diagonalizer) :
        diagonalizer_()
{
  diagonalize(matrix);
  return;
}

Eigen::VectorXcd Eigenspectrum::get_eigenvalues() const
{
  return eigenvalues_;
}

Eigen::MatrixXcd Eigenspectrum::get_eigenvectors() const
{
  return eigenvectors_;
}

std::complex<double> Eigenspectrum::get_eigenvalue(
    const unsigned int index) const
{
  return eigenvalues_(index);
}

Eigen::VectorXcd Eigenspectrum::get_eigenvector(const unsigned int index) const
{
  return eigenvectors_.col(index);
}

std::string Eigenspectrum::get_diagonalizer() const
{
  return diagonalizer_;
}

Eigenspectrum::~Eigenspectrum()
{/**/
}

void Eigenspectrum::diagonalize_eigen(const Eigen::MatrixXcd& matrix)
{
  Eigen::ComplexEigenSolver<Eigen::MatrixXcd> eigensolver(matrix.rows());
  eigensolver.compute(matrix);

  eigenvectors_ = eigensolver.eigenvectors();
  eigenvalues_  = eigensolver.eigenvalues();
  return;

}

void Eigenspectrum::diagonalize_lapack(const Eigen::MatrixXcd& matrix)
{
  quit_if_diagonalizer_not_supported();
  return;
}

void Eigenspectrum::quit_if_diagonalizer_not_supported() const
{
  std::string message = "Diagonalizer \"";
  message += diagonalizer_;
  message += "\" not supported.";
  Errors::quit(message);
  return;
}

Eigenspectrum::Eigenspectrum(const std::string& diagonalizer) :
    diagonalizer_(diagonalizer)
{
}

Eigen::MatrixXcd Eigenspectrum::spectralDecomposition() const
{
  return BoostEigen::spectralDecomposition(eigenvectors_,eigenvalues_);
}

void Eigenspectrum::diagonalize(const Eigen::MatrixXcd& matrix)
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
