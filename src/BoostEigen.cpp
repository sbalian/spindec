// See BoostEigen.h for description.
// Seto Balian 01/11/2013

#include "BoostEigen.h"
#include <Eigen/Dense>
#include <complex>

double BoostEigen::cosAngleBetween(const Eigen::Vector3d & a,
                                       const Eigen::Vector3d & b)
{
  return  ( a.dot(b) / (a.norm()*b.norm()) );
}

double BoostEigen::maxAbsCoeff(const Eigen::Vector3d & a)  {
  return (a.cwiseAbs()).maxCoeff();
}

unsigned int BoostEigen::dimension(const Eigen::MatrixXcd & A) {
  return static_cast<unsigned int> (A.rows());
}

Eigen::VectorXcd BoostEigen::exp(const Eigen::VectorXcd & a) {
  return (a.array().exp()).matrix();
}

Eigen::MatrixXcd BoostEigen::spectralDecomposition(
                                         const Eigen::MatrixXcd & eigenvectors,
                                         const Eigen::VectorXcd & eigenvalues) {
  return eigenvectors*(eigenvalues.asDiagonal())*(eigenvectors.inverse());
}

Eigen::MatrixXcd BoostEigen::tensorProduct(const Eigen::MatrixXcd & A,
                                      const Eigen::MatrixXcd & B)
{

  unsigned int dimension_A    = dimension(A);
  unsigned int dimension_B    = dimension(B);
  Eigen::MatrixXcd AB(dimension_A*dimension_B,dimension_A*dimension_B);//output

  // consistently with the definition of the parital trace
  for (unsigned int i=0;i<dimension_A;i++) {
    for (unsigned int j=0;j<dimension_A;j++) {
      AB.block(i*dimension_B,j*dimension_B,dimension_B,dimension_B)
                                                                     = A(i,j)*B;
    }
  }

  return AB;

}

Eigen::MatrixXcd BoostEigen::partialTrace(const Eigen::MatrixXcd & AB,
                                       const unsigned int dimension_B)
{

  unsigned int dimension_AB = dimension(AB);
  unsigned int dimension_A  = dimension_AB/dimension_B;
  Eigen::MatrixXcd TrB_A(dimension_A,dimension_A); // output

  // consistently with the definition of the tensor product
  unsigned int i=0, j=0;
  while (i<=dimension_AB-dimension_B) {
    j = 0;
    while (j<=dimension_AB-dimension_B) {
      TrB_A(i/dimension_B,j/dimension_B)
                = (AB.block(i,j,dimension_B,dimension_B)).trace();
      j += dimension_B;
    }
    i += dimension_B;
  }

  return TrB_A;

}
