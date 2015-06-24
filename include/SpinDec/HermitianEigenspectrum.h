#ifndef HERMITIANEIGENSPECTRUM_H_
#define HERMITIANEIGENSPECTRUM_H_

// Seto Balian, Jun 24, 2015

// TODO Eigenvectors are orthonormal, eigenvalues are always real.
// TODO ensure these conditions?

#include "SpinDec/Eigenspectrum.h"
#include "SpinDec/typedefs.h"

namespace SpinDec
{

/**
 * \brief Diagonalizes a Hermitian matrix.
 * 
 * Eigenvectors are orthonormal, eigenvalues are always real.
 * 
 */
class HermitianEigenspectrum : public Eigenspectrum
{
private:
  
  /// Diagonalizer.
  void diagonalize_eigen (const ComplexMatrix & matrix);
  
  virtual void diagonalize(const ComplexMatrix & matrix);

public:
  
  HermitianEigenspectrum();
  explicit HermitianEigenspectrum(const ComplexMatrix & matrix);

  //void diagonalize_lapack(const ComplexMatrix & matrix);

    
  /**
   * Since eigenvectors orthonormal, \f$ V^{-1} = V{^\dagger}\f$,
   * use faster (unitary) decomposition.
   */
  virtual ComplexMatrix spectralDecomposition() const;
  
  // TODO see base class, can you do this?
  //Eigen::VectorXd get_eigenvalues() const;
  //double get_eigenvalue(const unsigned int index) const;
  
};

} // namespace SpinDec

#endif // HERMITIANEIGENSPECTRUM_H_

// Graveyard

//void diagonalize_lapack(const ComplexMatrix & matrix);

