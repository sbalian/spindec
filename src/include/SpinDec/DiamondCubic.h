#ifndef DIAMONDCUBIC_H_
#define DIAMONDCUBIC_H_

// SpinDec::DiamondCubic
//
// Diamond cubic crystal structure.
// TODO Comment
//
// Seto Balian, Apr 6, 2014

#include "SpinDec/typedefs.h"
#include "SpinDec/CrystalStructure.h"
#include "SpinDec/SimpleCubicLatticeVectors.h"
#include "SpinDec/CrystalBasis.h"

namespace SpinDec
{

class DiamondCubic : public CrystalStructure
{

private:
  SimpleCubicLatticeVectors construct_lattice_vectors(
      const double lattice_constant) const;
  CrystalBasis construct_basis_vectors() const;
  
  // get integer range for centred cube
  int int_range_centred_cube(
      const double side_length, const double lattice_constant) const;
  
  
public:
  DiamondCubic();
  DiamondCubic(const double lattice_constant, // cubic lattice constant in
               const double side_length);     // Angstroms

  DiamondCubic(const double lattice_constant,
               const double side_length,
               const double fractional_abundance,
               const int seed_uniform_c_rand);

};

} // namespace SpinDec

#endif // DIAMONDCUBIC_H_
