#ifndef SPINOPERATOR_H_
#define SPINOPERATOR_H_

// SpinDec::SpinOperator
//
// Quantum spin operator in the Zeeman basis.
//
// Seto Balian, Oct 22, 2014

#include <complex>
#include <iostream>

#include "SpinDec/MatrixRepresentation.h"
#include "SpinDec/typedefs.h"
#include "SpinDec/SpinState.h"

namespace SpinDec
{

class SpinState;

class SpinOperator : public MatrixRepresentation
{
protected:

  ComplexMatrix matrix_;
  
  virtual void quit_if_dimension_mismatch() const;

public:
  SpinOperator();
    
  SpinOperator(const ComplexMatrix & matrix, const SpinBasis & basis);
  explicit SpinOperator(const SpinBasis & basis); // zero matrix

  const ComplexMatrix& get_matrix() const;
  void set_matrix(const ComplexMatrix & matrix);
    
  const CDouble& get_element(const UInt i,
      const UInt j) const;
  
  void set_element(const UInt i, const UInt j,
      const CDouble& element);
  void set_element(const UInt i, const UInt j,
      const double element); // stored as complex

  void add_to_element(const UInt i, const UInt j,
      const CDouble& to_add);

  // Operators: tensor product ^, Bases: combine ^ (like tensor product)
  SpinOperator operator^(const SpinOperator & rhs) const;
  SpinState operator*(const SpinState & operand) const;
  SpinOperator operator+(const SpinOperator & rhs) const;
  SpinOperator operator-(const SpinOperator & rhs) const;
  
  virtual void set_zero(); // set all elements to zero
  
  // Print with cout
  // TODO make this into a pure virtual function in MatrixRepresentation ...
  // and also implement in SpinState
  friend std::ostream& operator<<(std::ostream& os,
      SpinOperator const & spin_operator);
  
  virtual auto_ptr<MatrixRepresentation> clone() const;

};

} // namespace SpinDec

#endif // SPINOPERATOR_H_
