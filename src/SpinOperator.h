#ifndef SPINOPERATOR_H_
#define SPINOPERATOR_H_

// SpinOperator
//
// Quantum spin operator in the Zeeman basis.
//
// Seto Balian, Mar 5, 2014

#include <complex>
#include <iostream>

#include "SpinBasis.h"
#include "MatrixRepresentation.h"

#include "types.h"

namespace SpinDecoherence
{

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
  
  const cdouble& get_element(const unsigned int i,
      const unsigned int j) const;
  void set_element(const unsigned int i, const unsigned int j,
      const cdouble& element);
  
  void add_to_element(const unsigned int i, const unsigned int j,
      const cdouble& to_add);

  // Operators: tensor product ^, Bases: combine ^ (like tensor product)
  SpinOperator operator^(const SpinOperator & rhs);
  
  virtual void set_zero(); // set all elements to zero
  
  // Print with cout
  // TODO make this into a pure virtual function in MatrixRepresentation ...
  // and also implement in SpinState
  friend std::ostream& operator<<(std::ostream& os,
      SpinOperator const & spin_operator);

};

} // namespace SpinDecoherence

#endif // SPINOPERATOR_H_
