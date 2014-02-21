#ifndef SPINSTATE_H_
#define SPINSTATE_H_

// SpinState
//
// Quantum spin state in the Zeeman basis.
//
// Seto Balian, Feb 21, 2014

#include "SpinBasis.h"
#include "MatrixRepresentation.h"

#include "types.h"

namespace SpinDecoherence
{

class SpinState : public MatrixRepresentation
{
private:
  
  cdvector state_vector_;

  virtual void quit_if_dimension_mismatch() const;
  
public:
  SpinState();
  SpinState(const cdvector & state_vector,
      const SpinBasis & basis);
  explicit SpinState(const SpinBasis & basis); // zero state vector

  const cdvector& get_state_vector() const;
  void set_state_vector(const cdvector & state_vector);
  
  // States: tensor product ^, Bases: combine ^ (like tensor product)
  SpinState operator^(const SpinState & rhs);
  
  virtual void set_zero(); // set all elements to zero
    
};

} // namespace SpinDecoherence

#endif // SPINSTATE_H_
