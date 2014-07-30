// See MatrixRepresentation.h for description.
// Seto Balian, Jul 30, 2014

#include "SpinDec/MatrixRepresentation.h"
#include "SpinDec/Errors.h"

namespace SpinDec
{

MatrixRepresentation::MatrixRepresentation() :
    dimension_(0),
    basis_(SpinBasis()) 
{/**/}

MatrixRepresentation::MatrixRepresentation(const SpinBasis & basis) :
    dimension_(basis.num_basis_states()),
    basis_(basis)
{/**/}

UInt MatrixRepresentation::get_dimension() const
{
  return dimension_;
}

const SpinBasis& MatrixRepresentation::get_basis() const
{
  return basis_;
}

void MatrixRepresentation::quit_if_basis_mismatch(
    const std::auto_ptr<MatrixRepresentation>& to_check) const
{
  if (!( get_basis().is_equal(to_check->get_basis()) )) {
    Errors::quit("Basis mismatch.");
  }
  return;
}

MatrixRepresentation::~MatrixRepresentation() {/**/}

} // namespace SpinDec

