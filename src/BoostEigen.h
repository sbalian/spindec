#ifndef BOOSTEIGEN_H_
#define BOOSTEIGEN_H_

// BoostEigen
//
// Static methods to extend Eigen (linear algebra package).
// Note that the naming convention complies with that of Eigen, and is different
// from the rest of SpinDecoherence.
//
// TODO make this a proper template extension of Eigen. See Eigen doc.
//
// Seto Balian, Dec 4, 2013

#include <Eigen/Dense>

class BoostEigen
{

public:

  // Cosine of angle between real vectors a and b = a.b/ab
  static double cosAngleBetween(const Eigen::Vector3d & a,
                                const Eigen::Vector3d & b);

  // Maximum of ( abs(a1), abs(a2), abs(a3) ) for a real 3-vector
  static double maxAbsCoeff(const Eigen::Vector3d & a);
  
  // Exponentiate (element-wise complex exponentiation) for vectors
  template<typename ScalarType, int rows>
  static Eigen::Matrix<ScalarType, rows, 1>
    exp(const Eigen::Matrix<ScalarType, rows, 1> & a)
  {
    return (a.array().exp()).matrix();
  }

  // Tensor product for complex matrices
  // This evaluates C = A X B. For example, for 2 x 2 matrices,
  // C = A_11*B A_12*B
  //     A_21*B A_22*B
  // TODO Make this work for real matrices as well?
  //                                     (see broken commented out code
  //                                            at end of this file)
  static Eigen::MatrixXcd tensorProduct(const Eigen::MatrixXcd & A,
                                        const Eigen::MatrixXcd & B);
  
  // Tensor product for complex vectors
  // This evaluates c = a X b. For example, for 2-vectors,
  // C = a_1*B_1
  //     a_1*B_2
  //     a_2*B_1
  //     a_2*B_2
  // TODO Make this work for real vectors as well?
  // TODO Use the same method for both vectors and matrices?
  static Eigen::VectorXcd tensorProduct(const Eigen::VectorXcd & a,
                                        const Eigen::VectorXcd & b);


  // Partial trace
  // Given C = A x B, where x denotes the tensor product,
  // in addition to the dimension of B, this method outputs
  // Tr[B] A (where Tr denotes the sum of the diagonal elements)
  // TODO Make this work for real matrices as well?
  static Eigen::MatrixXcd partialTrace(const Eigen::MatrixXcd & AB,
                                       const unsigned int dimension_B);
  
  // Spectral decomposition (for complex square matrices)
  // Calculates A = V D V-1, where D is the diagonal of eigenvalues,
  // and V is the eigenvector matrix (col -> evector)
  // TODO Make this for real matrices as well?
  static Eigen::MatrixXcd spectralDecomposition(
                                         const Eigen::MatrixXcd & eigenvectors,
                                         const Eigen::VectorXcd & eigenvalues);
  // For Hermitian matrices (faster) V-1 = V'
  static Eigen::MatrixXcd hermitianSpectralDecomposition(
                                         const Eigen::MatrixXcd & eigenvectors,
                                         const Eigen::VectorXd & eigenvalues);
                                         // eigenvalues must be real

};

#endif // BOOSTEIGEN_H_

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
