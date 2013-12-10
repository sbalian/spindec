#ifndef EIGENSPECTRUM_H_
#define EIGENSPECTRUM_H_

// Eigenspectrum
//
// Holds the eigenvectors and eigenvalues of a matrix and the diagonalizer
// type (see below for list of diagonalizers).
// Note: eigenvectors stored columnwise.
//
// General complex diagonalizers:
// DEFAULT "Eigen"  - ComplexEigenSolver in Eigen
//
// Seto Balian, Dec 10, 2013

#include <Eigen/Dense>
#include <complex>
#include <string>

class Eigenspectrum
{
protected:
  Eigen::MatrixXcd eigenvectors_;
  Eigen::VectorXcd eigenvalues_;
  
  const std::string diagonalizer_; // string (see above)

  Eigenspectrum(const std::string & diagonalizer);
  
  // Diagonalizers
  virtual void diagonalize_eigen(const Eigen::MatrixXcd & matrix);
  virtual void diagonalize_lapack(const Eigen::MatrixXcd & matrix);
  
  void quit_if_diagonalizer_not_supported() const;
  
  virtual void diagonalize(const Eigen::MatrixXcd & matrix);

public:
  
  Eigenspectrum();
  Eigenspectrum(const Eigen::MatrixXcd & matrix);
  Eigenspectrum(const Eigen::MatrixXcd & matrix,
      const std::string & diagonalizer);

  
  Eigen::VectorXcd get_eigenvalues() const;
  Eigen::MatrixXcd get_eigenvectors() const;

  std::complex<double> get_eigenvalue(const unsigned int index) const;
  Eigen::VectorXcd get_eigenvector(const unsigned int index)    const;
    
  std::string get_diagonalizer() const;

  virtual ~Eigenspectrum();
  
  virtual Eigen::MatrixXcd spectralDecomposition() const;
  
};

#endif // EIGENSPECTRUM_H_
