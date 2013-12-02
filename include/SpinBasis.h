#ifndef SPINBASIS_H
#define SPINBASIS_H

// SpinBasis (Zeeman basis)
//
// Holds magnetic quantum numbers for in general multiple spins.
// Columns: spins
// Rows: magnetic quantum numbers
// For example, for 2 electrons, this is
//                  0.5  0.5 -> |mS1 = 0.5, mS2 = 0.5>
//                  0.5 -0.5
//                 -0.5  0.5
//                 -0.5 -0.5
//
// Seto Balian, December 2, 2013

#include "Spin.h"
#include "SpinVector.h"

#include <Eigen/Dense>

class SpinBasis
{

protected:

  void build (const SpinVector & spin_vector); // automatically build
                                               // using spin multiplicities
  Eigen::ArrayXXd basis_;
  
public:

  SpinBasis(); // a single element set to zero
  SpinBasis(const SpinVector & spin_vector); // automatically build
                                             // using spin multiplicities
  SpinBasis(const Eigen::ArrayXXd & basis); // custom build
  Eigen::ArrayXXd get_basis() const;
  
  // Number of basis states
  unsigned int dimension() const;

  // Number of spins
  virtual unsigned int num_spins() const;
  
  double get_element(const unsigned int row, const unsigned int col) const;
  
  //void truncate(const std::vector<unsigned int> & spin_indices,
  //                         const Eigen::ArrayXXd & to_keep);


  virtual ~SpinBasis() {/**/}

};

#endif // SPINBASIS_H
