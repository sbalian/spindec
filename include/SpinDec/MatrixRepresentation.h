#ifndef MATRIXREPRESENTATION_H_
#define MATRIXREPRESENTATION_H_

// Seto Balian, Jun 24, 2015

#include "SpinDec/SpinBasis.h"
#include "SpinDec/typedefs.h"

namespace SpinDec
{

/**
 * Abstract base class for spin states and operators in the matrix
 * representation. Has a SpinBasis (Zeeman basis) and a dimension.
 */
class MatrixRepresentation
{

protected:
  
  /// Dimension of Hilbert space.
  UInt dimension_; 
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
  
  /// Set all elements to zero.
  virtual void set_zero() = 0; 
  
  virtual ~MatrixRepresentation();
  
  virtual auto_ptr<MatrixRepresentation> clone() const = 0;
  
};

} // namespace SpinDec

#endif // MATRIXREPRESENTATION_H_
