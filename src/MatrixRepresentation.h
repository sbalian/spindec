#ifndef MATRIXREPRESENTATION_H_
#define MATRIXREPRESENTATION_H_

// MatrixRepresentation
//
// Abstract base class for SpinState and SpinOperator in the matrix
// representation. Holds the Zeeman basis and a dimension.
//
// Seto Balian, Feb 6, 2014

#include "SpinBasis.h"

namespace SpinDecoherence
{

class MatrixRepresentation
{

protected:
  
  unsigned dimension_; // dimension of Hilbert space

  MatrixRepresentation();
  explicit MatrixRepresentation(const unsigned int dimension);
  explicit MatrixRepresentation(const SpinBasis & basis);

  virtual void quit_if_dimension_mismatch() const = 0;
  
  SpinBasis basis_;

public:

  unsigned int get_dimension() const;
  
  SpinBasis get_basis() const;
  
  virtual void set_zero() = 0; // set all matrix elements to zero
  
  virtual ~MatrixRepresentation();
  
};

} // namespace SpinDecoherence

#endif // MATRIXREPRESENTATION_H_
