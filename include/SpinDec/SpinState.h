#ifndef SPINSTATE_H_
#define SPINSTATE_H_

// Seto Balian, Jun 25, 2015

#include "SpinDec/MatrixRepresentation.h"
#include "SpinDec/typedefs.h"
#include "SpinDec/SpinOperator.h"

namespace SpinDec
{

class SpinOperator;

/// Quantum spin state in the Zeeman basis.
class SpinState : public MatrixRepresentation
{
protected:
  
  ComplexVector state_vector_;
  virtual void quit_if_dimension_mismatch() const;
  
public:
  SpinState();
  
  SpinState(const ComplexVector & state_vector,
      const SpinBasis & basis);
  
  /// Zero state vector.
  explicit SpinState(const SpinBasis & basis);

  const ComplexVector& get_state_vector() const;
  virtual void set_state_vector(const ComplexVector & state_vector);
  
  const CDouble& get_element(const UInt index) const;
  
  virtual void set_element(const UInt index,
      const CDouble& element);
  
  /// Stored as complex.
  virtual void set_element(const UInt index,
        const double element);
  
  /// States: tensor product ^, Bases: combine ^ (like tensor product).
  SpinState operator^(const SpinState & rhs) const;
  
  /// Inner product.
  CDouble operator*(const SpinState & rhs) const;
  
  /// Outer product.
  SpinOperator operator%(const SpinState & rhs) const;
  
  SpinState operator+(const SpinState & rhs) const;
  SpinState operator-(const SpinState & rhs) const;
  
  SpinState operator*(const CDouble & c) const;

  
  /// Multiplies state_vector_ with unitary_evolution_matrix.
  void time_evolve(const ComplexMatrix& unitary_evolution_matrix);
  
  /// Set all elements to zero.
  virtual void set_zero();
  
  void normalize();
  SpinState normalized() const;
  
  virtual auto_ptr<MatrixRepresentation> clone() const;

};

} // namespace SpinDec

#endif // SPINSTATE_H_
