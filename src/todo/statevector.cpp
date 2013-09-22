// Quantum states: column vector of complex numbers
//
// Created  03/11/2011
// Modified 19/09/2012, 20/09/2012
// Seto Balian
// V1

#include "stdincludes.hpp"
#include "statevector.hpp"

using namespace Eigen;
using namespace std;

statevector::statevector() {
//
}

statevector::statevector(const int dim) {
  VectorXcd zeros(dim);
  zeros.setZero();
  set_col_vec(zeros);
  return;
}

statevector::statevector(const VectorXcd & col_vec_in) {
  set_col_vec(col_vec_in);
}

VectorXcd statevector::get_col_vec() const {
  return col_vec;
}

void statevector::set_col_vec(const VectorXcd & col_vec_in) {
  col_vec = col_vec_in;
  return;
}

void statevector::add_comp(const cmplxd & comp_in) {
  VectorXcd new_col_vec(dimension()+1);
  int i;
  for (i=0;i<dimension();i++) {
    new_col_vec(i) = get_comp(i);
  }
  new_col_vec(dimension()) = comp_in;
  col_vec = new_col_vec;
  return;
}

RowVectorXcd statevector::get_row_vec() const {
  return col_vec.adjoint();
}

cmplxd statevector::get_comp(const int i) const {
  return col_vec(i);
}
  
void statevector::set_comp(const int i,const cmplxd & comp_in) {
  col_vec(i) = comp_in;
  return;
}

int statevector::dimension() const {
  return col_vec.rows();
}

double statevector::mod() const {
  return sqrt( modSquared() );
}

double statevector::modSquared() const {
  cmplxd modulus_sq = get_row_vec()*col_vec; // this is real
  return real( modulus_sq );
}

statevector statevector::normalised() const {
  return statevector ( col_vec / (cmplxd(mod(),0.0)) );
}

statevector statevector::operator+(const statevector & toadd) const {
  return statevector (col_vec + toadd.col_vec);
}

statevector statevector::operator-(const statevector & tosubtract) const {
  return statevector (col_vec - tosubtract.col_vec);
}

statevector statevector::operator*(const cmplxd & complexnumber) const {
  return statevector ( col_vec*complexnumber);
}

cmplxd statevector::operator*(const statevector & tomultiply) const {
  return get_row_vec()*(tomultiply.get_col_vec());
}

statevector statevector::operator^(const statevector & statevector_in) const {
  VectorXcd tensorproduct(dimension()*statevector_in.dimension());
  int i, j;
  int k = 0;
  for (i=0;i<dimension();i++) {
    for (j=0;j<statevector_in.dimension();j++) {
      tensorproduct(k) = (col_vec(i))*(statevector_in.col_vec(j));
      k = k + 1;
    }
  }
  return statevector(tensorproduct);
}

void statevector::print() const {
  cout << col_vec << endl;
  return;
}

void statevector::print(const char c_or_r) const {
  if (c_or_r == 'r') {
    cout << get_row_vec() << endl;
  } else {
      print();
    }
  return;
}

