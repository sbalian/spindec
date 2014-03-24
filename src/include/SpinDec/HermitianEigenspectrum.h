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
// Seto Balian, Mar 24, 2014

#include "SpinDec/Eigenspectrum.h"
#include "SpinDec/typedefs.h"

namespace SpinDec
{

class HermitianEigenspectrum : public Eigenspectrum
{
private:
  
  // Diagonalizers
  virtual void diagonalize_eigen (const ComplexMatrix & matrix);
  virtual void diagonalize_lapack(const ComplexMatrix & matrix);
  
  virtual void diagonalize(const ComplexMatrix & matrix);

public:
  
  HermitianEigenspectrum();
  explicit HermitianEigenspectrum(const ComplexMatrix & matrix);
  HermitianEigenspectrum(const ComplexMatrix & matrix,
      const string & diagonalizer);
  
  // since eigenvectors orthonormal, V-1 = V^+,
  // so use faster (unitary) decomposition
  virtual ComplexMatrix spectralDecomposition() const;
  
  // TODO see base class, can you do this?
  //Eigen::VectorXd get_eigenvalues() const;
  //double get_eigenvalue(const unsigned int index) const;
  
};

} // namespace SpinDec

#endif // HERMITIANEIGENSPECTRUM_H_
