#ifndef SPINBASIS_H
#define SPINBASIS_H

// SpinBasis
//
// For holding magnetic quantum numbers (Zeeman basis) for (in general)
// multiple spins.
//
// Seto Balian, November 28, 2013

#include <Eigen/Dense>

#include "Spin.h"
#include <vector>

class SpinBasis
{
protected:
  Eigen::ArrayXXd basis_;
  // Stores magnetic quantum numbers for multiple spins
  // Columns: spins
  // Rows: magnetic quantum numbers
  // For example, for 2 electrons, this can be
  //                  0.5  0.5 -> |mS1 = 0.5, mS2 = 0.5>
  //                  0.5 -0.5
  //                 -0.5  0.5
  //                 -0.5 -0.5

public:
  
  SpinBasis();
  
  // Number of basis states
  unsigned int dimension() const;
  
  // Number of spins
  virtual unsigned int num_spins() const;
  
  // Clear the basis
  virtual void clear();
  
  // For example, SpinBasis   B1 = 0.5
  //                              -0.5
  // SpinBasis   B2 = 4.5
  //                 -4.5
  // B1.join(B2) gives 0.5  4.5
  //                  -0.5 -4.5
  SpinBasis join(const SpinBasis & to_join) const;
  
  // Quickly build basis using multiplicities
  
  std::vector<Spin*> spins;
  spins.push_back(&derivedSpin); // ...
  
  
  void build(const std::vector<Spin*> & spins);
  
  // Suppose basis is |m0, m1, m2> with m1=m2=m3=+/-0.5.
  // For example, given indices (0,1) and a to_keep array, 0.5 -0.5
  //                                                      -0.5  0.5
  // This truncates the original basis (of dimension 8) to
  //  0.5 -0.5  0.5
  //  0.5 -0.5 -0.5
  // -0.5  0.5  0.5
  // -0.5  0.5 -0.5
  void truncate(const std::vector<unsigned int> & spin_indices,
                     const Eigen::ArrayXXd & to_keep);
  
  virtual ~SpinBasis() {/**/};
  
};

#endif // SPINBASIS_H
