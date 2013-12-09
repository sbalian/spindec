#ifndef EIGENSPECTRUM_H_
#define EIGENSPECTRUM_H_

// Eigenspectrum
//
// Holds the eigenvectors and eigenvalues of a matrix and the diagonalizer
// type (see below for list of diagonalizers).
// Note: eigenvectors stored columnwise.
//
// Hermitian diagonalizers:
// DEFAULT "Eigen"  - SelfAdjointEigenSolver in Eigen
//         "Lapack" - Lapack zheev
//
// Seto Balian, Dec 9, 2013

#include <Eigen/Dense>
#include <complex>
#include <string>

class Eigenspectrum
{
protected:
  Eigen::MatrixXcd eigenvectors_;
  Eigen::VectorXcd eigenvalues_;
  
  const std::string diagonalizer_; // string (see above)

  Eigenspectrum();
  Eigenspectrum(const std::string & diagonalizer);
  
public:
  
  Eigen::VectorXcd get_eigenvalues() const;
  Eigen::MatrixXcd get_eigenvectors() const;

  std::complex<double> get_eigenvalue(const unsigned int index) const;
  Eigen::VectorXcd get_eigenvector(const unsigned int index)    const;
  
  virtual void diagonalize(const Eigen::MatrixXcd & matrix) = 0;
  
  std::string get_diagonalizer() const;

  virtual ~Eigenspectrum();
  
  virtual Eigen::MatrixXcd spectralDecomposition() const;
  
};

#endif // EIGENSPECTRUM_H_
