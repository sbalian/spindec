// See LatticeVectors.h for description.
// Seto Balian, Apr 3, 2014

#include "SpinDec/LatticeVectors.h"
#include "SpinDec/Errors.h"
#include <algorithm>

namespace SpinDec
{

void LatticeVectors::set_lattice_vectors(const ThreeVector& a1,
    const ThreeVector& a2,
    const ThreeVector& a3)
{
  a1_ = a1;
  a2_ = a2;
  a3_ = a3;

  // Check if linearly independent
  if (!linearly_independent()) {
    Errors::quit("Lattice vectors must be linearly independent.");
  }

  return;
}


bool LatticeVectors::linearly_independent() const
{
  // compute the determinant, if non-zero, then linearly independent
  double tolerance = 1.0e-10;
  
  Eigen::Matrix3d matrix_of_column_vectors;
  matrix_of_column_vectors.col(0) = a1_;
  matrix_of_column_vectors.col(1) = a2_;
  matrix_of_column_vectors.col(2) = a3_;

  if (abs(matrix_of_column_vectors.determinant()) <= tolerance) { // ie "zero"
    return false;
  } // else
  return true;
  
}

LatticeVectors::LatticeVectors()
{
}

LatticeVectors::LatticeVectors(const ThreeVector& a1,
               const ThreeVector& a2,
               const ThreeVector& a3)
{
  
  set_lattice_vectors(a1,a2,a3);
  
}

const ThreeVector& LatticeVectors::get_a1() const
{
  return a1_;
}

const ThreeVector& LatticeVectors::get_a2() const
{
  return a2_;
}

const ThreeVector& LatticeVectors::get_a3() const
{
  return a3_;
}


} // namespace SpinDec
