// See ZeemanBasis.h for description.
// Seto Balian 25/11/2013

#include <Eigen/Dense>

#include "ZeemanBasis.h"
#include "BoostEigen.h"

ZeemanBasis::ZeemanBasis() {
  Named::set_class_name("ZeemanBasis");
}

ZeemanBasis::ZeemanBasis(const Eigen::ArrayXXd & basis) {
  set_basis(basis);
  Named::set_class_name("ZeemanBasis");
}

Eigen::ArrayXXd ZeemanBasis::get_basis() const {
  return basis_;
}

void ZeemanBasis::set_basis(const Eigen::ArrayXXd & basis) {
  basis_ = basis;
  return;
}

void ZeemanBasis::combine(const ZeemanBasis & to_combine){
  return;
}

void ZeemanBasis::append(const ZeemanBasis & to_append) {
  BoostEigen::horizontalAppend(basis_,to_append.get_basis());
  return;
}

unsigned int ZeemanBasis::dimension() const {
  return static_cast<unsigned int>(basis_.rows());
}

unsigned int ZeemanBasis::num_spins() const {
  return static_cast<unsigned int>(basis_.cols());
}
