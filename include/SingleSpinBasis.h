#ifndef SINGLESPINBASIS_H
#define	SINGLESPINBASIS_H

// SingleSpinBasis
//
// Basis for a single spin.
//
// Seto Balian, November 29, 2013

#include "SpinBasis.h"
#include "Spin.h"

#include <Eigen/Dense>

class SingleSpinBasis : public SpinBasis
{

private:
  
  Eigen::ArrayXd basis_; // @todo make this const, but how do I initialize it?
  // e.g. for an electron, this can be 0.5 -> |mS =  1/2>
  //                                  -0.5 -> |mS = -1/2>
  
  void build(const Spin & spin); // build using multiplicity

public:

  SingleSpinBasis(); // single zero element
  SingleSpinBasis(const Spin & spin); // uses multiplicity to build basis
                                       // automatically
  SingleSpinBasis(const Eigen::ArrayXd & basis); // custom build
  
  virtual unsigned int dimension() const;
  virtual unsigned int num_spins() const;
  //virtual SpinBasis* join(const SpinBasis & to_join) const;
  
  Eigen::ArrayXd get_basis() const;

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
  //SpinBasis* combine(const SpinBasis & combine_to) const;
  
  virtual ~SingleSpinBasis() {/**/}

};

#endif	 // SINGLESPINBASIS_H
