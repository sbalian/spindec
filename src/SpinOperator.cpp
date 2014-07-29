// See SpinOperator.h for description.
// Seto Balian, Jul 29, 2014

#include "SpinDec/SpinOperator.h"
#include "SpinDec/BoostEigen.h"
#include "SpinDec/Errors.h"

namespace SpinDec
{

SpinOperator::SpinOperator() : MatrixRepresentation()
{
  set_matrix(ComplexMatrix::Zero(0,0)); // TODO Is this OK?
}

SpinOperator::SpinOperator(const ComplexMatrix & matrix,
    const SpinBasis & basis) :
    MatrixRepresentation(basis)
{
  set_matrix(matrix);
}

SpinOperator::SpinOperator(const SpinBasis & basis) :
    MatrixRepresentation(basis)
{
  set_matrix(ComplexMatrix::Zero(get_dimension(),get_dimension()));
}

const ComplexMatrix& SpinOperator::get_matrix() const
{
  return matrix_;
}

void SpinOperator::set_matrix(const ComplexMatrix & matrix)
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

const CDouble& SpinOperator::get_element(const UInt i,
    const UInt j) const
{
  return matrix_(i,j);
}

void SpinOperator::set_element(const UInt i, const UInt j,
    const CDouble& element)
{
  matrix_(i,j) = element;
  return;
}

void SpinOperator::set_element(const UInt i, const UInt j,
    const double element)
{
  matrix_(i,j) = CDouble(element,0.0);
  return;
}

void SpinOperator::add_to_element(const UInt i, const UInt j,
    const CDouble& to_add)
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

//std::auto_ptr<MatrixRepresentation> SpinOperator::clone() const
//{
//  return std::auto_ptr<MatrixRepresentation>( new SpinOperator(*this) );
//}

} // namespace SpinDec
