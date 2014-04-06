#ifndef SIMPLECUBICLATTICEVECTORS_H_
#define SIMPLECUBICLATTICEVECTORS_H_

// SpinDec::SimpleCubicLatticeVectors
//
// Simple cubic lattice vectors: |a1| = |a2| = |a3| = a0 and a1,a2,a3 mutually
// orthogonal ( || to x,y,z respectively in Cartesian coordinates).
//
// Seto Balian, Apr 6, 2014

#include "SpinDec/typedefs.h"
#include "SpinDec/LatticeVectors.h"

namespace SpinDec
{

class SimpleCubicLatticeVectors : public LatticeVectors
{
public:
  SimpleCubicLatticeVectors();
  
                                    // lattice constant a0 in Angstroms
  explicit SimpleCubicLatticeVectors(const double lattice_constant);
  
};

} // namespace SpinDec

#endif // SIMPLECUBICLATTICEVECTORS_H_
