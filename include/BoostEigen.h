#ifndef BOOSTEIGEN_H
#define BOOSTEIGEN_H

// BoostEigen
//
// Static methods to extend Eigen (linear algebra package).
// Note that the naming convention complies with that of Eigen, and is different
// from the rest of SpinDecoherence ...
//
// Seto Balian 25/11/2013

#include <Eigen/Dense>

class BoostEigen
{

public:

// *************************************************
// 3-vector
// *************************************************

  // Cosine of angle between vectors a and b = a.b/ab
  static double cosAngleBetween(const Eigen::Vector3d & a,
                                   const Eigen::Vector3d & b);

  // Maximum of ( abs(a.x), abs(a.y), abs(a.z) ) 
  static double maxAbsCoeff(const Eigen::Vector3d & a);

// *************************************************
// MatrixXcd and VectorXcd - Linear algebra
// *************************************************

  // Dimension = number of rows
  static unsigned int dimension(const Eigen::MatrixXcd & A);

  // Exponentiate (element-wise complex exponentiation)
  // @todo Use a base class to avoid the repetition here ...
  static Eigen::VectorXcd exp(const Eigen::VectorXcd & a);
  static Eigen::VectorXd exp(const Eigen::VectorXd & a);


  // Spectral decomposition
  // Calculates A = V D V-1, where D is the diagonal of eigenvalues,
  // and V is the eigenvector matrix (col -> evector)
  static Eigen::MatrixXcd spectralDecomposition(
                                         const Eigen::MatrixXcd & eigenvectors,
                                         const Eigen::VectorXcd & eigenvalues);
  // For Hermitian matrices (faster) V-1 = V'
  static Eigen::MatrixXcd hermitianSpectralDecomposition(
                                         const Eigen::MatrixXcd & eigenvectors,
                                         const Eigen::VectorXd & eigenvalues);
                                         // eigenvalues must be real


  // Tensor product
  // This evaluates C = A X B. For example, for 2 x 2 matrices,
  // C = A_11*B A_12*B
  //     A_21*B A_22*B
  static Eigen::MatrixXcd tensorProduct(const Eigen::MatrixXcd & A,
                                        const Eigen::MatrixXcd & B);

  // Partial trace
  // Given C = A x B, where x denotes the tensor product,
  // in addition to the dimension of B, this method outputs
  // Tr[B] A (where Tr denotes the sum of the diagonal elements)
  static Eigen::MatrixXcd partialTrace(const Eigen::MatrixXcd & AB,
                                       const unsigned int dimension_B);
  
// *************************************************
// ArrayXXd
// *************************************************
  // @todo Use base classes here to apply to other objects?
  static void addCol(Eigen::ArrayXXd & array,
                const Eigen::ArrayXd & column);
  static void addRow(Eigen::ArrayXXd & array,
                const Eigen::ArrayXd & row);
  static void addElement(Eigen::ArrayXd & array, const double element);
  static void horizontalAppend(Eigen::ArrayXXd & array,
                              const Eigen::ArrayXXd & to_append);
  static void verticalAppend(Eigen::ArrayXXd & array,
                              const Eigen::ArrayXXd & to_append);
  
};

#endif // BOOSTEIGEN_H

