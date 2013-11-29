#ifndef SPINBASIS_H
#define SPINBASIS_H

// SpinBasis (Zeeman basis)
//
// For holding magnetic quantum numbers for in general multiple spins.
//
// For storing magnetic quantum numbers for in general multiple spins
// Columns: spins
// Rows: magnetic quantum numbers
// For example, for 2 electrons, this can be
//                  0.5  0.5 -> |mS1 = 0.5, mS2 = 0.5>
//                  0.5 -0.5
//                 -0.5  0.5
//                 -0.5 -0.5
//
// Seto Balian, November 29, 2013

#include "Spin.h"
#include "SpinVector.h"

#include <Eigen/Dense>

class SpinBasis
{

private:
                                               // @todo
  void build (const SpinVector & spin_vector); // how can I make basis const?
                                               // and still use an init method?
                                               // suppose this returns ArrayXXd,
                                               // for Eigen, how do I use this
                                               // in an intializer list?
protected:
  
  Eigen::ArrayXXd basis_;
  
public:
  
  SpinBasis(); // a single element set to zero
  SpinBasis(const SpinVector & spin_vector); // automatically build
                                             // using spin multiplicities
  // Number of basis states
  unsigned int dimension() const;

  // Number of spins
  virtual unsigned int num_spins() const;

  // For example,         basis1 = 0.5
  //                              -0.5
  // SpinBasis            basis2 = 4.5
  //                              -4.5
  // basis1.join(basis2) gives 0.5  4.5
  //                          -0.5 -4.5
  SpinBasis join(const SpinBasis & to_join) const;

  virtual ~SpinBasis() {/**/}

};

#endif // SPINBASIS_H
