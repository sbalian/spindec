#ifndef BOOSTEIGEN_H_
#define BOOSTEIGEN_H_

// Seto Balian, Jun 24, 2015

#include "SpinDec/typedefs.h"

namespace SpinDec
{

/**
 * \brief Static methods to extend Eigen functionality.
 * 
 * Note that the naming convention complies with that of Eigen, and is different
 * from the rest of SpinDec. Eigen is for linear algebra and can be obtained
 * for free: http://eigen.tuxfamily.org/ .
 */
class BoostEigen
{

public:

  /**
   * \brief Cosine of angle between real vectors.
   * 
   * \f$ \cos\theta = \frac{{\bf a} \cdot {\bf b}}{|{\bf a}||{\bf b}|}\f$.
   */
  static double cosAngleBetween(const ThreeVector & a,
                                const ThreeVector & b);

  /**
   * \brief Maximum absolute coefficient.
   * 
   * Maximum of \f$ [ |a_1|,|a_2|,|a_3|] \f$ for real vector
   * \f$ {\bf a} = (a_1,a_2,a_3) \f$.
   * 
   */
  static double maxAbsCoeff(const ThreeVector & a);
  
  /// Element-wise exponentiation for complex vectors.
  static ComplexVector exp(const ComplexVector & a);

  /** 
   * \brief Tensor product for complex matrices.
   * 
   * Evaluates \f$ {\bf C} = {\bf A} \otimes {\bf B}\f$. For example,
   * for \f$ 2 \times 2 \f$ matrices, this is
   * \f[
   *   {\bf C}=
   *   \left( \begin{array}{cc}
   *   A_{11}{\bf B} & A_{12}{\bf B} \\
   *   A_{21}{\bf B} & A_{22}{\bf B}
   *   \end{array} \right)
   * \f]
   */
  static ComplexMatrix tensorProduct(const ComplexMatrix & A,
                                        const ComplexMatrix & B);
  
  /** 
   * \brief Tensor product for complex vectors.
   * 
   * Evaluates \f${\bf c} = {\bf a}\otimes{\bf b}\f$. For example, for
   * 2-vectors, this is
   * \f[
   *   {\bf c}=
   *   \left( \begin{array}{c}
   *   a_1 b_1 \\
   *   a_1 b_2 \\
   *   a_2 b_1 \\
   *   a_2 b_2 
   *   \end{array} \right)
   * \f]
   */
  static ComplexVector tensorProduct(const ComplexVector & a,
                                        const ComplexVector & b);

  /**
   * \brief Partial trace for complex matrices.
   * 
   * Given \f$ {\bf C} = {\bf A} \otimes {\bf B} \f$, and the dimension
   * of \f$ {\bf B} \f$, this method outputs \f$ {\rm Tr}_{\bf B} {\bf A}\f$.
   * 
   */
  static ComplexMatrix partialTrace(const ComplexMatrix & AB,
                                         const unsigned int dimension_B);
  
  
  /**
   * \brief Spectral decomposition of a complex matrix.
   * 
   * This is \f$ {\bf A } = {\bf V D V}^{-1} \f$, where \f$ {\bf D} \f$
   * is the diagonal of eigenvalues of \f${\bf A}\f$ and \f${\bf V}\f$
   * is the columnwise eigenvector matrix.
   * 
   */
  static ComplexMatrix spectralDecomposition(
                                         const ComplexMatrix & eigenvectors,
                                         const ComplexVector & eigenvalues);
  /// Spectral decomposition of a unitary matrix.
  /**
   * 
   * For a unitary matrix, \f$ {\bf A}^{-1} = {\bf V}^{\dagger} \f$
   * 
   */
  static ComplexMatrix unitarySpectralDecomposition(
                                         const ComplexMatrix & eigenvectors,
                                         const ComplexVector & eigenvalues);
  
  /// Is \f$ |{\bf r}| \leq d \f$?
  static bool isWithinDistance(const ThreeVector& r,
      const double distance);

};

} // namespace SpinDec

#endif // BOOSTEIGEN_H_
