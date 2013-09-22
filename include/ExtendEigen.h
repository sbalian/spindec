#ifndef EXTENDEIGEN_H
#define EXTENDEIGEN_H

// ExtendEigen
//
// Extend Eigen linear algebra package.
//
// Seto Balian 16/09/2013

#include <Eigen/Dense>

class ExtendEigen
{

public:

  // 3-vector

  // Cosine of angle between vectors a and b = a.b/ab
  static double cosineAngleBetween(const Eigen::Vector3d & a,
                                   const Eigen::Vector3d & b);

  // Maximum ( abs(x), abs(y), abs(z) ) 
  static double maxAbsCoeff(const Eigen::Vector3d & a);

  // MatrixXcd

  // Exponentiate (Hermitian)
  // This method calculates the following given real alpha:
  // e^(-i M alpha) = Sum_over_n_up_to_dim { |psi_n> e^(-i E_n alpha) <psi_n| },
  // where M is the matrix, |psi_n> are its eigenvectors, E_n
  // the eigenvalues and dim is the dimension of the matrix.
  static Eigen::MatrixXcd exponentiate(const Eigen::MatrixXcd & M,
                                       const Eigen::MatrixXcd & eigenvectors,
                                       const Eigen::VectorXd  & eigenvalues,
                                       const double alpha);

  // Partial trace
  static Eigen::MatrixXcd partialTrace(const Eigen::MatrixXcd & M,
                                       const unsigned int dof);

  // Tensor product
  static Eigen::MatrixXcd tensorProduct(const Eigen::MatrixXcd & M,
                                        const Eigen::MatrixXcd & N);
  
};

#endif // EXTENDEIGEN_H

