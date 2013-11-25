#ifndef ZEEMANBASIS_H
#define ZEEMANBASIS_H

// ZeemanBasis
//
// Holds magnetic quantum numbers (Zeeman basis).
//
// Seto Balian 25/11/2013

#include <Eigen/Dense>

#include "Named.h"

class ZeemanBasis : public Named
{

private:
  Eigen::ArrayXXd basis_; // Zeeman basis.
                          // cols -> spin slots
                          // rows -> product states,
                          // e.g. for 2 electrons,
                          // this can be   0.5  0.5
                          //               0.5 -0.5
                          //              -0.5  0.5
                          //              -0.5 -0.5

public:

  ZeemanBasis();
  ZeemanBasis(const Eigen::ArrayXXd & basis);
  
  Eigen::ArrayXXd get_basis() const;
  void set_basis(const Eigen::ArrayXXd & basis);
  
  void combine(const ZeemanBasis & to_combine);
  void append(const ZeemanBasis & to_append);
  
  // this is the rows of basis_
  unsigned int dimension() const;
  
  // this is the cols of basis_
  unsigned int num_spins() const;
  
};

#endif // ZEEMANBASIS_H
