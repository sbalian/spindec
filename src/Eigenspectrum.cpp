// See Eigenspectrum.h for description.
// Seto Balian, Dec 9, 2013

#include "Eigenspectrum.h"
#include "BoostEigen.h"

Eigenspectrum::Eigenspectrum() : diagonalizer_("Eigen")
{
}

Eigenspectrum::Eigenspectrum(const std::string& diagonalizer) :
        diagonalizer_(diagonalizer)
{
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

Eigen::MatrixXcd Eigenspectrum::spectralDecomposition() const
{
  return BoostEigen::spectralDecomposition(eigenvectors_,eigenvalues_);
}
