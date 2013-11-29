#ifndef SINGLESPINBASIS_H
#define	SINGLESPINBASIS_H

// SingleSpinBasis
//
// Basis for a single spin.
//
// Seto Balian, November 28, 2013

#include "SpinBasis.h"
#include <Eigen/Dense>
#include "Spin.h"

class SingleSpinBasis : public SpinBasis
{
  
public:

  SingleSpinBasis();
    
  unsigned int dimension() const;
  unsigned int num_spins() const;
  void clear();

  // add magnetic quantum number
  void add_magnetic_quantum_number(const double magnetic_quantum_number);

  void build(const Spin & spin); // using multiplicity

  // like tensor product,
  // for example, SingleSpinBasis.combine_to(SpinBasis)
  // SingleSpinBasis = 0.5
  //                  -0.5
  //              SpinBasis = 4.5
  //                         -4.5
  // SpinBasis changes to
  //                      4.5  0.5
  //                     -4.5 -0.5
  //                      4.5  0.5
  //                     -4.5 -0.5
  void combine_to(SpinBasis & basis) const;

};

#endif	 // SINGLESPINBASIS_H
