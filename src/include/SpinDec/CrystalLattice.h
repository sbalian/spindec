#ifndef CRYSTALLATTICE_H_
#define CRYSTALLATTICE_H_

// SpinDec::CrystalLattice
//
// Lattice vectors for crystal structures.
//
// Seto Balian, Apr 2, 2014

#include "SpinDec/typedefs.h"
#include <vector>

namespace SpinDec
{

class CrystalLattice
{
protected:
  std::vector<ThreeVector> lattice_vectors_;

public:
  CrystalLattice();
  
  void add_lattice_vector(const ThreeVector& lattice_vector);
  
  const std::vector<ThreeVector>& get_lattice_vectors() const;
  const ThreeVector& get_lattice_vector(const UInt index) const;

  UInt num_lattice_vectors() const;
  double max_lattice_vector_length() const;
  
  void clear_lattice_vectors();

};

} // namespace SpinDec

#endif // CRYSTALLATTICE_H_
