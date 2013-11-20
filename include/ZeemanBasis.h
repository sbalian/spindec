#ifndef ZEEMANBASIS_H
#define ZEEMANBASIS_H

// ZeemanBasis
//
// Calculates and holds magnetic quantum numbers (Zeeman basis) given a set of
// Spin objects.
//
// Seto Balian 20/11/2013

#include <Eigen/Dense>
#include <vector>

#include "Spins.h"

class ZeemanBasis
{

private:
  Eigen::ArrayXXd basis_; // Zeeman basis.
                          // cols -> spin slots
                          // rows -> product states,
                          // e.g. for 2 electrons,
                          // this is   0.5  0.5
                          //           0.5 -0.5
                          //          -0.5  0.5
                          //          -0.5 -0.5
  Spins spins_;

public:

  ZeemanBasis();
  ZeemanBasis(const Spins & spins, const Eigen::ArrayXXd & basis);

  Spins get_spins()    const;
  Eigen::ArrayXXd get_basis() const;

  void set_spins(const Spins & spins);
  void set_basis(const Eigen::ArrayXXd & basis);

  // build the basis using the multiplicites
  void build();

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

  // this is the rows of basis_, not from multiplicities (because of possible
  // truncation)
  unsigned int dimension() const;

};

#endif // ZEEMANBASIS_H

