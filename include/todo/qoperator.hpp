#ifndef QOPERATOR_H
#define QOPERATOR_H

// (Quantum) operator on a Hilbert space in the (complex) matrix representation.
// Acts on complex vectors (class "statevector").
// NOTE: must be Hermitian
//
// Created  05/11/2011
// Modified 19/09/2012, 20/09/2012, 22/09/2012, 26/09/2012, 27/09/2012, 28/09/2012, 30/09/2012, 03/10/2012
// Seto Balian
// V1

#include "stdincludes.hpp"
#include "statevector.hpp"

using namespace std;
using namespace Eigen;

class qoperator : public named
{
private:
  MatrixXcd matrix_rep;    // (Complex) matrix representation
  MatrixXcd eigenvectors;
  VectorXd  eigenvalues;   // Eigenvalues of a Hermitian matrix are always real

public:
  qoperator();
  qoperator(const int dim);
  qoperator(const MatrixXcd & matrix_rep_in);
  qoperator(const MatrixXcd & matrix_rep_in, const VectorXd & eigenvalues_in, const MatrixXcd & eigenvectors_in);
  qoperator(const statevector & state, const statevector & dualstate);

  MatrixXcd get_matrix_rep() const;
  void set_matrix_rep(const MatrixXcd & matrix_rep_in);
  void set_matrix_rep(const statevector & state, const statevector & dualstate);

  VectorXd  get_eigenvalues() const;
  MatrixXcd get_eigenvectors() const;

  void set_eigenvalues(const VectorXd & eigenvalues_in);
  void set_eigenvectors(const MatrixXcd & eigenvectors_in);
  
  cmplxd get_element(const int i, const int j) const;
  void set_element(const int i, const int j, const cmplxd & element_in);

  int dimension() const;

  qoperator operator+(const qoperator & toadd) const;
  qoperator operator-(const qoperator & tosubtract) const;
  qoperator operator*(const cmplxd & complexnumber) const;
  statevector operator*(const statevector & operand) const;
  qoperator operator^(const qoperator & qoperator_in) const; // tensor product

  void diagonalise(const string & option);
  void diagonalise_zheev();
  void diagonalise_eigen();
  void diagonalise(); // same as diagonalise_zheev

  void set_zeros();
  void set_eigenvalues_zeros();
  void set_eigenvectors_zeros();

  void print(const string & option) const;

// This method calculates the following given real alpha:
// e^(-i M alpha) = Sum_over_n_up_to_dim { |psi_n> e^(-i E_n alpha) <psi_n| },
// where M is the matrix, |psi_n> are its eigenvectors, E_n
// the eigenvalues and dim is the dimension of the Hilbert space.
  qoperator exponentiate(const double alpha) const;

  qoperator partial_trace(const int degrees_of_freedom) const;

  VectorXcd get_eigenvector(ArrayXi levels, const int level) const;

  static qoperator Identity(const int dim);

};

#endif // QOPERATOR_H


