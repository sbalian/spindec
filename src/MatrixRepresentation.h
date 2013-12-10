#ifndef MATRIXREPRESENTATION_H_
#define MATRIXREPRESENTATION_H_

// MatrixRepresentation
//
// Abstract base class for SpinState and SpinOperator in the matrix
// representation. Holds the Zeeman basis and a dimension.
//
// Seto Balian, Dec 10, 2013

#include "SpinBasis.h"

class MatrixRepresentation
{

protected:
  
  unsigned dimension_; // dimension of Hilbert space

  MatrixRepresentation();
  MatrixRepresentation(const unsigned int dimension);
  MatrixRepresentation(const SpinBasis & basis);

  virtual void quit_if_dimension_mismatch() const = 0;
  
  SpinBasis basis_;

public:

  unsigned int get_dimension() const;
  
  SpinBasis get_basis() const;
  
  virtual void set_zero() = 0; // set all matrix elements to zero
  
  virtual ~MatrixRepresentation();
  
};

#endif // MATRIXREPRESENTATION_H_
