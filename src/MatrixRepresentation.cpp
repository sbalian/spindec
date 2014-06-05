// See MatrixRepresentation.h for description.
// Seto Balian, Jun 5, 2014

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

MatrixRepresentation::~MatrixRepresentation() {/**/}

} // namespace SpinDec
