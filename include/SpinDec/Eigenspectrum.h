#ifndef EIGENSPECTRUM_H_
#define EIGENSPECTRUM_H_

// Seto Balian, Jun 24, 2015

#include <complex>

#include "SpinDec/typedefs.h"

namespace SpinDec
{

/**
 * \brief Holds the eigenvectors and eigenvalues of a matrix.
 * 
 * Note: eigenvectors stored columnwise.
 * General complex diagonalizer: ComplexEigenSolver in Eigen.
 * 
 */
class Eigenspectrum
{
protected:
  ComplexMatrix eigenvectors_;
  ComplexVector eigenvalues_;
  
  virtual void diagonalize(const ComplexMatrix & matrix);

public:
  
  Eigenspectrum();
  explicit Eigenspectrum(const ComplexMatrix & matrix);

  const ComplexVector& get_eigenvalues() const;
  const ComplexMatrix& get_eigenvectors() const;

  CDouble get_eigenvalue(const UInt index) const;
  ComplexVector get_eigenvector(const UInt index)  const;
  
  virtual ~Eigenspectrum();
  
  /// Note the Eigen naming convention here.
  virtual ComplexMatrix spectralDecomposition() const;
  
  /// NOTE: use with care.
  void set_spectrum(const ComplexMatrix & eigenvectors,
      const ComplexVector& eigenvalues);
  
};

} // namespace SpinDec

#endif // EIGENSPECTRUM_H_
