#ifndef SPINSTATE_H_
#define SPINSTATE_H_

// SpinState
//
// Quantum spin state in the Zeeman basis.
//
// Seto Balian, Mar 5, 2014

#include "SpinBasis.h"
#include "MatrixRepresentation.h"

#include "types.h"

namespace SpinDecoherence
{

class SpinState : public MatrixRepresentation
{
private:
  
  ComplexVector state_vector_;

  virtual void quit_if_dimension_mismatch() const;
  
public:
  SpinState();
  SpinState(const ComplexVector & state_vector,
      const SpinBasis & basis);
  explicit SpinState(const SpinBasis & basis); // zero state vector

  const ComplexVector& get_state_vector() const;
  void set_state_vector(const ComplexVector & state_vector);
  
  // States: tensor product ^, Bases: combine ^ (like tensor product)
  SpinState operator^(const SpinState & rhs);
  
  virtual void set_zero(); // set all elements to zero
    
};

} // namespace SpinDecoherence

#endif // SPINSTATE_H_
