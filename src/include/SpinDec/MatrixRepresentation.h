#ifndef MATRIXREPRESENTATION_H_
#define MATRIXREPRESENTATION_H_

// MatrixRepresentation
//
// Abstract base class for SpinState and SpinOperator in the matrix
// representation. Holds the Zeeman basis and a dimension.
//
// Seto Balian, Mar 24, 2014

#include "SpinDec/SpinBasis.h"
#include "SpinDec/typedefs.h"

namespace SpinDec
{

class MatrixRepresentation
{

protected:
  
  UInt dimension_; // dimension of Hilbert space
  SpinBasis basis_;

  MatrixRepresentation();
  explicit MatrixRepresentation(const SpinBasis & basis);
  
  // TODO Can you avoid using this? Eigen allows = between different sized
  // vectors/matrices ...
  virtual void quit_if_dimension_mismatch() const = 0;

public:

  UInt get_dimension() const;
  
  const SpinBasis& get_basis() const;
  
  virtual void set_zero() = 0; // set all elements to zero
  
  virtual ~MatrixRepresentation();
  
};

} // namespace SpinDec

#endif // MATRIXREPRESENTATION_H_
