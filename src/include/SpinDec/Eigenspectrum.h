#ifndef EIGENSPECTRUM_H_
#define EIGENSPECTRUM_H_

// SpinDec::Eigenspectrum
//
// Holds the eigenvectors and eigenvalues of a matrix and the diagonalizer
// type (see below for list of diagonalizers).
// Note: eigenvectors stored columnwise.
//
// General complex diagonalizers:
// DEFAULT "Eigen"  - ComplexEigenSolver in Eigen
//
// Seto Balian, May 21, 2014

#include <Eigen/Dense>
#include <complex>
#include <string>

#include "SpinDec/typedefs.h"

namespace SpinDec
{

class Eigenspectrum
{
protected:
  ComplexMatrix eigenvectors_;
  ComplexVector eigenvalues_;
  
  string diagonalizer_; // string (see above)

  explicit Eigenspectrum(const string & diagonalizer);
  
  // Diagonalizers
  virtual void diagonalize_eigen(const ComplexMatrix & matrix);
  virtual void diagonalize_lapack(const ComplexMatrix & matrix);
  
  void quit_if_diagonalizer_not_supported() const;
  
  virtual void diagonalize(const ComplexMatrix & matrix);

public:
  
  Eigenspectrum();
  Eigenspectrum(const ComplexMatrix & matrix);
  Eigenspectrum(const ComplexMatrix & matrix,
      const string & diagonalizer);

  
  const ComplexVector& get_eigenvalues() const;
  const ComplexMatrix& get_eigenvectors() const;

  CDouble get_eigenvalue(const UInt index) const;
  ComplexVector get_eigenvector(const UInt index)    const;
    
  const string& get_diagonalizer() const;

  virtual ~Eigenspectrum();
  
  // Note the Eigen naming convention here
  virtual ComplexMatrix spectralDecomposition() const;
  
};

} // namespace SpinDec

#endif // EIGENSPECTRUM_H_
