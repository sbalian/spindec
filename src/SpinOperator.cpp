// See SpinOperator.h for description.
// Seto Balian, Dec 10, 2013

#include "SpinOperator.h"
#include "BoostEigen.h"
#include "Errors.h"

SpinOperator::SpinOperator() : MatrixRepresentation()
{/**/}

SpinOperator::SpinOperator(const Eigen::MatrixXcd & matrix,
    const SpinBasis & basis) :
    MatrixRepresentation(basis)
{
  set_matrix(matrix);
}

SpinOperator::SpinOperator(const SpinBasis & basis) :
    MatrixRepresentation(basis)
{
  set_matrix(Eigen::MatrixXcd::Zero(get_dimension(),get_dimension()));
}

Eigen::MatrixXcd SpinOperator::get_matrix() const
{
  return matrix_;
}

void SpinOperator::set_matrix(const Eigen::MatrixXcd & matrix)
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
  matrix_.setZero(get_dimension(),get_dimension());
  return;
}
