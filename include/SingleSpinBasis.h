#ifndef SINGLESPINBASIS_H
#define	SINGLESPINBASIS_H

// SingleSpinBasis
//
// Basis for a single spin.
//
// Seto Balian, December 2, 2013

#include "SpinBasis.h"

class SingleSpinBasis : public SpinBasis
{

private:
  
  void build(const Spin & spin); // build using multiplicity
    
public:

  SingleSpinBasis(); // single zero element
  SingleSpinBasis(const Spin & spin); // uses multiplicity to build basis
                                       // automatically
  
  SingleSpinBasis(const Eigen::ArrayXd & basis); // custom build
  
  virtual unsigned int num_spins() const;
  
  double get_element(const unsigned int row) const;

  
  // For example,         basis1 = 0.5
  //                              -0.5
  //                      basis2 = 4.5
  //                              -4.5
  // basis1.join(basis2) gives 0.5  4.5
  //                          -0.5 -4.5
  SpinBasis join(const SingleSpinBasis & to_join) const;

  // like tensor product,
  // for example, SingleSpinBasis.combine(SpinBasis)
  // SingleSpinBasis = 0.5
  //                  -0.5
  //              SpinBasis = 4.5
  //                         -4.5
  // gives
  //                      4.5  0.5
  //                     -4.5 -0.5
  //                      4.5  0.5
  //                     -4.5 -0.5
  SpinBasis combine(const SpinBasis & basis) const;
  
  virtual ~SingleSpinBasis() {/**/}

};

#endif	 // SINGLESPINBASIS_H
