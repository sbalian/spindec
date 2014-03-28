#ifndef SPINBASIS_H_
#define SPINBASIS_H_

// SpinBasis (Zeeman basis)
//
// Holds magnetic quantum numbers for in general multiple spins.
// Includes build methods.
// Columns: spins
// Rows: magnetic quantum numbers
// For example, for 2 electrons, this is
//                 index slot
//                  0.5  0.5 -> |mS1 = 0.5, mS2 = 0.5>
//                  0.5 -0.5
//                 -0.5  0.5
//                 -0.5 -0.5
//
// Seto Balian, Mar 28, 2014

#include <Eigen/Dense>
#include <iostream>

#include "SpinDec/typedefs.h"

#include "SpinDec/SpinParameters.h"
#include "SpinDec/Spin"

namespace SpinDec
{

class SpinBasis
{
private:
  
  Eigen::ArrayXXd build (const SpinParametersVector& spin_parameters_vector);
                                           // automatically build
                                           // using spin multiplicities
  
  Eigen::ArrayXXd build(const SpinParameters& spin_parameters);
  // build using multiplicity
  
  Eigen::ArrayXXd basis_as_array_;

public:

  SpinBasis();
  explicit SpinBasis(const SpinParametersVector & spin_parameters_vector);
                                             // automatically build
                                             // using spin multiplicities
  explicit SpinBasis(const SpinParameters& spin_parameters);
                                                  // automatically build
                                                  // using spin multiplicity
  
  explicit SpinBasis(const Eigen::ArrayXXd & basis_as_array); // custom build
  const Eigen::ArrayXXd& get_basis_as_array() const;
  
  UInt num_basis_states() const;
  UInt num_spins() const;

  double get_element(const UInt index, const UInt slot) const;  
  
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
  
  bool operator==(const SpinBasis to_compare) const; // check if bases are
                                                     // identical
  
  // Print with cout
  friend std::ostream& operator<<(std::ostream& os, SpinBasis const & basis);

  
};

} // namespace SpinDec

#endif // SPINBASIS_H_

// GRAVEYARD
// OLD + Don't use this even if you update it ...

//void truncate(const std::vector<UInt> & spin_indices,
//                         const Eigen::ArrayXXd & to_keep);
