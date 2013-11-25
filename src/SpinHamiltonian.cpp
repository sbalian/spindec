// See SpinHamiltonian.h for description.
// Seto Balian 25/11/2013

#include "SpinHamiltonian.h"
#include "Errors.h"

void quit_if_not_diagonal(const SpinHamiltonian & hamiltonian) {
  if (!hamiltonian.is_diagonalized()) {
    Errors::quit(*this,"Spin Hamiltonian is not diagonal.");
  }
  return;
}

SpinHamiltonian::SpinHamiltonian() {
  is_built_ = 0;
  is_diagonalized_ = 0;
  Named::set_class_name("SpinHamiltonian");
}

void build(const SpinInteractionGraph & interaction_graph) {
 
  if (is_built()) {
    Errors::quit(*this,
      "Spin Hamiltonian already built. You may want to use rebuild().");
  }
  
  // build the basis
  basis_.build();
  
  
}


bool SpinHamiltonian::is_built() const {
  return is_built_;
}

bool SpinHamiltonian::is_diagonalized() const {
  return is_diagonalized_;
}

Eigen::MatrixXcd SpinHamiltonian::get_eigenvectors() const {
  quit_if_not_diagonal(*this);
  return eigenvectors_;
}

Eigen::VectorXd SpinHamiltonian::get_eigenvalues() const  {
  quit_if_not_diagonal(*this);
  return eigenvalues_;
}


Eigen::VectorXcd SpinHamiltonian::get_eigenvector(
                                      const unsigned int index) const {
  return get_eigenvectors().col(index);
}

double SpinHamiltonian::get_eigenvalue(const unsigned int index) const {
  return get_eigenvalues()(index);
}
