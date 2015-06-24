#ifndef SPINBASIS_H_
#define SPINBASIS_H_

// Seto Balian, Jun 24, 2015

#include <iostream>

#include "SpinDec/typedefs.h"

#include "SpinDec/SpinParameters.h"
#include "SpinDec/SpinParametersVector.h"


namespace SpinDec
{

/**
 * \brief Holds magnetic quantum numbers for (in general) multiple spins.
 * 
 * Implements the Zeeman basis and includes build methods.
 * 
 * Columns: spins.
 * Rows: magnetic quantum numbers.
 * 
 * For example, for two electrons, this is
 * \f[
 *   \begin{array}{cc}
 *   0.5 & 0.5 \\
 *   0.5 & -0.5 \\
 *   -0.5 & 0.5 \\
 *   -0.5 & 0.5 \\
 *   \end{array}
 * \f]
 * For example, the first row corresponds to
 * \f$ \left|m_{S1} = 0.5 , m_{S2} = 0.5\right \rangle \f$.
 * 
 */
class SpinBasis
{
private:
  
  /// Automatically build using spin multiplicities
  Eigen::ArrayXXd build (const SpinParametersVector& spin_parameters_vector);
  
  /// Build using multiplicity.
  Eigen::ArrayXXd build(const SpinParameters& spin_parameters);
  
  Eigen::ArrayXXd basis_as_array_;

public:

  SpinBasis();
  /// Automatically build using spin multiplicities.
  explicit SpinBasis(const SpinParametersVector & spin_parameters_vector);
  /// Automatically build using spin multiplicity.
  explicit SpinBasis(const SpinParameters& spin_parameters);
  
  /// Custom build.
  explicit SpinBasis(const Eigen::ArrayXXd & basis_as_array); 
  const Eigen::ArrayXXd& get_basis_as_array() const;
  
  UInt num_basis_states() const;
  UInt num_spins() const;

  double get_element(const UInt index, const UInt slot) const;  
  
  /**
   * For example,
   * \f[
   * {\rm basis1} =
   *   \begin{array}{c}
   *   0.5 \\
   *   -0.5 \\
   *   \end{array}
   * \f]
   * and
   * \f[
   * {\rm basis2} =
   *   \begin{array}{c}
   *   4.5 \\
   *   -4.5 \\
   *   \end{array}
   * \f]
   * basis1 + basis2 gives
   *    \f[
   *   \begin{array}{cc}
   *   0.5 & 4.5 \\
   *   -0.5 & -4.5 \\
   *   \end{array}
   * \f]
   * 
   */
  SpinBasis operator+(const SpinBasis & to_append) const;
  
  /**
   * Like tensor product. For example,
   * \f[
   * {\rm basis1} =
   *   \begin{array}{c}
   *   4.5 \\
   *   -4.5 \\
   *   \end{array}
   * \f]
   * and
   * \f[
   * {\rm basis2} =
   *   \begin{array}{c}
   *   0.5 \\
   *   -0.5 \\
   *   \end{array}
   * \f]
   * basis1^(basis2) is
   * \f[
   *   \begin{array}{cc}
   *   4.5 & 0.5 \\
   *   4.5 & -0.5 \\
   *   -4.5 & 0.5 \\
   *   -4.5 & -0.5
   *   \end{array}
   * \f]
   * 
   * 
   */
  SpinBasis operator^(const SpinBasis & to_combine) const;
  // TODO test this
  
  /// Check if bases are identical.
  bool operator==(const SpinBasis to_compare) const;
  
  /// Print with cout.
  friend std::ostream& operator<<(std::ostream& os, SpinBasis const & basis);
  
  bool is_equal(const SpinBasis& basis) const;
  
};

} // namespace SpinDec

#endif // SPINBASIS_H_

// GRAVEYARD
// OLD + Don't use this even if you update it ...

//void truncate(const std::vector<UInt> & spin_indices,
//                         const Eigen::ArrayXXd & to_keep);
