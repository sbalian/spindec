// See MatrixRepresentation.h for description.
// Seto Balian, Feb 19, 2014

#include "MatrixRepresentation.h"
#include "Errors.h"

namespace SpinDecoherence
{

MatrixRepresentation::MatrixRepresentation() :
    dimension_(0),
    basis_(SpinBasis()) 
{/**/}

MatrixRepresentation::MatrixRepresentation(const SpinBasis & basis) :
    dimension_(basis.num_basis_states()),
    basis_(basis)
{/**/}

unsigned int MatrixRepresentation::get_dimension() const
{
  return dimension_;
}

const SpinBasis& MatrixRepresentation::get_basis() const
{
  return basis_;
}

MatrixRepresentation::~MatrixRepresentation() {/**/}

} // namespace SpinDecoherence
