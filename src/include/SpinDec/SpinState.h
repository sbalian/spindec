#ifndef SPINSTATE_H_
#define SPINSTATE_H_

// SpinDec::SpinState
//
// Quantum spin state in the Zeeman basis.
//
// Seto Balian, Apr 1, 2014

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
  explicit SpinState(const SpinInteractionGraph& graph,
                     const UInt vertex_label); // zero state vector

  const ComplexVector& get_state_vector() const;
  void set_state_vector(const ComplexVector & state_vector);
  
  const CDouble& get_element(const UInt index) const;
  
  void set_element(const UInt index,
      const CDouble& element);
  void set_element(const UInt index,
        const double element); // stored as complex
  
  // States: tensor product ^, Bases: combine ^ (like tensor product)
  SpinState operator^(const SpinState & rhs);
  
  // Multiplies state_vector_ with unitary_evolution_matrix
  void time_evolve(const ComplexMatrix& unitary_evolution_matrix);
  
  virtual void set_zero(); // set all elements to zero

};

} // namespace SpinDec

#endif // SPINSTATE_H_
