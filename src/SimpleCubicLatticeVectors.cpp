// See SimpleCubicLatticeVectors.h for description.
// Seto Balian, Nov 6, 2014

#include "SpinDec/SimpleCubicLatticeVectors.h"

namespace SpinDec
{

SimpleCubicLatticeVectors::SimpleCubicLatticeVectors()
{
}

SimpleCubicLatticeVectors::SimpleCubicLatticeVectors(
    const double lattice_constant)
{
  
  // SOURCE: http://en.wikipedia.org/wiki/Cubic_crystal_system
  
  ThreeVector a1;
  a1(0) = lattice_constant;
  a1(1) = 0.0;
  a1(2) = 0.0;
  
  ThreeVector a2;
  a2(0) = 0.0;
  a2(1) = lattice_constant;
  a2(2) = 0.0;

  ThreeVector a3;
  a3(0) = 0.0;
  a3(1) = 0.0;
  a3(2) = lattice_constant;

  set_lattice_vectors(a1,a2,a3);
  
}

} // namespace SpinDec

