#ifndef HERMITIANEIGENSPECTRUM_H_
#define HERMITIANEIGENSPECTRUM_H_

// HermitianEigenspectrum
//
// Diagonalizes a Hermitian matrix, holding its eigenvectors and eigenvalues.
// Eigenvectors stored column-wise.
//
// Diagonalizer types (dense):
//  Default "eigen" (SelfAdjointEigenSolver) or "zheev" (Lapack)
//
// Seto Balian, Dec 5, 2013

#include <Eigen/Dense>
#include <string>
#include <complex>

class HermitianEigenspectrum
{
private:
  
  Eigen::VectorXd eigenvalues_; // real
  Eigen::VectorXcd eigenvectors_; // complex
  
  void diagonalize_zheev(const Eigen::MatrixXcd & matrix);
  void diagonalize_eigen(const Eigen::MatrixXcd & matrix);
  
public:
  HermitianEigenspectrum();
  HermitianEigenspectrum(const Eigen::MatrixXcd & matrix);
  
  HermitianEigenspectrum(const Eigen::MatrixXcd & matrix,
      const std::string & diagonalizer_type);
  //  "eigen" (SelfAdjointEigenSolver) or "zheev" (Lapack)

  void diagonalize(const Eigen::MatrixXcd & matrix);
  void diagonalize(const Eigen::MatrixXcd & matrix,
      const std::string & diagonalizer_type);

  Eigen::VectorXd get_eigenvalues() const;
  Eigen::MatrixXcd get_eigenvectors() const;

  double get_eigenvalue(const unsigned int index) const;
  Eigen::VectorXcd get_eigenvector(const unsigned int index) const;

  // The spectral decomposition of a complex matrix is
  // A = V D V-1, where D is the diagonal of eigenvalues
  // and V is the eigenvector matrix (col -> evector).
  // For a Hermitian matrix, V-1 = V' and the eigenvalues are real.
  // This method gives A = V exp(a D) V-1 (where a is a complex number)
  // for Hermitian matrices.
  Eigen::MatrixXcd expSpectralDecomposition(
                                  const std::complex<double> & a) const;

};

#endif // HERMITIANEIGENSPECTRUM_H_
