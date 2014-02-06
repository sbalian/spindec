#ifndef HERMITIANEIGENSPECTRUM_H_
#define HERMITIANEIGENSPECTRUM_H_

// HermitianEigenspectrum
//
// Diagonalizes a Hermitian matrix.
// Eigenvectors are orthonormal, eigenvalues are always real.
// TODO ensure these conditions?
//
// Hermitian diagonalizers:
// DEFAULT "Eigen"  - SelfAdjointEigenSolver in Eigen
//         "Lapack" - Lapack zheev
//
// Seto Balian, Feb 6, 2014

#include "Eigenspectrum.h"

namespace SpinDecoherence
{

class HermitianEigenspectrum : public Eigenspectrum
{
private:
  
  // Diagonalizers
  virtual void diagonalize_eigen (const Eigen::MatrixXcd & matrix);
  virtual void diagonalize_lapack(const Eigen::MatrixXcd & matrix);
  
  virtual void diagonalize(const Eigen::MatrixXcd & matrix);

public:
  
  HermitianEigenspectrum();
  explicit HermitianEigenspectrum(const Eigen::MatrixXcd & matrix);
  HermitianEigenspectrum(const Eigen::MatrixXcd & matrix,
      const std::string & diagonalizer);
  
  // since eigenvectors orthonormal, V-1 = V^+,
  // so use faster (unitary) decomposition
  virtual Eigen::MatrixXcd spectralDecomposition() const;
  
  // TODO see base class, can you do this?
  //Eigen::VectorXd get_eigenvalues() const;
  //double get_eigenvalue(const unsigned int index) const;
  
};

} // namespace SpinDecoherence

#endif // HERMITIANEIGENSPECTRUM_H_
