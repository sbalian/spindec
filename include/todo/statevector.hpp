#ifndef STATEVECTOR_H
#define STATEVECTOR_H

// Quantum states: column vector of complex numbers
//
// Created  03/11/2011
// Modified 19/09/2012, 20/09/2012
// Seto Balian
// V1

#include "stdincludes.hpp"

using namespace Eigen;

class statevector
{
private:
  VectorXcd col_vec; // (Complex) column vector representation
public:
  statevector();
  statevector(const int dim);
  statevector(const VectorXcd & col_vec_in);

  VectorXcd get_col_vec() const;
  void set_col_vec(const VectorXcd & col_vec_in);
  void add_comp(const cmplxd & comp_in);

  RowVectorXcd get_row_vec() const;

  cmplxd get_comp(const int i) const;
  void set_comp(const int i,const cmplxd & comp_in);

  int dimension() const;

  double mod() const;
  double modSquared() const;

  statevector normalised() const;

  statevector operator+(const statevector & toadd) const;
  statevector operator-(const statevector & tosubtract) const;
  statevector operator*(const cmplxd & complexnumber) const;
  // dot product
  cmplxd operator*(const statevector & tomultiply) const;
  // tensor product
  statevector operator^(const statevector & statevector_in) const;

  void print() const;
  void print(const char c_or_r) const; // option: column or row

};

#endif // STATEVECTOR_H

