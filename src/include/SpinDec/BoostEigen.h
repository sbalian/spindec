#ifndef BOOSTEIGEN_H_
#define BOOSTEIGEN_H_

// SpinDec::BoostEigen
//
// Static methods to extend Eigen (linear algebra package).
// Note that the naming convention complies with that of Eigen, and is different
// from the rest of SpinDec.
//
// Seto Balian, Mar 28, 2014

#include <Eigen/Dense>

#include <complex>

#include "SpinDec/typedefs.h"

namespace SpinDec
{

class BoostEigen
{

public:

  // Cosine of angle between real vectors a and b = a.b/ab
  static double cosAngleBetween(const ThreeVector & a,
                                const ThreeVector & b);

  // Maximum of ( abs(a1), abs(a2), abs(a3) ) for a real 3-vector
  static double maxAbsCoeff(const ThreeVector & a);
  
  // Exponentiate (element-wise complex exponentiation) for complex vectors
  static ComplexVector exp(const ComplexVector & a);

  // Tensor product for complex matrices
  // This evaluates C = A X B. For example, for 2 x 2 matrices,
  // C = A_11*B A_12*B
  //     A_21*B A_22*B
  static ComplexMatrix tensorProduct(const ComplexMatrix & A,
                                        const ComplexMatrix & B);
  
  // Tensor product for complex vectors
  // This evaluates c = a X b. For example, for 2-vectors,
  // C = a_1*B_1
  //     a_1*B_2
  //     a_2*B_1
  //     a_2*B_2
  static ComplexVector tensorProduct(const ComplexVector & a,
                                        const ComplexVector & b);

  // Partial trace for complex matrices
  // Given C = A x B, where x denotes the tensor product,
  // in addition to the dimension of B, this method outputs
  // Tr[B] A (where Tr denotes the sum of the diagonal elements)
  static ComplexMatrix partialTrace(const ComplexMatrix & AB,
                                         const unsigned int dimension_B);
  
  // The spectral decomposition of a complex matrix is
  // A = V D V-1, where D is the diagonal of eigenvalues
  // and V is the eigenvector matrix (col -> evector)
  static ComplexMatrix spectralDecomposition(
                                         const ComplexMatrix & eigenvectors,
                                         const ComplexVector & eigenvalues);
  // For a unitary matrix, V-1 = V^+
  static ComplexMatrix unitarySpectralDecomposition(
                                         const ComplexMatrix & eigenvectors,
                                         const ComplexVector & eigenvalues);

};

} // namespace SpinDec

#endif // BOOSTEIGEN_H_

// TEMPLATE GRAVEYARD
// ------------------

//// OK, but does not work on Eigen expressions in the arguments! ...
//// Exponentiate (element-wise complex exponentiation) for vectors
//template<typename ScalarType, int rows>
//static Eigen::Matrix<ScalarType, rows, 1>
//  exp(const Eigen::Matrix<ScalarType, rows, 1> & a)
//{
//  return (a.array().exp()).matrix();
//}

//// play ...
//template<typename ScalarType, int rows, int cols>
//static Eigen::Matrix<ScalarType,rows,cols> tensorProduct(
//    const Eigen::Matrix<ScalarType, rows, cols> & A,
//    const Eigen::Matrix<ScalarType, rows, cols> & B)
//{
//  unsigned int dimension_A    = A.rows();
//  unsigned int dimension_B    = B.rows();
////    rowsA= A.rows();
////    rowsB= B.rows();
////    rowsOut = rowsA*rowsB;
//  
//  //unsigned int dimension_AB    = dimension_A*dimension_B;
//  
//  //output
//  Eigen::Matrix<ScalarType, rows*rows, rows*rows> product;
//  
//  // consistently with the definition of the partial trace
//  for (unsigned int i=0;i<dimension_A;i++) {
//    for (unsigned int j=0;j<dimension_A;j++) {
//      product.block(i*dimension_B,j*dimension_B,dimension_B,dimension_B)
//                                                             = A(i,j)*B;
//    }
//  }
//  return product;
//
//}
