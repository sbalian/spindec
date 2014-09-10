#ifndef CRYSTALBASIS_H_
#define CRYSTALBASIS_H_

// SpinDec::CrystalBasis
//
// Basis vectors for crystal structures in 3D. Length units are Angstroms.
// They are in the basis of lattice vectors (a1,a2,a3) NOT (x,y,z)!
//
// Seto Balian, Apr 7, 2014

#include "SpinDec/typedefs.h"

namespace SpinDec
{

class CrystalBasis
{
protected:
  std::vector<ThreeVector> basis_vectors_;
  
public:
  CrystalBasis();
  
  void add_basis_vector(const ThreeVector& basis_vector);
  const std::vector<ThreeVector>& get_basis_vectors() const;
  const ThreeVector& get_basis_vector(const UInt index) const;
  
  UInt num_basis_vectors() const;
  
};

} // namespace SpinDec

#endif // CRYSTALBASIS_H_
