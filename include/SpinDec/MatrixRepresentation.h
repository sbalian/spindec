#ifndef MATRIXREPRESENTATION_H_
#define MATRIXREPRESENTATION_H_

// SpinDec::MatrixRepresentation
//
// Abstract base class for spin states and operators in the matrix
// representation. Has a SpinBasis (Zeeman basis) and a dimension.
//
// Seto Balian, Nov 6, 2014

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
  
  void quit_if_basis_mismatch(const auto_ptr<MatrixRepresentation>&
      to_check) const;
    
public:

  UInt get_dimension() const;
  
  const SpinBasis& get_basis() const;
  
  bool is_basis_equal(const auto_ptr<MatrixRepresentation>&
      to_check) const;
  
  virtual void set_zero() = 0; // set all elements to zero
  
  virtual ~MatrixRepresentation();
  
  virtual auto_ptr<MatrixRepresentation> clone() const = 0;
  
};

} // namespace SpinDec

#endif // MATRIXREPRESENTATION_H_
