// See DiamondCubic.h for description.
// Seto Balian, Apr 6, 2014
// TODO Comment

#include "SpinDec/DiamondCubic.h"
#include "SpinDec/SimpleCubicLatticeVectors.h"
#include "SpinDec/CrystalBasis.h"

namespace SpinDec
{

int DiamondCubic::int_range_centred_cube(
    const double side_length, const double lattice_constant) const
{
  return static_cast<int>(side_length / (lattice_constant*2.0) + 1);
}

SimpleCubicLatticeVectors DiamondCubic::construct_lattice_vectors(
    const double lattice_constant) const
{
  return SimpleCubicLatticeVectors(lattice_constant);
}

CrystalBasis DiamondCubic::construct_basis_vectors() const
{
  CrystalBasis basis;
  
  ThreeVector basis_vector;
  
  // SOURCE: Wiki TODO Comment + explain + cite properly
  
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
  
  const int int_range = int_range_centred_cube(side_length, lattice_constant);
  
  fill_site_vectors(construct_lattice_vectors(lattice_constant),
      construct_basis_vectors(),-int_range,int_range,-int_range,int_range,
      -int_range,int_range,-lattice_constant/2.0,lattice_constant/2.0,
      -lattice_constant/2.0,lattice_constant/2.0,-lattice_constant/2.0,
      lattice_constant/2.0,true,1.0,-1);
  
}

DiamondCubic::DiamondCubic(const double lattice_constant,
    const double side_length, const double fractional_abundance,
    const int seed_uniform_c_rand)
{
  
  const int int_range = int_range_centred_cube(side_length, lattice_constant);
  
  fill_site_vectors(construct_lattice_vectors(lattice_constant),
      construct_basis_vectors(),-int_range,int_range,-int_range,int_range,
      -int_range,int_range,-lattice_constant/2.0,lattice_constant/2.0,
      -lattice_constant/2.0,lattice_constant/2.0,-lattice_constant/2.0,
      lattice_constant/2.0,true,fractional_abundance,seed_uniform_c_rand);
  
}


} // namespace SpinDec

