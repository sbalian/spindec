// See BoostEigen.h for description.
// Seto Balian, Dec 10, 2013

#include "BoostEigen.h"
#include <Eigen/Dense>

double BoostEigen::cosAngleBetween(const Eigen::Vector3d & a,
                                       const Eigen::Vector3d & b)
{
  return  ( a.dot(b) / (a.norm()*b.norm()) );
}

double BoostEigen::maxAbsCoeff(const Eigen::Vector3d & a)
{
  return (a.cwiseAbs()).maxCoeff();
}

Eigen::VectorXcd BoostEigen::exp(const Eigen::VectorXcd & a)
{
  return Eigen::ArrayXcd(a.array().exp()).matrix();
}

Eigen::MatrixXcd BoostEigen::tensorProduct(const Eigen::MatrixXcd & A,
                                           const Eigen::MatrixXcd & B)
{
  unsigned int dimension_A    = A.rows();
  unsigned int dimension_B    = B.rows();
  unsigned int dimension_AB    = dimension_A*dimension_B;
  
  //output
  Eigen::MatrixXcd product(dimension_AB,dimension_AB);
  
  // consistently with other methods
  for (unsigned int i=0;i<dimension_A;i++) {
    for (unsigned int j=0;j<dimension_A;j++) {
      product.block(i*dimension_B,j*dimension_B,dimension_B,dimension_B)
                                                             = A(i,j)*B;
    }
  }
  return product;
}

Eigen::VectorXcd BoostEigen::tensorProduct(const Eigen::VectorXcd & a,
                                                  const Eigen::VectorXcd & b)
{
  // output
  Eigen::VectorXcd product(a.rows()*b.rows());
  
  // consistently with other methods
  unsigned int k = 0;
  for (unsigned int i=0;i<a.rows();i++) {
    for (unsigned int j=0;j<b.rows();j++) {
      product(k) = a(i)*b(j);
      k += 1;
    }
  }
  return product;
}

Eigen::MatrixXcd BoostEigen::partialTrace(const Eigen::MatrixXcd & AB,
                                       const unsigned int dimension_B)
{

  unsigned int dimension_AB = AB.rows();
  unsigned int dimension_A  = dimension_AB/dimension_B;
  
  // output
  Eigen::MatrixXcd partial_trace(dimension_A,dimension_A);

  // consistently with other methods
  unsigned int i=0, j=0;
  while (i<=dimension_AB-dimension_B) {
    j = 0;
    while (j<=dimension_AB-dimension_B) {
      partial_trace(i/dimension_B,j/dimension_B)
                = (AB.block(i,j,dimension_B,dimension_B)).trace();
      j += dimension_B;
    }
    i += dimension_B;
  }
  return partial_trace;
}

Eigen::MatrixXcd BoostEigen::spectralDecomposition(
    const Eigen::MatrixXcd& eigenvectors, const Eigen::VectorXcd& eigenvalues)
{
  return eigenvectors*(eigenvalues.asDiagonal())*(eigenvectors.inverse());
}

Eigen::MatrixXcd BoostEigen::unitarySpectralDecomposition(
    const Eigen::MatrixXcd& eigenvectors, const Eigen::VectorXcd& eigenvalues)
{
  return eigenvectors*(eigenvalues.asDiagonal())*(eigenvectors.adjoint());
}

