#ifndef SPINOPERATOR_H_
#define SPINOPERATOR_H_

// Seto Balian, Jun 25, 2015

#include <complex>
#include <iostream>

#include "SpinDec/MatrixRepresentation.h"
#include "SpinDec/typedefs.h"
#include "SpinDec/SpinState.h"

namespace SpinDec
{

class SpinState;

/// Quantum spin operator in the Zeeman basis.
class SpinOperator : public MatrixRepresentation
{
protected:

  ComplexMatrix matrix_;
  
  virtual void quit_if_dimension_mismatch() const;

public:
  SpinOperator();
    
  SpinOperator(const ComplexMatrix & matrix, const SpinBasis & basis);
  
  /// Zero matrix.
  explicit SpinOperator(const SpinBasis & basis);

  const ComplexMatrix& get_matrix() const;
  void set_matrix(const ComplexMatrix & matrix);
    
  const CDouble& get_element(const UInt i,
      const UInt j) const;
  
  void set_element(const UInt i, const UInt j,
      const CDouble& element);
  
  /// Stored as complex.
  void set_element(const UInt i, const UInt j,
      const double element); 

  void add_to_element(const UInt i, const UInt j,
      const CDouble& to_add);

  /// Operators: tensor product ^, Bases: combine ^ (like tensor product).
  SpinOperator operator^(const SpinOperator & rhs) const;
  SpinState operator*(const SpinState & operand) const;
  SpinOperator operator+(const SpinOperator & rhs) const;
  SpinOperator operator-(const SpinOperator & rhs) const;
  
  /// Set all elements to zero.
  virtual void set_zero(); 
  
  /// Print with cout.
  friend std::ostream& operator<<(std::ostream& os,
      SpinOperator const & spin_operator);
  // TODO make this into a pure virtual function in MatrixRepresentation ...
  // and also implement in SpinState

  
  virtual shared_ptr<MatrixRepresentation> clone() const;

};

} // namespace SpinDec

#endif // SPINOPERATOR_H_
