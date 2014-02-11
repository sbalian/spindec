// See BoostEigen.h for description.
// Seto Balian, Feb 11, 2014

#include "BoostEigen.h"
#include <Eigen/Dense>

namespace SpinDecoherence
{

double BoostEigen::cosAngleBetween(const d3vector & a,
                                       const d3vector & b)
{
  return  ( a.dot(b) / (a.norm()*b.norm()) );
}

double BoostEigen::maxAbsCoeff(const d3vector & a)
{
  return (a.cwiseAbs()).maxCoeff();
}

cdvector BoostEigen::exp(const cdvector & a)
{
  return Eigen::ArrayXcd(a.array().exp()).matrix();
}

cdmatrix BoostEigen::tensorProduct(const cdmatrix & A,
                                           const cdmatrix & B)
{
  unsigned int dimension_A    = A.rows();
  unsigned int dimension_B    = B.rows();
  unsigned int dimension_AB    = dimension_A*dimension_B;
  
  //output
  cdmatrix product(dimension_AB,dimension_AB);
  
  // consistently with other methods
  for (unsigned int i=0;i<dimension_A;i++) {
    for (unsigned int j=0;j<dimension_A;j++) {
      product.block(i*dimension_B,j*dimension_B,dimension_B,dimension_B)
                                                             = A(i,j)*B;
    }
  }
  return product;
}

cdvector BoostEigen::tensorProduct(const cdvector & a,
                                                  const cdvector & b)
{
  // output
  cdvector product(a.rows()*b.rows());
  
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

cdmatrix BoostEigen::partialTrace(const cdmatrix & AB,
                                       const unsigned int dimension_B)
{

  unsigned int dimension_AB = AB.rows();
  unsigned int dimension_A  = dimension_AB/dimension_B;
  
  // output
  cdmatrix partial_trace(dimension_A,dimension_A);

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

cdmatrix BoostEigen::spectralDecomposition(
    const cdmatrix& eigenvectors, const cdvector& eigenvalues)
{
  return eigenvectors*(eigenvalues.asDiagonal())*(eigenvectors.inverse());
}

cdmatrix BoostEigen::unitarySpectralDecomposition(
    const cdmatrix& eigenvectors, const cdvector& eigenvalues)
{
  return eigenvectors*(eigenvalues.asDiagonal())*(eigenvectors.adjoint());
}

} // namespace SpinDecoherence
