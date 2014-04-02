// See CrystalLattice.h for description.
// Seto Balian, Apr 2, 2014

#include "SpinDec/CrystalLattice.h"
#include <algorithm>

namespace SpinDec
{

void CrystalLattice::add_lattice_vector(
    const ThreeVector& lattice_vector)
{
  lattice_vectors_.push_back(lattice_vector);
  return;
}

CrystalLattice::CrystalLattice()
{
}

const std::vector<ThreeVector>& CrystalLattice::get_lattice_vectors() const
{
  return lattice_vectors_;
}

const ThreeVector& CrystalLattice::get_lattice_vector(
    const UInt index) const
{
  return lattice_vectors_[index];
}

UInt CrystalLattice::num_lattice_vectors() const
{
  return lattice_vectors_.size();
}

double CrystalLattice::max_lattice_vector_length() const
{
  DoubleArray lengths;
  for (UInt i=0;i < num_lattice_vectors();i++) {
    lengths.push_back(get_lattice_vector(i).norm());
  }
  return *max_element(lengths.begin(),lengths.end());
}

void CrystalLattice::clear_lattice_vectors()
{
  lattice_vectors_.clear();
  return;
}

} // namespace SpinDec

