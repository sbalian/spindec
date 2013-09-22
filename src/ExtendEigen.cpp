// See EigenTools.h for description.
// Seto Balian 16/09/2013

#include "ExtendEigen.h"
#include <Eigen/Dense>
#include <complex>

double ExtendEigen::cosineAngleBetween(const Eigen::Vector3d & a,
                                       const Eigen::Vector3d & b) {
  return  ( a.dot(b) / (a.norm()*b.norm()) );
}

double ExtendEigen::maxAbsCoeff(const Eigen::Vector3d & a)  {
  return (a.cwiseAbs()).maxCoeff();
}

Eigen::MatrixXcd ExtendEigen::exponentiate(const Eigen::MatrixXcd & M,
                              const Eigen::MatrixXcd & eigenvectors,
                              const Eigen::VectorXd  & eigenvalues,
                              const double alpha) {

  unsigned int dimension = static_cast<unsigned int>(M.rows());
  Eigen::MatrixXcd diagExpEvalues(dimension,dimension);
  diagExpEvalues.setZero();
  unsigned int i;
  for (i=0;i<dimension;i++) {
    diagExpEvalues(i,i) = std::polar(1.0,-(eigenvalues(i))*alpha);
  }
  return eigenvectors*(diagExpEvalues*(eigenvectors.adjoint()));


}


Eigen::MatrixXcd ExtendEigen::partialTrace(const Eigen::MatrixXcd & M,
                                      const unsigned int dof) {

  unsigned int dim = static_cast<unsigned int> (M.rows());

  Eigen::MatrixXcd matrixOut(dim/dof,dim/dof);
  unsigned int i = 0;
  unsigned int j = 0;
  while (i<=dim-dof) {
    j = 0;
    while (j<=dim-dof) {
      matrixOut(i/dof,j/dof) = (M.block(i,j,dof,dof)).trace();
      j = j + dof;
    }
    i = i + dof;
  }


  return matrixOut;

}


Eigen::MatrixXcd ExtendEigen::tensorProduct(const Eigen::MatrixXcd & M,
                                      const Eigen::MatrixXcd & N) {

  unsigned int dimN    = static_cast<unsigned int> ( N.rows() );
  unsigned int dimM    = static_cast<unsigned int> ( M.rows() );

  Eigen::MatrixXcd matrixOut(dimM*dimN,dimM*dimN);
  matrixOut.setZero();

  unsigned int i,j;
  for (i=0;i<dimM;i++) {
    for (j=0;j<dimM;j++) {

      matrixOut.block(i*dimN,j*dimN,dimN,dimN) = M(i,j)*N;

    }
  }

  
  return matrixOut;

}


