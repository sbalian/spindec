#ifndef SPINHAMILTONIAN_H
#define SPINHAMILTONIAN_H

// SpinHamiltonian
//
// Spin Hamiltonian in the Zeeman basis, built using spin interaction graphs.
// Returns eigenvectors and eigenvalues.
//
// Seto Balian, November 27, 2013

#include <Eigen/Dense>

#include "ZeemanBasis.h"
#include "SpinInteractionGraph.h"

class SpinHamiltonian
{

private:
  
  Eigen::MatrixXcd matrix_;
  ZeemanBasis basis_;
  
  SpinInteractionGraph interaction_graph_;  
  
  Eigen::MatrixXcd eigenvectors_; // stored as columns
  Eigen::VectorXd eigenvalues_;
  
  bool is_built_;
  bool is_diagonalized_;
  
  void diagonalize();
  
public:
  SpinHamiltonian();
  
  void build(const SpinInteractionGraph & interaction_graph);
  void update(const SpinInteractionGraph & interaction_graph);
  
  Eigen::MatrixXcd get_eigenvectors() const;
  Eigen::VectorXd  get_eigenvalues() const; 
  
  Eigen::VectorXcd get_eigenvector(const unsigned int index) const;
  double get_eigenvalue(const unsigned int index) const;  

  bool is_diagonalized() const;
  bool is_built() const;
  

};

#endif // SPINHAMILTONIAN_H
