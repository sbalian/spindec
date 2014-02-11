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
// Seto Balian, Feb 11, 2014

#include <Eigen/Dense>
#include <iostream>

#include "types.h"

namespace SpinDecoherence
{

class SpinBasis
{
private:
  
  unsigned int calc_multiplicity(const double quantum_number) const;
  unsigned int calc_multiplicity(const dvector & quantum_numbers) const;

  Eigen::ArrayXXd build (const dvector & quantum_numbers);
                                           // automatically build
                                           // using spin multiplicities
  
  Eigen::ArrayXXd build(const double quantum_number); // build using multiplicity
  
  const Eigen::ArrayXXd basis_as_array_;

public:

  SpinBasis();
  explicit SpinBasis(const dvector & quantum_numbers); // automatically build
                                             // using spin multiplicities
  explicit SpinBasis(const double quantum_number); // automatically build
                                              // using spin multiplicity
  
  explicit SpinBasis(const Eigen::ArrayXXd & basis_as_array); // custom build
  Eigen::ArrayXXd get_basis_as_array() const;
  
  // Number of basis states
  unsigned int dimension() const;

  // Number of spins
  unsigned int num_spins() const;

  double get_element(const unsigned int index, const unsigned int slot) const;  
  
  // For example,         basis1 = 0.5
  //                              -0.5
  //                      basis2 = 4.5
  //                              -4.5
  // basis1 + basis2     gives 0.5  4.5
  //                          -0.5 -4.5
  SpinBasis operator+(const SpinBasis & to_join) const;
  
  // like tensor product,
  // for example, a^(b)
  // SpinBasis b = 0.5
  //              -0.5
  //              SpinBasis a = 4.5
  //                           -4.5
  // gives
  //                      4.5  0.5
  //                     -4.5 -0.5
  //                      4.5  0.5
  //                     -4.5 -0.5
  SpinBasis operator^(const SpinBasis & to_combine) const;
  
  bool is_equal(const SpinBasis to_compare) const; // check if bases are
                                                   // identical
  
  // Print with cout
  friend std::ostream& operator<<(std::ostream& os, SpinBasis const & basis);

  
};

} // namespace SpinDecoherence

#endif // SPINBASIS_H_

// Don't use this ...
//void truncate(const std::vector<unsigned int> & spin_indices,
//                         const Eigen::ArrayXXd & to_keep);
