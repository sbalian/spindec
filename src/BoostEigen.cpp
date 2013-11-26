// See BoostEigen.h for description.
// Seto Balian, November 26, 2013

#include "BoostEigen.h"
#include "Errors.h"
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
Eigen::VectorXd BoostEigen::exp(const Eigen::VectorXd & a) {
  return (a.array().exp()).matrix();
}


Eigen::MatrixXcd BoostEigen::spectralDecomposition(
                                         const Eigen::MatrixXcd & eigenvectors,
                                         const Eigen::VectorXcd & eigenvalues) {
  return eigenvectors*(eigenvalues.asDiagonal())*(eigenvectors.inverse());
}
Eigen::MatrixXcd BoostEigen::hermitianSpectralDecomposition(
                                         const Eigen::MatrixXcd & eigenvectors,
                                         const Eigen::VectorXd & eigenvalues) {
  return eigenvectors*(eigenvalues.asDiagonal())*(eigenvectors.transpose());
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

void BoostEigen::addCol(Eigen::ArrayXXd & array,
                const Eigen::ArrayXd & column) {
  
  if (column.rows() != array.rows()) {
    Errors::quit("BoostEigen","Can't add column: dimension mismatch.");
  }
  
  Eigen::ArrayXXd new_array(array.rows(),array.cols()+1);
  
  for (unsigned int i=0;i<array.cols();i++) {
    
    new_array.col(i) = array.col(i);
    
  }
  
  new_array.col(array.cols()) = column;
  array = new_array;
  return;
  
}

void BoostEigen::addRow(Eigen::ArrayXXd & array,
                const Eigen::ArrayXd & row) {

  if (row.cols() != array.cols()) {
    Errors::quit("BoostEigen","Can't add column: dimension mismatch.");
  }
  
  Eigen::ArrayXXd new_array(array.rows()+1,array.cols());
  
  for (unsigned int i=0;i<array.rows();i++) {
    
    new_array.row(i) = array.row(i);
    
  }
  
  new_array.row(array.rows()) = row;
  array = new_array;
  return;
  
}


void BoostEigen::addElement(Eigen::ArrayXd & array, const double element) {
  Eigen::ArrayXd new_array(array.size()+1);
  for (unsigned int i=0;i<array.size();i++) {  
    new_array(i) = array(i);
  }
  new_array(array.size()) = element;
  array = new_array;
  return;
}


void BoostEigen::horizontalAppend(Eigen::ArrayXXd & array,
                              const Eigen::ArrayXXd & to_append) {
  if (array.rows() != to_append.rows()) {
    Errors::quit("BoostEigen","Can't append: dimension mismatch.");
  }
  for (unsigned int i=0;i<to_append.cols();i++) {
    BoostEigen::addCol(array,to_append.col(i));
  }
  return;
}
void BoostEigen::verticalAppend(Eigen::ArrayXXd & array,
                              const Eigen::ArrayXXd & to_append) {
  if (array.cols() != to_append.cols()) {
    Errors::quit("BoostEigen","Can't append: dimension mismatch.");
  }
  for (unsigned int i=0;i<to_append.rows();i++) {
    BoostEigen::addRow(array,to_append.row(i));
  }
  return;
}
