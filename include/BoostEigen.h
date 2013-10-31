#ifndef BOOSTEIGEN_H
#define BOOSTEIGEN_H

// BoostEigen
//
// Static methods to extend Eigen (linear algebra package).
// Note that the naming convention complies with that of Eigen, and is different
// to the rest of SpinDecoherence ...
//
// Seto Balian 31/10/2013

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
// MatrixXcd and VectorXcd
// *************************************************

  // Dimension = number of rows
  static unsigned int dimension(const Eigen::MatrixXcd & A);

  // Exponentiate (element-wise complex exponentiation)
  static Eigen::VectorXcd exp(const Eigen::VectorXcd & a);

  // Spectral decomposition
  // Calculates A = V D V-1, where D is the diagonal of eigenvalues,
  // and V is the eigenvector matrix (col -> evector)
  static Eigen::MatrixXcd spectralDecomposition(
                                         const Eigen::MatrixXcd & eigenvectors,
                                         const Eigen::VectorXcd & eigenvalues);

  // Tensor product
  static Eigen::MatrixXcd tensorProduct(const Eigen::MatrixXcd & A,
                                        const Eigen::MatrixXcd & B);

  // Partial trace
  // Given C = A x B, where x denotes the tensor product,
  // in addition to the dimension of B, this method outputs
  // Tr[B] A
  static Eigen::MatrixXcd partialTrace(const Eigen::MatrixXcd & AB,
                                       const unsigned int dimension_B);


  
};

#endif // BOOSTEIGEN_H

