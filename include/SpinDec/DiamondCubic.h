#ifndef DIAMONDCUBIC_H_
#define DIAMONDCUBIC_H_

// Seto Balian, Jul 22, 2015

#include "SpinDec/typedefs.h"
#include "SpinDec/CrystalStructure.h"
#include "SpinDec/SimpleCubicLatticeVectors.h"
#include "SpinDec/CrystalBasis.h"

namespace SpinDec
{

/**
 * \brief Diamond cubic crystal structure.
 * 
 * This is implemented as a simple cubic lattice with 8 basis vectors.
 * Source: http://en.wikipedia.org/wiki/Diamond_cubic.
 * 
 */
class DiamondCubic : public CrystalStructure
{

private:
  
  /// Set up and return the lattice vectors.
  SimpleCubicLatticeVectors construct_lattice_vectors(
      const double lattice_constant) const;
  
  /// Set up and return the basis vectors.
  CrystalBasis construct_basis_vectors() const;
  
  /**
   *  Get integer range (for constructing crystal structure) in a centred cube
   *  given the side length.
   */
  int int_range_centred_cube(
      const double side_length, const double lattice_constant) const;
  
public:
  DiamondCubic();
  
  /**
   * \brief Cubic lattice constant and side length of superlattice cube in
   * \f$\mbox{\AA}\f$.
   */
  DiamondCubic(const double lattice_constant, 
               const double side_length);
  
  void make_sphere(const double radius);
  void make_shell(const double min_radius, const double max_radius);

};

} // namespace SpinDec

#endif // DIAMONDCUBIC_H_
