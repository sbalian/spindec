#ifndef DIAMONDCUBIC_H_
#define DIAMONDCUBIC_H_

// SpinDec::DiamondCubic
//
// Diamond cubic crystal structure.
// This is implemented as a simple cubic lattice with 8 basis vectors.
// SOURCE: http://en.wikipedia.org/wiki/Diamond_cubic
//
// Seto Balian, Apr 16, 2015

#include "SpinDec/typedefs.h"
#include "SpinDec/CrystalStructure.h"
#include "SpinDec/SimpleCubicLatticeVectors.h"
#include "SpinDec/CrystalBasis.h"

namespace SpinDec
{

class DiamondCubic : public CrystalStructure
{

private:
  
  // set up and return the lattice vectors
  SimpleCubicLatticeVectors construct_lattice_vectors(
      const double lattice_constant) const;
  
  // get up and return the basis vectors
  CrystalBasis construct_basis_vectors() const;
  
  // get integer range (for constructing crystal structure) in a centred cube
  // given the side length
  int int_range_centred_cube(
      const double side_length, const double lattice_constant) const;
  
  
public:
  DiamondCubic();
  
  // cubic lattice constant in Angstroms
  // side length also in Angstroms
  DiamondCubic(const double lattice_constant, 
               const double side_length);
  
  DiamondCubic(const double lattice_constant,
               const double side_length,
               const double fractional_abundance);
  
  void make_sphere(const double radius);
  void make_shell(const double min_radius, const double max_radius);

};

} // namespace SpinDec

#endif // DIAMONDCUBIC_H_
