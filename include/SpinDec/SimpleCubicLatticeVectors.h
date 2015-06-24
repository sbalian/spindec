#ifndef SIMPLECUBICLATTICEVECTORS_H_
#define SIMPLECUBICLATTICEVECTORS_H_

// Seto Balian, Jun 24, 2015

#include "SpinDec/typedefs.h"
#include "SpinDec/LatticeVectors.h"

namespace SpinDec
{

/**
 * \brief Simple cubic lattice vectors.
 * 
 * \f$|{\bf a}_1| = |{\bf a}_2| = |{\bf a}_3| = a_0\f$ and
 * \f$ {\bf a}_1,{\bf a}_2,{\bf a}_3\f$ mutually
 * orthogonal (parallel to \f$x,y,z\f$ respectively in Cartesian coordinates).
 * 
 * Source: http://en.wikipedia.org/wiki/Cubic_crystal_system.
 * 
 */
class SimpleCubicLatticeVectors : public LatticeVectors
{
public:
  SimpleCubicLatticeVectors();
  
  /// Lattice constant \f$a_0\f$ in \f$\mbox{\AA}\f$.
  explicit SimpleCubicLatticeVectors(const double lattice_constant);
  
};

} // namespace SpinDec

#endif // SIMPLECUBICLATTICEVECTORS_H_
