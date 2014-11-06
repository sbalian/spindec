// See SpinState.h for description.
// Seto Balian, Nov 6, 2014

#include "SpinDec/SpinState.h"
#include "SpinDec/BoostEigen.h"
#include "SpinDec/Errors.h"

namespace SpinDec
{

SpinState::SpinState() : MatrixRepresentation()
{
  set_state_vector(ComplexVector::Zero(0)); // TODO Is this OK?
}

SpinState::SpinState(const ComplexVector & state_vector,
    const SpinBasis & basis) :
    MatrixRepresentation(basis)
{
  set_state_vector(state_vector);
}

SpinState::SpinState(const SpinBasis & basis) : MatrixRepresentation(basis)
{
  set_state_vector(ComplexVector::Zero(get_dimension()));
}

const ComplexVector& SpinState::get_state_vector() const
{
  return state_vector_;
}

void SpinState::set_state_vector(const ComplexVector & state_vector)
{
  state_vector_ = state_vector;
  quit_if_dimension_mismatch();
  return;
}

SpinState SpinState::operator^(const SpinState & rhs) const
{
  
  return SpinState( BoostEigen::tensorProduct(get_state_vector(),
                                              rhs.get_state_vector()) ,
      get_basis()^(rhs.get_basis()) );
}

CDouble SpinState::operator*(const SpinState & rhs) const
{
  quit_if_basis_mismatch(rhs.clone());
  return get_state_vector().adjoint()*rhs.get_state_vector();
}

SpinOperator SpinState::operator%(const SpinState & rhs) const
{
  quit_if_basis_mismatch(rhs.clone());
  return SpinOperator(get_state_vector()*(rhs.get_state_vector().adjoint()),
      get_basis());
}

void SpinState::quit_if_dimension_mismatch() const
{
  if (MatrixRepresentation::get_dimension() != state_vector_.rows()) {
    Errors::quit(
        "SpinState: State-vector and basis must have the same dimension!");
  }
  return;
}

void SpinState::time_evolve(const ComplexMatrix& unitary_evolution_matrix)
{
  state_vector_ = unitary_evolution_matrix*state_vector_;
  return;
}

const CDouble& SpinState::get_element(const UInt index) const
{
  return state_vector_(index);
}

void SpinState::set_element(const UInt index, const CDouble& element)
{
  state_vector_(index) = element;
  return;
}

void SpinState::set_element(const UInt index, const double element)
{
  state_vector_(index) = CDouble(element,0.0);
  return;
}

void SpinState::set_zero()
{
  state_vector_.setZero();
  return;
}

void SpinState::normalize()
{
  state_vector_.normalize();
  return;
}

SpinState SpinState::normalized() const
{
  return SpinState(get_state_vector().normalized(),get_basis());
}

SpinState SpinState::operator+(const SpinState& rhs) const
{
  quit_if_basis_mismatch(rhs.clone());
  return SpinState(get_state_vector()+rhs.get_state_vector(),get_basis());
}

SpinState SpinState::operator-(const SpinState& rhs) const
{
  quit_if_basis_mismatch(rhs.clone());
  return SpinState(get_state_vector()-rhs.get_state_vector(),get_basis());
}


auto_ptr<MatrixRepresentation> SpinState::clone() const
{
  return auto_ptr<MatrixRepresentation>( new SpinState(*this) );
}

SpinState SpinState::operator *(const CDouble& c) const
{
  return SpinState(get_state_vector()*c,get_basis());
}

} // namespace SpinDec
