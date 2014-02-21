// See SpinOperator.h for description.
// Seto Balian, Feb 21, 2014

#include "SpinOperator.h"
#include "BoostEigen.h"
#include "Errors.h"

namespace SpinDecoherence
{

SpinOperator::SpinOperator() : MatrixRepresentation()
{
  set_matrix(cdmatrix::Zero(0,0)); // TODO Is this OK?
}

SpinOperator::SpinOperator(const cdmatrix & matrix,
    const SpinBasis & basis) :
    MatrixRepresentation(basis)
{
  set_matrix(matrix);
}

SpinOperator::SpinOperator(const SpinBasis & basis) :
    MatrixRepresentation(basis)
{
  set_matrix(cdmatrix::Zero(get_dimension(),get_dimension()));
}

const cdmatrix& SpinOperator::get_matrix() const
{
  return matrix_;
}

void SpinOperator::set_matrix(const cdmatrix & matrix)
{
  matrix_ = matrix;
  quit_if_dimension_mismatch();
  return;
}

SpinOperator SpinOperator::operator^(const SpinOperator & rhs)
{
  return SpinOperator( BoostEigen::tensorProduct(get_matrix(),
      rhs.get_matrix()) ,
      get_basis()^(rhs.get_basis()) );
}

// TODO Very similar to SpinState method, put in MatrixRepresentation?
void SpinOperator::quit_if_dimension_mismatch() const
{
  if (MatrixRepresentation::get_dimension() != matrix_.rows()) {
    Errors::quit("SpinOperator: Operator and basis must have the same/"
                 "dimension!");
  }
  return;
}

void SpinOperator::set_zero()
{
  matrix_.setZero();
  return;
}

const cdouble& SpinOperator::get_element(const unsigned int i,
    const unsigned int j) const
{
  return matrix_(i,j);
}

void SpinOperator::set_element(const unsigned int i, const unsigned int j,
    const cdouble& element)
{
  matrix_(i,j) = element;
  return;
}

void SpinOperator::add_to_element(const unsigned int i, const unsigned int j,
    const cdouble& to_add)
{
  matrix_(i,j) += to_add;
  return;
}

std::ostream& operator<<(std::ostream& os,
    SpinOperator const & spin_operator)
{

  // To restore formatting later
  std::ios::fmtflags f( std::cout.flags() );
  
  os << spin_operator.get_matrix() << std::endl;
  
  // Restore formatting
  std::cout.flags( f );
  
  return os;
}


} // namespace SpinDecoherence
