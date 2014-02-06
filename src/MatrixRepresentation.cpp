// See MatrixRepresentation.h for description.
// Seto Balian, Feb 6, 2014

#include "MatrixRepresentation.h"
#include "Errors.h"

namespace SpinDecoherence
{

MatrixRepresentation::MatrixRepresentation() : dimension_(0),
                                               basis_(SpinBasis())
{/**/}

MatrixRepresentation::MatrixRepresentation(const unsigned int dimension) :
    dimension_(dimension), basis_(SpinBasis(dimension))
{/**/}

MatrixRepresentation::MatrixRepresentation(const SpinBasis & basis) :
    dimension_(basis.dimension()), basis_(basis)
{/**/}


unsigned int MatrixRepresentation::get_dimension() const
{
  return dimension_;
}

SpinBasis MatrixRepresentation::get_basis() const
{
  return basis_;
}

MatrixRepresentation::~MatrixRepresentation() {/**/}

} // namespace SpinDecoherence
