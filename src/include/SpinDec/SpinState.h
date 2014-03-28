#ifndef SPINSTATE_H_
#define SPINSTATE_H_

// SpinDec::SpinState
//
// Quantum spin state in the Zeeman basis.
//
// Seto Balian, Mar 28, 2014

#include "SpinDec/MatrixRepresentation.h"
#include "SpinDec/typedefs.h"

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
