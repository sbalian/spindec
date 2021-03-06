#ifndef LATTICEVECTORS_H_
#define LATTICEVECTORS_H_

// Seto Balian, Jun 24, 2015

// TODO vectors must be linearly independent ...

#include "SpinDec/typedefs.h"
#include <vector>

namespace SpinDec
{

/**
 * \brief Lattice vectors for 3D crystal structures.
 * 
 * Length units: \f$\mbox{\AA}\f$. In Cartesian coordinates.
 * Vectors must be linearly independent.
 * 
 */
class LatticeVectors
{
protected:
  
  bool linearly_independent() const;
  
  ThreeVector a1_;
  ThreeVector a2_;
  ThreeVector a3_;
  
  void set_lattice_vectors(const ThreeVector& a1,
      const ThreeVector& a2,const ThreeVector& a3);
  
public:
  LatticeVectors();
  LatticeVectors(const ThreeVector& a1,
                 const ThreeVector& a2,
                 const ThreeVector& a3);

  const ThreeVector& get_a1() const;
  const ThreeVector& get_a2() const;
  const ThreeVector& get_a3() const;
  

};

} // namespace SpinDec

#endif // LATTICEVECTORS_H_
