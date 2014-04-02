// See CrystalBasis.h for description.
// Seto Balian, Apr 2, 2014

#include "SpinDec/CrystalBasis.h"

namespace SpinDec
{

void CrystalBasis::add_basis_vector(const ThreeVector& basis_vector)
{
  basis_vectors_.push_back(basis_vector);
  return;
}

CrystalBasis::CrystalBasis()
{
}

const std::vector<ThreeVector>& CrystalBasis::get_basis_vectors() const
{
  return basis_vectors_;
}

const ThreeVector& CrystalBasis::get_basis_vector(
    const UInt index) const
{
  return basis_vectors_[index];
}

UInt CrystalBasis::num_basis_vectors() const
{
  return basis_vectors_.size();
}

void CrystalBasis::clear_basis_vectors()
{
  basis_vectors_.clear();
  return;
}


} // namespace SpinDec

