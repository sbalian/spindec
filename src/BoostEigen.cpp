// See BoostEigen.h for description.
// Seto Balian, Mar 6, 2014

#include "SpinDec/BoostEigen.h"
#include <Eigen/Dense>

namespace SpinDec
{

double BoostEigen::cosAngleBetween(const ThreeVector & a,
                                       const ThreeVector & b)
{
  return  ( a.dot(b) / (a.norm()*b.norm()) );
}

double BoostEigen::maxAbsCoeff(const ThreeVector & a)
{
  return (a.cwiseAbs()).maxCoeff();
}

ComplexVector BoostEigen::exp(const ComplexVector & a)
{
  return Eigen::ArrayXcd(a.array().exp()).matrix();
}

ComplexMatrix BoostEigen::tensorProduct(const ComplexMatrix & A,
                                           const ComplexMatrix & B)
{
  unsigned int dimension_A    = A.rows();
  unsigned int dimension_B    = B.rows();
  unsigned int dimension_AB    = dimension_A*dimension_B;
  
  //output
  ComplexMatrix product(dimension_AB,dimension_AB);
  
  // consistently with other methods
  for (unsigned int i=0;i<dimension_A;i++) {
    for (unsigned int j=0;j<dimension_A;j++) {
      product.block(i*dimension_B,j*dimension_B,dimension_B,dimension_B)
                                                             = A(i,j)*B;
    }
  }
  return product;
}

ComplexVector BoostEigen::tensorProduct(const ComplexVector & a,
                                                  const ComplexVector & b)
{
  // output
  ComplexVector product(a.rows()*b.rows());
  
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

ComplexMatrix BoostEigen::partialTrace(const ComplexMatrix & AB,
                                       const unsigned int dimension_B)
{

  unsigned int dimension_AB = AB.rows();
  unsigned int dimension_A  = dimension_AB/dimension_B;
  
  // output
  ComplexMatrix partial_trace(dimension_A,dimension_A);

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

ComplexMatrix BoostEigen::spectralDecomposition(
    const ComplexMatrix& eigenvectors, const ComplexVector& eigenvalues)
{
  return eigenvectors*(eigenvalues.asDiagonal())*(eigenvectors.inverse());
}

ComplexMatrix BoostEigen::unitarySpectralDecomposition(
    const ComplexMatrix& eigenvectors, const ComplexVector& eigenvalues)
{
  return eigenvectors*(eigenvalues.asDiagonal())*(eigenvectors.adjoint());
}

} // namespace SpinDec
