#ifndef CRYSTALBASIS_H_
#define CRYSTALBASIS_H_

// Seto Balian, Jun 24, 2015

#include "SpinDec/typedefs.h"

namespace SpinDec
{

/**
 * \brief Basis vectors for crystal structures in 3D.
 * 
 * Length units are \f$\mbox{\AA}\f$. They are in the basis of lattice vectors
 * \f$({\bf a}_1,{\bf a}_2,{\bf a}_3)\f$, NOT \f$(x,y,z)\f$!
 * 
 */
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
