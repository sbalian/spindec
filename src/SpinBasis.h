#ifndef SPINBASIS_H_
#define SPINBASIS_H_

// SpinBasis (Zeeman basis)
//
// Holds magnetic quantum numbers for in general multiple spins.
// Columns: spins
// Rows: magnetic quantum numbers
// For example, for 2 electrons, this is
//                 index slot
//                  0.5  0.5 -> |mS1 = 0.5, mS2 = 0.5>
//                  0.5 -0.5
//                 -0.5  0.5
//                 -0.5 -0.5
//
// Seto Balian, Dec 4, 2013

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

  SpinBasis(); // null
  SpinBasis(const SpinVector & spin_vector); // automatically build
                                             // using spin multiplicities
  SpinBasis(const Eigen::ArrayXXd & basis); // custom build
  Eigen::ArrayXXd get_basis() const;
  
  // Number of basis states
  unsigned int dimension() const;

  // Number of spins
  virtual unsigned int num_spins() const;
  
  double get_element(const unsigned int index, const unsigned int slot) const;  
  
  // For example,         basis1 = 0.5
  //                              -0.5
  //                      basis2 = 4.5
  //                              -4.5
  // basis1 + basis2     gives 0.5  4.5
  //                          -0.5 -4.5
  SpinBasis operator+(const SpinBasis & to_join) const;
  
  // like tensor product,
  // for example, a.combine(b)
  // SpinBasis b = 0.5
  //              -0.5
  //              SpinBasis a = 4.5
  //                           -4.5
  // gives
  //                      4.5  0.5
  //                     -4.5 -0.5
  //                      4.5  0.5
  //                     -4.5 -0.5
  SpinBasis combine(const SpinBasis & to_combine) const;

  virtual ~SpinBasis();
  
  // TODO don't use this ...
  //void truncate(const std::vector<unsigned int> & spin_indices,
  //                         const Eigen::ArrayXXd & to_keep);

};

#endif // SPINBASIS_H_
