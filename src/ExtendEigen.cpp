// See EigenTools.h for description.
// Seto Balian 04/10/2013

#include "ExtendEigen.h"
#include <Eigen/Dense>
#include <complex>

double ExtendEigen::cosineAngleBetween(const Eigen::Vector3d & a,
                                       const Eigen::Vector3d & b)
{
  return  ( a.dot(b) / (a.norm()*b.norm()) );
}

double ExtendEigen::maxAbsCoeff(const Eigen::Vector3d & a)  {
  return (a.cwiseAbs()).maxCoeff();
}

Eigen::MatrixXcd ExtendEigen::exponentiate(const Eigen::MatrixXcd & M,
                              const Eigen::MatrixXcd & eigenvectors,
                              const Eigen::VectorXd  & eigenvalues,
                              const double alpha)
{
  unsigned int dimension = static_cast<unsigned int>(M.rows());
  Eigen::MatrixXcd diagonal_eigenvalue_matrix(dimension,dimension);
  diagonal_eigenvalue_matrix.setZero();
  for (unsigned int i=0;i<dimension;i++) {
    diagonal_eigenvalue_matrix(i,i) = std::polar(1.0,-(eigenvalues(i))*alpha);
  }
  return eigenvectors*(diagonal_eigenvalue_matrix*(eigenvectors.adjoint()));

}


Eigen::MatrixXcd ExtendEigen::partialTrace(const Eigen::MatrixXcd & M,
                                     const unsigned int degrees_of_freedom)
{
  unsigned int dimension = static_cast<unsigned int> (M.rows());

  Eigen::MatrixXcd matrix_out(dimension/degrees_of_freedom,
                              dimension/degrees_of_freedom);
  unsigned int i=0, j=0;
  while (i<=dimension-degrees_of_freedom) {
    j = 0;
    while (j<=dimension-degrees_of_freedom) {
      matrix_out(i/degrees_of_freedom,j/degrees_of_freedom)
                = (M.block(i,j,degrees_of_freedom,degrees_of_freedom)).trace();
      j = j + degrees_of_freedom;
    }
    i = i + degrees_of_freedom;
  }


  return matrix_out;

}


Eigen::MatrixXcd ExtendEigen::tensorProduct(const Eigen::MatrixXcd & M,
                                      const Eigen::MatrixXcd & N)
{

  unsigned int dimension_N    = static_cast<unsigned int> ( N.rows() );
  unsigned int dimension_M    = static_cast<unsigned int> ( M.rows() );

  Eigen::MatrixXcd matrix_out(dimension_M*dimension_N,dimension_M*dimension_N);
  matrix_out.setZero();

  for (unsigned int i=0;i<dimension_M;i++) {
    for (unsigned int j=0;j<dimension_M;j++) {
      matrix_out.block(i*dimension_N,j*dimension_N,dimension_N,dimension_N)
                                                                     = M(i,j)*N;
    }
  }
  
  return matrix_out;

}


