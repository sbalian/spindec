// See DiamondCubic.h for description.
// Seto Balian, Jan 13, 2015

#include "SpinDec/DiamondCubic.h"
#include "SpinDec/SimpleCubicLatticeVectors.h"
#include "SpinDec/CrystalBasis.h"

namespace SpinDec
{

int DiamondCubic::int_range_centred_cube(
    const double side_length, const double lattice_constant) const
{
  // Given possible rounding of doubles, the final 1 is added to ensure
  // the int range is big enough to always include the cube of side length.
  // The fill method then excludes vectors based on their spatial lengths.
  return static_cast<int>(side_length / (lattice_constant*2.0)) + 1;
}

SimpleCubicLatticeVectors DiamondCubic::construct_lattice_vectors(
    const double lattice_constant) const
{
  // a simple cubic lattice
  return SimpleCubicLatticeVectors(lattice_constant);
}

CrystalBasis DiamondCubic::construct_basis_vectors() const
{
  CrystalBasis basis;
  
  ThreeVector basis_vector;
  
  // (a simple cubic lattice) with 8 basis vectors
  
  // SOURCE: http://en.wikipedia.org/wiki/Diamond_cubic

  basis_vector(0) = 0.0;
  basis_vector(1) = 0.0;
  basis_vector(2) = 0.0;
  basis.add_basis_vector(basis_vector);
  
  basis_vector(0) = 0.0;
  basis_vector(1) = 0.5;
  basis_vector(2) = 0.5;
  basis.add_basis_vector(basis_vector);

  basis_vector(0) = 0.5;
  basis_vector(1) = 0.0;
  basis_vector(2) = 0.5;
  basis.add_basis_vector(basis_vector);

  basis_vector(0) = 0.5;
  basis_vector(1) = 0.5;
  basis_vector(2) = 0.0;
  basis.add_basis_vector(basis_vector);

  basis_vector(0) = 0.75;
  basis_vector(1) = 0.75;
  basis_vector(2) = 0.75;
  basis.add_basis_vector(basis_vector);

  basis_vector(0) = 0.75;
  basis_vector(1) = 0.25;
  basis_vector(2) = 0.25;
  basis.add_basis_vector(basis_vector);

  basis_vector(0) = 0.25;
  basis_vector(1) = 0.75;
  basis_vector(2) = 0.25;
  basis.add_basis_vector(basis_vector);

  basis_vector(0) = 0.25;
  basis_vector(1) = 0.25;
  basis_vector(2) = 0.75;
  basis.add_basis_vector(basis_vector);

  return basis;

}

DiamondCubic::DiamondCubic()
{
}

DiamondCubic::DiamondCubic(const double lattice_constant,
    const double side_length)
{
  // get the int range
  const int int_range = int_range_centred_cube(side_length, lattice_constant);
    
  // add all site vectors of the crystal structure
  fill_site_vectors(construct_lattice_vectors(lattice_constant),
      construct_basis_vectors(),
      -int_range,int_range,
      -int_range,int_range,
      -int_range,int_range,
      -side_length/2.0,side_length/2.0,
      -side_length/2.0,side_length/2.0,
      -side_length/2.0,side_length/2.0,1.0);
  
}

DiamondCubic::DiamondCubic(const double lattice_constant,
    const double side_length, const double fractional_abundance)
{
  
  // get the int range
  const int int_range = int_range_centred_cube(side_length, lattice_constant);
  
  // add site vectors of the crystal structure with a given fractional abundance
  fill_site_vectors(construct_lattice_vectors(lattice_constant),
      construct_basis_vectors(),
      -int_range,int_range,
      -int_range,int_range,
      -int_range,int_range,
      -side_length/2.0,side_length/2.0,
      -side_length/2.0,side_length/2.0,
      -side_length/2.0,side_length/2.0,fractional_abundance);
  
}

void DiamondCubic::make_sphere(const double radius)
{
  
  vector<ThreeVector> new_sites;
  
  for (UInt i=0;i<num_site_vectors();i++) {
    if (get_site_vector(i).norm() <= radius) {
      new_sites.push_back(get_site_vector(i));
    }
  }
  
  site_vectors_ = new_sites;
  
  return;
  
}

} // namespace SpinDec

