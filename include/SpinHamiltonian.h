#ifndef SPINHAMILTONIAN_H
#define SPINHAMILTONIAN_H

// SpinHamiltonian
//
// Spin Hamiltonian in the Zeeman basis, built using spin interaction graphs.
// Returns eigenvectors and eigenvalues.
//
// Seto Balian 19/11/2013

#include <Eigen/Dense>

class SpinHamiltonian
{

private:
  
  Eigen::MatrixXcd matrix_;
  ZeemanBasis basis_;
  SpinInteractionGraph interaction_graph_;
  
  Eigen::MatrixXcd eigenvectors_;
  Eigen::VectorXcd eigenvalues_;
  
public:
  SpinHamiltonian();
  
  SpinHamiltonian(const SpinInteractionGraph & interaction_graph);
  
  void build();
  
  void update(const SpinInteractionGraph & interaction_graph);
  
  void diagonalize();
  
  Eigen::MatrixXcd eigenvectors() const;
  Eigen::VectorXcd eigenvalues() const;

};


#endif // SPINHAMILTONIAN_H
