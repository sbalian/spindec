#ifndef SPINHAMILTONIAN_H_
#define SPINHAMILTONIAN_H_

// SpinHamiltonian
//
// Effective spin Hamiltonian built from spin interaction graphs.
// Can diagonalize and get unitary time evolution matrix.
// No time dependence in Hamiltonian. TODO generalize
// Units: M rad s-1.
//
// Seto Balian, Dec 10, 2013

#include <Eigen/Dense>
#include <string>

#include "SpinInteractionGraph.h"
#include "SpinOperator.h"
#include "HermitianEigenspectrum.h"

class SpinHamiltonian : public SpinOperator
{
private:

  SpinBasis built_basis(const SpinInteractionGraph & graph) const;
  Eigen::MatrixXcd filled_matrix(const SpinInteractionGraph & graph) const;

public:

  SpinHamiltonian();
  SpinHamiltonian(const SpinInteractionGraph & graph);
  
  // TODO describe
  void update(const SpinInteractionGraph & graph);
  
  // Unitary matrix
  // U = \sum{n} ( |E_n> exp(- i E_n t) <E_n| )
  // E_n: eigenvalues
  // |E_n>: eigenvectors
  // t: time (real double) units: microseconds (energies in M rad s-1)
  // (for time independent spin Hamiltonians ...)
  Eigen::MatrixXcd evolutionMatrix(const HermitianEigenspectrum & spectrum,
      const double time) const;

};

#endif // SPINHAMILTONIAN_H_
