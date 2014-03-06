#ifndef SPINSTATE_H_
#define SPINSTATE_H_

// SpinState
//
// Quantum spin state in the Zeeman basis.
//
// Seto Balian, Mar 6, 2014

#include "SpinDec/SpinBasis.h"
#include "SpinDec/MatrixRepresentation.h"

#include "SpinDec/types.h"

namespace SpinDec
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

} // namespace SpinDec

#endif // SPINSTATE_H_
